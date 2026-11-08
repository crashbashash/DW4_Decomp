#include "dw4/ieee_words.h"

extern float __ieee754_sqrtf(float);
#define one ((float)1.0000000000e+00)
#define pi ((float)3.1415925026e+00)
#define pio2_hi ((float)1.5707962513e+00)
#define pio2_lo ((float)7.5497894159e-08)
#define pS0 ((float)1.6666667163e-01)
#define pS1 ((float)-3.2556581497e-01)
#define pS2 ((float)2.0121252537e-01)
#define pS3 ((float)-4.0055535734e-02)
#define pS4 ((float)7.9153501429e-04)
#define pS5 ((float)3.4793309169e-05)
#define qS1 ((float)-2.4033949375e+00)
#define qS2 ((float)2.0209457874e+00)
#define qS3 ((float)-6.8828397989e-01)
#define qS4 ((float)7.7038154006e-02)

float __ieee754_acosf(float x)
{
	float z,p,q,r,w,s,c,df;
	__int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix==0x3f800000) {		
	    if(hx>0) return 0.0;	
	    else return pi+(float)2.0*pio2_lo;	
	} else if(ix>0x3f800000) {	
	    return (x-x)/(x-x);		
	}
	if(ix<0x3f000000) {	
	    if(ix<=0x23000000) return pio2_hi+pio2_lo;
	    z = x*x;
	    p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	    q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	    r = p/q;
	    return pio2_hi - (x - (pio2_lo-x*r));
	} else  if (hx<0) {		
	    z = (one+x)*(float)0.5;
	    p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	    q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	    s = __ieee754_sqrtf(z);
	    r = p/q;
	    w = r*s-pio2_lo;
	    return pi - (float)2.0*(s+w);
	} else {			
	    __int32_t idf;
	    z = (one-x)*(float)0.5;
	    s = __ieee754_sqrtf(z);
	    df = s;
	    GET_FLOAT_WORD(idf,df);
	    SET_FLOAT_WORD(df,idf&0xfffff000);
	    c  = (z-df*df)/(s+df);
	    p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	    q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	    r = p/q;
	    w = r*s+c;
	    return (float)2.0*(df+w);
	}
}
