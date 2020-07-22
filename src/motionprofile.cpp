#include "vex.h"
mp trapezoid;
void generateTrapMP(const double maxVel, const double maxAcc,const double distance) {
  trapezoid.maxVel = maxVel;
  trapezoid.maxAcc = maxAcc;
  trapezoid.distance = distance;
  trapezoid.accelTime = trapezoid.maxVel/trapezoid.maxAcc;
  
  trapezoid.decelTime = trapezoid.maxVel/trapezoid.maxAcc;
  trapezoid.distanceAccel =.5*trapezoid.accelTime*trapezoid.maxVel;
  trapezoid.distanceCoast = (trapezoid.distance-(2*trapezoid.distanceAccel));
  trapezoid.coastTime =trapezoid.distanceCoast/maxVel;
  if (trapezoid.distanceCoast < 0) {
    trapezoid.accelTime = sqrt(trapezoid.distance / trapezoid.maxAcc);
    trapezoid.distanceCoast = 0;
  }
  trapezoid.distanceDecel = .5*trapezoid.decelTime*maxVel;
  trapezoid.totalTime = trapezoid.accelTime + trapezoid.coastTime + trapezoid.decelTime;
  trapezoid.test = 10;
} 
double accelVelocity;
double calculateMpVelocity(const double t) {
  if(t<trapezoid.accelTime) {
    //accelVelocity =(t*trapezoid.distanceAccel)/trapezoid.accelTime;
    accelVelocity =(t*(trapezoid.maxAcc));
    return(accelVelocity);}
  else if(t>trapezoid.accelTime && t<(trapezoid.accelTime+trapezoid.coastTime))
    return(trapezoid.maxVel);
  else if(t>trapezoid.accelTime+trapezoid.coastTime && t<trapezoid.totalTime){
    //return(((trapezoid.totalTime-t)*trapezoid.distanceDecel)/trapezoid.decelTime);
    return(((trapezoid.totalTime-t)*(trapezoid.maxAcc)));
  }
  return 0;
}

std::string getMpStatus(const double t) {
  if(t<trapezoid.accelTime)
    return("accelerating");
  else if(t>trapezoid.accelTime && t<trapezoid.accelTime+trapezoid.coastTime)
    return("coasting");
  else if(t>trapezoid.accelTime+trapezoid.coastTime && t<trapezoid.totalTime)
    return("decelerating");
  return("done");
}