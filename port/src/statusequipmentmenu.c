#include "menurecord.h"
#include "dw4/statusequipmentmenu.h"
#include "dw4/statusui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct equipment {dw4_statusgear_context c;dw4_statussubmenu *state; /* borrowed only during update */dw4_menu_window *root,*resources;int failed;char error[256];};
static int empty(void *u,dw4_statusview_io io,void *user){(void)u;(void)io;(void)user;return 0;}
static int create(struct equipment *e,const char *key,int call)
{
    dw4_statusview_context view=e->c.view;view.parent=NULL;view.parent_window=e->root;view.callno=call;dw4_menu_window *w=NULL;
    if(!key)w=dw4_statusui_selector_window(&view,e->root,DW4_STATUS_SELECT01,call,3,e->state->window.selection<0?0:e->state->window.selection,-83,172,NULL);
    else if(!strcmp(key,"EQUIP_TITLE"))w=dw4_statusview_window_open(DW4_STATUS_TITLE04,&view);
    else if(!strcmp(key,"BAND"))w=dw4_statusview_window_open(DW4_STATUS_TITLE02,&view);
    else {
        int kind=!strcmp(key,"POWER")?0:!strcmp(key,"MAIN")?1:!strcmp(key,"SUB")?2:-1;
        dw4_statusgear_context c=e->c;c.view=view;if(kind>=0)w=dw4_statusgear_window_open(&c,kind,0);
    }
    if(!w)return -1;
    if(dw4_menu_window_add(e->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int io(void *u,dw4_statussubmenu *s,int op,const char *name,const char *key,int32_t value)
{
    struct equipment *e=u;(void)s;
    switch(op){
    case DW4_SUBMENU_CREATE:return create(e,key,value);
    case DW4_SUBMENU_COUNT:return dw4_menu_window_count(e->root)>INT32_MAX?-1:(int)dw4_menu_window_count(e->root);
    case DW4_SUBMENU_MODEL:
        return !strncmp(key,"ISSEQNAME/",10)?dw4_statusui_call(&e->c.view,1,"MODELCTRL",name,0,"ISSEQNAME",key+10,e->error,sizeof e->error):-1;
    case DW4_SUBMENU_SCRIPT:return dw4_statusui_emit(e->resources,DW4_VIEW_SCRIPT,NULL,name,NULL,NULL,value);
    case DW4_SUBMENU_CLOSE_MODELS:case DW4_SUBMENU_CLEAR_TEXT:return 0;
    case DW4_SUBMENU_CLOSE_CHILDREN:
        for(size_t i=0;i<dw4_menu_window_count(e->root);i++)if(dw4_menu_window_data(e->root->children[i])->_st0<2)dw4_menu_window_remove(e->root->children[i]);
        return dw4_statusui_close(e->resources,e->error,sizeof e->error);
    case DW4_SUBMENU_FINISHED:return !e->resources && !dw4_menu_window_count(e->root);
    default:return -1;
    }
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct equipment *e=w->user;dw4_statussubmenu projection=menu_submenu_read(w,DW4_STATUS_EQUIP);e->state=&projection;dw4_statusctrl *s=&e->state->window;
    if(e->failed){snprintf(error,cap,"STATUS equipment menu failed; scene reset required");e->state=NULL;return -1;}
    int rc=dw4_statusui_drain(&e->resources,e->error,sizeof e->error);
    if(!rc && !e->resources && dw4_menu_window_data(w)->_st0==0)rc=dw4_statusui_open(&e->c.view,empty,e,&e->resources,e->error,sizeof e->error);
    if(!rc){
        rc=dw4_statussubmenu_tick(e->state,DW4_STATUS_EQUIP,io,e);
    }
    if(rc){e->failed=1;snprintf(error,cap,"STATUS equipment menu %d/%d/%d: %.150s",s->state,s->sub,s->delay,e->error[0]?e->error:"required child/view failed");}
    menu_submenu_write(w,DW4_STATUS_EQUIP,&projection);e->state=NULL;return rc;
}
static void release(void *u){struct equipment *e=u;dw4_menu_window_close(e->resources);free(e);}
dw4_menu_window *dw4_statusequipmentmenu_window_open(const dw4_statusgear_context *c)
{return dw4_statusequipmentmenu_window_open_entry(c,0);}
dw4_menu_window *dw4_statusequipmentmenu_window_open_entry(const dw4_statusgear_context *c,int entry)
{
    if(entry<0 || entry>1 || !c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || !c->stats || !c->input || !c->appearance || c->view.player<0 || c->view.player>3)return NULL;
    struct equipment *e=calloc(1,sizeof *e);if(!e)return NULL;e->c=*c;
    e->root=dw4_menu_window_open_class("beNDMWStatusCtrlEquip",update,e,release);if(!e->root){free(e);return NULL;}
    dw4_statussubmenu initial={.mode=entry,.window={.active=1,.selection=-1}};
    menu_submenu_write(e->root,DW4_STATUS_EQUIP,&initial);dw4_menu_window_data(e->root)->_playerNo=c->view.player;return e->root;
}
int dw4_statusequipmentmenu_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statussubmenu dw4_statusequipmentmenu_window_state(const dw4_menu_window *w)
{return dw4_statusequipmentmenu_window_is(w)?menu_submenu_read(w,DW4_STATUS_EQUIP):(dw4_statussubmenu){0};}
