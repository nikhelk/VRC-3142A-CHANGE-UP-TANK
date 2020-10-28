#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"

#include "Util/mathAndConstants.h"

using namespace vex;

namespace Intakes {

/// Main intake task
int intakeTask();

/// When set to true, we rotate our intakes backwards
extern bool backUp;

/// When set to true, we run at full speed
extern bool IntakesRunContinously;

/// When set to true, we stop the intakes
extern bool IntakesStop;

// different voltages depending on what we are doing (admittedly, it was probably not the best idea to use an enum)
enum IntakeVoltages {
    INTAKE_VOLTAGE = 12,
    INTAKE_STOP_VOLTAGE = 0,
    INTAKE_BACK_UP_VOLTAGE = -8,
    INTAKE_INDEX_BALL_VOLTAGE = 10,
};
}