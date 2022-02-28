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
    {7, 95, 75}, // front left middle
    {8, 80, 100} // front left outer
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}