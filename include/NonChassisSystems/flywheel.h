#pragma once
#include "Util/vex.h"
#include "Config/other-config.h"
#include "Config/chassis-config.h"
#include "Impl/goal.h"
using namespace vex;
int flywheelTask();

void outyTask();

extern bool startFlyDecel;
extern bool outy;
extern bool FlywheelStopWhenTopDetected;
extern bool doOuty;
extern bool doOuty2 ;
extern bool scored;
extern double scoreTimer;