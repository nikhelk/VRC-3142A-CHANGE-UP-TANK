#pragma once

#include "Util/vex.h"
#include "Impl/api.h"
void runAutoSkills();

void testAutoSkills();

extern bool atGoal;

struct globalBools {
  bool FlywheelStopWhenTopDetected;
  bool scored;
  bool backUp;
  bool IntakesRunContinously;
  bool IndexerStopWhenTopDetected;
  bool IndexerStopWhenMiddleDetected;
  bool IndexerStopWhenBottomDetected;
  bool IndexerRunContinuously;

  void resetBools() {
    FlywheelStopWhenTopDetected =
    scored =
    backUp =
    IntakesRunContinously =
    IndexerStopWhenTopDetected =
    IndexerStopWhenMiddleDetected =
    IndexerStopWhenBottomDetected =
    IndexerRunContinuously =
    false;
  }

};