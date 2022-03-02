#include <Servo.h>
#include <map>
#include <vector>
#include <math.h>
#include "ServoMovementsBase.h"
#include "DiscreteServoMovements.h"
#include "DiscreteServoMovements2.h"

void dumpData()
{
  Serial.println(gyroVals.size());

  // https://stackoverflow.com/a/14070977/2710227
  // sucks but easier to copy-paste into excel
  Serial.println("s");
  for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
  {
    Serial.println(it->first);
  }

  for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
  {
    Serial.println(it->second);
  }

  Serial.println("g");
  for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
  {
    Serial.println(it->first);
  }

  for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
  {
    Serial.println(it->second);
  }

  Serial.println("d");
  for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
  {
    Serial.println(it->first);
  }

  for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
  {
    Serial.println(it->second);
  }

  gyroVals = {};
  servoPosVals = {};
  depthVals = {};
}

/**
 * @brief runCount is referring to which sweep is running
 * there are three: top, middle, bottom
 * the count determines where the robot is pointing (left/right)
 * and this is important to not jump positions and not scan the same place
 * if you were to return to the middle everytime
 * 
 * @param {int} runCount 
 * @param {bool} noScan - means no sampling/fast
 */
void sweep(int runCount, bool noScan = false)
{
  if (runCount == 1)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotRight();
    pivotCenterFromRight();
    pivotLeft();
    sampleDepth = false;
    sampleGyroZ = false;
    dumpData();
  } else if (runCount == 2)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotCenterFromLeft();
    pivotRight();
    sampleDepth = false;
    sampleGyroZ = false;
    dumpData();
  } else
  {
    if (!noScan)
    {
      sampleDepth = true;
      sampleGyroZ = true;
    }

    pivotCenterFromRight();
    pivotLeft();
    pivotCenterFromLeft();

    if (!noScan)
    {
      sampleDepth = false;
      sampleGyroZ = false;
      dumpData();
    }
  }
}

void performSweep()
{
  sweep(1);
  // sweep(2);
  // sweep(3);
}

void performFullScan()
{
  // tiltUp1();
  // tiltUp2();
  sweep(1);
  // delay(10000);
  // tiltCenterFromUp2();
  // sweep(2);
  // delay(10000);
  // tiltCenterFromUp1();
  // sweep(3);
  // delay(10000);
  // tiltDown1();
  // sweep(1);
  // delay(10000);
  // tiltDown2();
  // sweep(2);
  // delay(10000);
  // tiltCenterFromDown2();
  // tiltCenterFromDown1();
  sweep(3, true);
}

void moveForward4()
{
  // move front left leg forward
  mf4MoveFrontRightLegDown();
  mf4MoveFrontLeftLegUp();
  mf4MoveFrontLeftLegForward();
  mf4MoveFrontLeftLegDownFromUp();
  mf4MoveFrontRightLegUpFromDown();

  // move front right leg forward
  mf4MoveFrontLeftLegDown();
  mf4MoveFrontRightLegUp();
  mf4MoveFrontRightLegForward();
  mf4MoveFrontRightLegDownFromUp();
  mf4MoveFrontLeftLegUpFromDown();

  mf4MoveAllForward();

  // move back-right leg forwrard
  mf4MoveBackRightLegUp();
  mf4MoveBackRightLegForward();
  mf4MoveBackRightLegDownFromUp();

  // move back left leg forward
  mf4MoveFrontRightLegUpOuterFlipped();
  mf4MoveBackLeftLegUp();
  mf4MoveBackLeftLegForward();
  mf4MoveBackLeftLegDownFromUp();
  mf4MoveFrontRightLegDownFromUpOuterFlipped();
}

void moveForward3()
{
  moveFrontRightLegUp();
  moveFrontRightLegForward();
  moveFrontRightLegDown();
  moveFrontLeftLegUp();
  moveFrontLeftLegForward();
  moveFrontLeftLegDown();
  pullForward();
  moveBackLeftLegUp();
  moveBackLeftLegForward();
  moveBackLeftLegDown();
  moveBackRightLegUp();
  moveBackRightLegForward();
  moveBackRightLegDown();
}

void moveForward5()
{
  mf5MoveFrontRightLegUp();
  mf5MoveFrontRightLegForward();
  mf5MoveFrontRightLegDownFromUp();

  mf5PullForwardRight();

  // mf5MoveFrontRightLegUpHalf();
  mf5MoveBackLeftLegUp();
  mf5MoveBackLeftLegForward();
  mf5MoveBackLeftLegDownFromUp();
  // mf5MoveFrontRightLegDownFromUpHalf();

  mf5MoveFrontLeftLegUp();
  mf5MoveFrontLeftLegForward();
  mf5MoveFrontLeftLegDownFromUp();

  mf5PullForwardLeft();

  // mf5MoveFrontLeftLegUpHalf();
  mf5MoveBackRightLegUp();
  mf5MoveBackRightLegForward();
  mf5MoveBackRightLegDownFromUp();
  // mf5MoveFrontLeftLegDownFromUpHalf();
}