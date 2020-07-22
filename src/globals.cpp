#include "vex.h"

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