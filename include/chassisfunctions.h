#pragma once
#include "vex.h"

void driveStraight(double targetDistance);
void turnToDegree(double angle);
void setDrive(double leftVoltage,double rightVoltage);
void setVelDrive(double leftVelocity,double rightVelocity);
void moveToPoint(const double x, const double y,bool backwards = false,long offset = 0);
void turnToAbsAngle(const double deg);
void driveArc( const double angle,double radius);
void driveArc2( const double angle,double radius);
void driveArc3( const double angle,double radius);
void driveArc4( const double x,const double y,double angle);
void driveArc5(const double left, const double right);
void moveToPointArc(const double x, const double y, const double theta);
void driveStraightFeedforward(const double distance);
void driveArcSortaWorks( const double angle,double radius);