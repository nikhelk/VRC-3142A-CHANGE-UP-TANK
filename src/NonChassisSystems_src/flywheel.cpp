#include "NonChassisSystems/flywheel.h"

bool startFlyDecel = false;
int flywheelTask()
{
  double slew = 0;
  while (true)
  {
    Flywheel.spin(fwd, slew, volt);
    if (slew > 12)
      slew = 12;
    if (!startFlyDecel)
      slew += .1;
    else
      slew -= .1;
    task::sleep(5);
  }
}

int outyTask()
{
  while (true)
  {
    Flywheel.spin(fwd, -12, volt);
    task::sleep(5);
  }
}