void mf4MoveFrontRightLegDown()
{
  int servoGroupArr[][3] = {
    {1, 80, 120}, // front right middle
    {2, 105, 85} // front right outer
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveFrontRightLegUpFromDown()
{
  int servoGroupArr[][3] = {
    {1, 120, 80}, // front right middle
    {2, 85, 105} // front right outer
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveFrontRightLegUp()
{
  int servoGroupArr[][3] = {
    {1, 80, 40}, // front right middle
    {2, 105, 125}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveFrontRightLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {1, 40, 80}, // front right middle
    {2, 125, 105}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveFrontRightLegForward()
{
  int servoGroupArr[][3] = {
    {0, 65, 105} // front right inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveFrontLeftLegUp()
{
  int servoGroupArr[][3] = {
    {7, 95, 115} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveFrontLeftLegForward()
{
  int servoGroupArr[][3] = {
    {6, 70, 30} // front left inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveFrontLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {7, 115, 95} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveFrontLeftLegDown()
{
  int servoGroupArr[][3] = {
    {7, 95, 55}, // front left middle
    {8, 80, 100} // front left outer
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveFrontLeftLegUpFromDown()
{
  int servoGroupArr[][3] = {
    {7, 55, 95}, // front left middle
    {8, 100, 80} // front left outer
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveAllForward()
{
  int servoGroupArr[][3] = {
    {6, 30, 70},
    {0, 105, 65},
    {9, 95, 135},
    {3, 80, 40}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}