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
bool warningLedState = false; //is left on or right on?

//Distance Sensor
#define distanceThreshold 60 //bridge lowers if less than this (cm)
#define distanceMax       200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(distanceTrigPin, distanceEchoPin, distanceMax); // NewPing setup of pins and maximum distance.

//Motor
#define motorPin1 6
#define motorPin2 7

//LIMIT SWITCHES!
#define limitSwitchTop    10
#define limitSwitchBottom 9

void setup() {
  //PinModes
  pinMode(warningLedPinLeft, OUTPUT);
  pinMode(warningLedPinRight, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(limitSwitchTop, OUTPUT);
  pinMode(limitSwitchBottom, OUTPUT);
  
  //Inital conditons
  digitalWrite(warningLedPinLeft, LOW);
  digitalWrite(warningLedPinRight, LOW);

  //Serial init
  Serial.begin(9600);
  Serial.println("El Puente!");
}

void loop() {
  Serial.print("bridgeState: ");
  Serial.println(bridgeState);
  
  //Check distance sensor
  int distance = getDist();
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance < distanceThreshold && bridgeState == 0) {
    bridgeState = 1;
  }
  if (digitalRead(limitSwitchTop) == HIGH && bridgeState == 1) {
    bridgeState = 2;
  }
  if (distance > distanceThreshold && bridgeState == 2) {
    bridgeState = 3;
  }
  if (digitalRead(limitSwitchBottom) == HIGH && bridgeState == 3) {
    bridgeState = 0;
  }

  //Bridge motor logic
  if(bridgeState == 0 || bridgeState == 2){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }
  else if(bridgeState == 1){
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
  else if(bridgeState == 3){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }

  //Timer
  if ((millis() - previousMillis) > millisDelay) {
    previousMillis = millis();
    Serial.println(previousMillis);

    //The bridge is raised
    if (bridgeState != 0) { //flash the lights
      //Railroad Lights
      if (warningLedState == false) {
        digitalWrite(warningLedPinLeft, HIGH);
        digitalWrite(warningLedPinRight, LOW);
        Serial.println("Left!");
      }
      else {
        digitalWrite(warningLedPinLeft, LOW);
        digitalWrite(warningLedPinRight, HIGH);
        Serial.println("Right!");
      }
      warningLedState = !warningLedState;
    }
    else{
      digitalWrite(warningLedPinLeft, LOW);
      digitalWrite(warningLedPinRight, LOW);
    }

    Serial.println("---------");
  }
}

int getDist() {
  //This fixes the sensor getting stuck at 0
  if (sonar.ping() == 0) {
    pinMode(distanceEchoPin, OUTPUT);
    digitalWrite(distanceEchoPin, LOW);
    pinMode(distanceEchoPin, INPUT);
  }

  delay(30);

  int reading = sonar.ping_cm();
  if (reading == 0){ //out of range
    reading = 9999; //really big number far larger than range
  }
  return reading;
}
