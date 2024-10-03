#include <Wire.h>
#include <BH1745NUC.h>
#include <SoftwareSerial.h>
#include <MsTimer2.h>

SoftwareSerial mySerial(12, 13);//rx.tx

BH1745NUC bh1745nuc_39(BH1745NUC_DEVICE_ADDRESS_39);
BH1745NUC bh1745nuc_38(BH1745NUC_DEVICE_ADDRESS_38);

const int button_1 = 2;
const int button_2 = 3;

const int out_1 = 13;

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

  mySerial.println("reset");

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