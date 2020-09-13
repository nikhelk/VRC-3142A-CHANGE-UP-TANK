#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"
#include "Util/mathAndConstants.h"

using namespace vex;

namespace Intakes {
int intakeTask(void* toBeCastedBools);



enum IntakeVoltages {
    INTAKE_VOLTAGE = 12,
    INTAKE_STOP_VOLTAGE = 0,
    INTAKE_BACK_UP_VOLTAGE = -8,
    INTAKE_INDEX_BALL_VOLTAGE = 10,
};

}