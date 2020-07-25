#pragma once
#include "vex.h"

int sgn(float num);
typedef struct distanceAndAngle_t
{
	float length;
	float theta;
} distanceAndAngle;

typedef struct _pos
{
	double a;
	double y;
	double x;
	int leftLst;
	int rightLst;
	int backLst;
  double angleLst;
} sPos; // Position of the robot


void computeDistanceAndAngleToPoint(const long x, const long y, distanceAndAngle *out);
int trackPosition();
const double encoderToInch = 28.6479;
double toDegrees(double angle);
double toRadians(double angle);
//POSITION TRACKING

extern double test2;
#define WHEEL_DIAMETER_IN_LR 4.0 // 2.843
#define WHEEL_DIAMETER_IN_S 4.0 // 2.843

// The distance between the tracking wheels and the centre of the robot in inches
#define L_DISTANCE_IN 7.0//6.8198
#define R_DISTANCE_IN 7.0 //6.8198
#define S_DISTANCE_IN 8.0

// The number of tick per rotation of the tracking wheel
#define TICKS_PER_ROTATION 360.0

// Used internally by trackPosition
#define SPIN_TO_IN_LR (WHEEL_DIAMETER_IN_LR * M_PI / TICKS_PER_ROTATION)
#define SPIN_TO_IN_S (WHEEL_DIAMETER_IN_S * M_PI / TICKS_PER_ROTATION)

enum positionVals {
  ODOM_X,
  ODOM_Y,
  ODOM_THETA,
};
extern double positionArray[3];
void setOdomOrigin(double x, double y, double a);
int trackPosition2();
void printPosition();
int trackPositionGyro();
extern float thetaDegrees;

double cosDegrees(double value);
double sinDigrees(double value);

