#include <Wire.h>
#include <BH1745NUC.h>
#include <SoftwareSerial.h>
#include <MsTimer2.h>
#include <Servo.h>

SoftwareSerial mySerial(12, 13);//rx.tx

BH1745NUC bh1745nuc_39(BH1745NUC_DEVICE_ADDRESS_39);
BH1745NUC bh1745nuc_38(BH1745NUC_DEVICE_ADDRESS_38);

Servo sv1;
Servo sv2;

const int button_1 = 2;
const int button_2 = 3;

const int out_1 = 13;

const int sv1_pin = 6;
const int sv2_pin = 7;

void sv1_speed(int pct){
  int angle = 90-0.9*pct;
  sv1.write(angle);
}

void sv2_speed(int pct){
  int angle = 90-0.9*pct;
  sv2.write(angle);
}

unsigned short point = 356;

void setup() {

  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);

  byte rc;
  byte rc_2;
	
  mySerial.begin(9600);
  while(!mySerial);
  
  Wire.begin();
  
  rc = bh1745nuc_39.init();
  rc_2 = bh1745nuc_38.init();

  sv1.attach(sv1_pin,700,2300);
  sv2.attach(sv2_pin,700,2300);

  delay(500);

}

void loop() {
  byte rc;
  byte rc_2;
  unsigned short rgbc_1[4];
  unsigned short rgbc_2[4];

  int rand;
  
  while(1){
    mySerial.print("point:");
    mySerial.println(point);
    
    delay(2000);

    mySerial.print("rank:");
    mySerial.println(4);
    delay(2000);
  }
}