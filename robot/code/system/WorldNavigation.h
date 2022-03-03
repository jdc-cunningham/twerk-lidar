#include <vector>

/**
 * units: inches, degrees
 * precision: 2 decimal places rounded up or truncated
 *
 * this file is what keeps track of the robot and its surroundings
 * the 0, 0, 0 coordinate of the robot is based on the IMU center
 * which is actually 3.31" above the ground with the current standing
 * position
 */

// counter-clockwise is positive rotation in all axes

float bodyLargestDimension = 10; // but treated as cube
float robotTofSensorHeight = 3.31;
float minDistance = 4.25; // room for legs to move forward from ToF sensor
float minScanDistance = 12.75; // one body length + minDistance
float sensorToMiddleOfBody = 2.5;
float extVerRotationAngle = 37.5; // external verified

// angles
// tilt up11 7.2
// tilt up2 15.3
// down1 6.8
// down2 16.1

// for 3D collision check
std::vector<std::vector <float>> robotCube = {
  {0, 0, 0},
  {8.5, 0, 0},
  {8.5, 8.5, 0},
  {0, 0, 8.5},
  {0, 8.5, 0},
  {8.5, 8.5, 0},
  {0, 8.5, 8.5},
  {8.5, 8.5, 8.5}
};

// what is being compared?
// 3D locations and cubes
bool collisionCheck(std::vector<std::vector <float>>)
{
  return false;
}