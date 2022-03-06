#include <Wire.h>
#include <VL53L0X.h>

// https://github.com/pololu/vl53l0x-arduino/blob/master/examples/Single/Single.ino
// #define HIGH_SPEED
// #define LONG_RANGE

VL53L0X sensor;

void setupTof() {
  Wire.begin();
  sensor.setTimeout(500);

  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // #if defined HIGH_SPEED
  //   sensor.setMeasurementTimingBudget(20000);
  // #endif

  // #if defined LONG_RANGE
  //   // lower the return signal rate limit (default is 0.25 MCPS)
  //   sensor.setSignalRateLimit(0.1);
  //   // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  //   sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  // #endif
}


