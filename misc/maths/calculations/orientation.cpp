#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// the math described here is from this matlab video:
// https://www.youtube.com/watch?v=0rlvvYgmTvI
// math from here https://www.mathsisfun.com/algebra/vectors-cross-product.html

float getVectorMagnitude(float x, float y, float z)
{
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

std::vector<float> getCrossProduct(float aX, float aY, float aZ, float bX, float bY, float bZ)
{
  float cX = aY * bZ - aZ * bY;
  float cY = aZ * bX - aX * bZ;
  float cZ = aX * bY - aY * bX;

  return {cX, cY, cZ};
}

float getMaxElement(std::vector<float> originalVector)
{
  std::vector<float> allPosVals = {0, 0, 0};

  // this is crap I know
  for (int i = 0; i < 3; i++)
  {
   if (originalVector[i] < 0)
   {
     allPosVals[i] = originalVector[i] * -1;
   } else
   {
     allPosVals[i] = originalVector[i];
   }
  }

  float largestVal = 0.0;
  int largestValIndex = 0;

  for (int i = 0; i < 3; i++)
  {
    if (allPosVals[i] > largestVal)
    {
      largestVal = allPosVals[i];
      largestValIndex = i;
    }
  }

  return originalVector[largestValIndex];
}

int main()
{
  std::vector<vector<float>> imuSample = {
    {-0.76, -1.16, -9.92},
    {0.03, -0.04, 0.01},
    {-19.15, 10.40, -11.38}
  };

  float down = getMaxElement(imuSample[0]);
  std::vector<float> east = getCrossProduct(imuSample[0][0], imuSample[0][1], imuSample[0][2], imuSample[2][0], imuSample[2][1], imuSample[2][2]);
  std::vector<float> north = getCrossProduct(east[0], east[1], east[2], imuSample[0][0], imuSample[0][1], imuSample[0][2]);

  std::cout << 0 << "," << 0 << "," << down << "\n";
  std::cout << east[0] << "," << east[1] << "," << east[2] << "\n";
  std::cout << north[0] << "," << north[1] << "," << north[2] << "\n";
}