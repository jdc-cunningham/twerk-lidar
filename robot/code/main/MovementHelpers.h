/**
 * @brief Get the Servo By Pin object
 * 
 * @param digitalPin 
 * @return struct
 */
Servo getServoByPin(int digitalPin)
{
  if (digitalPin == 0) // ugh this sucks
  {
    return frontRightInnerJoint.servo;
  } else if (digitalPin == 1)
  {
    return frontRightMiddleJoint.servo;
  } else if (digitalPin == 2)
  {
    return frontRightOuterJoint.servo;
  } else if (digitalPin == 3)
  {
    return backRightInnerJoint.servo;
  } else if (digitalPin == 4)
  {
    return backRightMiddleJoint.servo;
  } else if (digitalPin == 5)
  {
    return backRightOuterJoint.servo;
  } else if (digitalPin == 6)
  {
    return frontLeftInnerJoint.servo;
  } else if (digitalPin == 7)
  {
    return frontLeftMiddleJoint.servo;
  } else if (digitalPin == 8)
  {
    return frontLeftOuterJoint.servo;
  } else if (digitalPin == 9)
  {
    return backLeftInnerJoint.servo;
  } else if (digitalPin == 10)
  {
    return backLeftMiddleJoint.servo;
  } else {
    return backLeftOuterJoint.servo;
  }
}

