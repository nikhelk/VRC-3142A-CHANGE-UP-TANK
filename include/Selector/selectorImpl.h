#pragma once

#include "selectorAPI.h"


extern bool enableGraph;
extern bool allianceBlue;
extern bool simpleRun;

void makeBackground();
void displayAllButtonControls( int index, bool pressed );
int makeDisplay();

void userTouchCallbackPressed();
void userTouchCallbackReleased();

extern ButtonGroupMaker tabButtons;
extern ButtonGroupMaker confirmButton;
extern int confirmPress;