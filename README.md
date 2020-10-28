# 3142A-2020-2021


Hello! We are team 3142A from Atlanta, Georgia and this is our code for the VEX Robotics Competition 2020-2021 game: Change Up.

This is our sumbission for the Annotated Programming Skills Challenge

1. [ File System. ](#fileSys)
2. [ Resources. ](#resources)
3. [ Acknowledgements. ](#ack)


<a name="fileSys"></a>
## File System ##

###  Base files ###

 - `include/Impl/auto_skills.h` + `src/Impl/auto_skills.cpp` Initializes code for skills run and runs it
 - `include/Impl/api.h` tree for files used in robot implementation
 - `src/Impl_src/main.cpp` runs int main() function
 
 <br />**Our skills run code is in `src/Impl/auto_skills.cpp`**

### Chassis Systems ###

 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisSystems_src/ChassisGlobals.cpp` contains custom wrapper library for drive and tracking systems
 - `include/ChassisSystems/chassisConstraints.h` + `src/ChassisSystems_src/ChassisGlobals.cpp` contains wrapper for phyicial constraints for our robot
 - `include/ChassisSystems/ChassisGlobals.h` + `src/ChassisStystems_src/chassisfunctions.cpp` contains drive functions
 - `include/ChassisSystems/ChassisBuilder.h` contains chassis builder method 
 - `include/ChassisSystems/posPID.h` + `src/ChassisSystems_src/posPID.cpp` functions for position PID
 - `include/ChassisSystems/motionprofile.h` + `src/ChassisSystems_src/motionprofile.cpp` Library for motion profile and feedforward commands
 - `include/ChassisSystems/odometry.h` + `src/ChassisSystems_src/odometry.cpp` Robot odometry implementation
 
### Non-Chassis Systems ###

 - `include/NonChassisSystems/flywheel.h` + `src/NonChassisSystems_src/flywheel.cpp` flywheel helper functions/tasks
 - `include/NonChassisSystems/indexer.h` + `src/NonChassisSystems_src/indexer.cpp` indexer helper functions/tasks
 - `include/NonChassisSystems/intakes.h` + `src/NonChassisSystems_src/intakes.cpp` intakes helper functions/tasks

### Brain Screen Selector ###

 - `include/Selector/selectorAPI.h` + `include/Selector_src/selectorAPI.cpp` wrapper library for selector buttons
 - `include/Selector/selectorImpl.h` + `include/Selector_src/selectorImpl.cpp` Implmentation of selector library 

### Config ###

- `include/Config/chassis-config.h` + `src/Config_src/chassis-config.cpp`includes our impl of custom chassis builder
- `include/Config/other-config.h` +`src/Config_src/other-config.cpp`

### Utilities ###

 - `include/Util/vex.h` includes stdlib libraries and vex sdk 
 - `include/Util/literals.h` + `src/Util_src/literals.cpp` literal implementation
 - `include/Util/mathAndConstants.h` + `src/Util_src/mathAndConstants.cpp` math helper functions
 - `include/Util/premacros.h` our simple, custom logging method
 
<a name = "resources"></a>
## Resources

Our JavaScript simulation code is in the `MotionProfileSimJS` directory

We also created Educational Resources for other VEX teams to use: 

<https://paideiarobotics.wordpress.com/articles/>
<a name = "ack"></a>
## Acknowledgements
We would like to thank the following people for giving new insights on the amazing world of robotics:<br /><br />
    Our mentor, Dave<br />
    jpearman and other VEX Forumers<br />
    the Unofficial VEX discord, especially the folks from 5225A, Lachlan, hotel, Tabor, Theo <br />
    the FRC Discord Server and WPI lib<br />
    
