#include "vex.h"
int   tabSelection = -1;
int chassisSelection = -1;
int nonChassisSelection = -1;
bool enableGraph = false;
void makeLoadingScreen();
void Log(const char *message ) {
  std::cout << message << std::endl;
}
// Button array definitions for each software button. The purpose of each button data structure
// is defined above.  The array size can be extended, so you can have as many buttons as you 
// wish as long as it fits.
button tabButtons[] = {
    {  0,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "Auton" },
    {  80,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "Set." },
    {  160,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "PID" },
    {  240,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "Graph" },
    {  320,  0, 70, 30,  false, 0x303030, 0xD0D0D0, "Driver" },
};
button autonButtons[] = {
    {   30,  40, 60, 60,  false, 0xE00000, 0x0000E0, "Ally" },
    {  120,  40, 60, 60,  false, 0x303030, 0xD0D0D0, "Start" },
    {  210,  40, 60, 60,  false, 0x303030, 0xD0D0D0, "Simple" },
};
button settingButtons[] = {
    {  390,  200, 85, 30,  false, 0x303030, 0x303030, "speed" },
    {   30, 150, 60, 30,false, 0x303030, 0x303030,"up" },
    {  150, 150, 60, 30,false, 0x303030, 0x303030, "down" },
};
button pidToggleButtons[] {
  {   300, 150, 60, 40,false, 0x303030, 0x303030,"Chassis" },
  {   120, 40, 60, 30,false, 0x303030, 0x303030,"up" },
  {  120, 90, 60, 30,false, 0x303030, 0x303030, "down" },
  {   200, 40, 60, 30,false, 0x303030, 0x303030,"up" },
  {  200, 90, 60, 30,false, 0x303030, 0x303030, "down" },
  {   280, 40, 60, 30,false, 0x303030, 0x303030,"up" },
  {  280, 90, 60, 30,false, 0x303030, 0x303030, "down" },
};
button pidChassisTabButtons[] {
  
  {   30,  90, 60, 30,  false, 0x303030, 0xD0D0D0, "Dist." },
  {  30,  140, 60, 30,  false, 0x303030, 0xD0D0D0, "Angle" },
  {  30,  190, 60, 30,  false, 0x303030, 0xD0D0D0, "Turn" },
};

button pidNonChassisTabButtons[] {
  
  {   30,  90, 60, 30,  false, 0x303030, 0xD0D0D0, "leftFly" },
  {  30,  140, 60, 30,  false, 0x303030, 0xD0D0D0, "rightFly" },
  {  30,  190, 60, 30,  false, 0x303030, 0xD0D0D0, "leftIntake" },
  {  240,  210, 60, 30,  false, 0x303030, 0xD0D0D0, "rightIntake" },
};
pidValues chassisPidControllers[] = {
  {1,2,3,"distance"}, //lateral 
  {4,5,6,"angle"},
  {7,8,9,"turn"} //turn
};

pidValues nonChassisPidControllers[] = {
  {1,2,3,"leftFly"}, //leftFly 
  {4,5,6,"rightFly"}, //leftIntake
  {34,324,23,"leftIntake"}, //rightFly
  {12,123,321,"rightIntake"}, //righttIntake
};

