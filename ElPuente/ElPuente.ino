//byte IR1Pin = ;
byte warningLedPinLeft = 2;
byte warningLedPinRight = 3;

int millisDelay = 500;
int previousMillis = 0;

bool IR1State = false;
bool IR1LastState = false;
//bool IR2State = false;
//bool IR2LastState = false;
bool bridgeState = true; //false=lowered; true=raised
bool warningLedState = false;

void setup() {
  //pinMode(IR1Pin, OUTPUT);
  pinMode(warningLedPinLeft, OUTPUT);
  pinMode(warningLedPinRight, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("El Puente!");
}

void loop() {
  //check and store IR sensor 1
  //check and store IR sensor 2

  if((millis() - previousMillis) > millisDelay){
    previousMillis = millis();
    if(bridgeState=true){ //flash the lights
      if(warningLedState == false){
        digitalWrite(warningLedPinLeft, HIGH);  
        digitalWrite(warningLedPinRight, LOW);
      }
      else{
        digitalWrite(warningLedPinLeft, LOW);  
        digitalWrite(warningLedPinRight, HIGH);        
      }
      warningLedState = !warningLedState;
    }
    delay(1);
  }
  

  //if detection on IR sensor 1 (IR1State != IR1LastState && IR1State == true)
    //raise bridge for x seconds (see how long it takes to raise)
    //bridgeState = true
  
  //if detection on IR sensor 1 (IR1State != IR1LastState && IR1State == false)
    //delay() //wait for train to finish passing
    //lower bridge for x seconds (see how long it takes to lower)
    //bridgeState = false
}
