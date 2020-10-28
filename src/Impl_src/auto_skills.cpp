#include "Impl/auto_skills.h"
#include "Impl/api.h"


bool atGoal = false;

void runAutoSkills() {

  LOG("Running Auto Skills!");
  
  task intakes(Intakes::intakeTask );

  task taskedIndex(Rollers::indexerTask);
  
  task fly(Scorer::flywheelTask);



  chassis.driveStraightFeedforward(8.0_in);
  chassis.turnToDegreeGyro(-75.0_deg);

  Intakes::IntakesRunContinously = true;
  Scorer::FlywheelStopWhenTopDetected = true;
  Rollers::IndexerStopWhenTopDetected = true;

  chassis.driveStraightFeedforward(41.0_in);
  chassis.turnToDegreeGyro(-125.0_deg);
  chassis.driveStraightFeedforward(20.0_in);

  // at goal macro
  atGoal = true;
  waitUntil(!atGoal);
  chassis.driveStraightFeedforward(17.0_in,true);
  task::sleep(100);
  Intakes::backUp = false;
  Intakes::IntakesStop = true;


  chassis.turnToDegreeGyro(0.0_deg);
  Intakes::IntakesStop = false;
  Intakes::IntakesRunContinously = true;
  Scorer::FlywheelStopWhenTopDetected = true;
  Rollers::IndexerStopWhenTopDetected = true;

  chassis.driveStraightFeedforward(53.0_in);
  chassis.turnToDegreeGyro(-90.0_deg);
  chassis.driveStraightFeedforward(10.0_in);


  // at goal macro
  task::sleep(3000);
  atGoal = true;
  waitUntil(!atGoal);
  chassis.driveStraightFeedforward(17.0_in,true);
  task::sleep(100);
  Intakes::backUp = false;
  Intakes::IntakesStop = true;




  while(true) {
    task::sleep(100);
  }


}


