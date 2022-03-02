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
    {0, 65, 85}, // front right inner
    {2, 105, 95}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveFrontRightLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {1, 40, 80} // front right middle
    // {2, 105, 85}
    // {2, 125, 105} // keep extended
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardRight()
{
  int servoGroupArr[][3] = {
    {6, 50, 70}, // front left inner
    {2, 95, 105},
    {9, 115, 135},
    {3, 80, 60}
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
    {9, 135, 95} // back left inner
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
    {6, 70, 50}, // front left inner
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
    {0, 85, 65},
    {8, 100, 80},
    {3, 60, 40},
    {9, 95, 115}
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
    {3, 40, 80} // back right inner
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