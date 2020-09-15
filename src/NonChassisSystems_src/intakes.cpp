#include "NonChassisSystems/intakes.h"
#include "Util/premacros.h"
#include "Util/vex.h"

namespace Intakes {


int intakeTask(void* toBeCastedBools) {
  bool ballIn = false;

  globalBools* instance = static_cast<globalBools*>(toBeCastedBools);

  instance->resetBools();

  while (true) {
    LOG("Intake BackUp status: " , instance->backUp);

    if (atGoal) {

      instance->IntakesRunContinously = false;
      instance->backUp = false;
      instance->IntakesStop = false;

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

     if (instance->backUp) { //reverse the intakes as we back up
     instance->IntakesRunContinously = false;
     instance->IntakesStop = false;
      LOG("BACKING UP");
      ballIn = false; //roundabout way of "resetting" the bool as we backUp right after atGoal becomes false.

      IntakeL.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_BACK_UP_VOLTAGE, volt);

    }

     if (instance->IntakesRunContinously) { //run intakes at max voltage
     instance->backUp = false;
     instance->IntakesStop = false;
     LOG("INTAKES AT FULL SPEED");

      IntakeL.spin(fwd, INTAKE_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_VOLTAGE, volt);
    }

    if (instance->IntakesStop) { //run intakes at max voltage
     instance->backUp = false;
     instance->IntakesRunContinously = false;

      IntakeL.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
      IntakeR.spin(fwd, INTAKE_STOP_VOLTAGE, volt);
    }

    task::sleep(10);
  }
}

} // namespace Intakes
