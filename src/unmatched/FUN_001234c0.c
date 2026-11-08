#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

#define FLT_UWORD_IS_FINITE(x) 1

extern int FUN_0011f560(float, float *);
extern float FUN_00121a68(float, float, int);
extern double FUN_00122ce8();


	float FUN_001234c0(float x)
{
	float y[2],z=0.0;
	__int32_t n,ix;

	GET_FLOAT_WORD(ix,x);

	ix &= 0x7fffffff;
	if(ix <= 0x3f490fda) return FUN_00121a68(x,z,1);

	else if (!FLT_UWORD_IS_FINITE(ix)) return x-x;		

	else {
	    n = FUN_0011f560(x,y);
	    return FUN_00121a68(y[0],y[1],1-((n&1)<<1)); 
	}
}