joint getJointByPin (int digitalPin)
{
  if (digitalPin == 0) // ugh this sucks
  {
    return frontRightInnerJoint;
  } else if (digitalPin == 1)
  {
    return frontRightMiddleJoint;
  } else if (digitalPin == 2)
  {
    return frontRightOuterJoint;
  } else if (digitalPin == 3)
  {
    return backRightInnerJoint;
  } else if (digitalPin == 4)
  {
    return backRightMiddleJoint;
  } else if (digitalPin == 5)
  {
    return backRightOuterJoint;
  } else if (digitalPin == 6)
  {
    return frontLeftInnerJoint;
  } else if (digitalPin == 7)
  {
    return frontLeftMiddleJoint;
  } else if (digitalPin == 8)
  {
    return frontLeftOuterJoint;
  } else if (digitalPin == 9)
  {
    return backLeftInnerJoint;
  } else if (digitalPin == 10)
  {
    return backLeftMiddleJoint;
  } else {
    return backLeftOuterJoint;
  }
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

  // emergency stop
  if (stopRobot)
  {
    return;
  }

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
      int servoPin = servoGroupArr[servoGroupIndex][0];
      joint jointToMove; // this is like this to avoid a warning unused variable
      jointToMove = getJointByPin(servoGroupArr[servoGroupIndex][0]); // sucks double lookup
      int nextServoPos;

      if (servoGroupArr[servoGroupIndex][1] < servoGroupArr[servoGroupIndex][2]) {
        // increase
        if (servoGroupArr[servoGroupIndex][1] + pos < servoGroupArr[servoGroupIndex][2]) {
          nextServoPos = servoGroupArr[servoGroupIndex][1] + pos;
          safeServoWrite(servoPin, nextServoPos);
        }
      } else {
        // decrease
        if (servoGroupArr[servoGroupIndex][1] - pos > servoGroupArr[servoGroupIndex][2]) {
          nextServoPos = servoGroupArr[servoGroupIndex][1] - pos;
          safeServoWrite(servoPin, nextServoPos);
        }
      }

      // update global servo current position
      jointToMove.currentPos = nextServoPos;
    }

    int timeNow = millis();

    if (imu.Read())
    {
      // sample outer-most pos and every 4th degree
      // if (sampleDepth && (pos == 0 || (pos == largestServoRange - 1) || pos % 4 == 0))
      if (sampleDepth)
      {
        float distSample = tofSensor.readRangeSingleMillimeters();
        float distSampleIn = (distSample * 0.0393701);
        
        // this catches bad measurements
        // something can't be this close due to the allen wrench counter weight
        if (distSampleIn == 0 || distSampleIn >= 47)
        {
          depthVals[timeNow] = 47; // 47in is based on 1.2m max default measurement
        } else if (distSampleIn <= 4) {
          depthVals[timeNow] = 4;
        } else {
          depthVals[timeNow] = roundUp(distSampleIn);
        }
      }

      // pitch angle rate
      if (sampleGyroX)
      {
        gyroVals[timeNow] = roundUp(radianToDegree(imu.gyro_x_radps()));
      }

      // yaw angle rate
      if (sampleGyroZ)
      {
        gyroVals[timeNow] = roundUp(radianToDegree(imu.gyro_z_radps()));
      }

      if (sampleYAccel)
      {
        yAccelVals[timeNow] = roundUp(imu.accel_y_mps2());
      }

      if (sampleXAccel)
      {
        xAccelVals[timeNow] = roundUp(imu.accel_x_mps2());
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

void mf5MoveFrontRightLegUp()
{
  int servoGroupArr[][3] = {
    {1, 80, 40} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontRightLegForward()
{
  int servoGroupArr[][3] = {
    {0, 70, 100}, // front right inner
    {2, 105, 95}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveFrontRightLegForwardTwice()
{
  int servoGroupArr[][3] = {
    {0, 65, 125}, // front right inner
    {2, 105, 95}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveFrontRightLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {1, 40, 80} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardRight()
{
  int servoGroupArr[][3] = {
    {6, 30, 65},
    {2, 95, 105},
    {9, 125, 145},
    {3, 80, 50}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void mf5MoveBackLeftLegUp()
{
  int servoGroupArr[][3] = {
    {10, 85, 40}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegForward()
{
  int servoGroupArr[][3] = {
    {9, 145, 100}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {10, 40, 85} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegUp()
{
  int servoGroupArr[][3] = {
    {7, 70, 115}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegForward()
{
  int servoGroupArr[][3] = {
    {6, 60, 25}, // front left inner
    {8, 95, 115}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveFrontLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {7, 115, 70}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardLeft()
{
  int servoGroupArr[][3] = {
    {0, 100, 70},
    {8, 115, 95},
    {3, 50, 20},
    {9, 95, 125},
    {11, 85, 90}
  };

  moveServos(servoGroupArr, 5, servoMotionDelay);
}

void mf5MoveBackRightLegUp()
{
  int servoGroupArr[][3] = {
    {4, 95, 135},
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackRightLegForward()
{
  int servoGroupArr[][3] = {
    {3, 20, 80},
    {11, 90, 85}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveBackRightLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {4, 130, 90} // back right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontRightLegUpHalf()
{
  int servoGroupArr[][3] = {
    {1, 80, 60} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontRightLegDownFromUpHalf()
{
  int servoGroupArr[][3] = {
    {1, 60, 80} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegUpHalf()
{
  int servoGroupArr[][3] = {
    {7, 80, 105}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegDownFromUpHalf()
{
  int servoGroupArr[][3] = {
    {7, 105, 80}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegBackward()
{
  int servoGroupArr[][3] = {
    {9, 95, 125} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackRightLegBack()
{
  int servoGroupArr[][3] = {
    {3, 80, 50} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
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
    {6, 0, 60},
    {9, 95, 65},
    {3, 50, 20},
    {0, 100, 70}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void leftTurnPivot3()
{
  int servoGroupArr[][3] = {
    {6, 60, 30},
    {9, 65, 125},
    {3, 20, 0},
    {0, 70, 40}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void ltp3ToNeutral()
{
  int servoGroupArr[][3] = {
    {3, 0, 80}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void ltp3ToNeutral2()
{
  int servoGroupArr[][3] = {
    {0, 40, 70}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void ltp3ToNeutral3()
{
  int servoGroupArr[][3] = {
    {9, 95, 125},
    {1, 60, 80}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}