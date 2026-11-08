#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

#define FLT_UWORD_IS_FINITE(x) 1
#define FLT_UWORD_IS_ZERO(x) ((x)<0x00800000L)
#define FLT_UWORD_IS_SUBNORMAL(x) 0



#define one ((float)1.0)
#define tiny ((float)1.0e-30)

	float FUN_0011f910(float x)
{
	float z;
	__int32_t 	sign = (__int32_t)0x80000000; 
	__uint32_t r,hx;
	__int32_t ix,s,q,m,t,i;

	GET_FLOAT_WORD(ix,x);
	hx = ix&0x7fffffff;

	if(!FLT_UWORD_IS_FINITE(hx))
	    return x*x+x;		

	if(FLT_UWORD_IS_ZERO(hx)) return x;
	if(ix<0) return (x-x)/(x-x);		

	m = (ix>>23);
	if(FLT_UWORD_IS_SUBNORMAL(hx)) {		
	    for(i=0;(ix&0x00800000L)==0;i++) ix<<=1;
	    m -= i-1;
	}
	m -= 127;	
	ix = (ix&0x007fffffL)|0x00800000L;
	if(m&1)	
	    ix += ix;
	m >>= 1;	

	ix += ix;
	q = s = 0;		
	r = 0x01000000L;		

	while(r!=0) {
	    t = s+r; 
	    if(t<=ix) { 
		s    = t+r; 
		ix  -= t; 
		q   += r; 
	    } 
	    ix += ix;
	    r>>=1;
	}

	if(ix!=0) {
	    z = one-tiny; 
	    if (z>=one) {
	        z = one+tiny;
		if (z>one)
		    q += 2;
		else
		    q += (q&1);
	    }
	}
	ix = (q>>1)+0x3f000000L;
	ix += (m <<23);
	SET_FLOAT_WORD(z,ix);
	return z;
}
