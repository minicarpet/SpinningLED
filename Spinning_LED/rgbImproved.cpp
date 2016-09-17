/*
 * Declaration des fonctions de la librairie
 * Update : 17.09.16
 */

#include "rgbImproved.h"

rgb color_map(int color_index) { /* Fonction de PY : couleur Hue (de HSV) */

int r_out=0;
int g_out=0;
int b_out=0;

if (color_index >=0 && color_index<85){
r_out=map(color_index, 0, 85, 0, 255);
g_out=map(color_index, 0, 85, 255, 0);
b_out= 0;
}

else if (color_index >=85 && color_index<170){
r_out=map(color_index, 85, 170, 255, 0);
g_out=0;
b_out=map(color_index, 85, 170, 0, 255);
}

else if (color_index >=170 && color_index<255){
r_out=0; 
g_out=map(color_index, 170, 255, 0, 255);
b_out=map(color_index, 170, 255, 255, 0);
}

rgb out;
out.r=r_out;
out.g=g_out;
out.b=b_out;

return out; 
}

rgbImproved::rgbImproved(int pinRed, int pinGreen, int pinBlue) { /* Initialisation de la classe */
  _pinRed = pinRed;
  _pinGreen = pinGreen;
  _pinBlue = pinBlue;
  apply(LED);
}

void rgbImproved::setBrightness(unsigned char val) { /* Modification de la luminosite de la LED */
  brightness = constrain(val, 0, 255);
  apply(LED);
}

unsigned char rgbImproved::getBrightness() { /* Recuperation de la luminosite de la LED */
  return brightness;
}

void rgbImproved::apply(rgb values) { /* Mise a jour des valeurs PWMs de la LED avec la structure RGB (3 valeurs) */
  LED = values;
  analogWrite(_pinRed, LED.r/(256-brightness));
  analogWrite(_pinGreen, LED.g/(256-brightness));
  analogWrite(_pinBlue, LED.b/(256-brightness));
}

void rgbImproved::apply(int val) { /* Mise a jour des valeurs PWMs de la LED avec une valeur unique (utilise la fonction de PY) */
  apply(color_map(val));
}

rgb rgbImproved::getColor() { /* Recuperation des couleurs RGB */
  return LED;
}

