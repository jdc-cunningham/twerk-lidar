/**
 * top view of robot and servo names
 * FLO = front-left-outer
 * 
 *    FLO                          FRO
 *         FLM                 FRM
 *              FLI  TOF  FRI
 * 
 *                    ^
 *                    y
 * 
 *                   (z)   x >
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

int forwardCounter = 0;

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

  // allow time to position robot
  delay(10000);

  // performFullScan(true);
}

void loop()
{
  // moveForward5();
  // turnLeft();
  performFullScan(false);

  // check close
  // means something is within 4 inches or bad ToF measurements
  // the ToF sensor corrects erroneous measurements by outputting full distance for anything
  // less than 3", this seems to happen more often when scanning open space
  // also if measurements are under 4" it's considered a need to turn
  if (forwardGaitCount < 3 || posErrVals.size() > 10)
  {
    forwardGaitCount = 0;
  }

  if (forwardGaitCount == 0)
  {
    plotCube(12, robotHeading, 4); // 4 is min distance away from a wall to turn
  } else
  {
    plotCube(12, robotHeading, (forwardGaitCount * 2) + 4);
  }

  if (forwardGaitCount == 0)
  {
    turnLeft();
  } else
  {
    for (int i = 0; i < forwardGaitCount; i++)
    {
      moveForward5();
    }
  }

  // moveForward5();
  // delay(10000);

  // poll is like a keep-alive, it bunches up due timing mismatch
  String espMsg = getEspSerialMsg().replace("poll", "");
  espMsg.replace("Hello Server!", "");

  // delay(10000);

  // if (espMsg)
  // {
  //   Serial.println(espMsg);
  //   if (espMsg == "stop")
  //   {
  //     stopRobot = true;
  //   }

  //   clearEspSerial();
  // }

  // if (forwardCounter < 5)
  // {
  //   forwardCounter += 1;
  //   moveForward5();
  // } else
  // {
  //   forwardCounter = 0;
  //   turnLeft();
  // }

  // delay(1000);
}