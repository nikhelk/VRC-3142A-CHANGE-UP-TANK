#include "vex.h"

long double operator "" _in(long double x) {
  return(x*0.0254);
}

long double operator "" _rad(long double x) {
  return(x);
}
long double operator "" _deg(long double x) {
  return(x*(M_PI/180));
}
long double operator "" _inps(long double x) {
  return(x);
}long double operator "" _inps2(long double x) {
  return(x);
}
