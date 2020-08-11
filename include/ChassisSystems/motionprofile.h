#pragma once
#include <string>

struct TrapezoidalMotionProfile {
double m_accelTime;
double m_coastTime;
double m_decelTime;
double m_totalTime;
double m_distanceAccel;
double m_distanceCoast;
double m_distanceDecel;
double m_distanceTotal;
double m_maxVel;
double m_maxAcc;



/**
 * Initilizes TrapezoidalMotionProfile with constraints
 * @param max Velocity
 * @param max acceleration
 * @param distance desired
 */

TrapezoidalMotionProfile(const double maxVel, const double maxAcc,const double distance);

/**
 * calculates velocity at a given t
 * @param time for velocity to be calculated
 * @return velocity at the given time
 */


double calculateMpVelocity(const double t);

/**
 * calculates acceleration at a given t
 * @param time for acceleration to be calculated
 * @return acceleration at the given time
 */

double calculateMpAcceleration(const double t);

/**
 * gives profile status at a given t
 * @param time for status to be given
 * @return status at the given time (accelerating, coasting, decelerating)
 */

std::string getMpStatus(const double t);

};

struct Feedfoward {
  double kV;
  double kA;
  Feedfoward(double kV, double kA);
};