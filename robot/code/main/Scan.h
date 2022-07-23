#include "ScanHelpers.h"

/**
 * @brief runCount is referring to which sweep is running
 * there are three: top, middle, bottom
 * the count determines where the robot is pointing (left/right)
 * and this is important to not jump positions and not scan the same place
 * if you were to return to the middle everytime
 * 
 * @param {int} runCount 
 * @param {bool} scan - means no sampling/fast
 */
void sweep(int runCount, bool scan = false, String scanType = "")
{
  bool useSerial = dumpSerial; // true means it goes to monitor for manual copy/paste capture
  activeScan = scanType;

  if (runCount == 1)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotRight();
    pivotCenterFromRight();
    pivotLeft();
    sampleDepth = false;
    sampleGyroZ = false;
    dumpData(useSerial, scanType);
  } else if (runCount == 2)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotCenterFromLeft();
    pivotRight();
    sampleDepth = false;
    sampleGyroZ = false;
    dumpData(useSerial, scanType);
  } else
  {
    if (scan)
    {
      sampleDepth = true;
      sampleGyroZ = true;
    }

    pivotCenterFromRight();
    pivotLeft();
    pivotCenterFromLeft();

    if (scan)
    {
      sampleDepth = false;
      sampleGyroZ = false;
      dumpData(useSerial, scanType);
    }
  }

  // performObstacleCheck(scanType); // needs to be reworked
}

void performFullScan(bool addDelayBetweenSamples = false)
{
  // this slows down the robot a lot, each sensor probe takes 20-30ms
  // it's not used for walking, you can use IMU while walking that does not take 20-30ms to get

  bool printData = dumpSerial; // to serial monitor
  tiltUp1();
  tiltUp2();
  delay(1000); // wait to stop moving

  performScan = true; // so moveServos gather samples from the sensors
  sweep(1, true, printData ? "" : "tilt-up-2"); // second param means no delay
  performScan = false;

  if (addDelayBetweenSamples)
  {
    delay(10000); // for manual serial dump copy paste into excel
  }

  tiltCenterFromUp2();
  delay(1000); // wait to stop moving

  performScan = true;
  sweep(2, true, printData ? "" : "tilt-up-1");
  performScan = false;

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltCenterFromUp1();
  delay(1000); // wait to stop moving

  performScan = true;
  sweep(3, true, printData ? "" : "middle");
  performScan = false;

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltDown1();
  delay(1000); // wait to stop moving
  performScan = true;
  sweep(1, true, printData ? "" : "tilt-down-1");
  performScan = false;

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltDown2();
  delay(1000); // wait to stop moving

  performScan = true;
  sweep(2, true, printData ? "" : "tilt-down-2");
  performScan = false;

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltCenterFromDown2();
  tiltCenterFromDown1();

  sweep(3, false);
}