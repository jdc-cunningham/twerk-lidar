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

#include "Variables.h"
#include "BlueLed.h"
#include "ToFSensor.h"
#include "EspSerial.h"
#include "IMU.h"
#include "Misc.h"
#include "WorldNavigation.h"
#include "Orientation.h"
#include "Telemetry.h"
#include "ServoMovements.h"

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

  // updateTelemetry("mf");
  // moveForward5();
  // performSweep();


  // preSweepSwayForward(); // moves ToF sensor away from legs, 0.5" forward
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
  // turnLeft();
}

void loop()
{
  // poll is like a keep-alive, it bunches up due timing mismatch
  String espMsg = getEspSerialMsg().replace("poll", "");

  espMsg.replace("Hello Server!", "");

  if (espMsg)
  {
    Serial.println(espMsg);
    if (espMsg == "stop")
    {
      stopRobot = true;
    }

    clearEspSerial();
  }

  // moveForward5();
  // moveForward5();
  // moveForward5();
  // moveForward5();
  // moveForward5();
  // turnLeft();
  // turnLeft();

  // delay(1000);
}