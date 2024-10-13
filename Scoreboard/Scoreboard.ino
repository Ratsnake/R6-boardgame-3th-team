#include <SoftwareSerial.h>
#include <MsTimer2.h>

SoftwareSerial mySerial(12, 13);//rx,tx

int num_data = 0;

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
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  mySerial.begin(9600);
  while(!mySerial);

  /**
  Serial.begin(9600);
  while(!Serial)

  Serial.println("Setup Complete");
  **/
}

short type;

void loop() {
  // put your main code here, to run repeatedly:

  /**
  type 0: point
  type 1: level
  type 2, countdown
  **/

  while(1){
    
    if(mySerial.available()){
      String data = mySerial.readStringUntil('\n');

      if(data.startsWith("point:")){
        num_data = data.substring(6).toInt();
        type = 0;
      }else if(data.startsWith("level:")){
        num_data = data.substring(6).toInt();
        type = 1;
      }else if(data.startsWith("countdown:")){
        num_data = data.substring(10).toInt();
        type = 2;
      }
    }

    if (type == 0){
      display(num_data);
    }else if(type == 1){
      dynamic(11, 'l');
      display(num_data);
    }else if(type == 2){
      dynamic(11, num_data);
    }
    
  }

}

void display(int num){
  dynamic(9, num-num/10*10);

  if (num >= 1000 || num/10-num/100*10 != 0 || num/100 != 0){

    dynamic(10, num/10-num/100*10 );
      
  }
  if (num/100){

    dynamic(11, num/100);

  }
}

void dynamic(int index, int num){

  const int a = 2;
  const int b = 3;
  const int c = 4;
  const int d = 5;
  const int e = 6;
  const int f = 7;
  const int g = 8;

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
    case 'l':
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
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