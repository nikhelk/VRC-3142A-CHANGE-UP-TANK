#pragma once

#include "vex.h"

/**
 * Determnies whether a number is negative or positive
 * @param number to be determined
 * @return -1 if negative, 1 if positive, 0 if 0
 */

int sgn(double num);

/**
 * Determnies cosine of value in degrees
 * @param value (degrees)
 * @return cosine of value 
 */

double cosDegrees(double value);

/**
 * Determnies sine of value in degrees
 * @param value (degrees)
 * @return sine of value 
 */

double sinDegrees(double value);

/**
 * Converts to degrees from radians
 * @param value (radians)
 * @return value (degrees)
 */

double toDegrees(double angle);

/**
 * Converts to radians from degrees
 * @param value (degrees)
 * @return value (radians)
 */

double toRadians(double angle);


