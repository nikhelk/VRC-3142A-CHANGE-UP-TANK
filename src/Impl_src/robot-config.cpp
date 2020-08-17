#include "Util/vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors

motor Flywheel = motor(PORT19, ratio6_1, true);
motor IntakeL = motor(PORT18, ratio6_1, false);
motor IntakeR = motor(PORT6, ratio6_1, true);
motor Indexer = motor(PORT5, ratio6_1, false);
encoder EncoderG = encoder(Brain.ThreeWirePort.G);
inertial inert = inertial(PORT7);
line Line1 = line(Brain.ThreeWirePort.A);
line Line2 = line(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}