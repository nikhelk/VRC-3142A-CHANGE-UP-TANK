#include "Impl/auto_skills.h"
#include "Impl/api.h"
#include <memory>

void outyy();
bool atGoal = false;
void testAutoSkills() {
  LOG("Running Test Skills!");
  
  task intakes(Intakes::intakeTask );

  task taskedIndex(Rollers::indexerTask);
  
  task fly(Scorer::flywheelTask);


  //chassis.driveStraightFeedforward(20.0_in);
  atGoal = true;
  waitUntil(!atGoal);
  chassis.driveStraightFeedforward(10.0_in,true);
  Intakes::IntakesStop = true;



  while(true) {
    task::sleep(100);
  }
  // LOG("backup: ", autoSkillBools.backUp, "stop", autoSkillBools.IntakesStop);

  // LOG("BRUHHH: ", autoSkillBools.FlywheelStopWhenTopDetected);
  //doOuty2 =true;
  //FlywheelStopWhenTopDetected = true;
  //IndexerStopWhenBottomDetected = true;
  //task::sleep(3000);
  //FlywheelStopWhenTopDetected = false;
 // Goal1.atGoal = true;
 // IndexerStopWhenMiddleDetected = true;

  /*
  poseTracker.inert.setRotation(136, degrees);
 
  chassis.driveStraightFeedforward(20.0_in,true);

  task::sleep(100);

  chassis.turnToDegreeGyro(-3.0_deg);

  chassis.driveStraightFeedforward(55.0_in);

  task::sleep(100);

  chassis.turnToDegreeGyro(-90.0_deg);

  chassis.driveStraightFeedforward(13.0_in); */


  //topLine.changed(increment);

  BigBrother.ButtonA.pressed( outyy );




}


void outyy() {
   Scorer::outy = true;
}
void runAutoSkills() {

  LOG("Running Skills!");
  //PATH 1 (Starting position to first goal)
  // task intakeSpin( Intakes::intakeTask ); //start intakes to pick up first ball
  // task indexTask( Rollers::indexerTask ); //index up to line sensor
  // task scorerTask( Scorer::flywheelTask );

  chassis.driveStraightFeedforward(8.0_in);
  chassis.turnToDegreeGyro(-65.0_deg);
  std::cout <<"Done Turning" <<std::endl;

  //Intakes::intakeRunCont = true;
  //Rollers::IndexerStopWhenTopDetected = true;

  chassis.driveStraightFeedforward(34.0_in);
  chassis.turnToDegreeGyro(-130.0_deg);
  std::cout <<"Done Turning" <<std::endl;
  
  chassis.driveStraightFeedforward(30.0_in); 

  atGoal = true;
  waitUntil(!atGoal);

  //PATH 2 (first goal to second goal)

  poseTracker.inert.setRotation(145, degrees);
 
  chassis.driveStraightFeedforward(20.0_in,true);
  //Intakes::backUp = false;



  task::sleep(100);

  chassis.turnToDegreeGyro(0.0_deg);

  //Intakes::intakeRunCont = true;

  chassis.driveStraightFeedforward(55.0_in);

  task::sleep(100);

  chassis.turnToDegreeGyro(-90.0_deg);

  chassis.driveStraightFeedforward(13.0_in);

  // Goal1.atGoal = true;
  // while(Goal1.atGoal)
  // {
  //   task::sleep(1000);
  // }

  

  //PATH 3 (second goal to third goal)



  poseTracker.inert.setRotation(90, degrees);

  chassis.driveStraightFeedforward(24.0_in,true);
 // Intakes::backUp = false;
  task::sleep(100);

  chassis.turnToDegreeGyro(0.0_deg);

 // Intakes::intakeRunCont = true;

  chassis.driveStraightFeedforward(50.0_in);
  task::sleep(100);

  chassis.turnToDegreeGyro(-140.0_deg);

  chassis.driveStraightFeedforward(30.0_in);

  




  //task indexTask(indexerTask);
  //task spinFly(flywheelTask);
  //stopWhenTopDetected = true;
  //chassis.leftFront.spinFor(fwd,360, degrees);
  
  //indexTask.resume();


}


