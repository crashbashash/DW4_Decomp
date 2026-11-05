#include "dw4/modelfade.h"
void dw4_modelfade_start(dw4_modelfade *f,int in,ee_f32 frames,ee_f32 limit,int64_t clock)
{*f=(dw4_modelfade){in?0:limit,ee_f32_div(limit,frames),limit,in?1:2,0,clock};}
void dw4_modelfade_tick(dw4_modelfade *f,int64_t clock)
{
    if(!f || !f->direction || f->direction==3 || (f->updated && clock==f->clock))return;
    ee_f32 delta=0x3f800000;
    if(f->updated){
        int64_t ns=(int64_t)(((uint64_t)(clock>>18)-(uint64_t)(f->clock>>18))*262144u);
        delta=ee_f32_div(ee_f32_from_s32((int32_t)ns),0x4b7e502b);
        if(ee_f32_cmp(delta,0x40400000)>0)delta=0x40400000;
    }
    ee_f32 step=ee_f32_mul(delta,f->step);
    f->value=f->direction==1?ee_f32_add(f->value,step):ee_f32_sub(f->value,step);
    if(f->direction==1 && ee_f32_cmp(f->value,f->limit)>=0)f->direction=3;
    if(f->direction==2 && ee_f32_cmp(f->value,0)<=0){f->value=0;f->direction=3;}
    f->clock=clock;f->updated=1;
}
