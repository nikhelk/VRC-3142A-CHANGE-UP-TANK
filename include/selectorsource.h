#pragma once
#include "vex.h"
void userTouchCallbackPressed();
void userTouchCallbackReleased();
void makeBackground();
void displayButtonControls( int index, bool pressed );
int makeDisplay();
bool getAllianceColor();
extern int test;


typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
} button;
void Log(const char *message );
typedef struct _pidValues {
    double    kP;
    double    kI;
    double    kD;
    const char *label;
} pidValues;

int displayTabButtonControls(int index, bool pressed);
extern bool enableGraph;
extern bool allianceBlue;
extern bool simpleRun;
int makeGraph();