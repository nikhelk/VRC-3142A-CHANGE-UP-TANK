#include "NonChassisSystems/flywheel.h"
#include "Config/other-config.h"
bool startFlyDecel = false;
bool outy =false;
int flywheelTask()
{
  double slew = 0;
  while (true)
  {
    if(outy)
       Flywheel.spin(fwd, -12, volt);
    else
      Flywheel.spin(fwd, 12, volt);
    task::sleep(5);
  }
}

void outyTask()
{
  Flywheel.spin(fwd, -12, volt);
}