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

void setup()
{
  Serial.begin(115200);
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setAndCenterServos();
  setupEspSerial();
  setupTof();
  setupImu();

  // indicates setup is done
  blueLedOn();
  delay(500);
  blueLedOff();

  delay(5000);
  // moveForward5();
  // performSweep();

  preSweepSwayForward(); // moves ToF sensor away from legs, 0.5" forward
  // performFullScan();
  // postSweepSwayForward(); // return

  // turnLeft();
  // turnLeft();
  // dumpData();
  // mf5MoveFrontRightLegUp();

  // preSweepSwayForward();

  // {6, 40, 50},
  // {0, 65, 55},
  // {9, 125, 135},
  // {3, 80, 70}

  // sweep(1);
}

void loop()
{
  // moveForward5();
  // moveForward5();
  // moveForward5();
  // moveForward5();
  // moveForward5();
  // turnLeft();
  // turnLeft();
}