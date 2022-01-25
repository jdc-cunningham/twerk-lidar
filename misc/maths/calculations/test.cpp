#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// that math on this page is based on this site
// https://www.allaboutcircuits.com/technical-articles/how-to-interpret-IMU-sensor-data-dead-reckoning-rotation-matrix-creation

std::vector<double> getNormalizedVector(double aX, double aY, double aZ)
{
  double sqrtSquaredSum = sqrt(pow(aX, 2) + pow(aY, 2) + pow(aZ, 2));
  std::vector<double> normalizedVector = {aX / sqrtSquaredSum, aY / sqrtSquaredSum, aZ / sqrtSquaredSum};

  return normalizedVector;
}

std::vector< vector<double> > getRotatedMatrix(double aX, double aY, double aZ)
{
  double squaredSet = (pow(aX, 2) + pow(aY, 2));
  std::cout << aX << "," << aY << "," << aZ << "\n";
  std::vector< std::vector<double> > rotatedMatrix = {
    {((pow(aY, 2) * (-1 * pow(aX, 2)) * aZ / squaredSet), (((-1 * aX) * aY) - (-1 * aX * aY * aZ)) / squaredSet), aX},
    {((-1 * aX * aY) - (aX * aY * aZ)) / squaredSet,  ((pow(aX, 2) - (pow(aY, 2) * aZ)) / squaredSet, aY)},
    {-aX, -aY, -aZ}
  };

  return rotatedMatrix;
}

// use struct matrix{ double cell[3][3]; };
// matrix thing = {}
// double bar = foo.cell[5][7];

int main()
{
  // uncalibrated values: ax, ay, az, gx, gy, gz, mx, my, myz
  double exampleImuReading[] = {-0.23, 5.51, -8.68, 0.03, -0.04, 0.02, 13.53, -9.70, -32.44};
  std::vector<double> result = getNormalizedVector(exampleImuReading[0], exampleImuReading[1], exampleImuReading[2]);
  std::vector< std::vector<double> > matrix = getRotatedMatrix(result[0], result[1], result[2]);
  std::cout << matrix[0][0] << "," << matrix[0][1] << "," << matrix[0][2] << "\n";
  std::cout << matrix[1][0] << "," << matrix[1][1] << "," << matrix[1][2] << "\n";
  std::cout << matrix[2][0] << "," << matrix[2][1] << "," << matrix[2][2];
}
