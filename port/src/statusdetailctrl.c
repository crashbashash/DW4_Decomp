#include "dw4/statusdetailctrl.h"
static void phase(dw4_statusctrl *s,int sub,int delay)
{s->sub=sub;s->delay=delay;s->latch=0;}
static void state(dw4_statusctrl *s,int n)
{s->state=n;phase(s,0,0);}
static int snapshot(dw4_statusdetail_ctrl *c,dw4_statusdetail_io io,void *u)
{int q=io(u,c,DW4_DETAIL_COUNT,0);if(q<0)return -1;c->window.previous_count=q;return 0;}
static int changed(dw4_statusdetail_ctrl *c,dw4_statusdetail_io io,void *u)
{int q=io(u,c,DW4_DETAIL_COUNT,0);return q<0?-1:q!=c->window.previous_count;}
#define DO(op,v) do{if(io(u,c,op,v)<0)return -1;}while(0)
int dw4_statusdetailctrl_tick(dw4_statusdetail_ctrl *c,dw4_statusdetail_io io,void *u)
{
    if(!c || !io)return -1;
    dw4_statusctrl *s=&c->window;int q;
    if(s->state==3){q=io(u,c,DW4_DETAIL_FINISHED,0);if(q<0)return -1;if(q)s->active=0;return 0;}
    if(s->state==2){
        DO(DW4_DETAIL_CLOSE,0);if(s->latch==-1)DO(DW4_DETAIL_DEFAULT_COLOR,0);
        state(s,3);return 0;
    }
    if(s->state==0){DO(DW4_DETAIL_INIT,0);if(snapshot(c,io,u))return -1;state(s,1);}
    if(s->state!=1)return 0;
    switch(s->sub){
    case 0:
        q=changed(c,io,u);if(q<0)return -1;
        if(q){if(s->selection>=0 && s->selection<=2)phase(s,s->selection+1,0);else state(s,2);}
        break;
    case 1:
        if(s->delay!=2){
            if(s->delay!=1){
                if(s->delay)goto discard_end;
                q=io(u,c,DW4_DETAIL_DISCARD_CHECK,0);if(q<0)return -1;
                DO(DW4_DETAIL_POPUP,q);s->delay=q==78?1:10;s->latch=0;
                if(snapshot(c,io,u))return -1;
            }
            q=changed(c,io,u);if(q<0)return -1;if(!q)return 0;
            DO(DW4_DETAIL_CONFIRM,79);if(snapshot(c,io,u))return -1;s->delay++;s->latch=0;
        }
        q=changed(c,io,u);if(q<0)return -1;if(!q)return 0;
        if(s->selection==0)DO(DW4_DETAIL_REMOVE,0);
discard_end:
        q=changed(c,io,u);if(q<0)return -1;if(q)state(s,2);
        break;
    case 2:DO(DW4_DETAIL_SORT,0);state(s,2);break;
    case 3:
        if(s->delay==0){
            q=io(u,c,DW4_DETAIL_GIVE_CHECK,0);if(q<0)return -1;
            if(q){DO(DW4_DETAIL_POPUP,q);if(snapshot(c,io,u))return -1;s->delay=4;s->latch=0;return 0;}
            if(!c->retained)state(s,2);
            else{DO(DW4_DETAIL_DEVICE_CLOSE,0);DO(DW4_DETAIL_CURSOR_CLOSE,1);s->delay++;s->latch=0;}
            DO(DW4_DETAIL_CLEAR_TEXT,0);return 0;
        }
        if(s->delay==1){
            q=io(u,c,DW4_DETAIL_DEVICE_FINISHED,0);if(q<0)return -1;if(!q)return 0;
            DO(DW4_DETAIL_DEVICE_RELEASE,0);c->retained=0;DO(DW4_DETAIL_GIVE_SETUP,0);s->delay++;s->latch=0;return 0;
        }
        if(s->delay==2){
            DO(DW4_DETAIL_RECIPIENT_SELECTOR,0);if(snapshot(c,io,u))return -1;s->delay++;s->latch=0;
        }else if(s->delay!=3)goto give_end;
        q=changed(c,io,u);if(q<0)return -1;if(!q)return 0;
        if(s->selection==-1){state(s,2);return 0;}
        c->recipient=s->selection;q=io(u,c,DW4_DETAIL_RECIPIENT_COUNT,0);if(q<0)return -1;
        DO(DW4_DETAIL_POPUP,q<36?131:149);if(snapshot(c,io,u))return -1;s->delay++;s->latch=-1;
        if(q<36)DO(DW4_DETAIL_TRANSFER,0);
        DO(DW4_DETAIL_CURSOR_OPEN,0);return 0;
give_end:
        q=changed(c,io,u);if(q<0)return -1;
        if(q){int32_t latch=s->latch;DO(DW4_DETAIL_CURSOR_CLOSE,0);state(s,2);s->latch=latch;}
        break;
    default:break;
    }
    return 0;
}
#undef DO
