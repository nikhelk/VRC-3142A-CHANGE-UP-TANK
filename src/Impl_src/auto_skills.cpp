#include "Impl/auto_skills.h"
#include "Impl/api.h"
#include "Impl/goal.h"
task indexTask;

void outyy();
void testAutoSkills() {

  Goal2.atGoal = false;

  LOG("Running Test Skills!");
  task intakes(intakeTask);
  //intakeRunCont = true;

  task taskedIndex(indexerTask);
  
 // doOuty = true;
  task fly(flywheelTask);

  Goal1.atGoal = true;


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
   outy = true;
}
void runAutoSkills() {

  LOG("Running Skills!");
  //PATH 1 (Starting position to first goal)
  

   chassis.driveStraightFeedforward(8.0_in);
  chassis.turnToDegreeGyro(-65.0_deg);
  std::cout <<"Done Turning" <<std::endl;
  task intakeSpin(intakeTask); //start intakes to pick up first ball
  intakeRunCont = true;

  chassis.driveStraightFeedforward(34.0_in);
  chassis.turnToDegreeGyro(-130.0_deg);
  std::cout <<"Done Turning" <<std::endl;
  task indexTask(indexerTask); //index up to line sensor
  chassis.driveStraightFeedforward(30.0_in); 

  // Goal1.atGoal = true;
  // while(Goal1.atGoal){
  //   task::sleep(1000);
  // }

  task::sleep(2000);

  //PATH 2 (first goal to second goal)

  poseTracker.inert.setRotation(145, degrees);
 
  chassis.driveStraightFeedforward(20.0_in,true);
  backUp = false;



  task::sleep(100);

  chassis.turnToDegreeGyro(0.0_deg);

  intakeRunCont = true;

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
  backUp = false;
  task::sleep(100);

  chassis.turnToDegreeGyro(0.0_deg);

  intakeRunCont = true;

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


