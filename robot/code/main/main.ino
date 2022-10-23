#include "GlobalVariables.h"
#include "Util.h"
#include "Led.h"
#include "ToF.h"
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
#include "Navigate.h"

void setup_robot()
{
  setAndCenterServos();
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setupEspSerial();
  setupTof();
  setupTFminiS();
  setupImu();

  // indicates setup is done
  blueLedOn();
  delay(500);
  blueLedOff();
}

void setup()
{
  int ledPin = 13; // turn this off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  setup_robot();

  // allow time to position robot
  delay(10000);
  // performFullScan(false);
  // navigate();
  // turnLeft();

  // moveForward5();

  // dumpImuData();



  // for (int i = 0; i < 5; i++)
  // {
  //   moveForward5();
  // }
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
  // navigate();
  // delay(5000);
  // performFullScan(false);
  // webMessaging(); // internal delay + 250ms
  // main_nav_process(); // will call this from web interface
  // isUpsideDown();
  // Serial.println(getTFminiSDistance());
  // moveForward5();
}