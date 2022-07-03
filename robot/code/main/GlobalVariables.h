#include <Servo.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>

// Servo frontRightOuterServo;
// Servo frontRightMiddleServo;
// Servo frontRightInnerServo;
// Servo backRightOuterServo;
// Servo backRightMiddleServo;
// Servo backRightInnerServo;
// Servo frontLeftOuterServo;
// Servo frontLeftMiddleServo;
// Servo frontLeftInnerServo;
// Servo backLeftOuterServo;
// Servo backLeftMiddleServo;
// Servo backLeftInnerServo;

bool motionInProgress = false;
int servoMotionDelay = 8; // ms
int stepDelay = 0; // ms usually a second or more

// these positions are for a >= quad stance (top view)
struct leg {
  Servo servo;
  int startPos;
  int currentPos;
  int maxDeg; // later determined based on geometry
  int minDeg; // later determined based on geometry
};

struct
{
  Servo servo;
  int start = 105;
  int current = 105;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontRightOuterServo;

struct
{
  Servo servo;
  int start = 80;
  int current = 80;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontRightMiddleServo;

struct
{
  Servo servo;
  int start = 70;
  int current = 70;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontRightInnerServo;

struct
{
  Servo servo;
  int start = 67;
  int current = 67;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backRightOuterServo;

struct
{
  Servo servo;
  int start = 90;
  int current = 90;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backRightMiddleServo;

struct
{
  Servo servo;
  int start = 80;
  int current = 80;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backRightInnerServo;

struct
{
  Servo servo;
  int start = 85;
  int current = 85;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontLeftOuterServoInfo;

struct
{
  Servo servo;
  int start = 80;
  int current = 80;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontLeftMiddleServo;

struct
{
  Servo servo;
  int start = 30;
  int current = 30;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} frontLeftInnerServo;

struct
{
  Servo servo;
  int start = 95;
  int current = 95;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backLeftOuterServo;

struct
{
  Servo servo;
  int start = 75;
  int current = 75;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backLeftMiddleServo;

struct
{
  Servo servo;
  int start = 125;
  int current = 125;
  int max = 180; // later determined based on geometry
  int min = 0; // later determined based on geometry
} backLeftInnerServo;

std::map<int, struct> structMap = {};

structMap[0] = frontRightInnerServo;

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
