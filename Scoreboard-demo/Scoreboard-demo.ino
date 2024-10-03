#include <SoftwareSerial.h>
#include <MsTimer2.h>

SoftwareSerial mySerial(12, 13);//rx,tx

const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;

unsigned int point = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  mySerial.begin(9600);
  while(!mySerial);

  Serial.begin(9600);
  while(!Serial)

  Serial.println("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1){
    
    String data = mySerial.readStringUntil('\n');

    if (data.startsWith("SET")){
      point = 0;
    }else if(data.startsWith("PLUS")){
      point += 1;
    }

    display(point);
  }

}

void display(unsigned short num){
  dynamic(9, num-num/10*10);

  if (num/10-num/100*10 != 0 || num/100 != 0){

    dynamic(10, num/10-num/100*10);
      
  }
  else if (num/100){

    dynamic(11, num/100);

  }
}

void dynamic(int index, int num){

  digitalWrite(index, HIGH);

  switch(num){
    case 0:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
    break;
    case 1:
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;
    case 2:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    break;
    case 3:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    break;
    case 4:
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
    case 5:
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
    case 6:
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
    case 7:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;
    case 8:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
    case 9:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
  }

  digitalWrite(index, LOW);
  
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);

}