#include "Selector\selectorAPI.h"
#include "Selector\selectorImpl.h"

/* ***************************************************************************************************** */

// We would like to thank jpearman and walshbots for providing us a template for the autonomous selector

// <https://www.vexforum.com/t/walshbots-autonomous-feature-selector/51534>

// <https://www.vexforum.com/t/can-anyone-explain-jpearmans-code-buttons-one/51060/5>

/* ****************************************************************************************************** */

ButtonGroupMaker::ButtonGroupMaker(std::initializer_list<button> butonList) {

  this->buttonList.reserve(butonList.size()); // we need to convert initializer list to vector so we can index

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
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) ) // if we are not in the xbounds, skip
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) ) //if we are not in the ybounds, skip
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

void ButtonGroupMaker::switchStates(int index) {
  if( this->buttonList[index].state) {
    this->buttonList[index].state = false; }
  else    
    this->buttonList[index].state = true;
    
}

int ButtonGroupMaker::displayButtonControls(int index, bool pressed, bool permanant) {
  vex::color c;
  Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

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


