/*
*  17.09.16 : Logan Gallois
*  future imporvement :
*  Windows print graph of PWMs values from RGB LED
*/

import processing.serial.*;
Serial myPort;   
 
float var1;
float var2;
float var3;
float var4;
 
void setup() {
  size(1024, 576); //Affiche en plein écran
  println(Serial.list()); /* Verifier dans la liste ou se trouve l'arduino */
  /* Puis changer en dessous la valeur en fonction */
  /* En general 0 pour windows et 1 pour un mac */
  myPort = new Serial(this, Serial.list()[1], 115200);
  //Important : se câler sur la valeur en baud du prog Arduino
  myPort.bufferUntil('\n');
}
  
void draw() {
  background(color(int(var1), int(var2), int(var3)));
}
   
void serialEvent (Serial myPort) {
 
  String inString = myPort.readStringUntil('\n');
  //println(inString);
  if (inString != null) {
    
    inString = trim(inString); 
    int inputs[] = int(split(inString,',')); // on élude les virgules
   
    // on affecte nos 4 valeurs
    if(inputs.length == 4) {
     var1 = inputs[0];
     var2 = inputs[1];
     var3 = inputs[2];
     var4 = inputs[3];
    
    // On ré-échelonne la valeur analogique en valeur RGB
    var1 = map(var1, 0, 1023, 0, 255);
    var2 = map(var2, 0, 1023, 0, 255);
    var3 = map(var3, 0, 1023, 0, 255);
    var4 = map(var3, 0, 1023, 0, 255);
    print(int(var1));
    print(" ,");
    print(int(var2));
    print(" ,");
    print(int(var3));
    print(" ,");
    println(var4);
    }
  }
}