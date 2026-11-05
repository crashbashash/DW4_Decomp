#include "dw4/padrepeat.h"
void dw4_padrepeat_init(dw4_padrepeat *s)
{*s=(dw4_padrepeat){.first=10,.next=6};}
void dw4_padrepeat_tick(dw4_padrepeat *s,uint32_t held)
{
    uint32_t previous=s->held;s->held=held;s->trigger=held&(previous^held);
    if(previous==held){
        s->countdown=(int32_t)((uint32_t)s->countdown-1u);
        if(!s->countdown){s->repeat=held;s->countdown=s->next;}else s->repeat=0;
    }else{s->repeat=s->trigger;s->countdown=s->first;}
}

#include "eefloat.h"
#include <math.h>
#include <string.h>
static uint32_t bits(float value){uint32_t b;memcpy(&b,&value,4);return b;}
static float from_bits(uint32_t b){float value;memcpy(&value,&b,4);return value;}
uint32_t dw4_pad_directions_polar(float length,float angle,float threshold,float spread)
{
    uint32_t r=bits(length),a=bits(angle),limit=bits(threshold),half=ee_f32_mul(bits(spread),0x3f000000),out=0;
    if(ee_f32_cmp(r,limit)<0)return 0;
    if(ee_f32_cmp(a,ee_f32_add(0xc016cbe4,half))<0)out|=8;
    if(ee_f32_cmp(a,ee_f32_sub(0xc016cbe4,half))>=0 && ee_f32_cmp(a,ee_f32_add(0xbf490fdb,half))<=0)out|=4;
    if(ee_f32_cmp(a,ee_f32_sub(0xbf490fdb,half))>0 && ee_f32_cmp(a,ee_f32_add(0x3f490fdb,half))<0)out|=2;
    if(ee_f32_cmp(a,ee_f32_sub(0x3f490fdb,half))>=0 && ee_f32_cmp(a,ee_f32_add(0x4016cbe4,half))<=0)out|=1;
    if(ee_f32_cmp(a,ee_f32_sub(0x4016cbe4,half))>0)out|=8;
    return out;
}
/* sqrt.s rounds toward zero in the existing EE arithmetic model. */
static uint32_t positive_sqrt(uint32_t squared)
{
    float value=sqrtf(from_bits(squared));uint32_t result=bits(value);
    if((double)value*(double)value>(double)from_bits(squared) && result)result--;
    return result;
}
uint32_t dw4_pad_directions(float x,float y)
{
    if(!isfinite(x) || !isfinite(y))return 0;
    uint32_t radius=positive_sqrt(ee_f32_add(ee_f32_mul(bits(x),bits(x)),ee_f32_mul(bits(y),bits(y))));
    uint32_t threshold=positive_sqrt(ee_f32_mul(0x3ecccccd,0x3ecccccd));
    return dw4_pad_directions_polar(from_bits(radius),atan2f(y,x),from_bits(threshold),from_bits(0x3f490fdb));
}
