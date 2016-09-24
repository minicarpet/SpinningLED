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

rgbImproved::rgbImproved(unsigned char _numled, TLC59711 _driverPWM) { /* Initialisation de la classe */
  numled = _numled;
  driverPWM = _driverPWM;
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
  LED.r = map(r, 0, 255, 0, brightness);
  LED.g = map(g, 0, 255, 0, brightness);
  LED.b = map(b, 0, 255, 0, brightness);
  if(!_on) { return;}
  if(_pinRed >= 0) {
    analogWrite(_pinRed, LED.r);
    analogWrite(_pinGreen, LED.g);
    analogWrite(_pinBlue, LED.b);
  } else {
    driverPWM.setLED(numled, map(LED.r, 0, 255, 0, 65535), map(LED.g, 0, 255, 0, 65535), map(LED.b, 0, 255, 0, 65535));
  }
}

void rgbImproved::apply(rgb values) { /* Mise a jour des valeurs PWMs de la LED avec la structure RGB (3 valeurs) */
  LED.r = map(values.r, 0, 255, 0, brightness);
  LED.g = map(values.g, 0, 255, 0, brightness);
  LED.b = map(values.b, 0, 255, 0, brightness);
  if(!_on) { return;}
  if(_pinRed >= 0) {
    analogWrite(_pinRed, LED.r);
    analogWrite(_pinGreen, LED.g);
    analogWrite(_pinBlue, LED.b);
  } else {
    driverPWM.setLED(numled, map(LED.r, 0, 255, 0, 65535), map(LED.g, 0, 255, 0, 65535), map(LED.b, 0, 255, 0, 65535));
  }
}

void rgbImproved::apply(int val) { /* Mise a jour des valeurs PWMs de la LED avec une valeur unique (utilise la fonction de PY) */
  lastColor = val;
  color_map(val);
}

void rgbImproved::applySmooth(unsigned char color_fin, unsigned int nb_pas, uint32_t time_transition) {
  if(lastColor == color_fin) {
    return;
  }
  Serial.print("color_fin : ");
  Serial.println(color_fin);
  Serial.print("nb_pas : ");
  Serial.println(nb_pas);
  Serial.print("time_transition : ");
  Serial.println(time_transition);
  float ecart = abs(color_fin-lastColor);
  if(ecart > 127) {
    ecart -= 256;
    ecart *= -1;
    ecart /= nb_pas;
    if(lastColor>127) {
      for(float i=lastColor ; i<(256+color_fin) ; i = i + ecart) {
        apply(round(i)%255);
        delay(time_transition/nb_pas);
      }
    } else {
      for(float i=lastColor ; i>0 ; i = i - ecart) {
        apply(i);
        delay(time_transition/nb_pas);
      }
      for(float i=255 ; i>color_fin ; i = i - ecart) {
        if(i>color_fin) {
          apply(i);
          delay(time_transition/nb_pas);
        }
      }
    }
  } else {
    ecart /= nb_pas;
    if(color_fin > lastColor) {
      for(float i=lastColor ; i<=color_fin ; i = i + ecart) {
        if(i<=color_fin) {
          apply(i);
          delay(time_transition/nb_pas);
        }
      }
    } else {
      for(float i=lastColor ; i>color_fin ; i = i - ecart) {
        if(i>color_fin) {
          apply(i);
          delay(time_transition/nb_pas);
        }
      }
    }
  }
  if(lastColor != color_fin) {
    apply(color_fin);
  }
}

rgb rgbImproved::getColorRGB() { /* Recuperation des couleurs RGB */
  return LED;
}

unsigned char rgbImproved::getColor() { /* Recuperation des couleurs RGB */
  return lastColor;
}

rgb rgbImproved::color_map(int color_index) { /* Fonction de PY : couleur Hue (de HSV) */

  int r_out=0;
  int g_out=0;
  int b_out=0;
  lastColor = color_index;
  
  if (color_index >=0 && color_index<42) {
    r_out=255;
    g_out=map(color_index, 0, 41, 0, 255); 
    b_out= 0;
  } else if (color_index >=42 && color_index<85) {
    r_out=map(color_index, 42, 84, 255, 0);
    g_out=255;
    b_out=0;
  } else if (color_index >=85 && color_index<127) {
    r_out=0;
    g_out=255;
    b_out=map(color_index, 85, 126, 0, 255);   
  } else if (color_index >=127 && color_index<170) {
    r_out=0;
    g_out=map(color_index, 127, 169, 255, 0);
    b_out=255;
  } else if (color_index >=170 && color_index<212) {
    r_out=map(color_index, 170, 211, 0, 255);
    g_out=0;
    b_out=255;
  } else if (color_index >=212 && color_index<=255) {
    r_out=255;
    g_out=0;
    b_out=map(color_index, 212, 255, 255, 0);
  }
  
  rgb out;
  out.r=r_out;
  out.g=g_out;
  out.b=b_out;

  apply(out);

  #ifdef Monitoring
  sendMonitoring();
  #endif
  
  return out;
}

#ifdef Monitoring
void rgbImproved::sendMonitoring() {
  Serial.print(getColorRGB().r);
  Serial.print(",");
  Serial.print(getColorRGB().g);
  Serial.print(",");
  Serial.print(getColorRGB().b);
  Serial.print(",");
  Serial.print(getBrightness());
  Serial.print(",");
  Serial.println(getColor());
}
#endif
