#include "dw4/ieee_words.h"
#include "dw4/newlib_math.h"


double tan(double x)
{
	double y[2],z=0.0;
	__int32_t n,ix;

	GET_HIGH_WORD(ix,x);

	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) return __kernel_tan(x,z,1);

	else if (ix>=0x7ff00000) return x-x;		

	else {
	    n = __ieee754_rem_pio2(x,y);
	    return __kernel_tan(y[0],y[1],1-((n&1)<<1)); 
	}
}
