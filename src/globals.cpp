#include "vex.h"


FourMotorDrive::FourMotorDrive( std::vector<int32_t> leftGroup, 
    std::vector<int32_t> rightGroup,
    vex::gearSetting setting,double gearRatio, std::initializer_list<PDcontroller> PDGains) :

    leftFront(leftGroup[FRONT],setting),

    rightFront(rightGroup[FRONT],setting),

    leftBack(leftGroup[BACK],setting),

    rightBack(rightGroup[BACK],setting)

    {
      int count = 0;
      for(auto element : PDGains) {
        
        switch(count)
        {

          case 0:
            distancePID.KP = element.kP;
            distancePID.KD = element.kD;
            break;
          case 1:
            anglePID.KP = element.kP;
            anglePID.KD = element.kD;
            break;
          case 2:
            turnPID.KP = element.kP;
            turnPID.KD = element.kD;
            break;

        }

        count++;

      }
      this->gearRatio = gearRatio;
      this-> setting = setting;
    } 
 void FourMotorDrive::setReverseSettings(std::vector<bool> LeftReverseVals, std::vector<bool> RightReverseVals) {
    leftFront.setReversed(LeftReverseVals[0]);
    leftBack.setReversed(LeftReverseVals[1]);
    rightFront.setReversed(RightReverseVals[0]);
    rightBack.setReversed(RightReverseVals[1]);

  }

Dimensions::Dimensions( FourMotorDrive *drive,double trackWidth, double wheelRadius)
{
      drive->trackWidth = trackWidth;
      drive->wheelRadius = wheelRadius;
} 


Limits::Limits( FourMotorDrive *drive,double maxVelocity, double maxAcceleration)
{
      drive->maxVelocity  = maxVelocity;
      drive->maxAcceleration = maxAcceleration;
} 