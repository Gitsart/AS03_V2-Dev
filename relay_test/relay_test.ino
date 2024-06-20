#include<MobaTools.h>

MoToTimer pAuse;

void setup() {
 pinMode(25,OUTPUT);
 pinMode(7,OUTPUT);

}

void loop() {
digitalWrite(25,HIGH);
pAuse.setTime(1000);

digitalWrite(25,LOW);
pAuse.setTime(1000);

}

 
