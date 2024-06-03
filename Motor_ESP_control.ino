/*  Example for MobaTools
    Moving a stepper back and forth
*/
#include <MobaTools.h>

// Adjust pins, steps and time as needed
const byte stepPina = 9;
const byte dirPina  = 8;
const byte stepPinb = 4;
const byte dirPinb = 3;
const int stepsPerReva = 800;   // Steps per Revolution ( example with 1/4 microsteps )
const int stepsPerRevb = 800;
const long  targetPosa =8000;
const long targetPosb = 8000;// stepper moves between 0 and targetpos
long nextPosa;
long nextPosb;
int a = 0;
int b = 0;

MoToStepper mySteppera( stepsPerReva, STEPDIR );
MoToStepper myStepperb(stepsPerRevb, STEPDIR);
MoToTimer stepperPausea;//formotor1
MoToTimer stepperPauseb;//formotor2
bool stepperaRunning;
bool stepperbRunning;

void setup() {
  mySteppera.attach( stepPina, dirPina );
  mySteppera.setSpeed( 10000 );  // 60 Rev/Min ( if stepsPerRev is set correctly )
  mySteppera.setRampLen( 20 );
  stepperaRunning = true;

  myStepperb.attach( stepPinb, dirPinb);
  myStepperb.setSpeed(10000);
  myStepperb.setRampLen(20);
  stepperbRunning = true;

  
  pinMode(A7, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(52, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  espRead();

  Serial.print("a=");Serial.println(a);
  Serial.print("b=");Serial.println(b);

  if(a>=200) {
    motor1();
    digitalWrite(52,LOW);
  }
  if(b>=200) {
    motor2();
    digitalWrite(52,LOW);
  }
  else(digitalWrite(52,HIGH));
  
}

void motor1() {
  if ( stepperaRunning ) {
    // Wait till stepper has reached target, then set pause time
    if ( !mySteppera.moving() ) {
      // stepper has reached target, start pause
      stepperPausea.setTime( 1000 );
      stepperaRunning = false;
    }
  } else {
    // stepper doesn't move, wait till stepperPause time expires
    if ( stepperPausea.expired() ) {
      // stepperPause time expired. Start stepper in opposite direction
      if ( nextPosa == 0 ) {
        nextPosa = targetPosa;
      } else {
        nextPosa = 0;
      }
      mySteppera.moveTo( nextPosa );
      stepperaRunning = true;
    }
  }
}
void motor2() {
  if ( stepperbRunning ) {
    // Wait till stepper has reached target, then set pause time
    if ( !myStepperb.moving() ) {
      // stepper has reached target, start pause
      stepperPauseb.setTime( 1000 );
      stepperbRunning = false;
    }
  } else {
    // stepper doesn't move, wait till stepperPause time expires
    if ( stepperPauseb.expired() ) {
      // stepperPause time expired. Start stepper in opposite direction
      if ( nextPosb == 0 ) {
        nextPosb = targetPosb;
      } else {
        nextPosb = 0;
      }
      myStepperb.moveTo( nextPosb );
      stepperbRunning = true;
    }
  }
}

void espRead() {
  a = analogRead(A7);
  b = analogRead(A6);
}
