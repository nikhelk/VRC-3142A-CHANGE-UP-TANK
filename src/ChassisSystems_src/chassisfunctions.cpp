#include "ChassisSystems/posPID.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/mathAndConstants.h"
#include "ChassisSystems/motionprofile.h"
#include "Config/chassis-config.h"

#include <algorithm>
#include "Util/literals.h"
#include <memory>

void FourMotorDrive::turnToDegreeFeedforward(const double angle) {
  const double initialEncodersLeft = this->getLeftEncoderValueMotors();
  const double initialEncodersRight = this->getRightEncoderValueMotors();

  const double totalEncoderTicks = math3142a::toDegrees(angle)*m_chassisDimensions.ticksToDegrees;

  TrapezoidalMotionProfile trap(getMaxAngularVelocity(),getMaxAngularAcceleration(),totalEncoderTicks);

  const double startTime = Brain.timer(timeUnits::sec); //"resetting" timer


  double mpVel, mpAcc; //forward ref for motion profile velocity and acceleration

  double currentTime = 0, prevTime = 0;


  double lPose = 0, rPose = 0; //position on the motion profile

  // Here we use different feedfoward and P loops on both sides of the drivetrain
  // Ideally, we would not have to do this but the frictional losses on the right side were significantly greater than the left
  // Our estamate for kV was 11V / maxVel as the inputted max velocity in the FourMotorDrive constructor was base on the robot travelling at 11V
  // the values for kA had to be tuned, but again it took consideriably less time than tuning PID

  const Feedfoward rFeedforwardConstants(11/trap.getMpMaxVelocity(),.1);

  const Feedfoward lFeedforwardConstants(11/trap.getMpMaxVelocity(),.08);

  posPID rFeedback(0, 0);

  posPID lFeedback(0,  0);

  double rPower, lPower;

  while (currentTime <= trap.getMpTotalTime())
    {

      double currLeftMoved = this->getLeftEncoderValueMotors() - initialEncodersLeft; // (in meters)

      double currRightMoved = this->getRightEncoderValueMotors() - initialEncodersRight; // (in meters)

      currentTime = Brain.timer(timeUnits::sec) - startTime;

      mpVel = trap.calculateMpVelocity(currentTime); //velocity of motion profile
      
      mpAcc = trap.calculateMpAcceleration(currentTime); //acceleration of motion profile

      auto currentStatus = trap.getMpStatus(currentTime);

      rPower = rFeedback.calculatePower(rPose, currRightMoved);

      lPower = lFeedback.calculatePower(lPose, currLeftMoved);
      
      LOG(currLeftMoved,currRightMoved,rPose,lPower,rPower);

     double lVoltage =  -1* lFeedforwardConstants.kV * mpVel + lFeedforwardConstants.kA * mpAcc + lPower; //kV * velocity + kA* acceleration + kP*(pose-measuredPose)
     double rVoltage =  rFeedforwardConstants.kV * mpVel + rFeedforwardConstants.kA * mpAcc + rPower; //kV * velocity + kA* acceleration + kP*(pose-measuredPose)
     
     
     this->setDrive(lVoltage,rVoltage);

     rPose += mpVel * (currentTime - prevTime); //Way of apporoximating position on the profile: pose_t += velocity_t * dt
     lPose -= mpVel * (currentTime - prevTime); //Way of apporoximating position on the profile: pose_t += velocity_t * dt

     prevTime = currentTime;

     task::sleep(10);
      
    }

  this->setDrive(0, 0); //stopping bot

  

}


void FourMotorDrive::turnToDegreeGyro(const double angle)
{
  bool atAngle = false;
  /***************************************************************************************************************************/

  // We would like to thank Team Optimistic for providing us a template of the PID exit function

  // <https://github.com/Team-Optimistic/Team_Optimistic/blob/d6b11f7d5a9e58c72e2c5dd9d944369602bc20a7/turningFunctions.c#L69>

  /****************************************************************************************************************************/
  pidTimer turnTimer;

  const double timeoutPeriod = 200;

  const double acceptableError = 3.0_deg; // give three degrees of error

  while (!atAngle)
  {
    double currentAngleRadians = math3142a::toRadians(poseTracker.getInertialHeading());

    double angleOutput = chassis.turnPID.calculatePower(angle, currentAngleRadians); //no need to initilze turnPID here becuase it is in the initlizer list (see Config_src/chassis-config.cpp)
    
    adjustOutput(angle,angleOutput);
    
    this->setDrive(-1 * angleOutput, angleOutput );
    
    //If we are close to the target start incrementing timeout
    if (std::abs(angle - currentAngleRadians) < acceptableError)
    {
      turnTimer.close += 10;
    }

    else
    {
      turnTimer.close = 0;
    }

    //If we've been close enough for long enough, we're there
    if (turnTimer.close > timeoutPeriod)
    {
      atAngle = true;
    }

    LOG(math3142a::toDegrees(angle),math3142a::toDegrees(currentAngleRadians));
    
    task::sleep(10);
  }
  this->setDrive(0, 0);
}

