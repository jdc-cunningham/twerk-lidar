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
#include "Orientation.h"

float levelGravityVal;

void setup()
{
  Serial.begin(115200);
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setAndCenterServos();
  setupEspSerial();
  setupTof();
  setupImu();

  Serial.println("place robot on floor");
  delay(3000);

  if (imu.Read())
  {
    levelGravityVal = imu.accel_z_mps2();
  }

  // getMagnetometerOffset();
  // delay(3000);

  // float levelGravityVal;
  // float angledGravityVal;

  // if (imu.Read())
  // {
  //   Serial.println("rest robot on floor");
  //   delay(5000);
  //   levelGravityVal = imu.accel_z_mps2() * 3.28084;
  //   Serial.println(levelGravityVal);
  //   delay(5000);
    
  // }

  // if (imu.Read())
  // {
  //   Serial.println("rotate robot");
  //   delay(5000);
  //   angledGravityVal = imu.accel_z_mps2() * 3.28084;
  //   Serial.println(angledGravityVal);
  //   Serial.println("angle is");
  //   float angle = acos(angledGravityVal/levelGravityVal) * 57.2958; // to degree
  //   Serial.println(angle);
  // }

  // std::vector<std::vector <float>> imuNed = getNed();

  // Serial.println(imuNed[0][0]);
  // Serial.println(imuNed[0][1]);
  // Serial.println(imuNed[0][2]);

  // Serial.println(imuNed[1][0]);
  // Serial.println(imuNed[1][1]);
  // Serial.println(imuNed[1][2]);

  // Serial.println(imuNed[2][0]);
  // Serial.println(imuNed[2][1]);
  // Serial.println(imuNed[2][2]);

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

  // delay(15000);
  // sampleDepth = true;
  // sampleGyroX = true;
  // tiltDown();
  // dumpData();
  // delay(15000);
  // tiltCenterFromDown();
  // dumpData();
  // sampleDepth = false;
  // sampleGyroX = false;

  // performPitchTest();
  // tiltUp();
  // moveFrontRightLegUp();
  // moveBackLeftLegUp();
  // moveBackLeftLegDown();
}

void loop()
{
  if (imu.Read())
  {
    float currentGravityVal = imu.accel_z_mps2();
    Serial.println(currentGravityVal/levelGravityVal);
    Serial.println(acos(currentGravityVal/levelGravityVal) * 57.2958);
  }

  delay(100);

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