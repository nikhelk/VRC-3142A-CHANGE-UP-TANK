#include "Util/vex.h"

double positionArray[3];

int sgn(double num)
{
  if (num > 0)
    return 1;
  if (num < 0)
    return -1;
  return 0;
}

double cosDegrees(double value)
{
  return (cos(value * (M_PI / 180)));
}

double sinDegrees(double value)
{
  return (sin(value * (M_PI / 180)));
}

double toDegrees(double angle)
{
  return angle * (180 / M_PI);
}

double toRadians(double angle)
{
  return angle * (M_PI / 180);
}

