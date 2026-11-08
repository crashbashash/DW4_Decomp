#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;



#ifndef _DOUBLE_IS_32BITS

	double FUN_00122538(double x)
{
	__uint32_t high;
	GET_HIGH_WORD(high,x);
	SET_HIGH_WORD(x,high&0x7fffffff);
        return x;
}

#endif 
