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

std::vector<std::vector <float>> getNed(bool flipGravity = false)
{
  if (imu.Read())
  {
    std::vector<std::vector <float>> imuSample = {
      {imu.accel_x_mps2(), imu.accel_y_mps2(), (flipGravity ? (imu.accel_z_mps2() * -1) : imu.accel_z_mps2())},
      {imu.gyro_x_radps(), imu.gyro_y_radps(), imu.gyro_z_radps()},
      {imu.mag_x_ut(), imu.mag_y_ut(), imu.mag_z_ut()}
    };

    float down = getMaxElement(imuSample[0]);
    std::vector<float> east = getCrossProduct(imuSample[0][0], imuSample[0][1], imuSample[0][2], imuSample[2][0], imuSample[2][1], imuSample[2][2]);
    std::vector<float> north = getCrossProduct(east[0], east[1], east[2], imuSample[0][0], imuSample[0][1], imuSample[0][2]);

    return {
      {north[0], north[1], north[2]},
      {east[0], east[1], east[2]},
      {0, 0, down}
    };
  } else
  {
    return {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
    };
  }
}