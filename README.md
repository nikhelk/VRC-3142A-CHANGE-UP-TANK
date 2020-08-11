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
 - `include/ChassisSystems/posPID.h` + `src/ChassisSystems_src/posPID.cpp` functions for position PID
 - `include/ChassisSystems/motionprofile.h` + `src/ChassisSystems_src/motionprofile.cpp` Library for motion profile and feedforward commands
 - `include/ChassisSystems/odometry.h` + `src/ChassisSystems_src/odometry.cpp` Robot odometry implementation
 
 ### Non-Chassis Systems ###

 - `include/NonChassisSystems/flywheel.h` + `src/NonChassisSystems/flywheel.cpp` flywheel helper functions/tasks
 - `include/NonChassisSystems/indexer.h` + `src/NonChassisSystems/indexer.cpp` indexer helper functions/tasks
 - `include/NonChassisSystems/intakes.h` + `src/NonChassisSystems/intakes.cpp` intakes helper functions/tasks
 
