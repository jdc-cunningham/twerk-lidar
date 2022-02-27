#include <Servo.h>
#include <map>
#include <vector>
#include <math.h>

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
int servoMotionDelay = 6; // min 1 ms
int stepDelay = 0; // ms usually a second or more
bool sampleDepth = false;
bool sampleGyroZ = false; // yaw
bool sampleGyroX = false; // pitch

// these use time from millis() as a shared key to sync the data
std::map<int, float> gyroVals = {};
std::map<int, int> servoPosVals = {};
std::map<int, float> depthVals = {};

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
  // int moveCounter = 0;

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
          int nextServoPos = servoGroupArr[servoGroupIndex][1] + pos;
          getServoByPin(servoGroupArr[servoGroupIndex][0]).write(nextServoPos);
        }
      } else {
        // decrease
        if (servoGroupArr[servoGroupIndex][1] - pos > servoGroupArr[servoGroupIndex][2]) {
          int nextServoPos = servoGroupArr[servoGroupIndex][1] - pos;
          getServoByPin(servoGroupArr[servoGroupIndex][0]).write(nextServoPos);
        }
      }
    }

    int timeNow = millis();

    if (imu.Read())
    {
      if (sampleDepth)
      {
        float distSample = sensor.readRangeSingleMillimeters() * 0.0393701;
        depthVals[timeNow] = distSample;
      }

      // pitch angle rate
      if (sampleGyroX)
      {
        gyroVals[timeNow] = radianToDegree(imu.gyro_x_radps());
      }

      // yaw angle rate
      if (sampleGyroZ)
      {
        gyroVals[timeNow] = radianToDegree(imu.gyro_z_radps());
      }
    }

    if (sampleDepth || sampleGyroX || sampleGyroZ)
    {
      servoPosVals[timeNow] = pos;
    }
    delay(motionDuration);
  }

  motionInProgress = false;
  delay(stepDelay);
}

void centerAllLegs()
{
  frontRightInnerServo.write(65);
  frontRightMiddleServo.write(80);
  frontRightOuterServo.write(105);
  backRightInnerServo.write(80);
  backRightMiddleServo.write(95);
  backRightOuterServo.write(65);
  frontLeftInnerServo.write(70);
  frontLeftMiddleServo.write(95);
  frontLeftOuterServo.write(80);
  backLeftInnerServo.write(95);
  backLeftMiddleServo.write(70);
  backLeftOuterServo.write(100);
}

