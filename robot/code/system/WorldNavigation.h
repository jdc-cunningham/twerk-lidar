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
// angles
// tilt up 1 6.7
// tilt up 2 13.5
// down 1 -8.4
// down 2 -17.3

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