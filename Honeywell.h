/*
  Honeywell.h - Library for controlling Honeywell HPMA 115S0-XXX sensor.
  Created by Jurgen Çelmeta, May 17, 2020.
  
  MIT License
*/
#ifndef Honeywell_H
#define Honeywell_H

#include "Arduino.h"
#include "SoftwareSerial.h"

class Honeywell {
    public:
        Honeywell(int softSerialRX, int softSerialTX, int delayBetweenMeasurement, int respinTime);
        void begin(int baudRate);
        bool stopAutoSend();
        bool startMeasurement();
        bool stopMeasurement();
        bool readMeasurement();
        int[2] getMeasurement();
    private:
        int _softSerialRX;
        int _softSerialTX;
        int _delayBetweenMeasurement;
        int _respinTime;
        int _pm25;
        int _pm10;
        SoftwareSerial _honeywellSoftwareSerial(int softSerialRX, int softSerialTX);
}

#endif