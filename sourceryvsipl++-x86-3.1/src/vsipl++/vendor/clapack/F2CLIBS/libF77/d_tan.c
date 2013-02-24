#include "f2c.h"

#ifdef KR_headers
double tan();
double d_tan(x) doublereal *x;
#else
#undef abs
#include "math.h"
#undef complex
double d_tan(doublereal *x)
#endif
{
return( tan(*x) );
}
