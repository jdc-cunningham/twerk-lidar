/**
 * top view of robot and servo names
 * FLO = front-left-outer
 * 
 *    FLO                          FRO
 *         FLM                 FRM
 *              FLI  TOF  FRI
 * 
 *
 *                   IMU
 *
 *
 *              BLI       BRI
 *         BLM                 BRM
 *    BLO                           BRO
 */

#include "ToFSensor.h"
#include "ServoMovements.h"
#include "Misc.h"
#include "IMU.h"
#include "TeensySerial.h"
#include "ESP01.h"

void setup()
{
  setAndCenterServos();
  Serial.begin(115200);
  setupSerial5();
  // Serial.println(getBatteryVoltage());
  setupTof();
  setupImu();
  // Serial.println(sensor.readRangeSingleMillimeters() * 0.0393701);
  delay(3000);
  // turnLeft();
  // performScan();
  // Serial.print(sampleSetPerSweep[0][0]);
}

void loop()
{
  // moveForward3();
  // performScan();
  // turnLeft();
  if (imu.Read()) {
    // Serial5.print(sensor.readRangeSingleMillimeters() * 0.0393701);
    checkEspSerialMsg();

    String sensorAccelSample = String(imu.accel_x_mps2()) + "," + String(imu.accel_y_mps2()) + "," + String(imu.accel_z_mps2()) + ",";
    String sensorGyroSample = String(imu.gyro_x_radps()) + "," + String(imu.gyro_y_radps()) + "," + String(imu.gyro_z_radps()) + ",";
    String sensorMagSample = String(imu.mag_x_ut()) + "," + String(imu.mag_y_ut()) + "," + String(imu.mag_z_ut());

    Serial5.print(sensorAccelSample);
    Serial5.print(sensorGyroSample);
    Serial5.print(sensorMagSample);
  }

  delay(1000);
}