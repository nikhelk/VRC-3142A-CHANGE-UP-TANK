# 3142A-2020-2021


Hello! We are team 3142A from Atlanta, Georgia and this is our code for the VEX Robotics Competition 2020-2021 game: Change up.

This is our code forour sumbission for the Annotated Programming Skills Challenge

## File System ##

###  Base files ###

 - `include/vex.h` includes stdlib libraries and vex sdk 
 - `include/robot-config.h` + `src/robot-config.cpp` stores all of the non chassis systens and the bulk of the sensors
 - `include/usercontrol.h` + `src/usercontrolcpp` driver controls and functions (in development)
 - `src/main.cpp` initializes robot and runs code


### Chassis Systems ###

 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisSystems_src/ChassisGlobals.cpp` contains custom wrapper library for drive and tracking systems
 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisStystems_src/chassisfunctions.cpp` contains drive functions
