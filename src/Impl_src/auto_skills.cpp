#include "Impl/auto_skills.h"
#include "Impl/api.h"
#include "Impl/goal.h"
task indexTask;

void outyy();
void testAutoSkills() {

  Goal1.atGoal = false;
  Goal2.atGoal = false;
  Goal3.atGoal= false;
  LOG("Running Test Skills!");
  task intakes(intakeTask);
  task taskedIndex(indexerTask);
  //task fly(flywheelTask);
 // FlywheelStopWhenTopDetected = true;
  IndexerStopWhenMiddleDetected = true;
  BigBrother.ButtonA.pressed( outyy );

 


}


void outyy() {
   outy = true;
}
void runAutoSkills() {

  LOG("Running Skills!");
  //PATH 1 (Starting position to first goal)
  

 /*  chassis.driveStraightFeedforward(6.5_in);
  chassis.turnToDegreeGyro(-65.0_deg);
  std::cout <<"Done Turning" <<std::endl;
  task intakeSpin(intakeTask); //start intakes to pick up first ball

  chassis.driveStraightFeedforward(34.0_in);
  chassis.turnToDegreeGyro(-130.0_deg);
  std::cout <<"Done Turning" <<std::endl;
  task indexTask(indexerTask); //index up to line sensor
  chassis.driveStraightFeedforward(21.0_in); */

  //PATH 2 (first goal to second goal)




  //PATH 3 (second goal to third goal)



  //task indexTask(indexerTask);
  //task spinFly(flywheelTask);
  //stopWhenTopDetected = true;
  //chassis.leftFront.spinFor(fwd,360, degrees);
  
  //indexTask.resume();


}


