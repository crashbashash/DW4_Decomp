#include "dw4/hudmeter.h"
#include "eefloat.h"
#include <string.h>
static uint32_t bits(float f){uint32_t b;memcpy(&b,&f,4);return b;}
int dw4_hudmeter_init(dw4_hudmeter *s,float maximum,int notch,int64_t nonzero,int64_t nonmax)
{
    if(!s || !(maximum>0) || nonzero<0 || nonmax<nonzero)return -1;
    *s=(dw4_hudmeter){.maximum=bits(maximum),.notch=!!notch,.nonzero=nonzero,.nonmax=nonmax,.time=1000000000};
    s->ratio=ee_f32_div(bits(2000000000.0f),s->maximum);
    s->step=ee_f32_div(s->maximum,bits(60.0f));
    if(ee_f32_cmp(s->step,bits(1.0f))<0)s->step=bits(1.0f);
    return 0;
}
void dw4_hudmeter_percent(dw4_hudmeter *s,float percent)
{
    uint32_t p=bits(percent);s->target=ee_f32_div(ee_f32_mul(p,s->maximum),bits(100.0f));
    if(ee_f32_cmp(s->target,bits(1.0f))<0 && ee_f32_cmp(p,0))s->target=bits(1.0f);
}
void dw4_hudmeter_tick(dw4_hudmeter *s)
{
    uint32_t diff=ee_f32_sub(s->target,s->display);int direction=ee_f32_cmp(diff,0);
    if(!direction)return;
    if(direction<0)diff=ee_f32_sub(0,diff);
    uint32_t step=ee_f32_cmp(diff,s->step)<=0?diff:s->step;
    uint32_t value=direction<0?ee_f32_sub(s->display,step):ee_f32_add(s->display,step);
    if(ee_f32_cmp(value,0)<0)value=0;
    if(ee_f32_cmp(value,s->maximum)>0)value=s->maximum;
    if(s->notch){int nonzero=ee_f32_cmp(value,0)!=0;value=ee_f32_from_s32(ee_f32_trunc_s32(value));if(nonzero && !ee_f32_cmp(value,0))value=bits(1.0f);}
    s->display=value;
    if(ee_f32_cmp(value,0)<=0){s->display=0;s->time=1000000000;}
    else if(ee_f32_cmp(value,s->maximum)>=0){s->display=s->maximum;s->time=3000000000;}
    else {int64_t time=ee_f32_to_s64(ee_f32_mul(value,s->ratio));if(time<s->nonzero)time=s->nonzero;if(time>s->nonmax)time=s->nonmax;s->time=time+1000000000;}
}
