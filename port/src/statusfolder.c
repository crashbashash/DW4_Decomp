#include "menurecord.h"
#include "dw4/statusfolder.h"
#include "dw4/statusdetail.h"
#include "dw4/statusflag.h"
#include "dw4/statusbit.h"
#include "dw4/statusdisk.h"
#include "dw4/statusui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct folder {dw4_statusfolder_context c;dw4_statussubmenu *state; /* borrowed only during update */dw4_menu_window *root,*resources;int failed;char error[256];};
static int empty(void *u,dw4_statusview_io io,void *user){(void)u;(void)io;(void)user;return 0;}
static dw4_menu_window *device(struct folder *f)
{
    for(size_t i=0;i<dw4_menu_window_count(f->root);i++)if(dw4_statusdevice_window_is(f->root->children[i]))return f->root->children[i];
    return NULL;
}
static int retained_device(void *u,int op)
{
    struct folder *f=u;dw4_menu_window *w=device(f);
    if(op==DW4_DETAIL_RETAINED_FINISHED)return w?0:1;
    if(op!=DW4_DETAIL_RETAINED_CLOSE || !w)return -1;
    dw4_menu_window_remove(w);return 0;
}
static int create(struct folder *f,const char *key,int call)
{
    dw4_statusview_context view=f->c.view;view.parent=NULL;view.parent_window=f->root;view.callno=call;dw4_menu_window *w=NULL;
    if(!key){w=dw4_statusui_selector_window(&view,f->root,DW4_STATUS_SELECT01,call,4,f->state->window.selection<0?0:f->state->window.selection,-83,172,NULL);}
    else if(!strcmp(key,"FOLDER_TITLE"))w=dw4_statusview_window_open(DW4_STATUS_TITLE04,&view);
    else if(!strcmp(key,"DEVICE")){
        dw4_statusdevice_context c={.view=view,.databases=f->c.databases,.input=f->c.input,.user=f->c.user};
        w=dw4_statusdevice_window_open(&c);
    }else if(!strcmp(key,"DEVICE_DETAIL")){
        if(!device(f))return -1;
        dw4_statusdetail_context c={.view=view,.databases=f->c.databases,.dialogue=f->c.dialogue,.selected=call,
            .device=retained_device,.device_user=f,.device_window=device(f)};w=dw4_statusdetail_window_open(&c);
    }else if(!strcmp(key,"FLAG")){
        dw4_statusflag_context c={.view=view,.databases=f->c.databases};w=dw4_statusflag_window_open(&c);
    }else if(!strcmp(key,"DISK")){
        dw4_statusdisk_context c={.view=view,.databases=f->c.databases,.dialogue=f->c.dialogue};w=dw4_statusdisk_window_open(&c);
    }else if(!strcmp(key,"BANK")){
        dw4_statusbit_context c={.view=view,.dialogue=f->c.dialogue,.input=f->c.input,.user=f->c.user};w=dw4_statusbit_window_open(&c);
    }
    if(!w)return -1;
    if(dw4_menu_window_add(f->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int io(void *u,dw4_statussubmenu *state,int op,const char *name,const char *key,int32_t value)
{
    struct folder *f=u;(void)state;
    switch(op){
    case DW4_SUBMENU_CREATE:return create(f,key,value);
    case DW4_SUBMENU_COUNT:return dw4_menu_window_count(f->root)>INT32_MAX?-1:(int)dw4_menu_window_count(f->root);
    case DW4_SUBMENU_SCRIPT:return dw4_statusui_emit(f->resources,DW4_VIEW_SCRIPT,NULL,name,NULL,NULL,value);
    case DW4_SUBMENU_CLEAR_MESSAGE:return dw4_statusui_emit(f->resources,DW4_VIEW_SWITCH,name,key,NULL,"DISPOFF",0);
    case DW4_SUBMENU_FIND_SELECTOR:return device(f)!=NULL;
    case DW4_SUBMENU_SELECTOR_READY:return dw4_statusdevice_window_ready(device(f));
    case DW4_SUBMENU_SELECTOR_RESTART:return dw4_statusdevice_window_restart(device(f));
    case DW4_SUBMENU_SELECTOR_CLOSE:{dw4_menu_window *w=device(f);if(!w)return -1;dw4_menu_window_remove(w);return 0;}
    /* FOLDER owns no models/text itself; its actual title and page children
     * retain those resources. Retiring DEVICE detail closes its own resources. */
    case DW4_SUBMENU_CLOSE_MODELS:case DW4_SUBMENU_RESET_RESOURCES:case DW4_SUBMENU_CLEAR_TEXT:return 0;
    case DW4_SUBMENU_CLOSE_CHILDREN:
        for(size_t i=0;i<dw4_menu_window_count(f->root);i++)if(dw4_menu_window_data(f->root->children[i])->_st0<2)dw4_menu_window_remove(f->root->children[i]);
        return dw4_statusui_close(f->resources,f->error,sizeof f->error);
    case DW4_SUBMENU_FINISHED:return !f->resources && !dw4_menu_window_count(f->root);
    default:return -1;
    }
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct folder *f=w->user;dw4_statussubmenu projection=menu_submenu_read(w,DW4_STATUS_FOLDER);f->state=&projection;dw4_statusctrl *s=&f->state->window;
    if(f->failed){snprintf(error,cap,"STATUS folder failed; scene reset required");f->state=NULL;return -1;}
    int rc=dw4_statusui_drain(&f->resources,f->error,sizeof f->error);
    if(!rc && !f->resources && dw4_menu_window_data(w)->_st0==0)rc=dw4_statusui_open(&f->c.view,empty,f,&f->resources,f->error,sizeof f->error);
    if(!rc){
        rc=dw4_statussubmenu_tick(f->state,DW4_STATUS_FOLDER,io,f);
    }
    if(rc){f->failed=1;snprintf(error,cap,"STATUS folder %d/%d/%d: %.150s",s->state,s->sub,s->delay,f->error[0]?f->error:"required child/view failed");}
    menu_submenu_write(w,DW4_STATUS_FOLDER,&projection);f->state=NULL;return rc;
}
static void release(void *u){struct folder *f=u;dw4_menu_window_close(f->resources);free(f);}
dw4_menu_window *dw4_statusfolder_window_open(const dw4_statusfolder_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || !c->dialogue || !c->input || c->view.player<0 || c->view.player>3)return NULL;
    struct folder *f=calloc(1,sizeof *f);if(!f)return NULL;f->c=*c;
    f->root=dw4_menu_window_open_class("beNDMWStatusCtrlFolder",update,f,release);if(!f->root){free(f);return NULL;}
    dw4_statussubmenu initial={.window={.active=1,.selection=-1}};
    menu_submenu_write(f->root,DW4_STATUS_FOLDER,&initial);dw4_menu_window_data(f->root)->_playerNo=c->view.player;return f->root;
}
int dw4_statusfolder_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statussubmenu dw4_statusfolder_window_state(const dw4_menu_window *w)
{return dw4_statusfolder_window_is(w)?menu_submenu_read(w,DW4_STATUS_FOLDER):(dw4_statussubmenu){0};}
