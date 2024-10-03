#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop(){

  if (mySerial.available() >= 0){

    String data = mySerial.readStringUntil('\n');

    int value = data.toInt();

    Serial.println(value);

  }

}