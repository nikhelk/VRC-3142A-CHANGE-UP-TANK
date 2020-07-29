#include "vex.h"


FourMotorDrive::FourMotorDrive( std::vector<int32_t> leftGroup, 
    std::vector<int32_t> rightGroup,
    vex::gearSetting setting,double gearRatio, Dimensions chassisDimensions,Limits chassisLimits,std::initializer_list<PDcontroller> PDGains) :
    
    m_chassisDimensions(chassisDimensions),

    m_chassisLimits(chassisLimits),

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



void FourMotorDrive::setVoltDrive(double leftVoltage,double rightVoltage) {
  this->leftFront.spin (fwd,leftVoltage, volt);
  this->leftBack.spin(fwd,leftVoltage,volt);
  this->rightFront.spin(fwd,rightVoltage,volt);
  this->rightBack.spin(fwd,rightVoltage,volt);
}


void FourMotorDrive::setVelocityDrive(double leftVelocity, double rightVelocity, velocityUnits vel) {
  this->leftFront.spin (fwd,leftVelocity, vel);
  this->leftBack.spin(fwd,leftVelocity,vel);
  this->rightFront.spin(fwd,leftVelocity,vel);
  this->rightBack.spin(fwd,leftVelocity,vel);


}

void FourMotorDrive::turnToDegreeGyro(double degree) {
  double atTarget = false;
  double atTargetAngle = .1/2;
  while(!atTarget) {
      double currentAngleRadians = toRadians(poseTracker.getInertialHeading());
      double targetAngleRadians = toRadians(degree);

      double angleOutput = chassis.turnPID.calculatePower(targetAngleRadians,currentAngleRadians);
      pidTimer turnTimer;
      double timeoutPeriod = 250;
      setVoltDrive(angleOutput,-1*angleOutput);
    if (std::abs(targetAngleRadians - currentAngleRadians) <= atTargetAngle)
		{
			turnTimer.close += 10;
		}
		else
		{
			turnTimer.close = 0;
      turnTimer.notMoved =0;
		}
    //cout << currentRight <<" " << currentLeft<< " " << " " << targetAngle/conv << " " <<angleChange/conv <<endl;
		//If we've been close enough for long enough, we're there
		if (turnTimer.close >= timeoutPeriod||turnTimer.notMoved >=timeoutPeriod)
		{
			atTarget = true;
		}
    std::cout << toDegrees(currentAngleRadians) <<std::endl;
    task::sleep(10);




  }



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

double Tracking::getInertialHeading() {
  if(this->inert.heading() > 180) {
    return(this->inert.heading() - 360);
  }
  else if(this->inert.heading()  <-180) {
    return(this->inert.heading() + 360);
  }
  else {
    return(this->inert.heading());
  }
}