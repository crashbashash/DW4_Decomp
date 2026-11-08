#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

extern float FUN_0011f910(float);
extern float FUN_00123210(float);


#define one ((float)1.0000000000e+00)
#define huge ((float)1.000e+30)
#define pio2_hi ((float)1.5707962513e+00)
#define pio2_lo ((float)7.5497894159e-08)
#define pio4_hi ((float)7.8539818525e-01)
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

	float FUN_0011ea48(float x)
{
	float t,w,p,q,c,r,s;
	__int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix==0x3f800000) {

	    return x*pio2_hi+x*pio2_lo;	
	} else if(ix> 0x3f800000) {	
	    return (x-x)/(x-x);		   
	} else if (ix<0x3f000000) {	
	    if(ix<0x32000000) {		
		if(huge+x>one) return x;
          } else {
		t = x*x;
		p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
		q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
		w = p/q;
		return x+x*w;
          }
	}

	w = one-FUN_00123210(x);
	t = w*(float)0.5;
	p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
	q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
	s = FUN_0011f910(t);
	if(ix>=0x3F79999A) { 	
	    w = p/q;
	    t = pio2_hi-((float)2.0*(s+s*w)-pio2_lo);
	} else {
	    __int32_t iw;
	    w  = s;
	    GET_FLOAT_WORD(iw,w);
	    SET_FLOAT_WORD(w,iw&0xfffff000);
	    c  = (t-w*w)/(s+w);
	    r  = p/q;
	    p  = (float)2.0*s*r-(pio2_lo-(float)2.0*c);
	    q  = pio4_hi-(float)2.0*w;
	    t  = pio4_hi-(p-q);
	}    
	if(hx>0) return t; else return -t;    
}
