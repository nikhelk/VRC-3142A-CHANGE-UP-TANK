#include "vex.h"

double positionArray[3];



int sgn(double num) {
  if(num > 0 )
    return 1;
  if(num < 0) 
    return -1;
  return 0;
}



double cosDegrees(double value) {
  return(cos(value*(M_PI/180)));
}



double sinDegrees(double value) {
  return(sin(value*(M_PI/180)));
}



double toDegrees(double angle) {
  return angle*(180/M_PI);
}



double toRadians(double angle) {
  return angle*(M_PI/180);
}
void computeDistanceAndAngleToPoint(const long x, const long y, distanceAndAngle *out)
{
  
	//If no lock, return empty type
	out->length = 0;
	out->theta = 0;


		//Compute difference in distance

		const float xDiff = x - positionArray[ODOM_X], yDiff = y - positionArray[ODOM_Y];
		out->length = sqrt((xDiff * xDiff) + (yDiff * yDiff));
		
		//Compute difference in angle
		out->theta = ((atan2(yDiff, xDiff) * (180 / M_PI))) -  positionArray[ODOM_THETA];
}

void setOdomOrigin(double x, double y, double a) {
  positionArray[ODOM_X] = x;
  positionArray[ODOM_Y] = y;
  positionArray[ODOM_THETA] = a;

}




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
  position.leftLst =0; 
  position.rightLst = 0;
  position.backLst = 0;
  position.x = positionArray[ODOM_X];
  position.y = positionArray[ODOM_Y];
  position.a = positionArray[ODOM_THETA]*(M_PI/180);
  while(true) {
  int left = leftFront.position(degrees);
  int right = rightFront.position(degrees);
  int back = EncoderG.position(degrees);
	double L = (left - position.leftLst) * SPIN_TO_IN_LR; // The amount the left side of the robot moved
	double R = (right - position.rightLst) * SPIN_TO_IN_LR; // The amount the right side of the robot moved
	double S = (back - position.backLst) * SPIN_TO_IN_S; // The amount the back side of the robot moved

	// Update the last values
	position.leftLst = left;
	position.rightLst = right;
	position.backLst = back;
	double h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
	double i; // Half on the angle that I've traveled
	double h2; // The same as h but using the back instead of the side wheels
	double a = (R - L) / (L_DISTANCE_IN + R_DISTANCE_IN); // The angle that I've traveled
	if (a)
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
	position.y += h * sinP;
	position.x += h * cosP;

	position.y += h2 * cosP; // -sin(x) = sin(-x)
	position.x += h2 * -sinP; // cos(x) = cos(-x)

	position.a += a;
  while(position.a > 2*M_PI)
    position.a-=2*M_PI;
  while(position.a < -2*M_PI)
    position.a += 2*M_PI;
  //cout << "hi" <<SPIN_TO_IN_LR <<endl;
  positionArray[ODOM_X] = position.x;
  positionArray[ODOM_Y] = position.y;
  positionArray[ODOM_THETA] = position.a*(180/M_PI);
 // std::cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " <<positionArray[ODOM_THETA] <<" " << a<<std::endl;
  //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " <<positionArray[ODOM_THETA] <<" " << left<< " " <<right<<endl;
  //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] <<endl;;
  //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " << positionArray[ODOM_THETA] << " " << leftFront.position(degrees)<< " " << rightFront.position(degrees)<< " "<<
  //    (leftFront.position(degrees)/rightFront.position(degrees)) <<endl;
  task::sleep(15);
  }
  return 1;
}

void printPosition() {
  std::cout << positionArray[ODOM_X] << " "
  << positionArray[ODOM_Y] <<
  " " << positionArray[ODOM_THETA] <<std::endl;
}
int trackPositionGyro()
{
  sPos position;
  position.leftLst =0; 
  position.rightLst = 0;
  position.backLst = 0;
  position.angleLst =0;
  position.x = positionArray[ODOM_X];
  position.y = positionArray[ODOM_Y];
  position.a = toRadians(positionArray[ODOM_THETA]);
  while(true) {
  int left = leftFront.position(degrees);
  int right = rightFront.position(degrees);
  int back = EncoderG.position(degrees);
	double L = (left - position.leftLst) * SPIN_TO_IN_LR; // The amount the left side of the robot moved
	double R = (right - position.rightLst) * SPIN_TO_IN_LR; // The amount the right side of the robot moved
	double S = (back - position.backLst) * SPIN_TO_IN_S; // The amount the back side of the robot moved

	// Update the last values
	position.leftLst = left;
	position.rightLst = right;
	position.backLst = back;
  
	double h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
	double i; // Half on the angle that I've traveled
	double h2; // The same as h but using the back instead of the side wheels
	double a = toRadians(inert.heading(degrees)) -  position.angleLst; // The angle that I've traveled
  //if(a <(toRadians(.0001))) {
  //  a = 0;
  //}
  if (a != 0 && L!=0)
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

	position.y += h2 * cosP; // -sin(x) = sin(-x)
	position.x += h2 * -sinP; // cos(x) = cos(-x)

	position.a += a;
  while(position.a > 2*M_PI)
    position.a-=2*M_PI;
  while(position.a < -2*M_PI)
    position.a += 2*M_PI;
  //cout << "hi" <<SPIN_TO_IN_LR <<endl;
  positionArray[ODOM_X] = position.x;
  positionArray[ODOM_Y] = position.y;
  positionArray[ODOM_THETA] = toDegrees(position.a);
  //std::cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << ", " <<positionArray[ODOM_THETA] <<" ," << h * sinP << ", " <<h2<<std::endl;
  //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] <<endl;;
  //cout << positionArray[ODOM_X] << "," << positionArray[ODOM_Y] << " " << positionArray[ODOM_THETA] << " " << leftFront.position(degrees)<< " " << rightFront.position(degrees)<< " "<<
  //    (leftFront.position(degrees)/rightFront.position(degrees)) <<endl;
  position.angleLst = toRadians(inert.heading(degrees));
  task::sleep(20);
  }
  return 1;
}

int trackPosition2() {

  long lastLeft =0, lastRight =0, leftTicks, rightTicks;

  double leftMM, rightMM, mm;

  int leftSample, rightSample;

  while (true)
  {
    //Save quads
    leftSample = leftFront.position(degrees);
    rightSample = rightFront.position(degrees);

    //Get delta
    leftTicks = leftSample - lastLeft;
    rightTicks = rightSample - lastRight;

    //Save last vals
    lastLeft = leftSample;
    lastRight = rightSample;

    //Convert to mm
    leftMM = (double)leftTicks / encoderToInch;
    rightMM = (double)rightTicks / encoderToInch;

    //Get avg delta
    mm = (leftMM + rightMM) / 2.0;

    //Get theta
    positionArray[ODOM_THETA] += ((rightTicks - leftTicks) / 14)*(180/M_PI);
    //Wrap theta
    if(positionArray[ODOM_THETA] > 180)
      positionArray[ODOM_THETA]  -= 360;
    if(positionArray[ODOM_THETA] < -180)
      positionArray[ODOM_THETA] += 360;

    //Do the odom math
    positionArray[ODOM_X] += mm * cosDegrees(positionArray[ODOM_THETA]);
    positionArray[ODOM_Y] += mm * sinDegrees(positionArray[ODOM_THETA]);
    
    //Save to global

    //Task wait
    task::sleep(10);
  }
  return 1;
}


