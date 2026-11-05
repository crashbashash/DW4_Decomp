#include "dw4/cameratime.h"
static int less(uint64_t a,uint64_t b)
{ return (a^(UINT64_C(1)<<63)) < (b^(UINT64_C(1)<<63)); }
void dw4_camera_time_tick(dw4_camera_time *c,uint64_t now)
{
    if(!c->loaded)return;
    if(c->frozen){c->last=now;return;}
    if(c->finished)return;
    uint64_t delta=c->last ? now-c->last : 0;
    if(!less(delta,UINT64_C(50000001)))delta=50000000;
    c->time+=delta;c->last=now;
    if(!less(c->time,c->end)){c->finished=1;c->time=c->end;}
}
