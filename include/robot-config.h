using namespace vex;

extern brain Brain;

using signature = vision::signature;

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
extern motor IntakeL;
extern motor IntakeR;
extern motor Flywheel;
extern motor Indexer;
extern signature Vision__SIG_1;
extern signature Vision__SIG_2;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );