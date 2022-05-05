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
    {0, 60, 100}, // front right inner
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
    {6, 40, 80}, // front left inner
    {2, 95, 105},
    {9, 125, 155},
    {3, 80, 50}
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
    {9, 155, 95} // back left inner
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
    {7, 90, 130} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegForward()
{
  int servoGroupArr[][3] = {
    {6, 80, 40}, // front left inner
    {8, 80, 100}
  };

  moveServos(servoGroupArr, 2, servoMotionDelay);
}

void mf5MoveFrontLeftLegDownFromUp()
{
  int servoGroupArr[][3] = {
    {7, 130, 90} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5PullForwardLeft()
{
  int servoGroupArr[][3] = {
    {0, 100, 60},
    {8, 100, 80},
    {3, 50, 20},
    {9, 95, 125}
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
    {3, 20, 80} // back right inner
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
    {7, 90, 110} // front left middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void mf5MoveFrontLeftLegDownFromUpHalf()
{
  int servoGroupArr[][3] = {
    {7, 110, 90} // front left middle
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

void preSweepSwayForward()
{
  int servoGroupArr[][3] = {
    {6, 40, 50},
    {0, 70, 60},
    {9, 125, 135},
    {3, 80, 70}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void postSweepSwayForward()
{
  int servoGroupArr[][3] = {
    {6, 50, 40},
    {0, 60, 70},
    {9, 135, 125},
    {3, 70, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}