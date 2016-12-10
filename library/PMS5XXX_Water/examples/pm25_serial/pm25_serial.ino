#include "PMS5XXX.h"
#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
SoftwareSerial mySerial(6, 7); // MEAG TX:10, RX:11
PMS5XXX pm2_5(mySerial);
#else
PMS5XXX pm2_5(Serial2);
#endif
void setup() {
  Serial.begin(9600);  
}

void loop() {
  pm2_5.read();
  Serial.print("pm1.0=");
  Serial.print(pm2_5.pm1);
  Serial.print("; pm2.5=");
  Serial.print(pm2_5.pm2d5);
  Serial.print("; pm10=");
  Serial.print(pm2_5.pm10);
  Serial.print("; AQI=");
  Serial.print(pm2_5.getAQI(pm2_5.pm2d5));
  Serial.println();
  delay(1000);
}
