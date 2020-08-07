#pragma once 
#include "vex.h"
#include "pid.h"


/* 
* Header file with all the global classes (motors, sensors) and other applications such as PID and Motion Profiling
*
* @author Nikhel Krishna, 3142A

*/


class Dimensions {
private:

public:
long double m_trackWidth ;
long double m_wheelRadius;

    /**
     * Initilizes dimensions for 4 motor drive
     * @param four motor drive to add dimensions to
     * @param track width of drive
     * @param wheel radius of drive
     */
    Dimensions( long double trackWidth, long double wheelRadius);
};

class Limits {
private:

public:
long double m_maxVelocity;
    long double m_maxAcceleration;
    /**
     * Initilizes kinematic limits for 4 motor drive
     * @param four motor drive to add limits to
     * @param max Velocity of drive (inches/sec)
     * @param max Acceleration of drive (inches/sec^2)
     */
    Limits(long double maxVelocity, long double maxAcceleration);
    
  //void setGearRatio(double ratio);
  //double getGearRatio() {return(gearRatio);}
  //void setReverseSettings(std::vector<bool> LeftReverseVals, std::vector<bool> RightReverseVals);
};
class FourMotorDrive {
private:

vex::gearSetting setting;
public:
Dimensions m_chassisDimensions;
Limits m_chassisLimits;
  enum backOrFront {
    FRONT,
    BACK,
  };
  posPID distancePID;
  posPID anglePID;
  posPID turnPID;
    double trackWidth;
    double wheelRadius;
    double gearRatio;
    double maxVelocity;
    double maxAcceleration;
    motor leftFront;
    motor rightFront;
    motor leftBack;
    motor rightBack;
    
    /**
     * Initilizes 4 motor drive
     * @param vector of left motor ports (front,back)
     * @param vector of right motor ports (front,back)
     * @param gear cartridge
     * @param gear ratio
     * @param chassis dimensions (trackWidth and wheel size)
     * @param chassis limits (max velocity and acceleration)
     * @param PD Controller chassis parameters
     */

    FourMotorDrive( std::vector<int32_t> leftGroup, 
    std::vector<int32_t> rightGroup,
    vex::gearSetting setting,double gearRatio, Dimensions chassisDimensions,Limits chassisLimits,std::initializer_list<PDcontroller> PDGains);



    /**
     * Handles the reversal of motors.
     * @param LeftReverseVals boolean array of leftFront and leftBack desired reversal states
     * @param RightReverseVals boolean array of rightFront and rightBack desired reversal states
     */

  void setReverseSettings(std::vector<bool> LeftReverseVals,std::vector<bool> RightReverseVals);

  long double getTrackWidth() {
    return(m_chassisDimensions.m_trackWidth);
  }
  long double getWheelRadius() {
    return(m_chassisDimensions.m_wheelRadius);
  }
  long double getMaxVelocity() {
    return(m_chassisLimits.m_maxVelocity);
  }
  long double getMaxAcceleration() {
    return(m_chassisLimits.m_maxAcceleration);
  }

  /**
   * sets the chassis to drive at a voltage
   * @param the desired left side voltage of chassis
   * @param the desired right side voltage of chassis
   */

  void setVoltDrive(double leftVoltage,double rightVoltage);

  /**
   * sets the chassis to drive at a velocity 
   * @param the desired left side velocity
   * @param the desired right side velocity
   * @param the desired units of velocity (dps, rpm)
   */

  void setVelocityDrive(double leftVelocity, double rightVelocity, velocityUnits vel);

  void turnToDegreeGyro(double degree);

  void driveStraight(const double distance);
  void turnToDegree(double angle);
  void setDrive(double leftVoltage,double rightVoltage);
  void setVelDrive(double leftVelocity,double rightVelocity);
  void moveToPoint(const double x, const double y,bool backwards = false);
  void turnToAbsAngle(const double deg);
  void driveArc( const double angle,double radius);
  void driveArc2( const double angle,double radius);
  void driveArc3( const double angle,double radius);
  void driveArc4( const double x,const double y,double angle);
  void driveArc5(const double left, const double right);
  void moveToPointArc(const double x, const double y, const double theta);
  void driveStraightFeedforward(const double distance);
  void driveArcSortaWorks( const double angle,double radius);
  double getAverageEncoderValueMotors();
  
}; 




class WheelDistances{
  public:
    double R_DISTANCE;
    double L_DISTANCE;
    double B_DISTANCE;

};

class Tracking {
private:
  double gearRatio;
  
  vex::gearSetting gearCart;
public:


  enum trackingWheelID {
    LEFT_ENCODER,
    RIGHT_ENCODER,
    BACK_ENCODER,
  };

  enum trackType {
    THREE_ENCODER_MODEL,
    IME_ENCODER_MODEL
  };

  enum triportIndex {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
  };
    brain brained;
    double trackWidth;
    double wheelRadius;
    double backDistance;
    double ticksPerRev;
    double maxVelocity;
    double maxAcceleration;
    WheelDistances m_odomImpl;
    encoder rightEncoder;
    encoder leftEncoder;
    encoder backEncoder;
    inertial inert;
    
    /**
     * Constructor for 3 encoder model
     * @param trackWidth of encoder model
     * @param distance from tracking center to the back encoder
     * @param encoder wheel radius
     * @param encoder ticks per revolution
     * @param list of triports (in order of left, right, back)
     * @param gyroport (if any)
     */

    Tracking(WheelDistances wheels, double wheelRadius,std::vector<triportIndex> enocoderPorts, int GyroPort = NULL, double ticksPerRev = 360.0);

    /**
     * Constructor for 2 IME  and one backEncoder model
     * @param trackWidth of encoder model
     * @param distance from tracking center to the back encoder
     * @param encoder wheel radius
     * @param encoder ticks per revolution
     * @param list of triports (in order of left, right, back)
     * @param gyroport (if any)
     */



    Tracking(FourMotorDrive drive, triportIndex backPort, int GyroPort = NULL);



    Tracking(FourMotorDrive drive, int GyroPort = NULL);
    /**
     * returns "fixed" inertial value
     * @return intertial value
     */

    double getInertialHeading();


    double getAverageEncoderValueEncoders();
};
extern Tracking poseTracker;
extern FourMotorDrive chassis;
