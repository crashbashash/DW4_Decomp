#include "dw4/statusmenu.h"
#include "dw4/statusequipmentmenu.h"
#include "dw4/statusfolder.h"
#include "dw4/statusskill.h"
#include "dw4/statusui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct menu {dw4_statusmenu_context c;dw4_menu_window *root,*resources;int failed;char error[256];};
static int resources(void *u,dw4_statusview_io io,void *user)
{(void)u;(void)io;(void)user;return 0;}
static dw4_statusview_context view(struct menu *m)
{
    dw4_statusview_context c=m->c.gear.view;c.parent=NULL;c.parent_window=m->root;c.callno=0;
    c.refresh=dw4_statusstats_refresh;c.user=m->c.gear.stats;return c;
}
static int create(struct menu *m,int kind)
{
    dw4_statusview_context c=view(m);dw4_menu_window *w=NULL;
    if(kind>=DW4_STATUS_TITLE00 && kind<=DW4_STATUS_TITLE04)w=dw4_statusview_window_open(kind,&c);
    else if(kind==DW4_STATUS_SELECT00){c.selected=DW4_ARENA_OBJ(m->root->arena,beNDMWStatusCtrl00,m->root->object)->_statusMenu;w=dw4_statusview_window_open(kind,&c);}
    else if(kind==DW4_STATUS_EQUIP){dw4_statusgear_context gear=m->c.gear;gear.view=c;w=dw4_statusequipmentmenu_window_open(&gear);}
    else if(kind==DW4_STATUS_FOLDER){
        dw4_statusfolder_context f={.view=c,.databases=m->c.gear.databases,.dialogue=m->c.dialogue,.input=m->c.gear.input,.user=m->c.gear.user};
        w=dw4_statusfolder_window_open(&f);
    }else if(kind==DW4_STATUS_SKILL){
        dw4_statusskill_context s={.view=c,.databases=m->c.gear.databases,.input=m->c.gear.input,.user=m->c.gear.user};w=dw4_statusskill_window_open(&s);
    }
    if(!w)return -1;
    if(dw4_menu_window_add(m->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int io(void *u,int op,const char *name,const char *key,int32_t value)
{
    struct menu *m=u;dw4_statusview_context c=view(m);
    switch(op){
    case DW4_STATUS_CREATE:return create(m,value);
    case DW4_STATUS_COUNT:return dw4_menu_window_count(m->root)>INT32_MAX?-1:(int)dw4_menu_window_count(m->root);
    case DW4_STATUS_MODEL:
        if(!strncmp(key,"ISSEQNAME/",10))return dw4_statusui_call(&c,1,"MODELCTRL",name,0,"ISSEQNAME",key+10,m->error,sizeof m->error);
        return !strcmp(key,"ISRUN")?dw4_statusui_call(&c,1,"MODELCTRL",name,0,key,NULL,m->error,sizeof m->error):-1;
    case DW4_STATUS_LAYER:{char encoded[64];snprintf(encoded,sizeof encoded,"%s/%s",name,key);
        return dw4_statusui_call(&c,0,"LAYERCTL",NULL,-1,"SWITCH",encoded,m->error,sizeof m->error);}
    case DW4_STATUS_TEXT:return dw4_statusui_emit(m->resources,DW4_VIEW_TEXT,name,"font000","LEFT",key,0);
    case DW4_STATUS_CLOSE_CHILDREN:
        for(size_t i=value?1:0;i<dw4_menu_window_count(m->root);i++)if(dw4_menu_window_data(m->root->children[i])->_st0<2)dw4_menu_window_remove(m->root->children[i]);
        return 0;
    case DW4_STATUS_CLOSE_MODELS:return dw4_statusui_close(m->resources,m->error,sizeof m->error);
    case DW4_STATUS_CLEAR_TEXT:return 0;
    case DW4_STATUS_FINISHED:return !m->resources && !dw4_menu_window_count(m->root);
    default:return -1;
    }
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct menu *m=w->user;dw4_statusctrl value,*s=&value;dw4_statusctrl_load(w,s);
    if(m->failed){snprintf(error,cap,"STATUS root failed; scene reset required");return -1;}
    int rc=dw4_statusui_drain(&m->resources,m->error,sizeof m->error);
    if(!rc && !m->resources && dw4_menu_window_data(w)->_st0==0)rc=dw4_statusui_open(&m->c.gear.view,resources,m,&m->resources,m->error,sizeof m->error);
    if(!rc){rc=dw4_statusctrl_tick(s,io,m);dw4_statusctrl_store(w,s);}
    if(rc){m->failed=1;snprintf(error,cap,"STATUS root %d/%d/%d: %.150s",s->state,s->sub,s->delay,m->error[0]?m->error:"required child/view failed");return -1;}return 0;
}
static void release(void *u){struct menu *m=u;dw4_menu_window_close(m->resources);free(m);}
dw4_menu_window *dw4_statusmenu_window_open(const dw4_statusmenu_context *c)
{
    if(!c || !c->gear.view.sd || !c->gear.view.engine || !c->gear.view.players || !c->gear.databases || !c->dialogue || !c->gear.stats ||
       c->gear.stats->players!=c->gear.view.players || !c->gear.input || !c->gear.appearance || c->gear.view.player<0 || c->gear.view.player>3)return NULL;
    struct menu *m=calloc(1,sizeof *m);if(!m)return NULL;m->c=*c;
    m->root=dw4_menu_window_open_class("beNDMWStatusCtrl00",update,m,release);if(!m->root){free(m);return NULL;}
    dw4_menu_window_data(m->root)->_retCode=-1;dw4_menu_window_data(m->root)->_playerNo=c->gear.view.player;return m->root;
}
const beNDMWStatusCtrl00 *dw4_statusmenu_window_state(const dw4_menu_window *w)
{return w && w->update==update?DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrl00,w->object):NULL;}
