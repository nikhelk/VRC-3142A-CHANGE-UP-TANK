#include "ChassisSystems/chassisGlobals.h"

using namespace vex;

extern Tracking poseTracker;
extern FourMotorDrive testchassis;
extern FourMotorDrive chassis;

// VEXcode devices
extern encoder testEncoder;

extern brain Brain;


/**
 * Used to initialize code/tasks/devices in the chassis
 */
void initChassis(void);