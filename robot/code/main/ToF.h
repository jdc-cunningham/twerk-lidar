#include <Wire.h>
#include <VL53L0X.h>

// https://github.com/pololu/vl53l0x-arduino/blob/master/examples/Single/Single.ino

VL53L0X tofSensor;

#define HIGH_SPEED

void setupTof() {
  Wire.begin();
  tofSensor.setTimeout(500);

  if (!tofSensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  #if defined HIGH_SPEED
    tofSensor.setMeasurementTimingBudget(20000);
  #endif
}

float getTofDistance()
{
  float distSample = tofSensor.readRangeSingleMillimeters();
  float distSampleIn = (distSample * 0.0393701);
  return distSampleIn;
}