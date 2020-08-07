#pragma once
#include <vector>
#include "vex.h"
#include "premacros.h"
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