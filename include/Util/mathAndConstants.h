#pragma once

#include "Util/vex.h"

namespace math3142a {
/**
 * Determnies whether a number is negative or positive
 * @param num number to be determined
 * @return -1 if negative, 1 if positive, 0 if 0
 */
template <class T>
int sgn(T num) {   return (num < 0) ? -1 : ((num > 0) ? 1 : 0); };

/**
 * Determnies cosine of value in degrees
 * @param value (degrees)
 * @return cosine of value 
 */

double cosDegrees(double value) {return cos(value) * (180/M_PI); };

/**
 * Determnies sine of value in degrees
 * @param value (degrees)
 * @return sine of value 
 */

double sinDegrees(double value) {return sin(value) * (180/M_PI); };

//coverts input degree value to radians
double toRadians(double value) {return (value) * (180/M_PI); };

//coverts input degree value to radians
double toDegrees(double value) {return (value) * (M_PI/180); };


}