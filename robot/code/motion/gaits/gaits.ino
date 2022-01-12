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

bool motionInProgress = false;
int servoMotionDelay = 6; // ms

Servo getServoByPin(int digitalPin)
{
  if (digitalPin == 0) // ugh this sucks
  {
    return frontRightInnerServo;
  } else if (digitalPin == 1)
  {
    return frontRightMiddleServo;
  } else if (digitalPin == 2)
  {
    return frontRightOuterServo;
  } else if (digitalPin == 3)
  {
    return backRightInnerServo;
  } else if (digitalPin == 4)
  {
    return backRightMiddleServo;
  } else if (digitalPin == 5)
  {
    return backRightOuterServo;
  } else if (digitalPin == 6)
  {
    return frontLeftInnerServo;
  } else if (digitalPin == 7)
  {
    return frontLeftMiddleServo;
  } else if (digitalPin == 8)
  {
    return frontLeftOuterServo;
  } else if (digitalPin == 9)
  {
    return backLeftInnerServo;
  } else if (digitalPin == 10)
  {
    return backLeftMiddleServo;
  } else {
    return backLeftOuterServo;
  }
}

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
  // frontRightInnerServo.write(90); // base throw in either direction is 35 deg
  // frontRightMiddleServo.write(90);
  // frontRightOuterServo.write(90);
  // backRightInnerServo.write(90);
  // backRightMiddleServo.write(90);
  // backRightOuterServo.write(90);
  // frontLeftInnerServo.write(80);
  // frontLeftMiddleServo.write(90);
  // frontLeftOuterServo.write(90);
  // backLeftInnerServo.write(90);
  // backLeftMiddleServo.write(90);
  // backLeftOuterServo.write(90);

  // neutral stance
  frontRightInnerServo.write(105); // +40
  frontRightMiddleServo.write(80); // -10
  frontRightOuterServo.write(95); // +5
  backRightInnerServo.write(50); // -30
  backRightMiddleServo.write(95); // +10
  backRightOuterServo.write(75); // -15
  frontLeftInnerServo.write(40); // -30
  frontLeftMiddleServo.write(100); // +10
  frontLeftOuterServo.write(85); // -5
  backLeftInnerServo.write(130); // +30
  backLeftMiddleServo.write(80); // -10
  backLeftOuterServo.write(95); // +5
}

// ex call
// servoGroupArr[][3] = {
//   {#, #, #}
//   {#, #, #}
//   {#, #, #}
//   {#, #, #}    
// }

/**
 * This function moves servos together at the same speed
 * there is a "bias" where the shortest motion will end first
 * @param {int} - array of arrays with the following: servo enum, start pos, end pos
 * @param {int} - array length
 * @param {int} - duration of motion in ms
 */
void moveServos(int servoGroupArr[][3], int servoGroupArrLen, int motionDuration) {
  /**
   * loop through servos, find largest range between start/end pos
   * there is no error checking, I find coding in Arduino to be cumbersome */
  motionInProgress = true;
  int largestServoRange = 0;

  for (int servoGroupIndex = 0; servoGroupIndex < servoGroupArrLen; servoGroupIndex++) {
    int range = 0;
    if (servoGroupArr[servoGroupIndex][1] < servoGroupArr[servoGroupIndex][2]) {
      // increase
      range = servoGroupArr[servoGroupIndex][2] - servoGroupArr[servoGroupIndex][1];
      if (range > largestServoRange) {
        largestServoRange = range;
      }
    } else {
      // decrease
      range = servoGroupArr[servoGroupIndex][1] - servoGroupArr[servoGroupIndex][2];
      if (range > largestServoRange) {
        largestServoRange = range;
      }
    }
  }

  /* do the motion on the servos going by largest range
   * this will update all the servo positions at the same rate
   * but some will finish earlier than others if the motion range is not the same */
  for (int pos = 0; pos < largestServoRange; pos++) {
    for(int servoGroupIndex = 0; servoGroupIndex < servoGroupArrLen; servoGroupIndex++) {
      if (servoGroupArr[servoGroupIndex][1] < servoGroupArr[servoGroupIndex][2]) {
        // increase
        if (servoGroupArr[servoGroupIndex][1] + pos < servoGroupArr[servoGroupIndex][2]) {
          getServoByPin(servoGroupArr[servoGroupIndex][0]).write(servoGroupArr[servoGroupIndex][1] + pos);
        }
      } else {
        // decrease
        if (servoGroupArr[servoGroupIndex][1] - pos > servoGroupArr[servoGroupIndex][2]) {
          getServoByPin(servoGroupArr[servoGroupIndex][0]).write(servoGroupArr[servoGroupIndex][1] - pos);
        }
      }
    }
    delay(motionDuration);
  }

  motionInProgress = false;
}

void moveForward()
{
  // move front-right leg up
  int servoGroupArr[][3] = {
    // {4, 100, 75},
    {1, 80, 40},
    // {0, 150, 170}
  };

  moveServos(servoGroupArr, 1, 6);

  // move back-left leg forward
  int servoGroupArr2[][3] = { // lol
    {9, 130, 100},
    // {4, 75, 100},

  };

  moveServos(servoGroupArr2, 1, 6);

  // move front-right leg down
   int servoGroupArr3[][3] = {
    // {4, 100, 75},
    {1, 40, 80},
    // {0, 150, 170}
  };

  moveServos(servoGroupArr3, 1, 6);

  // move front-left leg up
  int servoGroupArr4[][3] = {
    // {4, 100, 75},
    {7, 100, 140},
    // {0, 150, 170}
  };

  moveServos(servoGroupArr4, 1, 6);

  // move back-right leg forward
  int servoGroupArr5[][3] = {
    // {4, 100, 75},
    {3, 50, 80},
    // {0, 150, 170}
  };

  moveServos(servoGroupArr5, 1, 6);

  // move front-left leg down
  int servoGroupArr6[][3] = {
    // {4, 100, 75},
    {7, 140, 100},
    // {0, 150, 170}
  };

  moveServos(servoGroupArr6, 1, 6);

  // move back-left leg up
    int servoGroupArr7[][3] = {
    {10, 80, 40}
  };

  moveServos(servoGroupArr7, 1, 6);

  // move front-right leg forward
  int servoGroupArr8[][3] = {
    {0, 105, 135},
  };

  moveServos(servoGroupArr8, 1, 6);

  // move back-left leg down
  int servoGroupArr9[][3] = {
    {10, 40, 80}
  };

  moveServos(servoGroupArr9, 1, 6);

  // move back-right leg up
  int servoGroupArr10[][3] = {
    {4, 95, 125}
  };

  moveServos(servoGroupArr10, 1, 6);

  // move front-left leg forward
  int servoGroupArr11[][3] = {
    {6, 40, 20}
  };

  moveServos(servoGroupArr11, 1, 6);

  // move back-right leg down
  int servoGroupArr12[][3] = {
    {4, 125, 95}
  };

  moveServos(servoGroupArr12, 1, 6);

  // move all four legs back
  int servoGroupArr13[][3] = {
    {6, 20, 40},
    {0, 135, 105},
    {9, 100, 130},
    {3, 80, 50}
  };

  moveServos(servoGroupArr13, 4, 6);
  
}

void level()
{

}

void setup()
{
  setAndCenterServos();
  delay(5000);
  // moveForward();
  // delay(1000);
  // level();
}

void loop()
{
  // moveForward();
}