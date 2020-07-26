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

using namespace vex;

FourMotorDrive chassis( {PORT11,PORT13} , {PORT11,PORT16} , ratio18_1 , 1.66667, 
{15.0_in , 4.0_in}, 

{42.0_inps,3} ,
{
  { 0 , 0 },     //Distance PD
  { 0 , 0 },     //Angle PD
  { 0 , 0},    //Turn PD
  }

);    




Tracking poseTracker(4.0_in,2.75_in,360.0,{Tracking::A,Tracking::C,Tracking::G},PORT18);

competition Competition;
task autonSelect;
// A global instance of vex::brain used for printing to the V5 brain screen
// define your global instances of motors and other devices here
void pre_auto(void) {
  chassis.leftBack.position(degrees);
  poseTracker.leftEncoder.position(degrees);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.pressed( userTouchCallbackPressed );
  Brain.Screen.released( userTouchCallbackReleased );
  setOdomOrigin(0,0,0);
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
  std::cout << "BROOOOOOO" <<std::endl;
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

    task trackPos(trackPositionGyro);
    task::sleep(100);
    //turnToDegree(90);
    //turnToDegree(180);
    //driveStraightFeedforward(50);
    double time = Brain.Timer.time(timeUnits::sec);
    driveArcSortaWorks(20,20);
    while(true) {
      /*
      Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
      Brain.Screen.setFillColor ("black");
      Brain.Screen.printAt(50,50,"%d",inert.isCalibrating());*/
      //printPosition();
      //std::cout <<chassis.turnPID.KD <<std::endl;;
      this_thread::sleep_for(10)  ;
       }
}

