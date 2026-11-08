#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

#define FLT_UWORD_MAX 0x7fffffff
#define FLT_UWORD_IS_FINITE(x) 1
#define FLT_LARGEST_EXP (FLT_UWORD_MAX>>23)
#define FLT_UWORD_IS_ZERO(x) ((x)<0x00800000L)
#define FLT_UWORD_IS_SUBNORMAL(x) 0
#define FLT_SMALLEST_EXP 1

extern double FUN_001229c8(double, int);
extern float FUN_001230f8(float, float);



#if 2147483647 > 50000
#define OVERFLOW_INT 50000
#else
#define OVERFLOW_INT 30000
#endif

#define two25 ((float)3.355443200e+07)
#define twom25 ((float)2.9802322388e-08)
#define huge ((float)1.0e+30)
#define tiny ((float)1.0e-30)

	float FUN_00123310 (float x, int n)
{
	__int32_t  k,ix;
	__uint32_t hx;

	GET_FLOAT_WORD(ix,x);
	hx = ix&0x7fffffff;
        k = hx>>23;		
	if (FLT_UWORD_IS_ZERO(hx))
	    return x;
        if (!FLT_UWORD_IS_FINITE(hx))
	    return x+x;		
        if (FLT_UWORD_IS_SUBNORMAL(hx)) {
	    x *= two25;
	    GET_FLOAT_WORD(ix,x);
	    k = ((ix&0x7f800000)>>23) - 25; 
            if (n< -50000) return tiny*x; 	
        }
        k = k+n; 
        if (k > FLT_LARGEST_EXP) return huge*FUN_001230f8(huge,x); 
        if (k > 0) 				
	    {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
        if (k < FLT_SMALLEST_EXP) {
            if (n > OVERFLOW_INT) 	
		return huge*FUN_001230f8(huge,x);	
	    else return tiny*FUN_001230f8(tiny,x);	
        }
        k += 25;				
	SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
        return x*twom25;
}
