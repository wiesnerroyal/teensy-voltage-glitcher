 // IO's
const int mosfetPin = 13;
const int resetPin  = 14; 

// VAR's
uint32_t i_resetDelay   = 100;
uint32_t i_startDelay   = 0;    // in millis
uint32_t i_impulsLength = 0;    // in micros
byte b_msg = 0x00;

// CONST's
#define setBootDelay      0x41
#define setImpulsLength   0x42
#define getSettings       0x43
#define startGlitch       0x44


void setup(){
  pinMode(mosfetPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(mosfetPin, HIGH);
  digitalWrite(resetPin, HIGH);
  Serial.begin(115200);
  while(!Serial){}
}

void loop(){
  if (Serial.available() > 0){
    b_msg = Serial.read();

    switch(b_msg){
      case setBootDelay:
        while(Serial.available() == 0) {}
        i_startDelay = Serial.parseInt();
        break;
      
      case setImpulsLength:
        while(Serial.available() == 0) {}
        i_impulsLength = Serial.parseInt();  
        break;

      case getSettings:
        Serial.print(i_startDelay);
        Serial.print(",");
        Serial.println(i_impulsLength);
        break;
    
      case startGlitch:
      // teensy
        // start glitch
        digitalWriteFast(resetPin, LOW);
        delay(i_resetDelay);
        digitalWriteFast(resetPin, HIGH);
        delay(i_startDelay);
        digitalWriteFast(mosfetPin, LOW);
        delayMicroseconds(i_impulsLength);
        digitalWriteFast(mosfetPin, HIGH);
        break;
    }
  }
}
// for shorter impulse count clock pulses with ARM_DWT_CYCCNT
