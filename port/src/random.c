#include "dw4/random.h"
#include <string.h>
void dw4_random_init(dw4_random *r)
{
    uint32_t seed=5150;
    for(unsigned i=0;i<624;i++) {
        r->words[i]=seed&0xffff0000u;
        seed=69069u*seed+1u;
        r->words[i]|=seed>>16;
        seed=69069u*seed+1u;
    }
    r->index=624;
}
uint32_t dw4_random_next(dw4_random *r)
{
    if(r->index>=624) {
        /* In-place twist: later positions consume already replaced words. */
        for(unsigned i=0;i<624;i++) {
            uint32_t y=(r->words[i]&0x80000000u)|(r->words[(i+1)%624]&0x7fffffffu);
            r->words[i]=r->words[(i+397)%624]^(y>>1)^((y&1)?0x9908b0dfu:0);
        }
        r->index=0;
    }
    uint32_t y=r->words[r->index++];
    y^=y>>11;
    y^=(y<<7)&0x9d2c5680u;
    y^=(y<<15)&0xefc60000u;
    return y^(y>>18);
}
int32_t dw4_random_mod(dw4_random *r,int32_t modulus)
{
    uint32_t value=dw4_random_next(r);
    if(modulus)value%=(uint32_t)modulus;
    int32_t result;
    memcpy(&result,&value,sizeof(result));
    return result;
}
