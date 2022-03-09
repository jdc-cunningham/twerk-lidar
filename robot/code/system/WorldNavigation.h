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
float sensorToMiddleOfBody = 2.5;
float extVerRotationAngle = 37.5; // external verified
float minScanDistance = 14.62;
float imuFromFloorHeight = 3.5;
float curAngle = 0; // done in 52 increments

std::vector<float> robotWorldPos = {0, 0, 3.5};

// each walk forward step time is around 1.35s per 2" of ground covered
// leg clearance 0.78" lowest clearance

// rotation is 37.5 deg

// angles
// tilt up11 7.2
// tilt up2 15.3
// down1 6.8
// down2 16.1

// for 3D collision check
std::vector<std::vector <float>> robotCube = {
  {0, 0, 0},
  {10, 0, 0},
  {10, 10, 0},
  {0, 0, 10},
  {0, 10, 0},
  {10, 10, 0},
  {0, 10, 10},
  {10, 10, 10}
};

// what is being compared?
// 3D locations and cubes
bool collisionCheck(std::vector<std::vector <float>>)
{
  return false;
}

void initRobotPos()
{

}