void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int swtch = digitalRead(8);
  if (swtch == 0) {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
  }
  else if (swtch == 1) {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    }

}
