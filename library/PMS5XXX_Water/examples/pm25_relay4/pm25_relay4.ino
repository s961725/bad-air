// ¼ÌµçÆ÷¿ØÖÆ
#include "PMS5XXX.h"
#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
SoftwareSerial mySerial(10, 11); // MEAG TX:10, RX:11
PMS5XXX pm2_5(mySerial);
#else
PMS5XXX pm2_5(Serial2);
#endif

int lmt_relay[] = {50, 75, 90, 110};
int rel_pin[] = {2, 3, 4, 5};
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
    pinMode(rel_pin[i], OUTPUT);

  // test relay
  for (int i = 0; i < 4; i++)
    digitalWrite(rel_pin[i], HIGH);

  delay(2000);

  for (int i = 0; i < 4; i++)
    digitalWrite(rel_pin[i], LOW);
}

void loop() {
  int i = 0;
  pm2_5.read();
  int AQI = pm2_5.getAQI(pm2_5.pm2d5);
  Serial.print("pm1.0=");
  Serial.print(pm2_5.pm1);
  Serial.print("; pm2.5=");
  Serial.print(pm2_5.pm2d5);
  Serial.print("; pm10=");
  Serial.print(pm2_5.pm10);
  Serial.print("; AQI=");
  Serial.print(AQI);
  Serial.println();
  for (i = 0; i < 4; i++) {
    if (AQI > lmt_relay[i]) digitalWrite(rel_pin[i], LOW);
    else digitalWrite(rel_pin[i], HIGH);
  }

  delay(1000);
}
