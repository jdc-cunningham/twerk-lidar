#include "GlobalVariables.h"
#include "Led.h"
#include "ToF.h"
#include "ESPSerial.h"
#include "IMU.h"
#include "Power.h"
#include "WorldNavigation.h"
#include "Orientation.h"
#include "Telemetry.h"
#include "Movement.h"
#include "Misc.h"
#include "ObstacleDetection.h"
#include "Scan.h"

void setup_robot()
{
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
}

void setup()
{
  Serial.begin(115200);

  setup_robot();

  // performFullScan(false);

  // allow time to position robot
  // delay(10000);

  // performFullScan(true);
  // leftTurnPivot();
  // frontRightLegUp();
  // switchToRightDefaultStance();
}

// void main_nav_process()
// {
//   // moveForward5();
//   // turnLeft();
//   performFullScan(false);

//   // check close
//   // means something is within 4 inches or bad ToF measurements
//   // the ToF sensor corrects erroneous measurements by outputting full distance for anything
//   // less than 3", this seems to happen more often when scanning open space
//   // also if measurements are under 4" it's considered a need to turn
//   if (forwardGaitCount < 3 || posErrVals.size() > 10)
//   {
//     forwardGaitCount = 0;
//   }

//   if (forwardGaitCount == 0)
//   {
//     plotCube(12, robotHeading, robotDistance < 4 ? 4 : robotDistance);
//   }

//   if (forwardGaitCount == 0)
//   {
//     robotDistance = 0;
//     turnLeft();
//   } else
//   {
//     for (int i = 0; i < forwardGaitCount; i++)
//     {
//       robotDistance += forwardGaitCount * 2;
//       moveForward5();
//     }
//   }
// }

void webMessaging()
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

    // manual web-based servo control
    if (espMsg.indexOf("msc_") > -1)
    {
      manualMoveServo(espMsg);
    }

    if (espMsg.indexOf("tel_") > -1)
    {
      checkTelemetry(espMsg);
    }

    clearEspSerial();
  }

  delay(1000); // delay for sync
}

void loop()
{
  // moveForward5();
  // delay(10000);

  // delay(10000);

  webMessaging();

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