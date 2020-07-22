#pragma once
#include "vex.h"
typedef struct mp {
double accelTime; 
double decelTime;
double distanceAccel;
double distanceCoast;
double coastTime;
double distanceDecel;
double fullSpeedDist;
double maxVel;
double maxAcc;
double totalTime;
double test;
double distance;
} mp;
void generateTrapMP(const double maxVel, const double maxAcc,const double distance);
double calculateMpVelocity(const double t);
std::string getMpStatus(const double t);