void moveForward4()
{
  // 1, 4, 7, 10 middle servos
  // move front-left leg forward
  int servoGroupArr[][3] = {
    {1, 80, 120} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);

  // move front right outer outwards
  int servoGroupArrA[][3] = {
    {2, 105, 85} // front right middle
  };

  moveServos(servoGroupArrA, 1, servoMotionDelay);

  int servoGroupArr1[][3] = {
    {7, 95, 115} // front left middle
  };

  moveServos(servoGroupArr1, 1, servoMotionDelay);

  int servoGroupArr2[][3] = {
    {6, 70, 30} // front left inner
  };

  moveServos(servoGroupArr2, 1, servoMotionDelay);

  int servoGroupArr3[][3] = {
    {7, 115, 95} // front left middle
  };

  moveServos(servoGroupArr3, 1, servoMotionDelay);

  int servoGroupArr4[][3] = {
    {1, 120, 80} // front right middle
  };

  moveServos(servoGroupArr4, 1, servoMotionDelay);

  // move front-right leg forward
  int servoGroupArr5[][3] = {
    {7, 95, 75} // front left middle
  };

  moveServos(servoGroupArr5, 1, servoMotionDelay);

  int servoGroupArr6[][3] = {
    {1, 80, 40} // front right middle
  };

  moveServos(servoGroupArr6, 1, servoMotionDelay);

  int servoGroupArr7[][3] = {
    {0, 65, 105} // front right inner
  };

  moveServos(servoGroupArr7, 1, servoMotionDelay);

  int servoGroupArr8[][3] = {
    {1, 40, 80} // front right middle
  };

  moveServos(servoGroupArr8, 1, servoMotionDelay);

  // frontLeftMiddleServo.write(95);
  int servoGroupArr9[][3] = {
    {7, 75, 95} // front left middle
  };

  moveServos(servoGroupArr9, 1, servoMotionDelay);

  // move all for forward
  int servoGroupArr10[][3] = {
    {6, 30, 70},
    {0, 105, 65},
    {9, 95, 135},
    {3, 80, 40}
  };

  moveServos(servoGroupArr10, 4, servoMotionDelay);

  // move back-right leg forwrard
  int servoGroupArr11[][3] = {
    {4, 95, 115} // back right middle
  };

  moveServos(servoGroupArr11, 1, servoMotionDelay);

  int servoGroupArr12[][3] = {
    {3, 40, 80} // back right inner
  };

  moveServos(servoGroupArr12, 1, servoMotionDelay);

  int servoGroupArr13[][3] = {
    {4, 115, 95} // back right middle
  };

  moveServos(servoGroupArr13, 1, servoMotionDelay);

  // // move back left leg forward
  int servoGroupArr15[][3] = {
    {1, 80, 60} // front right middle
  };

  moveServos(servoGroupArr15, 1, servoMotionDelay);

  int servoGroupArr16[][3] = {
    {9, 115, 95} // back left inner
  };

  moveServos(servoGroupArr16, 1, servoMotionDelay);

  int servoGroupArr17[][3] = {
    {1, 60, 80} // front right middle
  };

  moveServos(servoGroupArr17, 1, servoMotionDelay);
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
    {10, 80, 30}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontRightLegUp()
{
  int servoGroupArr[][3] = {
    {1, 80, 30},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegForward()
{
  int servoGroupArr[][3] = { // lol
    {9, 150, 130},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontRightLegDown()
{
  int servoGroupArr[][3] = {
    {1, 30, 80},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontLeftLegUp()
{
  int servoGroupArr[][3] = {
    {7, 100, 150},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackRightLegForward()
{
  int servoGroupArr[][3] = {
    {3, 60, 80}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackRightLegBackward()
{
  int servoGroupArr[][3] = {
    {3, 80, 60}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontLeftLegDown()
{
  int servoGroupArr[][3] = {
    {7, 150, 100},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveFrontRightLegForward()
{
  int servoGroupArr[][3] = {
    {0, 85, 105},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegDown()
{
  int servoGroupArr9[][3] = {
    {10, 30, 80}
  };

  moveServos(servoGroupArr9, 1, servoMotionDelay);
}

void moveBackRightLegUp()
{
  int servoGroupArr10[][3] = {
    {4, 95, 135}
  };

  moveServos(servoGroupArr10, 1, servoMotionDelay);
}

void moveFrontLeftLegForward()
{
  int servoGroupArr[][3] = {
    {6, 50, 30}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackRightLegDown()
{
  int servoGroupArr[][3] = {
    {4, 135, 95}
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
    {6, 40, 80}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegBack()
{
  int servoGroupArr[][3] = { // lol
    {9, 130, 150},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void pivotLeft()
{
  int servoGroupArr[][3] = {
    {6, 50, 0},
    {9, 130, 80},
    {0, 85, 35},
    {3, 80, 30}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromLeft()
{
  int servoGroupArr[][3] = {
    {6, 0, 50},
    {9, 80, 130},
    {0, 35, 85},
    {3, 30, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotRight()
{
  int servoGroupArr[][3] = {
    {6, 50, 100},
    {9, 130, 180},
    {0, 85, 135},
    {3, 80, 130}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromRight()
{
  int servoGroupArr[][3] = {
    {6, 100, 50},
    {9, 180, 130},
    {0, 135, 85},
    {3, 130, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltUp1()
{
  int servoGroupArr[][3] = {
    {10, 70, 50},
    {7, 100, 80},
    {2, 95, 80},
    {8, 75, 90},
    {4, 85, 105},
    {1, 80, 100},
    {11, 95, 110},
    {5, 70, 55}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromUp1()
{
  int servoGroupArr[][3] = {
    {10, 50, 70},
    {7, 80, 100},
    {2, 80, 95},
    {8, 90, 75},
    {4, 105, 85},
    {1, 100, 80},
    {11, 110, 95},
    {5, 55, 70}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltUp2()
{
  int servoGroupArr[][3] = {
    {10, 50, 30},
    {7, 80, 60},
    {2, 80, 65},
    {8, 90, 105},
    {4, 105, 125},
    {1, 100, 120},
    {11, 110, 125},
    {5, 55, 40}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromUp2()
{
  int servoGroupArr[][3] = {
    {10, 30, 50},
    {7, 60, 80},
    {2, 65, 80},
    {8, 105, 90},
    {4, 125, 105},
    {1, 120, 100},
    {11, 125, 110},
    {5, 40, 55}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown1()
{
  int servoGroupArr[][3] = {
    {10, 70, 90},
    {7, 100, 120},
    {2, 95, 110}, // outer
    {8, 75, 60}, // outer
    {4, 105, 85},
    {1, 80, 60},
    {11, 95, 80}, // outer
    {5, 70, 85} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown1()
{
  int servoGroupArr[][3] = {
    {10, 90, 70},
    {7, 120, 100},
    {2, 110, 95},
    {8, 60, 75},
    {4, 85, 105},
    {1, 60, 80},
    {11, 80, 95},
    {5, 85, 70}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown2()
{
  int servoGroupArr[][3] = {
    {10, 90, 110},
    {7, 120, 140},
    {2, 110, 125}, // outer
    {8, 60, 45}, // outer
    {4, 85, 65},
    {1, 60, 40},
    {11, 80, 65}, // outer
    {5, 85, 100} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown2()
{
  int servoGroupArr[][3] = {
    {10, 110, 90},
    {7, 140, 120},
    {2, 125, 110}, // outer
    {8, 45, 60}, // outer
    {4, 65, 85},
    {1, 40, 60},
    {11, 65, 80}, // outer
    {5, 100, 85} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

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

// tilt-away-from-moving type gait
void turnLeft()
{
  // moveBackRightLegUp();
  // moveBackRightLegBackward();
  // moveBackRightLegDown();

  // moveBackLeftLegUp();
  // moveFrontRightLegForward();
  // moveBackLeftLegDown();

  // moveBackLeftLegUp();
  // moveBackLeftLegBack();
  // moveBackLeftLegDown();

  moveFrontRightLegUp();
  moveFrontRightLegForward();
  moveFrontRightLegDown();
  
  // moveFrontLeftLegUp();

  // moveBackRightLegUp();
  // moveBackRightLegForward();
  // moveBackRightLegDown();

  // moveFrontLeftLegDown();

  // moveFrontLeftLegUp();
  // moveFrontLeftLegBack();
  // moveFrontLeftLegDown();

  // centerAllLegs();
}

void cgShiftBackRight()
{
  int servoGroupArr[][3] = {
    // {8, 85, 65},
    {9, 130, 110},
    {0, 105, 125},
    // {5, 75, 95}
  };

  int servoCount = sizeof(servoGroupArr) / sizeof(servoGroupArr[0]);
  moveServos(servoGroupArr, servoCount, servoMotionDelay);
}

void centerFromCgShiftBackRight()
{
  int servoGroupArr[][3] = {
    // {8, 65, 85},
    {9, 110, 130},
    {0, 125, 105},
    // {5, 95, 75}
  };

  int servoCount = sizeof(servoGroupArr) / sizeof(servoGroupArr[0]);
  moveServos(servoGroupArr, servoCount, servoMotionDelay);
}

void pullForward()
{
  int servoGroupArr[][3] = {
    {6, 30, 60},
    {0, 105, 75},
    {9, 130, 150},
    {3, 80, 40}
  };

  int servoCount = sizeof(servoGroupArr) / sizeof(servoGroupArr[0]);
  moveServos(servoGroupArr, servoCount, servoMotionDelay);
}

void pitchDown() // tiltDown command as well but 4 servos
{
  int servoGroupArr[][3] = {
    {7, 100, 125},
    {1, 80, 55},
  };

  int servoCount = sizeof(servoGroupArr) / sizeof(servoGroupArr[0]);
  moveServos(servoGroupArr, servoCount, servoMotionDelay);
}

void pitchUp()
{
  int servoGroupArr[][3] = {
    {7, 125, 100},
    {1, 55, 80}
  };

  int servoCount = sizeof(servoGroupArr) / sizeof(servoGroupArr[0]);
  moveServos(servoGroupArr, servoCount, servoMotionDelay);
}

void performPitchTest()
{
  tiltUp1();
  delay(5000);
  tiltCenterFromUp1();
  delay(5000);
  tiltDown1();
  delay(5000);
  tiltCenterFromDown1();
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