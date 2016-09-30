/*
 * Librairie SpinningLED
 * Update : 22.09.16
 */

#include "rgbImproved.h" /* Librairie d'utilisation d'une LED RGB */
#include "L293.h" /* Gestion des moteurs */
#include "TaskScheduler.h"

typedef enum {
  fullAuto = 0,
  ledAuto = 1,
  motAuto = 2,
  fullControlled = 3
} SpinningLEDMode;

class SpinningLED {
  public:
    SpinningLED() { }; /* WILL BE REMOVED, ONLY FOR TESTING*/
    SpinningLED(unsigned char _led1, unsigned char _led2, unsigned char _led3, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4, unsigned char pin5, unsigned char pin6);
    SpinningLED(unsigned char _led1, unsigned char _led2, unsigned char _led3);
    void setMode(SpinningLEDMode mode);
    void setBrightness(unsigned char brightness);
    void poll();
    void setColor(unsigned char _color);
    void setLedOn(unsigned char numLed, bool on);
  private:
    L293_twoWire motor0 = L293_twoWire(0,0);
    L293_twoWire motor1 = L293_twoWire(0,0);
    L293_twoWire motor2 = L293_twoWire(0,0);
    unsigned char color = 0;
    rgbImproved led0;
    rgbImproved led1;
    rgbImproved led2;
    TLC59711 driverPWM;
    SpinningLEDMode actual = fullAuto;
    void functionCallbackLed0();
    void functionCallbackLed1();
    void functionCallbackLed2();
    Scheduler schedule;
    Task led0Task;
    Task led1Task;
    Task led2Task;
};

