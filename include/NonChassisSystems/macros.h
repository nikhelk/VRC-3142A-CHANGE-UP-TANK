#pragma once //DO NOT REMOVE

#include "Util/vex.h"
#include "Config/other-config.h"

using namespace vex;
/**
 * Handles all automation for driver control
 */

void macrosUser();

/**
 * Gets the state of line sensor 1
 * @return true if line sensor 1 detects ball
 */

bool getS1Status();

/**
 * Gets the state of line sensor 2
 * @return true if line sensor 2 detects ball
 */

bool getS2Status();

/**
 * Detects whether robot is in a shooting state
 * @return true if controller button L1 is pressed
 */

bool getIsShooting();

/**
 * Updates the enum botStates
 */

void setMacroState();

/**
 * enum visionSensor
 * Stores the state of the visionsensor for use with the sorter
 */

enum visionSensor
{
  RED,  /**< Red ball detected */
  BLUE, /**< Blue ball detected */
  BLACK /**< default; no ball detected */
};

/**
 * enum botStates
 * Stores every possibility of ball positions found from two line sensors, a vision sensor for ball ejection and the wattage of the intakes.
 */

enum botStates
{
  S2_EMPTY_E_SAME_I_HIGH,           /**< SENSOR2 EMPTY, EJECTOR SAME COLOR, INTAKE BALL DETECTED */
  S2_EMPTY_E_SAME_I_LOW,            /**< SENSOR2 EMPTY, EJECTOR SAME COLOR, INTAKE EMPTY */
  S2_EMPTY_E_OPP,                   /**< SENSOR2 EMPTY, EJECTOR OPPOSITE COLOR */
  S2_EMPTY_E_EMPTY_S1_EMPTY_I_HIGH, /**< SENSOR2 EMPTY, SENSOR1 EMPTY, BALL DETECTED IN INTAKE */
  S2_EMPTY_E_EMPTY_S1_EMPTY_I_LOW,  /**< SENSOR2 EMPTY, SENSOR1 EMPTY, EJECTOR EMPTY, INTAKE EMPTY */
  S2_EMPTY_E_EMPTY_S1_BALL_I_HIGH,  /**< SENSOR2 EMPTY, EJECTOR EMPTY, SENSOR1 BALL DETECTED, INTAKE BALL DETECTED */
  S2_EMPTY_E_EMPTY_S1_BALL_I_LOW,   /**< SENSOR2 EMPTY, EJECTOR EMPTY, SENSOR1 BALL DETECTED, INTAKE EMPTY */
  S2_BALL_SHOOTING,                 /**< SENSOR2 BALL DETECTED, SHOOTING */
  S2_BALL_N_SHOOTING_I_HIGH,        /**< SENSOR2 BALL DETECTED, NOT SHOOTING, INTAKE BALL DETECTED */
  S2_BALL_N_SHOOTING_I_LOW          /**< SENSOR2 BALL DETECTED, NOT SHOOTING, INTAKE EMPTY */
};
