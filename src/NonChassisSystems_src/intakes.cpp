#include "NonChassisSystems/intakes.h"
#include "Util/vex.h"
#include "Util/premacros.h"

namespace Intakes {

bool backUp = false;

bool intakeRunCont = false;

static constexpr int INTAKE_VOLTAGE = 12;

static constexpr int STOP_VOLTAGE = 0;

static constexpr int BACKUP_VOLTAGE = -8;

static constexpr int BALL_DETECT_THRESHOLD = 615;

int intakeTask()
{
  bool ballIn = false;

  while (true)
  {
  
    if(atGoal) {
      intakeRunCont = false;
      backUp = false;
      
      if(!ballIn) {
        IntakeL.spin(fwd, 10, volt);
        IntakeR.spin(fwd, 10, volt);

        if(intakeDetect.value(analogUnits::range10bit) < BALL_DETECT_THRESHOLD) {
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

}
