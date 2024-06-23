#include<MobaTools.h>
char inData;
const byte stepPin = 9;
const byte dirPin  = 8;
const int stepsPerRev = 800;   // Steps per Revolution ( example with 1/4 microsteps )
const long  targetPos = 4000;         // stepper moves between 0 and targetpos
long nextPos;

MoToStepper myStepper ( stepsPerRev, STEPDIR );
MoToTimer stepperPause;
bool stepperRunning;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  myStepper.attach(stepPin, dirPin);
  myStepper.setSpeed(3000);
  myStepper.setRampLen(20);
  stepperRunning = true;

}

void loop() {
  readSerial();
  if (Serial2.read() == 3) {
    Serial.print("Eda Mwoone data vannu:");
    Serial.println(inData);
  }

}
void motor() {
  if ( stepperRunning ) {
    // Wait till stepper has reached target, then set pause time
    if ( !myStepper.moving() ) {
      // stepper has reached target, start pause
      stepperPause.setTime( 1000 );
      stepperRunning = false;
    }
  } else {
    // stepper doesn't move, wait till stepperPause time expires
    if ( stepperPause.expired() ) {
      // stepperPause time expired. Start stepper in opposite direction
      if ( nextPos == 0 ) {
        nextPos = targetPos;
      } else {
        nextPos = 0;
      }
      myStepper.moveTo( nextPos );
      stepperRunning = true;
    }
  }
}

void readSerial() {
  while (Serial2.available()) {
    inData = Serial2.read();
    delay(10);
    Serial.print("Serial Recieved :");
    Serial.println(inData);
  }

}
