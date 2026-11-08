#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;



#define half ((float)5.0000000000e-01)
#define S1 ((float)-1.6666667163e-01)
#define S2 ((float)8.3333337680e-03)
#define S3 ((float)-1.9841270114e-04)
#define S4 ((float)2.7557314297e-06)
#define S5 ((float)-2.5050759689e-08)
#define S6 ((float)1.5896910177e-10)

	float FUN_00121960(float x, float y, int iy)
{
	float z,r,v;
	__int32_t ix;
	GET_FLOAT_WORD(ix,x);
	ix &= 0x7fffffff;			
	if(ix<0x32000000)			
	   {if((int)x==0) return x;}		
	z	=  x*x;
	v	=  z*x;
	r	=  S2+z*(S3+z*(S4+z*(S5+z*S6)));
	if(iy==0) return x+v*(S1+z*r);
	else      return x-((z*(half*y-v*r)-y)-v*S1);
}
