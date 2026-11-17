#include "dw4/ieee_words.h"
#include "dw4/newlib_reent.h"

extern int finite(double);
extern double scalbn(double, int);

double ldexp(double value, int exp)
{
	if(!finite(value)||value==0.0) return value;
	value = scalbn(value,exp);
	if(!finite(value)||value==0.0) (*__errno()) = 34;
	return value;
}
