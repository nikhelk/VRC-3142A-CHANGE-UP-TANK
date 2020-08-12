#include "Selector\selectorAPI.h"
#include "Selector\selectorImpl.h"


/* ***************************************************************************************************** */

// We would like to thank jpearman and walshbots for providing us a template for the autonomous selector

// <https://www.vexforum.com/t/walshbots-autonomous-feature-selector/51534>

// <https://www.vexforum.com/t/can-anyone-explain-jpearmans-code-buttons-one/51060/5>

/* ****************************************************************************************************** */

//values store what tab selection on (used for debugging)
int tabSelection = -1;
int chassisSelection = -1;
int nonChassisSelection = -1;
// Button group definitions
ButtonGroupMaker tabButtons({
    {0, 0, 70, 30, false, 0x303030, 0xD0D0D0, "Auton"},
    {80, 0, 70, 30, false, 0x303030, 0xD0D0D0, "Set."},
    {160, 0, 70, 30, false, 0x303030, 0xD0D0D0, "PID"},
});

ButtonGroupMaker autonButtons({
    {30, 40, 60, 60, false, 0xE00000, 0x0000E0, "Ally"},
    {120, 40, 60, 60, false, 0x303030, 0xD0D0D0, "Start"},
    {210, 40, 60, 60, false, 0x303030, 0xD0D0D0, "Skills"},
});

ButtonGroupMaker settingButtons({
    {390, 200, 85, 30, false, 0x303030, 0x303030, "speed"},
    {30, 150, 60, 30, false, 0x303030, 0x303030, "up"},
    {150, 150, 60, 30, false, 0x303030, 0x303030, "down"},
});

ButtonGroupMaker pidToggleButtons({
    {300, 150, 60, 40, false, 0x303030, 0x303030, "Chassis"},
    {120, 40, 60, 30, false, 0x303030, 0x303030, "up"},
    {120, 90, 60, 30, false, 0x303030, 0x303030, "down"},
    {200, 40, 60, 30, false, 0x303030, 0x303030, "up"},
    {200, 90, 60, 30, false, 0x303030, 0x303030, "down"},
    {280, 40, 60, 30, false, 0x303030, 0x303030, "up"},
    {280, 90, 60, 30, false, 0x303030, 0x303030, "down"},
});

ButtonGroupMaker pidChassisTabButtons({

    {30, 90, 60, 30, false, 0x303030, 0xD0D0D0, "Dist."},
    {30, 140, 60, 30, false, 0x303030, 0xD0D0D0, "Angle"},
    {30, 190, 60, 30, false, 0x303030, 0xD0D0D0, "Turn"},
});

ButtonGroupMaker pidNonChassisTabButtons({

    {30, 90, 60, 30, false, 0x303030, 0xD0D0D0, "leftFly"},
    {30, 140, 60, 30, false, 0x303030, 0xD0D0D0, "rightFly"},
    {30, 190, 60, 30, false, 0x303030, 0xD0D0D0, "leftIntake"},
    {240, 210, 60, 30, false, 0x303030, 0xD0D0D0, "rightIntake"},
});

pidValues chassisPidControllers[] = {
    {1, 2, 3, "distance"}, //lateral pid values
    {4, 5, 6, "angle"},    //anglespid values
    {7, 8, 9, "turn"}      //turn pid values
};

ButtonGroupMaker hiButtons({

    {30, 90, 60, 30, false, 0x303030, 0xD0D0D0, "leftFly"},
    {30, 140, 60, 30, false, 0x303030, 0xD0D0D0, "rightFly"},
    {30, 190, 60, 30, false, 0x303030, 0xD0D0D0, "leftIntake"},
    {240, 210, 60, 30, false, 0x303030, 0xD0D0D0, "rightIntake"},
});

pidValues nonChassisPidControllers[] = {
    {1, 2, 3, "leftFly"},          //leftFly pid values
    {4, 5, 6, "rightFly"},         //leftIntake pid values
    {34, 324, 23, "leftIntake"},   //rightFly pid values
    {12, 123, 321, "rightIntake"}, //righttIntake pid values
};

enum tabID {
  AUTON,
  SETTINGS,
  PID
};

ButtonGroupMaker confirmButton({{390, 120, 50, 50, false, 0x303030, 0x303030, "confirm"}});

std::string settings[] = {"speed", "angle"};              //settings buttons names
double doubleSettings[] = {50, 50};                       //settings buttons values
int settingsLen = sizeof(settings) / sizeof(settings[0]); //size of the setting button array

std::string pidToggle[] = {"chassis", "non-chassis"};          //pid menu names
int pidSettingsLen = sizeof(pidToggle) / sizeof(pidToggle[0]); //size of pid menu names (2)

