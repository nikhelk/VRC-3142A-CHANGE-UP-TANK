#include "Selector\selectorAPI.h"
#include "Selector\selectorImpl.h"

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


