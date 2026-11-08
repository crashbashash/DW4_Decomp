#include "dw4/ieee_words.h"

extern int finite(double);
extern double scalbn(double, int);
extern int *__errno(void);

double ldexp(double value, int exp)
{
	if(!finite(value)||value==0.0) return value;
	value = scalbn(value,exp);
	if(!finite(value)||value==0.0) (*__errno()) = 34;
	return value;
}
