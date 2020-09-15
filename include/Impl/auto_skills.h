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
  bool IntakesStop;
  bool IndexerStopWhenTopDetected;
  bool IndexerStopWhenMiddleDetected;
  bool IndexerStopWhenBottomDetected;
  bool IndexerRunContinuously;
  bool IndexerStop;

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