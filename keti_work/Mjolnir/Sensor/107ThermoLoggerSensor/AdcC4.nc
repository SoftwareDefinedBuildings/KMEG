/**
 * To convert from ADC counts to actual voltage, divide by 4096 and
 * multiply by 3.
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/06/15 
 */

generic configuration AdcC4() {
  provides interface Read<uint16_t>;
  provides interface ReadStream<uint16_t>;

  provides interface Resource;
  provides interface ReadNow<uint16_t>;
}

implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components new AdcReadStreamClientC();
  ReadStream = AdcReadStreamClientC;

  components AdcP4;
  AdcReadClientC.AdcConfigure -> AdcP4;
  AdcReadStreamClientC.AdcConfigure -> AdcP4;

  components new AdcReadNowClientC();
  Resource = AdcReadNowClientC;
  ReadNow = AdcReadNowClientC;
  
  AdcReadNowClientC.AdcConfigure -> AdcP4;
}