void FourMotorDrive::driveStraightFeedforward(const double distance, bool backwards)
{
    const double startTime = Brain.timer(timeUnits::sec); //"resetting" timer

    TrapezoidalMotionProfile trap(getMaxLinearVelocity(), getMaxLinearAcceleration(), distance);

    double mpVel, mpAcc; //forward ref for motion profile velocity and acceleration

    double currentTime = 0, prevTime = 0;

    const double initialMetersLeft = this->convertTicksToMeters(this->getLeftEncoderValueMotors()); //this is a way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = this->convertTicksToMeters(this->getRightEncoderValueMotors());

    double pose = 0; //position on the motion profile

    // Here we use different feedfoward and P loops on both sides of the drivetrain
    // Ideally, we would not have to do this but the frictional losses on the right side were significantly greater than the left
    // Our estamate for kV was 11V / maxVel as the inputted max velocity in the FourMotorDrive constructor was base on the robot travelling at 11V
    // the values for kA had to be tuned, but again it took consideriably less time than tuning PID

    const Feedfoward rFeedforwardConstants(11/trap.getMpMaxVelocity(),.1);

    const Feedfoward lFeedforwardConstants(11/trap.getMpMaxVelocity(),.08);

    posPID rFeedback(0, 0);

    posPID lFeedback(0,  0);

    double rPower, lPower;

    while (currentTime <= trap.getMpTotalTime())
    {

      double currLeftMoved = this->convertTicksToMeters(this->getLeftEncoderValueMotors()) - initialMetersLeft; // (in meters)

      double currRightMoved = this->convertTicksToMeters(this->getRightEncoderValueMotors()) - initialMetersRight; // (in meters)

      currentTime = Brain.timer(timeUnits::sec) - startTime;

      mpVel = trap.calculateMpVelocity(currentTime); //velocity of motion profile
      
      mpAcc = trap.calculateMpAcceleration(currentTime); //acceleration of motion profile

      auto currentStatus = trap.getMpStatus(currentTime);

      rPower = rFeedback.calculatePower(pose, currRightMoved);

      lPower = lFeedback.calculatePower(pose, currLeftMoved);
      
      LOG(currLeftMoved,currRightMoved,pose,lPower,rPower);

     double lVoltage =  lFeedforwardConstants.kV * mpVel + lFeedforwardConstants.kA * mpAcc + lPower; //kV * velocity + kA* acceleration + kP*(pose-measuredPose)
     double rVoltage =  rFeedforwardConstants.kV * mpVel + rFeedforwardConstants.kA * mpAcc + rPower; //kV * velocity + kA* acceleration + kP*(pose-measuredPose)
     
     checkBackwards(lVoltage,rVoltage,backwards);
     
     this->setDrive(lVoltage,rVoltage);

     if (!backwards)
     {
       pose += mpVel * (currentTime - prevTime); //Way of apporoximating position on the profile: pose_t += velocity_t * dt
     }

     else
     {
       pose -= mpVel * (currentTime - prevTime); // When we go backwards we subtract pose
     }

     prevTime = currentTime;

     task::sleep(10);
      
    }

  this->setDrive(0, 0); //stopping bot
}


