# 3142A-2020-2021


Hello! We are team 3142A from Atlanta, Georgia and this is our code for the VEX Robotics Competition 2020-2021 game: Change Up.

This is our sumbission for the Annotated Programming Skills Challenge

1. [ File System. ](#fileSys)


<a name="fileSys"></a>
## 1. Description

sometext

<a name="usage"></a>
## 2. Usage tips

## File System ##

###  Base files ###

 - `include/Impl/auto_skills.h` + `src/Impl/auto_skills.cpp` Initializes chassis and code for skills run
 - `include/Impl/robot-config.h` + `src/Impl_src/robot-config.cpp` stores all of the non chassis systens and the bulk of the sensors
 - `include/Impl/usercontrol.h` + `src/Impl_src/usercontrol.cpp` driver controls and functions (in development)
 - `include/Impl/api.h` tree for files used in robot implementation
 - `src/Impl_src/main.cpp` runs int main() function


### Utilities ###

 - `include/Util/vex.h` includes stdlib libraries and vex sdk 
 - `include/Util/literals.h` + `src/Util_src/literals.cpp` literal implementation
 - `include/Util/mathAndConstants.h` + `src/Util_src/mathAndConstants.cpp` math helper functions

### Chassis Systems ###

 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisSystems_src/ChassisGlobals.cpp` contains custom wrapper library for drive and tracking systems
 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisStystems_src/chassisfunctions.cpp` contains drive functions
 - `include/ChassisSystems/posPID.h` + `src/ChassisSystems_src/posPID.cpp` functions for position PID
 - `include/ChassisSystems/motionprofile.h` + `src/ChassisSystems_src/motionprofile.cpp` Library for motion profile and feedforward commands
 - `include/ChassisSystems/odometry.h` + `src/ChassisSystems_src/odometry.cpp` Robot odometry implementation
 
### Non-Chassis Systems ###

 - `include/NonChassisSystems/flywheel.h` + `src/NonChassisSystems_src/flywheel.cpp` flywheel helper functions/tasks
 - `include/NonChassisSystems/indexer.h` + `src/NonChassisSystems_src/indexer.cpp` indexer helper functions/tasks
 - `include/NonChassisSystems/intakes.h` + `src/NonChassisSystems_src/intakes.cpp` intakes helper functions/tasks
 - `include/NonChassisSystems/macros.h` + `src/NonChassisSystems_src/macros.cpp` macros helper functions/tasks for usercontrol (in development)
 
### Brain Screen Selector ###

 - `include/Selector/selectorAPI.h` + `include/Selector_src/selectorAPI.cpp` wrapper library for selector buttons
 - `include/Selector/selectorImpl.h` + `include/Selector_src/selectorImpl.cpp` Implmentation of selector library 
 
