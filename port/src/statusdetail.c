#include "menurecord.h"
#include "dw4/statusdetail.h"
#include "dw4/statusdetailctrl.h"
#include "dw4/statusui.h"
#include "dw4/playerstats.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct detail {
    dw4_statusdetail_context c;
    dw4_menu_window *root,*resources;

    int retained,failed;
    char error[256];
};
static beNDMWStatusSubMenu *record(const struct detail *d)
{return DW4_ARENA_OBJ(d->root->arena,beNDMWStatusSubMenu,d->root->object);}
static int command(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static int setup(void *u,dw4_statusview_io io,void *user)
{
    struct detail *d=u;char seq[64];snprintf(seq,sizeof seq,"SQ_OPEN%02d/V<-121,128,0>",record(d)->_selectDevice%12);
    if(command(io,user,DW4_VIEW_MODEL,NULL,"i_stcursor04",seq,"SQ_CLOSE",0) ||
       command(io,user,DW4_VIEW_MODEL,NULL,"i_stmenu02","SQ_3LINEOPEN","SQ_CLOSE",0))return -1;
    for(unsigned i=0;i<3;i++){
        char name[16];snprintf(name,sizeof name,"font%03u",i);
        if(command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT26",name,NULL,NULL,0))return -1;
    }
    return command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,67);
}
static int add(struct detail *d,int kind,int call,int rows,int selected,float x,float y)
{
    dw4_menu_window *w=dw4_statusui_selector_window(&d->c.view,d->root,kind,call,rows,selected,x,y,NULL);
    if(!w)return -1;
    if(dw4_menu_window_add(d->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
struct popup {int call;};
static int popup_setup(void *u,dw4_statusview_io io,void *user)
{
    struct popup *p=u;
    return command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font000",NULL,NULL,0) ||
           command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,p->call)?-1:0;
}
static int popup(struct detail *d,int call)
{
    dw4_menu_window *w=dw4_statusui_selector_window(&d->c.view,d->root,DW4_STATUS_SHOPSELECT00,0,1,0,0,0,NULL);
    struct popup p={call};if(!w)return -1;
    if(dw4_statusview_window_prepare(w,popup_setup,&p) || dw4_menu_window_add(d->root,w)){
        dw4_menu_window_close(w);return -1;
    }
    return 0;
}
static int item(struct detail *d,dw4_item_record *out)
{
    dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",d->c.view.player);size_t n;
    const dw4_item_record *v=dw4_property_items(f,"DEVICEFOLDER",&n);
    if(dw4_property_item_count(f,"DEVICEFOLDER",&n) || record(d)->_selectDevice<0 || (size_t)record(d)->_selectDevice>=n || n>36){
        snprintf(d->error,sizeof d->error,"STATUS detail selected identity unavailable");return -1;}
    *out=v[record(d)->_selectDevice];return 0;
}
static int recipients(struct detail *d)
{
    int32_t players[3],counts[3];int nrecipient=0;
    for(int player=0;player<4;player++){
        dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",player);int32_t use;
        if(dw4_property_number(f,"ISUSE",&use))return -1;
        if(player==d->c.view.player || !(uint8_t)use)continue;
        size_t n;if(dw4_property_item_count(f,"DEVICEFOLDER",&n) || n>36)return -1;
        players[nrecipient]=player;counts[nrecipient++]=(int32_t)n;
    }
    return menu_int_set(d->root,&record(d)->_playerNoList,players,nrecipient) ||
        menu_int_set(d->root,&record(d)->_playerDeviceCnt,counts,nrecipient)?-1:0;
}
static int give_setup(struct detail *d)
{
    char seq[32];snprintf(seq,sizeof seq,"SQ_%zuCHIPOPEN",(size_t)menu_int_count(d->root,record(d)->_playerNoList));
    /* Names below are pinned to the actual authored sequence strings before
     * caller publication; no host timing estimates or placeholder rows. */
    if(dw4_statusui_emit(d->resources,DW4_VIEW_MODEL,NULL,"i_stmenu02",seq,"SQ_CLOSE",0) ||
       dw4_statusui_emit(d->resources,DW4_VIEW_TRACK_TEXT,"STWINFONT39","font000",NULL,NULL,0) ||
       dw4_statusui_emit(d->resources,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,73))return -1;
    dw4_item_record v;if(item(d,&v))return -1;
    const char *name=dw4_statuscontent_item_string(d->c.databases,&v,"NAME");if(!name)return -1;
    if(dw4_statusui_emit(d->resources,DW4_VIEW_TEXT,"STWINFONT14","font000","LEFT",name,0))return -1;
    float rgb[3];char color[80];dw4_statuscontent_item_color(&v,rgb);snprintf(color,sizeof color,"V<%.9g,%.9g,%.9g>",rgb[0],rgb[1],rgb[2]);
    if(dw4_statusui_emit(d->resources,DW4_VIEW_COLOR,"STWINFONT14","font000","COLOR",color,0))return -1;
    for(size_t i=0;i<(size_t)menu_int_count(d->root,record(d)->_playerNoList);i++){
        dw4_unicode_object value;char font[16];size_t count;
        dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",menu_int_data(d->root,record(d)->_playerNoList)[i]);
        if(dw4_property_unicode_object(f,"PLAYERNAME",0,&value) || !value.present ||
           dw4_property_item_count(f,"DEVICEFOLDER",&count) || count>36)return -1;
        menu_int_data(d->root,record(d)->_playerDeviceCnt)[i]=(int32_t)count;
        snprintf(font,sizeof font,"font%03u",(unsigned)i+1);
        if(dw4_statusui_emit(d->resources,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) ||
           dw4_dialogue_set_unicode(d->c.dialogue,"STWINFONT14",font,value.codes,value.count))return -1;
    }
    return 0;
}
static int detail_io(void *u,dw4_statusdetail_ctrl *c,int op,int32_t value)
{
    struct detail *d=u;
    menu_base_write(d->root,&c->window);record(d)->_receipt=c->recipient;d->retained=c->retained;
    dw4_item_record v;int32_t flag;int result;
    switch(op){
    case DW4_DETAIL_INIT:
        if(item(d,&v) || dw4_statusui_open(&d->c.view,setup,d,&d->resources,d->error,sizeof d->error))return -1;
        return add(d,DW4_STATUS_SELECTE1,0,3,0,115,145);
    case DW4_DETAIL_COUNT:return dw4_menu_window_count(d->root)>INT32_MAX?-1:(int)dw4_menu_window_count(d->root);
    case DW4_DETAIL_CLOSE:
        if(dw4_statusui_close(d->resources,d->error,sizeof d->error))return -1;
        for(size_t i=0;i<dw4_menu_window_count(d->root);i++)if(dw4_menu_window_data(d->root->children[i])->_st0<2)dw4_menu_window_remove(d->root->children[i]);
        return 0;
    case DW4_DETAIL_FINISHED:return !d->resources && !dw4_menu_window_count(d->root);
    case DW4_DETAIL_DEFAULT_COLOR:return dw4_statusui_call(&d->c.view,0,"TEXTCTL",NULL,-1,"DEFAULTCOLOR","STWINFONT14/font000",d->error,sizeof d->error)<0?-1:0;
    case DW4_DETAIL_DISCARD_CHECK:
        if(item(d,&v))return -1;
        if((uint8_t)v.equipped)return 144;
        if(v.kind==0){if(dw4_playerstats_item_bool((void *)d->c.databases,&v,"ISHAKAI",&flag))return -1;if(!(uint8_t)flag)return 145;}
        return 78;
    case DW4_DETAIL_POPUP:return popup(d,value);
    case DW4_DETAIL_CONFIRM:return add(d,DW4_STATUS_SELECTE0,value,2,0,0,0);
    case DW4_DETAIL_REMOVE:return dw4_playertransactions_remove_item(d->c.view.players,d->c.view.player,(size_t)record(d)->_selectDevice,&result) || !result?-1:0;
    case DW4_DETAIL_SORT:return dw4_playertransactions_sort_device(d->c.view.players,d->c.view.player);
    case DW4_DETAIL_GIVE_CHECK:
        if(item(d,&v) || recipients(d))return -1;
        if((uint8_t)v.equipped)return 146;
        if(dw4_playerstats_item_bool((void *)d->c.databases,&v,"ISJYOUDO",&flag))return -1;
        if(!(uint8_t)flag)return 147;
        return (size_t)menu_int_count(d->root,record(d)->_playerNoList)?0:148;
    case DW4_DETAIL_DEVICE_CLOSE:return d->c.device?d->c.device(d->c.device_user,DW4_DETAIL_RETAINED_CLOSE):-1;
    case DW4_DETAIL_DEVICE_FINISHED:return d->c.device?d->c.device(d->c.device_user,DW4_DETAIL_RETAINED_FINISHED):-1;
    case DW4_DETAIL_DEVICE_RELEASE:
        dw4_menu_window_close(d->c.device_window);d->c.device_window=NULL;record(d)->_deviceFolderList=0;return 0;
    case DW4_DETAIL_CURSOR_CLOSE:return dw4_statusui_call(&d->c.view,0,"MODELCTRL","i_stcursor04",0,"SQ_CLOSE",NULL,d->error,sizeof d->error)<0?-1:0;
    case DW4_DETAIL_CLEAR_TEXT:return dw4_statusview_window_clear_text(d->resources);
    case DW4_DETAIL_GIVE_SETUP:return give_setup(d);
    case DW4_DETAIL_RECIPIENT_SELECTOR:return add(d,DW4_STATUS_SELECTE1,0,(int)(size_t)menu_int_count(d->root,record(d)->_playerNoList),record(d)->_receipt,-121,109);
    case DW4_DETAIL_RECIPIENT_COUNT:return record(d)->_receipt>=0 && (size_t)record(d)->_receipt<(size_t)menu_int_count(d->root,record(d)->_playerNoList)?menu_int_data(d->root,record(d)->_playerDeviceCnt)[record(d)->_receipt]:-1;
    case DW4_DETAIL_TRANSFER:
        if(record(d)->_receipt<0 || (size_t)record(d)->_receipt>=(size_t)menu_int_count(d->root,record(d)->_playerNoList))return -1;
        return dw4_playertransactions_give_item(d->c.view.players,d->c.view.player,menu_int_data(d->root,record(d)->_playerNoList)[record(d)->_receipt],(size_t)record(d)->_selectDevice,&result) || !result?-1:0;
    case DW4_DETAIL_CURSOR_OPEN:{char seq[32];snprintf(seq,sizeof seq,"SQ_OPEN%02d",record(d)->_receipt);
        return dw4_statusui_positioned(&d->c.view,"i_stcursor04",0,seq,-121,109,0,d->error,sizeof d->error);}
    default:return -1;
    }
}
static int tick(struct detail *d)
{
    dw4_statusdetail_ctrl c={menu_base_read(d->root),record(d)->_receipt,d->retained};
    int rc=dw4_statusdetailctrl_tick(&c,detail_io,d);
    menu_base_write(d->root,&c.window);record(d)->_receipt=c.recipient;d->retained=c.retained;return rc;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct detail *d=w->user;
    if(d->failed){snprintf(error,cap,"STATUS detail failed; scene reset required");return -1;}
    int rc=dw4_statusui_drain(&d->resources,d->error,sizeof d->error);
    if(!rc)rc=tick(d);
    if(rc){d->failed=1;snprintf(error,cap,"STATUS detail %d/%d/%d: %.150s",dw4_menu_window_data(w)->_st0,dw4_menu_window_data(w)->_st1,dw4_menu_window_data(w)->_st2,d->error[0]?d->error:"required record/view unavailable");}
    return rc;
}
static void release(void *u)
{struct detail *d=u;dw4_menu_window_close(d->resources);dw4_menu_window_close(d->c.device_window);record(d)->_deviceFolderList=0;menu_int_release(d->root,&record(d)->_playerNoList);menu_int_release(d->root,&record(d)->_playerDeviceCnt);free(d);}
dw4_menu_window *dw4_statusdetail_window_open(const dw4_statusdetail_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || !c->dialogue || c->view.player<0 || c->view.player>3 || c->selected<0 || c->selected>=36)return NULL;
    struct detail *d=calloc(1,sizeof(*d));if(!d)return NULL;
    d->c=*c;d->c.device_window=NULL;d->retained=c->device!=NULL;
    d->root=dw4_menu_window_open_class("beNDMWStatusSubMenu",update,d,release);if(!d->root){free(d);return NULL;}
    dw4_statusctrl initial={.active=1,.selection=0};
    menu_base_write(d->root,&initial);dw4_menu_window_data(d->root)->_playerNo=c->view.player;record(d)->_selectDevice=c->selected;
    if(c->device_window){d->c.device_window=dw4_menu_window_retain(c->device_window);
        if(!d->c.device_window){dw4_menu_window_close(d->root);return NULL;}
        record(d)->_deviceFolderList=(int32_t)c->device_window->object.off;
    }return d->root;
}
int dw4_statusdetail_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statusctrl dw4_statusdetail_window_state(const dw4_menu_window *w)
{return dw4_statusdetail_window_is(w)?menu_base_read(w):(dw4_statusctrl){0};}
