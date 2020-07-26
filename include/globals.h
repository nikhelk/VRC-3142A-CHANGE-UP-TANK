#pragma once 
#include "vex.h"



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


    long double gearRatio;
    
    motor leftFront;
    motor rightFront;
    motor leftBack;
    motor rightBack;
    
    /**
    * Constructor for 4 motor drive
    * @param vector of left motor ports (front,back)
    * @param vector of right motor ports (front,back)
    * @param gear cartridge
    * @param gear ratio
    */

    FourMotorDrive( std::vector<int32_t> leftGroup, 
    std::vector<int32_t> rightGroup,
    vex::gearSetting setting,long double gearRatio, Dimensions chassisDimensions,Limits chassisLimits);


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
    double ticksPerRev;
    double maxVelocity;
    double maxAcceleration;
    encoder rightEncoder;
    encoder leftEncoder;
    encoder backEncoder;
    inertial inert;
    Tracking( double trackWidth,double wheelRadius, double ticksPerRev,std::vector<triportIndex> enocoderPorts,int GyroPort) :
    leftEncoder(brained.ThreeWirePort.Port[enocoderPorts[LEFT_ENCODER]]),
    rightEncoder(brained.ThreeWirePort.Port[enocoderPorts[RIGHT_ENCODER]]),
    backEncoder(brained.ThreeWirePort.Port[enocoderPorts[BACK_ENCODER]]),
    inert(GyroPort)
    {
      this-> ticksPerRev = ticksPerRev;
      this-> trackWidth = trackWidth;
      this-> wheelRadius = wheelRadius;
    } 
};
extern Tracking poseTracker;
extern FourMotorDrive chassis;
