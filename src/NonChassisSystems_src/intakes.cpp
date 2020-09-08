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

      if (!ballIn) {
        IntakeL.spin(fwd, INTAKE_INDEX_BALL_VOLTAGE, volt);
        IntakeR.spin(fwd, INTAKE_INDEX_BALL_VOLTAGE, volt);

        if (intakeDetect.value(analogUnits::range10bit) <
            INTAKE_STOP_LINE_THRESHOLD) {
          ballIn = true;
        }
      }

      else {
        IntakeL.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
        IntakeR.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
      }

    }

    else if (backUp) {

      IntakeL.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);

    }

    else if (intakeRunCont) {

      IntakeL.spin(fwd, INTAKE_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_VOLTAGE, volt);
    }

    task::sleep(5);
  }
}

} // namespace Intakes
