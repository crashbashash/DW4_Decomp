#include "dw4/statusdiskctrl.h"
static void phase(dw4_statusctrl *s,int sub,int delay)
{s->sub=sub;s->delay=delay;s->latch=0;}
static void state(dw4_statusctrl *s,int n)
{s->state=n;phase(s,0,0);}
static int snapshot(dw4_statusdisk_ctrl *c,dw4_statusdisk_io io,void *u)
{int n=io(u,c,DW4_DISK_COUNT,0);if(n<0)return -1;c->window.previous_count=n;return 0;}
static int changed(dw4_statusdisk_ctrl *c,dw4_statusdisk_io io,void *u)
{int n=io(u,c,DW4_DISK_COUNT,0);return n<0?-1:n!=c->window.previous_count;}
#define DO(op,v) do{if(io(u,c,op,v)<0)return -1;}while(0)
int dw4_statusdiskctrl_tick(dw4_statusdisk_ctrl *c,dw4_statusdisk_io io,void *u)
{
    if(!c || !io)return -1;
    dw4_statusctrl *s=&c->window;int q;
    if(s->state==3){q=io(u,c,DW4_DISK_FINISHED,0);if(q<0)return -1;if(q)s->active=0;return 0;}
    if(s->state==2){DO(DW4_DISK_CLOSE,0);state(s,3);return 0;}
    if(s->state==0){
        if(!s->sub)c->selected=0;
        DO(DW4_DISK_INIT,0);state(s,1);
    }
    if(s->state!=1)return 0;
    switch(s->sub){
    case 0:
        DO(DW4_DISK_MAIN_SELECTOR,0);if(snapshot(c,io,u))return -1;
        phase(s,2,c->selected);s->latch=999;DO(DW4_DISK_REFRESH,1);break;
    case 2:
        q=changed(c,io,u);if(q<0)return -1;
        if(!q){
            if(s->selection!=-1 && (s->delay!=s->selection || s->latch==999)){
                DO(DW4_DISK_REFRESH,0);s->delay=s->selection;s->latch=0;
            }
        }else if(s->selection==-1)state(s,2);
        else{c->selected=s->selection;phase(s,3,0);}break;
    case 3:
        if(s->delay!=2){
            if(s->delay!=1){
                if(s->delay)return 0;
                DO(DW4_DISK_ACTION_SELECTOR,0);if(snapshot(c,io,u))return -1;
                s->delay++;s->latch=0;
            }
            DO(DW4_DISK_ACTION_TEXT,65);s->delay++;s->latch=0;
        }
        q=changed(c,io,u);if(q<0)return -1;
        if(q){
            if(s->selection==1)phase(s,5,0);
            else if(s->selection==0)phase(s,4,0);
            else{DO(DW4_DISK_CURSOR_CLOSE,0);phase(s,0,0);}
        }break;
    case 4:
        if(s->delay==2){
            q=changed(c,io,u);if(q<0)return -1;
            if(!q){if(s->selection!=-1 && s->latch!=s->selection){DO(DW4_DISK_REFRESH,0);s->latch=s->selection;}}
            else{
                if(s->selection!=-1)DO(DW4_DISK_SWAP,0);
                DO(DW4_DISK_CURSOR_CLOSE,0);phase(s,0,0);
            }
        }else{
            if(s->delay!=1){
                if(s->delay)return 0;
                DO(DW4_DISK_REORDER_SELECTOR,0);if(snapshot(c,io,u))return -1;s->delay++;s->latch=0;
            }
            s->delay++;s->latch=c->selected;
        }break;
    case 5:
        if(s->delay!=2){
            if(s->delay!=1){
                if(s->delay)return 0;
                q=io(u,c,DW4_DISK_GIVE_CHECK,0);if(q<0)return -1;
                if(!q){c->recipient=0;phase(s,6,0);return 0;}
                DO(DW4_DISK_POPUP,q);s->delay++;s->latch=0;return 0;
            }
            if(snapshot(c,io,u))return -1;
            s->delay++;s->latch=0;
        }
        q=changed(c,io,u);if(q<0)return -1;
        if(q){DO(DW4_DISK_CURSOR_CLOSE,0);phase(s,0,0);}break;
    case 6:
        switch(s->delay){
        case 0:DO(DW4_DISK_RETIRE_MAIN,0);s->delay++;s->latch=0;break;
        case 1:s->delay++;s->latch=0;break;
        case 2:DO(DW4_DISK_GIVE_SETUP,0);s->delay++;s->latch=0;
            /* fall through */
        case 3:
            DO(DW4_DISK_RECIPIENT_SELECTOR,0);if(snapshot(c,io,u))return -1;s->delay++;s->latch=0;break;
        case 4:
            q=changed(c,io,u);if(q<0)return -1;
            if(q){
                if(s->selection==-1)phase(s,7,0);
                else{
                    c->recipient=s->selection;q=io(u,c,DW4_DISK_RECIPIENT_QUANTITY,0);if(q<0)return -1;
                    if(q<9){DO(DW4_DISK_CURSOR_OPEN,0);s->delay++;s->latch=0;}
                    else{s->delay=10;s->latch=0;}
                }
            }break;
        case 5:
            q=io(u,c,DW4_DISK_QUANTITY_SELECTOR,0);if(q<0)return -1;c->limit=q;
            if(snapshot(c,io,u))return -1;
            s->delay++;s->latch=0;break;
        case 6:
            DO(DW4_DISK_QUANTITY_TEXT,c->limit-s->selection);s->delay++;s->latch=s->selection;
            /* fall through */
        case 7:
            q=changed(c,io,u);if(q<0)return -1;
            if(!q){if(s->selection!=-1 && s->selection!=s->latch){s->delay=6;s->latch=0;}}
            else if(s->selection==-1){DO(DW4_DISK_QUANTITY_TEXT,0);DO(DW4_DISK_CURSOR_CLOSE,0);s->delay=3;s->latch=0;}
            else{DO(DW4_DISK_TRANSFER,0);DO(DW4_DISK_POPUP,132);if(snapshot(c,io,u))return -1;s->delay++;s->latch=0;}
            break;
        case 8:
            q=changed(c,io,u);if(q<0)return -1;
            if(q){DO(DW4_DISK_ACK_CLEAR,0);DO(DW4_DISK_QUANTITY_TEXT,0);DO(DW4_DISK_CURSOR_CLOSE,0);phase(s,7,0);}break;
        case 10:
            DO(DW4_DISK_POPUP,143);if(snapshot(c,io,u))return -1;s->delay++;s->latch=0;
            /* fall through */
        case 11:
            q=changed(c,io,u);if(q<0)return -1;
            if(q){DO(DW4_DISK_QUANTITY_TEXT,0);DO(DW4_DISK_CURSOR_CLOSE,0);s->delay=3;s->latch=0;}break;
        default:break;
        }break;
    case 7:
        if(s->delay!=1){if(s->delay)return 0;DO(DW4_DISK_RETIRE_GIVE,0);s->delay++;s->latch=0;}
        state(s,0);phase(s,1,0);break;
    default:break;
    }
    return 0;
}
#undef DO
