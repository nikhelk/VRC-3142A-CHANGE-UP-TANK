#include "NonChassisSystems\intakes.h"


int intakeTask()
{
  while (true)
  {
    IntakeL.spin(fwd, 12, volt);
    IntakeR.spin(fwd, 12, volt);
    task::sleep(5);
  }
}