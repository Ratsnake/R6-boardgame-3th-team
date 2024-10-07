#include <Servo.h>

const int sv1_pin = 7;
const int sv2_pin = 6;
Servo sv1;
Servo sv2;

void sv1_speed(int pct){
  int angle = 90-0.9*pct;
  sv1.write(angle);
}

void sv2_speed(int pct){
  int angle = 90-0.9*pct;
  sv2.write(angle);
}

void setup() {
  sv1.attach(sv1_pin,700,2300);
  sv2.attach(sv2_pin,700,2300);
}

void loop() {
  sv1_speed(10000);
  sv2_speed(1000); 
  delay(100);
  sv1_speed(0);
  sv2_speed(0);

}
