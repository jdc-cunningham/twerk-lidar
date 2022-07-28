#include <Servo.h>
#include <math.h>
#include <map>
#include <vector>

bool motionInProgress = false;
int servoMotionDelay = 4; // ms - the higher this number, the slower the robot moves, 4 is normal speed
int stepDelay = 0; // ms usually a second or more

// these positions are for a >= quad stance (top view)
struct joint {
  int startPos;
  int currentPos;
  int minPos; // later determined based on geometry
  int maxPos; // later determined based on geometry
  Servo servo; // last due to order of agg init
};

// should follow clockwise but it does not
joint frontRightInnerJoint = {70, 70, 45, 160};       // 0
joint frontRightMiddleJoint = {80, 80, 40, 180};      // 1
joint frontRightOuterJoint = {105, 105, 50, 160};     // 2
joint backRightInnerJoint = {80, 80, 0, 110};         // 3
joint backRightMiddleJoint = {90, 90, 0, 140};        // 4
joint backRightOuterJoint = {67, 67, 15, 130};        // 5
joint frontLeftInnerJoint = {30, 30, 0, 100};         // 6
joint frontLeftMiddleJoint = {70, 70, 40, 160};       // 7
joint frontLeftOuterJoint = {95, 95, 0, 180};         // 8
joint backLeftInnerJoint = {125, 125, 60, 180};       // 9
joint backLeftMiddleJoint = {95, 95, 30, 180};        // 10
joint backLeftOuterJoint = {85, 85, 70, 140};         // 11

bool sampleDepth = false;
bool sampleGyroZ = false; // yaw
bool sampleGyroX = false; // pitch
bool sampleYAccel = false;
bool sampleXAccel = false;

bool movedForward = true;
bool stopRobot = false;

// these use time from millis() as a shared key to sync the data
std::map<int, float> gyroVals = {};
std::map<int, int> servoPosVals = {};
std::map<int, float> depthVals = {};
std::map<int, float> xAccelVals = {};
std::map<int, float> yAccelVals = {};
std::vector<int> posErrVals;

// used to avoid buffer buildup between ESP and web communication delay
String curEspMsg = "";

// used for performFullScan
int forwardGaitCount = 0;

// tilt angles
float u1 = 18.7;
float u2 = 9.8;
float c1 = 2; // assumed 0 but it's not
float d1 = -8.4;
float d2 = -17.6;

// sweep angles
float sweepRightMax = 18.7; // 19.3
float sweepLeftMax = 16.5; // 15.2, don't match lol
// rest of angles in recent devlog

float robotHeading = 0;
float robotDistance = 0;

float lidarSensorDistanceFromCenter = 3.38;
float lidarSensorDistanceFromFloor = 3.75;

float tofSensorDistanceFromCenter = 2.78;
float tofSensorDistanceFromFloor = 3.125;

// this means data from the scan is sent to the monitor
// usually to be copied/pasted into a spreadsheet manually
bool dumpSerial = false;

bool performScan = false;

// these store the pan/tilt values for transmission
String activeScan = "";
// std::map<std::string, std::map<int, float, float, float>> scanSampleValues = {};
// I'm casting servo pos to float nasty, guess it's fine tested in C++ shell
// stores scan type (tilt-up-2) -> time ms -> {servoPos, gyroMeasurement, shortScan, longScan}
// change to vector, easier to use
std::map<String, std::map<int, std::vector<float>>> scanSampleValues = {};