void makeBackground()
{
  Brain.Screen.setFillColor(vex::color(0x404040));
  Brain.Screen.setPenColor(vex::color(0x404040));
  Brain.Screen.drawRectangle(0, 0, 480, 120);
  Brain.Screen.setFillColor(vex::color(0x808080));
  Brain.Screen.setPenColor(vex::color(0x808080));
  Brain.Screen.drawRectangle(0, 120, 480, 120);
}

int countSettingsPress = 0;    //number of times the settings switch has been pressed
int countPidSettingsPress = 0; //number of times the pid settings switch has been pressed
bool togglePressed = false;    //state of a settings toggle button press
bool togglePidPressed = false; //state of a pid settings toggle button press

void changeChassisPidValues(int type)
{
  /**
   * enum pidChassisToggles. Keeps track of what value to change depending on press
   */

  enum pidChassisToggles
  {
    SETTINGS_TOGGLE,
    INCREASE_KP,
    DECREASE_KP,
    INCREASE_KI,
    DECREASE_KI,
    INCREASE_KD,
    DECREASE_KD,
  };

  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();

  int valueIndex = pidToggleButtons.findButton(xpos, ypos); //which toggle button is pressed
  switch (valueIndex)
  {
    case SETTINGS_TOGGLE:
      break;
    case INCREASE_KP:
      chassisPidControllers[type].kP += 2;
      break;
    case DECREASE_KP:
      chassisPidControllers[type].kP -= 2;
      break;
    case INCREASE_KI:
      chassisPidControllers[type].kI += 2;
      break;
    case DECREASE_KI:
      chassisPidControllers[type].kI -= 2;
      break;
    case INCREASE_KD:
      chassisPidControllers[type].kD += 2;
      break;
    case DECREASE_KD:
      chassisPidControllers[type].kD -= 2;
      break;
  }
}

void changeNonChassisPidValues(int type)
{
  /**
   * enum pidNonChassisToggles. Keeps track of what value to change depending on press
   */
  enum pidNonChassisToggles
  {
    SETTINGS_TOGGLE,
    INCREASE_KP,
    DECREASE_KP,
    INCREASE_KI,
    DECREASE_KI,
    INCREASE_KD,
    DECREASE_KD,
  };
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  int valueIndex = pidToggleButtons.findButton(xpos, ypos);
  switch (valueIndex)
  {
    case SETTINGS_TOGGLE:
      break;
    case INCREASE_KP:
      nonChassisPidControllers[type].kP += 2;
      break;
    case DECREASE_KP:
      nonChassisPidControllers[type].kP -= 2;
      break;
    case INCREASE_KI:
      nonChassisPidControllers[type].kI += 2;
      break;
    case DECREASE_KI:
      nonChassisPidControllers[type].kI -= 2;
      break;
    case INCREASE_KD:
      nonChassisPidControllers[type].kD += 2;
      break;
    case DECREASE_KD:
      nonChassisPidControllers[type].kD -= 2;
      break;
  }
}

int confirmPress = 0; //number of times confirm button has beem pressed

void userTouchCallbackPressed()
{
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  if (confirmPress == 0)
  {                                                            //only register when we have not hit the confirm button
    int currentSettingsPos = countSettingsPress % settingsLen; // index of what setting we are on
    if ((index = tabButtons.findButton(xpos, ypos)) >= 0)
    {

      displayAllButtonControls(index, true);

    } //if we are in auton button menu
    if (tabButtons.buttonList[AUTON].state)
    {
      if ((index = autonButtons.findButton(xpos, ypos)) >= 0)
      {
        autonButtons.displayButtonControls(index, true);
      }
    }
    if (tabButtons.buttonList[SETTINGS].state)
    { //if we are in tabButton menu
      if ((index = settingButtons.findButton(xpos, ypos)) >= 0)
      {
        if (index == 0)
        { //if the settings toggle is pressed
          displayAllButtonControls(index, true);
          countSettingsPress++; //changing the setting menu
        }
        else if (index > 0)
        {
          togglePressed = true;
        }

        // Changes the values of the settings buttons
        // This is in a while loop to allow for increasing by press and hold
        while (togglePressed)
        {
          if (index == 1)
          { //if pressing increase
            displayAllButtonControls(index, true);
            doubleSettings[currentSettingsPos] += 5;
          }
          if (index == 2)
          { //if we are pressing decrease
            displayAllButtonControls(index, true);
            doubleSettings[currentSettingsPos] -= 5;
          }
          task::sleep(400);
        }
      }
    }
    if (tabButtons.buttonList[PID].state)
    { // if we are in the PID tuner menu
      if ((index = pidToggleButtons.findButton(xpos, ypos)) >= 0)
      { //display the "chassis" vs "non-chassis" toggle no matter what
        if (index == 0)
        {
          countPidSettingsPress++;

          displayAllButtonControls(index, true);
        }
        else if (index > 0)
        {
          togglePidPressed = true;
        }
      }
      if (!(pidToggleButtons.buttonList[0].state))
      { //i we are in the chassis menu of pid tuner
        if ((index = pidChassisTabButtons.findButton(xpos, ypos)) >= 0)
        {
          displayAllButtonControls(index, true);
        }
        while (togglePidPressed)
        { //similar to the settings button toggles
          for (int i = 0; i < pidChassisTabButtons.buttonList.size(); i++)
          {
            if (pidChassisTabButtons.buttonList[i].state)
            {

              displayAllButtonControls(index, true);

              if (Brain.Screen.pressing())
                changeChassisPidValues(i);
            }
          }
          if (!(Brain.Screen.pressing())) //make sure not to get stuck in loop!
            togglePidPressed = false;

          task::sleep(400);
        }
      }
      else
      { //if we are in the non-chassis pid menu
        if ((index = pidNonChassisTabButtons.findButton(xpos, ypos)) >= 0)
        {
          displayAllButtonControls(index, true);
        }
        while (togglePidPressed)
        {
          for (int i = 0; i < pidNonChassisTabButtons.buttonList.size(); i++)
          {
            if (pidNonChassisTabButtons.buttonList[i].state)
            {
              displayAllButtonControls(index, true);
              if (Brain.Screen.pressing())
                changeNonChassisPidValues(i);
            }
          }
          if (!(Brain.Screen.pressing()))
            togglePidPressed = false;
          task::sleep(400);
        }
      }
    }
  }
}
//values to be used from the seletor
//NOTE: This is not a final list of all variables
bool allianceBlue = false;
bool skills = false;

