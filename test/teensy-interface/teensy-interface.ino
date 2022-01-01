
#include "mpu9250.h"
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
bfs::Mpu9250 imu(&Wire, 0x68);

void setupEsp() {

}

void setupTof() {
  sensor.setTimeout(500);

  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // sensor.startContinuous();
}

float getTofSample() {
  sensor.startContinuous();
  float sample = sensor.readRangeContinuousMillimeters() * 0.0393701;
  sensor.stopContinuous();
  return sample;
}

void setupImu() {
  /* Initialize and configure IMU */
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }
  /* Set the sample rate divider */
  if (!imu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }
}

void setupBus() {
  Wire.begin();
  // Wire.setClock(400000);
}

void setupTofSingle() {

  #if defined LONG_RANGE
    // lower the return signal rate limit (default is 0.25 MCPS)
    sensor.setSignalRateLimit(0.1);
    // increase laser pulse periods (defaults are 14 and 10 PCLKs)
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  #endif

  sensor.setMeasurementTimingBudget(200000);
}

void setup() {
  setupBus();
  // setupImu();
  setupTof();
  // setupTofSingle();
}

void loop() {
  // Serial.print("imu z");
  // Serial.print(imu.accel_z_mps2());
  // Serial.println("");
  Serial.print("tof in ");
  Serial.print(getTofSample());
  // Serial.print(sensor.readRangeSingleMillimeters() * 0.0393701);
  Serial.println("");
  delay(1000);
}