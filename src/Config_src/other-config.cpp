#include "Config/other-config.h"

using namespace vex;

using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

controller BigBrother = controller(primary);

motor Flywheel = motor(PORT19, ratio6_1, true);
motor IntakeL = motor(PORT18, ratio6_1, false);
motor IntakeR = motor(PORT6, ratio6_1, true);
motor Indexer = motor(PORT5, ratio6_1, false);


triport Expander21 = triport(PORT21);
line bottomLine = line(Expander21.F);
line middleLine = line(Expander21.G);
line topLine = line(Expander21.H);