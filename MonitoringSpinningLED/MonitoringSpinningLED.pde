/*
*  17.09.16 : Logan Gallois
*  future imporvement :
*  Add autoDetect position to move windows at the good location
*/
import processing.serial.*;
Serial myPort;
SecondApplet sa;
 
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
  print("Running OS : ");
  println(os);
  if(!os.equals("Mac OS X")) {
    print("Connect with : ");
    println(Serial.list()[0]);
    if(Serial.list().length > 0) {
      myPort = new Serial(this, Serial.list()[0], 115200);
    }
  } else {
    print("Connect with : ");
    println(Serial.list()[1]);
    if(Serial.list().length > 1) { /* Module BLE en position 0 */
      myPort = new Serial(this, Serial.list()[1], 115200);
    }
  }
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
    
      // On ré-échelonne la valeur analogique en valeur RGB
      var1 = map(var1, 0, var4, 0, 255);
      var2 = map(var2, 0, var4, 0, 255);
      var3 = map(var3, 0, var4, 0, 255);
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
      vertex(i,height-40-numbersRed[i]);
    }
    endShape();
    stroke(0,255,0);
    beginShape();
    for(int j = 0; j<numbersGreen.length;j++){
      vertex(j,height-220-numbersGreen[j]);
    }
    endShape();
    stroke(0,0,255);
    beginShape();
    for(int k = 0; k<numbersBlue.length;k++){
      vertex(k,height-400-numbersBlue[k]);
    }
    endShape();
  }
}