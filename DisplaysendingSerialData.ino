String data_display = "";
String DATA = "";
int led = 13;
int ledpin = 11;
void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
  Serial.println("Enta Manakkaleku Swaagatham");

  pinMode(ledpin, OUTPUT); // Ensure you set the pinMode for the LED
  pinMode(led, OUTPUT);
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
    //    Serial.println("INPUT STRING IS: TESTING");
  }
}

void send_data(String data_display) {

  if (data_display == "1") {
    Serial.println("Eda MWone data KITTY");

  } else if (data_display == "2") {
    Serial.println("Adichu keri Vaa");

  } else if (data_display == "RESET") {
    Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println("."); Serial.println(".");
    Serial.println("Ippo Engane Irikanu, Ellam Tholachille??");
  } else {
    Serial.println(" Correct Data Thaada Thendi");
  }
}
