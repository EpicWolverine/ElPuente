#include <NewPing.h> //A better sensor library. See http://playground.arduino.cc/Code/NewPing

//Pins
#define warningLedPinLeft  2
#define warningLedPinRight 4
#define distanceTrigPin    12
#define distanceEchoPin    11

//Timer
int millisDelay = 500;
unsigned long previousMillis = 0;

//StateTracking
byte bridgeState = 2; //0=lowered; 1=raising; 2=raised; 3=lowering
bool warningLedState = false; //true=on

//Distance Sensor
#define distanceThreshold 1000 //bridge lowers if less than this
#define distanceMax       200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(distanceTrigPin, distanceEchoPin, distanceMax); // NewPing setup of pins and maximum distance.

//Motor
//#define motorPin1 
//#define motorPin2 

void setup() {
  //PinModes
  pinMode(warningLedPinLeft, OUTPUT);
  pinMode(warningLedPinRight, OUTPUT);
//  pinMode(motorPin1, OUTPUT);
//  pinMode(motorPin2, OUTPUT);
    
  //Inital conditons
  digitalWrite(warningLedPinLeft, HIGH);  
  digitalWrite(warningLedPinRight, HIGH);
  
  //Serial init
  Serial.begin(9600);
  Serial.println("El Puente!");
}

void loop() {
  //Check distance sensor
  Serial.print(getDist());
  Serial.println(" cm"); 
//  int distance = analogRead(distancePin);
//  if(distance < distanceThreshold && bridgeState == 0){
//    bridgeState = 1;
//  }
//  if(distance > distanceThreshold && bridgeState == 2){
//    bridgeState = 3;
//  }

//  if(bridgeState == 0 || bridgeState == 2){
//    digitalWrite(motorPin1, LOW);
//    digitalWrite(motorPin2, LOW);
//  }
//  else if(bridgeState == 1){
//    digitalWrite(motorPin1, HIGH);
//    digitalWrite(motorPin2, LOW);
//  }
//  else if(bridgeState == 3){
//    digitalWrite(motorPin1, LOW);
//    digitalWrite(motorPin2, HIGH);
//  }
  
  //if detection on IR sensor 1 (IR1State != IR1LastState && IR1State == true)
    //raise bridge for x seconds (see how long it takes to raise)
    //bridgeState = true
  
  //if detection on IR sensor 1 (IR1State != IR1LastState && IR1State == false)
    //delay() //wait for train to finish passing
    //lower bridge for x seconds (see how long it takes to lower)
    //bridgeState = false

  //Timer
  if((millis() - previousMillis) > millisDelay){
    previousMillis = millis();
    Serial.println(previousMillis);

    //The bridge is raised
    if(bridgeState != 0){ //flash the lights
      //Railroad Lights
      if(warningLedState == false){
        digitalWrite(warningLedPinLeft, HIGH);  
        digitalWrite(warningLedPinRight, LOW);
        Serial.println("Left!");
      }
      else{
        digitalWrite(warningLedPinLeft, LOW);
        digitalWrite(warningLedPinRight, HIGH);
        Serial.println("Right!");
      }
      warningLedState = !warningLedState;
    }
    
    Serial.println("---------");
  }
}

long getDist(){
  //This fixes the sensor getting stuck at 0 
  if(sonar.ping() == 0){
    pinMode(distanceEchoPin, OUTPUT);
    digitalWrite(distanceEchoPin, LOW);
    pinMode(distanceEchoPin, INPUT);
  }
  
  delay(30);
  
  return sonar.ping_cm();
}
