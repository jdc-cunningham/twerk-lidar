/**
 * top view of robot and servo names
 * FLO = front-left-outer
 * 
 *    FLO                          FRO
 *         FLM                 FRM
 *              FLI  TOF  FRI
 *                    ^
 *                    y
 * 
 *                   (z)  x >
 *                   IMU
 *
 * 
 *
 *              BLI       BRI
 *         BLM                 BRM
 *    BLO                           BRO
 */

#include "BlueLed.h"
#include "ToFSensor.h"
#include "IMU.h"
#include "ServoMovements.h"
#include "Misc.h"
#include "EspSerial.h"
#include "WorldNavigation.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setAndCenterServos();
  setupEspSerial();
  setupTof();
  setupImu();
  // getMagnetometerOffset();
  // delay(3000);

  // turnLeft();
  // performScan();
  // Serial.print(sampleSetPerSweep[0][0]);
  // Serial.begin(115200);
  // Serial.println(sensor.readRangeSingleMillimeters() * 0.0393701);

  // delay(15000);
  // sampleDepth = true;
  // sampleGyroX = true;
  // tiltDown();
  // sampleDepth = false;
  // sampleGyroX = false;
  // dumpData();
  // delay(15000);
  // performSweep();
  // dumpData();
  // performScan();

  // performPitchTest();
  // tiltUp();
  // moveFrontRightLegUp();
  // moveBackLeftLegUp();
  // moveBackLeftLegDown();
}

void loop()
{
  delay(5000);
  tiltDown();
  delay(5000);
  tiltCenterFromDown();

  // moveForward3();
  // performScan();
  // turnLeft();

  // if (imu.Read())
  // {
  //   Serial.println(radianToDegree(imu.gyro_z_radps()));
    // Serial5.print(sensor.readRangeSingleMillimeters() * 0.0393701);
    // String espMsg = getEspSerialMsg();

    // if (espMsg.length() > 0)
    // {
    //   String sensorAccelSample = String(imu.accel_x_mps2()) + "," + String(imu.accel_y_mps2()) + "," + String(imu.accel_z_mps2()) + ",";
    //   String sensorGyroSample = String(imu.gyro_x_radps()) + "," + String(imu.gyro_y_radps()) + "," + String(imu.gyro_z_radps()) + ",";
    //   String sensorMagSample = String(imu.mag_x_ut()) + "," + String(imu.mag_y_ut()) + "," + String(imu.mag_z_ut());

    //   ESPSERIAL.print(sensorAccelSample);
    //   ESPSERIAL.print(sensorGyroSample);
    //   ESPSERIAL.print(sensorMagSample);
    // }
  // }

  // performScan();
  // performSweep();

  // delay(1000);
}