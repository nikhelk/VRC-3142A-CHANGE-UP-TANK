#include "vex.h"
FourMotorDrive::FourMotorDrive( std::vector<int32_t> leftGroup, 
    std::vector<int32_t> rightGroup,
    vex::gearSetting setting,long double gearRatio,Dimensions chassisDimensions,Limits chassisLimits) :

    m_chassisDimensions(chassisDimensions),

    m_chassisLimits(chassisLimits),

    leftFront(leftGroup[FRONT],setting),

    rightFront(rightGroup[FRONT],setting),

    leftBack(leftGroup[BACK],setting),

    rightBack(rightGroup[BACK],setting)


    {
      this->gearRatio = gearRatio;
      this-> setting = setting;
    }



 void FourMotorDrive::setReverseSettings(std::vector<bool> LeftReverseVals, std::vector<bool> RightReverseVals) {
    leftFront.setReversed(LeftReverseVals[0]);
    leftBack.setReversed(LeftReverseVals[1]);
    rightFront.setReversed(RightReverseVals[0]);
    rightBack.setReversed(RightReverseVals[1]);

  }

Dimensions::Dimensions(long  double trackWidth, long  double wheelRadius) :

    m_trackWidth(trackWidth),
    m_wheelRadius(wheelRadius)
{

} 


Limits::Limits( long double maxVelocity, long double maxAcceleration) :
    m_maxVelocity(maxVelocity),
    m_maxAcceleration(maxAcceleration)
{
} 