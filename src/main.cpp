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

FourMotorDrive chassis( {PORT12,PORT13} , {PORT11,PORT16} , ratio18_1 , 1.66667);


Dimensions *chassisDimensions = new Dimensions(&chassis,15.0_in,3.25_in);Limits *chassisLimits = new Limits(&chassis, 42.0_inps,12.0_inps2);


Tracking poseTracker(4.0,2.75,360.0,{Tracking::A,Tracking::C,Tracking::G},PORT18);

competition Competition;
task autonSelect;
// A global instance of vex::brain used for printing to the V5 brain screen
// define your global instances of motors and other devices here
void pre_auto(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  delete chassisDimensions;
  delete chassisLimits;
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
  driveStraight(2);
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
    while(true) {
      /*
      Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
      Brain.Screen.setFillColor ("black");
      Brain.Screen.printAt(50,50,"%d",inert.isCalibrating());*/
      //printPosition();
      
      this_thread::sleep_for(10)  ;
       }
}

