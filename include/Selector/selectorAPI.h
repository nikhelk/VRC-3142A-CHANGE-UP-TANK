#pragma once
#include <vector>
#include "vex.h"
#include "premacros.h"


/* ***************************************************************************************************** */

// We would like to thank jpearman and walshbots for providing us a template for the autonomous selector

// <https://www.vexforum.com/t/walshbots-autonomous-feature-selector/51534>

// <https://www.vexforum.com/t/can-anyone-explain-jpearmans-code-buttons-one/51060/5>

/* ****************************************************************************************************** */

/**
 * Button constructor with properties
 */

struct button {
    int    xpos; //x-coordanate
    int    ypos; //y-coordanate
    int    width; 
    int    height;
    bool   state; //if its been pressed or not
    vex::color offColor; //color when state is "false"
    vex::color onColor; //color wgen state is "true" 
    const char *label; //name of button
};

struct pidValues {
    double    kP;
    double    kI;
    double    kD;
    const char *label;
};

/**
 * Class buttonGroupMaler. Use to make and use a button type
 */

class ButtonGroupMaker {
  public:

  std::vector<button> buttonList; //list of buttons
        
  /**
   * Button group constructor
   * @param initlizer list of buttons
   */

  ButtonGroupMaker(std::initializer_list<button> butonList);

  /**
   * gets the index of a button oressed in a button group
   * @param x coordinate of brain press
   * @param y coordinate of brain press
   * @return index of buton pressed in button group
   */

  int findButton(int16_t xpos, int16_t ypos);

  /**
   * Sets the state of all buttons in a group to false
   */
  void initButtons();

  /**
   * Displays all of the temporary buttons in a group
   * @param index of button pressed
   * @param state of press on button
   */

  int displayButtonControls(int index, bool pressed);

  /**
   * Displays all of the permamant buttons in a group (PID, tab, and confirm)
   * @param index of button pressed
   * @param state of press on button 
   * @param if button is permamant (always true)
   */
  int displayButtonControls(int index, bool pressed,bool permamant);

  /**
   * switches the button state
   * @param index of button pressed
   */
  void switchStates(int index);

    
}; 