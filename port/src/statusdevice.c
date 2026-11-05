#include "dw4/statusdevice.h"
#include <string.h>
int dw4_statusdevice_decide(const dw4_item_record *items,size_t count,int page,
    const dw4_statusdevice_filter *f,dw4_statusdevice_attribute attribute,void *u,dw4_statusdevice_rows *out)
{
    if(!f || !out || (count && !items) || count>96 || f->nkinds<0 || f->nkinds>4 || page<0 || page>7 || (count?(size_t)page*12>=count:page!=0))return -1;
    dw4_statusdevice_rows r={.pages=count?(int32_t)((count+11)/12):1};
    size_t n=count-(size_t)page*12;if(n>12)n=12;
    r.count=(int32_t)n;r.rows=n?(int32_t)n:1;
    for(size_t j=0;j<n;j++){
        const dw4_item_record *i=items+(size_t)page*12+j;int enabled=!f->nkinds;
        for(int k=0;k<f->nkinds;k++){
            if(f->kinds[k]==3 && i->kind==3){
                int32_t wu,blue;
                if(!attribute || attribute(u,i,"WU",&wu) || attribute(u,i,"BLUEAB",&blue))return -1;
                int32_t v=f->ab_type==1?blue:f->ab_type==0?wu:1;
                if((uint8_t)v==1){enabled=1;break;}
            }else if(f->kinds[k]>=0 && f->kinds[k]<=2 && f->kinds[k]==i->kind){enabled=1;break;}
        }
        int unknown=(i->kind==0 && i->record==276) || (i->kind==1 && i->record==31) || (i->kind==2 && i->record==44);
        if(f->equip_disable && (uint8_t)i->equipped)enabled=0;
        if(f->unknown_disable && unknown)enabled=0;
        if(f->unknown_enable)enabled=unknown;
        r.enabled[j]=(uint8_t)enabled;
    }
    *out=r;return 0;
}
static void state(dw4_statusctrl *s,int n){s->state=n;s->sub=s->delay=s->latch=0;}
static void sub(dw4_statusctrl *s,int n){s->sub=n;s->delay=s->latch=0;}
#define Q(op,v) io(u,c,op,v)
#define DO(op,v) do{if(Q(op,v)<0)return -1;}while(0)
int dw4_statusdevice_tick(dw4_statusdevice *c,dw4_statusdevice_io io,void *u)
{
    if(!c || !io)return -1;
    dw4_statusctrl *s=&c->window;int q;
    if(s->state==3){q=Q(DW4_DEVICE_FINISHED,0);if(q<0)return -1;if(q)s->active=0;return 0;}
    if(s->state==2){DO(DW4_DEVICE_CLOSE_MODELS,0);DO(DW4_DEVICE_CLEAR_TEXT,0);DO(DW4_DEVICE_CLOSE_CHILDREN,0);state(s,3);DO(DW4_DEVICE_COLORS,12);return 0;}
    if(s->state==0){DO(DW4_DEVICE_INIT,0);q=Q(DW4_DEVICE_COUNT,0);if(q<0)return -1;s->previous_count=q;state(s,1);}
    if(s->state!=1)return 0;
    if(s->sub==2){
        if(s->delay==1){
            q=Q(DW4_DEVICE_INVENTORY_COUNT,0);if(q<0)return -1;
            if(q<=c->row+c->page*12){if(!c->row){if(c->page>0)c->page--;}else c->row--;}
            DO(DW4_DEVICE_RESELECT,0);state(s,1);
        }
        return 0;
    }
    if(s->sub!=0 && s->sub!=1)return 0;
    if(!s->sub){DO(DW4_DEVICE_REFRESH,3);sub(s,1);}
    q=Q(DW4_DEVICE_COUNT,0);if(q<0)return -1;
    if(q==s->previous_count){
        if(s->selection!=-1){
            if(s->selection==s->latch){
                q=Q(DW4_DEVICE_TOP,0);if(q<0)return -1;
                if(q){q=Q(DW4_DEVICE_PREVIOUS,0);if(q<0)return -1;
                    if(!q){q=Q(DW4_DEVICE_NEXT,0);if(q<0)return -1;}
                    if(q){DO(DW4_DEVICE_REPAGE,0);sub(s,0);}
                }
            }else {DO(DW4_DEVICE_REFRESH,2);s->latch=s->selection;}
        }
    }else {
        int32_t selected=-1;
        if(s->selection!=-1){selected=c->page*12+s->selection;c->row=s->selection;}
        DO(DW4_DEVICE_PUBLISH,selected);
        if(c->auto_close)state(s,2);else sub(s,2);
    }
    return 0;
}
int dw4_statusdevice_hover(const dw4_statusdevice *c,int32_t *latch,const uint8_t enabled[12],int32_t *index)
{
    if(!c || !latch || !enabled || !index)return -1;
    if(c->window.state!=1 || c->window.sub!=1 || c->window.selection==-1)return 1;
    if(c->page<0 || c->page>2 || c->window.selection<0 || c->window.selection>=12)return -1;
    int32_t selected=c->page*12+c->window.selection;
    if(selected==*latch && *latch!=999)return 1;
    *latch=*index=selected;return enabled[c->window.selection]?0:2;
}
