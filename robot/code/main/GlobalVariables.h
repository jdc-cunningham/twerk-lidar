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
int servoMotionDelay = 8; // ms
int stepDelay = 0; // ms usually a second or more

// these positions are for a >= quad stance (top view)
struct {
  int start = 105;
  int current = 105;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontRightOuterServoInfo;

struct {
  int start = 80;
  int current = 80;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontRightMiddleServoInfo;

struct {
  int start = 70;
  int current = 70;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontRightInnerServoInfo;

struct {
  int start = 67;
  int current = 67;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backRightOuterServoInfo;

struct {
  int start = 90;
  int current = 90;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backRightMiddleServoInfo;

struct {
  int start = 80;
  int current = 80;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backRightInnerServoInfo;

struct {
  int start = 85;
  int current = 85;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontLeftOuterServoInfo;

struct {
  int start = 80;
  int current = 80;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontLeftMiddleServoInfo;

struct {
  int start = 30;
  int current = 30;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontLeftInnerServoInfo;

struct {
  int start = 95;
  int current = 95;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backLeftOuterServoInfo;

struct {
  int start = 75;
  int current = 75;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backLeftMiddleServoInfo;

struct {
  int start = 125;
  int current = 125;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backLeftInnerServoInfo;

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
