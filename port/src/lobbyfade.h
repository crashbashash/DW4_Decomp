/* beAction2FADESET_Start/Update (376930/376680), frame timer 3a8140.
 * Presentation attributes are native; arithmetic and the initial delta are EE. */
#ifndef DW4_LOBBYFADE_H
#define DW4_LOBBYFADE_H
#include "eefloat.h"
#include <string.h>
typedef struct { ee_f32 value,step; int direction,updated; int64_t clock; } lobby_fade;
static inline void lobby_fade_start(lobby_fade *f,int in,ee_f32 frames,int64_t clock)
{
    *f=(lobby_fade){in?0:0x3f800000,ee_f32_div(0x3f800000,frames),in?1:2,0,clock};
}
static inline void lobby_fade_tick(lobby_fade *f,int64_t clock)
{
    if(!f->direction || f->direction==3 || (f->updated && clock==f->clock)) return;
    ee_f32 delta=0x3f800000;
    if(f->updated) {
        int64_t ns=((clock>>18)-(f->clock>>18))*262144;
        delta=ee_f32_div(ee_f32_from_s32((int32_t)ns),0x4b7e502b); /* 16666667 */
        if(ee_f32_cmp(delta,0x40400000)>0) delta=0x40400000;
    }
    ee_f32 step=ee_f32_mul(delta,f->step);
    f->value=f->direction==1?ee_f32_add(f->value,step):ee_f32_sub(f->value,step);
    if(f->direction==1 && ee_f32_cmp(f->value,0x3f800000)>=0) f->direction=3;
    if(f->direction==2 && ee_f32_cmp(f->value,0)<=0) {f->value=0;f->direction=3;}
    f->clock=clock;f->updated=1;
}
static inline float lobby_fade_alpha(const lobby_fade *f)
{ float value;memcpy(&value,&f->value,4);return value<0?0:value>1?1:value; }
#endif
