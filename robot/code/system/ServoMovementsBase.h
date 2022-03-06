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
int servoMotionDelay = 4; // min 1 ms
int stepDelay = 0; // ms usually a second or more

bool sampleDepth = false;
bool sampleGyroZ = false; // yaw
bool sampleGyroX = false; // pitch
bool sampleYAccel = false;
bool sampleXAccel = false;

// these use time from millis() as a shared key to sync the data
std::map<int, float> gyroVals = {};
std::map<int, int> servoPosVals = {};
std::map<int, float> depthVals = {};
std::map<int, float> xAccelVals = {};
std::map<int, float> yAccelVals = {};

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
        float distSample = sensor.readRangeSingleMillimeters();
        float distSampleIn = distSample * 0.0393701;
        depthVals[timeNow] = distSampleIn;
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

      if (sampleYAccel)
      {
        yAccelVals[timeNow] = imu.accel_y_mps2();
      }

      if (sampleXAccel)
      {
        xAccelVals[timeNow] = imu.accel_x_mps2();
      }
    }

    if (sampleDepth || sampleGyroX || sampleGyroZ || sampleYAccel || sampleXAccel)
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
  frontRightMiddleServo.write(90);
  frontRightOuterServo.write(105);
  backRightInnerServo.write(80);
  backRightMiddleServo.write(95);
  backRightOuterServo.write(65);
  frontLeftInnerServo.write(50);
  frontLeftMiddleServo.write(95);
  frontLeftOuterServo.write(80);
  backLeftInnerServo.write(125);
  backLeftMiddleServo.write(70);
  backLeftOuterServo.write(100);
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
    {6, 30, 50},
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
    {6, 50, 90}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void moveBackLeftLegBack()
{
  int servoGroupArr[][3] = {
    {9, 125, 155},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void pivotLeft()
{
  int servoGroupArr[][3] = {
    {6, 50, 10},
    {9, 125, 85},
    {0, 65, 25},
    {3, 80, 40}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromLeft()
{
  int servoGroupArr[][3] = {
    {6, 10, 50},
    {9, 85, 125},
    {0, 25, 65},
    {3, 40, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotRight()
{
  int servoGroupArr[][3] = {
    {6, 50, 90},
    {9, 125, 165},
    {0, 65, 105},
    {3, 80, 120}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromRight()
{
  int servoGroupArr[][3] = {
    {6, 90, 50},
    {9, 165, 125},
    {0, 105, 65},
    {3, 120, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltUp1()
{
  int servoGroupArr[][3] = {
    {10, 70, 50},
    {7, 95, 75},
    {2, 105, 90},
    {8, 80, 95},
    {4, 95, 115},
    {1, 80, 100},
    {11, 100, 115},
    {5, 65, 50}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromUp1()
{
  int servoGroupArr[][3] = {
    {10, 50, 70},
    {7, 75, 90},
    {2, 90, 105},
    {8, 95, 80},
    {4, 115, 95},
    {1, 100, 80},
    {11, 115, 100},
    {5, 50, 65}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltUp2()
{
  int servoGroupArr[][3] = {
    {10, 50, 30},
    {7, 75, 50},
    {2, 90, 70},
    {8, 95, 110},
    {4, 115, 135},
    {1, 100, 115},
    {11, 115, 130},
    {5, 50, 35}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromUp2()
{
  int servoGroupArr[][3] = {
    {10, 30, 50},
    {7, 50, 75},
    {2, 70, 90},
    {8, 110, 95},
    {4, 135, 115},
    {1, 115, 100},
    {11, 130, 115},
    {5, 35, 50}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown1()
{
  int servoGroupArr[][3] = {
    {10, 70, 90},
    {7, 95, 115},
    {2, 105, 120}, // outer
    {8, 80, 65}, // outer
    {4, 95, 75},
    {1, 80, 60},
    {11, 100, 85}, // outer
    {5, 65, 80} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown1()
{
  int servoGroupArr[][3] = {
    {10, 90, 70},
    {7, 115, 95},
    {2, 120, 105},
    {8, 65, 80},
    {4, 75, 95},
    {1, 60, 80},
    {11, 85, 100},
    {5, 80, 65}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown2()
{
  int servoGroupArr[][3] = {
    {10, 90, 110},
    {7, 115, 145},
    {2, 120, 135}, // outer
    {8, 60, 45}, // outer
    {4, 75, 55},
    {1, 60, 40},
    {11, 85, 70}, // outer
    {5, 80, 95} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown2()
{
  int servoGroupArr[][3] = {
    {10, 110, 90},
    {7, 145, 115},
    {2, 135, 120}, // outer
    {8, 45, 60}, // outer
    {4, 55, 75},
    {1, 40, 60},
    {11, 70, 85}, // outer
    {5, 95, 80} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
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

void leftTurnPivot()
{
  int servoGroupArr[][3] = {
    {6, 40, 10},
    {9, 125, 95},
    {3, 80, 50},
    {0, 65, 95}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void leftTurnPivot2()
{
  int servoGroupArr[][3] = {
    {6, 10, 70}, // front left inner
    {9, 95, 65},
    {3, 50, 20},
    {0, 95, 65}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void leftTurnPivot3()
{
  int servoGroupArr[][3] = {
    {6, 80, 50}, // front left inner
    {9, 65, 125}, // back left inner
    {3, 20, 0}, // back right inner
    {0, 65, 35}
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
    {0, 35, 65} // front right inner
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