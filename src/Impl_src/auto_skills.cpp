#include "Impl/auto_skills.h"
#include "Impl/api.h"
void runAutoSkills() {
  //task indexTask(indexerTask);
  //task spinFly(flywheelTask);
  
  chassis.driveStraightFeedforward(6.5_in);
  chassis.turnToDegreeGyro(-65.0_deg);
  std::cout <<"DONE" <<std::endl;
  task intakeSpin(intakeTask);
  chassis.driveStraightFeedforward(34.0_in);
   chassis.turnToDegreeGyro(-130.0_deg);
  std::cout <<"DONE" <<std::endl;
  task indexTask(indexerTask);
  chassis.driveStraightFeedforward(21.0_in);

}

