// 25.08.2016 -- RGB spinning LED ball
// Pierre-Yves Bloqueau
//----Etat d'avancement: x- fait o- à faire
// o-lien entre appli android et arduino
//  o- distinction entre mode auto et manuel
//    o-codage mode auto
//      x- Look up-table: 1int-->3int rgb 
//    o-codage mode manuel

#include "rgbImproved.h"

rgbImproved led(9, 6, 3);
rgb yolo;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0 ; i<256 ; i++) {
    led.apply(i);
    delay(20);
  }

}
