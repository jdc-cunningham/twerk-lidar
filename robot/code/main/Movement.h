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
        float distSampleIn = (distSample * 0.0393701) - 0.5; // due to sway forward
        
        // this catches bad measurements
        // something can't be this close due to the allen wrench counter weight
        if (distSampleIn == 0 || distSampleIn >= 47)
        {
          depthVals[timeNow] = 47; // 47in is based on 1.2m max default measurement
        } else if (distSampleIn <= 4) {
          depthVals[timeNow] = 4;
        } else {
          depthVals[timeNow] = distSampleIn;
        }
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
  frontRightInnerServo.write(frontRightInnerServoInfo.start);
  frontRightMiddleServo.write(frontRightMiddleServoInfo.start);
  frontRightOuterServo.write(frontRightOuterServoInfo.start);
  backRightInnerServo.write(backRightInnerServoInfo.start);
  backRightMiddleServo.write(backRightMiddleServoInfo.start);
  backRightOuterServo.write(backRightOuterServoInfo.start);
  frontLeftInnerServo.write(frontLeftInnerServoInfo.start);
  frontLeftMiddleServo.write(frontLeftMiddleServoInfo.start);
  frontLeftOuterServo.write(frontLeftOuterServoInfo.start);
  backLeftInnerServo.write(backLeftInnerServoInfo.start);
  backLeftMiddleServo.write(backLeftMiddleServoInfo.start);
  backLeftOuterServo.write(backLeftOuterServoInfo.start);
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