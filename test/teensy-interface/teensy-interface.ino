#include "mpu9250.h"
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
bfs::Mpu9250 imu(&Wire1, 0x68);

void setupEsp() {

}

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

float getTofSample() {
  sensor.startContinuous();
  float sample = sensor.readRangeContinuousMillimeters() * 0.0393701;
  sensor.stopContinuous();
  return sample;
}

void setupImu() {
  Serial.begin(115200);
  while(!Serial) {}
  Wire1.begin();
  Wire1.setClock(400000);
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

void checkEspSerialMsg() {
  if (Serial5.available()) {
    Serial.print(Serial5.readString());
  }
}

void setupSerial() {
  Serial5.begin(115200);
}

void setup() {
  setupSerial();
  setupImu();
  setupTof();
}

void loop() {
  if (imu.Read()) {
    Serial.print("imu z ");
    Serial.print(imu.accel_z_mps2());
    Serial.print("\t");
  }

  Serial.print("tof in ");
  Serial.print(sensor.readRangeSingleMillimeters() * 0.0393701);
  Serial.println("");
  checkEspSerialMsg();
  Serial5.print("yo");
  delay(1000);
}