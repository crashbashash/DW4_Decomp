#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

#define FLT_UWORD_IS_FINITE(x) 1
#define FLT_UWORD_IS_ZERO(x) ((x)<0x00800000L)
#define FLT_UWORD_IS_SUBNORMAL(x) 0

extern float FUN_0011f198(float);


static const float
two25      =  3.3554432000e+07, 
ivln10     =  4.3429449201e-01, 
log10_2hi  =  3.0102920532e-01, 
log10_2lo  =  7.9034151668e-07; 

static const float zero   =  0.0;

	float FUN_0011f478(float x)
{
	float y,z;
	__int32_t i,k,hx;

	GET_FLOAT_WORD(hx,x);

        k=0;
        if (FLT_UWORD_IS_ZERO(hx&0x7fffffff))
            return -two25/zero;             
        if (hx<0) return (x-x)/zero;        
	if (!FLT_UWORD_IS_FINITE(hx)) return x+x;
        if (FLT_UWORD_IS_SUBNORMAL(hx)) {
            k -= 25; x *= two25; 
	    GET_FLOAT_WORD(hx,x);
        }
	k += (hx>>23)-127;
	i  = ((__uint32_t)k&0x80000000)>>31;
        hx = (hx&0x007fffff)|((0x7f-i)<<23);
        y  = (float)(k+i);
	SET_FLOAT_WORD(x,hx);
	z  = y*log10_2lo + ivln10*FUN_0011f198(x);
	return  z+y*log10_2hi;
}
