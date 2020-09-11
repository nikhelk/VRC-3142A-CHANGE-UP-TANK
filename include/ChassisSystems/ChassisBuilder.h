#pragma once
#include "ChassisSystems/chassisGlobals.h"
class FourMotorDrive::FourMotorDriveBuilder {

  private:
  std::array<int32_t, 2> m_leftGroup;
  std::array<int32_t, 2> m_rightGroup;
  gearSetting gearbox;
  double gearRatio;
  Dimensions m_chassisDimensions;
  Limits b_chassisLinearLimits;
  Limits b_chassisAngularLimits;
  std::initializer_list<PDcontroller> m_PDGains;


  public:
    FourMotorDriveBuilder& withMotors(const std::array<int32_t, 2> &leftGroup,const std::array<int32_t, 2> &rightGroup) {
      m_leftGroup = leftGroup;
      m_rightGroup = rightGroup;
      return *this;
    }
    FourMotorDriveBuilder& withGearSetting(const gearSetting gears) {
      gearbox = gears;
      return *this;
    }
    FourMotorDriveBuilder& withGearRatio(const double ratio) {
      gearRatio = ratio;
      return *this;
    }
    FourMotorDriveBuilder& withDimensions(const Dimensions chassisDimensions) {
      m_chassisDimensions = chassisDimensions;
      return *this;
    }
    FourMotorDriveBuilder& withLinearLimits(Limits linearChassisLimits) {
      b_chassisLinearLimits = linearChassisLimits;
      return *this;
    }
    FourMotorDriveBuilder& withAngularLimits(Limits angularChassisLimits) {
      b_chassisAngularLimits = angularChassisLimits;
      return *this;
    }
    FourMotorDriveBuilder& withPDGains(std::initializer_list<PDcontroller> PDGains) {
      PDGains = PDGains;
      return *this;
    }

    FourMotorDrive buildChassis() const
    {
      return FourMotorDrive{m_leftGroup, m_rightGroup, gearbox, gearRatio,m_chassisDimensions,b_chassisLinearLimits,b_chassisAngularLimits,m_PDGains};
    }

};


