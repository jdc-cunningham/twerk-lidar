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
 * @brief this function is used to move the servos by a web interface
 * espMsg pattern msc_servoInt__deg
 */
void manualMoveServo(String espMsg)
{
  int degStart = espMsg.indexOf("__");
  int servoPin = espMsg.substring(4, degStart).toInt();
  int servoDeg = espMsg.substring(degStart + 2).toInt();
  safeServoWrite(servoPin, servoDeg);
}

// based on visual observation of Regis Hsu 2017 spider bot
void moveForward5()
{
  // these motions could specify degree, dir and use global to know where servo is
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

  // increment rotation
  robotHeading -= 58.8;

  // updateTelemetry("tl");
}

void turnRight()
{
  
  
}