button confirmButtons[] {
  { 390, 120, 50, 50, false, 0x303030, 0x303030, "confirm"}
};


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
int
findTabButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(tabButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &tabButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

int
findAutonButton( int16_t xpos, int16_t ypos) {
  int nButtons = sizeof(autonButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &autonButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);

}


int
findSettingsButton(int16_t xpos, int16_t ypos) {
  int nButtons = sizeof(settingButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &settingButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}
int
findPidToggleButton(int16_t xpos, int16_t ypos) {
  int nButtons = sizeof(pidToggleButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &pidToggleButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

int
findPidChassisTabButton(int16_t xpos, int16_t ypos) {
  int nButtons = sizeof(pidChassisTabButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &pidChassisTabButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

int 
findPidNonChassisTabButton(int16_t xpos, int16_t ypos) {
  int nButtons = sizeof(pidNonChassisTabButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &pidNonChassisTabButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

int 
findConfirmButton(int16_t xpos, int16_t ypos) {
  int nButtons = sizeof(confirmButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &confirmButtons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/




void
initButtons() {
    int nButtons = sizeof(tabButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      tabButtons[index].state = false;
    }
}

void
initPidChassisTabButtons() {
  int nButtons = sizeof(pidChassisTabButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      pidChassisTabButtons[index].state = false;
    }
}
void
initPidNonChassisTabButtons() {
  int nButtons = sizeof(pidNonChassisTabButtons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      pidNonChassisTabButtons[index].state = false;
    }
}
void initConfirmButtons() {
  confirmButtons[0].state = false;
}

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
  int valueIndex = findPidToggleButton( xpos, ypos );
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
  int valueIndex = findPidToggleButton( xpos, ypos );
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
  if( (index = findTabButton( xpos, ypos )) >= 0 ) {
    displayButtonControls( index, true );
    }
  if(tabButtons[0].state) {
    if( (index = findAutonButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
      }
    }
  if(tabButtons[1].state) { 
    if( (index = findSettingsButton( xpos, ypos )) >= 0 ) {
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
  if(tabButtons[2].state) {
    if( (index = findPidToggleButton( xpos, ypos )) >= 0 ) {
      if (index ==0) {
        countPidSettingsPress ++;
        
        displayButtonControls( index, true );
        }
      else if( index > 0) {
        togglePidPressed = true;
        }
      }
    if(!(pidToggleButtons[0].state)) {
      if( (index = findPidChassisTabButton( xpos, ypos )) >= 0 ) {
        displayButtonControls( index, true );
        }
      while(togglePidPressed) {
       for(int i = 0; i < sizeof(pidChassisTabButtons)/sizeof(pidChassisTabButtons[0]);i++) {
          if(pidChassisTabButtons[i].state) {
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
      if( (index = findPidNonChassisTabButton( xpos, ypos )) >= 0 ) {
        displayButtonControls( index, true );
        }
      while(togglePidPressed){
        for(int i = 0; i < sizeof(pidNonChassisTabButtons)/sizeof(pidNonChassisTabButtons[0]);i++) {
          if(pidNonChassisTabButtons[i].state) {
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
    if( (index = findTabButton( xpos, ypos )) >= 0 && confirmPress == 0) {
      // clear all buttons to false, ie. unselected
      initButtons(); 

      // now set this one as true
      if( tabButtons[index].state == true) {
      if (index ==3) {
        enableGraph = false;}
      tabButtons[index].state = false; }
      else    {
      if (index ==3) {
        enableGraph = true;}
      tabButtons[index].state = true;
      }
      tabSelection = index;

      displayButtonControls( index, false );

      // save as auton selection
 
    }
    if(confirmPress == 0 ) {
    if((index = findConfirmButton( xpos,  ypos))==0) {
      initButtons();
      if( confirmButtons[index].state == true) {
        confirmButtons[index].state = false;}
        
        else    {
        confirmButtons[index].state = true;
        }
      confirmPress += 1;
      allianceBlue = autonButtons[0].state;
      simpleRun = autonButtons[2].state;
      Brain.Screen.clearScreen();
      makeLoadingScreen();
    }
    if(tabButtons[0].state) {
      if( (index = findAutonButton( xpos, ypos )) >= 0 ) {
        if( autonButtons[index].state == true) {
        autonButtons[index].state = false; 
        std::cout << autonButtons[index].state <<std::endl;}
        
        else    {
        autonButtons[index].state = true;
        }

        displayButtonControls( index, false );
      }
    }
    if(tabButtons[1].state) {
      if( (index = findSettingsButton( xpos, ypos )) >= 0 ) {
        if(index ==0)
          settingButtons[index].label = settings[currentSettingsPos].c_str();
        if( settingButtons[index].state == true) {
        settingButtons[index].state = false; }
        else    {
        settingButtons[index].state = true;
        }
        togglePressed = false;
        displayButtonControls( index, false );
      }
    }
    if(tabButtons[2].state) {
      if( (index = findPidToggleButton( xpos, ypos )) >= 0 ) {
        if(index == 0)
          pidToggleButtons[index].label = pidToggle[currentPidSettingsPos].c_str();
        if( pidToggleButtons[index].state == true) {
          pidToggleButtons[index].state = false; }
          else    {
          pidToggleButtons[index].state = true;
          }
          displayButtonControls( index, true );
          togglePidPressed = false;
        }
      

      if(!(pidToggleButtons[0].state)) {
        if( (index = findPidChassisTabButton( xpos, ypos )) >= 0 ) {
          initPidChassisTabButtons();

          if( pidChassisTabButtons[index].state == true) {
          pidChassisTabButtons[index].state = false; }
          else    {
          pidChassisTabButtons[index].state = true;
          }
          chassisSelection = index;
          displayButtonControls( index, true );
          }
        }
      else {
        if( (index = findPidNonChassisTabButton( xpos, ypos )) >= 0 ) {
          initPidNonChassisTabButtons();
          if( pidNonChassisTabButtons[index].state == true) {
          pidNonChassisTabButtons[index].state = false; }
          else    {
          pidNonChassisTabButtons[index].state = true;
          }
          nonChassisSelection = index;
          displayButtonControls( index, true );
          }
        }
    }
    }
}


int displayConfirmButton(int index,bool pressed) {
  vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(confirmButtons)/sizeof(button);i++) {

      if( confirmButtons[i].state )
        c = confirmButtons[i].onColor;
      else
        c = confirmButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) 
        Brain.Screen.drawRectangle( confirmButtons[i].xpos, confirmButtons[i].ypos, confirmButtons[i].width, confirmButtons[i].height,c);
      else
        Brain.Screen.drawRectangle( confirmButtons[i].xpos, confirmButtons[i].ypos, confirmButtons[i].width, confirmButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( confirmButtons[i].xpos, confirmButtons[i].ypos, confirmButtons[i].width, confirmButtons[i].height, vex::color::transparent );

      if(  confirmButtons[i].label != NULL )
        Brain.Screen.printAt( confirmButtons[i].xpos + 8, confirmButtons[i].ypos + confirmButtons[i].height - 8, confirmButtons[i].label );
    }
    return 1;
}
int displayTabButtonControls(int index, bool pressed) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(tabButtons)/sizeof(button);i++) {

      if( tabButtons[i].state )
        c = tabButtons[i].onColor;
      else
        c = tabButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( tabButtons[i].xpos, tabButtons[i].ypos, tabButtons[i].width, tabButtons[i].height,c);
      }
      else
        Brain.Screen.drawRectangle( tabButtons[i].xpos, tabButtons[i].ypos, tabButtons[i].width, tabButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( tabButtons[i].xpos, tabButtons[i].ypos, tabButtons[i].width, tabButtons[i].height, vex::color::transparent );

      if(  tabButtons[i].label != NULL )
        Brain.Screen.printAt( tabButtons[i].xpos + 8, tabButtons[i].ypos + tabButtons[i].height - 8, tabButtons[i].label );
    }
    return 1;
}


int 
displayAutonControls(int index, bool pressed) {
  
  Brain.Screen.clearScreen();
  makeBackground();
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
  displayTabButtonControls(0, false);
  displayConfirmButton(0,false);


  // NEW STUFF
  for(int i=0;i<sizeof(autonButtons)/sizeof(button);i++) {

      if( autonButtons[i].state )
        c = autonButtons[i].onColor;
      else
        c = autonButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( autonButtons[i].xpos, autonButtons[i].ypos, autonButtons[i].width, autonButtons[i].height,c);
      }
      else
        Brain.Screen.drawRectangle( autonButtons[i].xpos, autonButtons[i].ypos, autonButtons[i].width, autonButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( autonButtons[i].xpos, autonButtons[i].ypos, autonButtons[i].width, autonButtons[i].height, vex::color::transparent );


      if(  tabButtons[i].label != NULL )
        Brain.Screen.printAt( autonButtons[i].xpos + 8, autonButtons[i].ypos + autonButtons[i].height - 8, autonButtons[i].label );
    }
  return 1;
}


int 
displaySettingControls(int index, bool pressed) {
  Brain.Screen.clearScreen();
  makeBackground();
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
  displayTabButtonControls(0, false);
  displayConfirmButton(0,false);
  
  
  // NEW STUFF
  for(int i=0;i<sizeof(settingButtons)/sizeof(button);i++) {

      if( settingButtons[i].state )
        c = settingButtons[i].onColor;
      else
        c = settingButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( settingButtons[i].xpos, settingButtons[i].ypos, settingButtons[i].width, settingButtons[i].height,c);
      }
      else
        Brain.Screen.drawRectangle( settingButtons[i].xpos, settingButtons[i].ypos, settingButtons[i].width, settingButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( settingButtons[i].xpos, settingButtons[i].ypos, settingButtons[i].width, settingButtons[i].height, vex::color::transparent );

      if(  settingButtons[i].label != NULL ) {
        if(i == 0) {
          Brain.Screen.printAt( settingButtons[i].xpos + 8, settingButtons[i].ypos + settingButtons[i].height - 8, settingButtons[0].label );
        }
        else {
          Brain.Screen.printAt( settingButtons[i].xpos + 8, settingButtons[i].ypos + settingButtons[i].height - 8, settingButtons[i].label );
        }
      }
  }



        Brain.Screen.setCursor(7,7);
        Brain.Screen.print(settingButtons[0].label);
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
  return 1;
}


int
displayPIDControls(int index,bool pressed) {
  
  Brain.Screen.clearScreen();
  makeBackground();
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
  displayTabButtonControls(0, false);
  displayConfirmButton(0,false);
  if(!(pidToggleButtons[0].state)) {
  Brain.Screen.printAt(120,85,"kP:%.2f",chassisPidControllers[chassisSelection].kP);
  Brain.Screen.printAt(210,85,"kI:%.2f",chassisPidControllers[chassisSelection].kI);
  Brain.Screen.printAt(290,85,"kD:%.2f",chassisPidControllers[chassisSelection].kD);
  }
  if((pidToggleButtons[0].state)) {
  Brain.Screen.printAt(120,85,"kP:%.2f",nonChassisPidControllers[nonChassisSelection].kP);
  Brain.Screen.printAt(210,85,"kI:%.2f",nonChassisPidControllers[nonChassisSelection].kI);
  Brain.Screen.printAt(390,85,"kD:%.2f",nonChassisPidControllers[nonChassisSelection].kD);
  }

  // NEW STUFF

  for(int i=0;i<sizeof(pidToggleButtons)/sizeof(button);i++) {

      if( pidToggleButtons[i].state )
        c = pidToggleButtons[i].onColor;
      else
        c = pidToggleButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( pidToggleButtons[i].xpos, pidToggleButtons[i].ypos, pidToggleButtons[i].width, pidToggleButtons[i].height,c);
      }
      else
        Brain.Screen.drawRectangle( pidToggleButtons[i].xpos, pidToggleButtons[i].ypos, pidToggleButtons[i].width, pidToggleButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( pidToggleButtons[i].xpos, pidToggleButtons[i].ypos, pidToggleButtons[i].width, pidToggleButtons[i].height, vex::color::transparent );

      if(  pidToggleButtons[i].label != NULL ) {
        if(i == 0) {
          Brain.Screen.printAt( pidToggleButtons[i].xpos + 8, pidToggleButtons[i].ypos + pidToggleButtons[i].height - 8, pidToggleButtons[0].label );
        }
        else {
          Brain.Screen.printAt( pidToggleButtons[i].xpos + 8, pidToggleButtons[i].ypos + pidToggleButtons[i].height - 8, pidToggleButtons[i].label );
        }
      }
  }

  if(!(pidToggleButtons[0].state)) {
    for(int i=0;i<sizeof(pidChassisTabButtons)/sizeof(button);i++) {

      if( pidChassisTabButtons[i].state )
        c = pidChassisTabButtons[i].onColor;
      else
        c = pidChassisTabButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( pidChassisTabButtons[i].xpos, pidChassisTabButtons[i].ypos, pidChassisTabButtons[i].width, pidChassisTabButtons[i].height,c);
      }
      else
        Brain.Screen.drawRectangle( pidChassisTabButtons[i].xpos, pidChassisTabButtons[i].ypos, pidChassisTabButtons[i].width, pidChassisTabButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( pidChassisTabButtons[i].xpos, pidChassisTabButtons[i].ypos, pidChassisTabButtons[i].width, pidChassisTabButtons[i].height, vex::color::transparent );

      if(  pidChassisTabButtons[i].label != NULL ) {
        if(i == 0) {
          Brain.Screen.printAt( pidChassisTabButtons[i].xpos + 8, pidChassisTabButtons[i].ypos + pidChassisTabButtons[i].height - 8, pidChassisTabButtons[0].label );
        }
        else {
          Brain.Screen.printAt( pidChassisTabButtons[i].xpos + 8, pidChassisTabButtons[i].ypos + pidChassisTabButtons[i].height - 8, pidChassisTabButtons[i].label );
        }
      }
  }


  }
  else {
    for(int i=0;i<sizeof(pidNonChassisTabButtons)/sizeof(button);i++) {

      if( pidNonChassisTabButtons[i].state )
        c = pidNonChassisTabButtons[i].onColor;
      else
        c = pidNonChassisTabButtons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( pidNonChassisTabButtons[i].xpos, pidNonChassisTabButtons[i].ypos, pidChassisTabButtons[i].width, pidNonChassisTabButtons[i].height,c);
      }
      else
        Brain.Screen.drawRectangle( pidNonChassisTabButtons[i].xpos, pidNonChassisTabButtons[i].ypos, pidNonChassisTabButtons[i].width, pidNonChassisTabButtons[i].height );

      // outline
      Brain.Screen.drawRectangle( pidNonChassisTabButtons[i].xpos, pidNonChassisTabButtons[i].ypos, pidNonChassisTabButtons[i].width, pidNonChassisTabButtons[i].height, vex::color::transparent );

      if(  pidChassisTabButtons[i].label != NULL ) {
        if(i == 0) {
          Brain.Screen.printAt( pidNonChassisTabButtons[i].xpos + 8, pidNonChassisTabButtons[i].ypos + pidNonChassisTabButtons[i].height - 8, pidNonChassisTabButtons[0].label );
        }
        else {
          Brain.Screen.printAt( pidNonChassisTabButtons[i].xpos + 8, pidNonChassisTabButtons[i].ypos + pidNonChassisTabButtons[i].height - 8, pidNonChassisTabButtons[i].label );
        }
      }
  }

  }
  return 1;
}


task t3;
task t4;
task t2;
thread ren;
int displayTabs() {
  while(true) {
  displayTabButtonControls(0, false);
  Brain.Screen.render();
  }
}
int makeGraph() {
  graph g( 4, 0, 230 );
  
    // set line colors
    
    g.setColor(2, vex::color::green );
    g.setColor(1, vex::color::white );
    
    g.setColor(0, vex::color::red );
    g.setColor(3, vex::color::white );
    
      task t3( goalTask, static_cast<void *>(&g) );
      task t4( currentTask, static_cast<void *>(&g) );
      task t2( successTask, static_cast<void *>(&g) );
    // and we are using separate tasks to add points to each line, this is a bit overkill
    //thread t1( sinTask1, static_cast<void *>(&g) );
    //th                             
  return 1;
}
task t1;
int
displayGraphControls(int index, bool pressed) {
  Brain.Screen.clearScreen();
  makeBackground();
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );
  
  task t1(makeGraph);
    
    
    
    
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
    displayTabButtonControls(0, false);
    displayConfirmButton(0,false);
    Brain.Screen.drawImageFromFile("logo_test.png",160,50);
    if(tabButtons[0].state)
     displayAutonControls(0,false);
    else if(tabButtons[1].state) {
      t1.stop();
      Brain.Screen.clearScreen();
      displaySettingControls(0,false);
      }
    else if(tabButtons[2].state)
      displayPIDControls(0,false);
    else if(tabButtons[3].state)
      displayGraphControls(0,false);
    }

  
}


void makeLoadingScreen() {
  if(confirmButtons[0].state) {
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




bool getAllianceColor() {
  return(autonButtons[0].state);
}