// probably duplicate file but import issues

void navigate()
{
  /*
   * there is a minimum 3" clearance from the sensor plate so the robot can still turn
   * the robot moves 2" forward for one walk gait cycle
   * the ToF sensor is used for anything <= 12" distance away
   * the lidar is for long distance eg. 16" or greater
   * ToF 25deg FOV
   * TFmini-S 2-3deg FOV
   * 
   * the lowest scan, has the closest scan even in open space, less than 5" away 
   */

  // scan far ahead first, short-circuit immediate scan
  float tofScan = getTofDistanceCorrected();
  float lidarScan = getTFminiSDistance();

  if (tofScan < 5 || lidarScan < 5 || (prevActionWasTurn && tofScan < 6) || (prevActionWasTurn && lidarScan < 6))
  {
    turnLeft();
    prevActionWasTurn = true; // this is because if you turn once, you may have to turn again in the case of a wall
  } else
  {
    // do scan
    performFullScan(false); // writes distance samples to data store while moving
    setAndCenterServos();

    // check
    // upper set, all have at least 12" check
    // d2 lowest scan, > 5, good, else turn

    if ((obstacleFound && forwardGaitCount == 0) || d2Smallest <= 5)
    {
      turnLeft();
      prevActionWasTurn = true;
      setAndCenterServos(); // call this because after servo upgrade legs don't line up
    }
    else
    {
      // ignoring sky
      // if (u2Smallest > d1Smallest && u1Smallest > d1Smallest && mSmallest > d1Smallest)
      // {
      //   forwardGaitCount = (d1Smallest - 3) / 2; // tried modulus at first
      // }

      forwardGaitCount = (d1Smallest - 3) / 2;

      for (int i = 0; i < forwardGaitCount; i++)
      {
        moveForward5();
        setAndCenterServos();
      }
    }
  }

  prevActionWasTurn = false;
  forwardGaitCount = 0;
  obstacleFound = false;
  u2Smallest = 0.0; // dumb
  u1Smallest = 0.0;
  mSmallest = 0.0;
  d1Smallest = 0.0;
  d2Smallest = 0.0;
}