void FourMotorDrive::driveArcFeedforward(const double radius, const double exitAngle) {

  double startTimeA = Brain.timer(timeUnits::sec);

  const double distance = radius *exitAngle;

  double rRadius = radius + .15;
  double lRadius = radius - .15;
  double rDistance = rRadius * exitAngle;
  double lDistance = lRadius * exitAngle;

  double ratio = lDistance/rDistance;
  TrapezoidalMotionProfile trap(getMaxLinearVelocity(),getMaxLinearAcceleration(), distance);

  TrapezoidalMotionProfile trapR(getMaxLinearVelocity(),getMaxLinearAcceleration(), rDistance);

  TrapezoidalMotionProfile trapL(getMaxLinearVelocity(),getMaxLinearAcceleration(), lDistance);

    double mpVel, mpAcc;

    double drift;

    double currentTime, prevTime;

    const double initialMetersLeft = this->convertTicksToMeters(this->getLeftEncoderValueMotors()); //this is my way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = this->convertTicksToMeters(this->getRightEncoderValueMotors());

    double rPose = 0;

    double lPose = 0;

    Feedfoward rFeed(9/trap.getMpMaxVelocity() , .1);

    Feedfoward lFeed(9/trap.getMpMaxVelocity() , .08);

    posPID rPush(0, 0);

    posPID lPush(0, 0);

    double rPower, lPower;

    double t = 0;

    double lastLeft, lastRight;

  while(t <= trap.getMpTotalTime()) {

    double currLeftMoved = this->convertTicksToMeters(this->getLeftEncoderValueMotors()) - initialMetersLeft;

    double currRightMoved = this->convertTicksToMeters(this->getRightEncoderValueMotors()) - initialMetersRight;

  
    drift = currLeftMoved - currRightMoved;

    currentTime = Brain.timer(timeUnits::sec) - startTimeA;

    mpVel = trap.calculateMpVelocity(currentTime);
      
    mpAcc = trap.calculateMpAcceleration(currentTime);


    double rAdjust = mpVel * (2 - this->m_chassisDimensions.m_trackWidth * (1/radius)) / 2;

    double lAdjust = mpVel * (2 + this->m_chassisDimensions.m_trackWidth * (1/radius)) / 2;

   // chassis.normalize(lAdjust, rAdjust);


    double rightVel = (currRightMoved-lastRight)/.01;
    double leftVel = (currLeftMoved-lastLeft)/.01;

    std::cout << lPose <<" " << this->convertTicksToMeters(this->getLeftEncoderValueMotors()) << " "
    << rPose << " " << this->convertTicksToMeters(this->getRightEncoderValueMotors()) <<  " " << 
    this->convertTicksToMeters(this->getAverageEncoderValueMotors()) << " " << (rPose+lPose)/2<< " "
    << rAdjust << " " << lAdjust << std::endl;


    auto rPower = rPush.calculatePower(rPose, currRightMoved);
    auto lPower = lPush.calculatePower(lPose, currLeftMoved);

    setDrive(lAdjust*lFeed.kV + lPower ,rAdjust*rFeed.kV+rPower);
    //setVelDrive(chassis.convertMetersToTicks(lAdjust), chassis.convertMetersToTicks(rAdjust));
    t = currentTime;

    rPose += rAdjust * .01;

    lPose += lAdjust * .01;

    lastLeft = currLeftMoved;
    lastRight = currLeftMoved;
    task::sleep(10);

  }

  setDrive(0, 0);
  

}

void FourMotorDrive::normalize(double &left, double &right) {

  double maxSpeed = std::max(std::abs(left), std::abs(right));

  if (maxSpeed > getMaxLinearVelocity()) 
  {
    std::cout << "NORMALIZING" << " " << maxSpeed << std::endl;

    left = left / maxSpeed * getMaxLinearVelocity();

    right = right / maxSpeed * getMaxLinearVelocity();

  }
}


void FourMotorDrive::setVelDrive(double leftVelocity, double rightVelocity, velocityUnits units)
{
    leftFront.spin(fwd, leftVelocity, units);
    leftBack.spin(fwd, leftVelocity, units);
    rightFront.spin(fwd, rightVelocity, units);
    rightBack.spin(fwd, rightVelocity, units);
}

void FourMotorDrive::setDrive(double leftVoltage, double rightVoltage)
{
    leftFront.spin(fwd, leftVoltage, volt);
    leftBack.spin(fwd, leftVoltage, volt);
    rightFront.spin(fwd, rightVoltage, volt);
    rightBack.spin(fwd, rightVoltage, volt);
}


inline void FourMotorDrive::adjustOutput(double targetAngle,double& angleOutput) {
    if(targetAngle - math3142a::toRadians(poseTracker.getInertialHeading()) > M_PI || targetAngle - math3142a::toRadians(poseTracker.getInertialHeading()) < -1 * M_PI ) {

    angleOutput = -1*angleOutput;
    }
}

inline void FourMotorDrive::checkBackwards(double& lVoltage , double& rVoltage , bool backwards) {
  if(backwards) {
    lVoltage = lVoltage * -1;
    rVoltage = rVoltage * -1;
  }
}




double FourMotorDrive::getAverageEncoderValueMotors()
{
  return ((leftFront.position(degrees) + rightFront.position(degrees) + leftBack.position(degrees) + rightBack.position(degrees)) / 4);
}

double FourMotorDrive::getRightEncoderValueMotors()
{
  return ((rightFront.position(degrees) + rightBack.position(degrees)) / 2);
}

double FourMotorDrive::getLeftEncoderValueMotors()
{
  return ((leftFront.position(degrees) + leftBack.position(degrees)) / 2);
}
double Tracking::getAverageEncoderValueEncoders() 
{
  return ((this->leftEncoder.position(degrees) + this->rightEncoder.position(degrees)) / 2);
}




/*

void FourMotorDrive::moveToPoint(const double x, const double y, bool backwards)
{
    pointVals vector;
    computeDistanceAndAngleToPoint(x, y, &vector);
    if (backwards)
    {
        vector.theta += 180;
        vector.length *= -1;
    }

    turnToDegree(vector.theta);

    driveStraight(vector.length);
}

*/