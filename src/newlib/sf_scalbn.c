#include "dw4/ieee_words.h"

extern float copysignf(float, float);
#define OVERFLOW_INT 50000
#define two25 ((float)3.355443200e+07)
#define twom25 ((float)2.9802322388e-08)
#define huge ((float)1.0e+30)
#define tiny ((float)1.0e-30)

float scalbnf (float x, int n)
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
        if (k > FLT_LARGEST_EXP) return huge*copysignf(huge,x); 
        if (k > 0) 				
	    {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
        if (k < FLT_SMALLEST_EXP) {
            if (n > OVERFLOW_INT) 	
		return huge*copysignf(huge,x);	
	    else return tiny*copysignf(tiny,x);	
        }
        k += 25;				
	SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
        return x*twom25;
}
