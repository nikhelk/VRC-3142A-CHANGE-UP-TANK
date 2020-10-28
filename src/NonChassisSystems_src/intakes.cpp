#include "NonChassisSystems/intakes.h"
#include "Util/premacros.h"
#include "Util/vex.h"

namespace Intakes {

bool backUp = false;

bool IntakesRunContinously = false;

bool IntakesStop = false;



int intakeTask() {

  bool ballIn = false; //we havent intaked a ball in at the start of our program



  while (true) {
    if (atGoal) {

      IntakesRunContinously = false;
      backUp = false;
      IntakesStop = false;

      if (!ballIn) { //we only "de-score" one ball out of the goal so after we  detect we don't take another one in

        IntakeL.spin(fwd, INTAKE_INDEX_BALL_VOLTAGE, volt);
        IntakeR.spin(fwd, INTAKE_INDEX_BALL_VOLTAGE, volt);

        if (intakeDetect.value(analogUnits::range10bit) < INTAKE_STOP_LINE_THRESHOLD) { //once the line sensor detects a ball, we can set our ballIn value to true: stopping the intakes
          ballIn = true;
        }

      }

      else { //if a ball is "descored" then stop the intakes
        IntakeL.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
        IntakeR.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
      }

    }

     if (backUp) { //reverse the intakes as we back up

      LOG("BACKING UP");
      ballIn = false; //roundabout way of "resetting" the bool as we backUp right after atGoal becomes false. ( we always back up after at a goal)

      IntakeL.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);

    }

     if (IntakesRunContinously) { //run intakes at max voltage

     LOG("INTAKES AT FULL SPEED");

      IntakeL.spin(fwd, INTAKE_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_VOLTAGE, volt);
    }

    if (IntakesStop) { //run intakes at min voltage

      LOG("INTAKES STOPPED");

      IntakeL.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
    }

    task::sleep(10);
  }
}

} // namespace Intakes
