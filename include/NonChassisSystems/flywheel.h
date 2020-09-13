#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"
#include "Util/mathAndConstants.h"


using namespace vex;

namespace Scorer{

int flywheelTask(void* toBeCastedBools);

void outyTask();

extern bool outy;

enum FlywheelVoltages {
    SCORE_VOLTAGE = 12,
    FLYWHEEL_STOP_VOLTAGE = 0,
    FLYWHEEL_OUTY_VOLTAGE = -12
};


}