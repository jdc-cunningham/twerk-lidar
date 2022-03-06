#include <Wire.h>
#include <VL53L0X.h>

// https://github.com/pololu/vl53l0x-arduino/blob/master/examples/Single/Single.ino

VL53L0X sensor;

void setupTof() {
  Wire.begin();
  sensor.setTimeout(500);

  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
}