void userTouchCallbackReleased()
{
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  int currentSettingsPos = countSettingsPress % settingsLen;
  int currentPidSettingsPos = countPidSettingsPress % pidSettingsLen;
  if ((index = tabButtons.findButton(xpos, ypos)) >= 0 && confirmPress == 0)
  {

    // clear all buttons to false
    //this allows for tab buttons to be chosen induvitually, instead of all at once
    tabButtons.initButtons();

    tabButtons.switchStates(index); //set the pressed one to true

    tabSelection = index;

    displayAllButtonControls(index, false);
  }
  if (confirmPress == 0)
  {
    if ((index = confirmButton.findButton(xpos, ypos)) == 0)
    { //if we have confirmed our selction

      tabButtons.initButtons();
      confirmButton.switchStates(index);

      confirmPress += 1;

      //store variables made in selector
      allianceBlue = autonButtons.buttonList[0].state;
      skills = autonButtons.buttonList[2].state;

      Brain.Screen.clearScreen();

      //generate loading screen
      makeLoadingScreen();
    }
    if (tabButtons.buttonList[AUTON].state)
    {
      if ((index = autonButtons.findButton(xpos, ypos)) >= 0)
      {
        autonButtons.switchStates(index);

        autonButtons.displayButtonControls(index, false);
      }
    }
    if (tabButtons.buttonList[SETTINGS].state)
    {
      if ((index = settingButtons.findButton(xpos, ypos)) >= 0)
      {
        if (index == 0)
          settingButtons.buttonList[index].label = settings[currentSettingsPos].c_str(); //change the label of the setting button depending on toggle
        settingButtons.switchStates(index);
        togglePressed = false;
        displayAllButtonControls(index, false);
      }
    }
    if (tabButtons.buttonList[PID].state)
    {
      if ((index = pidToggleButtons.findButton(xpos, ypos)) >= 0)
      {
        if (index == 0)
          pidToggleButtons.buttonList[index].label = pidToggle[currentPidSettingsPos].c_str(); //change the label of the pidsetting button depending on toggle
        pidToggleButtons.switchStates(index);
        displayAllButtonControls(index, true);
        togglePidPressed = false;
      }

      if (!(pidToggleButtons.buttonList[0].state))
      {
        if ((index = pidChassisTabButtons.findButton(xpos, ypos)) >= 0)
        {
          pidChassisTabButtons.initButtons();

          pidChassisTabButtons.switchStates(index);

          chassisSelection = index;
          displayAllButtonControls(index, true);
        }
      }
      else
      {
        if ((index = pidNonChassisTabButtons.findButton(xpos, ypos)) >= 0)
        {
          pidNonChassisTabButtons.initButtons();
          pidNonChassisTabButtons.switchStates(index);
          nonChassisSelection = index;
          displayAllButtonControls(index, true);
        }
      }
    }
  }
}

