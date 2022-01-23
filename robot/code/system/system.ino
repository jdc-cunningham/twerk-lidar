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

void setupSerial() {
  Serial5.begin(115200);
}

void setup()
{
  setupSerial();
  Serial.println(getBatteryVoltage());
  setupTof();
  Serial.println(sensor.readRangeSingleMillimeters() * 0.0393701);
  setAndCenterServos();
  delay(5000);
  // turnLeft();
  // performScan();
  // Serial.print(sampleSetPerSweep[0][0]);
}

void loop()
{
  // moveForward3();
  // performScan();
  // turnLeft();
}