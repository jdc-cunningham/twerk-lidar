/**
 * top view of robot and servo names
 * FLO = front-left-outer
 * 
 *    FLO                          FRO
 *         FLM                 FRM
 *              FLI  TOF  FRI
 *                    ^
 *                    y
 * 
 *                   (z)  x >
 *                   IMU
 *
 * 
 *
 *              BLI       BRI
 *         BLM                 BRM
 *    BLO                           BRO
 */

#include "BlueLed.h"
#include "ToFSensor.h"
#include "IMU.h"
#include "ServoMovements.h"
#include "Misc.h"
#include "EspSerial.h"
#include "WorldNavigation.h"
#include "Orientation.h"

float levelGravityVal;

void setup()
{
  Serial.begin(115200);
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setAndCenterServos();
  setupEspSerial();
  setupTof();
  setupImu();
  
  delay(10000);

  // performFullScan();

  // delay(10000);

  // tiltUp1();
  // delay(2000);
  // tiltUp2();
  // delay(2000);
  // tiltCenterFromUp2();
  // delay(2000);
  // tiltCenterFromUp1();
  // delay(2000);
  // tiltDown1();
  // delay(2000);
  // tiltDown2();
  // delay(2000);
  // tiltCenterFromDown2();
  // delay(2000);
  // tiltCenterFromDown1();

  // delay(1000); // wait to stop moving

  // std::vector<std::vector <float>> imuNed = getNed(true);

  // Serial.println(imuNed[0][0]);
  // Serial.println(imuNed[0][1]);
  // Serial.println(imuNed[0][2]);

  // Serial.println(imuNed[1][0]);
  // Serial.println(imuNed[1][1]);
  // Serial.println(imuNed[1][2]);

  // Serial.println(imuNed[2][0]);
  // Serial.println(imuNed[2][1]);
  // Serial.println(imuNed[2][2]);
}

void loop()
{
  
}