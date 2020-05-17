## Arduino library for Honeywell HPMA 115S0-XXX sensor

This is a Arduino Library which offers an easy way for using Honeywell HPMA 115S0-XXX dust sensor.

### Dependecies

This library uses SoftwareSerial to communicate with the Honeywell sensor, and thus may cause conflicts.

### A short word

The idea behind this library is to make it easy to perform some of the basic functions of the sensor. There are 4 functions that can be used to start, stop, read measurements and to stop the autosend of data. Other functionalities may be implemented in the future

## **The sensors works with 3.3V be sure to step the voltage down from 5V to 3.3V otherwise you may damage your sensor**

### Docs

1. Create an instance of the class in the beginning of a sketch.

```cpp
#include <Honeywell.h>
#define SOFT_SERIAL_RX 2
#define SOFT_SERIAL_TX 3

Honeywell honeywell(SOFT_SERIAL_RX, SOFT_SERIAL_TX);
```

2. Call the `begin` method in the `setup` function. You may stop the autosend feature of the sensors and perform measurements manually.

```cpp
void setup() {
  //DO OTHER STUFF
  
  honeywell.begin(9600);
  
  //OPTIONAL: Stop autosend 
  //honeywell.stopAutoSend();
  
  //DO OTHER STUFF
}
```

3. Starting and stopping of measurements is controlled by the following methods

```cpp
  //Somewhere in your code...
  
  //Fan will start spinning. It takes about 6 sec of fan spin in order of the measurement to be correct.
  //You may consider adding a delay after starting the measurement.
  honeywell.startMeasurement();
  
  //Here in between you may want to read the measurement. Please read below on how to do that.
  
  //Fan will stop spinning.
  honeywell.stopMeasurement();
```

4. Read the measurement by using `readMesurement` method. A long array is passed to the function, and it will be modified. The values of PM25 and P10 are saved in the array and they are in index 0 and 1 respectively.

```cpp
//Declare a long array of length two
long measurement[2];

//Somewhere between honeywell.startMeasurement(); and honeywell.stopMeasurement();
//measurement will have the values PM25 -> index 0, PM10 -> index 1
honeywell.readMeasurement(measurement);
```

5. All methods return a `bool` to indicate whether the action was successful!

6. You may check [this gist](https://gist.github.com/jcelmeta14/85d15d033db25961a66acad21d6ccbe5) for a simple example how to use this library with Arduino.
