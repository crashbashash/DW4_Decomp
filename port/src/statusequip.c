#include "menurecord.h"
/* Retail 40f720, 411180 and Power/Main/Sub transaction virtual methods. */
#include "dw4/statusequip.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static void state(dw4_statusctrl *s,int n){s->state=n;s->sub=s->delay=s->latch=0;}
static void sub(dw4_statusctrl *s,int n){s->sub=n;s->delay=s->latch=0;}
static void delay(dw4_statusctrl *s,int n){s->delay=n;s->latch=0;}
#define Q(op,v) io(u,c,op,v)
#define DO(op,v) do{if(Q(op,v)<0)return -1;}while(0)
#define V(n,v) DO(DW4_EQUIP_VIRTUAL+n,v)
static int count(dw4_statusequip *c,dw4_equip_io io,void *u)
{int q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;c->window.previous_count=q;return 0;}
static void restart(dw4_statusctrl *s){state(s,0);sub(s,1);}
int dw4_statusequip_tick(dw4_statusequip *c,dw4_equip_io io,void *u)
{
    if(!c || !io)return -1;
    dw4_statusctrl *s=&c->window;int q;
    if(s->state==3){q=Q(DW4_EQUIP_FINISHED,0);if(q<0)return -1;if(q)s->active=0;return 0;}
    if(s->state==2){DO(DW4_EQUIP_CLOSE_MODELS,0);DO(DW4_EQUIP_CLEAR_TEXT,0);DO(DW4_EQUIP_CLOSE_CHILDREN,0);state(s,3);return 0;}
    if(s->state==0){
        DO(DW4_EQUIP_PREPARE,0);
        if(!s->sub){V(23,1);DO(DW4_EQUIP_BLANK,0);}else DO(DW4_EQUIP_CURSOR,-1);
        DO(DW4_EQUIP_SELECTOR,0);if(count(c,io,u))return -1;state(s,1);return 0;
    }
    if(s->state!=1)return 0;
    if(s->sub==0){
        if(s->delay!=2){if(s->delay==0){V(24,0);delay(s,1);}else if(s->delay!=1)return 0;
            V(26,0);delay(s,s->delay+1);s->latch=s->selection;}
        q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
        if(q==s->previous_count){if(s->selection!=-1 && s->latch!=s->selection)delay(s,1);}
        else if(s->selection==-1)state(s,2);
        else {V(25,0);c->slot=s->selection;DO(DW4_EQUIP_CURSOR,s->selection);}
    }else if(s->sub==1){
        if(s->delay!=1){if(s->delay!=0)return 0;V(27,0);if(count(c,io,u))return -1;delay(s,1);}
        q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
        if(q==s->previous_count){if(s->selection!=-1 && s->latch!=s->selection){
            if(s->selection==2){V(32,-1);}else DO(DW4_EQUIP_PREVIEW_OFF,0);s->latch=s->selection;}}
        else {DO(DW4_EQUIP_PREVIEW_OFF,0);DO(DW4_EQUIP_COLORS,3);
            if(s->selection==-1)restart(s);else V(28,0);}
    }else if(s->sub==2){
        switch(s->delay){
        case 0:V(33,0);if(count(c,io,u))return -1;delay(s,1);break;
        case 1:V(34,0);delay(s,2);s->latch=s->selection; /* fall through */
        case 2:
            q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
            if(q==s->previous_count){if(s->selection!=-1 && s->selection!=s->latch)delay(s,1);}
            else if(s->selection==-1){c->pocket=0;restart(s);}
            else {c->pocket=s->selection;delay(s,3);}break;
        case 3:V(35,0);if(count(c,io,u))return -1;delay(s,4);break;
        case 4:DO(DW4_EQUIP_SCRIPT,127);delay(s,5);s->latch=999;break;
        case 5:
            q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
            if(q==s->previous_count){if(s->selection!=-1 && s->selection!=s->latch){
                if(s->selection==1){V(39,-1);}else DO(DW4_EQUIP_PREVIEW_OFF,0);s->latch=s->selection;}}
            else {DO(DW4_EQUIP_PREVIEW_OFF,0);DO(DW4_EQUIP_COLORS,1);
                if(s->selection==1){s->selection=-1;V(37,0);s->selection=c->pocket;V(24,0);DO(DW4_EQUIP_REFRESH,0);}
                else if(!s->selection){delay(s,6);V(23,0);DO(DW4_EQUIP_CURSOR,-1);return 0;}
                sub(s,2);}break;
        case 6:V(36,0);if(count(c,io,u))return -1;delay(s,7);s->latch=999; /* fall through */
        case 7:
            q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
            if(q==s->previous_count){V(39,0);}
            else {DO(DW4_EQUIP_PREVIEW_OFF,0);if(s->selection!=-1){V(37,0);DO(DW4_EQUIP_REFRESH,0);}
                V(23,1);DO(DW4_EQUIP_BLANK,0);delay(s,8);}break;
        case 8:V(24,0);DO(DW4_EQUIP_CURSOR,c->slot);sub(s,2);break;
        }
    }else if(s->sub==3){
        if(s->delay!=2){if(s->delay==0){DO(DW4_EQUIP_SELECTOR,1);if(count(c,io,u))return -1;delay(s,1);return 0;}
            if(s->delay!=1)return 0;
            V(24,0);delay(s,2);s->latch=s->selection;}
        q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
        if(q==s->previous_count){if(s->selection!=-1 && s->selection!=s->latch){DO(DW4_EQUIP_SWAP_PREVIEW,0);delay(s,1);}}
        else {DO(DW4_EQUIP_HIDE,0);DO(DW4_EQUIP_PREVIEW_OFF,0);
            if(s->selection>=0 && s->selection<=2){DO(DW4_EQUIP_SWAP,0);
                if(!s->selection || !c->slot){V(38,0);}
                DO(DW4_EQUIP_REFRESH,0);
                if((!s->selection || !c->slot) && !c->mode){DO(DW4_EQUIP_PLAYER_MODEL,0);}
                V(22,0);}
            /* Retail publishes UPDATE twice after an accepted swap. */
            DO(DW4_EQUIP_REFRESH,1);restart(s);}
    }else if(s->sub==4){
        if(s->delay!=13){
            if(s->delay!=12){
                if(s->delay==11){V(24,0);restart(s);return 0;}
                if(s->delay==10){q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;if(q==s->previous_count)return 0;
                    V(23,1);DO(DW4_EQUIP_BLANK,0);delay(s,11);return 0;}
                if(s->delay==9){V(31,0);DO(DW4_EQUIP_REFRESH,0);delay(s,10);return 0;}
                if(s->delay!=1){if(s->delay!=0)return 0;
                    V(23,0);DO(DW4_EQUIP_CURSOR,-1);V(29,0);if(count(c,io,u))return -1;delay(s,1);s->latch=999;}
                q=Q(DW4_EQUIP_FIND,0);if(q<0)return -1;if(!q)return -1;
                if(s->selection==-1){DO(DW4_EQUIP_PREVIEW_OFF,0);DO(DW4_EQUIP_SELECTOR_CLOSE,0);delay(s,10);return 0;}
                q=Q(DW4_EQUIP_READY,0);if(q<0)return -1;
                if(q){DO(DW4_EQUIP_PREVIEW_OFF,0);q=Q(DW4_EQUIP_VIRTUAL+30,s->selection);if(q<0)return -1;
                    if(q){delay(s,9);DO(DW4_EQUIP_SELECTOR_CLOSE,0);}else delay(s,12);return 0;}
                V(32,0);return 0;
            }
            DO(DW4_EQUIP_ERROR,0);DO(DW4_EQUIP_SCRIPT,130);if(count(c,io,u))return -1;delay(s,13);s->latch=s->selection;
        }
        q=Q(DW4_EQUIP_COUNT,0);if(q<0)return -1;
        if(q!=s->previous_count){DO(DW4_EQUIP_HIDE,1);q=Q(DW4_EQUIP_FIND,0);if(q<0)return -1;
            if(q){s->selection=s->latch;if(count(c,io,u))return -1;DO(DW4_EQUIP_SELECTOR_RESTART,0);delay(s,1);}}
    }
    return 0;
}
struct owner {dw4_menu_window *w;dw4_equip_io io;void *user;};
static int owned(void *u,dw4_statusequip *c,int op,int32_t v)
{
    struct owner *o=u;
    if(op==DW4_EQUIP_COUNT)return dw4_menu_window_count(o->w)>INT32_MAX?-1:(int)dw4_menu_window_count(o->w);
    if(op==DW4_EQUIP_CLOSE_CHILDREN){for(size_t i=0;i<dw4_menu_window_count(o->w);i++)if(dw4_menu_window_data(o->w->children[i])->_st0<2)dw4_menu_window_remove(o->w->children[i]);return 0;}
    size_t before=dw4_menu_window_count(o->w);int q=o->io(o->user,c,op,v);
    if(q>=0 && (op==DW4_EQUIP_SELECTOR || op==DW4_EQUIP_ERROR || op==DW4_EQUIP_VIRTUAL+27 || op==DW4_EQUIP_VIRTUAL+29 || op==DW4_EQUIP_VIRTUAL+33 || op==DW4_EQUIP_VIRTUAL+35 || op==DW4_EQUIP_VIRTUAL+36) && dw4_menu_window_count(o->w)<=before)return -1;
    return op==DW4_EQUIP_FINISHED && q>0 && dw4_menu_window_count(o->w)?0:q;
}
static int update(dw4_menu_window *w,char *e,size_t n)
{
    struct owner *o=w->user;dw4_statusequip projection=menu_equip_read(w);dw4_statusctrl *s=&projection.window;

    int rc=dw4_statusequip_tick(&projection,owned,o);

    if(rc)snprintf(e,n,"STATUS equipment failed at %d/%d/%d",s->state,s->sub,s->delay);
    menu_equip_write(w,&projection);return rc;
}
dw4_menu_window *dw4_statusequip_window_open(int mode,int slots,dw4_equip_io io,void *u)
{
    if(!io || mode<0 || mode>1 || slots<1 || slots>3)return NULL;
    struct owner *o=calloc(1,sizeof(*o));if(!o)return NULL;
    o->io=io;o->user=u;
    o->w=dw4_menu_window_open_class("beNDMWStatusCtrlBaseEquip",update,o,free);if(!o->w){free(o);return NULL;}
    dw4_statusequip initial={.mode=mode,.slots=slots,.window={.active=1,.selection=-1}};
    menu_equip_write(o->w,&initial);return o->w;
}
int dw4_statusequip_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statusequip dw4_statusequip_window_state(const dw4_menu_window *w)
{return dw4_statusequip_window_is(w)?menu_equip_read(w):(dw4_statusequip){0};}
