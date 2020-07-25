
#include "vex.h"
botStates myBot;
visionSensor ejector = visionSensor::BLACK;
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


void setMacroState()
{
  if(getS2Status())
  {
    if(getIsShooting())
    {
      myBot = S2_BALL_SHOOTING;
    }
    else
    {
      if(IntakeL.power()>8)
      {
        myBot = S2_BALL_N_SHOOTING_I_HIGH;
        
      }
      else
      {
        myBot = S2_BALL_N_SHOOTING_I_LOW;
      }
    }

  }
  else
  {
    Vision.takeSnapshot(SIG_1);
    if (Vision.objects[0].exists)
    {
      if (IntakeL.power() > 8)
      {
        myBot = S2_EMPTY_E_SAME_I_HIGH;
      }
      else
      {
        myBot = S2_EMPTY_E_SAME_I_LOW;
      }
    }
    else
    {
      Vision.takeSnapshot(SIG_2);
      if (Vision.objects[0].exists)
      {
        myBot = S2_EMPTY_E_OPP;
      }
      else
      {
        if(getS1())
        {
          if(IntakeL.power()>8)
          {
            myBot = S2_EMPTY_E_EMPTY_S1_BALL_I_HIGH;
          }
          else
          {
            myBot = S2_EMPTY_E_EMPTY_S1_BALL_I_LOW;
          }
        }

        else
        {
          if(IntakeL.power()>8)
          {
            myBot = S2_EMPTY_E_EMPTY_S1_EMPTY_I_HIGH;
          }
          else
          {
            myBot = S2_EMPTY_E_EMPTY_S1_EMPTY_I_LOW;
          }
        }
      }
    }
  }
}
//bruhhhhh
bool getIsShooting()
{
  return (Controller1.ButtonL1.pressing());
}

void macrosUser()
{
  switch (myBot)
  {
    case S2_EMPTY_E_SAME_I_HIGH:
      break;
    case S2_EMPTY_E_SAME_I_LOW:
      break;
    case S2_EMPTY_E_OPP:
      break;
    case S2_EMPTY_E_EMPTY_S1_EMPTY_I_HIGH:
      break;
    case S2_EMPTY_E_EMPTY_S1_EMPTY_I_LOW:
      break;
    case S2_EMPTY_E_EMPTY_S1_BALL_I_HIGH:
      break;
    case S2_EMPTY_E_EMPTY_S1_BALL_I_LOW:
      break;
    case S2_BALL_SHOOTING:
      break;
    case S2_BALL_N_SHOOTING_I_HIGH:
      break;
    case S2_BALL_N_SHOOTING_I_LOW:
      break;
  }
}
