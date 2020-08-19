#include "Util/vex.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/literals.h"
#include "ChassisSystems/odometry.h"
#include "Config/other-config.h"
using namespace vex;

//TEST CHASSIS CONFIG
/* FourMotorDrive testchassis(

    {PORT11, PORT12}, //Left motors (front and back)

    {PORT13, PORT16}, //Right motors (front and back)

    ratio18_1, //motor gear cartridge

    1.66667, //gear ratio

    {15.0_in, 4.0_in}, //Dimensions (trackWidth and wheel size)

    {1.5, 2.2}, //Limits (maxVelocity and maxAcceleration)

    {
        {0, 0},   //Distance PD (deprecated thanks to feedforwards control)
        {0, 0},    //Angle PD (deprecated thanks to feedforwards control)
        {7, 79.8}, //Turn PD (used for inertial sensor based turns)
    }

); */

FourMotorDrive chassis(

    {PORT8, PORT7}, //Left motors (front and back)

    {PORT9, PORT10}, //Right motors (front and back)

    ratio18_1, //motor gear cartridge

    1.66667, //gear ratio

    {12.0_in, 3.25_in}, //Dimensions (trackWidth and wheel size)

    {1.2, 1.9}, //Limits (maxVelocity and maxAcceleration)

    {
        {.2, 0}, //Distance PD (deprecated thanks to feedforwards control)
        {0, 0},   //Angle PD (deprecated thanks to feedforwards control)
        {20, 0},  //Turn PD (used for inertial sensor based turns)
    }

);

/**
 * This is the implementation of the poseTracker.
 * The only part that we use is the interial port. We don't use the quad encoders becuase since the encoders were very close together,
 * the turning resolution was bad so we resorted to using the integrated motor encoders in the motors
 */
Tracking poseTracker({4, 4, 5}, //Tracking wheel distances (left, right, back)
 2.75, //Tracking wheel radius
 {Tracking::G, Tracking::C, Tracking::A}, //Tracking wheel ports (left, right, back)
 PORT7); //Intertial Sensor port

\


encoder testEncoder = encoder(Brain.ThreeWirePort.A);


// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices in the chassis
 */
void initChassis(void)
{
  chassis.setReverseSettings( {true, true} , {false, false} );
  // chassis.setReverseSettings({false, false}, {true, true});
  chassis.resetPosition();
  chassis.resetRotation();

  setOdomOrigin(0, 0, 0);

  poseTracker.inert.calibrate();

  while (poseTracker.inert.isCalibrating()) {

    Controller1.Screen.print("Calibrating Inert");

    Controller1.Screen.clearLine(3);
  }

  Controller1.Screen.print("DONE!");
}