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

void mf4MoveFrontRightLegUpOuterFlipped()
{
  int servoGroupArr[][3] = {
    {1, 80, 60}, // front right middle
    {2, 105, 135},
    {5, 65, 70},
    {8, 80, 75}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void mf4MoveFrontRightLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {1, 40, 80}, // front right middle
    {2, 125, 105}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf4MoveFrontRightLegDownFromUpOuterFlipped()
{
  int servoGroupArr[][3] = {
    {1, 60, 80}, // front right middle
    {2, 135, 105},
    {5, 70, 65},
    {8, 75, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
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
    {7, 95, 115}, // front left middle
    {8, 80, 60}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
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
    {7, 115, 95}, // front left middle
    {8, 60, 80}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
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
    {3, 80, 40},
    {0, 105, 65},
    {9, 95, 135}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void mf4MoveBackRightLegUp()
{
  int servoGroupArr[][3] = {
    {4, 95, 115}, // back right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveBackRightLegForward()
{
  int servoGroupArr[][3] = {
    {3, 40, 80} // back right inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveBackRightLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {4, 115, 95} // back right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveBackLeftLegUp()
{
  int servoGroupArr[][3] = {
    {10, 70, 50} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveBackLeftLegForward()
{
  int servoGroupArr[][3] = {
    {9, 115, 95} // back left inner
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4MoveBackLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {10, 50, 70} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf4HalfRollRight()
{
  int servoGroupArr[][3] = {
    {1, 80, 40}, // front right middle
    {2, 105, 125},
    {4, 95, 135},
    {5, 65, 45}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}
