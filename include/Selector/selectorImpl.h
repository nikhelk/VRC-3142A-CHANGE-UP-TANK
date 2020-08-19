#pragma once
#include "Impl/auto_skills.h"
#include "selectorAPI.h"

/* ***************************************************************************************************** */

// We would like to thank jpearman and walshbots for providing us a template for the autonomous selector

// <https://www.vexforum.com/t/walshbots-autonomous-feature-selector/51534>

// <https://www.vexforum.com/t/can-anyone-explain-jpearmans-code-buttons-one/51060/5>

/* ****************************************************************************************************** */

/**
 * Creates background for the selector
 */

void makeBackground();

/**
   * Displays all of the  buttons in the selector
   * @param index of button pressed
   * @param state of press on button
   */

void displayAllButtonControls(int index, bool pressed);

/**
 * tasked function that is called in main
 */

int makeDisplay();

/**
 * callback function for when Brain Screen is pressed
 */

void userTouchCallbackPressed();

/**
 * callback function for when brain screen is "unpressed"
 */

void userTouchCallbackReleased();

/**
 * Changes pid values of a chassis system
 * @param type of system to change PID settings (e.g. straight or turn)
 */

void changeChassisPidValues(int type);

/**
 * Changes pid values of a non chassis system
 * @param type of system to change PID settings (e.g. flywheel or intake)
 */

void changeNonChassisPidValues(int type);

/**
 * Displays values made in the "settings menu"
 */

void displaySettingsValues();

/**
 * Displaus PID tuner values
 */

void displayPIDSettings();

/**
 * Displays all the PID tuner buttons
 * This had to be a standalone function (not part of ButtonGroupMaker) becuase it had different properties
 * @param index of button pressed
 * @param pressed state of press on button
 */

int displayPIDControls(int index, bool pressed);

/**
 * Generates the loading screen when the confirm button is pressed
 */

void makeLoadingScreen();

//externs that are used in mutiple src files
extern ButtonGroupMaker tabButtons;
extern ButtonGroupMaker confirmButton;
extern int confirmPress;

extern bool allianceBlue;
extern bool skills;