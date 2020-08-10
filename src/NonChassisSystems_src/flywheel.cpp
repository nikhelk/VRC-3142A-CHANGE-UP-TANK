#include "NonChassisSystems\flywheel.h"
#include "vex.h"

int flywheelTask()
{
  double slew = 0;
  while (true)
  {
    Flywheel.spin(reverse, slew, volt);
    if (slew > 12)
      slew = 12;
    if (!startFlyDecel)
      slew += .1;
    else
      slew -= .1;
    task::sleep(5);
  }
}