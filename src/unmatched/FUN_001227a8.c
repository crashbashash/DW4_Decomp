#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;



#ifndef _DOUBLE_IS_32BITS

#define two54 1.80143985094819840000e+16

	double FUN_001227a8(double x, int *eptr)
{
	__int32_t hx, ix, lx;
	EXTRACT_WORDS(hx,lx,x);
	ix = 0x7fffffff&hx;
	*eptr = 0;
	if(ix>=0x7ff00000||((ix|lx)==0)) return x;	
	if (ix<0x00100000) {		
	    x *= two54;
	    GET_HIGH_WORD(hx,x);
	    ix = hx&0x7fffffff;
	    *eptr = -54;
	}
	*eptr += (ix>>20)-1022;
	hx = (hx&0x800fffff)|0x3fe00000;
	SET_HIGH_WORD(x,hx);
	return x;
}

#endif 
