#include <MobaTools.h>

const byte stepPin = 9;
const byte dirPin  = 8;
const int stepsPerRev = 400;// Steps per Revolution
const long  targetPos = 2000;       // stepper moves between 0 and targetpos
long nextPos;

String data_display = "";
String DATA = "";

MoToStepper motor1(stepsPerRev, STEPDIR);
MoToTimer stepperPause;
bool stepperRunning;

bool speed1, speed2, speed3, speed4, speed5, res;

void setup() {
  motor1.attach( stepPin, dirPin);
  motor1.setRampLen(50);
  stepperRunning = true;

  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("Motor Display Control Test");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  speed1 = false;
  speed2 = false;
  speed3 = false;
  speed4 = false;
  speed5 = false;
  res = false;
  if (Serial2.available()) {
    data_display = "";
    delay(30);
    while (Serial2.available()) {
      char ch = Serial2.read();
      if (ch != '\n' && ch != '\r') {
        data_display += ch;
      }
    }
    send_data(data_display);
  }
  while (speed1 == true); {
    Serial.println("RPM:20");
    motor1.setSpeed(200);
    motor();
  }
  while (speed2 == true); {
    motor1.setSpeed(500);
    Serial.println("RPM:50");
    motor();
  }
  while (speed3 == true); {
    motor1.setSpeed(800);
    Serial.println("RPM:80");
    motor();
  }
  while (speed4 == true); {
    motor1.setSpeed(1200);
    Serial.println("RPM:120");
    motor();
  }
  while (speed5 == true); {
    motor1.setSpeed(100);
    motor1.rotate(1);
  }
  while(res == true); {
    digitalWrite(LED_BUILTIN, HIGH);
      }
}

void motor() {
  if (!stepperRunning) {
    if (!motor1.moving()) {
      stepperPause.setTime(1000);
      stepperRunning = false;
    }
  } else {
    if (stepperPause.expired() ) {
      if (nextPos == 0) {
        nextPos = targetPos;
      } else {
        nextPos = 0;
      }
      motor1.moveTo(nextPos);
      stepperRunning = true;
    }
  }
}

void send_data(String data_display) {
  if (data_display == "1") {
    speed1 = true;
  } else if (data_display == "2") {
    speed2 = true;
  } else if (data_display == "3") {
    speed3 = true;
  } else if (data_display == "4") {
    speed4 = true;
  } else if (data_display == "5") {
    speed5 = true;
  } else if (data_display == "RESET") {
    res = true;
  }

}
