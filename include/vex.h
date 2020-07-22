/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "v5.h"
#include "v5_vcs.h"
#include <iostream>
#include "robot-config.h"
#include <vector>
#include <stdint.h>
#include <string.h>
#include "pid.h"
#include "graph.h"
#include "globals.h"
#include "literals.h"
#include "mathAndConstants.h"
#include "chassisfunctions.h"
#include "selectorsource.h"
#include "motionprofile.h"
#include "macros.h"
#include "usercontrol.h"
#define GEAR_RATIO 1.666666667
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)