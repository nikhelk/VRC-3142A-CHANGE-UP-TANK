// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// Line2                line          B               
// Controller1          controller                    
// IntakeL              motor         4               
// IntakeR              motor         3               
// Flywheel             motor         2               
// Indexer              motor         1               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// Line2                line          B               
// Controller1          controller                    
// IntakeL              motor         4               
// IntakeR              motor         3               
// Flywheel             motor         2               
// Indexer              motor         1               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// Line2                line          B               
// Controller1          controller                    
// IntakeL              motor         4               
// IntakeR              motor         3               
// Flywheel             motor         2               
// Indexer              motor         1               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightFront           motor         13              
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// Line2                line          B               
// Controller1          controller                    
// IntakeL              motor         4               
// IntakeR              motor         3               
// Flywheel             motor         2               
// Indexer              motor         1               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         11              
// rightFront           motor         13              
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// Line2                line          B               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         11              
// rightFront           motor         13              
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// Line2                line          B               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         11              
// rightFront           motor         13              
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// Line1                line          A               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         11              
// rightFront           motor         13              
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      7               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         11              
// rightFront           motor         13              
// leftBack             motor         12              
// rightBack            motor         16              
// EncoderG             encoder       G, H            
// inert                inertial      18              
// ---- END VEXCODE CONFIGURED DEVICES ----
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

FourMotorDrive chassis( 

{PORT11,PORT12} , //Left motors (front and back)

{PORT13,PORT16} , //Right motors (front and back)

ratio18_1 , //motor gear cartridge

1.66667, //gear ratio

{15.0_in , 4.0_in}, //Dimensions (trackWidth and wheel size)

{42.0_inps,3.3_inps2} , //Limits (maxVelocity and maxAcceleration)

{
  { .2 , 0 },     //Distance PD
  { 0 , 0 },     //Angle PD
  { 7 , 0 },      //Turn PD
  }

);    


/*
Tracking poseTracker(4.0_in,2.75_in,360.0,{Tracking::A,Tracking::C,Tracking::G},PORT7);
*/
Tracking poseTracker({4,4,5},2.75,{Tracking::A,Tracking::C,Tracking::G});

competition Competition;
task autonSelect;
// A global instance of vex::brain used for printing to the V5 brain screen
// define your global instances of motors and other devices here
void pre_auto(void) {
  chassis.setReverseSettings({false,false}, {true,true});
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
  //driveStraight(2);
}

/*void usercontrol(void) {
  while(true) {

    task::sleep(20);
  }
}*/
int main() {

    // 4 lines, axis at position 120, 120
   /*
    int originX = 10;
    int width = 100;

    int originY = 10;
    int height = 100;

    int endX = originX + width;
    int endY = originY + height;

    Brain.Screen.drawRectangle(originX, originY, width, height);
    graph g( 4, 0, 230 );

    // set line colors
    g.setColor(2, vex::color::green );
    g.setColor(1, vex::color::white );

    g.setColor(0, vex::color::red );
    g.setColor(3, vex::color::white );

    // and we are using separate tasks to add points to each line, this is a bit overkill
    //thread t1( sinTask1, static_cast<void *>(&g) );
    //

    thread t3( goalTask, static_cast<void *>(&g) );
    thread t4( currentTask, static_cast<void *>(&g) );
    thread t2( successTask, static_cast<void *>(&g) );*/
    //Competition.autonomous(autonomous);
    //Competition.drivercontrol(usercontrol);
    
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    pre_auto();
    /*while(inert.isCalibrating()) {
      task::sleep(1000);
    }*/
    task::sleep(1000);

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

