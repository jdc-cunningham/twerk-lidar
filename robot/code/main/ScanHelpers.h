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
    {7, 25, 50},
    {2, 70, 90},
    {8, 125, 110},
    {4, 130, 110},
    {1, 115, 100},
    {11, 115, 100},
    {5, 33, 48}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromUp1()
{
  int servoGroupArr[][3] = {
    {10, 55, 85},
    {7, 50, 70},
    {2, 90, 105},
    {8, 110, 95},
    {4, 110, 90},
    {1, 100, 80},
    {11, 100, 85},
    {5, 48, 67}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown1()
{
  int servoGroupArr[][3] = {
    {10, 85, 105},
    {7, 70, 90},
    {2, 105, 120}, // outer
    {8, 95, 80}, // outer
    {4, 90, 70},
    {1, 80, 65},
    {11, 85, 70}, // outer
    {5, 67, 82} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltDown2()
{
  int servoGroupArr[][3] = {
    {10, 105, 125},
    {7, 90, 120},
    {2, 120, 135}, // outer
    {8, 80, 65}, // outer
    {4, 70, 50},
    {1, 65, 55},
    {11, 70, 55}, // outer
    {5, 82, 97} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown2()
{
  int servoGroupArr[][3] = {
    {10, 125, 105},
    {7, 120, 90},
    {2, 135, 120}, // outer
    {8, 65, 80}, // outer
    {4, 50, 70},
    {1, 55, 65},
    {11, 55, 70}, // outer
    {5, 97, 82} // outer
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltCenterFromDown1()
{
  int servoGroupArr[][3] = {
    {10, 105, 85},
    {7, 90, 70},
    {2, 120, 105},
    {8, 80, 95},
    {4, 70, 90},
    {1, 65, 80},
    {11, 70, 85},
    {5, 82, 67}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltUp1()
{
  int servoGroupArr[][3] = {
    {10, 85, 55},
    {7, 70, 50},
    {2, 105, 90},
    {8, 95, 110},
    {4, 90, 110},
    {1, 80, 100},
    {11, 85, 100},
    {5, 67, 48}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}

void tiltUp2()
{
  int servoGroupArr[][3] = {
    {10, 55, 35},
    {7, 50, 25},
    {2, 90, 70},
    {8, 110, 125},
    {4, 110, 130},
    {1, 100, 115},
    {11, 100, 115},
    {5, 48, 33}
  };

  moveServos(servoGroupArr, 8, servoMotionDelay);
}