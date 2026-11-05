#include "menurecord.h"
#include "arenalist.h"
#include "dw4/statusdisk.h"
#include "dw4/statusdiskctrl.h"
#include "dw4/statusui.h"
#include "dw4/playertransactions.h"
#include <stdlib.h>
#include <stdio.h>
struct disk {
    dw4_statusdisk_context c;dw4_menu_window *root,*main,*give;
    int failed;char error[256];
};
static beNDMWStatusCtrlDisk *record(const struct disk *d)
{return DW4_ARENA_OBJ(d->root->arena,beNDMWStatusCtrlDisk,d->root->object);}
static int recipient_quantity(const struct disk *d,int i)
{
    dw4_arena *a=d->root->arena;int32_t list=record(d)->_diskList;
    if(i<0 || i>=al_count(a,list))return -1;
    const beNDMWItemDisk *v=DW4_ARENA_OBJ(a,beNDMWItemDisk,al_handle(al_words(a,list)[i]));return v?v->_kazu:-1;
}
static void disk_refs_drop(struct disk *d)
{
    dw4_arena *a=d->root->arena;int32_t list=record(d)->_diskList;
    int n=al_count(a,list);int32_t *v=al_words(a,list);
    for(int i=0;i<n;i++)dw4_property_list_release(a,al_handle(v[i]));
    al_drop(a,&record(d)->_diskList);menu_record_release(d->root,&record(d)->_sendDisk);
}
static int disk_refs(struct disk *d)
{
    dw4_arena *a=d->root->arena;int n=menu_int_count(d->root,record(d)->_playerNoList),count=0;
    int32_t held[4]={0},source_record=-1;
    for(int i=0;i<=n;i++){
        int player=i?menu_int_data(d->root,record(d)->_playerNoList)[i-1]:d->c.view.player;
        dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",player);
        dw4_handle list=dw4_property_list_acquire(f,"DISKFOLDER",DW4_PROPERTY_ITEMS);if(!list.off)goto fail;
        igDataList *l=al_list(a,(int32_t)list.off);int32_t *v=al_words(a,(int32_t)list.off);int j=i?0:record(d)->_cursor;
        if(i)for(;j<l->_count;j++)if(DW4_ARENA_OBJ(a,beNDMWItemDisk,al_handle(v[j]))->_recNo==source_record)break;
        if(j<0 || j>=l->_count || !v[j]){dw4_property_list_release(a,list);goto fail;}
        held[i]=v[j];if(dw4_arena_object_addref(a,al_handle(held[i]))<1){held[i]=0;dw4_property_list_release(a,list);goto fail;}
        count++;if(!i)source_record=DW4_ARENA_OBJ(a,beNDMWItemDisk,al_handle(held[0]))->_recNo;
        dw4_property_list_release(a,list);
    }
    int32_t recipients=al_new(a,"beNDMWItemBaseList",4,n,held+1);if(!recipients)goto fail;
    disk_refs_drop(d);record(d)->_sendDisk=held[0];record(d)->_diskList=recipients;return 0;
fail:for(int i=0;i<count;i++)dw4_property_list_release(a,al_handle(held[i]));return -1;
}
static int command(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static const dw4_item_record *items(struct disk *d,int player)
{
    size_t n;const dw4_item_record *v=dw4_property_items(dw4_playerrecords_get(d->c.view.players,"GETPLAYER",player),"DISKFOLDER",&n);
    if(!v || n!=12)return NULL;
    for(size_t i=0;i<n;i++)if(v[i].kind!=4 || v[i].revision<0 || v[i].revision>9)return NULL;
    return v;
}
static int main_setup(void *u,dw4_statusview_io io,void *user)
{
    (void)u;
    if(command(io,user,DW4_VIEW_MODEL,NULL,"i_stfolder","SQ_AWINOFFOPEN","SQ_CLOSE",0) ||
       command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,72))return -1;
    for(unsigned i=0;i<12;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(command(io,user,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) ||
           command(io,user,DW4_VIEW_TEXT,"STWINFONT15",font,"RIGHT"," ",0))return -1;
    }
    return command(io,user,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0);
}
static int action_setup(void *u,dw4_statusview_io io,void *user)
{
    (void)u;
    if(command(io,user,DW4_VIEW_MODEL,NULL,"i_stmenu02","SQ_2LINEOPEN","SQ_CLOSE",0))return -1;
    for(unsigned i=0;i<2;i++){char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(command(io,user,DW4_VIEW_TEXT,"STWINFONT26",font,"LEFT"," ",0))return -1;}
    return 0;
}
static int give_setup(void *u,dw4_statusview_io io,void *user)
{
    struct disk *d=u;char seq[32];snprintf(seq,sizeof seq,"SQ_%dITEMOPEN",menu_int_count(d->root,record(d)->_playerNoList));
    if(command(io,user,DW4_VIEW_MODEL,NULL,"i_stmenu02",seq,"SQ_CLOSE",0))return -1;
    for(unsigned i=0;i<2;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT39",font,NULL,NULL,0))return -1;
    }
    if(command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,74))return -1;
    const dw4_item_record *v=items(d,d->c.view.player);if(!v)return -1;
    const char *name=dw4_statuscontent_item_string(d->c.databases,v+record(d)->_cursor,"NAME");if(!name)return -1;
    if(command(io,user,DW4_VIEW_TEXT,"STWINFONT14","font000","LEFT",name,0))return -1;
    for(int i=0;i<menu_int_count(d->root,record(d)->_playerNoList);i++){
        char font[16],quantity[2]={(char)('0'+recipient_quantity(d,i)),0};dw4_unicode_object name;
        snprintf(font,sizeof font,"font%03d",i+1);
        dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",menu_int_data(d->root,record(d)->_playerNoList)[i]);
        if(dw4_property_unicode_object(f,"PLAYERNAME",0,&name) || !name.present ||
           command(io,user,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) ||
           dw4_dialogue_set_unicode(d->c.dialogue,"STWINFONT14",font,name.codes,name.count) ||
           command(io,user,DW4_VIEW_TEXT,"STWINFONT15",font,"CENTER",quantity,0))return -1;
    }
    char quantity[2]={(char)('0'+v[record(d)->_cursor].revision),0};
    return command(io,user,DW4_VIEW_TEXT,"STWINFONT38","font000","CENTER",quantity,0) ||
           command(io,user,DW4_VIEW_TEXT,"STWINFONT38","font001","CENTER","0",0) ||
           command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font000",NULL,NULL,0)?-1:0;
}
static int add(struct disk *d,int kind,int call,int rows,int selected,float x,float y,const uint8_t *enabled)
{
    dw4_statusview_context c=d->c.view;if(kind==DW4_STATUS_SHOPSELECT52)c.variant=record(d)->_sendMax;
    dw4_menu_window *w=dw4_statusui_selector_window(&c,d->root,kind,call,rows,selected,x,y,enabled);
    if(!w)return -1;
    if(dw4_menu_window_add(d->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int emit(dw4_menu_window *w,int op,const char *g,const char *n,const char *v)
{return dw4_statusui_emit(w,op,g,n,NULL,v,0);}
static int refresh(struct disk *d,int rows)
{
    const dw4_item_record *v=items(d,d->c.view.player);if(!v)return -1;
    if(rows)for(unsigned i=0;i<12;i++){
        char font[16],quantity[2]={(char)('0'+v[i].revision),0};snprintf(font,sizeof font,"font%03u",i);
        const char *name=dw4_statuscontent_item_string(d->c.databases,v+i,"NAME");if(!name)return -1;
        if(emit(d->main,DW4_VIEW_SET_TEXT,"STWINFONT14",font,name) || emit(d->main,DW4_VIEW_SET_TEXT,"STWINFONT15",font,quantity))return -1;
    }
    int selected=dw4_menu_window_data(d->root)->_retCode;
    if(selected==-1)return emit(d->main,DW4_VIEW_SWITCH,"STWINFONT29","font000","DISPOFF");
    if(selected<0 || selected>=10)return -1;
    const char *txt=dw4_statuscontent_item_string(d->c.databases,v+selected,"TXT");
    return !txt || emit(d->main,DW4_VIEW_SET_TEXT,"STWINFONT29","font000",txt) ||
           emit(d->main,DW4_VIEW_SWITCH,"STWINFONT29","font000","DISPON")?-1:0;
}
static int selector_setup(void *u,dw4_statusview_io io,void *user)
{
    int call=*(int *)u;
    return command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT29",call==43?"font100":"font000",NULL,NULL,0) ||
           command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,call)?-1:0;
}
static int prepared_selector(struct disk *d,int rows,int selected,float x,float y,
    int (*initialize)(void *,dw4_statusview_io,void *),void *user)
{
    dw4_menu_window *w=dw4_statusui_selector_window(&d->c.view,d->root,DW4_STATUS_SELECTE1,0,rows,selected,x,y,NULL);
    if(!w)return -1;
    if(dw4_statusview_window_prepare(w,initialize,user) || dw4_menu_window_add(d->root,w)){
        dw4_menu_window_close(w);return -1;
    }
    return 0;
}
static int popup(struct disk *d,int call)
{
    dw4_menu_window *w=dw4_statusui_selector_window(&d->c.view,d->root,DW4_STATUS_SHOPSELECT00,0,1,0,0,0,NULL);
    if(!w)return -1;
    if(dw4_statusview_window_prepare(w,selector_setup,&call) || dw4_menu_window_add(d->root,w)){
        dw4_menu_window_close(w);return -1;
    }
    return 0;
}
/* 41acf0 clears its model/text reference lists immediately at these boundaries.
 * The controller programs keep running independently; releasing the tracker
 * must not query them or issue another close after the next set is published. */
static int retire(struct disk *d,dw4_menu_window **w)
{
    if(dw4_statusui_close(*w,d->error,sizeof d->error))return -1;
    dw4_menu_window_close(*w);*w=NULL;return 0;
}
static int recipients(struct disk *d)
{
    int32_t players[3];int count=0;const dw4_item_record *source=items(d,d->c.view.player);if(!source)return -1;
    for(int i=0;i<4;i++){
        int32_t use;dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",i);
        if(dw4_property_number(f,"ISUSE",&use))return -1;
        if(i==d->c.view.player || !(uint8_t)use)continue;
        const dw4_item_record *v=items(d,i);if(!v)return -1;
        size_t j=0;while(j<12 && v[j].record!=source[record(d)->_cursor].record)j++;if(j==12)return -1;
        players[count++]=i;
    }return menu_int_set(d->root,&record(d)->_playerNoList,players,count) || disk_refs(d)?-1:0;
}
static int disk_io(void *u,dw4_statusdisk_ctrl *c,int op,int32_t value)
{
    struct disk *d=u;
    menu_base_write(d->root,&c->window);record(d)->_cursor=c->selected;record(d)->_receipt=c->recipient;record(d)->_sendMax=c->limit;
    switch(op){
    case DW4_DISK_INIT:
        if(!items(d,d->c.view.player))return -1;
        return dw4_statusui_open(&d->c.view,main_setup,d,&d->main,d->error,sizeof d->error);
    case DW4_DISK_MAIN_SELECTOR:{int call=43;return prepared_selector(d,10,record(d)->_cursor,-121,128,selector_setup,&call);}
    case DW4_DISK_REFRESH:return refresh(d,value);
    case DW4_DISK_ACTION_SELECTOR:{
        char seq[32];snprintf(seq,sizeof seq,"SQ_OPEN%02d",record(d)->_cursor);
        if(dw4_statusui_positioned(&d->c.view,"i_stcursor04",0,seq,-121,128,0,d->error,sizeof d->error))return -1;
        return prepared_selector(d,2,0,115,145,action_setup,d);
    }
    case DW4_DISK_ACTION_TEXT:return dw4_statusui_emit(d->main,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,value);
    case DW4_DISK_REORDER_SELECTOR:{uint8_t enabled[10];for(int i=0;i<10;i++)enabled[i]=i!=record(d)->_cursor;
        return add(d,DW4_STATUS_SELECTE1,0,10,record(d)->_cursor,-121,128,enabled);}
    case DW4_DISK_SWAP:return dw4_playertransactions_swap_disk(d->c.view.players,d->c.view.player,record(d)->_cursor,dw4_menu_window_data(d->root)->_retCode);
    case DW4_DISK_CURSOR_CLOSE:return dw4_statusui_call(&d->c.view,0,"MODELCTRL","i_stcursor04",0,"SQ_CLOSE",NULL,d->error,sizeof d->error)<0?-1:0;
    case DW4_DISK_GIVE_CHECK:{
        const dw4_item_record *v=items(d,d->c.view.player);if(!v)return -1;
        if(v[record(d)->_cursor].revision<1)return 141;
        if(recipients(d))return -1;
        return menu_int_count(d->root,record(d)->_playerNoList)?0:142;
    }
    case DW4_DISK_POPUP:return popup(d,value);
    case DW4_DISK_RETIRE_MAIN:
        if(dw4_statusui_call(&d->c.view,0,"MODELCTRL","i_stcursor04",0,"SQ_CLOSE",NULL,d->error,sizeof d->error)<0)return -1;
        return retire(d,&d->main);
    case DW4_DISK_GIVE_SETUP:return dw4_statusui_open(&d->c.view,give_setup,d,&d->give,d->error,sizeof d->error);
    case DW4_DISK_RECIPIENT_SELECTOR:return add(d,DW4_STATUS_SELECTE1,0,menu_int_count(d->root,record(d)->_playerNoList),record(d)->_receipt,-121,109,NULL);
    case DW4_DISK_RECIPIENT_QUANTITY:return record(d)->_receipt>=0 && record(d)->_receipt<menu_int_count(d->root,record(d)->_playerNoList)?recipient_quantity(d,record(d)->_receipt):-1;
    case DW4_DISK_CURSOR_OPEN:{char seq[32];snprintf(seq,sizeof seq,"SQ_OPEN%02d",record(d)->_receipt);
        return dw4_statusui_positioned(&d->c.view,"i_stcursor04",0,seq,-121,109,0,d->error,sizeof d->error);}
    case DW4_DISK_QUANTITY_SELECTOR:{
        const dw4_item_record *v=items(d,d->c.view.player);if(!v || record(d)->_receipt<0 || record(d)->_receipt>=menu_int_count(d->root,record(d)->_playerNoList))return -1;
        record(d)->_sendMax=v[record(d)->_cursor].revision;if(9-recipient_quantity(d,record(d)->_receipt)<record(d)->_sendMax)record(d)->_sendMax=9-recipient_quantity(d,record(d)->_receipt);
        return add(d,DW4_STATUS_SHOPSELECT52,0,record(d)->_sendMax,record(d)->_sendMax-1,68,-3,NULL)?-1:record(d)->_sendMax;
    }
    case DW4_DISK_QUANTITY_TEXT:{if(value<0 || value>9)return -1;char quantity[2]={(char)('0'+value),0};return emit(d->give,DW4_VIEW_SET_TEXT,"STWINFONT38","font001",quantity);}
    case DW4_DISK_TRANSFER:{int result;
        if(record(d)->_receipt<0 || record(d)->_receipt>=menu_int_count(d->root,record(d)->_playerNoList))return -1;
        return dw4_playertransactions_give_disk(d->c.view.players,d->c.view.player,menu_int_data(d->root,record(d)->_playerNoList)[record(d)->_receipt],record(d)->_cursor,record(d)->_sendMax-dw4_menu_window_data(d->root)->_retCode,&result) || !result?-1:0;
    }
    case DW4_DISK_ACK_CLEAR:return emit(d->give,DW4_VIEW_SWITCH,"STWINFONT29","font100","DISPOFF");
    case DW4_DISK_RETIRE_GIVE:return retire(d,&d->give);
    case DW4_DISK_CLOSE:
        if(dw4_statusui_close(d->main,d->error,sizeof d->error) || dw4_statusui_close(d->give,d->error,sizeof d->error))return -1;
        for(size_t i=0;i<dw4_menu_window_count(d->root);i++)if(dw4_menu_window_data(d->root->children[i])->_st0<2)dw4_menu_window_remove(d->root->children[i]);
        return 0;
    case DW4_DISK_FINISHED:return !d->main && !d->give && !dw4_menu_window_count(d->root);
    case DW4_DISK_COUNT:return dw4_menu_window_count(d->root)>INT32_MAX?-1:(int)dw4_menu_window_count(d->root);
    default:return -1;
    }
}
static int tick(struct disk *d)
{
    dw4_statusdisk_ctrl c={menu_base_read(d->root),record(d)->_cursor,record(d)->_receipt,record(d)->_sendMax};
    int rc=dw4_statusdiskctrl_tick(&c,disk_io,d);
    menu_base_write(d->root,&c.window);record(d)->_cursor=c.selected;record(d)->_receipt=c.recipient;record(d)->_sendMax=c.limit;return rc;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct disk *d=w->user;
    if(d->failed){snprintf(error,cap,"STATUS disk failed; scene reset required");return -1;}
    int rc=dw4_statusui_drain(&d->main,d->error,sizeof d->error) || dw4_statusui_drain(&d->give,d->error,sizeof d->error);
    if(!rc)rc=tick(d);
    if(rc){d->failed=1;snprintf(error,cap,"STATUS disk %d/%d/%d: %.150s",dw4_menu_window_data(w)->_st0,dw4_menu_window_data(w)->_st1,dw4_menu_window_data(w)->_st2,d->error[0]?d->error:"record/view unavailable");return -1;}return 0;
}
static void release(void *u){struct disk *d=u;dw4_menu_window_close(d->main);dw4_menu_window_close(d->give);disk_refs_drop(d);menu_int_release(d->root,&record(d)->_playerNoList);free(d);}
dw4_menu_window *dw4_statusdisk_window_open(const dw4_statusdisk_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || !c->dialogue || c->view.player<0 || c->view.player>3)return NULL;
    struct disk *d=calloc(1,sizeof *d);if(!d)return NULL;d->c=*c;
    d->root=dw4_menu_window_open_class("beNDMWStatusCtrlDisk",update,d,release);if(!d->root){free(d);return NULL;}
    dw4_statusctrl initial={.active=1,.selection=-1};
    menu_base_write(d->root,&initial);dw4_menu_window_data(d->root)->_playerNo=c->view.player;return d->root;
}
int dw4_statusdisk_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statusctrl dw4_statusdisk_window_state(const dw4_menu_window *w)
{return dw4_statusdisk_window_is(w)?menu_base_read(w):(dw4_statusctrl){0};}
