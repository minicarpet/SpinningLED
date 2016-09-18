/*
*  17.09.16 : Logan Gallois
*  future imporvement :
*  Windows print graph of PWMs values from RGB LED
*  Add autoDetect position to move windows at the good location
*/

import processing.serial.*;
Serial myPort;
SecondApplet sa;
 
int[] numbers = new int[600];
boolean flag = false;
float var1;
float var2;
float var3;
float var4;
 
void setup() {
  size(1024, 576); //Affiche en plein écran
  surface.setResizable(false);
  noStroke();
  println(Serial.list()); /* Verifier dans la liste ou se trouve l'arduino */
  /* Puis changer en dessous la valeur en fonction */
  /* En general 0 pour windows et 1 pour un mac */
  String os=System.getProperty("os.name"); /* Detection automatique de l'OS */
  if(os != "Mac OS X") {
    if(Serial.list().length > 0) {
      myPort = new Serial(this, Serial.list()[0], 115200);
    }
  } else {
    if(Serial.list().length > 1) { /* Module BLE en position 0 */
      myPort = new Serial(this, Serial.list()[1], 115200);
    }
  }
  //Important : se câler sur la valeur en baud du prog Arduino
  myPort.bufferUntil('\n');
  String[] args = {"TwoFrameTest"};
  sa = new SecondApplet();
  PApplet.runSketch(args, sa);
  delay(100);
}
  
void draw() {
  if(!flag) {
    surface.setLocation(displayWidth/2-width/2-400,displayHeight/2-height/2);
    sa.frame.setTitle("Monitoring RGB Values");
    flag = true;
  }
  background(color(int(var1), int(var2), int(var3)));
  //sa.background(0, 255, 0);
    /*for(int i = 0 ;i<=width/10;i++){
     sa.stroke(200);
     sa.line((-frameCount%10)+i*10,0,(-frameCount%10)+i*10,height);
     
     sa.line(0,i*10,width,i*10);
    }
  
    sa.noFill();
    sa.stroke(0);
    sa.beginShape();
    for(int i = 0; i<numbers.length;i++){
      sa.vertex(i,350-numbers[i]);
    }
    sa.endShape();
    for(int i = 1; i<numbers.length;i++){
      numbers[i-1] = numbers[i];
    }
    numbers[numbers.length-1]=mouseY;*/
}

void mouseClicked() {
  print("clicked");
  sa.background(0, 0, 255);
  sa.fill(100);
  sa.redraw();
  background(0, 0, 255);
  redraw();
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

public class SecondApplet extends PApplet {

  public void settings() {
    size(600, 600);
    noLoop();
  }
  public void draw() {
    
  }
  
  public void mouseClicked() {
    print("clicked2");
    background(0, 255, 0);
    redraw();
  }
}