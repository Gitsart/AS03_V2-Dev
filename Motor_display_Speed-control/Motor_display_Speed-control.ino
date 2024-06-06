#include<MobaTools.h>

const byte stepPin = 9;
const byte dirPin = 8;
const int stepsPerRev = 200;
const long targetPos = 2000;
long nextPos;

#define ledPin A15

bool sPeed1, sPeed2, sPeed3, lEd = false;

MoToStepper myStepper(stepsPerRev, STEPDIR);
MoToTimer stepperPause;
bool stepperRunning;

String data_display = "";
String DATA = "";

void setup() {
  myStepper.attach(stepPin, dirPin);
  myStepper.setRampLen(20);
  stepperRunning = true;

  pinMode(ledPin, OUTPUT);

  Serial2.begin(9600);
  Serial.begin(115200);
  Serial.println("DISPLAY MOTOR TEST");
}
void loop() {
  if (Serial2.available()) {
    data_display = "";
    delay(30);
    while (Serial2.available()) {
      char ch = Serial2.read();
      if (ch != '\n' && ch != '\r') { // filter out newline and carriage return
        data_display += ch;
      }
    }
    send_data(data_display);

  }

  if (sPeed1) {
    myStepper.setSpeed(1000);
    motor();
  }
  else if (sPeed2) {
    myStepper.setSpeed(2000);
    motor();
  }
  else if (sPeed3) {
    myStepper.setSpeed(3000);
    motor();
  }
  else if (lEd) {
    digitalWrite(ledPin, HIGH);
  }
  else if(!lEd){
    digitalWrite(ledPin, LOW);
    
  }
}

void send_data(String data_display) {

  if (data_display == "1") {
    Serial.println("setSpeed:100RPM");
    sPeed1 = true;
    lEd = false;
    digitalWrite(ledPin, LOW);

  } else if (data_display == "2") {
    Serial.println("setSpeed:200RPM");
    sPeed2 = true;
    lEd = false;
    digitalWrite(ledPin, LOW);

  } else if (data_display == "3") {
    Serial.println("setSpeed:300RPM");
    sPeed3 = true;
    lEd = false;
    digitalWrite(ledPin, LOW);

  }
  else if (data_display == "5") {
    myStepper.setSpeed(5000);
    myStepper.rotate(1);
    lEd = true;
  }
  else if (data_display == "RESET") {
    myStepper.stop();
    sPeed1=false;sPeed2 = false; sPeed3 = false;
    lEd = true;
    Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println(".");
    Serial.println("Ippo Engane Irikanu, Ellam Tholachille??");
  } else {
    Serial.println(" Correct Data Thaada Thendi");
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
