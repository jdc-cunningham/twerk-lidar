#include "MovementHelpers.h"

void centerAllLegs()
{
  frontRightInnerJoint.servo.write(frontRightInnerJoint.startPos);
  frontRightMiddleJoint.servo.write(frontRightMiddleJoint.startPos);
  frontRightOuterJoint.servo.write(frontRightOuterJoint.startPos);
  backRightInnerJoint.servo.write(backRightInnerJoint.startPos);
  backRightMiddleJoint.servo.write(backRightMiddleJoint.startPos);
  backRightOuterJoint.servo.write(backRightOuterJoint.startPos);
  frontLeftInnerJoint.servo.write(frontLeftInnerJoint.startPos);
  frontLeftMiddleJoint.servo.write(frontLeftMiddleJoint.startPos);
  frontLeftOuterJoint.servo.write(frontLeftOuterJoint.startPos);
  backLeftInnerJoint.servo.write(backLeftInnerJoint.startPos);
  backLeftMiddleJoint.servo.write(backLeftMiddleJoint.startPos);
  backLeftOuterJoint.servo.write(backLeftOuterJoint.startPos);
}

/**
 * these are attached with regard to the board's design
 * where the right half of the robot pins are on the right side, etc...
 * also it goes inner out
 */
void setAndCenterServos()
{
  frontRightInnerJoint.servo.attach(0);
  frontRightMiddleJoint.servo.attach(1);
  frontRightOuterJoint.servo.attach(2);
  backRightInnerJoint.servo.attach(3);
  backRightMiddleJoint.servo.attach(4);
  backRightOuterJoint.servo.attach(5);
  frontLeftInnerJoint.servo.attach(6);
  frontLeftMiddleJoint.servo.attach(7);
  frontLeftOuterJoint.servo.attach(8);
  backLeftInnerJoint.servo.attach(9);
  backLeftMiddleJoint.servo.attach(10);
  backLeftOuterJoint.servo.attach(11);

  // neutral stance
  centerAllLegs();
}

/**
 * @brief this function is a wrapper around Joint.write() however
 * it checks against the servo's min/max throws based on robot geometry
 * the min/max values are determined upon assembling the robot/calibrated
 * manually since the servos have not feedback
 * 
 * @param servo 
 * @param deg 
 */
void safeServoWrite(int servoPin, int deg)
{
  joint jointToMove = getJointByPin(servoPin);
  int servoMin = jointToMove.minPos;
  int servoMax = jointToMove.maxPos;

  if (deg <= servoMax && deg >= servoMin)
  {
    jointToMove.servo.write(deg);
  }
}

/**
 * @brief this function is used to move the servos by a web interface
 * espMsg pattern msc_servoInt__deg
 */
void manual_move_servo(String espMsg)
{
  int degStart = espMsg.indexOf("__");
  int servoPin = espMsg.substring(4, degStart).toInt();
  int servoDeg = espMsg.substring(degStart + 2).toInt();
  safeServoWrite(servoPin, servoDeg);
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

void leftTurnPivot()
{
  int servoGroupArr[][3] = {
    {6, 30, 0},
    {9, 125, 95},
    {3, 80, 50},
    {0, 70, 100}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void leftTurnPivot2()
{
  int servoGroupArr[][3] = {
    {6, 0, 60}, // front left inner
    {9, 95, 65},
    {3, 50, 20},
    {0, 100, 70}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void leftTurnPivot3()
{
  int servoGroupArr[][3] = {
    {6, 60, 30}, // front left inner
    {9, 65, 125}, // back left inner
    {3, 20, 0}, // back right inner
    {0, 70, 40}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void ltp3ToNeutral()
{
  int servoGroupArr[][3] = {
    {3, 0, 80} // back right inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void ltp3ToNeutral2()
{
  int servoGroupArr[][3] = {
    {0, 40, 70} // front right inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void ltp3ToNeutral3()
{
  int servoGroupArr[][3] = {
    {9, 95, 125}, // back left inner
    {1, 60, 80}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
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

  // increment rotation
  robotHeading -= 58.8;

  // updateTelemetry("tl");
}

void turnRight()
{
  
  
}