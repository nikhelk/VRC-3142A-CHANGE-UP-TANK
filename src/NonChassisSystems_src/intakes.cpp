#include "NonChassisSystems/intakes.h"
#include "Util/vex.h"
#include "Util/premacros.h"
static int ballCount =0;
void increment() {
  ballCount =1;
}
bool backUp = false;
bool intakeRunCont = false;
int intakeTask()
{
  while (true)
  {
  
    if(Goal1.atGoal) {
      intakeRunCont = false;
      backUp = false;
      
      while(ballCount <1) {
      IntakeL.spin(fwd, 10, volt);
      IntakeR.spin(fwd, 10, volt);
    if(intakeDetect.value(analogUnits::range10bit) < 615) {
      ballCount =1;
    }
    }

    IntakeL.spin(fwd, 0, volt);
    IntakeR.spin(fwd, 0, volt);

    }
    else if (backUp) {
    IntakeL.spin(fwd, 8, volt);
    IntakeR.spin(fwd, 8, volt);
    }
    else if(intakeRunCont) {
    IntakeL.spin(fwd, 12, volt);
    IntakeR.spin(fwd, 12, volt);

  }
    task::sleep(5);

  }
}
