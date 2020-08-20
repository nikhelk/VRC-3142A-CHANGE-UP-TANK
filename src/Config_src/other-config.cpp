#include "Config/other-config.h"

using namespace vex;

using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

motor Flywheel = motor(PORT19, ratio6_1, true);
motor IntakeL = motor(PORT18, ratio6_1, false);
motor IntakeR = motor(PORT6, ratio6_1, true);
motor Indexer = motor(PORT5, ratio6_1, false);


line Line1 = line(Brain.ThreeWirePort.A);
line Line2 = line(Brain.ThreeWirePort.B);
controller BigBrother = controller(primary);
triport Expander21 = triport(PORT21);

line bottomLine = line(Expander21.C);
line middleLine = line(Expander21.B);
line topLine = line(Expander21.A);