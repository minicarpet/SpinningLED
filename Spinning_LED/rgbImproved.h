/*
 * Librairie led RGB
 * Update : 17.09.16
 */

#include "Arduino.h"

typedef struct{
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
}rgb;

class rgbImproved {
  public:
    rgbImproved(unsigned char pinRed, unsigned char pinGreen, unsigned char pinBlue);
    void setOn(bool on);
    bool getOn();
    void setBrightness(unsigned char val);
    unsigned char getBrightness();
    void apply(int r, int g, int b);
    void apply(rgb values);
    void apply(int val);
    rgb getColor();
  private:
    unsigned char _pinRed;
    unsigned char _pinGreen;
    unsigned char _pinBlue;
    unsigned char lastColor = 0;
    bool _on = true;
    unsigned char brightness = 255;
    rgb LED;
    rgb color_map(int color_index);
};
