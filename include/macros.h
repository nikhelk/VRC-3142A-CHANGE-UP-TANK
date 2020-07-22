#pragma once //DO NOT REMOVE
#include "vex.h"

void indexerUser();
void flywheelUser();
void intakeUser();
bool getS1 ();
bool getS2 ();
bool getIsShooting();
void setMacroState();
std::string getState ();
enum visionSensor
{
  RED,
  BLUE,
  BLACK
};
enum botStates
{
  //Every possibility of ball positions found from two line sensors, a vision sensor for ball ejection and the wattage of the intakes.

  S2_EMPTY_E_SAME_I_HIGH,           //SENSOR2 EMPTY, EJECTOR CORRECT COLOR, INTAKE BALL DETECTED
  S2_EMPTY_E_SAME_I_LOW,            //SENSOR2 EMPTY, EJECTOR CORRECT COLOR, INTAKE EMPTY
  S2_EMPTY_E_OPP,                   //SENSOR2 EMPTY, EJECTOR OPPOSITE COLOR
  S2_EMPTY_E_EMPTY_S1_EMPTY_I_HIGH, //SENSOR2 EMPTY, SENSOR1 EMPTY, BALL DETECTED IN INTAKE
  S2_EMPTY_E_EMPTY_S1_EMPTY_I_LOW,  //SENSOR2 EMPTY, SENSOR1 EMPTY, EJECTOR EMPTY, INTAKE EMPTY
  S2_EMPTY_E_EMPTY_S1_BALL_I_HIGH,  //SENSOR2 EMPTY, EJECTOR EMPTY, SENSOR1 BALL DETECTED, INTAKE BALL DETECTED
  S2_EMPTY_E_EMPTY_S1_BALL_I_LOW,   //SENSOR2 EMPTY, EJECTOR EMPTY, SENSOR1 BALL DETECTED, INTAKE EMPTY
  S2_BALL_SHOOTING,                 //SENSOR2 BALL DETECTED, SHOOTING
  S2_BALL_N_SHOOTING_I_HIGH,        //SENSOR2 BALL DETECTED, NOT SHOOTING, INTAKE BALL DETECTED
  S2_BALL_N_SHOOTING_I_LOW          //SENSOR2 BALL DETECTED, NOT SHOOTING, INTAKE EMPTY
};

//extern bool isShooting;
//extern bool s1;
//extern bool s2;
//test2



bool getS1Status ();
bool getS2Status ();

