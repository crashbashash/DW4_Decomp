#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

#define FLT_UWORD_IS_FINITE(x) 1

extern int FUN_0011f560(float, float *);
extern float FUN_00120fa8(float, float);
extern float FUN_00121960(float, float, int);
extern double FUN_00122bb0();


	float FUN_001233d8(float x)
{
	float y[2],z=0.0;
	__int32_t n,ix;

	GET_FLOAT_WORD(ix,x);

	ix &= 0x7fffffff;
	if(ix <= 0x3f490fd8) return FUN_00121960(x,z,0);

	else if (!FLT_UWORD_IS_FINITE(ix)) return x-x;

	else {
	    n = FUN_0011f560(x,y);
	    switch(n&3) {
		case 0: return  FUN_00121960(y[0],y[1],1);
		case 1: return  FUN_00120fa8(y[0],y[1]);
		case 2: return -FUN_00121960(y[0],y[1],1);
		default:
			return -FUN_00120fa8(y[0],y[1]);
	    }
	}
}
