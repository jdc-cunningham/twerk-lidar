#ifndef MATH_H
#include <math.h>
#endif

#include <vector>

// this is a basic distance scanner
// not factoring in IMU yet or other info

// min distances
// d2 - 12"
// d1 - 20.86" (if this is clear means can move forward 4 more steps eg. 8")
// the rest are the same at least 12" means can move forward 5 times
// if there is intent to turn only move forward 4 times maybe 3 to give space for the turning radius

/**
 * @brief returns number of steps forward
 * if 0 it should turn
 * 
 * @param depthVals - time:depth ToF pair
 * @param scanType - eg. u2, u1, m1, d1, d2
 * @return int - number of forward gaits to perform based on depth scan
 */
int parseScanData(std::map<int, float> depthVals, String scanType)
{
  float smallestMeasurement = 0;

  // check for smallest value
  // add to error collection (too close)
  for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
  {
    float depthVal = it->second;

    // Serial.print("depth val");
    // Serial.print(depthVal);
    // Serial.println("");

    if (smallestMeasurement == 0)
    {
      smallestMeasurement = depthVal;
    }

    if (
      smallestMeasurement > 0 and
      depthVal > 0 and
      depthVal < smallestMeasurement
    ) {
      smallestMeasurement = depthVal;
    }

    if (depthVal <= 4) // probably bad sensor value or too close to something/need to turn
    {
      posErrVals.push_back(depthVal);
    }
  }

  if (scanType == "d2")
  {
    if (smallestMeasurement >= 11) {
      return 7;
    } else {
      return floor(smallestMeasurement / 2);
    }
  } else if (scanType == "d1")
  {
    if (smallestMeasurement >= 18)
    {
      return 4; // added ontop of 5 above
    } else
    {
      return floor(smallestMeasurement / 2);
    }
  // here the top-most scan u2 takes precedence, and u1 matches it, this is overhead clearance
  // the robot is 8" tall primarily due to the servo wires
  } else if (scanType == "m1")
  {
    if (smallestMeasurement >= 18)
    {
      return 7;
    } else
    {
      return floor(smallestMeasurement / 2);
    }
  } else {
    if (smallestMeasurement >= 18)
    {
      return 7;
    } else
    {
      return floor(smallestMeasurement / 2);
    }
  }
}

void performObstacleCheck(String scanType)
{
  // do obstacle detection check
  if (scanType == "d1")
  {
    // reset back to min, top scans run first
    int d1GaitCount = parseScanData(depthVals, "d1");

    if (d1GaitCount < 4) {
      forwardGaitCount = d1GaitCount;
    }
  }

  if (scanType == "d2")
  {
    forwardGaitCount = parseScanData(depthVals, "d2");
  }

  // repeated code
  if (scanType == "m1")
  {
    forwardGaitCount = parseScanData(depthVals, "m1");
  }

  if (scanType == "u1")
  {
    forwardGaitCount = parseScanData(depthVals, "u1");
  }

  if (scanType == "u2")
  {
    forwardGaitCount = parseScanData(depthVals, "u2");
  }

  gyroVals = {};
  depthVals = {};
  posErrVals = {};
}
