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
  frontRightInnerServo.write(85); // +40
  frontRightMiddleServo.write(80); // -10
  frontRightOuterServo.write(95); // +5
  backRightInnerServo.write(80); // -30
  backRightMiddleServo.write(105); // +10
  backRightOuterServo.write(70); // -15
  frontLeftInnerServo.write(50); // -30
  frontLeftMiddleServo.write(100); // +10
  frontLeftOuterServo.write(75); // -5
  backLeftInnerServo.write(130); // +30
  backLeftMiddleServo.write(70); // -10
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
    sampleDepth = true;
    sampleGyroZ = true;
    pivotRight();
    pivotCenterFromRight();
    pivotLeft();
    sampleDepth = false;
    sampleGyroZ = false;
  } else if (runCount == 2)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotCenterFromLeft();
    pivotRight();
    sampleDepth = false;
    sampleGyroZ = false;
  } else {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotCenterFromRight();
    pivotLeft();
    pivotCenterFromLeft();
    sampleDepth = false;
    sampleGyroZ = false;
  }
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

void performSweep()
{
  sweep(1);
  sweep(2);
  sweep(3);
}

void performScan()
{
  sampleDepth = true;
  sampleGyroX = true;
  tiltUp();
  sampleDepth = false;
  sampleGyroX = false;

  dumpData();

  delay(15000); // to copy paste form serial monitor output

  sweep(1);

  dumpData();

  delay(15000);

  sampleDepth = true;
  sampleGyroX = true;
  tiltCenterFromUp();
  sampleDepth = false;
  sampleGyroX = false;

  dumpData();

  delay(15000);

  sweep(2);

  dumpData();

  delay(15000);

  sampleDepth = true;
  sampleGyroX = true;
  tiltDown();
  sampleDepth = false;
  sampleGyroX = false;

  dumpData();

  delay(15000);

  sweep(3);

  dumpData();

  delay(15000);

  sampleDepth = true;
  sampleGyroX = true;
  tiltCenterFromDown();
  sampleDepth = false;
  sampleGyroX = false;

  dumpData();

  delay(15000);
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