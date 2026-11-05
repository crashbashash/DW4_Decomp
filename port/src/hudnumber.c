#include "dw4/hudnumber.h"
#include "eefloat.h"
#include <string.h>
int32_t dw4_hudnumber_digit(int32_t value,int mode,unsigned place)
{
    if(value<0)return mode?-1:0;
    for(unsigned i=0;i<place;i++)value/=10;
    return !value && place && mode?-1:value%10;
}
void dw4_hudnumber_uv(int32_t digit,unsigned kind,float offset,float uv[2])
{
    if(digit<0){uv[0]=uv[1]=0;return;}
    uint32_t step;memcpy(&step,&offset,4);
    uint32_t u=ee_f32_mul(ee_f32_from_s32(digit),step);
    if(kind==1 || kind==3)u=ee_f32_add(step,u);
    memcpy(uv,&u,4);uv[1]=kind>=2?1:0;
}
