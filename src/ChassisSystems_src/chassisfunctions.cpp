#include "ChassisSystems/posPID.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/mathAndConstants.h"
#include "ChassisSystems/motionprofile.h"
using namespace std;

void FourMotorDrive::turnToDegreeGyro(double degree)
{
  double atTarget = false;
  double atTargetAngle = 3;
  while (!atTarget)
  {
    double currentAngleRadians = toRadians(poseTracker.getInertialHeading());
    double targetAngleRadians = toRadians(degree);

    double angleOutput = chassis.turnPID.calculatePower(targetAngleRadians, currentAngleRadians);
    pidTimer turnTimer;
    double timeoutPeriod = 250;
    this->setDrive(-1 * angleOutput, angleOutput);
    if (std::abs(degree - poseTracker.getInertialHeading()) <= atTargetAngle)
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
    std::cout << poseTracker.getInertialHeading() << std::endl;
    task::sleep(10);
  }
}





void FourMotorDrive::driveStraightFeedforward(const double distance)
{
    double startTimeA = Brain.timer(vex::timeUnits::sec);

    double mpVel;

    TrapezoidalMotionProfile trap(this->m_chassisLimits.m_maxVelocity, this->m_chassisLimits.m_maxAcceleration, distance);

    double drift;

    

    double currentTime;

    const double initialMetersLeft = chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()); //this is my way of resetting the encoder vals instead of setting them to 0
    
    const double initialMetersRight = chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors());


    double pose = 0;

    posPID rPush(7, 0);

    posPID lPush(0, 0);

    double t = 0;

    while (t <=trap.m_totalTime)
    {

      double currLeftMoved = chassis.convertTicksToMeters((chassis.getLeftEncoderValueMotors()) - initialMetersLeft);

      double currRightMoved = chassis.convertTicksToMeters((chassis.getRightEncoderValueMotors()) - initialMetersRight);

      drift = currLeftMoved - currRightMoved;

      currentTime = Brain.timer(vex::timeUnits::sec) - startTimeA;

      mpVel = trap.calculateMpVelocity(currentTime);

      double rPower = rPush.calculatePower(pose, chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors()));

      double lPower = lPush.calculatePower(pose, chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()));

      std::string currentStatus = trap.getMpStatus(currentTime);

      cout << chassis.convertTicksToMeters(chassis.getLeftEncoderValueMotors()) << " " << chassis.convertTicksToMeters(chassis.getRightEncoderValueMotors()) << " " << pose << endl;
      
      this->setDrive((11 / trap.m_maxVel) * mpVel + .08 * trap.calculateMpAcceleration(currentTime) + lPower, (11.2 / trap.m_maxVel) * mpVel + .1 * trap.calculateMpAcceleration(currentTime) + rPower); // setting the drive and adding the correction pid
      
      t = currentTime;
     
      task::sleep(10);
      
     
    }

  this->setDrive(0, 0); //stopping bot
}



























void FourMotorDrive::setVelDrive(double leftVelocity, double rightVelocity)
{
    leftFront.spin(fwd, leftVelocity, velocityUnits::rpm);
    leftBack.spin(fwd, leftVelocity, velocityUnits::rpm);
    rightFront.spin(fwd, rightVelocity, velocityUnits::rpm);
    rightBack.spin(fwd, rightVelocity, velocityUnits::rpm);
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