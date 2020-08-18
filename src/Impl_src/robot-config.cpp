#include "Util/vex.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/literals.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;


FourMotorDrive testchassis(

    {PORT11, PORT12}, //Left motors (front and back)

    {PORT13, PORT16}, //Right motors (front and back)

    ratio18_1, //motor gear cartridge

    1.66667, //gear ratio

    {15.0_in, 4.0_in}, //Dimensions (trackWidth and wheel size)

    {1.5, 2.2}, //Limits (maxVelocity and maxAcceleration)

    {
        {.2, 0},   //Distance PD
        {0, 0},    //Angle PD
        {7, 79.8}, //Turn PD
    }

);

FourMotorDrive chassis(

    {PORT8, PORT7}, //Left motors (front and back)

    {PORT9, PORT10}, //Right motors (front and back)

    ratio18_1, //motor gear cartridge

    1.66667, //gear ratio

    {12.0_in, 3.25_in}, //Dimensions (trackWidth and wheel size)

    {1.2, 1.9}, //Limits (maxVelocity and maxAcceleration)

    {
        {.2, 0},  //Distance PD
        {0, 0},   //Angle PD
        {20, 0}, //Turn PD
    }

);

/*
Tracking poseTracker(4.0_in,2.75_in,360.0,{Tracking::A,Tracking::C,Tracking::G},PORT7);
*/
Tracking poseTracker({4, 4, 5}, 2.75, {Tracking::G, Tracking::C, Tracking::A}, PORT4);

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
triport Expander21 = triport(PORT21);

line bottomLine = line(Expander21.C);
line middleLine = line(Expander21.B);
line topLine = line(Expander21.A);
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