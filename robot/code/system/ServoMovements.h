#include <Servo.h>
#include <map>
#include <vector>
#include <math.h>
#include "ServoMovementsBase.h"
#include "DiscreteServoMovements.h"

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
  // mf4MoveFrontRightLegDown();
  // mf4MoveFrontLeftLegUp();
  // mf4MoveFrontLeftLegForward();
  // mf4MoveFrontLeftLegDownFromUp();
  // mf4MoveFrontRightLegUpFromDown();

  // move front right leg forward
  mf4MoveFrontLeftLegDown();

  // int servoGroupArr6[][3] = {
  //   {1, 80, 40} // front right middle
  // };

  // moveServos(servoGroupArr6, 1, servoMotionDelay);

  // int servoGroupArr7[][3] = {
  //   {0, 65, 105} // front right inner
  // };

  // moveServos(servoGroupArr7, 1, servoMotionDelay);

  // int servoGroupArr8[][3] = {
  //   {1, 40, 80} // front right middle
  // };

  // moveServos(servoGroupArr8, 1, servoMotionDelay);

  // // frontLeftMiddleServo.write(95);
  // int servoGroupArr9[][3] = {
  //   {7, 75, 95} // front left middle
  // };

  // moveServos(servoGroupArr9, 1, servoMotionDelay);

  // // move all for forward
  // int servoGroupArr10[][3] = {
  //   {6, 30, 70},
  //   {0, 105, 65},
  //   {9, 95, 135},
  //   {3, 80, 40}
  // };

  // moveServos(servoGroupArr10, 4, servoMotionDelay);

  // // move back-right leg forwrard
  // int servoGroupArr11[][3] = {
  //   {4, 95, 115} // back right middle
  // };

  // moveServos(servoGroupArr11, 1, servoMotionDelay);

  // int servoGroupArr12[][3] = {
  //   {3, 40, 80} // back right inner
  // };

  // moveServos(servoGroupArr12, 1, servoMotionDelay);

  // int servoGroupArr13[][3] = {
  //   {4, 115, 95} // back right middle
  // };

  // moveServos(servoGroupArr13, 1, servoMotionDelay);

  // // // move back left leg forward
  // int servoGroupArr15[][3] = {
  //   {1, 80, 60} // front right middle
  // };

  // moveServos(servoGroupArr15, 1, servoMotionDelay);

  // int servoGroupArr16[][3] = {
  //   {9, 115, 95} // back left inner
  // };

  // moveServos(servoGroupArr16, 1, servoMotionDelay);

  // int servoGroupArr17[][3] = {
  //   {1, 60, 80} // front right middle
  // };

  // moveServos(servoGroupArr17, 1, servoMotionDelay);
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