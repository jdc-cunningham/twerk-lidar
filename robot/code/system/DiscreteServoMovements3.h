// tr means turn right, this partial motion
// is part of that larger motion
void trMoveForward()
{
  int servoGroupArr[][3] = {
    {6, 30, 60},
    {9, 125, 155},
    {3, 80, 50},
    {0, 125, 95},
    {2, 95, 105}
  };

  moveServos(servoGroupArr, 5, servoMotionDelay);
}

void switchToRightDefaultStance()
{
  // tilt towards back-left
  // move forward right leg 2x, back down
  // sway forward so left leg front leg is perpendicular with x-axis
  // move back-left leg forward so it is also perpendicular to x-axis
  mf5MoveBackLeftLegUp();
  mf5MoveFrontRightLegForwardTwice();
  mf5MoveBackLeftLegDownFromUp();
  trMoveForward();
  mf5MoveBackLeftLegUp();
  mf5MoveBackLeftLegForward();
  mf5MoveBackLeftLegDownFromUp();
}

void frontRightLegUp()
{
  int servoGroupArr[][3] = {
    {7, 80, 120} // front right middle
  };

  moveServos(servoGroupArr, 1, servoMotionDelay);
}

void rightTurnPivot()
{
  int servoGroupArr[][3] = {
    {6, 30, 0},
    {9, 125, 95},
    {3, 80, 50},
    {0, 70, 100}
  };

  moveServos(servoGroupArr, 4, servoMotionDelay);
}