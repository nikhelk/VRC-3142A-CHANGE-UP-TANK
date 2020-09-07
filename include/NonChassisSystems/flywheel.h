#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"


using namespace vex;

namespace Scorer{

int flywheelTask();

void outyTask();

extern bool outy;

extern bool FlywheelStopWhenTopDetected;

extern bool scored;



}