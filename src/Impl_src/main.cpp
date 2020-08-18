/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nikhelkrishna                                             */
/*    Created:      Mon May 18 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "Util/vex.h"
#include "Impl/api.h"
#include "Impl/usercontrol.h"
#include "Impl/auto_skills.h"
using namespace vex;



competition Competition;
task autonSelect;
// A global instance of vex::brain used for printing to the V5 brain screen
// define your global instances of motors and other devices here
bool notSkills;
void pre_auto(void)
{
  chassis.setReverseSettings({true, true}, {false, false});
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.pressed(userTouchCallbackPressed);
  Brain.Screen.released(userTouchCallbackReleased);
  setOdomOrigin(0, 0, 0);
  while (poseTracker.inert.isCalibrating())
  {
    task::sleep(1000);
  }
  // make nice background
  makeBackground();
  // initial display
  task autonSelect(makeDisplay);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void autonomous(void)
{
  // autonSelect.stop();
  if (!(notSkills))
  {
    std::cout << "in skills!" << std::endl;
    chassis.setReverseSettings({true, true}, {false, false});
  }
  else
    std::cout << "not in skills" << std::endl;
  //driveStraight(2);
}

/*void usercontrol(void) {
  while(true) {

    task::sleep(20);
  }
}*/
void DRIVE(double leftVelocity, double rightVelocity) {
  chassis.leftFront.spin (fwd,leftVelocity, velocityUnits::rpm);
  chassis.leftBack.spin (fwd,leftVelocity, velocityUnits::rpm);
  chassis.rightFront.spin (fwd,rightVelocity, velocityUnits::rpm);
  chassis.rightBack.spin (fwd,rightVelocity, velocityUnits::rpm);
}

bool startFlyDecel = false;

task spinFly;
task spinIntakes;
task spinIndexer;

int main()
{

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auto();
  notSkills = true;
  while (inert.isCalibrating())
  {
    task::sleep(1000);
  }

  task trackPos(trackPosition);
 runAutoSkills();
 

  
  task::sleep(100);

  double time = Brain.Timer.time(timeUnits::sec);

  TrapezoidalMotionProfile trapp = TrapezoidalMotionProfile(1, 4, 0.8);
   double t = 0;
   double pose =0;
 /* while(t<trapp.m_totalTime) {
    double linearVel = trapp.calculateMpVelocity(t);
    double linearAcc = trapp.calculateMpAcceleration(t);
      pose += (linearVel*.01);

    DRIVE(179.0269326118058*linearVel*(2+14*0.05)/2,179.0269326118058*linearVel*(2-14*0.05)/2);
   // setVoltDrive(11.1*linearVel -lPower,11.1*linearVel - rPower);
   t += .01;
   
   //std::cout << linearVel << std::endl;
   
  task::sleep(10);
  }*/
  DRIVE(0,0);
  while (true)
  {
 
   // chassis.setDrive(0, 12);
    // std::cout << poseTracker.getInertialHeading() <<std::endl;
    //std::cout << poseTracker.getInertialHeading() << std::endl;
    //std::cout <//Left motors (front and back) << std::endl;
    /*
    
      
      Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
      Brain.Screen.setFillColor ("black");
      Brain.Screen.printAt(50,50,"%d",inert.isCalibrating());*/
    //printPosition();
   // std::cout << chassis.rightBack.ve()<<" " << chassis.rightFront.voltage()<<std::endl;;
    this_thread::sleep_for(10);
  }
}
