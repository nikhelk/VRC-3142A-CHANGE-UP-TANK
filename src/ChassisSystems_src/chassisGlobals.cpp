#include "vex.h"
#include "ChassisSystems\chassisGlobals.h"
FourMotorDrive::FourMotorDrive(std::vector<int32_t> leftGroup, 
std::vector<int32_t> rightGroup, 
vex::gearSetting setting, 
double gearRatio, 
Dimensions chassisDimensions, 
Limits chassisLimits,
 std::initializer_list<PDcontroller> PDGains) :
 m_chassisDimensions(chassisDimensions),
 m_chassisLimits(chassisLimits),
 leftFront(leftGroup[FRONT], setting),
 rightFront(rightGroup[FRONT], setting),
 leftBack(leftGroup[BACK], setting),
 rightBack(rightGroup[BACK], setting)

{
  int count = 0;
  for (auto &element : PDGains)
  {

    switch (count)
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
  this->setting = setting;
}
void FourMotorDrive::setReverseSettings(std::vector<bool> LeftReverseVals, std::vector<bool> RightReverseVals)
{
  leftFront.setReversed(LeftReverseVals[0]);
  leftBack.setReversed(LeftReverseVals[1]);
  rightFront.setReversed(RightReverseVals[0]);
  rightBack.setReversed(RightReverseVals[1]);
}

void FourMotorDrive::setVoltDrive(double leftVoltage, double rightVoltage)
{
  this->leftFront.spin(fwd, leftVoltage, volt);
  this->leftBack.spin(fwd, leftVoltage, volt);
  this->rightFront.spin(fwd, rightVoltage, volt);
  this->rightBack.spin(fwd, rightVoltage, volt);
}

void FourMotorDrive::setVelocityDrive(double leftVelocity, double rightVelocity, velocityUnits vel)
{
  this->leftFront.spin(fwd, leftVelocity, vel);
  this->leftBack.spin(fwd, leftVelocity, vel);
  this->rightFront.spin(fwd, leftVelocity, vel);
  this->rightBack.spin(fwd, leftVelocity, vel);
}


Dimensions::Dimensions(long double trackWidth, long double wheelRadius) :
m_trackWidth(trackWidth),
m_wheelRadius(wheelRadius)
{
}

Limits::Limits(long double maxVelocity, long double maxAcceleration) : 
m_maxVelocity(maxVelocity),
m_maxAcceleration(maxAcceleration)
{
}

Tracking::Tracking(WheelDistances wheels, double wheelRadius, std::vector<triportIndex> enocoderPorts, int GyroPort, double ticksPerRev) : leftEncoder(brained.ThreeWirePort.Port[enocoderPorts[LEFT_ENCODER]]),
rightEncoder(brained.ThreeWirePort.Port[enocoderPorts[RIGHT_ENCODER]]),
backEncoder(brained.ThreeWirePort.Port[enocoderPorts[BACK_ENCODER]]),
inert(GyroPort),
m_odomImpl(wheels)
{
  this->ticksPerRev = ticksPerRev;
  this->trackWidth = trackWidth;
  this->wheelRadius = wheelRadius;
  this->backDistance = backDistance;
}

double FourMotorDrive::convertMetersToTicks(double num_meters)
{
  return (num_meters * (360 / (this->m_chassisDimensions.m_wheelRadius * M_PI)) * this->gearRatio);
}
double FourMotorDrive::convertTicksToMeters(double num_ticks)
{
  return (num_ticks * (this->m_chassisDimensions.m_wheelRadius * M_PI / 360) * this->gearRatio);
}
double Tracking::getInertialHeading()
{
  double fixedRotation = -1 * this->inert.rotation();
  while (fixedRotation > 180)
  {
    (fixedRotation -= 360);
  }
  while (fixedRotation < -180)
  {
    (fixedRotation += 360);
  }

  return (fixedRotation);
}
