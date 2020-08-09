/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nikhelkrishna                                             */
/*    Created:      Mon May 18 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

#include "Selector\selectorImpl.h"

using namespace vex;

FourMotorDrive testchassis( 

{PORT11,PORT12} , //Left motors (front and back)

{PORT13,PORT16} , //Right motors (front and back)

ratio18_1 , //motor gear cartridge

1.66667, //gear ratio

{15.0_in , 4.0_in}, //Dimensions (trackWidth and wheel size)

{42.0_inps,3.3_inps2} , //Limits (maxVelocity and maxAcceleration)

{
  { .2 , 0 },     //Distance PD
  { 0 , 0 },     //Angle PD
  { 7 , 79.8 },      //Turn PD
}

);    
FourMotorDrive chassis( 

{PORT11,PORT12} , //Left motors (front and back)

{PORT9,PORT10} , //Right motors (front and back)

ratio18_1 , //motor gear cartridge

1.66667, //gear ratio

{15.0_in , 4.0_in}, //Dimensions (trackWidth and wheel size)

{42.0_inps,3.3_inps2} , //Limits (maxVelocity and maxAcceleration)

{
  { .2 , 0 },     //Distance PD
  { 0 , 0 },     //Angle PD
  { 7 , 79.8 },      //Turn PD
}

);    

/*
Tracking poseTracker(4.0_in,2.75_in,360.0,{Tracking::A,Tracking::C,Tracking::G},PORT7);
*/
Tracking poseTracker({4 , 4 ,5 },2.75,{Tracking::A,Tracking::C,Tracking::G});

competition Competition;
task autonSelect;
// A global instance of vex::brain used for printing to the V5 brain screen
// define your global instances of motors and other devices here
bool notSkills;
void pre_auto(void) {
  chassis.setReverseSettings({true,true}, {false,false});
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.pressed( userTouchCallbackPressed );
  Brain.Screen.released( userTouchCallbackReleased );
  setOdomOrigin(0,0,0);
  while(poseTracker.inert.isCalibrating()) {
    task::sleep(1000);
  }
    // make nice background
  makeBackground();
    // initial display
  task autonSelect(makeDisplay);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void autonomous(void) {
 // autonSelect.stop();
  if(!(notSkills))
    std::cout << "in skills!" <<std::endl;
  else
    std::cout <<"not in skills" << std::endl;
  //driveStraight(2);
}

/*void usercontrol(void) {
  while(true) {

    task::sleep(20);
  }
}*/
int main() {

    
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    pre_auto();
    notSkills = true;
    while(inert.isCalibrating()) {
      task::sleep(1000);
    }

    task trackPos(trackPosition);
    task::sleep(100);
    //chassis.turnToDegreeGyro(-90);
  //  task::sleep(3000);
    //chassis.driveArc2(90, 20);
    //turnToDegree(180);
    //driveStraightFeedforward(50);
    double time = Brain.Timer.time(timeUnits::sec);
    //driveArcSortaWorks(90, 20);
    while(true) {
      //std::cout << poseTracker.getInertialHeading() << std::endl;
      //std::cout <//Left motors (front and back) << std::endl;
      /*
      
      Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
      Brain.Screen.setFillColor ("black");
      Brain.Screen.printAt(50,50,"%d",inert.isCalibrating());*/
     // printPosition();
      //std::cout <<chassis.turnPID.KD <<std::endl;;
      this_thread::sleep_for(10)  ;
       }
}

