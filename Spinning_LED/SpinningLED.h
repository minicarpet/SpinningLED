/*
 * Librairie SpinningLED
 * Update : 22.09.16
 */

#include "rgbImproved.h" /* Librairie d'utilisation d'une LED RGB */
#include "L293.h" /* Gestion des moteurs */

typedef enum {
  fullAuto = 0,
  ledAuto = 1,
  motAuto = 2,
  fullControlled = 3
} mode;

class SpinningLED {
  public:
    SpinningLED(unsigned char _led1, unsigned char _led2, unsigned char _led3, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4, unsigned char pin5, unsigned char pin6);
  private:
    L293_twoWire motor0 = L293_twoWire(0,0);
    L293_twoWire motor1 = L293_twoWire(0,0);
    L293_twoWire motor2 = L293_twoWire(0,0);
    rgbImproved led0;
    rgbImproved led1;
    rgbImproved led2;
    TLC59711 driverPWM;
    mode actual = fullAuto;
};

