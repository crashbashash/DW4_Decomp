#include "dw4/statusctrl.h"
#include "dw4/object.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
static int instance(const dw4_menu_window *w,const char *name)
{const dw4_metaobject *m=dw4_metaobject_find(name);return w && m && dw4_arena_object_is(w->arena,w->object,m->vtable);}
void dw4_statusctrl_load(const dw4_menu_window *w,dw4_statusctrl *s)
{
    const beNDMWWindow *o=dw4_menu_window_data(w);*s=(dw4_statusctrl){0};if(!o)return;
    s->active=o->_isRun;s->state=o->_st0;s->sub=o->_st1;s->delay=o->_st2;s->latch=o->_st3;s->selection=o->_retCode;
    if(instance(w,"beNDMWWindowCtrl"))s->previous_count=DW4_ARENA_OBJ(w->arena,beNDMWWindowCtrl,w->object)->_nowProcKazu;
    if(instance(w,"beNDMWStatusCtrl00"))s->last_selection=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrl00,w->object)->_statusMenu;
    else if(instance(w,"beNDMWWindowSelect"))s->last_selection=DW4_ARENA_OBJ(w->arena,beNDMWWindowSelect,w->object)->_startPoint;
}
void dw4_statusctrl_store(dw4_menu_window *w,const dw4_statusctrl *s)
{
    beNDMWWindow *o=dw4_menu_window_data(w);
    o->_isRun=(unsigned char)s->active;o->_st0=s->state;o->_st1=s->sub;o->_st2=s->delay;o->_st3=s->latch;o->_retCode=s->selection;
    if(instance(w,"beNDMWWindowCtrl"))DW4_ARENA_OBJ(w->arena,beNDMWWindowCtrl,w->object)->_nowProcKazu=s->previous_count;
    if(instance(w,"beNDMWStatusCtrl00"))DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrl00,w->object)->_statusMenu=s->last_selection;
    else if(instance(w,"beNDMWWindowSelect"))DW4_ARENA_OBJ(w->arena,beNDMWWindowSelect,w->object)->_startPoint=s->last_selection;
}
static void state(dw4_statusctrl *s,int32_t n)
{s->state=n;s->sub=s->delay=s->latch=0;}
static void sub(dw4_statusctrl *s,int32_t n)
{s->sub=n;s->delay=s->latch=0;}
static void delay(dw4_statusctrl *s,int32_t n)
{s->delay=n;s->latch=0;}
static int layers(dw4_status_io io,void *u,const char *key)
{
    static const char *names[]={"BG01","BG02","BG03","GM01","GM03"};
    for(unsigned i=0;i<5;i++)if(io(u,DW4_STATUS_LAYER,names[i],key,0)<0)return -1;
    return 0;
}
static int close_window(dw4_statusctrl *s,dw4_status_io io,void *u,int children)
{
    if(s->state==2){
        if(io(u,DW4_STATUS_CLOSE_MODELS,NULL,NULL,0)<0 || io(u,DW4_STATUS_CLEAR_TEXT,NULL,NULL,0)<0 ||
           (children && io(u,DW4_STATUS_CLOSE_CHILDREN,NULL,NULL,0)<0))return -1;
        state(s,3);
    }else if(s->state==3){int q=io(u,DW4_STATUS_FINISHED,NULL,NULL,0);if(q<0)return -1;if(q)s->active=0;}
    return 0;
}
int dw4_statusctrl_tick(dw4_statusctrl *s,dw4_status_io io,void *u)
{
    if(!s || !io)return -1;
    int q;
    if(s->state==0){
        if(s->sub==0){if(io(u,DW4_STATUS_CREATE,NULL,NULL,DW4_STATUS_TITLE00)<0)return -1;sub(s,1);}
        else if(s->sub==1){
            q=io(u,DW4_STATUS_MODEL,"i_stback","ISSEQNAME/SQ_OPEN",0);if(q<0)return -1;if((uint8_t)q==1)return 0;
            if(layers(io,u,"DISPOFF"))return -1;
            for(int32_t i=DW4_STATUS_TITLE01;i<=DW4_STATUS_TITLE03;i++)
                if(io(u,DW4_STATUS_CREATE,NULL,NULL,i)<0)return -1;
            s->last_selection=0;sub(s,2);
        }else if(s->sub==2){
            q=io(u,DW4_STATUS_MODEL,"i_messwn","ISSEQNAME/SQ_STOPEN",0);if(q<0)return -1;
            if((uint8_t)q!=1)state(s,1);
        }
    }else if(s->state==1){
        if(s->sub==0){
            if(s->delay==0){
                if(io(u,DW4_STATUS_CREATE,NULL,NULL,DW4_STATUS_SELECT00)<0 ||
                   io(u,DW4_STATUS_TEXT,"STWINFONT29"," ",s->last_selection)<0)return -1;
                q=io(u,DW4_STATUS_COUNT,NULL,NULL,0);if(q<0)return -1;
                s->previous_count=q;delay(s,1);
                /* Retail falls through 40e4b0 and 40e4c0 on creation. */
            }
            if(s->delay==1)delay(s,2);
            if(s->delay==2){
                q=io(u,DW4_STATUS_COUNT,NULL,NULL,0);if(q<0)return -1;
                if(q!=s->previous_count){
                    if(s->selection!=-1)s->last_selection=s->selection;
                    sub(s,s->selection>=0 && s->selection<=2?s->selection+1:4);
                }
            }
        }else if(s->sub>=1 && s->sub<=3){
            if(s->delay==0){
                if(io(u,DW4_STATUS_CREATE,NULL,NULL,DW4_STATUS_EQUIP+s->sub-1)<0)return -1;
                q=io(u,DW4_STATUS_COUNT,NULL,NULL,0);if(q<0)return -1;
                s->previous_count=q;delay(s,1);
            }
            if(s->delay==1){q=io(u,DW4_STATUS_COUNT,NULL,NULL,0);if(q<0)return -1;if(q!=s->previous_count)sub(s,0);}
        }else if(s->sub==4){
            if(s->delay==0){
                if(io(u,DW4_STATUS_CLOSE_CHILDREN,NULL,NULL,1)<0)return -1;
                delay(s,1);
            }else if(s->delay==1){
                q=io(u,DW4_STATUS_MODEL,"i_messwn","ISRUN",0);if(q<0)return -1;
                if((uint8_t)q!=1){if(layers(io,u,"DISPON"))return -1;state(s,2);}
            }
        }
    }else return close_window(s,io,u,1);
    return 0;
}
int dw4_statustitle_tick(dw4_statusctrl *s,dw4_status_io io,void *u)
{
    if(!s || !io)return -1;
    if(s->state==0){
        if(io(u,DW4_STATUS_MODEL,"i_stback","GENERATE/SQ_OPEN",0)<0 ||
           io(u,DW4_STATUS_MODEL,"i_bgclear","GENERATE/SQ_OPEN",0)<0)return -1;
        state(s,1);return 0;
    }
    return close_window(s,io,u,1);
}
int dw4_statusselect_tick(dw4_statusctrl *s,dw4_statusctrl *parent,dw4_status_io io,void *u)
{
    if(!s || !parent || !io)return -1;
    int q;
    if(s->state==0){
        if(io(u,DW4_STATUS_SELECT_INIT,"i_stcursor02","GENERATE",s->last_selection)<0)return -1;
        state(s,1); /* Falls through to GETSELECT/ISEND on the first call. */
    }
    if(s->state==1){
        q=io(u,DW4_STATUS_SELECT_GET,"i_stcursor02","GETSELECT",0);if(q< -1)return -1;parent->selection=q;
        q=io(u,DW4_STATUS_SELECT_END,"i_stcursor02","ISEND",0);if(q<0)return -1;
        if((uint8_t)q)state(s,2);
    }else if(s->state==4){
        q=io(u,DW4_STATUS_SELECT_IS_TOP,"i_stcursor02","ISFO2TOP",0);if(q<0)return -1;
        if(q){
            if(io(u,DW4_STATUS_SELECT_TOP,"i_stcursor02","FO2TOP",0)<0)return -1;
            q=io(u,DW4_STATUS_SELECT_GET,"i_stcursor02","GETSELECT",0);if(q< -1)return -1;parent->selection=q;
        }
        state(s,1);
        return 0;
    }
    /* 4235a4 -> 4235c0 -> 4235e8: completion falls through both close
     * stages in the same update; title/root callbacks branch to their exit. */
    if(s->state==2){
        if(io(u,DW4_STATUS_CLOSE_MODELS,NULL,NULL,0)<0 || io(u,DW4_STATUS_CLEAR_TEXT,NULL,NULL,0)<0)return -1;
        state(s,3);
    }
    if(s->state==3){q=io(u,DW4_STATUS_FINISHED,NULL,NULL,0);if(q<0)return -1;if(q)s->active=0;}
    return 0;
}

