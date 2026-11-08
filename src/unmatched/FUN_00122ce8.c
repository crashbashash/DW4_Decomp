#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

extern int FUN_0011dd48(double, double *);
extern double FUN_00120a40(double, double, int);


#ifndef _DOUBLE_IS_32BITS

	double FUN_00122ce8(double x)
{
	double y[2],z=0.0;
	__int32_t n,ix;

	GET_HIGH_WORD(ix,x);

	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) return FUN_00120a40(x,z,1);

	else if (ix>=0x7ff00000) return x-x;		

	else {
	    n = FUN_0011dd48(x,y);
	    return FUN_00120a40(y[0],y[1],1-((n&1)<<1)); 
	}
}

#endif 
