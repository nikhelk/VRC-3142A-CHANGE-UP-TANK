#include "NonChassisSystems/intakes.h"
#include "Util/premacros.h"
#include "Util/vex.h"

namespace Intakes {

bool backUp = false;

bool intakeRunCont = false;

int intakeTask() {
  bool ballIn = false;

  while (true) {

    if (atGoal) {

      intakeRunCont = false;
      backUp = false;

      if (!ballIn) { //we only "de-score" one ball out of the goal so after we detect we don't take another one in

        IntakeL.spin(fwd, INTAKE_INDEX_BALL_VOLTAGE, volt);
        IntakeR.spin(fwd, INTAKE_INDEX_BALL_VOLTAGE, volt);

        if (intakeDetect.value(analogUnits::range10bit) < INTAKE_STOP_LINE_THRESHOLD) {
          ballIn = true;
        }
      }

      else { //if a ball is "descored" then stop the intakes
        IntakeL.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
        IntakeR.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
      }

    }

    else if (backUp) { //reverse the intakes as we back up

      ballIn = false; //roundabout way of "resetting" the bool as we backUp right after atGoal becomes false.

      IntakeL.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);

    }

    else if (intakeRunCont) { //run intakes at max voltage

      IntakeL.spin(fwd, INTAKE_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_VOLTAGE, volt);
    }

    task::sleep(10);
  }
}

} // namespace Intakes
