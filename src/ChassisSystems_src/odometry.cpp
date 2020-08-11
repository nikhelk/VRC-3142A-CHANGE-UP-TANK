#include "ChassisSystems/odometry.h"
#include "ChassisSystems/chassisGlobals.h"
#include "Util/mathAndConstants.h"
#include <cmath>


/*
Copyright (c) 2018 5225A E-bot PiLons
Modifications nikhelkrishna
2020-31-7: Modify constants for bot use

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



int trackPosition()
{
  sPos position;
  position.leftLst = 0;
  position.rightLst = 0;
  position.backLst = 0;
  position.x = positionArray[ODOM_X];
  position.y = positionArray[ODOM_Y];
  position.a = positionArray[ODOM_THETA] * (M_PI / 180);
  while (true)
  {
    int left = chassis.leftFront.position(degrees);
    int right = chassis.rightFront.position(degrees);
    int back = poseTracker.backEncoder.position(degrees);
    double deltaL = chassis.convertTicksToMeters((left - position.leftLst)); // The amount the left side of the robot moved
    double deltaR = chassis.convertTicksToMeters((left - position.leftLst)); // The amount the right side of the robot moved
    double deltaB = (back - position.backLst) * SPIN_TO_IN_S;                // The amount the back side of the robot moved

    // Update the last values
    position.leftLst = left;
    position.rightLst = right;
    position.backLst = back;
    double h;                                                       // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
    double i;                                                       // Half on the angle that I've traveled
    double h2;                                                      // The same as h but using the back instead of the side wheels
    double a = (deltaR - deltaL) / (L_DISTANCE_IN + R_DISTANCE_IN); // The angle that I've traveled
    if (a)
    {
      double r = deltaL / a; // The radius of the circle the robot travel's around with the right side of the robot
      i = a / 2.0;
      double sinI = sin(i);
      h = ((r + L_DISTANCE_IN) * sinI) * 2.0;

      double r2 = deltaB / a; // The radius of the circle the robot travel's around with the back of the robot
      h2 = ((r2 + S_DISTANCE_IN) * sinI) * 2.0;
    }
    else
    {
      h = deltaL;
      i = 0;

      h2 = deltaB;
    }
    double p = i + position.a; // The global ending angle of the robot
    double cosP = cos(p);
    double sinP = sin(p);

    // conversion from polar to cartesian
    position.y += h * sinP;
    position.x += h * cosP;

    position.y += h2 * cosP;
    position.x += h2 * -sinP;

    position.a += a;
    while (position.a > 2 * M_PI)
      position.a -= 2 * M_PI;
    while (position.a < -2 * M_PI)
      position.a += 2 * M_PI;
    //cout << "hi" <<SPIN_TO_IN_LR <<endl;
    positionArray[ODOM_X] = position.x;
    positionArray[ODOM_Y] = position.y;
    positionArray[ODOM_THETA] = position.a * (180 / M_PI);
    // std::cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " <<positionArray[ODOM_THETA] <<" " << a<<std::endl;
    //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " <<positionArray[ODOM_THETA] <<" " << left<< " " <<right<<endl;
    //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] <<endl;;
    //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " << positionArray[ODOM_THETA] << " " << leftFront.position(degrees)<< " " << rightFront.position(degrees)<< " "<<
    //    (leftFront.position(degrees)/rightFront.position(degrees)) <<endl;
    task::sleep(15);
  }
  return 1;
}

int trackPositionGyro()
{
  sPos position;
  position.leftLst = 0;
  position.rightLst = 0;
  position.backLst = 0;
  position.angleLst = 0;
  position.x = positionArray[ODOM_X];
  position.y = positionArray[ODOM_Y];
  position.a = toRadians(positionArray[ODOM_THETA]);
  while (true)
  {
    int left = chassis.leftFront.position(degrees);
    int right = chassis.rightFront.position(degrees);
    int back = poseTracker.backEncoder.position(degrees);
    double L = chassis.convertTicksToMeters((left - position.leftLst)); // The amount the left side of the robot moved
    double R = chassis.convertTicksToMeters((left - position.leftLst)); // The amount the right side of the robot moved
    double S = (back - position.backLst) * SPIN_TO_IN_S;                // The amount the back side of the robot moved

    // Update the last values
    position.leftLst = left;
    position.rightLst = right;
    position.backLst = back;

    double h;                                                                   // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
    double i;                                                                   // Half on the angle that I've traveled
    double h2;                                                                  // The same as h but using the back instead of the side wheels
    double a = toRadians(poseTracker.getInertialHeading()) - position.angleLst; // The angle that I've traveled
    //if(a <(toRadians(.0001))) {
    //  a = 0;
    //}
    if (a != 0 && L != 0)
    {
      double r = L / a; // The radius of the circle the robot travel's around with the right side of the robot
      i = a / 2.0;
      double sinI = sin(i);
      h = ((r + L_DISTANCE_IN) * sinI) * 2.0;

      double r2 = S / a; // The radius of the circle the robot travel's around with the back of the robot
      h2 = ((r2 + S_DISTANCE_IN) * sinI) * 2.0;
    }
    else
    {
      h = L;
      i = 0;

      h2 = S;
    }
    double p = i + position.a; // The global ending angle of the robot
    double cosP = cos(p);
    double sinP = sin(p);

    // Update the global position
    /*if((h * sinP >-.0001 && h* sinP <.0001) && 
  (h * cosP >-.0001 && h* cosP <.0001)&&
  (h2 * -sinP >-.0001 && h2* -sinP <.0001)&&
  (h * cosP >-.0001 && h* cosP <.0001)) {
    position.y +=0;
	  position.x += 0;
	  position.y += 0; 
	  position.x += 0;

  }*/
    position.y += h * sinP;
    position.x += h * cosP;

    position.y += h2 * cosP;  // -sin(x) = sin(-x)
    position.x += h2 * -sinP; // cos(x) = cos(-x)

    position.a += a;
    while (position.a > 2 * M_PI)
      position.a -= 2 * M_PI;
    while (position.a < -2 * M_PI)
      position.a += 2 * M_PI;
    //cout << "hi" <<SPIN_TO_IN_LR <<endl;
    positionArray[ODOM_X] = position.x;
    positionArray[ODOM_Y] = position.y;
    positionArray[ODOM_THETA] = toDegrees(position.a);
    //std::cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << ", " <<positionArray[ODOM_THETA] <<" ," << h * sinP << ", " <<h2<<std::endl;
    //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] <<endl;;
    //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " << positionArray[ODOM_THETA] << " " << leftFront.position(degrees)<< " " << rightFront.position(degrees)<< " "<<
    //    (leftFront.position(degrees)/rightFront.position(degrees)) <<endl;
    position.angleLst = toRadians(poseTracker.getInertialHeading());
    task::sleep(20);
  }
  return 1;
}

void setOdomOrigin(double x, double y, double a)
{
  positionArray[ODOM_X] = x;
  positionArray[ODOM_Y] = y;
  positionArray[ODOM_THETA] = a;
}

void printPosition()
{
  std::cout << positionArray[ODOM_X] << " "
            << positionArray[ODOM_Y] << " " << positionArray[ODOM_THETA] << std::endl;
}




/*
Copyright (c) 2016 BCI Module
Modifications nikhelkrishna
2020-31-7: Modify constants for bot use

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


void computeDistanceAndAngleToPoint(const double x, const double y, pointVals *out)
{

  //Compute difference in distance

  const double xDiff = x - positionArray[ODOM_X], yDiff = y - positionArray[ODOM_Y];
  out->length = sqrt((xDiff * xDiff) + (yDiff * yDiff));

  //Compute difference in angle
  out->theta = ((atan2(yDiff, xDiff) * (180 / M_PI))) - positionArray[ODOM_THETA];
}

