/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nikhelkrishna                                             */
/*    Created:      Mon May 18 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "Impl/api.h"
#include "Impl/auto_skills.h"
#include "Impl/usercontrol.h"
#include "Util/vex.h"

using namespace vex;

competition Competition;

void pre_auto(void) {

  initChassis();

  Brain.Screen.pressed( userTouchCallbackPressed ); // set up callback for brain screen press
  Brain.Screen.released( userTouchCallbackReleased ); // set up callback for brain screen release

  // make background
  makeBackground();
  // auton selector task
  task autonSelect( makeDisplay);
}

void autonomous(void) {}

int main() {

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auto();

  BigBrother.ButtonA.pressed( runAutoSkills ); //Run autonomous skills when button "A" is pressed on controller

  BigBrother.ButtonX.pressed( testAutoSkills );

  task trackPos(trackPosition);

  while (true) {
    this_thread::sleep_for(10);
  }
}
