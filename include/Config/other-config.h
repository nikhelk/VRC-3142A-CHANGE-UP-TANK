#pragma once
#include "Util/vex.h"

using namespace vex;

using signature = vision::signature;

extern brain Brain;

extern controller BigBrother;

extern motor IntakeL;
extern motor IntakeR;
extern motor Flywheel;
extern motor Indexer;

extern triport Expander21;
extern line bottomLine;
extern line middleLine;
extern line topLine;
extern line outyLine;

enum LineSensorThresolds {
  TOP_LINE_THRESHOLD = 711,
  TOP_LINE_EMPTY_THRESHOLD = 720,
  MIDDLE_LINE_THRESHOLD = 697,
  BOTTOM_LINE_THRESHOLD = 695,
  OUTY_LINE_THRESHOLD = 700,
  INTAKE_STOP_LINE_THRESHOLD = 615
};
