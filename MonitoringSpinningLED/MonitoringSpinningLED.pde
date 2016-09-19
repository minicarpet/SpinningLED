/*
*  17.09.16 : Logan Gallois
*  future imporvement :
*  Add autoDetect position to move windows at the good location
*/

import controlP5.*;
import processing.serial.*;
Serial myPort;
SecondApplet sa;

ControlP5 cp5;
DropdownList p1;
 
boolean flag = false;
float var1;
float var2;
float var3;
float var4;
PApplet test;
 
void setup() {
  size(1024, 576); //Affiche en plein écran
  surface.setResizable(false);
  noStroke();
  test = this;
  cp5 = new ControlP5(this);
  p1 = cp5.addDropdownList("USB detected")
          .setPosition(0, 0)
          ;
  for(int i = 0 ; i<Serial.list().length ; i++) {
    p1.addItem(Serial.list()[i], i);
  }
  p1.changeValue(1.0);
  p1.close();
  delay(100);
  //Important : se câler sur la valeur en baud du prog Arduino
  String[] args = {"TwoFrameTest"};
  sa = new SecondApplet();
  PApplet.runSketch(args, sa);
  delay(40);
}
  
void draw() {
  if(!flag) {
    surface.setLocation(displayWidth/2-width/2-400,displayHeight/2-height/2);
    flag = true;
  }
  background(color(constrain(int(var1),0,255), constrain(int(var2),0,255), constrain(int(var3),0,255)));
}

void mouseClicked() {
  for(int i = 0 ; i<p1.getItems().size() ; i++) {
    p1.changeValue(i);
    println(p1.getStringValue());
    p1.removeItem(p1.getStringValue());
  }
  for(int i = 0 ; i<Serial.list().length ; i++) {
    p1.addItem(Serial.list()[i], i);
  }
}

void customize(DropdownList ddl) {
  ddl.setBackgroundColor(20);
  ddl.setItemHeight(40);
  ddl.setBarHeight(20);
}

void controlEvent(ControlEvent theEvent) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (theEvent.isGroup()) {
    // check if the Event was triggered from a ControlGroup
  } 
  else if (theEvent.isController()) {
    myPort.stop();
    myPort.clear();
    myPort = new Serial(this, Serial.list()[int(theEvent.getController().getValue())], 115200);
    myPort.bufferUntil('\n');
    //p1.setColorActive(100);
  }
}
   
void serialEvent (Serial myPort) {
 
  String inString = myPort.readStringUntil('\n');
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
    for(int i = 1; i<sa.numbersRed.length;i++){
     sa.numbersRed[i-1] = sa.numbersRed[i];
    }
    sa.numbersRed[sa.numbersRed.length-1]=parseInt(var1);
    
    for(int i = 1; i<sa.numbersGreen.length;i++){
     sa.numbersGreen[i-1] = sa.numbersGreen[i];
    }
    sa.numbersGreen[sa.numbersGreen.length-1]=parseInt(var2);
    
    for(int i = 1; i<sa.numbersBlue.length;i++){
     sa.numbersBlue[i-1] = sa.numbersBlue[i];
    }
    sa.numbersBlue[sa.numbersBlue.length-1]=parseInt(var3);
    }
  }
}

public class SecondApplet extends PApplet {
  
  int[] numbersRed = new int[601];
  int[] numbersGreen = new int[601];
  int[] numbersBlue = new int[601];

  public void settings() {
    size(600, 600);
  }
  
  public void setup() {
    surface.setTitle("Monitoring RGB Values");
  }
  
  public void draw() {
    background(255);
    stroke(255,0,0);
    beginShape();
    for(int i = 0; i<numbersRed.length;i++){
      vertex(i,height-50-numbersRed[i]);
    }
    endShape();
    stroke(0,255,0);
    beginShape();
    for(int j = 0; j<numbersGreen.length;j++){
      vertex(j,height-250-numbersGreen[j]);
    }
    endShape();
    stroke(0,0,255);
    beginShape();
    for(int k = 0; k<numbersBlue.length;k++){
      vertex(k,height-500-numbersBlue[k]);
    }
    endShape();
  }
}