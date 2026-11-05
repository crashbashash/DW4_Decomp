#include "dw4/statusbitctrl.h"
static void state(dw4_statusctrl *s,int n)
{s->state=n;s->sub=s->delay=s->latch=0;}
int dw4_statusbitctrl_tick(dw4_statusbit_ctrl *c,dw4_statusbit_io io,void *u)
{
    if(!c || !io)return -1;
    dw4_statusctrl *s=&c->window;int q;
    if(s->state==3){q=io(u,c,DW4_BIT_FINISHED,0);if(q<0)return -1;if(q)s->active=0;return 0;}
    if(s->state==2){if(io(u,c,DW4_BIT_CLOSE,0)<0)return -1;state(s,3);return 0;}
    if(s->state==0){
        q=io(u,c,DW4_BIT_COLLECT,0);if(q<0)return -1;c->recipients=q;
        state(s,1);s->sub=q?1:0;
    }
    if(s->state!=1 || (s->sub!=0 && s->sub!=1))return 0;
    if(s->delay==0){
        if(io(u,c,s->sub?DW4_BIT_SEND_CHILD:DW4_BIT_POPUP,s->sub?0:88)<0)return -1;
        q=io(u,c,DW4_BIT_COUNT,0);if(q<0)return -1;s->previous_count=q;s->delay=1;s->latch=0;
        if(!s->sub)return 0; /* No-recipient popup does not fall through. */
    }else if(s->delay!=1)return 0;
    q=io(u,c,DW4_BIT_COUNT,0);if(q<0)return -1;
    if(q!=s->previous_count)state(s,2);
    return 0;
}
#define DO(op,v) do{if(io(u,c,op,v)<0)return -1;}while(0)
static int count(dw4_statussendbit_ctrl *c,dw4_statussendbit_io io,void *u)
{int q=io(u,c,DW4_SEND_COUNT,0);if(q<0)return -1;c->window.previous_count=q;return 0;}
static int changed(dw4_statussendbit_ctrl *c,dw4_statussendbit_io io,void *u)
{int q=io(u,c,DW4_SEND_COUNT,0);return q<0?-1:q!=c->window.previous_count;}
int dw4_statussendbitctrl_tick(dw4_statussendbit_ctrl *c,dw4_statussendbit_io io,void *u)
{
    if(!c || !io)return -1;
    dw4_statusctrl *s=&c->window;int q;
    if(s->state==3){q=io(u,c,DW4_SEND_FINISHED,0);if(q<0)return -1;if(q)s->active=0;return 0;}
    if(s->state==2){DO(DW4_SEND_CLOSE,0);state(s,3);DO(DW4_SEND_HIDE_DIGITS,0);return 0;}
    if(s->state==0){DO(DW4_SEND_INIT,0);c->recipient=0;state(s,1);}
    if(s->state!=1)return 0;
    if(s->delay==4){
        q=changed(c,io,u);if(q<0)return -1;
        if(q){DO(DW4_SEND_ACK_HIDE,0);DO(DW4_SEND_REFRESH,0);DO(DW4_SEND_CURSOR_CLOSE,0);s->delay=s->latch=0;}
    }else if(s->delay==3){
        DO(DW4_SEND_POPUP,133);if(count(c,io,u))return -1;s->delay++;s->latch=0;
    }else if(s->delay==2){
        q=changed(c,io,u);if(q<0)return -1;
        if(!q){if(s->selection!=-1)DO(DW4_SEND_EDIT,0);}
        else if(s->selection==-1 || c->amount<1){DO(DW4_SEND_CURSOR_CLOSE,0);s->delay=s->latch=0;}
        else{DO(DW4_SEND_HIDE_PROMPT,0);DO(DW4_SEND_TRANSFER,0);s->delay++;s->latch=0;}
    }else{
        if(s->delay!=1){
            if(s->delay)return 0;
            DO(DW4_SEND_HIDE_DIGITS,0);c->amount=0;DO(DW4_SEND_RESET,0);
            if(count(c,io,u))return -1;
            s->delay++;s->latch=0;
        }
        q=changed(c,io,u);if(q<0)return -1;
        if(q){
            if(s->selection==-1)state(s,2);
            else{
                c->recipient=s->selection;DO(DW4_SEND_CURSOR_OPEN,0);DO(DW4_SEND_NUMBER_SELECTOR,0);DO(DW4_SEND_NUMBER,1);
                if(count(c,io,u))return -1;
                q=io(u,c,DW4_SEND_LIMIT,0);if(q<0)return -1;c->limit=q;
                if(count(c,io,u))return -1;
                s->delay++;s->latch=0;
            }
        }
    }
    return 0;
}
#undef DO
