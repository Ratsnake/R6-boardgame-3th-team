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

const int LED_1 = 4;
const int LED_2 = 5;
const int LED_3 = 6;

const int sv1_pin = 10;
const int sv2_pin = 11;

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
        Serial.println(time);

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
      sv1_speed(0);
      sv2_speed(0);
      

      send_data('p', point);

      delay(2000);

      if(digitalRead(button_1) != HIGH){
        break;
      }

      send_data('l', point/10);

      delay(2000);
    }else{

      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      send_data('c', 3);
      delay(1000);
      digitalWrite(LED_3, LOW);
      send_data('c', 2);
      delay(1000);
      digitalWrite(LED_2, LOW);
      send_data('c', 1);
      delay(1000);
      digitalWrite(LED_1, LOW);

      time = 30;
      cont = 0;
      point = 0;
      send_data('p', point);
      MsTimer2::start();
      sv1_speed(10);
      sv2_speed(10);
    }

  }
}

void time_countdown(){
  time -= 1;

  sum_time += 1;

  if(time <= 0 || sum_time > 180){
    cont = 1;
  }

  //LED制御

  unsigned short rem_sum_time = 180 - sum_time;

  if(time > 180){

    if(rem_sum_time > 120){
      if(rem_sum_time > 150){
        digitalWrite(LED_3, HIGH);
      }else{
        if(rem_sum_time %2 == 0){
          digitalWrite(LED_3, HIGH);
        }else{
          digitalWrite(LED_3, LOW);
        }
      }
    }else{
      digitalWrite(LED_3, LOW);
    }

    if(rem_sum_time > 60){
      if(rem_sum_time > 90){
       digitalWrite(LED_2, HIGH);
      }else{
        if(rem_sum_time %2 == 0){
          digitalWrite(LED_2, HIGH);
        }else{
          digitalWrite(LED_2, LOW);
        }
      }
    }else{
      digitalWrite(LED_2, LOW);
    }

    if(rem_sum_time > 0){
      if(rem_sum_time > 30){
        digitalWrite(LED_1, HIGH);
      }else{
        if(rem_sum_time %2 == 0){
          digitalWrite(LED_1, HIGH);
        }else{
          digitalWrite(LED_1, LOW);
        }
      }
   }else{
     digitalWrite(LED_1, LOW);
   }
  }else{
  
    if(time > 120){
      if(time > 150){
        digitalWrite(LED_3, HIGH);
      }else{
       if(time %2 == 0){
         digitalWrite(LED_3, HIGH);
        }else{
          digitalWrite(LED_3, LOW);
        }
      }
    }else{
      digitalWrite(LED_3, LOW);
    }

    if(time > 60){
      if(time > 90){
        digitalWrite(LED_2, HIGH);
      }else{
        if(time %2 == 0){
          digitalWrite(LED_2, HIGH);
        }else{
          digitalWrite(LED_2, LOW);
        }
      }
    }else{
      digitalWrite(LED_2, LOW);
    }

    if(time > 0){
      if(time > 30){
        digitalWrite(LED_1, HIGH);
      }else{
        if(time %2 == 0){
          digitalWrite(LED_1, HIGH);
        }else{
          digitalWrite(LED_1, LOW);
        }
      }
    }else{
      digitalWrite(LED_1, LOW);
    }
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

  float r_norm = (float)data[0] / data[3];
  float g_norm = (float)data[1] / data[3];
  float b_norm = (float)data[2] / data[3];
  
  // 最大値を見つける
  float max_val = max(max(r_norm, g_norm), b_norm);
  
  // 2番目に大きい値を見つける
  float second_max = 0;
  if (max_val == r_norm) {
    second_max = max(g_norm, b_norm);
  } else if (max_val == g_norm) {
    second_max = max(r_norm, b_norm);
  } else {
    second_max = max(r_norm, g_norm);
  }
  
  // 最大値と2番目の値の差を計算
  float difference = max_val - second_max;
  
  // 閾値（この値は調整可能）
  float threshold = 0.2;
  
  if (difference > threshold) {
    if (max_val == r_norm) {
      point += 2;
      time += 2;
    } else if (max_val == g_norm) {
      point += 1;
      time += 1;
    } else if (max_val == b_norm) {
      point += 5;
      time += 5;
    }
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
    break;
  }

}