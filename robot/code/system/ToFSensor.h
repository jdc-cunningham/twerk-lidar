#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

int sampleAngles[3] = {};
float sampleSetPerSweep[60][3] = {};

void setupTof() {
  Wire.begin();
  sensor.setTimeout(500);

  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();
}


