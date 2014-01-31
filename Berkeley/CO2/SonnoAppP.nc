/* "Copyright (c) 2008 The Regents of the University  of California.
 * All rights reserved."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 */

/**
 * ACme Energy Monitor application adapted for HydroWatch+Sonno node
 * @author Fred Jiang <fxjiang@eecs.berkeley.edu>
 * @author Stephen Dawson-Haggerty <stevedh@eecs.berkeley.edu>
 * @author Jay Taneja <taneja@cs.berkeley.edu>
 * @version $Revision: 1.2 $
 */

#include <ip.h>
#include <lib6lowpan.h>
#include <IPDispatch.h>
#include <Shell.h>
#include <Timer.h>
#include <BinaryShell.h>

// #include "blip_printf.h"
#include "CO2Report.h"
#include "ACmeShell.h"

#define PERIOD 15
#define SEQUENCE_SAVE_EVERY 500

module SonnoAppP {
  uses {
    interface Boot;
    interface SplitControl as RadioControl;
    interface UDP as ReportSend;
    interface Leds;

    interface Statistics<route_statistics_t> as RouteStats;
    interface Timer<TMilli> as SenseTimer;
    interface Get<uint32_t> as UnixTime;
    interface Random;
    interface LocalIeeeEui64;
    interface CC2420Config;

    /* config storage interfaces */
    interface Mount;
    interface ConfigStorage;

    /* shell commands */
    interface BinaryCommand as ReadConfig;
    interface BinaryCommand as WriteConfig;
    interface BinaryCommand as ReadData;

#define N_SENSORS 3
	interface Read<uint16_t> as ReadSonnoSensor;
	interface Read<uint16_t> as Humidity;
	interface Read<uint16_t> as Temperature;
	interface Read<uint16_t> as ReadPAR;
	interface Read<uint16_t> as ReadTSR;
	interface Read<uint16_t> as ReadBattVol;
	interface Read<uint16_t> as ReadIntVol;
  }

} implementation {

  nx_struct co2_report report;
  uint16_t senseDoneCnt = 0;

  nx_struct {
    nx_struct cmd_payload hdr;
    nx_struct co2_report report;
  } read_reply;

  /* Change this whenever the format of the data stored on flash
     changes, so we can update the data in the volume.

     This causes the configuration to be overwritten with the default.
  */
#define CONFIG_MAGIC 0x8ac2
  /* this whole struct gets saved to our ConfigStorage volume; put
     things that should be saved in here. */
  struct {
    uint16_t magic;
    struct sockaddr_in6 report_dest;
    uint16_t myPeriod;

    uint32_t sequence;

    uint16_t channel;
    uint16_t panid;
  } m_config;

  /* running statistics  */
  uint16_t current_reading;

  enum {
    CONFIG_ADDR = 0x0,
  };

  /* reset the config structure to hard-coded defaults if we fail to
     read our config off the flash. */
  void setDefaultConfig() {
    m_config.magic = CONFIG_MAGIC;

    m_config.report_dest.sin6_port = htons(8005);
    inet_pton6(REPORT_ADDR, &m_config.report_dest.sin6_addr);

    m_config.myPeriod = PERIOD;
    m_config.sequence = 0;

    m_config.channel = CC2420_DEF_CHANNEL;
    m_config.panid = TOS_AM_GROUP;
  }

  void startSampling() {
    call CC2420Config.setChannel(m_config.channel);
    call CC2420Config.setPanAddr(m_config.panid);
    call CC2420Config.sync();

    call SenseTimer.startPeriodic(call Random.rand16() % (m_config.myPeriod*1024L));
  }

  event void Boot.booted() {
    current_reading = 0;
  	
	call Leds.led0Toggle();
    setDefaultConfig();

    call RouteStats.clear();
    call RadioControl.start();
  
     printfUART_init();

    if ((call Mount.mount()) != SUCCESS) {
      setDefaultConfig();
      startSampling();
    }
  }

  event void Mount.mountDone(error_t e) {
    if (e == SUCCESS) {
      if (call ConfigStorage.valid()) {
        /* if there's data in the volume, read our config back */
        if ((call ConfigStorage.read(CONFIG_ADDR, &m_config, sizeof(m_config))) != SUCCESS) {
          startSampling();
        }
      } else {
        /* otherwise just use the default */
        startSampling();
        // printfUART("Start sampling -- no valid config\n");
      }
    }
  }

  event void ConfigStorage.readDone(storage_addr_t addr, void* buf, storage_len_t len, error_t err) {
    /* we only read at startup */
    if (err != SUCCESS || m_config.magic != CONFIG_MAGIC) {
      /* make sure to reset the config if the magic changes. */
      setDefaultConfig();
    } else {
      /* make sure we skip all the sequence numbers we could have generated */
      /* this should be persistent... */
      m_config.sequence += SEQUENCE_SAVE_EVERY;
      call ConfigStorage.write(CONFIG_ADDR, &m_config, sizeof(m_config));
    }

    startSampling();
  }

  event void ConfigStorage.writeDone(storage_addr_t addr, void* buf, storage_len_t len, error_t err) {
    call ConfigStorage.commit();
  }

  event void ConfigStorage.commitDone(error_t err) {

  }
  
  event void ReportSend.recvfrom(struct sockaddr_in6 *from,
                                 void *data, uint16_t len,
                                 struct ip_metadata *meta) {

  }

  void senseDone() {
	call Leds.led1Toggle();
    current_reading++;
    /* start a new interval */
    if (current_reading == CO2_NUMBER_READINGS) {
      ieee_eui64_t eui;
      eui = call LocalIeeeEui64.getId();
      call RouteStats.get(&report.stats.route);
//      call IPStats.get(&report.stats.ip);
//      call UDPStats.get(&report.stats.udp);
      memcpy(report.eui64, eui.data, IEEE_EUI64_LENGTH);
      /* start creating a new report */
      current_reading = 0;
      report.seq = m_config.sequence ++;
      report.localTime = call SenseTimer.getNow();
      report.globalTime = call UnixTime.get();
      report.period = m_config.myPeriod;

      printfUART("Start Send[%d]\n", sizeof(nx_struct co2_report));
      printfUART("dest : 0x%x\n",m_config.report_dest);

      /* send the report we just finished */
      call ReportSend.sendto(&m_config.report_dest, &report, sizeof(nx_struct co2_report));
      memcpy(&read_reply.report, &report, sizeof(report));

      if ((m_config.sequence % SEQUENCE_SAVE_EVERY) == 0) {
        call ConfigStorage.write(CONFIG_ADDR, &m_config, sizeof(m_config));
      }
    }
  }

  void startSense() {	  
	senseDoneCnt = 0;
	
	call Leds.led2Toggle();
	if (call ReadSonnoSensor.read() != SUCCESS)
	  senseDoneCnt++;
	/*
	if (call Humidity.read() != SUCCESS)
	  senseDoneCnt++;
	if (call Temperature.read() != SUCCESS)
	  senseDoneCnt++;
	if (call ReadPAR.read() != SUCCESS)
	  senseDoneCnt++;
	if (call ReadTSR.read() != SUCCESS)
	  senseDoneCnt++;
	*/
	if (call ReadBattVol.read() != SUCCESS)
	  senseDoneCnt++;	
	if (call ReadIntVol.read() != SUCCESS)
	  senseDoneCnt++;

	if (senseDoneCnt == N_SENSORS) senseDone();
	senseDone();
  }

  event void SenseTimer.fired() {
	  startSense();
  }
  
  event void Humidity.readDone(error_t result, uint16_t data) {
	  report.readings[current_reading].hum = data;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }

  event void Temperature.readDone(error_t result, uint16_t data) {
	  report.readings[current_reading].temp = data;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }

  event void ReadPAR.readDone(error_t result, uint16_t data) {
	  report.readings[current_reading].par = data;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }

  event void ReadTSR.readDone(error_t result, uint16_t data) {
	  report.readings[current_reading].tsr = data;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }

  event void ReadBattVol.readDone(error_t result, uint16_t data) {
	  report.readings[current_reading].battvol = data;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }

  event void ReadIntVol.readDone(error_t result, uint16_t data) {
	  report.readings[current_reading].intvol = data;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }
  
  event void ReadSonnoSensor.readDone(error_t result, uint16_t data) {
	  //report.readings[current_reading].co2 = data;
	  report.readings[current_reading].co2 = 0x77;
	  if (++senseDoneCnt == N_SENSORS) senseDone();
  }  
  
  event void ReadConfig.dispatch(nx_struct cmd_payload *data, int len) {
    nx_struct read_config_cmd *cmd = (nx_struct read_config_cmd *)(data->data);
    nx_struct {
      nx_struct cmd_payload header;
      nx_struct config_cmd data;
    } reply;

    ip_memclr((void *)&reply, sizeof(reply));

    reply.header.id = BSHELL_WRITE_CONFIG;
    reply.data.key = cmd->key;

    switch (cmd->key) {
    case ACME_PERIOD:
      reply.data.value.period = m_config.myPeriod;
      break;
    case ACME_DEST:
      memcpy(reply.data.value.report_addr, &m_config.report_dest.sin6_port, 2);
      memcpy(&reply.data.value.report_addr[2], m_config.report_dest.sin6_addr.s6_addr, 16);
      break;
    case ACME_RADIO:
      reply.data.value.radio.curChannel = call CC2420Config.getChannel();
      reply.data.value.radio.configChannel = m_config.channel;
      reply.data.value.radio.curPanid = call CC2420Config.getPanAddr();
      reply.data.value.radio.configPanid = m_config.panid;
      break;
    default:
      reply.data.key = ACME_NONE;
    }

    call ReadConfig.write((nx_struct cmd_payload *)&reply, sizeof(reply));
  }

  event void WriteConfig.dispatch(nx_struct cmd_payload *data, int len) {
    nx_struct config_cmd *cmd = (nx_struct config_cmd *)(data->data);
    if (len != sizeof(nx_struct cmd_payload) + sizeof(nx_struct config_cmd))
      return;

    switch (cmd->key) {
    case ACME_PERIOD:
      m_config.myPeriod = cmd->value.period;
	  call SenseTimer.stop();
	  call SenseTimer.startPeriodic(call Random.rand16() % (m_config.myPeriod*1024L));
      break;
    case ACME_DEST:
      memcpy(m_config.report_dest.sin6_addr.s6_addr, &cmd->value.report_addr[2], 16);
      memcpy(&m_config.report_dest.sin6_port, cmd->value.report_addr, 2);
      break;
    case ACME_RADIO:
      m_config.channel = cmd->value.radio.configChannel;
      m_config.panid = cmd->value.radio.configPanid;
      break;
    default:
      cmd->key = ACME_NONE; 
    }
 
    call ConfigStorage.write(CONFIG_ADDR, &m_config, sizeof(m_config));
  }

  event void ReadData.dispatch(nx_struct cmd_payload *data, int len) {
    read_reply.hdr.id = BSHELL_READ;
    read_reply.hdr.forward = 0;
    call ReadData.write(&read_reply, sizeof(read_reply));
  }
 
  event void RadioControl.startDone(error_t e) {}
  event void RadioControl.stopDone(error_t e) {}
  event void CC2420Config.syncDone(error_t e) {}
}
