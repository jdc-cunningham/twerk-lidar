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
    {0, 60, 90}, // front right inner
    {2, 100, 90}
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
    {6, 50, 75}, // front left inner
    {2, 90, 100},
    {9, 125, 140},
    {3, 85, 55}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void mf5MoveBackLeftLegUp()
{
  int servoGroupArr[][3] = {
    {10, 70, 30} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegForward()
{
  int servoGroupArr[][3] = {
    {9, 140, 100} // back left inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {10, 30, 70} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegUp()
{
  int servoGroupArr[][3] = {
    {7, 95, 135} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegForward()
{
  int servoGroupArr[][3] = {
    {6, 75, 50}, // front left inner
    {8, 80, 100}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveFrontLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {7, 135, 95} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardLeft()
{
  int servoGroupArr[][3] = {
    {0, 90, 60},
    {8, 100, 80},
    {3, 55, 25},
    {9, 100, 125}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void mf5MoveBackRightLegUp()
{
  int servoGroupArr[][3] = {
    {4, 95, 135}, // back right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveBackRightLegForward()
{
  int servoGroupArr[][3] = {
    {3, 25, 85} // back right inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
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
    {1, 90, 70} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontRightLegDownFromUpHalf()
{
  int servoGroupArr[][3] = {
    {1, 70, 90} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegUpHalf()
{
  int servoGroupArr[][3] = {
    {7, 95, 115} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegDownFromUpHalf()
{
  int servoGroupArr[][3] = {
    {7, 115, 95} // front left middle
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