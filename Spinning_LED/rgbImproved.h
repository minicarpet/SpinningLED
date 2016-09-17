/*
 * Librairie led RGB
 * Update : 17.09.16
 */

#include "declaration.h"

class rgbImproved {
  public:
    rgbImproved(int pinRed, int pinGreen, int pinBlue);
    void setBrightness(unsigned char val);
    unsigned char getBrightness();
    void apply(rgb values);
    void apply(int val);
    rgb getColor();
  private:
    int _pinRed;
    int _pinGreen;
    int _pinBlue;
    unsigned char brightness = 255;
    rgb LED;
    rgb color_map(int color_index);
    color chose = red;
};
