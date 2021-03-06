/*
 * Librairie SpinningLED
 * Update : 22.09.16
 * WORK ONLY WITH DRIVER ACTUALLY
 * toDo : ADD NO DRIVER FUNCTION
 */

#include "SpinningLED.h"

SpinningLED::SpinningLED(unsigned char _led1, unsigned char _led2, unsigned char _led3, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4, unsigned char pin5, unsigned char pin6) {
  motor0 = L293_twoWire(pin1,pin2); /* uint8_t _enablePin, uint8_t _directionPin */
  motor1 = L293_twoWire(pin3,pin4);
  motor2 = L293_twoWire(pin5,pin6);
  led0 = rgbImproved(_led1, driverPWM);
  led1 = rgbImproved(_led2, driverPWM);
  led2 = rgbImproved(_led3, driverPWM);
}

SpinningLED::SpinningLED(unsigned char _led1, unsigned char _led2, unsigned char _led3) {
  led0 = rgbImproved(_led1, _led2, _led3);
  led0.setBrightness(255); /* Par defaut : 255 (max) */
}

void SpinningLED::setMode(SpinningLEDMode mode) {
  actual = mode;
}

void SpinningLED::poll() {
  randomSeed(analogRead(0));
  switch(actual) {
    case fullAuto:
      led0.applySmooth(random(256), random(20, 400), random(400, 10000));
      break;
    case ledAuto:
      led0.applySmooth(random(256), random(20, 400), random(400, 10000));
      break;
    case motAuto:
      led0.applySmooth(color, random(20, 400), random(400, 10000));
      break;
    default:
      break;
  }
}

void SpinningLED::setColor(unsigned char _color) {
  color = _color;
}

void SpinningLED::setBrightness(unsigned char brightness) {
  led0.setBrightness(brightness);
}

void SpinningLED::setLedOn(unsigned char numLed, bool on) {
  led0.setOn(on);
}

