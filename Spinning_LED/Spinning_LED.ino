/* 25.08.2016 -- RGB spinning LED ball
 * Pierre-Yves Bloqueau/Logan Gallois (jte beze)
 * ----Etat d'avancement: x- fait o- à faire
 * o-lien entre appli android et arduino
 *  o- distinction entre mode auto et manuel
 *    o-codage mode auto
 *      x- Look up-table: 1int-->3int rgb
 *      o-fonction de transition mot
 *      o-fonction de transition color
 *    o-codage mode manuel moteur
 *    o-codage mode manuel led
 *    o-codage mode manuel full
 *    o-codage enregistrement mode
 */

#include "rgbImproved.h" /* Librairie d'utilisation d'une LED RGB */

/*
 * Gestion du BLE
 */
 
#include <CurieBLE.h> /* Module BLE a modifier pour la carte ADA */

BLEPeripheral blePeripheral; /* instantiation du module BLE */

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); /* instantiation des services */

BLECharacteristic ledChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLEWrite, 20); /* instantiation des characteristique */

/*
 * Utilities for monitoring
 */

#ifdef Monitoring
unsigned long int timeout = 10000; /* Timeout to check connection on Serial port */
unsigned long int Time = 10000;
#endif

rgbImproved led(9, 6, 3);

void setup() {
  // put your setup code here, to run once:
  #ifdef Monitoring
  Serial.begin(115200);
  Time = millis();
  while(!Serial) {
    if(millis() - Time > timeout) {
      break;
    }
  }
  Serial.println("Monitoring on");
  #endif
  pinMode(13, OUTPUT); /* LED on pin 13 use to know if BLE is connected or not On : connected */
  digitalWrite(13, LOW);
  led.setBrightness(100); /* Par defaut : 255 (max) */
  led.apply(0);
  delay(1000);
  led.applySmooth(100, 100, 1000);
  delay(1000);
  led.applySmooth(0, 10, 20000);
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0 ; i<256 ; i++) { /* Test de toutes les valeurs possible en boucle en utilisant le fonction de PY */
    led.apply(i);
    Serial.println(led.getColor());
    delay(20);
  }
  led.setOn(!led.getOn());
}

/*
 * Gestion du BLE
 */

void initBLE() {
  blePeripheral.setLocalName("LEDCB"); /* Initialisation du BLE */
  blePeripheral.setDeviceName("SpinningLED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(ledChar);
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  ledChar.setEventHandler(BLEWritten, ledCharacteristicWritten);
  blePeripheral.begin(); /* Demarrage du BLE */
}

void blePeripheralConnectHandler(BLECentral& central) {
  // central connected event handler
  digitalWrite(13, HIGH);
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  // central disconnected event handler
  digitalWrite(13, LOW);
}

String toString(const unsigned char* entry, unsigned char len) {
  char Temp[len];
  for (int i=0;i<len;i++) {
    Temp[i] = char(entry[i]);
  }
  String Out = Temp;
  Out.remove(len);
  return Out;
}

const unsigned char* tocstChar(String entry) {
  unsigned int len = entry.length();
  unsigned char Temp[len];
  for (int i=0;i<len;i++) {
    Temp[i] = entry.charAt(i);
  }
  const unsigned char* Out = Temp;
  return Out;
}

void ledCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  String In = toString(ledChar.value(), ledChar.valueLength());
  rgb newLed;
  newLed.r = In.toInt();
  led.apply(newLed);
}
