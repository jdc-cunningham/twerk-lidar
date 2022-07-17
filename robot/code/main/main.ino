#include "GlobalVariables.h"
#include "Led.h"
#include "TFmini-s.h"
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
#include "Comms.h"

void setup_robot()
{
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setAndCenterServos();
  setupEspSerial();
  setupTof(); // this is abstracted to use either VL or TF
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

  // allow time to position robot
  delay(10000);
}

void main_nav_process()
{
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
    plotCube(12, robotHeading, robotDistance < 4 ? 4 : robotDistance);
  }

  if (forwardGaitCount == 0)
  {
    robotDistance = 0;
    turnLeft();
  } else
  {
    for (int i = 0; i < forwardGaitCount; i++)
    {
      robotDistance += forwardGaitCount * 2;
      moveForward5();
    }
  }
}

void loop()
{
  webMessaging(); // internal delay + 250ms
  // main_nav_process(); // will call this from web interface
  isUpsideDown();
}