/* "Copyright (c) 2008,2010 The Regents of the University  of California.
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
 * ACme Energy Monitor adapted for HydroWatch+CO2 node
 * @author Fred Jiang <fxjiang@eecs.berkeley.edu>
 * @author Stephen Dawson-Haggerty <stevedh@eecs.berkeley.edu>
 * @author Jay Taneja <taneja@cs.berkeley.edu>
 * @version $Revision: 1.1 $
 */

#ifndef _CO2REPORT_H
#define _CO2REPORT_H

#include <IeeeEui64.h>
#include "Statistics.h"

#define CO2_NUMBER_READINGS 2

nx_struct co2_report {
  nx_uint8_t  eui64[IEEE_EUI64_LENGTH];
  nx_struct {
    route_statistics_t route;
    //    ip_statistics_t    ip;
    //    udp_statistics_t   udp;
  } stats; 
  /* sequence number of the report message; increases by one every
     time a message is sent */
  nx_uint32_t seq;

  /* time (in seconds) of the local clock */
  nx_uint32_t localTime;
  /* time (in seconds) since the epoch GMT */
  nx_uint32_t globalTime;
  /* time interval between successive readings */
  nx_uint16_t period;

  /* readings -- each one of these is separated by "period" seconds */
  nx_struct {
	nx_uint16_t temp;
	nx_uint16_t hum;
	nx_uint16_t par;
	nx_uint16_t tsr;
	nx_uint16_t battvol;
	nx_uint16_t intvol;
	nx_uint16_t co2;
  } readings [CO2_NUMBER_READINGS];
};

#endif
