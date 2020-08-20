#pragma once


struct Dimensions
{
  long double m_trackWidth;
  long double m_wheelRadius;

  /**
   * Initilizes dimensions for 4 motor drive
   * @param trackWidth width of drive
   * @param wheelRadius radius of  wheels on drive
   */
  Dimensions(long double trackWidth, long double wheelRadius);
};

struct Limits
{
  long double m_maxVelocity;
  long double m_maxAcceleration;

  /**
   * Initilizes kinematic limits for 4 motor drive
   * @param maxVelocity of drive (inches/sec)
   * @param maxAcceleration of drive (inches/sec^2)
   */
  Limits(long double maxVelocity, long double maxAcceleration);

};