#include "menurecord.h"
#include "arenalist.h"
#include "dw4/statusflag.h"
#include "dw4/statusui.h"
#include <stdio.h>
#include <stdlib.h>
struct flag {
    dw4_statusflag_context c;dw4_statusctrl *state; /* borrowed only during update */
    dw4_menu_window *root,*resources;
    int failed;char error[256];
};
static int setup(void *u,dw4_statusview_io io,void *user)
{
    struct flag *s=u;
    dw4_statusview_command c={DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0};
    if(io(user,&c))return -1;
    c=(dw4_statusview_command){DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,71};if(io(user,&c))return -1;
    for(unsigned i=0;i<12;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        c=(dw4_statusview_command){DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0};if(io(user,&c))return -1;
    }
    for(unsigned i=0;i<2;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        c=(dw4_statusview_command){DW4_VIEW_TEXT,"STWINFONT23",font,"RIGHT"," ",0};if(io(user,&c))return -1;
    }
    c=(dw4_statusview_command){DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0};
    (void)s;return io(user,&c);
}
static int refresh(struct flag *s,int rows)
{
    return dw4_statuscontent_flag(s->c.databases,al_words(s->root->arena,DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlFlag,s->root->object)->_impItems),(size_t)al_count(s->root->arena,DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlFlag,s->root->object)->_impItems),s->state->selection,rows,1,
        dw4_statusview_window_emit,s->resources);
}
static int initialize(struct flag *s)
{
    size_t n;const uint8_t *flags=dw4_property_bytes(dw4_playerrecords_get(s->c.view.players,"GETCOMMON",0),"FLAGFOLDER",&n);
    if(!flags || n!=12)return -1;
    int32_t indices[12];int count=0;for(size_t i=0;i<n;i++)if(flags[i])indices[count++]=(int32_t)i;
    beNDMWStatusCtrlFlag *d=DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlFlag,s->root->object);
    int32_t list=al_new(s->root->arena,"igIntList",4,count,indices);if(!list)return -1;
    al_drop(s->root->arena,&d->_impItems);d->_impItems=list;
    if(dw4_statusui_open(&s->c.view,setup,s,&s->resources,s->error,sizeof s->error))return -1;
    dw4_menu_window *child=dw4_statusui_selector_window(&s->c.view,s->root,DW4_STATUS_SELECTE1,0,count?count:1,0,-121,128,NULL);
    if(!child)return -1;
    /* Caller prompt is emitted by the real selector's tracker. */
    if(dw4_menu_window_add(s->root,child)){dw4_menu_window_close(child);return -1;}
    if(dw4_statusui_emit(s->resources,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
       dw4_statusui_emit(s->resources,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,135) ||
       dw4_statusui_emit(s->resources,DW4_VIEW_MODEL,NULL,"i_stfolder","SQ_FLAGOPEN","SQ_CLOSE",0))return -1;
    s->state->previous_count=(int)dw4_menu_window_count(s->root);s->state->selection=0;return 0;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct flag *s=w->user;dw4_statusctrl projection=menu_base_read(w);s->state=&projection;dw4_statusctrl *c=&projection;int rc=0;
    if(s->failed){snprintf(error,cap,"STATUS flag failed; scene reset required");s->state=NULL;return -1;}

    if(dw4_statusui_drain(&s->resources,s->error,sizeof s->error))rc=-1;
    if(!rc && c->state==0){rc=initialize(s);if(!rc){c->state=1;c->sub=c->delay=c->latch=0;}}
    if(!rc && c->state==1){
        if(!c->sub){rc=refresh(s,1);if(!rc){c->sub=1;c->delay=c->latch=0;}}
        if(!rc && (int)dw4_menu_window_count(w)!=c->previous_count){c->state=2;c->sub=c->delay=c->latch=0;}
        else if(!rc && c->selection!=-1 && c->selection!=c->delay){rc=refresh(s,0);if(!rc){c->delay=c->selection;c->latch=0;}}
    }else if(!rc && c->state==2){
        rc=dw4_statusui_close(s->resources,s->error,sizeof s->error);
        for(size_t i=0;i<dw4_menu_window_count(w);i++)if(dw4_menu_window_data(w->children[i])->_st0<2)dw4_menu_window_remove(w->children[i]);
        if(!rc){c->state=3;c->sub=c->delay=c->latch=0;}
    }else if(!rc && c->state==3 && !s->resources && !dw4_menu_window_count(w))c->active=0;

    if(rc){s->failed=1;snprintf(error,cap,"STATUS flag: %.200s",s->error[0]?s->error:"record/view operation failed");}menu_base_write(w,&projection);s->state=NULL;return rc;
}
static void release(void *u){struct flag *s=u;dw4_menu_window_close(s->resources);al_drop(s->root->arena,&DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlFlag,s->root->object)->_impItems);free(s);}
dw4_menu_window *dw4_statusflag_window_open(const dw4_statusflag_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || c->view.player<0 || c->view.player>3)return NULL;
    struct flag *s=calloc(1,sizeof *s);if(!s)return NULL;
    s->c=*c;s->root=dw4_menu_window_open_class("beNDMWStatusCtrlFlag",update,s,release);
    if(!s->root){free(s);return NULL;}
    dw4_statusctrl initial={.active=1,.selection=-1};
    menu_base_write(s->root,&initial);dw4_menu_window_data(s->root)->_playerNo=c->view.player;return s->root;
}
int dw4_statusflag_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statusctrl dw4_statusflag_window_state(const dw4_menu_window *w)
{return dw4_statusflag_window_is(w)?menu_base_read(w):(dw4_statusctrl){0};}
