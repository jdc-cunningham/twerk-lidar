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

#include "ServoMovements.h"
#include "Misc.h"

void setup()
{
  Serial.println(getBatteryVoltage());
  setAndCenterServos();
  delay(5000);
  // performScan();
  // moveForward();
}

void loop()
{

}