#include "dw4/selectctrl.h"
#include <stdio.h>
#include <string.h>
static int send(dw4_selectctrl *s,dw4_selectctrl_io io,void *u,const char *key,const char *seq)
{
    snprintf(s->sequence,sizeof s->sequence,"%s",seq);
    return io(u,0,key,s->sequence)<0?-1:0;
}
static int line(dw4_selectctrl *s,dw4_selectctrl_io io,void *u,const char *format)
{
    char seq[32];snprintf(seq,sizeof seq,format,s->selected);return send(s,io,u,seq,seq);
}
static void reset(dw4_selectctrl *s,int state)
{s->state=state;s->sub=s->delay=s->latch=0;}
int dw4_selectctrl_tick(dw4_selectctrl *s,uint32_t analog,uint32_t held,
    uint32_t pressed,dw4_selectctrl_io io,void *u)
{
    if(!s->active)return 0;
    int q;
    switch(s->state) {
    case 0:
        if(!s->sub) {if(send(s,io,u,"GENERATE","SQ_OPEN"))return -1;s->sub=1;s->delay=s->latch=0;}
        else if(s->sub==1) {
            q=io(u,1,"ISSEQNAME","SQ_OPEN");if(q<0)return -1;
            if(q!=1){if(line(s,io,u,"SQ_LINESL%02d"))return -1;reset(s,1);}
        }
        break;
    case 1:
        if(s->sub==2) {
            if(s->delay<16){s->delay++;s->latch=0;}else{s->sub=s->delay=s->latch=0;}
        } else if(s->sub==1) {
            q=io(u,1,"ISSEQNAME",s->sequence);if(q<0)return -1;if(!q)reset(s,2);
        } else if(!s->sub) {
            if(analog || (held&0xf0)) {
                if(!s->latch) {
                    int left=(analog&8)||(held&0x80),right=(analog&2)||(held&0x20);
                    int up=(analog&1)||(held&0x10),down=(analog&4)||(held&0x40);
                    if((s->vertical?up:left) && s->selected!=0) {
                        s->selected--;if(line(s,io,u,"SQ_LINEUP%02d"))return -1;s->latch++;
                    } else if(!(s->vertical?up:left) && (s->vertical?down:right) && s->selected!=s->count-1) {
                        s->selected++;if(line(s,io,u,"SQ_LINEDW%02d"))return -1;s->latch++;
                    }
                } else {
                    q=io(u,1,"ISSEQNAME",s->sequence);if(q<0)return -1;if(!q)s->latch=0;
                }
            }
            /* Circle takes priority when both edges arrive together. */
            if(pressed&0x2000) {
                if(s->cancel){s->selected=-1;reset(s,2);}
                else {if(io(u,0,"SOUND","ERROR")<0)return -1;s->sub=2;s->delay=s->latch=0;}
            } else if(pressed&0x4000) {
                if(!s->enabled || s->enabled[s->selected]) {
                    if(line(s,io,u,"SQ_LINEON%02d"))return -1;
                    s->sub=1;s->delay=s->latch=0;
                } else {if(io(u,0,"SOUND","ERROR")<0)return -1;s->sub=2;s->delay=s->latch=0;}
            }
        }
        break;
    case 2:
        if(!s->sub) {
            const char *seq=s->selected==-1?"SQ_CANCEL":"SQ_CLOSE";
            if(send(s,io,u,seq,seq))return -1;
            s->sub=1;s->delay=s->latch=0;
        } else if(s->sub==1) {
            q=io(u,1,"ISSEQNAME",s->sequence);if(q<0)return -1;if(!q)reset(s,3);
        }
        break;
    case 10:
        if(!s->sub){if(send(s,io,u,"SQ_FO2TOP","SQ_FO2TOP"))return -1;s->sub=1;s->delay=s->latch=0;}
        else if(s->sub==1){q=io(u,1,"ISSEQNAME","SQ_FO2TOP");if(q<0)return -1;if(!q)reset(s,1);}
        break;
    default:s->active=0;break;
    }
    return 0;
}
