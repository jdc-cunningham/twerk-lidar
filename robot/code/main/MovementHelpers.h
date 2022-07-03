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