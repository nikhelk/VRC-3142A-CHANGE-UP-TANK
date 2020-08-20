#include "ChassisSystems/posPID.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/mathAndConstants.h"
#include "ChassisSystems/motionprofile.h"
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include <algorithm>
#include "Util/literals.h"
using namespace std;

void FourMotorDrive::turnToDegreeGyro(double angle)
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
    double currentAngleRadians = (M_PI/180.0)*(poseTracker.getInertialHeading());

    double angleOutput = chassis.turnPID.calculatePower(angle, currentAngleRadians); //no need to initilze turnPID here becuase it is in the initlizer list (see Config_src/chassis-config.cpp)
    
    this->setDrive(-1 * angleOutput, angleOutput);
    
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

    std::cout << angle <<  " "  << currentAngleRadians <<std::endl;

    task::sleep(10);
  }

}





void FourMotorDrive::driveStraightFeedforward(const double distance, bool backwards)
{
  double switchDirections =1;
  if(backwards) {
    switchDirections = -1;
  }
    const double startTime = Brain.timer(vex::timeUnits::sec); //"resetting" timer

    TrapezoidalMotionProfile trap(this->m_chassisLimits.m_maxVelocity, this->m_chassisLimits.m_maxAcceleration, distance);

    double mpVel, mpAcc; //motion profile velocity and acceleration

    double drift;

    double currentTime, prevTime;

    const double initialMetersLeft = this->convertTicksToMeters(this->getLeftEncoderValueMotors()); //this is a way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = this->convertTicksToMeters(this->getRightEncoderValueMotors());

    double pose = 0; //position on the motion profile

    // Here we use different feedfoward and P loops on both sides of the drivetrain
    // Ideally, we would not have to do this but the frictional losses on the right side were significantly greater than the left

    Feedfoward rFeed(11/trap.m_maxVel,.1);

    Feedfoward lFeed(11/trap.m_maxVel,.08);

    posPID rPush(0, 0);

    posPID lPush(0,  0);

    double rPower, lPower;

    double t = 0;

    while (t <=trap.m_totalTime)
    {

      double currLeftMoved = this->convertTicksToMeters(this->getLeftEncoderValueMotors()) - initialMetersLeft; // (in meters)

      double currRightMoved = this->convertTicksToMeters(this->getRightEncoderValueMotors()) - initialMetersRight; // (in meters)

      drift = currLeftMoved - currRightMoved;

      currentTime = Brain.timer(vex::timeUnits::sec) - startTime;

      mpVel = trap.calculateMpVelocity(currentTime); //velocity of motion profile
      
      mpAcc = trap.calculateMpAcceleration(currentTime); //acceleration of motion profile

      std::string currentStatus = trap.getMpStatus(currentTime);

      rPower = rPush.calculatePower(pose, this->convertTicksToMeters(this->getRightEncoderValueMotors()));

      lPower = lPush.calculatePower(pose, this->convertTicksToMeters(this->getLeftEncoderValueMotors()));
      
      cout << this->convertTicksToMeters(this->getRightEncoderValueMotors()) << 
      " " << this->convertTicksToMeters(this->getLeftEncoderValueMotors()) << 
      " " << pose <<
       " " << lPower <<" " << rPower << " " << lPush.getKp() << endl;

     double lVoltage =  lFeed.kV * mpVel + lFeed.kA * mpAcc + lPower; //kV * velocity + kA* acceleration + kP*(pose-measuredPose)
     double rVoltage =  rFeed.kV * mpVel + rFeed.kA * mpAcc + rPower; //kV * velocity + kA* acceleration + kP*(pose-measuredPose)
     // this->setDrive(switchDirections*lVoltage, switchDirections*rVoltage);

     if (!backwards)
     {
       pose += mpVel * (currentTime - prevTime); //Way of apporoximating position on the profile: pose_t += velocity_t * dt
     }

     else
     {
       pose -= mpVel * (currentTime - prevTime); // When we go backwards we subtract pose
     }

     t = currentTime;

     prevTime = currentTime;

     task::sleep(10);
      
    }

  this->setDrive(0, 0); //stopping bot
}


