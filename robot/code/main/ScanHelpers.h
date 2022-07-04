void pivotRight()
{
  int servoGroupArr[][3] = {
    {6, 30, 60},
    {9, 125, 155},
    {0, 70, 100},
    {3, 80, 110}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromRight()
{
  int servoGroupArr[][3] = {
    {6, 60, 30},
    {9, 155, 125},
    {0, 100, 70},
    {3, 110, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotLeft()
{
  int servoGroupArr[][3] = {
    {6, 30, 0},
    {9, 125, 95},
    {0, 70, 40},
    {3, 80, 50}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void pivotCenterFromLeft()
{
  int servoGroupArr[][3] = {
    {6, 0, 30},
    {9, 95, 125},
    {0, 40, 70},
    {3, 50, 80}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}

void tiltCenterFromUp2()
{
  int servoGroupArr[][3] = {
    {10, 35, 55},
    {7, 45, 70},
    {2, 70, 90},
    {8, 115, 100},
    {4, 135, 115},
    {1, 115, 100},
    {11, 125, 110},
    {5, 35, 50}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromUp1()
{
  int servoGroupArr[][3] = {
    {10, 55, 85},
    {7, 70, 90},
    {2, 90, 105},
    {8, 100, 85},
    {4, 115, 95},
    {1, 100, 80},
    {11, 110, 95},
    {5, 50, 65}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown1()
{
  int servoGroupArr[][3] = {
    {10, 85, 105},
    {7, 70, 90},
    {2, 105, 120}, // outer
    {8, 85, 70}, // outer
    {4, 95, 75},
    {1, 80, 65},
    {11, 95, 80}, // outer
    {5, 65, 80} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown2()
{
  int servoGroupArr[][3] = {
    {10, 85, 105},
    {7, 90, 120},
    {2, 120, 135}, // outer
    {8, 70, 55}, // outer
    {4, 75, 55},
    {1, 65, 55},
    {11, 80, 65}, // outer
    {5, 80, 95} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown2()
{
  int servoGroupArr[][3] = {
    {10, 105, 85},
    {7, 120, 90},
    {2, 135, 120}, // outer
    {8, 55, 70}, // outer
    {4, 55, 75},
    {1, 55, 65},
    {11, 65, 80}, // outer
    {5, 95, 80} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown1()
{
  int servoGroupArr[][3] = {
    {10, 85, 65},
    {7, 90, 70},
    {2, 120, 105},
    {8, 70, 85},
    {4, 75, 95},
    {1, 65, 80},
    {11, 80, 95},
    {5, 80, 65}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltUp1()
{
  int servoGroupArr[][3] = {
    {10, 85, 55},
    {7, 70, 50},
    {2, 105, 90},
    {8, 85, 100},
    {4, 95, 115},
    {1, 80, 100},
    {11, 95, 110},
    {5, 65, 50}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltUp2()
{
  int servoGroupArr[][3] = {
    {10, 55, 35},
    {7, 50, 25},
    {2, 90, 70},
    {8, 100, 115},
    {4, 115, 135},
    {1, 100, 115},
    {11, 110, 125},
    {5, 50, 35}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}