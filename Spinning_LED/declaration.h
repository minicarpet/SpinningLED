#include "Arduino.h"

typedef struct{
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
}rgb;

enum color {
  unknown,
  red,
  green,
  blue
};
