#include <cmath>

long double operator"" _in(long double x)
{
  //convert to meters
  return (x * 0.0254);
}

long double operator"" _rad(long double x)
{
  return (x);
}
long double operator"" _deg(long double x)
{
  //convert to radians
  return (x * (M_PI / 180));
}
long double operator"" _mps(long double x)
{
  return (x);
}
long double operator"" _mps2(long double x)
{
  return (x);

}
