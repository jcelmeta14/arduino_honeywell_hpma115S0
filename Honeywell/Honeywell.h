/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Honeywell_H
#define Honeywell_H

#include "Arduino.h"
#include "SoftwareSerial.h"

class Honeywell {
    public:
        Honeywell(int softSerialRX, int softSerialTX, int delayBetweenMeasurement, int respinTime);
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