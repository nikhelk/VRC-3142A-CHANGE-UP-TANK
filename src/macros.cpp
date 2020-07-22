
#include "vex.h"
visionSensor ejector = visionSensor::BLACK;
botStates myBot;
bool getS1 ();
bool getS1Status ()
{
  if (Line1.value(analogUnits::range10bit)>3000)
    {
      return true;
    }
  else 
  {
    return false;
  }
}

bool getS2Status()
{
  if (Line2.value(analogUnits::range10bit)>3000)
  {
    return true;
  }
  else 
  {
    return false;
  }
}


void setMacroState() {


}


bool getIsShooting()
{
  return (Controller1.ButtonL1.pressing());
}

void indexerUser()
{
  switch (myBot)
  {
  }
}

void flywheelUser()
{

}
void intakeUser()
{
 
}