void FourMotorDrive::driveArcFeedforward(const double radius, const double exitAngle) {

  double startTimeA = Brain.timer(vex::timeUnits::sec);

  const double distance = radius *exitAngle;

  double rRadius = radius + .15;
  double lRadius = radius - .15;
  double rDistance = rRadius * exitAngle;
  double lDistance = lRadius * exitAngle;

  double ratio = lDistance/rDistance;
  TrapezoidalMotionProfile trap(this->m_chassisLimits.m_maxVelocity, this->m_chassisLimits.m_maxAcceleration, distance);

  TrapezoidalMotionProfile trapR(this->m_chassisLimits.m_maxVelocity, this->m_chassisLimits.m_maxAcceleration, rDistance);

  TrapezoidalMotionProfile trapL(this->m_chassisLimits.m_maxVelocity, this->m_chassisLimits.m_maxAcceleration, lDistance);

    double mpVel, mpAcc;

    double drift;

    double currentTime, prevTime;

    const double initialMetersLeft = this->convertTicksToMeters(this->getLeftEncoderValueMotors()); //this is my way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = this->convertTicksToMeters(this->getRightEncoderValueMotors());

    double rPose = 0;

    double lPose = 0;

    Feedfoward rFeed(11.2/trap.m_maxVel,.1);

    Feedfoward lFeed(11/trap.m_maxVel,.08);

    posPID rPush(7, 0);

    posPID lPush(0, 0);

    double rPower, lPower;

    double t = 0;

    double lastLeft, lastRight;
    posPID r(0,0);
    posPID l(1,0);

  while(t <= trap.m_totalTime) {

    double currLeftMoved = this->convertTicksToMeters(this->getLeftEncoderValueMotors()) - initialMetersLeft;

    double currRightMoved = this->convertTicksToMeters(this->getRightEncoderValueMotors()) - initialMetersRight;


    drift = currLeftMoved - currRightMoved;

    currentTime = Brain.timer(vex::timeUnits::sec) - startTimeA;

    mpVel = trap.calculateMpVelocity(currentTime);
      
    mpAcc = trap.calculateMpAcceleration(currentTime);


    double rAdjust = mpVel * (2 - this->m_chassisDimensions.m_trackWidth * (1/radius)) / 2;

    double lAdjust = mpVel * (2 + this->m_chassisDimensions.m_trackWidth * (1/radius)) / 2;

    double R = trapR.calculateMpVelocity(currentTime);
    double L = trapL.calculateMpVelocity(currentTime);

   // chassis.normalize(lAdjust, rAdjust);


    double rightVel = (currRightMoved-lastRight)/.01;
    double leftVel = (currLeftMoved-lastLeft)/.01;
    cout << lPose <<" " << this->convertTicksToMeters(this->getLeftEncoderValueMotors()) << " "
    << rPose << " " << this->convertTicksToMeters(this->getRightEncoderValueMotors()) <<  " " << 
    this->convertTicksToMeters(this->getAverageEncoderValueMotors()) << " " << (rPose+lPose)/2<< " "
    << rAdjust << " " << lAdjust << endl;


    auto rPower = r.calculatePower(rPose, currRightMoved);
    auto lPower = l.calculatePower(lPose, currLeftMoved);

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

  if (maxSpeed > this->m_chassisLimits.m_maxVelocity) 
  {
    std::cout << "NORMALIZING" << " " << maxSpeed << std::endl;

    left = left / maxSpeed * this->m_chassisLimits.m_maxVelocity;

    right = right / maxSpeed * this->m_chassisLimits.m_maxVelocity;

  }
}


void FourMotorDrive::setVelDrive(double leftVelocity, double rightVelocity)
{
    leftFront.spin(fwd, leftVelocity, velocityUnits::dps);
    leftBack.spin(fwd, leftVelocity, velocityUnits::dps);
    rightFront.spin(fwd, rightVelocity, velocityUnits::dps);
    rightBack.spin(fwd, rightVelocity, velocityUnits::dps);
}

void FourMotorDrive::setDrive(double leftVoltage, double rightVoltage)
{
    leftFront.spin(fwd, leftVoltage, volt);
    leftBack.spin(fwd, leftVoltage, volt);
    rightFront.spin(fwd, rightVoltage, volt);
    rightBack.spin(fwd, rightVoltage, volt);
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

void FourMotorDrive::turnToAbsAngle(const double deg)
{
    long theta = 0;
    theta = positionArray[ODOM_THETA];

    turnToDegree(deg - theta);
}


void FourMotorDrive::driveArc2(const double angle, double radius)
{
    bool atTarget = false;
    double distanceElapsed = 0, angleChange = 0;
    double lastDistance = 0;
    double distance = toRadians(angle) * (radius);
    double rRadius = radius + 7.0;
    double lRadius = radius - 7.0;
    double rDistance = rRadius * toRadians(angle);
    double lDistance = lRadius * toRadians(angle);
    double ratio = lDistance / rDistance;

    double unroundedTargetDistance = encoderToInch * distance;
    double targetDistance = truncf(unroundedTargetDistance * 10) / 10;

    const long encoderLeft = leftFront.position(degrees);
    const long encoderRight = rightFront.position(degrees);

    const double atTargetDistance = 26 / 4;
    pidTimer driveTimer;
    const double threshold = 2;

    double currentRatio = 0;
    const int timeoutPeriod = 2000;
    long currentLeft, currentRight;
    driveTimer.notMoved = 0;
    driveTimer.close = 0;
    double distancePower, anglePower, ratioPower;
    posPID arcPID(9, .3);
    double curAngle = positionArray[ODOM_THETA];
    while (!atTarget)
    {
        currentLeft = chassis.leftFront.position(degrees) - encoderLeft;
        currentRight = chassis.rightFront.position(degrees) - encoderRight;
        if (currentRight == 0 || currentLeft == 0)
        {
            currentRatio = 0;
        }
        else
        {
            currentRatio = (double)currentLeft / currentRight;
        }
        // std::cout << targetDistance << " " << 1/curvature << " " <<angleChange << " " << angle*(720/102.0)<<std::endl;
        distanceElapsed = (currentLeft + currentRight) / 2.0;
        angleChange = currentRight - currentLeft;
        //angleChange = positionArray[ODOM_THETA] - curAngle;
        distancePower = chassis.distancePID.calculatePower(targetDistance, distanceElapsed);
        // double realPower = distancePower/11;
        //anglePower = 0;

        std::cout << distancePower << " " << currentRatio << " " << ratio << std::endl;
        setDrive(ratio * (distancePower) + ratioPower, distancePower - ratioPower);

        if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance)
        {
            driveTimer.close += 10;
        }
        //Place mark if we haven't moved much
        else if (std::abs(distanceElapsed - lastDistance) <= threshold)
        {
            driveTimer.notMoved += 10;
        }
        else
        {
            driveTimer.close = 0;
            driveTimer.notMoved = 0;
        }
        bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
        bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
        bool pass = driveTimer.notMoved >= timeoutPeriod;
        bool pass2 = driveTimer.close >= timeoutPeriod;

        //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
        lastDistance = distanceElapsed;

        //If we've been close enough for long enough, we're there
        if (driveTimer.close >= timeoutPeriod || driveTimer.notMoved >= timeoutPeriod)
        {
            atTarget = true;
        }
        Brain.Screen.printAt(100, 150, "%f", leftFront.position(degrees));
        Brain.Screen.printAt(0, 150, "timerClose: %.0f, timerNotMoved: %.0f", driveTimer.close, driveTimer.notMoved);
        Brain.Screen.printAt(0, 200, "distanceElapsed: %.2f,Error %.2f  ", distanceElapsed, targetDistance);
        task::sleep(10);
    }
    Brain.Screen.clearScreen();
    setDrive(0, 0);
}


*/