#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront = motor(PORT11, ratio18_1, false);
motor rightFront = motor(PORT13, ratio18_1, true);
motor leftBack = motor(PORT12, ratio18_1, false);
motor rightBack = motor(PORT16, ratio18_1, true);
encoder EncoderG = encoder(Brain.ThreeWirePort.G);
inertial inert = inertial(PORT7);
line Line1 = line(Brain.ThreeWirePort.A);
line Line2 = line(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);
motor IntakeL = motor(PORT4, ratio6_1, false);
motor IntakeR = motor(PORT3, ratio6_1, false);
motor Flywheel = motor(PORT2, ratio6_1, false);
motor Indexer = motor(PORT1, ratio6_1, false);
/*vex-vision-config:begin*/
vision Vision = vision (PORT15, 50);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}