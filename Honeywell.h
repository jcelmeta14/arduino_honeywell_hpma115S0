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
        Honeywell(int softSerialRX, int softSerialTX);
        void begin(int baudRate);
        bool stopAutoSend();
        bool startMeasurement();
        bool stopMeasurement();
        bool readMeasurement(long measurement[]);
    private:
        int _softSerialRX;
        int _softSerialTX;
        long _pm25;
        long _pm10;
        SoftwareSerial _honeywellSoftwareSerial;
};

#endif