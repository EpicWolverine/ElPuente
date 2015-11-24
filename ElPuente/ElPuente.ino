//Pins
//byte distancePin = ;
byte warningLedPinLeft = 2;
byte warningLedPinRight = 3;

//Timer
int millisDelay = 500;
unsigned long previousMillis = 0;

//StateTracking
byte bridgeState = 2; //0=lowered; 1=raising; 2=raised; 3=lowering
bool warningLedState = false; //true=on

//Distance Sensor
int distanceThreshold = 1000; //bridge lowers if less than this

//Motor
//byte motorPin1 = ;
//byte motorPin2 = ;

void setup() {
//  pinMode(distancePin, OUTPUT);
  pinMode(warningLedPinLeft, OUTPUT);
  pinMode(warningLedPinRight, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("El Puente!");
}

void loop() {
  //Check distance sensor
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
