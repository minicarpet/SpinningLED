// 25.08.2016 -- RGB spinning LED ball
// Pierre-Yves Bloqueau/Logan Gallois
//----Etat d'avancement: x- fait o- à faire
// o-lien entre appli android et arduino
//  o- distinction entre mode auto et manuel
//    o-codage mode auto
//      x- Look up-table: 1int-->3int rgb 
//    o-codage mode manuel

#include "rgbImproved.h"
#include <CurieBLE.h>

BLEPeripheral blePeripheral;

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLECharacteristic ledChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLEWrite, 20);

rgbImproved led(9, 6, 3);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  blePeripheral.setLocalName("LEDCB");
  blePeripheral.setDeviceName("SpinningLED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(ledChar);
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  ledChar.setEventHandler(BLEWritten, ledCharacteristicWritten);
  blePeripheral.begin();
  led.setBrightness(150);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0 ; i<256 ; i++) {
    led.apply(i);
    delay(20);
  }

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
