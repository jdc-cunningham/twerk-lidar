#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// that math on this page is based on this site
// https://www.allaboutcircuits.com/technical-articles/how-to-interpret-IMU-sensor-data-dead-reckoning-rotation-matrix-creation

std::vector<double> getNormalizedVector(double aX, double aY, double aZ)
{
  int sqrtSquaredSum = sqrt(pow(aX, 2) + pow(aY, 2) + pow(aZ, 2));
  std::vector<double> normalizedVector = {aX / sqrtSquaredSum, aY / sqrtSquaredSum, aZ / sqrtSquaredSum};

  return normalizedVector;
}

int main()
{
  // uncalibrated values: ax, ay, az, gx, gy, gz, mx, my, myz
  double exampleImuReading[] = {-0.23, 5.51, -8.68, 0.03, -0.04, 0.02, 13.53, -9.70, -32.44};
  std::vector<double> result = getNormalizedVector(exampleImuReading[0], exampleImuReading[1], exampleImuReading[2]);
  std::cout << result[0] << "," << result[1] << "," << result[2];
}
