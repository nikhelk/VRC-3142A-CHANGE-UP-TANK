#pragma once

/**
 * struct Dimensions
 * Used for setting dimension values for chassis
 * (see ChassisSystems/chassisGlobals.h for impl)
 */

struct Dimensions
{
  long double m_trackWidth;
  long double m_wheelRadius;
  long double ticksToDegrees;

  /**
   * Initializes dimensions for 4 motor drive
   * @param trackWidth width of drive
   * @param wheelRadius radius of  wheels on drive
   */
  Dimensions( const long double trackWidth,  const long double wheelRadius, const long double ticksToDegrees);
  Dimensions() {}
};

/**
 * struct Limits
 * Used for setting max kinematic values for chassis
 * (see ChassisSystems/chassisGlobals.h for impl)
 */

class Limits
{
  public:
    long double m_maxVelocity;
    long double m_maxAcceleration;

    /**
    * Initializes kinematic limits for 4 motor drive
    * @param maxVelocity of drive (m/sec)
    * @param maxAcceleration of drive (m/sec^2)
    */
    Limits(  long double maxVelocity,   long double maxAcceleration);
    Limits() {}

};
