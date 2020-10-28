#pragma once
#include <string>

class TrapezoidalMotionProfile {
private:
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
public:
  /// WE WROTE AN EDUCATIONAL ARTICLE DETAILING THE PROCCESS OF GENERATING A TRAPEZOIDAL MOTION PROFILE
  /// <https://paideiarobotics.files.wordpress.com/2020/10/feedforward-series-chapter-two.pdf>

  /**
   * Initilizes TrapezoidalMotionProfile with constraints
   *
   * We use a trapezoidal motion profile generator for our 1D motion generator
   *
   * The user inputs wheel velcoity constraints and a distance to travelled
   *
   * Using kinematic formulas, we are able to find the position, acceleration
   * and most importantly the velocity at every timestep in the motion
   *
   * @param maxVel max Velocity
   * @param maxAcc max acceleration
   * @param distance desired distance
   */
  TrapezoidalMotionProfile(const double maxVel, const double maxAcc, const double distanceTotal);

  /**
   * calculates velocity at a given t
   * @param t time for velocity to be calculated
   * @return velocity at the given time
   */
  double calculateMpVelocity(const double t) const;

  /**
   * calculates acceleration at a given t
   * @param t time for acceleration to be calculated
   * @return acceleration at the given time
   */

  double calculateMpAcceleration(const double t) const;

  /**
   * gives profile status at a given t
   * @param t time for status to be given
   * @return status at the given time (accelerating, coasting, decelerating)
   */

  std::string getMpStatus(const double t) const;

  double getMpTotalTime() const {return(m_totalTime);}

  double getMpMaxVelocity() const {return(m_maxVel);}
};

struct Feedfoward {
  double kV;
  double kA;
  /**
   * constructs an object with feedforward values
   *
   * These feed foward constants are multplied by velocity and acceleration from
   * the motion profile to estamate the desired motor voltage
   *
   * @param kV velocity constant
   * @param kA acceleration constant
   */
  Feedfoward(double kV, double kA);
};