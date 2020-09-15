#pragma once

#include "Util/vex.h"
#include "Impl/api.h"
void runAutoSkills();

void testAutoSkills();

extern bool atGoal;

struct globalBools {
  static bool FlywheelStopWhenTopDetected;
  static bool scored;
 static bool backUp;
 static bool IntakesRunContinously;
static  bool IntakesStop;
static  bool IndexerStopWhenTopDetected;
static  bool IndexerStopWhenMiddleDetected;
static  bool IndexerStopWhenBottomDetected;
 static bool IndexerRunContinuously;
 static bool IndexerStop;

  void resetBools() {
    FlywheelStopWhenTopDetected =
    scored =
    backUp =
    IntakesRunContinously =
    IndexerStopWhenTopDetected =
    IndexerStopWhenMiddleDetected =
    IndexerStopWhenBottomDetected =
    IndexerRunContinuously =
    IntakesStop =
    IndexerStop =
    false;
  }

};