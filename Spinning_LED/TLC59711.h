/*
 * Librairie Driver PWM
 * Update : 23.09.16
 */

#include "SPI.h"

 class TLC59711 {
  public:
    TLC59711();
    void setPWM(uint8_t chan, uint16_t pwm);
    void setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b);
    void write(void);
    void spiwriteMSB(uint32_t d);
  private:
    uint16_t *pwmbuffer;
  
    uint8_t BCr, BCg, BCb;
    int8_t _clk, _dat;
 };

