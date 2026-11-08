#include "dw4/ieee_words.h"

extern float atanf(float);
extern float fabsf(float);
#define tiny ((float)1.0e-30)
#define zero ((float)0.0)
#define pi_o_4 ((float)7.8539818525e-01)
#define pi_o_2 ((float)1.5707963705e+00)
#define pi ((float)3.1415925026e+00)
#define pi_lo ((float)1.5099578832e-07)

float __ieee754_atan2f(float y, float x)
{  
	float z;
	__int32_t k,m,hx,hy,ix,iy;

	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	GET_FLOAT_WORD(hy,y);
	iy = hy&0x7fffffff;
	if(FLT_UWORD_IS_NAN(ix)||
	   FLT_UWORD_IS_NAN(iy))	
	   return x+y;
	if(hx==0x3f800000) return atanf(y);   
	m = ((hy>>31)&1)|((hx>>30)&2);	

	if(FLT_UWORD_IS_ZERO(iy)) {
	    switch(m) {
		case 0: 
		case 1: return y; 	
		case 2: return  pi+tiny;
		case 3: return -pi-tiny;
	    }
	}

	if(FLT_UWORD_IS_ZERO(ix)) return (hy<0)?  -pi_o_2-tiny: pi_o_2+tiny;

	if(FLT_UWORD_IS_INFINITE(ix)) {
	    if(FLT_UWORD_IS_INFINITE(iy)) {
		switch(m) {
		    case 0: return  pi_o_4+tiny;
		    case 1: return -pi_o_4-tiny;
		    case 2: return  (float)3.0*pi_o_4+tiny;
		    case 3: return (float)-3.0*pi_o_4-tiny;
		}
	    } else {
		switch(m) {
		    case 0: return  zero  ;	
		    case 1: return -zero  ;	
		    case 2: return  pi+tiny  ;	
		    case 3: return -pi-tiny  ;	
		}
	    }
	}

	if(FLT_UWORD_IS_INFINITE(iy)) return (hy<0)? -pi_o_2-tiny: pi_o_2+tiny;

	k = (iy-ix)>>23;
	if(k > 60) z=pi_o_2+(float)0.5*pi_lo; 	
	else if(hx<0&&k<-60) z=0.0; 	
	else z=atanf(fabsf(y/x));	
	switch (m) {
	    case 0: return       z  ;	
	    case 1: {
	    	      __uint32_t zh;
		      GET_FLOAT_WORD(zh,z);
		      SET_FLOAT_WORD(z,zh ^ 0x80000000);
		    }
		    return       z  ;	
	    case 2: return  pi-(z-pi_lo);
	    default: 
	    	    return  (z-pi_lo)-pi;
	}
}
