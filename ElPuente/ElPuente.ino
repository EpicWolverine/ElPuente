//byte IR1Pin = ;
//byte warningLedPin = ;

bool IR1State = false;
bool IR1LastState = false;
//bool IR2State = false;
//bool IR2LastState = false;
bool bridgeState = false; //false=lowered; true=raised

void setup() {
  //pinMode(IR1Pin, OUTPUT);
  //pinMode(warningLedPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("El Puente!");
}

void loop() {
  //if(bridgeState=true){ //flash the lights

  //check and store IR sensor 1
  //check and store IR sensor 2

  //if detection on IR sensor 1 (IR1State != IR1LastState && IR1State == true)
    //raise bridge for x seconds (see how long it takes to raise)
    //bridgeState = true
  
  //if detection on IR sensor 1 (IR1State != IR1LastState && IR1State == false)
    //delay() //wait for train to finish passing
    //lower bridge for x seconds (see how long it takes to lower)
    //bridgeState = false
}
