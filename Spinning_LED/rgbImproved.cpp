/*
 * Declaration des fonctions de la librairie
 * Update : 17.09.16
 */

#include "rgbImproved.h"

rgbImproved::rgbImproved(unsigned char pinRed, unsigned char pinGreen, unsigned char pinBlue) { /* Initialisation de la classe */
  _pinRed = pinRed;
  _pinGreen = pinGreen;
  _pinBlue = pinBlue;
  apply(LED);
}

/*
 * Mettre a 1 pour allumer la LED et a 0 pour l'eteindre
 * Il est aussi possible d'eteindre la led en mettant la luminosite a 0
 * Ou encore en appliquant 0, 0, 0 a la LED avec apply
 * 
 * Si la LED est ON, les valeur RGB peuvent toujours etre modifier ! Cependant
 * lorsque setOn est appeler pour eteindre la LED, les valeurs RGB sont
 * renitialiser a 0
 */
void rgbImproved::setOn(bool on) { /* Set On/Off de la LED */
  if(!on) {
    apply(0, 0, 0);
  }
  _on = on;
  apply(LED);
}

bool rgbImproved::getOn() { /* Get On/Off de la LED */
  return _on;
}

void rgbImproved::setBrightness(unsigned char val) { /* Modification de la luminosite de la LED */
  brightness = constrain(val, 0, 255);
  apply(LED);
}

unsigned char rgbImproved::getBrightness() { /* Recuperation de la luminosite de la LED */
  return brightness;
}

void rgbImproved::apply(int r, int g, int b) { /* Mise a jour des valeurs PWMs de la LED avec la structure RGB (3 valeurs) */
  LED.r = r*(brightness/255.0);
  LED.g = g*(brightness/255.0);
  LED.b = b*(brightness/255.0);
  if(!_on) { return;}
  analogWrite(_pinRed, LED.r);
  analogWrite(_pinGreen, LED.g);
  analogWrite(_pinBlue, LED.b);
}

void rgbImproved::apply(rgb values) { /* Mise a jour des valeurs PWMs de la LED avec la structure RGB (3 valeurs) */
  LED.r = values.r*(brightness/255.0);
  LED.g = values.g*(brightness/255.0);
  LED.b = values.b*(brightness/255.0);
  if(!_on) { return;}
  analogWrite(_pinRed, LED.r);
  analogWrite(_pinGreen, LED.g);
  analogWrite(_pinBlue, LED.b);
}

void rgbImproved::apply(int val) { /* Mise a jour des valeurs PWMs de la LED avec une valeur unique (utilise la fonction de PY) */
  lastColor = val;
  color_map(val);
}

void rgbImproved::applySmooth(int val) { /* Mise a jour des valeurs PWMs de la LED avec une valeur unique (utilise la fonction de PY) */
  //MET TA FONCTION SMOOTH POUR LE CHANGEMENT DE COULEUR ICI ENCULER
  //TU PEUX UTILISER LA VARIABLE lastColor QUI ENREGISTRE LA DERNIERE VALEUR UTILISE
}

rgb rgbImproved::getColor() { /* Recuperation des couleurs RGB */
  return LED;
}

rgb rgbImproved::color_map(int color_index) { /* Fonction de PY : couleur Hue (de HSV) */

  int r_out=0;
  int g_out=0;
  int b_out=0;
  
  if (color_index >=0 && color_index<42) {
    r_out=255;
    g_out=map(color_index, 0, 42, 0, 255); 
    b_out= 0;
  } else if (color_index >=42 && color_index<85) {
    r_out=map(color_index, 42, 85, 255, 0);
    g_out=255;
    b_out=0;
  } else if (color_index >=85 && color_index<127) {
    r_out=0;
    g_out=255;
    b_out=map(color_index, 85, 127, 0, 255);   
  } else if (color_index >=127 && color_index<170) {
    r_out=0;
    g_out=map(color_index, 127, 170, 255, 0);
    b_out=255;
  } else if (color_index >=170 && color_index<212) {
    r_out=map(color_index, 170, 212, 0, 255);
    g_out=0;
    b_out=255;
  } else if (color_index >=170 && color_index<=255) {
    r_out=255;
    g_out=0;
    b_out=map(color_index, 212, 255, 255, 0);
  }
  
  rgb out;
  out.r=r_out;
  out.g=g_out;
  out.b=b_out;

  out.r = out.r*(brightness/255.0);
  out.g = out.g*(brightness/255.0);
  out.b = out.b*(brightness/255.0);

  LED = out;

  if(!_on) { return LED;}

  analogWrite(_pinRed, out.r);
  analogWrite(_pinGreen, out.g);
  analogWrite(_pinBlue, out.b);
  
  return out;
}

