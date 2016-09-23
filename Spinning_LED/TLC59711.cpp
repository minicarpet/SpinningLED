/*
 * Librairie Driver PWM
 * Update : 23.09.16
 */

#include "TLC59711.h"

TLC59711::TLC59711() {
  SPI.begin();
  BCr = BCg = BCb = 0x7F;
  pwmbuffer = (uint16_t *)calloc(2, 12);
}

void TLC59711::spiwriteMSB(uint32_t d) {
  SPI.transfer(d);
}

void TLC59711::write(void) {
  uint32_t command;

  // Magic word for write
  command = 0x25;

  command <<= 5;
  //OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 1, BLANK = 0 -> 0x16
  command |= 0x16;

  command <<= 7;
  command |= BCr;

  command <<= 7;
  command |= BCg;

  command <<= 7;
  command |= BCb;

  spiwriteMSB(command >> 24);
  spiwriteMSB(command >> 16);
  spiwriteMSB(command >> 8);
  spiwriteMSB(command);

  // 12 channels per TLC59711
  for (int8_t c=11; c >= 0 ; c--) {
    // 16 bits per channel, send MSB first
    spiwriteMSB(pwmbuffer[12+c]>>8);
    spiwriteMSB(pwmbuffer[12+c]);
  }
  delayMicroseconds(2);
}



void TLC59711::setPWM(uint8_t chan, uint16_t pwm) {
  if (chan > 12) return;
  pwmbuffer[chan] = pwm;  
}


void TLC59711::setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b) {
  setPWM(lednum*3, r);
  setPWM(lednum*3+1, g);
  setPWM(lednum*3+2, b);
}
