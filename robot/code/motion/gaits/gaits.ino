/**
 * top view of servos
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
  // Serial.println(getBatteryVoltage());
  setAndCenterServos();
  delay(5000);
  // turnLeft();
  // moveForward();
  // moveForward2();
  // delay(1000);
  // level();
}

void loop()
{
  // moveForward();
  // turnLeft();
  // Serial.println(getBatteryVoltage());
  // delay(500);
}