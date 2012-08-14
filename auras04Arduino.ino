#include <Servo.h> 

#define ANALOG_IN A5
#define THRESH   500
#define ONTIME   1500
#define ONDELAY  1500

// state variables
int ledState;
unsigned long lastOn;
unsigned long toTurnOn;
//Buttons
int cameraButton = 0; 
int closeButton = 0;
Servo myservo; 

void setup() {
  // setup  
  myservo.attach(7);  
  pinMode(13,OUTPUT);
  //digitalWrite(ANALOG_IN, HIGH);
  //Button
  pinMode(2, INPUT);  
  pinMode(4, INPUT);
  //RGB led
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT); 
  // cathodes
  analogWrite(3,0);  
  analogWrite(5,0); 
  analogWrite(6,0); 
  Serial.begin(19200);
   // initial state
  ledState = LOW;
  lastOn = millis();
  toTurnOn = -1;
  // pin stuff
  digitalWrite(13,ledState);
  analogReference(DEFAULT);    // 5V  
  //analogReference(EXTERNAL);   // 
  //analogReference(INTERNAL);    // 1.1V
}

void loop() {
  // read analog in
  int val = analogRead(ANALOG_IN);
  //cameraButton = digitalRead(4);  
  closeButton = digitalRead(2); 
      
  if ((closeButton == HIGH)) { 
    digitalWrite(13,HIGH);
    myservo.write(90); 
    delay(1);
    myservo.write(0);
    delay(1000);    

}
  else
    digitalWrite(13,LOW); 
    //myservo.write(0); 
     
  // if off and saw a value and haven't seen other value yet
  // then set up a time to turn on
  //if((ledState == LOW)&&(cameraButton == LOW)&&(toTurnOn == -1)){
  if((ledState == LOW)&&(val < THRESH)&&(toTurnOn == -1)){
    toTurnOn = millis()+ONDELAY;
  }
  // if off and have seen a high value and it's time to turn on
  //else if((ledState == LOW)&&(cameraButton == HIGH)&&(toTurnOn != -1)&&(millis() > toTurnOn)){
    else if((ledState == LOW)&&(val > THRESH)&&(toTurnOn != -1)&&(millis() > toTurnOn)){
    //turn leds on
    ledState = HIGH;
    digitalWrite(13,ledState);
    rgb(5,6,3,A0,A1,0);
      delay(ONTIME/3);
      turnOff(3,5,6);
    rgb(5,6,3,A2,0,A3);
      delay(ONTIME/3);
      turnOff(3,5,6);
    rgb(5,6,3,0,A1,A4);
      delay(ONTIME/3);
//      turnOff(3,5,6);
    toTurnOn = -1;
    lastOn = millis();   
  }
  // if on for more than ONTIME milliseconds
  else if((ledState == HIGH)&&((millis()-lastOn) > ONTIME)){
    //turn leds off
    ledState = LOW;
    digitalWrite(13,ledState);
    digitalWrite(6,ledState);
    digitalWrite(5,ledState);
    digitalWrite(3,ledState);
    myservo.write(0); 
    delay(1);
    //open camera box
    myservo.write(90);
    delay(1000);  
  }

  Serial.write( 0xff);
  Serial.write( (val >> 8) & 0xff);
  Serial.write( val & 0xff);
}



void rgb(int r, int g, int b, int analog1, int analog2, int analog3){
  
  int oldRGB[3] = {
  0,0,0};

 int val = analogRead(analog1);
  val = constrain(val,600,900);
  if(abs(val - oldRGB[0]) > 5){
    int mval = map(val,600,900,255,0);
    analogWrite(b,mval); 
    oldRGB[0] = val;
    Serial.print("B ");
    Serial.print(mval);
    Serial.print('\n');
  }
  delay(10);

  val = analogRead(analog2);
  val = constrain(val,600,900);
  if(abs(val - oldRGB[1]) > 5){
    int mval = map(val,600,900,255,0);
    analogWrite(r,mval); 
    oldRGB[1] = val;
    Serial.print("R ");
    Serial.print(mval);
    Serial.print('\n');
  }
  delay(10);

  val = analogRead(analog3);
  val = constrain(val,600,900);
  if(abs(val - oldRGB[2]) > 5){
    int mval = map(val,600,900,255,0);    
    analogWrite(g,mval); 
    oldRGB[2] = val;
    Serial.print("G ");
    Serial.print(mval);
    Serial.print('\n');
  }
  delay(10);

}


void turnOff (int r, int g, int b){
    digitalWrite(r,LOW);
    digitalWrite(g,LOW);
    digitalWrite(b,LOW);
}
