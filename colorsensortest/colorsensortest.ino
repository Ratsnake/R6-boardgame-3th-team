#include <Wire.h>
#include <BH1745NUC.h>

BH1745NUC bh1745nuc_39(BH1745NUC_DEVICE_ADDRESS_39);
BH1745NUC bh1745nuc_38(BH1745NUC_DEVICE_ADDRESS_38);

void setup() {

  byte rc;
  byte rc_2;

  Serial.begin(9600);
	
  Wire.begin();
  
  rc = bh1745nuc_39.init();
  rc_2 = bh1745nuc_38.init();

}

void loop() {
  byte rc;
  byte rc_2;
  unsigned short rgbc_1[4];
  unsigned short rgbc_2[4];

  rc = bh1745nuc_39.get_val(rgbc_1);
  rc_2 = bh1745nuc_38.get_val(rgbc_2);

  if (rc == 0){
    Serial.write("BH1745NUC_39 (RED)   = ");
    Serial.println(rgbc_1[0]);
    Serial.write("BH1745NUC_39 (GREEN) = ");
    Serial.println(rgbc_1[1]);
    Serial.write("BH1745NUC_39 (BLUE)  = ");
    Serial.println(rgbc_1[2]);
    Serial.write("BH1745NUC_39 (CLEAR) = ");
    Serial.println(rgbc_1[3]);    
    Serial.println();
  }
  if (rc == 0){
    Serial.write("BH1745NUC_38 (RED)   = ");
    Serial.println(rgbc_2[0]);
    Serial.write("BH1745NUC_38 (GREEN) = ");
    Serial.println(rgbc_2[1]);
    Serial.write("BH1745NUC_38 (BLUE)  = ");
    Serial.println(rgbc_2[2]);
    Serial.write("BH1745NUC_38 (CLEAR) = ");
    Serial.println(rgbc_2[3]);    
    Serial.println();
  }

}