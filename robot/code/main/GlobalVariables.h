#include <Servo.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>

bool motionInProgress = false;
int servoMotionDelay = 8; // ms
int stepDelay = 0; // ms usually a second or more

// these positions are for a >= quad stance (top view)
struct joint {
  int startPos;
  int currentPos;
  int minPos; // later determined based on geometry
  int maxPos; // later determined based on geometry
  Servo servo; // last due to order of agg init
};

joint frontRightInnerJoint = {70, 70, 0, 180};
joint frontRightMiddleJoint = {80, 80, 0, 180};
joint frontRightOuterJoint = {105, 105, 0, 180};
joint backRightInnerJoint = {80, 80, 0, 180};
joint backRightMiddleJoint = {90, 90, 0, 180};
joint backRightOuterJoint = {67, 67, 0, 180};
joint backLeftInnerJoint = {125, 125, 0, 180};
joint backLeftMiddleJoint = {75, 75, 0, 180};
joint backLeftOuterJoint = {95, 95, 0, 180};
joint frontLeftInnerJoint = {30, 30, 0, 180};
joint frontLeftMiddleJoint = {80, 80, 0, 180};
joint frontLeftOuterJoint = {85, 85, 0, 180};

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
float u1 = 13.1;
float u2 = 18.7;
float d1 = -6.7;
float d2 = -15.9;

// sweep angles
float sweepRightMax = 18.7; // 19.3
float sweepLeftMax = 16.5; // 15.2, don't match lol

float robotHeading = 0;
float robotDistance = 0;
