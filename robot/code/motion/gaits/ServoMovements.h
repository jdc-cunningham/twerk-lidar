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
int servoMotionDelay = 8; // ms
int stepDelay = 0; // ms usually a second or more

/**
 * @brief Get the Servo By Pin object
 * 
 * @param digitalPin 
 * @return Servo 
 */
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
 * This function moves servos together at the same speed
 * there is a "bias" where the shortest motion will end first
 * @param {int} - array of arrays with the following: servo enum, start pos, end pos
 * @param {int} - array length
 * @param {int} - duration of motion in ms
 */
void moveServos(int servoGroupArr[][3], int servoGroupArrLen, int motionDuration)
{
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
  delay(stepDelay);
}

void centerAllLegs()
{
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

  // neutral stance
  centerAllLegs();
}

void moveBackLeftLegUp()
{
  int servoGroupArr[][3] = {
    {10, 80, 40}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontRightLegUp()
{
  int servoGroupArr[][3] = {
    {1, 80, 40},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegForward()
{
  int servoGroupArr[][3] = { // lol
    {9, 130, 100},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontRightLegDown()
{
  int servoGroupArr[][3] = {
    {1, 40, 80},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontLeftLegUp()
{
  int servoGroupArr[][3] = {
    {7, 100, 140},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackRightLegForward()
{
  int servoGroupArr[][3] = {
    {3, 50, 80},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontLeftLegDown()
{
  int servoGroupArr[][3] = {
    {7, 140, 100},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontRightLegForward()
{
  int servoGroupArr[][3] = {
    {0, 105, 135},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegDown()
{
  int servoGroupArr9[][3] = {
    {10, 40, 80}
  };

  moveServos(servoGroupArr9, 1, servoMotionDelay);
}

void moveBackRightLegUp()
{
  int servoGroupArr10[][3] = {
    {4, 95, 125}
  };

  moveServos(servoGroupArr10, 1, servoMotionDelay);
}

void moveFrontLeftLegForward()
{
  int servoGroupArr[][3] = {
    {6, 40, 20}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackRightLegDown()
{
  int servoGroupArr[][3] = {
    {4, 125, 95}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveAllFourLegsBack()
{
  int servoGroupArr[][3] = {
    {6, 20, 40},
    {0, 135, 105},
    {9, 100, 130},
    {3, 80, 50}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void moveFrontRightLegBack()
{
  int servoGroupArr[][3] = {
    {0, 105, 95}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontLeftLegBack()
{
  int servoGroupArr[][3] = {
    {6, 40, 70}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegBack()
{
  int servoGroupArr[][3] = { // lol
    {9, 130, 160},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveForward()
{
  moveFrontRightLegUp();
  moveBackLeftLegUp();
  moveBackLeftLegForward();
  moveFrontRightLegDown();
  moveFrontLeftLegUp();
  moveBackRightLegForward();
  moveFrontLeftLegDown();
  moveBackLeftLegUp();
  moveFrontRightLegForward();
  moveBackLeftLegDown();
  moveBackRightLegUp();
  moveFrontLeftLegForward();
  moveBackRightLegDown();
  moveAllFourLegsBack();  
}

void moveForward2()
{

}

void turnLeft()
{
  moveBackLeftLegUp();
  moveFrontRightLegForward();
  moveBackLeftLegDown();

  moveBackRightLegUp();
  moveFrontLeftLegBack();
  moveBackRightLegDown();

  moveFrontRightLegUp();
  moveBackLeftLegBack();
  moveFrontRightLegDown();

  moveFrontLeftLegUp();
  moveBackRightLegForward();
  moveFrontLeftLegDown();

  centerAllLegs();
}

void pivotLeft()
{
  int servoGroupArr[][3] = {
    {6, 40, 10},
    {9, 130, 100},
    {0, 105, 70},
    {3, 50, 20}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromLeft()
{
  int servoGroupArr[][3] = {
    {6, 10, 40},
    {9, 100, 130},
    {0, 70, 105},
    {3, 20, 50}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotRight()
{
  int servoGroupArr[][3] = {
    {6, 40, 70},
    {9, 130, 160},
    {0, 105, 135},
    {3, 50, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromRight()
{
  int servoGroupArr[][3] = {
    {6, 70, 40},
    {9, 160, 130},
    {0, 135, 105},
    {3, 80, 50}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltUp()
{
  int servoGroupArr[][3] = {
    {10, 80, 60},
    {4, 95, 110},
    {7, 100, 80},
    {1, 80, 100}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltCenterFromUp()
{
  int servoGroupArr[][3] = {
    {10, 60, 80},
    {4, 110, 95},
    {7, 80, 100},
    {1, 100, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltDown()
{
  int servoGroupArr[][3] = {
    {10, 80, 100},
    {4, 95, 80},
    {7, 100, 120},
    {1, 80, 60}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltCenterFromDown()
{
  int servoGroupArr[][3] = {
    {10, 100, 80},
    {4, 80, 95},
    {7, 120, 100},
    {1, 60, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

/**
 * @brief runCount is referring to which sweep is running
 * there are three: top, middle, bottom
 * the count determines where the robot is pointing (left/right)
 * and this is important to not jump positions and not scan the same place
 * if you were to return to the middle everytime
 * 
 * @param runCount 
 */
void sweep(int runCount)
{
  if (runCount == 1)
  {
    pivotRight();
    // start sample
    pivotCenterFromRight();
    pivotLeft();
    // end sample
  } else if (runCount == 2)
  {
    // start sample
    pivotCenterFromLeft();
    pivotRight();
    // end sample
  } else {
    // start sample
    pivotCenterFromRight();
    pivotLeft();
    // end sample
    pivotCenterFromLeft();
  }
}

void performScan()
{
  tiltUp();
  delay(1000);
  sweep(1);
  delay(1000);
  tiltCenterFromUp();
  delay(1000);
  sweep(2);
  delay(1000);
  tiltDown();
  delay(1000);
  sweep(3);
  delay(1000);
  tiltCenterFromDown();
}

void rollFrontLeft()
{
  int servoGroupArr[][3] = {
    {8, 85, 65},
    {5, 75, 95}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void centerFromRollFrontLeft()
{
  int servoGroupArr[][3] = {
    {8, 65, 85},
    {5, 95, 75}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void moveForward3()
{
  rollFrontLeft();
  moveFrontLeftLegUp();
  moveFrontLeftLegForward();
  moveFrontLeftLegDown();
  centerFromRollFrontLeft();
}