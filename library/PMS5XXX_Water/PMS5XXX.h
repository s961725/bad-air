
#ifndef pm2_5_h
#define pm2_5_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define PMS5XXX_USE_SOFTWARE_SERIAL

//#define DEBUG
#define ERROR_MAX 10

// if not find mega, using SoftwareSerial
#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
#include "SoftwareSerial.h"
#endif


class PMS5XXX{
public:
#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
    PMS5XXX(SoftwareSerial &uart);
#else    
    PMS5XXX(HardwareSerial &uart);
#endif
    int i_error = 0;
    long *p;
    int pm1;
    int pm2d5;
    int pm10;
    void read();
    int getAQI(int pm2d5);   //pm2.5
    
#ifdef PMS5XXX_USE_SOFTWARE_SERIAL
    SoftwareSerial *m_puart; 
#else
    HardwareSerial *m_puart; 
#endif    
};
#endif