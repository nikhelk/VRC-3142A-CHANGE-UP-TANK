#include "NonChassisSystems/intakes.h"
#include "Util/vex.h"
#include "Util/premacros.h"

static bool ballIn = false;

bool backUp = false;

bool intakeRunCont = false;

int intakeTask()
{
  while (true)
  {
  
    if(atGoal) {
      intakeRunCont = false;
      backUp = false;
      
      if(!ballIn) {
        IntakeL.spin(fwd, 10, volt);
        IntakeR.spin(fwd, 10, volt);

        if(intakeDetect.value(analogUnits::range10bit) < 615) {
        ballIn = true;
        }
      }

      else {
        IntakeL.spin(fwd, 0, volt);
        IntakeR.spin(fwd, 0, volt);

      }

    }

    else if (backUp) {

      IntakeL.spin(fwd, -8, volt);
      IntakeR.spin(fwd, -8, volt);

    }

    else if(intakeRunCont) {

      IntakeL.spin(fwd, 12, volt);
      IntakeR.spin(fwd, 12, volt);

    }

    task::sleep(5);

  }
  
}