struct controller {
    dw4_menu_window *window;
    struct controller *parent;
    dw4_status_io io;void *user;int kind;
};
static dw4_menu_window *open_window(struct controller *,int,dw4_status_io,void *);
static int window_io(void *user,int op,const char *name,const char *key,int32_t value)
{
    struct controller *c=user;dw4_menu_window *w=c->window;
    if(op==DW4_STATUS_COUNT)return dw4_menu_window_count(w)>INT32_MAX?-1:(int)dw4_menu_window_count(w);
    if(op==DW4_STATUS_CREATE && (value==DW4_STATUS_TITLE00 || value==DW4_STATUS_SELECT00)){
        dw4_menu_window *child=open_window(c,value,c->io,c->user);if(!child)return -1;
        if(dw4_menu_window_add(w,child)){dw4_menu_window_close(child);return -1;}return 0;
    }
    if(op==DW4_STATUS_CLOSE_CHILDREN){
        for(size_t i=value?1:0;i<dw4_menu_window_count(w);i++)if(dw4_menu_window_data(w->children[i])->_st0<2)dw4_menu_window_remove(w->children[i]);
        return 0;
    }
    /* Keep model/text tracking per window: backend gets the child kind in
     * value for close/finished, preserving model ownership between siblings. */
    if(op==DW4_STATUS_CLOSE_MODELS || op==DW4_STATUS_CLEAR_TEXT || op==DW4_STATUS_FINISHED)value=c->kind;
    int q=c->io(c->user,op,name,key,value);
    /* The parent reply is visible to the following ISEND/close query. */
    if(op==DW4_STATUS_SELECT_GET && q>=-1 && c->parent)
        dw4_menu_window_data(c->parent->window)->_retCode=q;
    return op==DW4_STATUS_FINISHED && q>0 && dw4_menu_window_count(w)?0:q;
}
static int update_window(dw4_menu_window *w,char *error,size_t cap)
{
    struct controller *c=w->user;dw4_statusctrl value,parent,*s=&value;dw4_statusctrl_load(w,s);
    if(c->parent)dw4_statusctrl_load(c->parent->window,&parent);
    int rc=c->kind==-1?dw4_statusctrl_tick(s,window_io,c):
        c->kind==DW4_STATUS_TITLE00?dw4_statustitle_tick(s,window_io,c):
        dw4_statusselect_tick(s,&parent,window_io,c);
    dw4_statusctrl_store(w,s);
    if(rc)snprintf(error,cap,"STATUS controller %d failed in state %d/%d/%d",c->kind,s->state,s->sub,s->delay);
    return rc;
}
static dw4_menu_window *open_window(struct controller *parent,int kind,dw4_status_io io,void *user)
{
    if(!io)return NULL;
    struct controller *c=calloc(1,sizeof(*c));if(!c)return NULL;
    c->kind=kind;c->parent=parent;c->io=io;c->user=user;
    const char *name=kind==-1?"beNDMWStatusCtrl00":kind==DW4_STATUS_TITLE00?"beNDMWStatusTitle00":"beNDMWStatusSelect00";
    c->window=dw4_menu_window_open_class(name,update_window,c,free);
    if(!c->window){free(c);return NULL;}
    dw4_statusctrl value={.active=1,.selection=-1};
    if(parent){dw4_statusctrl p;dw4_statusctrl_load(parent->window,&p);value.last_selection=p.last_selection;}
    dw4_statusctrl_store(c->window,&value);return c->window;
}
dw4_menu_window *dw4_statustitle_window_open(dw4_status_io io,void *user)
{return open_window(NULL,DW4_STATUS_TITLE00,io,user);}
dw4_menu_window *dw4_statusctrl_window_open(dw4_status_io io,void *user)
{return open_window(NULL,-1,io,user);}
beNDMWStatusCtrl00 *dw4_statusctrl_window_state(dw4_menu_window *w)
{return w && w->update==update_window && ((struct controller *)w->user)->kind==-1?DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrl00,w->object):NULL;}
