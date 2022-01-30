#include "mpu9250.h"
#include <math.h>

bfs::Mpu9250 imu(&Wire1, 0x68);

float magXOffset = 0.0;
float magYOffset = 0.0;
float magZOffset = 0.0;

// calibration
void getMagnetometerOffset()
{
  float magXMin = 0.0;
  float magXMax = 0.0;
  float magYMin = 0.0;
  float magYMax = 0.0;
  float magZMin = 0.0;
  float magZMax = 0.0;
  
  for (int a = 0; a < 3; a++)
  {
    Serial.print("prepare to calibrate axis:");
    blueLedBlink(2);

    if (a == 0)
    {
      Serial.println("x");
    } else if (a == 1)
    {
      Serial.println("y");
    } else
    {
      Serial.println("z");
    }

    delay(5000);

    Serial.println("start rotating");
    blueLedOn();

    for (int i = 0; i < 360; i++)
    {
      // this is nasty code can be flexed by function
      if (a == 0)
      {
        float magVal = imu.mag_x_ut();
        if (magVal < 0 && magVal < magXMin)
        {
          magXMin = magVal;
        }
        if (magVal > 0 && magVal > magXMax)
        {
          magXMax = magVal;
        }
      }

      if (a == 1)
      {
        float magVal = imu.mag_y_ut();
        if (magVal < 0 && magVal < magYMin)
        {
          magYMin = magVal;
        }
        if (magVal > 0 && magVal > magYMax)
        {
          magYMax = magVal;
        }
      }

      if (a == 2)
      {
        float magVal = imu.mag_z_ut();
        if (magVal < 0 && magVal < magZMin)
        {
          magZMin = magVal;
        }
        if (magVal > 0 && magVal > magZMax)
        {
          magZMax = magVal;
        }
      }
      delay(16);
    }

    blueLedOff();
  }

  magXOffset = (magXMax - magXMin) / 2;
  magYOffset = (magYMax - magYMin) / 2;
  magZOffset = (magZMax - magZMin) / 2;

  Serial.println("Offsets found done");
}

float applyMagOffset(char axis, float magVal)
{
  float offsetMagVal = 0.0;
  float activeOffset = 0.0;

  if (axis == 'x') activeOffset = magXOffset;
  if (axis == 'y') activeOffset = magYOffset;
  if (axis == 'z') activeOffset = magZOffset;

  if (magVal < 0)
  {
    offsetMagVal = magVal + activeOffset;
  } else
  {
    offsetMagVal = magVal - activeOffset;
  }

  return offsetMagVal;
}

float radianToDegree(float rad)
{
  // return std::trunc(10000 * (rad * 57.2958)) / 10000;
  return rad * 57.2958;
}

void setupImu() {
  Serial.begin(115200);
  while(!Serial) {}
  Wire1.begin();
  Wire1.setClock(400000);
  /* Initialize and configure IMU */
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }
  /* Set the sample rate divider */
  if (!imu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }
}