void displaySettingsValues()
{
  Brain.Screen.setCursor(7, 7);
  Brain.Screen.print(settingButtons.buttonList[0].label);
  Brain.Screen.setCursor(7, 14);
  Brain.Screen.print(doubleSettings[countSettingsPress % settingsLen]);
  double speed = doubleSettings[0];
  double angle = doubleSettings[1];
  Brain.Screen.setCursor(9, 23);
  Brain.Screen.print("Speed: ");
  Brain.Screen.setCursor(9, 30);
  Brain.Screen.print(speed);
  Brain.Screen.setCursor(11, 23);
  Brain.Screen.print("Angle: ");
  Brain.Screen.setCursor(11, 30);
  Brain.Screen.print(angle);
}

void displayPIDSettings()
{
  if (!(pidToggleButtons.buttonList[0].state))
  {
    Brain.Screen.printAt(120, 85, "kP:%.2f", chassisPidControllers[chassisSelection].kP);
    Brain.Screen.printAt(210, 85, "kI:%.2f", chassisPidControllers[chassisSelection].kI);
    Brain.Screen.printAt(290, 85, "kD:%.2f", chassisPidControllers[chassisSelection].kD);
  }
  if ((pidToggleButtons.buttonList[0].state))
  {
    Brain.Screen.printAt(120, 85, "kP:%.2f", nonChassisPidControllers[nonChassisSelection].kP);
    Brain.Screen.printAt(210, 85, "kI:%.2f", nonChassisPidControllers[nonChassisSelection].kI);
    Brain.Screen.printAt(390, 85, "kD:%.2f", nonChassisPidControllers[nonChassisSelection].kD);
  }
}

int displayPIDControls(int index, bool pressed)
{

  pidToggleButtons.displayButtonControls(0, false);

  if (!(pidToggleButtons.buttonList[0].state))
  { //display chassis pid settings
    pidChassisTabButtons.displayButtonControls(0, false, false);
  }

  else
  { //display non chassis pid settings
    pidNonChassisTabButtons.displayButtonControls(0, false, false);
  }
  return 1;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/

void displayAllButtonControls(int index, bool pressed)
{
  vex::color c;

  Brain.Screen.setPenColor(vex::color(0xe0e0e0));
  if (confirmPress == 0)
  {
    //always display these buttons on the selector
    tabButtons.displayButtonControls(0, false, true);
    confirmButton.displayButtonControls(0, false, true);

    Brain.Screen.drawImageFromFile("logo_test.png", 160, 50);

    if (tabButtons.buttonList[AUTON].state) //display auton menu
      autonButtons.displayButtonControls(0, false);

    else if (tabButtons.buttonList[SETTINGS].state)
    { //display settings menu
      settingButtons.displayButtonControls(0, false);
      displaySettingsValues();
    }

    else if (tabButtons.buttonList[PID].state)
    { //display pid settings menu
      displayPIDControls(0, false);
      displayPIDSettings();
    }
  }
}

void makeLoadingScreen()
{

  // this function shows "a loading screen" of what features are loaded
  //Some of them are time-based and are just for show :)
  // But the clibration of the IMU is real time amd we can see it actually happening and know when it is done calibarting

  if (confirmButton.buttonList[0].state)
  { // check if we are in confirm menu
    double time = Brain.Timer.time(timeUnits::sec);
    double currentTime = 0;
    bool firstDone = false;
    bool secondDone = false;
    bool thirdDone = false;
    currentTime = Brain.Timer.time(timeUnits::sec) - time;
    while (currentTime < 2)
    {
      Brain.Screen.printAt(100, 100, "Generating Paths...");

      currentTime = Brain.Timer.time(timeUnits::sec) - time;
      //Brain.Screen.render();
      if (currentTime > 1.96)
      {
        firstDone = true;
        break;
      }
    }
    Brain.Screen.printAt(330, 100, "DONE");
    task::sleep(600);
    inert.calibrate();
    while (inert.isCalibrating())
    {
      Brain.Screen.printAt(100, 150, "Calibrating Sensors...");
      //Brain.Screen.render();
    }
    secondDone = true;
    if (secondDone)
      Brain.Screen.printAt(330, 150, "DONE");
    task::sleep(600);
    double time2 = Brain.timer(timeUnits::sec);
    double currentTime2 = 0;
    while (currentTime2 < 2)
    {
      Brain.Screen.printAt(100, 200, "Configuring Robot...");

      currentTime2 = Brain.Timer.time(timeUnits::sec) - time2;
      //Brain.Screen.render();
      if (currentTime2 > 1.95)
      {
        thirdDone = true;
        break;
      }
    }
    if (thirdDone)
      Brain.Screen.printAt(330, 200, "DONE");
    //Brain.Screen.printAt(100,150, "Calibrating Sensors...");
    // Brain.Screen.printAt(100,200, "Configuring Robot...");
    Brain.Screen.printAt(50, 50, "hi");
  }
}

int makeDisplay()
{
  displayAllButtonControls(0, false);

  /*while(1) {
    std::cout <<autonButtons[0].state << std::endl;
    this_thread::sleep_for(10);
  }*/
  return (-1);
}