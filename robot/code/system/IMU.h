#include "mpu9250.h"

bfs::Mpu9250 imu(&Wire1, 0x68);

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