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
  } else
  {
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
  } else
  {
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
    } else
    {
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
      } else
      {
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

    // track robot trajectory over time
    if (trackImu)
    {
      if (imu.Read())
      {
        motionImuTracking[timeNow] = {
          roundUp(imu.accel_x_mps2()),
          roundUp(imu.accel_y_mps2()),
          roundUp(radianToDegree(imu.gyro_z_radps()))
        };
      } else
      {
        motionImuTracking[timeNow] = {
          0.0, // to see how many are missed
          0.0,
          0.0
        };
      }
    }

    if (performScan && !obstacleFound)
    {
      float tofSampleIn = 0.00;
      float tfMiniSDistance = 0.00;

      int midPos = (largestServoRange - 1) / 2;
      int lowMidPos = midPos / 2; // this is expecting to truncate floats
      int highMidPos = (largestServoRange - 1) - lowMidPos;

      // ToF ranging sensor
      if (
        pos == 0 || pos == midPos
        || pos == lowMidPos || pos == highMidPos
        || (pos == largestServoRange - 1)
      ) // scan 5 samples per plane, not happening here no overlap check
      {
        // scanCounter += 1;
        tofSampleIn = getTofDistanceCorrected();

        // short circuit
        if (tofSampleIn < 5) // not able to move forward must turn
        {
          obstacleFound = true;
        }

        if (!obstacleFound && activeScan == "tilt-up-2")
        {
          if (u2Smallest == 0.0) // can turn this block into a function
          {
            u2Smallest = tofSampleIn;
          } else if (tofSampleIn < u2Smallest)
          {
            u2Smallest = tofSampleIn;
          }
        }

        if (!obstacleFound && activeScan == "tilt-up-1")
        {
          if (u1Smallest == 0.0)
          {
            u1Smallest = tofSampleIn;
          } else if (tofSampleIn < u1Smallest)
          {
            u1Smallest = tofSampleIn;
          }
        }

        if (!obstacleFound && activeScan == "middle")
        {
          if (mSmallest == 0.0)
          {
            mSmallest = tofSampleIn;
          } else if (tofSampleIn < mSmallest)
          {
            mSmallest = tofSampleIn;
          }
        }

        if (!obstacleFound && activeScan == "tilt-down-1")
        {
          if (d1Smallest == 0.0)
          {
            d1Smallest = tofSampleIn;
          } else if (tofSampleIn < d1Smallest)
          {
            d1Smallest = tofSampleIn;
          }
        }

        if (!obstacleFound && activeScan == "tilt-down-2")
        {
          if (d2Smallest == 0.0)
          {
            d2Smallest = tofSampleIn;
          } else if (tofSampleIn < d2Smallest)
          {
            d2Smallest = tofSampleIn;
          }
        }

        Serial.println("sample");
        Serial.println(tofSampleIn);
      }

      // lidar distance
      // skip lidar for now
      // if (pos == 0 || pos == largestServoRange || pos % 3) // measure all
      // // if (pos == 0 || pos == largestServoRange || pos % 3 == 0)
      // {
      //   tfMiniSDistance = getTFminiSDistance(); // skip until have it
      // }

      // fill out the basic mesh data
      // scanSampleValues[activeScan][timeNow] = {
      //   static_cast<float>(pos), // yuck https://stackoverflow.com/a/22589942/2710227
      //   roundUp(radianToDegree(imu.gyro_z_radps())),
      //   tfMiniSDistance,
      //   // correctedDistanceSampleIn,
      //   0 //tfMiniSDistance
      // };

      if (imu.Read())
      {
        // pitch angle rate, this didn't really work
        if (sampleGyroX)
        {
          gyroVals[timeNow] = roundUp(radianToDegree(imu.gyro_x_radps()));
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
    {1, 90, 50} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontRightLegForward()
{
  int servoGroupArr[][3] = {
    {0, 65, 95}, // front right inner
    {2, 115, 105}
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
    {1, 50, 90} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardRight()
{
  int servoGroupArr[][3] = {
    {6, 30, 65},
    {2, 105, 115},
    {9, 130, 150},
    {3, 80, 50}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void mf5MoveBackLeftLegUp()
{
  int servoGroupArr[][3] = {
    {10, 100, 55}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegForward()
{
  int servoGroupArr[][3] = {
    {9, 150, 105}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {10, 55, 100} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegUp()
{
  int servoGroupArr[][3] = {
    {7, 60, 105}
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
    {7, 105, 60}
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardLeft()
{
  int servoGroupArr[][3] = {
    {0, 95, 65},
    {8, 115, 95},
    {3, 50, 20},
    {9, 100, 130},
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
    {4, 135, 95} // back right middle
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
    {6, 0, 50},
    {9, 95, 65},
    {3, 50, 20},
    {0, 100, 70}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void leftTurnPivot3()
{
  int servoGroupArr[][3] = {
    {6, 50, 30},
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