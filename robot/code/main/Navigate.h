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
    performFullScan(false);
    setAndCenterServos();

    // check
    // upper set, all have at least 12" check
    // d2 lowest scan, > 5, good, else turn

    if (obstacleFound)
    {
      turnLeft();
      setAndCenterServos(); // call this because after servo upgrade legs don't line up
      obstacleFound = false;
    } else
    {

    }

    moveForward5();
    prevActionWasTurn = false;
  }
}