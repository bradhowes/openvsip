#include "f2c.h"

#ifdef KR_headers
double atan();
double d_atan(x) doublereal *x;
#else
#undef abs
#include "math.h"
#undef complex
double d_atan(doublereal *x)
#endif
{
return( atan(*x) );
}
