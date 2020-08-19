#include "ChassisSystems/posPID.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/mathAndConstants.h"
#include "ChassisSystems/motionprofile.h"
#include <algorithm>
using namespace std;

void FourMotorDrive::turnToDegreeGyro(double degree)
{
  double atTarget = false;
  double atTargetAngle = 3;
  while (!atTarget)
  {
    double currentAngleRadians = (M_PI/180)*(poseTracker.getInertialHeading());
    double targetAngleRadians = (degree);

    double angleOutput = chassis.turnPID.calculatePower(targetAngleRadians, currentAngleRadians);
    pidTimer turnTimer;
    double timeoutPeriod = 250;
    this->setDrive(-1 * angleOutput, angleOutput);
    if (std::abs(degree - currentAngleRadians) < (M_PI/180)*(atTargetAngle))
    {
      turnTimer.close += 10;
    }
    else
    {
      turnTimer.close = 0;
      turnTimer.notMoved = 0;
    }
    //cout << currentRight <<" " << currentLeft<< " " << " " << targetAngle/conv << " " <<angleChange/conv <<endl;
    //If we've been close enough for long enough, we're there
    if (turnTimer.close >= timeoutPeriod || turnTimer.notMoved >= timeoutPeriod)
    {
      atTarget = true;
    }
    std::cout << targetAngleRadians <<  " "  << currentAngleRadians <<std::endl;
    task::sleep(10);
  }
}





void FourMotorDrive::driveStraightFeedforward(const double distance, bool backwards)
{
  int switchDirections =1;
  if(backwards) {
    switchDirections = -1;
  }
    double startTimeA = Brain.timer(vex::timeUnits::sec);

    TrapezoidalMotionProfile trap(this->m_chassisLimits.m_maxVelocity, this->m_chassisLimits.m_maxAcceleration, distance);

    double mpVel, mpAcc;

    double drift;

    double currentTime, prevTime;

    const double initialMetersLeft = chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()); //this is my way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors());

    double pose = 0;

    Feedfoward rFeed(11/trap.m_maxVel,.1);

    Feedfoward lFeed(11/trap.m_maxVel,.08);

    posPID rPush(0, 0);

    posPID lPush(0,  0);

    double rPower, lPower;

    double t = 0;

    while (t <=trap.m_totalTime)
    {

      double currLeftMoved = chassis.convertTicksToMeters((chassis.getLeftEncoderValueMotors()) - initialMetersLeft);

      double currRightMoved = chassis.convertTicksToMeters((chassis.getRightEncoderValueMotors()) - initialMetersRight);

      drift = currLeftMoved - currRightMoved;

      currentTime = Brain.timer(vex::timeUnits::sec) - startTimeA;

      mpVel = trap.calculateMpVelocity(currentTime);
      
      mpAcc = trap.calculateMpAcceleration(currentTime);

      std::string currentStatus = trap.getMpStatus(currentTime);

      rPower = rPush.calculatePower(pose, chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors()));

      lPower = lPush.calculatePower(pose, chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()));
      
      cout << chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors()) << 
      " " << chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()) << 
      " " << pose <<
       " " << lPower <<" " << rPower << " " << lPush.getKp() << endl;
      
     // this->setDrive(lFeed.kV * mpVel + lFeed.kA * mpAcc + lPower, 
     // rFeed.kV * mpVel + rFeed.kA * mpAcc + rPower); // setting the drive and adding the correction pid
      
      pose += mpVel * (currentTime -prevTime);

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

    const double initialMetersLeft = chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()); //this is my way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors());

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

    double currLeftMoved = chassis.convertTicksToMeters((chassis.getLeftEncoderValueMotors()) - initialMetersLeft);

    double currRightMoved = chassis.convertTicksToMeters((chassis.getRightEncoderValueMotors()) - initialMetersRight);

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
    cout << lPose <<" " << chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()) << " "
    << rPose << " " << chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors()) <<  " " << 
    chassis.convertTicksToMeters(chassis.getAverageEncoderValueMotors()) << " " << (rPose+lPose)/2<< " "
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