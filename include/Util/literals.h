#include "Util/vex.h"

/// inches operator (coverted to meters)
long double operator"" _in(long double x) {return(x*0.0254);}

/// meters operator
long double operator"" _m(long double x) {return(x);};

/// radians operator
long double operator"" _rad(long double x) {return(x);};

/// degree operator (converted to radians)
long double operator"" _deg(long double x) {return (x * (M_PI / 180));}

/// meters per second operator 
long double operator"" _mps(long double x) {return(x);};

/// meters per second^2 operator
long double operator"" _mps2(long double x) {return(x);};
