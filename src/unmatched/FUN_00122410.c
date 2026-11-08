#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

extern int FUN_0011dd48(double, double *);
extern double FUN_0011f9e0(double, double);
extern double FUN_00120808(double, double, int);


#ifndef _DOUBLE_IS_32BITS

	double FUN_00122410(double x)
{
	double y[2],z=0.0;
	__int32_t n,ix;

	GET_HIGH_WORD(ix,x);

	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) return FUN_0011f9e0(x,z);

	else if (ix>=0x7ff00000) return x-x;

	else {
	    n = FUN_0011dd48(x,y);
	    switch(n&3) {
		case 0: return  FUN_0011f9e0(y[0],y[1]);
		case 1: return -FUN_00120808(y[0],y[1],1);
		case 2: return -FUN_0011f9e0(y[0],y[1]);
		default:
		        return  FUN_00120808(y[0],y[1],1);
	    }
	}
}

#endif 
