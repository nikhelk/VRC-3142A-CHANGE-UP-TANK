using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftFront;
extern motor rightFront;
extern motor leftBack;
extern motor rightBack;
extern encoder EncoderG;
extern inertial inert;
extern line Line1;
extern line Line2;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );