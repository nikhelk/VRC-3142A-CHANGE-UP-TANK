#include "vex.h"
#include "premacros.h"
int   tabSelection = -1;
int chassisSelection = -1;
int nonChassisSelection = -1;
bool enableGraph = false;
void makeLoadingScreen();

// Button array definitions for each software button. The purpose of each button data structure
// is defined above.  The array size can be extended, so you can have as many buttons as you 
// wish as long as it fits.
ButtonGroupMaker tabButtons ( {
    {  0,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "Auton" },
    {  80,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "Set." },
    {  160,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "PID" },
});


ButtonGroupMaker autonButtons ( {
    {   30,  40, 60, 60,  false, 0xE00000, 0x0000E0, "Ally" },
    {  120,  40, 60, 60,  false, 0x303030, 0xD0D0D0, "Start" },
    {  210,  40, 60, 60,  false, 0x303030, 0xD0D0D0, "Simple" },
});

ButtonGroupMaker settingButtons ( {
    {  390,  200, 85, 30,  false, 0x303030, 0x303030, "speed" },
    {   30, 150, 60, 30,false, 0x303030, 0x303030,"up" },
    {  150, 150, 60, 30,false, 0x303030, 0x303030, "down" },
});

ButtonGroupMaker pidToggleButtons ( {
  {   300, 150, 60, 40,false, 0x303030, 0x303030,"Chassis" },
  {   120, 40, 60, 30,false, 0x303030, 0x303030,"up" },
  {  120, 90, 60, 30,false, 0x303030, 0x303030, "down" },
  {   200, 40, 60, 30,false, 0x303030, 0x303030,"up" },
  {  200, 90, 60, 30,false, 0x303030, 0x303030, "down" },
  {   280, 40, 60, 30,false, 0x303030, 0x303030,"up" },
  {  280, 90, 60, 30,false, 0x303030, 0x303030, "down" },
});

ButtonGroupMaker pidChassisTabButtons ( {
  
  {   30,  90, 60, 30,  false, 0x303030, 0xD0D0D0, "Dist." },
  {  30,  140, 60, 30,  false, 0x303030, 0xD0D0D0, "Angle" },
  {  30,  190, 60, 30,  false, 0x303030, 0xD0D0D0, "Turn" },
});

ButtonGroupMaker pidNonChassisTabButtons ( {
  
  {   30,  90, 60, 30,  false, 0x303030, 0xD0D0D0, "leftFly" },
  {  30,  140, 60, 30,  false, 0x303030, 0xD0D0D0, "rightFly" },
  {  30,  190, 60, 30,  false, 0x303030, 0xD0D0D0, "leftIntake" },
  {  240,  210, 60, 30,  false, 0x303030, 0xD0D0D0, "rightIntake" },
});

pidValues chassisPidControllers[] = {
  {1,2,3,"distance"}, //lateral 
  {4,5,6,"angle"},
  {7,8,9,"turn"} //turn
};


ButtonGroupMaker::ButtonGroupMaker(std::initializer_list<button> butonList) {

  this->buttonList.reserve(butonList.size());

  for (auto &aButton : butonList)  {
    buttonList.push_back(button
    { 
    aButton.xpos,
    aButton.ypos,
    aButton.width,
    aButton.height,
    aButton.state,
    aButton.offColor,
    aButton.onColor,
    aButton.label
    }
    );
  }
}

