#include "dw4/ieee_words.h"

extern int __ieee754_rem_pio2(double, double *);
extern double __kernel_cos(double, double);
extern double __kernel_sin(double, double, int);

double sin(double x)
{
	double y[2],z=0.0;
	__int32_t n,ix;

	GET_HIGH_WORD(ix,x);

	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) return __kernel_sin(x,z,0);

	else if (ix>=0x7ff00000) return x-x;

	else {
	    n = __ieee754_rem_pio2(x,y);
	    switch(n&3) {
		case 0: return  __kernel_sin(y[0],y[1],1);
		case 1: return  __kernel_cos(y[0],y[1]);
		case 2: return -__kernel_sin(y[0],y[1],1);
		default:
			return -__kernel_cos(y[0],y[1]);
	    }
	}
}
