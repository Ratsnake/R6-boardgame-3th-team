#include <Wire.h>
#include <BH1745NUC.h>

BH1745NUC bh1745nuc(BH1745NUC_DEVICE_ADDRESS_38);

void setup() {
  byte rc;

  Serial.begin(9600);
  while (!Serial);
  
  Wire.begin();
  
  rc = bh1745nuc.init();
}

void loop() {
  byte rc;
  unsigned short rgbc[4];

  bh1745nuc.init();
  
  rc = bh1745nuc.get_val(rgbc);
  if (rc == 0) {
    Serial.write("BH1745NUC (RED)   = ");
    Serial.println(rgbc[0]);
    Serial.write("BH1745NUC (GREEN) = ");
    Serial.println(rgbc[1]);
    Serial.write("BH1745NUC (BLUE)  = ");
    Serial.println(rgbc[2]);
    Serial.write("BH1745NUC (CLEAR) = ");
    Serial.println(rgbc[3]);    
    Serial.println();
  }
 
  delay(500);

}
