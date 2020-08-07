#pragma once
#include "vex.h"
void userTouchCallbackPressed();
void userTouchCallbackReleased();
void makeBackground();
void displayButtonControls( int index, bool pressed );
int makeDisplay();
bool getAllianceColor();
extern int test;


struct button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
};

struct pidValues {
    double    kP;
    double    kI;
    double    kD;
    const char *label;
};

int displayTabButtonControls(int index, bool pressed);
extern bool enableGraph;
extern bool allianceBlue;
extern bool simpleRun;
int makeGraph();

class ButtonGroupMaker {
    private:
    public:
        std::vector<button> buttonList;
        ButtonGroupMaker(std::initializer_list<button> butonList);

        int findButton(int16_t xpos, int16_t ypos);

        void initButtons();

        int displayButtonControls(int index, bool pressed);

        int displayButtonControls(int index, bool pressed,bool permamant);


    
}; 
extern ButtonGroupMaker hiButtons;