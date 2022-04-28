#include "ServoMovementsBase.h"
#include "DiscreteServoMovements.h"
#include "DiscreteServoMovements2.h"
#include "ObstacleDetection1.h"

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
void sweep(int runCount, bool noScan = false, String scanType = "")
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

  // do obstacle detection check
  if (scanType == "d1")
  {
    forwardGaitCount = parseScanData(depthVals, "d1");
  }

  if (scanType == "d2")
  {
    forwardGaitCount += parseScanData(depthVals, "d2");
  }

  // repeated code
  if (scanType == "m1")
  {
    int sampleForwardGaitCount = parseScanData(depthVals, "m1");

    if (sampleForwardGaitCount < 5)
    {
      forwardGaitCount = sampleForwardGaitCount;
    }
  }

  if (scanType == "u1")
  {
    int sampleForwardGaitCount = parseScanData(depthVals, "u1");

    if (sampleForwardGaitCount < 5)
    {
      forwardGaitCount = sampleForwardGaitCount;
    }
  }

  if (scanType == "u2")
  {
    int sampleForwardGaitCount = parseScanData(depthVals, "u1");

    if (sampleForwardGaitCount < 5)
    {
      forwardGaitCount = sampleForwardGaitCount;
    }
  }
}

void performSweep()
{
  sweep(1);
  delay(1000);
  sweep(2);
  delay(1000);
  sweep(3);
}

void performFullScan(bool sampling = false)
{
  tiltUp1();
  tiltUp2();
  delay(1000); // wait to stop moving
  sweep(1, false, "up2"); // second param means no delay

  if (sampling)
  {
    delay(10000); // for manual serial dump copy paste into excel
  }

  tiltCenterFromUp2();
  delay(1000); // wait to stop moving
  sweep(2, false, "up1");

  if (sampling)
  {
    delay(10000);
  }

  tiltCenterFromUp1();
  delay(1000); // wait to stop moving
  sweep(3, false, "m1");

  if (sampling)
  {
    delay(10000);
  }

  tiltDown1();
  delay(1000); // wait to stop moving
  sweep(1, false, "d1");

  if (sampling)
  {
    delay(10000);
  }

  tiltDown2();
  delay(1000); // wait to stop moving
  sweep(2, false, "d2");

  if (sampling)
  {
    delay(10000);
  }

  tiltCenterFromDown2();
  tiltCenterFromDown1();
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

// based on visual observation of Regis Hsu 2017 spider bot
void moveForward5()
{
  mf5MoveFrontRightLegUp();
  mf5MoveFrontRightLegForward();
  mf5MoveFrontRightLegDownFromUp();

  sampleYAccel = true;
  mf5PullForwardRight();
  sampleYAccel = false;

  mf5MoveBackLeftLegUp();
  mf5MoveBackLeftLegForward();
  mf5MoveBackLeftLegDownFromUp();

  mf5MoveFrontLeftLegUp();
  mf5MoveFrontLeftLegForward();
  mf5MoveFrontLeftLegDownFromUp();

  sampleYAccel = true;
  mf5PullForwardLeft();
  sampleYAccel = false;

  mf5MoveBackRightLegUp();
  mf5MoveBackRightLegForward();
  mf5MoveBackRightLegDownFromUp();

  updateTelemetry("mf");
}

// also inspired by Regis Hsu 2017 spider robot turn gait
void turnLeft()
{
  mf5MoveFrontRightLegUp();
  sampleGyroZ = true;
  leftTurnPivot();
  sampleGyroZ = false;
  mf5MoveFrontRightLegDownFromUp();

  // mf5MoveFrontRightLegUp();
  mf5MoveFrontLeftLegUp();
  leftTurnPivot2();
  mf5MoveFrontLeftLegDownFromUp();

  mf5MoveBackLeftLegUp();
  sampleGyroZ = true;
  leftTurnPivot3();
  sampleGyroZ = false;
  mf5MoveBackLeftLegDownFromUp();

  // at 45 deg here
  // rest below returns to neutral

  mf5MoveBackRightLegUp();
  ltp3ToNeutral();
  mf5MoveBackRightLegDownFromUp();

  mf5MoveFrontRightLegUp();
  ltp3ToNeutral2();
  mf5MoveFrontRightLegDownFromUp();

  updateTelemetry("tl");
}