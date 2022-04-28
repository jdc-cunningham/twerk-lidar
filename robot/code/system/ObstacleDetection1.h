#ifndef MATH_H
#include <math.h>
#endif

#include <vector>

#include "MockData.h"

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
  Serial.print("run parse scan data ");
  Serial.print(scanType);
  Serial.println("");

  float smallestMeasurement = 0;

  for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
  {
    float depthVal = it->second;

    Serial.print("depth val");
    Serial.print(depthVal);
    Serial.println("");

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

  Serial.print("smolv ");
  Serial.print(smallestMeasurement);
  Serial.println("");

  if (scanType == "d2")
    {
      if (smallestMeasurement >= 12) {
        return 3;
      } else {
        return floor(smallestMeasurement) / 2;
      }
    } else if (scanType == "d1")
    {
      if (smallestMeasurement >= 20)
      {
        return 3; // added ontop of 5 above
      } else
      {
        return floor(smallestMeasurement) / 2;
      }
    // here the top-most scan u2 takes precedence, and u1 matches it, this is overhead clearance
    // the robot is 8" tall primarily due to the servo wires
    } else if (scanType != "m1")
    {
      if (smallestMeasurement >= 17)
      {
        return 3;
      } else
      {
        return floor(smallestMeasurement) / 2;
      }
    } else {
      if (smallestMeasurement >= 12)
      {
        return 3;
      } else
      {
        return floor(smallestMeasurement) / 2;
      }
    }
}

/**
 * @brief this is parsing through mock data
 * determin how many steps the robot would take based on fed mock depth data
 * following the map pattern used by performFullScan
 * 
 * d2, d1 have precedence, d2 can add to d1 since it scans further forward
 * m1 is just straight ahead goes on the down scans
 * u1, u2 these are capped to 12 based on d2
 */
void performMockScan()
{
  int forwardGaitCount = 0;

  forwardGaitCount = parseScanData(d1DepthValsMap, "d1");
  forwardGaitCount += parseScanData(d2DepthValsMap, "d2");
  int m1ForwardGaitCount = parseScanData(m1DepthValsMap, "m1");
  int u1ForwardGaitCount = parseScanData(u1DepthValsMap, "u1");
  int u2ForwardGaitCount = parseScanData(u2DepthValsMap, "u2");

  if (m1ForwardGaitCount < 5)
  {
    forwardGaitCount = m1ForwardGaitCount;
  }

  if (u1ForwardGaitCount < 5)
  {
    forwardGaitCount = u1ForwardGaitCount;
  }

  if (u2ForwardGaitCount < 5)
  {
    forwardGaitCount = u2ForwardGaitCount;
  }

  Serial.println(forwardGaitCount);
}