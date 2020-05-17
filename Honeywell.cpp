#include "Arduino.h"
#include "Honeywell.h"
#include "SoftwareSerial.h"

#define ACK 0xA5

Honeywell::Honeywell(int softSerialRX, int softSerialTX)
:
    _honeywellSoftwareSerial(softSerialRX, softSerialTX)
{
    _softSerialRX = softSerialRX;
    _softSerialTX = softSerialTX;
    _pm25 = 0;
    _pm10 = 0;
}

void Honeywell::begin(int baudRate)
{
    _honeywellSoftwareSerial.begin(baudRate);
}

bool Honeywell::stopAutoSend()
{
    byte stopAutoSendCommand[] = {0x68, 0x01, 0x20, 0x77};

    _honeywellSoftwareSerial.write(stopAutoSendCommand, sizeof(stopAutoSendCommand));

    // Wait to get the two response bytes
    while(_honeywellSoftwareSerial.available() < 2);

    byte response[2];
    _honeywellSoftwareSerial.readBytes(response, 2);

    if (response[0] == ACK && response[1] == ACK) {
        return true;
    }

    return false;
}

bool Honeywell::startMeasurement()
{
    byte startMeasurementCommand[] = {0x68, 0x01, 0x01, 0x96};

    _honeywellSoftwareSerial.write(startMeasurementCommand, sizeof(startMeasurementCommand));

    // Wait to get the two response bytes
    while(_honeywellSoftwareSerial.available() < 2);

    byte response[2];
    _honeywellSoftwareSerial.readBytes(response, 2);

    if (response[0] == ACK && response[1] == ACK) {
        return true;
    }

    return false;
}

bool Honeywell::stopMeasurement()
{
    byte stopMeasurementCommand[] = {0x68, 0x01, 0x02, 0x95};

    _honeywellSoftwareSerial.write(stopMeasurementCommand, sizeof(stopMeasurementCommand));

    // Wait to get two response bytes
    while(_honeywellSoftwareSerial.available() < 2);

    byte response[2];
    _honeywellSoftwareSerial.readBytes(response, 2);

    if (response[0] == ACK && response[1] == ACK) {
        return true;
    }

    return false;
}

bool Honeywell::readMeasurement(long measurement[])
{
    byte readMeasurementCommand[] = {0x68, 0x01, 0x04, 0x93};

    _honeywellSoftwareSerial.write(readMeasurementCommand, sizeof(readMeasurementCommand));

    // Wait to get two response bytes, if bytes match readMeasurement from datasheet get additional 6 bytes of response
    while(_honeywellSoftwareSerial.available() < 2);

    byte head;
    byte len;
    byte response[2];
    _honeywellSoftwareSerial.readBytes(response, 2);

    head = response[0];
    len = response[1];

    if (head == 0x40 && len == 0x05) {
        // Read the rest of the bytes of the response
        while(_honeywellSoftwareSerial.available() < 6);

        byte comd;
        byte df1;
        byte df2;
        byte df3;
        byte df4;
        byte cs;

        byte restResponse[6];
        _honeywellSoftwareSerial.readBytes(restResponse, 6);

        comd = restResponse[0];
        df1 = restResponse[1];
        df2 = restResponse[2];
        df3 = restResponse[3];
        df4 = restResponse[4];
        cs = restResponse[5];

        // Verify checksum
        if (((0x10000 - head - len - comd - df1 - df2 - df3 - df4) % 0xFF) != cs) {
            return false;
        }

        _pm25 = df1 * 256 + df2;
        _pm10 = df3 * 256 + df4;


        measurement[0] = _pm25;
        measurement[1] = _pm10;

        return true;
    }

    // NACK
    return false;
}