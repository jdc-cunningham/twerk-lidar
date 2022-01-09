/**
 * top view of servos
 * 
 *    FLO                      FRO
 *         FLM            FRM
 *              FLI  FRI
 * 
 * 
 *              BLI  BRI
 *         BLM            BRM
 *    BLO                      BLO
 */

#include <Servo.h>

Servo frontRightOuterServo;
Servo frontRightMiddleServo;
Servo frontRightInnerServo;
Servo backRightOuterServo;
Servo backRightMiddleServo;
Servo backRightInnerServo;
Servo frontLeftOuterServo;
Servo frontLeftMiddleServo;
Servo frontLeftInnerServo;
Servo backLeftOuterServo;
Servo backLeftMiddleServo;
Servo backLeftInnerServo;

/**
 * these are attached with regard to the board's design
 * where the right half of the robot pins are on the right side, etc...
 * also it goes inner out
 */
void setAndCenterServos()
{
  frontRightInnerServo.attach(0);
  frontRightMiddleServo.attach(1);
  frontRightOuterServo.attach(2);
  backRightInnerServo.attach(3);
  backRightMiddleServo.attach(4);
  backRightOuterServo.attach(5);
  frontLeftInnerServo.attach(6);
  frontLeftMiddleServo.attach(7);
  frontLeftOuterServo.attach(8);
  backLeftInnerServo.attach(9);
  backLeftMiddleServo.attach(10);
  backLeftOuterServo.attach(11);

  // convention is 0-90 clockwise, 90+ is counter clockwise

  // centered as in ]-[ shape vs. x
  frontRightInnerServo.write(90); // base throw in either direction is 35 deg
  frontRightMiddleServo.write(90);
  frontRightOuterServo.write(90);
  backRightInnerServo.write(90);
  backRightMiddleServo.write(90);
  backRightOuterServo.write(90);
  frontLeftInnerServo.write(80);
  frontLeftMiddleServo.write(90);
  frontLeftOuterServo.write(90);
  backLeftInnerServo.write(90);
  backLeftMiddleServo.write(90);
  backLeftOuterServo.write(90);
}

void setup()
{
  setAndCenterServos();
}

void loop()
{

}