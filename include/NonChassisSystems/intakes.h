#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"


using namespace vex;

namespace Intakes {
int intakeTask();

extern bool backUp;

extern bool intakeRunCont;

enum IntakeVoltages {
    INTAKE_VOLTAGE = 12,
    INTAKE_STOP_VOLTAGE = 0,
    INTAKE_BACK_UP_VOLTAGE = -8,
    INTAKE_INDEX_BALL_VOLTAGE = 10,
};

}