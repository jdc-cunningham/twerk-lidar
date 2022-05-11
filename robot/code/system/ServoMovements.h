#include "ServoMovementsBase.h"
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
 * @param {bool} scan - means no sampling/fast
 */
void sweep(int runCount, bool scan = false, String scanType = "")
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
    if (!scanType) dumpData();
  } else if (runCount == 2)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotCenterFromLeft();
    pivotRight();
    sampleDepth = false;
    sampleGyroZ = false;
    if (!scanType) dumpData();
  } else
  {
    if (scan)
    {
      sampleDepth = true;
      sampleGyroZ = true;
    }

    pivotCenterFromRight();
    pivotLeft();
    pivotCenterFromLeft();

    if (scan)
    {
      sampleDepth = false;
      sampleGyroZ = false;
      if (!scanType) dumpData();
    }
  }

  performObstacleCheck(scanType);
}

void performFullScan(bool addDelayBetweenSamples = false)
{
  tiltUp1();
  tiltUp2();
  delay(1000); // wait to stop moving
  sweep(1, true, "");
  // sweep(1, true, "u2"); // second param means no delay

  if (addDelayBetweenSamples)
  {
    delay(10000); // for manual serial dump copy paste into excel
  }

  tiltCenterFromUp2();
  delay(1000); // wait to stop moving
  sweep(2, true, "");
  // sweep(2, true, "u1");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltCenterFromUp1();
  delay(1000); // wait to stop moving
  sweep(3, true, "");
  // sweep(3, true, "m1");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltDown1();
  delay(1000); // wait to stop moving
  sweep(1, true, "");
  // sweep(1, true, "d1");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltDown2();
  delay(1000); // wait to stop moving
  sweep(2, true, "");
  // sweep(2, true, "d2");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltCenterFromDown2();
  tiltCenterFromDown1();
  sweep(3, false);
}

// based on visual observation of Regis Hsu 2017 spider bot
void moveForward5()
{
  mf5MoveFrontRightLegUp();
  mf5MoveFrontRightLegForward();
  mf5MoveFrontRightLegDownFromUp();

  // sampleYAccel = true;
  mf5PullForwardRight();
  sampleYAccel = false;

  mf5MoveBackLeftLegUp();
  mf5MoveBackLeftLegForward();
  mf5MoveBackLeftLegDownFromUp();

  mf5MoveFrontLeftLegUp();
  mf5MoveFrontLeftLegForward();
  mf5MoveFrontLeftLegDownFromUp();

  // sampleYAccel = true;
  mf5PullForwardLeft();
  sampleYAccel = false;

  mf5MoveBackRightLegUp();
  mf5MoveBackRightLegForward();
  mf5MoveBackRightLegDownFromUp();

  // updateTelemetry("mf");
}

// also based on Regis Hsu 2017 spider robot turn gait
void turnLeft()
{
  mf5MoveFrontRightLegUp();
  // sampleGyroZ = true;
  leftTurnPivot();
  sampleGyroZ = false;
  mf5MoveFrontRightLegDownFromUp();

  // mf5MoveFrontRightLegUp();
  mf5MoveFrontLeftLegUp();
  leftTurnPivot2();
  mf5MoveFrontLeftLegDownFromUp();

  mf5MoveBackLeftLegUp();
  // sampleGyroZ = true;
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

  // updateTelemetry("tl");
}