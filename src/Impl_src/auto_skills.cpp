#include "Impl/auto_skills.h"
#include "Impl/api.h"
task indexTask;
void runAutoSkills() {
  //task indexTask(indexerTask);
  //task spinFly(flywheelTask);
  /*
  
  chassis.turnToDegreeGyro(-65.0_deg);
  std::cout <<"DONE" <<std::endl;
  task intakeSpin(intakeTask);

  chassis.driveStraightFeedforward(34.0_in);
   chassis.turnToDegreeGyro(-130.0_deg);
  std::cout <<"DONE" <<std::endl;
  task indexTask(indexerTask);
  chassis.driveStraightFeedforward(21.0_in);*/
  //task indexTask(indexerTask);
  //stopWhenTopDetected = true;
  //chassis.leftFront.spinFor(fwd,360, degrees);
  
  chassis.driveStraightFeedforward(70.0_in);

  task::sleep(2000);
  //indexTask.resume();

  

  
}

