#include "Util/vex.h"
/// inches operator (coverted to meters)
long double operator"" _in(long double x);

/// meters operator
long double operator"" _m(long double x);

/// radians operator
long double operator"" _rad(long double x);

/// degree operator (converted to radians)
long double operator"" _deg(long double x);

/// meters per second operator 
long double operator"" _mps(long double x);

/// meters per second^2 operator
long double operator"" _mps2(long double x);
