
#include "PMS5XXX.h"

#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
PMS5XXX::PMS5XXX(SoftwareSerial &uart): m_puart(&uart)
{
    m_puart->begin(9600);
    p = new long[13];
}
#else
PMS5XXX::PMS5XXX(HardwareSerial &uart): m_puart(&uart)
{
    m_puart->begin(9600);
    p = new long[13];
}
#endif

void PMS5XXX::read(){
  byte b3[32] = {0};
  int i = 0;
  int j = 0;
  int k = 0;
#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
  m_puart->listen();
#endif
  while (m_puart->available() > 0) {
    b3[i] = m_puart->read();
    i++;
    if (i > 1 && (b3[0] != 0x42 || b3[1] != 0x4d))
      i = 0;
    if (i >= 32) break;
  }

  for (j = 0; j < 13; j++) {
    p[j] = b3[2 * j + 4] * 0x100 + b3[2 * j + 5];
  }

  for (j = 0; j < 30; j++) {
    k += b3[j];
  }
  j = b3[30] * 0x100 + b3[31];
#ifdef DEBUG
  Serial.print(b3[0], HEX); p_null();
  Serial.print(b3[1], HEX); p_null();
  //Serial.print(b3[28]); p_null();
  //Serial.print(b3[29]); p_null();
  Serial.print(j); p_null();
  Serial.print(k); p_null();
  Serial.print(i_error); p_null();
  Serial.println();
#endif
  if (j > 0 && j == k) {
    i_error = 0;    
    pm1 = p[3];
    pm2d5 = p[4];
    pm10 = p[5];
  } else if (i_error >= ERROR_MAX) {
    i_error = 0;
    for (j = 0; j < 13; j++)
      p[j] = 0;
    pm1 = 0;
    pm2d5 = 0;
    pm10 = 0;
  } else {
    i_error++;
    delay(200);
    read();
  }    
}

int PMS5XXX::getAQI(int pm2d5){
    if(pm2d5 > 500)
        return 500;
    if(pm2d5 > 350)
        return (pm2d5 - 350) * 100 / (500 - 350) + 400;
    if(pm2d5 > 250)         
        return (pm2d5 - 250) * 100 / (350 - 250) + 300;
    if(pm2d5 > 150)         
        return (pm2d5 - 150) * 100 / (250 - 150) + 200;
    if(pm2d5 > 115)         
        return (pm2d5 - 115) * 50  / (150 - 115) + 150;
    if(pm2d5 > 75)          
        return (pm2d5 - 75)  * 50  / (115 - 75 ) + 100; 
    if(pm2d5 > 35)          
        return (pm2d5 - 35)  * 50  / (75  - 35 ) + 50; 
    else                    
        return (pm2d5 - 0)   * 50  / (35  - 0  ) + 0;
    
}