#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"
#include "Util/mathAndConstants.h"


using namespace vex;

namespace Scorer{

/// Main flywheel task
int flywheelTask();


/// when we set this bool to true, then the flywheel stops when the top line sensor detects a ball
extern bool FlywheelStopWhenTopDetected;

/// Wether or not we have scored
extern bool Scored;


// different voltages depending on what we are doing (admittedly, it was probably not the best idea to use an enum)
enum FlywheelVoltages { 
    SCORE_VOLTAGE = 12,
    FLYWHEEL_STOP_VOLTAGE = 0,
    FLYWHEEL_OUTY_VOLTAGE = -12 ///voltage while ejecting
};


}