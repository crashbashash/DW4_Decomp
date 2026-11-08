#include "dw4/ieee_words.h"

typedef int __int32_t;
typedef unsigned int __uint32_t;

extern int FUN_00122570(double);
extern double FUN_001229c8(double, int);
extern int *FUN_00124d50(void);


#ifndef _DOUBLE_IS_32BITS

	double FUN_00122918(double value, int exp)
{
	if(!FUN_00122570(value)||value==0.0) return value;
	value = FUN_001229c8(value,exp);
	if(!FUN_00122570(value)||value==0.0) (*FUN_00124d50()) = 34;
	return value;
}

#endif 
