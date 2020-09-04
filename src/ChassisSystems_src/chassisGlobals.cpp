#include "ChassisSystems/chassisGlobals.h"
#include "Util/vex.h"

FourMotorDrive::FourMotorDrive(const std::array<int32_t, 2> &leftGroup,
                               const std::array<int32_t, 2> &rightGroup,
                               gearSetting setting, double gearRatio,
                               Dimensions chassisDimensions,
                               Limits chassisLimits,
                               std::initializer_list<PDcontroller> PDGains)

    : m_chassisDimensions(chassisDimensions), m_chassisLimits(chassisLimits),
      leftFront(leftGroup[FRONT], setting),
      rightFront(rightGroup[FRONT], setting),
      leftBack(leftGroup[BACK], setting), rightBack(rightGroup[BACK], setting) {

  enum posPIDType { DISTANCEPID, ANGLEPID, TURNPID };
  int count = 0;
  for (auto &element : PDGains) {

    switch (count) {

    case DISTANCEPID:
      distancePID.setPD(element.kP, element.kD);
      break;
    case ANGLEPID:
      anglePID.setPD(element.kP, element.kD);
      break;
    case TURNPID:
      turnPID.setPD(element.kP, element.kD);
      break;
    }

    count++;
  }
  this->gearRatio = gearRatio;
  this->setting = setting;
}
void FourMotorDrive::setReverseSettings(
    const std::array<bool, 2> &LeftReverseVals,
    const std::array<bool, 2> &RightReverseVals) {
  leftFront.setReversed(LeftReverseVals[0]);
  leftBack.setReversed(LeftReverseVals[1]);
  rightFront.setReversed(RightReverseVals[0]);
  rightBack.setReversed(RightReverseVals[1]);
}

void FourMotorDrive::resetPosition() {
  this->leftFront.resetPosition();
  this->leftBack.resetPosition();
  this->rightFront.resetPosition();
  this->rightBack.resetPosition();
}

void FourMotorDrive::resetRotation() {
  this->leftFront.resetRotation();
  this->leftBack.resetRotation();
  this->rightFront.resetRotation();
  this->rightBack.resetRotation();
}

Dimensions::Dimensions(long double trackWidth, long double wheelRadius)
    : m_trackWidth(trackWidth), m_wheelRadius(wheelRadius) {}

Limits::Limits(long double maxVelocity, long double maxAcceleration)
    : m_maxVelocity(maxVelocity), m_maxAcceleration(maxAcceleration) {}

Tracking::Tracking(WheelDistances wheels, double wheelRadius,
                   std::vector<triportIndex> enocoderPorts, int GyroPort,
                   double ticksPerRev)
    : m_odomImpl(wheels),
      rightEncoder(brained.ThreeWirePort.Port[enocoderPorts[RIGHT_ENCODER]]),
      leftEncoder(brained.ThreeWirePort.Port[enocoderPorts[LEFT_ENCODER]]),
      backEncoder(brained.ThreeWirePort.Port[enocoderPorts[BACK_ENCODER]]),
      inert(GyroPort) {
  this->ticksPerRev = ticksPerRev;

  this->wheelRadius = wheelRadius;
}

double FourMotorDrive::convertMetersToTicks(double num_meters) {
  return (num_meters * (360 / (m_chassisDimensions.m_wheelRadius * M_PI)) * this->gearRatio);
}
double FourMotorDrive::convertTicksToMeters(double num_ticks) {
  return (num_ticks * (m_chassisDimensions.m_wheelRadius * M_PI / 360) * this->gearRatio);
}
double Tracking::getInertialHeading() {
  // change the direction to counter clockwise = positive
  double fixedRotation = -1 * this->inert.rotation();

  // Fix the inertial value between [-180,180]
  while (fixedRotation > 180) {
    (fixedRotation -= 360);
  }
  while (fixedRotation < -180) {
    (fixedRotation += 360);
  }

  return (fixedRotation);
}
