#ifndef DW4_HUDNUMBER_H
#define DW4_HUDNUMBER_H
#include <stdint.h>
/* beNumberCtrl's least-significant-first digit and vertex UV projection. */
int32_t dw4_hudnumber_digit(int32_t value,int mode,unsigned place);
void dw4_hudnumber_uv(int32_t digit,unsigned kind,float offset,float uv[2]);
#endif