int ButtonGroupMaker::findButton(int16_t xpos, int16_t ypos) {
  int nButtons = this->buttonList.size();

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttonList[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

void ButtonGroupMaker::initButtons() {
    int nButtons = this->buttonList.size();

    for( int index=0;index < nButtons;index++) {

      this->buttonList[index].state = false;
    
    }
}

ButtonGroupMaker hiButtons( {
  
  {   30,  90, 60, 30,  false, 0x303030, 0xD0D0D0, "leftFly" },
  {  30,  140, 60, 30,  false, 0x303030, 0xD0D0D0, "rightFly" },
  {  30,  190, 60, 30,  false, 0x303030, 0xD0D0D0, "leftIntake" },
  {  240,  210, 60, 30,  false, 0x303030, 0xD0D0D0, "rightIntake" },
}
);


pidValues nonChassisPidControllers[] = {
  {1,2,3,"leftFly"}, //leftFly 
  {4,5,6,"rightFly"}, //leftIntake
  {34,324,23,"leftIntake"}, //rightFly
  {12,123,321,"rightIntake"}, //righttIntake
};

ButtonGroupMaker confirmButton( {
  { 390, 120, 50, 50, false, 0x303030, 0x303030, "confirm"}
});


std::string settings[] = {"speed","angle"};
double doubleSettings[] = {50,50};
int settingsLen = sizeof(settings)/sizeof(settings[0]);

std::string pidToggle[] = {"chassis","non-chassis"};
int pidSettingsLen = sizeof(pidToggle)/sizeof(pidToggle[0]);

void makeBackground() {
    Brain.Screen.setFillColor( vex::color(0x404040) );
    Brain.Screen.setPenColor( vex::color(0x404040) );
    Brain.Screen.drawRectangle( 0, 0, 480, 120 );
    Brain.Screen.setFillColor( vex::color(0x808080) );
    Brain.Screen.setPenColor( vex::color(0x808080) );
    Brain.Screen.drawRectangle( 0, 120, 480, 120 );
}
// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/




/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
int countSettingsPress = 0;
int countPidSettingsPress = 0;
bool togglePressed = false; 
bool togglePidPressed = false;


void 
changeChassisPidValues(int type) {
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  int valueIndex = pidToggleButtons.findButton( xpos, ypos );
    switch(valueIndex) {
      case 0:
        break;
      case 1:
        chassisPidControllers[type].kP += 2;
        break;
      case 2: 
        chassisPidControllers[type].kP -= 2;
        break;
      case 3:
        chassisPidControllers[type].kI += 2;
        break;
      case 4:
        chassisPidControllers[type].kI -=2;
        break;
      case 5:
        chassisPidControllers[type].kD +=2;
        break;
      case 6:
        chassisPidControllers[type].kD -= 2;
        break;
      }
}

void
changeNonChassisPidValues(int type ) {
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  int valueIndex = pidToggleButtons.findButton( xpos, ypos );
    switch(valueIndex) {
      case 0:
        break;
      case 1:
        nonChassisPidControllers[type].kP += 2;
        break;
      case 2: 
        nonChassisPidControllers[type].kP -= 2;
        break;
      case 3:
        nonChassisPidControllers[type].kI += 2;
        break;
      case 4:
        nonChassisPidControllers[type].kI -=2;
        break;
      case 5:
        nonChassisPidControllers[type].kD +=2;
        break;
      case 6:
        nonChassisPidControllers[type].kD -= 2;
        break;
      }
}




int confirmPress = 0;

void
userTouchCallbackPressed() {
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();
  if(confirmPress == 0) {
  int currentSettingsPos = countSettingsPress % settingsLen;
  if( (index = tabButtons.findButton( xpos, ypos )) >= 0 ) {
    displayButtonControls( index, true );
    }
  if(tabButtons.buttonList[0].state) {
    if( (index = autonButtons.findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
      }
    }
  if(tabButtons.buttonList[1].state) { 
    if( (index = settingButtons.findButton( xpos, ypos )) >= 0 ) {
      if (index == 0) {
        displayButtonControls( index, true );
        countSettingsPress ++;
        }
      else if(index >0) {
        togglePressed = true;
      }
      while(togglePressed) {
          if (index == 1) {
            displayButtonControls( index, true );
            doubleSettings[currentSettingsPos] += 5;
            }
          if (index == 2) {
            displayButtonControls( index, true );
            doubleSettings[currentSettingsPos] -= 5;
            }
          task::sleep(400);
        }
      }
    }
  if(tabButtons.buttonList[2].state) {
    if( (index = pidToggleButtons.findButton( xpos, ypos )) >= 0 ) {
      if (index ==0) {
        countPidSettingsPress ++;
        
        displayButtonControls( index, true );
        }
      else if( index > 0) {
        togglePidPressed = true;
        }
      }
    if(!(pidToggleButtons.buttonList[0].state)) {
      if( (index = pidChassisTabButtons.findButton( xpos, ypos )) >= 0 ) {
        displayButtonControls( index, true );
        }
      while(togglePidPressed) {
       for(int i = 0; i < pidChassisTabButtons.buttonList.size();i++) {
          if(pidChassisTabButtons.buttonList[i].state) {
            displayButtonControls( index, true );
            if(Brain.Screen.pressing())
              changeChassisPidValues(i);
            } 
          }
          if(!(Brain.Screen.pressing())) 
            togglePidPressed = false;
          task::sleep(400); 
        }
      }
    else {
      if( (index = pidNonChassisTabButtons.findButton( xpos, ypos )) >= 0 ) {
        displayButtonControls( index, true );
        }
      while(togglePidPressed){
        for(int i = 0; i < pidNonChassisTabButtons.buttonList.size(); i++) {
          if(pidNonChassisTabButtons.buttonList[i].state) {
            displayButtonControls( index, true );
            if(Brain.Screen.pressing())
              changeNonChassisPidValues(i);
            } 
          }
        if(!(Brain.Screen.pressing())) 
          togglePidPressed = false; 
        task::sleep(400);
        }
      }
    
    
    }

  }

}
bool allianceBlue = false;
bool simpleRun = false;
/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();
    int currentSettingsPos = countSettingsPress % settingsLen;
    int currentPidSettingsPos = countPidSettingsPress % pidSettingsLen;
    if( (index = tabButtons.findButton( xpos, ypos )) >= 0 && confirmPress == 0) {
      // clear all buttons to false, ie. unselected
      tabButtons.initButtons(); 

      // now set this one as true
      if( tabButtons.buttonList[index].state == true) {

      tabButtons.buttonList[index].state = false; 
      
      }
      else    {

      tabButtons.buttonList[index].state = true;
      }
      tabSelection = index;

      displayButtonControls( index, false );

      // save as auton selection
 
    }
    if(confirmPress == 0 ) {
    if((index = confirmButton.findButton( xpos,  ypos))==0) {
      tabButtons.initButtons();
      if( confirmButton.buttonList[index].state == true) {
        confirmButton.buttonList[index].state = false;}
        
        else    {
        confirmButton.buttonList[index].state = true;
        
        }
      confirmPress += 1;
      allianceBlue = autonButtons.buttonList[0].state;
      simpleRun = autonButtons.buttonList[2].state;
      Brain.Screen.clearScreen();
      makeLoadingScreen();
    }
    if(tabButtons.buttonList[0].state) {
      if( (index = autonButtons.findButton( xpos, ypos )) >= 0 ) {
        if( autonButtons.buttonList[index].state == true) {
        autonButtons.buttonList[index].state = false; 
        std::cout << autonButtons.buttonList[index].state <<std::endl;}
        
        else    {
        autonButtons.buttonList[index].state = true;
        }

        displayButtonControls( index, false );
      }
    }
    if(tabButtons.buttonList[1].state) {
      if( (index = settingButtons.findButton( xpos, ypos )) >= 0 ) {
        if(index ==0)
          settingButtons.buttonList[index].label = settings[currentSettingsPos].c_str();
        if( settingButtons.buttonList[index].state == true) {
        settingButtons.buttonList[index].state = false; }
        else    {
        settingButtons.buttonList[index].state = true;
        }
        togglePressed = false;
        displayButtonControls( index, false );
      }
    }
    if(tabButtons.buttonList[2].state) {
      if( (index = pidToggleButtons.findButton( xpos, ypos )) >= 0 ) {
        if(index == 0)
          pidToggleButtons.buttonList[index].label = pidToggle[currentPidSettingsPos].c_str();
        if( pidToggleButtons.buttonList[index].state == true) {
          pidToggleButtons.buttonList[index].state = false; }
          else    {
          pidToggleButtons.buttonList[index].state = true;
          }
          displayButtonControls( index, true );
          togglePidPressed = false;
        }
      

      if(!(pidToggleButtons.buttonList[0].state)) {
        if( (index = pidChassisTabButtons.findButton( xpos, ypos )) >= 0 ) {
          pidChassisTabButtons.initButtons();

          if( pidChassisTabButtons.buttonList[index].state == true) {
          pidChassisTabButtons.buttonList[index].state = false; }
          else    {
          pidChassisTabButtons.buttonList[index].state = true;
          }
          chassisSelection = index;
          displayButtonControls( index, true );
          }
        }
      else {
        if( (index = pidNonChassisTabButtons.findButton( xpos, ypos )) >= 0 ) {
          pidNonChassisTabButtons.initButtons();
          if( pidNonChassisTabButtons.buttonList[index].state == true) {
          pidNonChassisTabButtons.buttonList[index].state = false; }
          else    {
          pidNonChassisTabButtons.buttonList[index].state = true;
          }
          nonChassisSelection = index;
          displayButtonControls( index, true );
          }
        }
    }
    }
}


int ButtonGroupMaker::displayButtonControls(int index, bool pressed, bool permanant) {
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

  for(int i=0;i<this->buttonList.size();i++) {
    LOG("TEST");
    if( this->buttonList[i].state )
      c = this->buttonList[i].onColor;
    else
      c = this->buttonList[i].offColor;

    Brain.Screen.setFillColor( c );

      // button fill
    if( i == index && pressed == true ) 
      Brain.Screen.drawRectangle( this->buttonList[i].xpos, this->buttonList[i].ypos, this->buttonList[i].width, this->buttonList[i].height,c);
    else
      Brain.Screen.drawRectangle( this->buttonList[i].xpos, this->buttonList[i].ypos, this->buttonList[i].width, this->buttonList[i].height );

      // outline
    Brain.Screen.drawRectangle( this->buttonList[i].xpos, this->buttonList[i].ypos, this->buttonList[i].width, this->buttonList[i].height, vex::color::transparent );

    if(  this->buttonList[i].label != NULL )
      Brain.Screen.printAt( this->buttonList[i].xpos + 8, this->buttonList[i].ypos + this->buttonList[i].height - 8, this->buttonList[i].label );
  
  }
    return 1; 


}


int ButtonGroupMaker::displayButtonControls(int index, bool pressed) {
  Brain.Screen.clearScreen();
  makeBackground();
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
  tabButtons.displayButtonControls(0, false , true);
  confirmButton.displayButtonControls(0,false ,true);


  // NEW STUFF
  for(int i=0;i<this->buttonList.size();i++) {

    if( this->buttonList[i].state )
      c = this->buttonList[i].onColor;
    else
      c = this->buttonList[i].offColor;

    Brain.Screen.setFillColor( c );

      // button fill
    if( i == index && pressed == true ) 
      Brain.Screen.drawRectangle( this->buttonList[i].xpos, this->buttonList[i].ypos, this->buttonList[i].width, this->buttonList[i].height,c);
    else
      Brain.Screen.drawRectangle( this->buttonList[i].xpos, this->buttonList[i].ypos, this->buttonList[i].width, this->buttonList[i].height );

      // outline
    Brain.Screen.drawRectangle( this->buttonList[i].xpos, this->buttonList[i].ypos, this->buttonList[i].width, this->buttonList[i].height, vex::color::transparent );

    if(  this->buttonList[i].label != NULL )
      Brain.Screen.printAt( this->buttonList[i].xpos + 8, this->buttonList[i].ypos + this->buttonList[i].height - 8, this->buttonList[i].label );
  
  }
    return 1; 
}




void displaySettingsValues() {
  Brain.Screen.setCursor(7,7);
  Brain.Screen.print(settingButtons.buttonList[0].label);
  Brain.Screen.setCursor(7,14);
  Brain.Screen.print(doubleSettings[countSettingsPress % settingsLen]);
  double speed = doubleSettings[0];
  double angle = doubleSettings[1];
  Brain.Screen.setCursor(9,23);
  Brain.Screen.print("Speed: ");
  Brain.Screen.setCursor(9,30);
  Brain.Screen.print(speed);
  Brain.Screen.setCursor(11,23);
  Brain.Screen.print("Angle: ");
  Brain.Screen.setCursor(11,30);
  Brain.Screen.print(angle);

}

void displayPIDSettings() {
  if(!(pidToggleButtons.buttonList[0].state)) {
    Brain.Screen.printAt(120,85,"kP:%.2f",chassisPidControllers[chassisSelection].kP);
    Brain.Screen.printAt(210,85,"kI:%.2f",chassisPidControllers[chassisSelection].kI);
    Brain.Screen.printAt(290,85,"kD:%.2f",chassisPidControllers[chassisSelection].kD);
  }
  if((pidToggleButtons.buttonList[0].state)) {
    Brain.Screen.printAt(120,85,"kP:%.2f",nonChassisPidControllers[nonChassisSelection].kP);
    Brain.Screen.printAt(210,85,"kI:%.2f",nonChassisPidControllers[nonChassisSelection].kI);
    Brain.Screen.printAt(390,85,"kD:%.2f",nonChassisPidControllers[nonChassisSelection].kD);
  }
}

int
displayPIDControls(int index,bool pressed) {
  
  pidToggleButtons.displayButtonControls(0,false);

  if(!(pidToggleButtons.buttonList[0].state)) { //displayPidChassisTab
    pidChassisTabButtons.displayButtonControls(0,false,false);
  }


  
  else { //displayPidNonChassis
    pidNonChassisTabButtons.displayButtonControls(0,false,false);

  }
  return 1;
}



/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/

void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
    if (confirmPress == 0) {
    tabButtons.displayButtonControls(0, false,true);
    confirmButton.displayButtonControls(0,false,true);
    Brain.Screen.drawImageFromFile("logo_test.png",160,50);
    if(tabButtons.buttonList[0].state)
     autonButtons.displayButtonControls(0,false);
    else if(tabButtons.buttonList[1].state) {
      settingButtons.displayButtonControls(0,false);
      displaySettingsValues();
      }
    else if(tabButtons.buttonList[2].state) {
      displayPIDControls(0,false);
      displayPIDSettings();
      }
    }
}

    

  



void makeLoadingScreen() {
  if(confirmButton.buttonList[0].state) {
  double time = Brain.Timer.time(timeUnits::sec);
  double currentTime =0;
  bool firstDone = false;
  bool secondDone = false;
  bool thirdDone = false;
    currentTime = Brain.Timer.time(timeUnits::sec) - time;
  while(currentTime <2) {
     Brain.Screen.printAt(100,100, "Generating Paths...");
     
    currentTime = Brain.Timer.time(timeUnits::sec) - time;
    //Brain.Screen.render();
    if(currentTime>1.96) {
      firstDone = true;
      break;
    }
  }
  Brain.Screen.printAt(330,100, "DONE");
  task::sleep(600);
  inert.calibrate();
  while(inert.isCalibrating()) {
     Brain.Screen.printAt(100,150, "Calibrating Sensors...");
    //Brain.Screen.render();
  }
  secondDone = true;
  if(secondDone)
    Brain.Screen.printAt(330,150, "DONE");
  task::sleep(600);
  double time2 = Brain.timer(timeUnits::sec);
  double currentTime2 =0;
  while(currentTime2 < 2) {
     Brain.Screen.printAt(100,200, "Configuring Robot...");
     
    currentTime2 = Brain.Timer.time(timeUnits::sec) - time2;
    //Brain.Screen.render();
    if(currentTime2>1.95) {
      thirdDone = true;
      break;
      
    }
  }
  if(thirdDone)
    Brain.Screen.printAt(330,200, "DONE");
  //Brain.Screen.printAt(100,150, "Calibrating Sensors...");
 // Brain.Screen.printAt(100,200, "Configuring Robot...");
 Brain.Screen.printAt(50,50,"hi");
  }
}

int makeDisplay() {
  displayButtonControls(0, false);
  
  /*while(1) {
    std::cout <<autonButtons[0].state << std::endl;
    this_thread::sleep_for(10);
  }*/
  return(-1);
}

