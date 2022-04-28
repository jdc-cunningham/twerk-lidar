#include <Servo.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>

Servo frontRightOuterServo;
Servo frontRightMiddleServo;
Servo frontRightInnerServo;
Servo backRightOuterServo;
Servo backRightMiddleServo;
Servo backRightInnerServo;
Servo frontLeftOuterServo;
Servo frontLeftMiddleServo;
Servo frontLeftInnerServo;
Servo backLeftOuterServo;
Servo backLeftMiddleServo;
Servo backLeftInnerServo;

bool motionInProgress = false;
int servoMotionDelay = 4; // default 4, min 1 ms
int stepDelay = 0; // ms usually a second or more

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

// used to avoid buffer buildup between ESP and web communication delay
String curEspMsg = "";

// used for performFullScan
int forwardGaitCount = 0;