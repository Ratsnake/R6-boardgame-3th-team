#include <Wire.h>
#include <BH1745NUC.h>
#include <SoftwareSerial.h>
#include <MsTimer2.h>
#include <Servo.h>

SoftwareSerial mySerial(12, 13);//rx.tx

BH1745NUC bh1745nuc_1(BH1745NUC_DEVICE_ADDRESS_38);
BH1745NUC bh1745nuc_2(BH1745NUC_DEVICE_ADDRESS_39);

Servo sv1;
Servo sv2;

unsigned int point = 0;

const int button_1 = 2;
const int button_2 = 3;

const int sv1_pin = 6;
const int sv2_pin = 7;

int time = 0;
int sum_time = 0;

void setup() {

  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);

  byte rc;
  byte rc_2;
	
  mySerial.begin(9600);
  while(!mySerial);

  Serial.begin(9600);
  while(!Serial);
  
  Wire.begin();
  
  rc = bh1745nuc_1.init();
  rc_2 = bh1745nuc_2.init();

  sv1.attach(sv1_pin,700,2300);
  sv2.attach(sv2_pin,700,2300);

  MsTimer2::set(1000, time_countdown);

  delay(500);

}

int buttonState_1 = HIGH;
int lastButtonState_1 = HIGH;
int buttonState_2 = HIGH;
int lastButtonState_2 = HIGH;
bool actionDone_1 = false;
bool actionDone_2 = false;

int cont = 1;

void loop() {
  byte rc;
  byte rc_2;
  unsigned short rgbc_1[4];
  unsigned short rgbc_2[4];

  while(cont == 0){

    sv1_speed(10);
    sv2_speed(10);

    //ボタンの処理ここから
    buttonState_1 = digitalRead(button_1);
    buttonState_2 = digitalRead(button_2);

    //Serial.println(buttonState_1);
    //Serial.println(buttonState_2);

    if(buttonState_1 == LOW && lastButtonState_1 == HIGH){
      if(!actionDone_1) {

        Serial.println("action");
        Serial.println(time);

        bh1745nuc_1.get_val(rgbc_1);

        point_proc(rgbc_1);

        send_data('p', point);

        actionDone_1 = true;
      }

    }

    if(buttonState_2 == LOW && lastButtonState_2 == HIGH){
      if(!actionDone_2) {

        Serial.println("action");

        bh1745nuc_2.get_val(rgbc_2);

        point_proc(rgbc_2);

        send_data('p', point);

        actionDone_2 = true;
      }

    }

    if (buttonState_1 == HIGH && lastButtonState_1 == LOW) {

      actionDone_1 = false;
    }

    if (buttonState_2 == HIGH && lastButtonState_2 == LOW) {

      actionDone_2 = false;
    }

    lastButtonState_1 = buttonState_1;
    lastButtonState_2 = buttonState_2;
    //ボタンの処理終わり
  }

  while(cont == 1){

    if (digitalRead(button_1) == HIGH){
      MsTimer2::stop();

      send_data('p', point);

      delay(2000);

      if(digitalRead(button_1) != HIGH){
        break;
      }

      send_data('l', point/10);

      delay(2000);
    }else{

      send_data('c', 3);
      delay(1000);
      send_data('c', 2);
      delay(1000);
      send_data('c', 1);
      delay(1000);

      time = 30;
      cont = 0;
      point = 0;
      send_data('p', point);
      MsTimer2::start();
    }

  }
}

void time_countdown(){
  time -= 1;

  sum_time += 1;

  if(time <= 0 || sum_time > 180){
    cont = 1;
  }
}

void sv1_speed(int pct){
  int angle = 90-0.9*pct;
  sv1.write(angle);
}

void sv2_speed(int pct){
  int angle = 90-0.9*pct;
  sv2.write(angle);
}

void point_proc(int data[4]){
  //r:0, g:1, b:2, c:3

  if(data[0] > 5000){

    point += 2;
    time += 2;
  }else if (data[1] > 5000){

    point += 1;
    time += 1;
  }else if (data[2] > 5000){

    point += 5;
    time += 5;
  }
}

void send_data(int type, int data){

  switch (type){
    case 'p':
    mySerial.print("point:");
    mySerial.println(data);
    break;

    case 'l':
    mySerial.print("level:");
    mySerial.println(data);
    break;

    case 'c':
    mySerial.print("countdown:");
    mySerial.println(data);
  }

}