/* beNDMWShopCtrl10 update 4270a0..42860c over native selector windows.
 * Field names follow docs/engine/xdata-controller.md: primary state 28 is the
 * window state, 32/36/40 are main/sub/flag, 84 is _xdataMenu, 88 is _parameter and
 * 48 is _retCode (the selector's GETSELECT, published into the arena owner). */
#include "dw4/xdatashop.h"
#include "arenalist.h"
#include "dw4/statusui.h"
#include "dw4/playertransactions.h"
#include "dw4/playerstats.h"
#include "dw4/statuscontent.h"
#include "dw4/statuspage.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct xdata {
    dw4_xdatashop_context c;
    dw4_menu_window *self;
    int32_t quote_remaining;
    char error[256];
};
static beNDMWShopCtrl10 *arena_xdata(const struct xdata *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWShopCtrl10,p->self->object);}

static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static const int32_t prompts[7]={11730,11735,11740,11745,11750,11755,11760};
static const char *const fonts[7]={"font000","font001","font002","font003","font004","font005","font006"};
static void phase(struct xdata *x,int32_t main){arena_xdata(x)->_st1=main;arena_xdata(x)->_st2=0;arena_xdata(x)->_st3=0;}
static void next_sub(struct xdata *x){arena_xdata(x)->_st2++;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static int changed(const struct xdata *x){return dw4_menu_window_count(x->self)!=(size_t)arena_xdata(x)->_nowProcKazu;}
static dw4_property_folder *folder(struct xdata *x)
{return dw4_playerrecords_get(x->c.view.players,"GETPLAYER",x->c.view.player);}
static int fail(struct xdata *x,const char *what)
{snprintf(x->error,sizeof x->error,"XDATA shop: %s",what);return -1;}
/* GAMERAM RECALCPLAYER. explicit_false sends the optional boolean (no equipment). */
static int recalc(struct xdata *x,int explicit_false)
{
    /* The SD fifth argument is a delay when numeric; the optional boolean travels as data. */
    dw4_script_value a[]={str("GAMERAM"),{0},{DW4_SCRIPT_NUMBER,x->c.view.player,NULL,0},str("RECALCPLAYER"),str("FALSE")},r={0};
    if(dw4_scriptservices_call(x->c.view.sd,"sd",a,explicit_false?5:4,&r,x->error,sizeof x->error))return -1;
    return 0;
}
static int restore_hp_mp(struct xdata *x)
{
    dw4_property_folder *f=folder(x);int32_t mhp,mmp;
    if(!f || dw4_property_number(f,"MHP",&mhp) || dw4_property_number(f,"MMP",&mmp) ||
       dw4_property_set_number(f,"HP",mhp) || dw4_property_set_number(f,"MP",mmp))return fail(x,"HP/MP records unavailable");
    return 0;
}
static int script(struct xdata *x,int32_t call)
{
    int rc=dw4_scriptengine_text_event(x->c.view.engine,x->c.view.scope,"txt_shop.lua",call);
    if(rc)snprintf(x->error,sizeof x->error,"txt_shop.lua %d: %.200s",call,dw4_scriptengine_error(x->c.view.engine));
    return rc;
}
static dw4_menu_window *open_child(struct xdata *x,int kind,int32_t call,int rows,int selected)
{
    dw4_menu_window *w=dw4_statusui_selector_window(&x->c.view,x->self,kind,call,rows,selected,0,0,NULL);
    if(!w){fail(x,"selector window could not be opened");return NULL;}
    if(dw4_menu_window_add(x->self,w)){dw4_menu_window_close(w);fail(x,"selector window could not be attached");return NULL;}
    arena_xdata(x)->_nowProcKazu=dw4_menu_window_count(x->self);return w;
}
/* Quote dialog resources the controller issues before the dialog's first update (3f5410). */
static int quote_resources(void *user,dw4_statusview_io io,void *iou)
{
    struct xdata *x=user;char remaining[16];snprintf(remaining,sizeof remaining,"%d",x->quote_remaining);
    dw4_statusview_command text[]={
        {DW4_VIEW_TEXT,"STWINFONT41","font011","RIGHT","+1",0},
        {DW4_VIEW_TEXT,"STWINFONT41","font012","RIGHT",remaining,0}};
    for(unsigned i=0;i<2;i++)if(io(iou,text+i))return -1;
    /* Close pairs: STWINFONT41 fonts 000..003, font011, font012, then STWINFONT29/font002. */
    for(unsigned i=0;i<4;i++){
        dw4_statusview_command c={DW4_VIEW_TRACK_TEXT,"STWINFONT41",fonts[i],NULL,NULL,0};if(io(iou,&c))return -1;
    }
    dw4_statusview_command tail[]={{DW4_VIEW_TRACK_TEXT,"STWINFONT41","font011",NULL,NULL,0},
        {DW4_VIEW_TRACK_TEXT,"STWINFONT41","font012",NULL,NULL,0},
        {DW4_VIEW_TRACK_TEXT,"STWINFONT29","font002",NULL,NULL,0}};
    for(unsigned i=0;i<3;i++)if(io(iou,tail+i))return -1;
    return 0;
}
static int dialog(struct xdata *x,int32_t code,int quote)
{
    dw4_menu_window *w=open_child(x,DW4_STATUS_SHOPSELECT00,code,1,0);if(!w)return -1;
    if(quote && dw4_statusview_window_prepare(w,quote_resources,x))return fail(x,"quote resources could not be published");
    return 0;
}
static int menu_child(struct xdata *x,int32_t code,int rows,int start)
{return open_child(x,DW4_STATUS_XDATAMENU,code,rows,start)?0:-1;}
static int stat_main(struct xdata *x)
{
    switch(arena_xdata(x)->_st2) {
    case 0:
        if(recalc(x,1))return -1;
        if(open_child(x,DW4_STATUS_XDATASTAT,0,7,arena_xdata(x)->_parameter)==NULL)return -1;
        next_sub(x);arena_xdata(x)->_st3=arena_xdata(x)->_parameter;return 0;
    case 1: {
        if(!changed(x)) {
            int32_t selected=arena_xdata(x)->_retCode;
            if(selected!=-1 && selected!=arena_xdata(x)->_st3){if(script(x,1154+selected))return -1;arena_xdata(x)->_st3=selected;}
            return 0;
        }
        /* Reset each cost colour independently (messages are per font). */
        for(unsigned i=0;i<7;i++){
            char name[24];snprintf(name,sizeof name,"STWINFONT14/%s/",fonts[i]);
            if(dw4_statusui_call(&x->c.view,0,"TEXTCTL",NULL,-1,"DEFAULTCOLOR",name,x->error,sizeof x->error)<0)return -1;
        }
        dw4_property_folder *f=folder(x);uint32_t selected=(uint32_t)arena_xdata(x)->_retCode;
        if(selected>=7){phase(x,0);return 0;}
        const char *key;int32_t limit,stat,balance;
        if(!f || dw4_xdata_stat((int32_t)selected,&key,&limit,NULL) || dw4_property_number(f,key,&stat))return fail(x,"stat record unavailable");
        int32_t price=dw4_xdata_price(stat);arena_xdata(x)->_parameter=(int32_t)selected;
        if(dw4_property_number(f,"XDATA",&balance))return fail(x,"XDATA balance unavailable");
        next_sub(x);
        if(stat>=limit){if(dialog(x,0x48a,0))return -1;
            arena_xdata(x)->_st3=0;}
        else if(balance<price){if(dialog(x,0x489,0))return -1;
            arena_xdata(x)->_st3=0;}
        else {
            x->quote_remaining=(int32_t)((uint32_t)balance-(uint32_t)price);
            if(dialog(x,prompts[selected],1))return -1;
            arena_xdata(x)->_st3=1;
        }
        return 0;
    }
    case 2:
        if(!changed(x))return 0;
        if(arena_xdata(x)->_st3==1){if(menu_child(x,0x48b,2,0))return -1;next_sub(x);}
        else phase(x,1);
        return 0;
    case 3: {
        if(!changed(x))return 0;
        if(arena_xdata(x)->_retCode){phase(x,1);return 0;}
        if(dw4_playertransactions_xdata_upgrade(x->c.view.players,x->c.view.player,arena_xdata(x)->_parameter,
               dw4_playerstats_recalculate,(void *)x->c.databases))return fail(x,"upgrade transaction failed");
        /* SUBWND UPDATE refreshes the stat owner for the selected player. */
        if(dw4_statusui_call(&x->c.view,0,"SUBWND",NULL,x->c.view.player,"UPDATE",NULL,x->error,sizeof x->error)<0)return -1;
        if(dialog(x,0x48d,0))return -1;
        next_sub(x);return 0;
    }
    case 4:
        if(!changed(x))return 0;
        if(menu_child(x,0x48e,2,0))return -1;
        next_sub(x);return 0;
    case 5:
        if(changed(x))phase(x,arena_xdata(x)->_retCode?0:1);
        return 0;
    }
    return 0;
}

/* ---- beNDMWShopCtrlXdataChip 43aae0 ---- */
struct chip {
    dw4_xdatashop_context c;
    dw4_menu_window *self,*content;

    size_t index[36];
    dw4_statuspage_input input;
    /* Quote texts handed to the dialog before its first update. */
    char quote_name[256],quote_diff[16],quote_remaining[16];int have_diff;
    char error[256];
};
static beNDMWShopCtrlXdataChip *arena_chip(const struct chip *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWShopCtrlXdataChip,p->self->object);}

static int chip_fail(struct chip *k,const char *what){snprintf(k->error,sizeof k->error,"XDATA chip: %s",what);return -1;}
static int chip_changed(const struct chip *k){return dw4_menu_window_count(k->self)!=(size_t)arena_chip(k)->_nowProcKazu;}
static void chip_phase(struct chip *k,int32_t main){arena_chip(k)->_st1=main;arena_chip(k)->_st2=0;arena_chip(k)->_st3=0;}
static dw4_property_folder *chip_folder(struct chip *k)
{return dw4_playerrecords_get(k->c.view.players,"GETPLAYER",k->c.view.player);}
static size_t chip_count(const struct chip *k)
{return (size_t)al_count(k->self->arena,arena_chip(k)->_itemBaseList);}
static const dw4_item_record *chip_values(const struct chip *k)
{return dw4_item_list_view(k->self->arena,al_handle(arena_chip(k)->_itemBaseList),NULL);}
static int chip_inventory(struct chip *k)
{
    dw4_property_folder *f=chip_folder(k);size_t n;
    const dw4_item_record *items=f?dw4_property_items(f,"DEVICEFOLDER",&n):NULL;
    if(!items || n>36)return chip_fail(k,"DEVICEFOLDER unavailable");
    dw4_handle inventory=dw4_property_list_acquire(f,"DEVICEFOLDER",DW4_PROPERTY_ITEMS);if(!inventory.off)return -1;
    int32_t held[36]={0};size_t count=0;int32_t *ids=al_words(k->self->arena,(int32_t)inventory.off);
    for(size_t i=0;i<n;i++)if(items[i].kind==3){
        if(dw4_arena_object_addref(k->self->arena,al_handle(ids[i]))<1){for(size_t j=0;j<count;j++)dw4_property_list_release(k->self->arena,al_handle(held[j]));dw4_property_list_release(k->self->arena,inventory);return -1;}
        held[count]=ids[i];k->index[count++]=i;
    }
    int32_t list=al_new(k->self->arena,"beNDMWItemBaseList",4,(int)count,held);
    dw4_property_list_release(k->self->arena,inventory);
    if(!list){for(size_t i=0;i<count;i++)dw4_property_list_release(k->self->arena,al_handle(held[i]));return chip_fail(k,"filtered item allocation failed");}
    dw4_property_list_release(k->self->arena,al_handle(arena_chip(k)->_itemBaseList));arena_chip(k)->_itemBaseList=list;return 0;
}
/* 43c720: pages and the row count of the current page (at least one). */
static int chip_rows(struct chip *k)
{
    int32_t count=(int32_t)chip_count(k);arena_chip(k)->_maxPage=count/12+(count%12!=0);
    int32_t remaining=count-arena_chip(k)->_nowPage*12,rows=remaining<12?remaining%12:12;return rows<1?1:rows;
}
static int chip_model_sequence(void *u,const char *model,const char *key)
{
    struct chip *k=u;
    dw4_script_value a[]={str("MODELCTRL"),str(model),{DW4_SCRIPT_NUMBER,0,NULL,0},str(key)},r;
    return dw4_scriptservices_call(k->c.view.sd,"sd",a,4,&r,k->error,sizeof k->error);
}
static int chip_command(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *key,const char *value,int call)
{dw4_statusview_command c={op,g,n,key,value,call};return io(u,&c);}
/* Primary 0's text/close queues, then phase 0 sub 0's model, prompt script and arrows. */
static int chip_setup(void *u,dw4_statusview_io io,void *iou)
{
    struct chip *k=u;
    if(chip_command(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       chip_command(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT35","font000",NULL,NULL,0))return -1;
    for(unsigned i=0;i<12;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) ||
           chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT17",font,"RIGHT"," ",0))return -1;
    }
    if(chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0) ||
       chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font100","LEFT"," ",0) ||
       chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT30","font000","CENTER"," ",0) ||
       chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT30","font001","CENTER"," ",0))return -1;
    if(chip_command(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin","SQ_XDATAITEMOPEN","SQ_CLOSE",0) ||
       chip_command(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1110))return -1;
    /* Arrow presentation: left hidden at (-146,25,0); right selectable only with two pages. */
    return chip_command(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,25,0>","SQ_CLOSE",0) ||
        chip_command(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorright",arena_chip(k)->_maxPage<2?"SQ_HIDE/V<236,25,0>":"SQ_SELECT/V<236,25,0>","SQ_CLOSE",0)?-1:0;
}
static int chip_refresh(struct chip *k,int rows,int description)
{
    if(!k->content)return chip_fail(k,"content window unavailable");
    int rc=dw4_statuscontent_xdata_chip(k->c.databases,chip_values(k),chip_count(k),arena_chip(k)->_nowPage,arena_chip(k)->_maxPage,
        arena_chip(k)->_retCode,rows,description,dw4_statusview_window_emit,k->content);
    if(rc)snprintf(k->error,sizeof k->error,"XDATA chip text refresh failed");
    return rc;
}
static dw4_menu_window *chip_child(struct chip *k,int kind,int32_t call,int rows,int selected,int variant)
{
    dw4_statusview_context c=k->c.view;c.parent=NULL;c.parent_window=k->self;c.callno=call;c.rows=rows;c.selected=selected;
    c.variant=variant;c.position[0]=c.position[1]=c.position[2]=0;c.enabled=NULL;c.selection_initialize=NULL;
    if(kind==DW4_STATUS_SELECTE1){c.position[0]=-121;c.position[1]=128;}
    dw4_menu_window *w=dw4_statusview_window_open(kind,&c);
    if(!w){chip_fail(k,"selector window could not be opened");return NULL;}
    if(dw4_menu_window_add(k->self,w)){dw4_menu_window_close(w);chip_fail(k,"selector window could not be attached");return NULL;}
    arena_chip(k)->_nowProcKazu=dw4_menu_window_count(k->self);return w;
}
static int chip_quote_resources(void *u,dw4_statusview_io io,void *iou)
{
    struct chip *k=u;
    static const char *const blank[]={"font001","font002","font003"};
    if(chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT",k->quote_name,0))return -1;
    for(unsigned i=0;i<3;i++)if(chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT41",blank[i],"LEFT"," ",0))return -1;
    if(chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font002","LEFT"," ",0))return -1;
    if(k->have_diff && chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT41","font011","RIGHT",k->quote_diff,0))return -1;
    return chip_command(io,iou,DW4_VIEW_TEXT,"STWINFONT41","font012","RIGHT",k->quote_remaining,0);
}
static int chip_sd_subwnd(struct chip *k,const char *key)
{return dw4_statusui_call(&k->c.view,0,"SUBWND",NULL,k->c.view.player,key,NULL,k->error,sizeof k->error)<0?-1:0;}
static int chip_preview_visit(void *u,dw4_property_folder *staged)
{
    struct chip *k=u;
    return k->c.preview(k->c.user,staged,k->error,sizeof k->error);
}
static int chip_next_x(struct chip *k,const dw4_item_record *item,int32_t *out)
{return dw4_playerstats_item_attribute((void *)k->c.databases,item,"NEXTX",out)?chip_fail(k,"NEXTX unavailable"):0;}
/* The quote notice: equipped preview, next-level name, first positive attribute and remaining XDATA. */
static int chip_quote(struct chip *k,size_t selected)
{
    static const char *const keys[12]={"TSUYOSA","KASHIKOSA","SEISHIN","SUBAYASA","RES_FIRE","RES_ICE","RES_THUNDER",
        "RES_DARK","CHIMEIRITSU","HPDRAIN","MPDRAIN","CHOHATURITSU"};
    static const int32_t prompts[8]={11765,11769,11773,11777,11781,11785,11789,11793};
    dw4_item_record item=chip_values(k)[selected];
    if(item.equipped && dw4_playertransactions_chip_preview(k->c.view.players,k->c.view.player,k->index[selected],
           dw4_playerstats_recalculate,(void *)k->c.databases,chip_preview_visit,k))return chip_fail(k,"equipped preview failed");
    dw4_item_record next={.kind=3,.record=(int32_t)((uint32_t)item.record+1u)};
    const char *name=dw4_statuscontent_item_string(k->c.databases,&next,"NAME");
    if(!name)return chip_fail(k,"next chip name unavailable");
    snprintf(k->quote_name,sizeof k->quote_name,"%s",name);
    int32_t prompt=0;k->have_diff=0;
    for(unsigned i=0;i<12;i++){
        int32_t value;
        if(dw4_playerstats_item_attribute((void *)k->c.databases,&next,keys[i],&value))return chip_fail(k,"chip attribute unavailable");
        if(value>0){snprintf(k->quote_diff,sizeof k->quote_diff,"%d",value);k->have_diff=1;prompt=prompts[i>=8?7:i];break;}
    }
    int32_t cost,balance;dw4_property_folder *f=chip_folder(k);
    if(chip_next_x(k,&item,&cost) || !f || dw4_property_number(f,"XDATA",&balance))return chip_fail(k,"XDATA balance unavailable");
    snprintf(k->quote_remaining,sizeof k->quote_remaining,"%d",(int32_t)((uint32_t)balance-(uint32_t)cost));
    dw4_menu_window *w=chip_child(k,DW4_STATUS_SHOPSELECT00,prompt,1,0,0);if(!w)return -1;
    return dw4_statusview_window_prepare(w,chip_quote_resources,k)?chip_fail(k,"quote resources could not be published"):0;
}
static int chip_main(struct chip *k)
{
    if(arena_chip(k)->_st1==10 || arena_chip(k)->_st1==11) {
        if(arena_chip(k)->_st2==0){if(!chip_child(k,DW4_STATUS_SHOPSELECT00,arena_chip(k)->_st3,1,0,arena_chip(k)->_st1==10))return -1;arena_chip(k)->_st2++;}
        if(arena_chip(k)->_st2==1 && chip_changed(k)){if(arena_chip(k)->_st1==10)return 1; /* close */ arena_chip(k)->_st1=0;arena_chip(k)->_st2=1;arena_chip(k)->_st3=0;}
        return 0;
    }
    if(arena_chip(k)->_st1==3) {
        size_t idx=(size_t)(arena_chip(k)->_nowPage*12+arena_chip(k)->_cursor);int32_t cost,balance;dw4_property_folder *f=chip_folder(k);
        if(idx>=chip_count(k) || !f || dw4_property_number(f,"XDATA",&balance) || chip_next_x(k,chip_values(k)+idx,&cost))return chip_fail(k,"selected chip unavailable");
        if(cost==-1){chip_phase(k,11);arena_chip(k)->_st3=0x492;}
        else if(balance<cost){chip_phase(k,11);arena_chip(k)->_st3=0x489;}
        else arena_chip(k)->_st1++;
        return 0;
    }
    if(arena_chip(k)->_st1==4) {
        size_t idx=(size_t)(arena_chip(k)->_nowPage*12+arena_chip(k)->_cursor);
        if(idx>=chip_count(k))return chip_fail(k,"selected chip unavailable");
        if(arena_chip(k)->_st2==0){if(chip_quote(k,idx))return -1;arena_chip(k)->_st2=1;return 0;}
        if(arena_chip(k)->_st2==1){
            if(!chip_changed(k))return 0;
            if(!chip_child(k,DW4_STATUS_XDATAMENU,0x493,2,0,0))return -1;
            arena_chip(k)->_st2=2;return 0;
        }
        if(arena_chip(k)->_st2==2 && chip_changed(k)) {
            if(chip_sd_subwnd(k,"OFPREVIEW"))return -1;
            if(!arena_chip(k)->_retCode) {
                if(dw4_playertransactions_chip_upgrade(k->c.view.players,k->c.view.player,k->index[idx],
                       dw4_playerstats_item_attribute,(void *)k->c.databases,dw4_playerstats_recalculate,(void *)k->c.databases))
                    return chip_fail(k,"upgrade transaction failed");
                if(chip_sd_subwnd(k,"UPDATE"))return -1;
            }
            arena_chip(k)->_st1=0;arena_chip(k)->_st2=1;arena_chip(k)->_st3=0; /* restart selection */
        }
        return 0;
    }
    if(arena_chip(k)->_st1==0) {
        if(chip_inventory(k))return -1;
        if(!chip_count(k)){chip_phase(k,10);arena_chip(k)->_st3=0x491;return 0;}
        if((size_t)arena_chip(k)->_nowPage*12>=chip_count(k))arena_chip(k)->_nowPage=0;
        int rows=chip_rows(k);
        if(arena_chip(k)->_st2==0) {
            dw4_statusview_context v=k->c.view;v.initialize=chip_setup;v.user=k;
            if(k->content)return chip_fail(k,"content already open");
            k->content=dw4_statusview_window_open(DW4_STATUS_CONTENT,&v);
            if(!k->content || dw4_menu_window_tick(k->content,k->error,sizeof k->error))return chip_fail(k,"content window failed");
        }
        int start=arena_chip(k)->_cursor<rows?arena_chip(k)->_cursor:0;
        if(!chip_child(k,DW4_STATUS_SELECTE1,0,rows,start,0))return -1;
        arena_chip(k)->_st1=1;arena_chip(k)->_st2=arena_chip(k)->_st2?arena_chip(k)->_st2:0;arena_chip(k)->_st3=0;
        return 0;
    }
    if(arena_chip(k)->_st1==1) {
        if(arena_chip(k)->_retCode!=-1 && chip_refresh(k,1,1))return -1;
        arena_chip(k)->_st1=2;arena_chip(k)->_st3=0;
    }
    if(arena_chip(k)->_st1==2) {
        if(!chip_changed(k)) {
            int32_t selected=arena_chip(k)->_retCode;
            if(selected!=-1) {
                if(arena_chip(k)->_st3!=selected){if(chip_refresh(k,0,1))return -1;arena_chip(k)->_st3=selected;}
                else if(dw4_menu_window_count(k->self)==1 && dw4_statusview_selector_ready(k->self->children[0])==1) {
                    int turn=dw4_statuspage_turn(&arena_chip(k)->_nowPage,arena_chip(k)->_maxPage,0,&k->input,chip_model_sequence,k);
                    if(turn>=0 && !turn)turn=dw4_statuspage_turn(&arena_chip(k)->_nowPage,arena_chip(k)->_maxPage,1,&k->input,chip_model_sequence,k);
                    if(turn<0)return chip_fail(k,"page request failed");
                    if(turn) {
                        arena_chip(k)->_st1=1;arena_chip(k)->_st3=0;
                        if(dw4_statusview_selector_restart(k->self->children[0],chip_rows(k),NULL))return chip_fail(k,"selector repage failed");
                    }
                }
            }
        }else if(arena_chip(k)->_retCode==-1)return 1;
        else{arena_chip(k)->_cursor=arena_chip(k)->_retCode;arena_chip(k)->_st1=3;arena_chip(k)->_st2=0;arena_chip(k)->_st3=0;}
    }
    return 0;
}
static int chip_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct chip *k=w->user;int rc=0;
    if(dw4_menu_window_data(w)->_st0==3) {
        if(k->content && dw4_statusui_drain(&k->content,k->error,sizeof k->error))rc=-1;
        else if(!k->content && !dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;
    }else if(dw4_menu_window_data(w)->_st0==2) {
        if(k->content && dw4_statusui_close(k->content,k->error,sizeof k->error))rc=-1;
        else{dw4_menu_window_data(w)->_st0=3;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
    }else {
        memset(&k->input,0,sizeof k->input);
        if(k->c.input(k->c.user,k->c.view.player,&k->input))rc=chip_fail(k,"pad input unavailable");
        else {
            if(dw4_menu_window_data(w)->_st0==0){dw4_menu_window_data(w)->_st0=1;arena_chip(k)->_st1=0;arena_chip(k)->_st2=0;arena_chip(k)->_st3=0;}
            int r=chip_main(k);
            if(r<0)rc=-1;
            else if(r==1)dw4_menu_window_data(w)->_st0=2; /* close */
        }
    }
    if(rc)snprintf(error,cap,"%s",k->error[0]?k->error:"XDATA chip failed");
    return rc;
}
static void chip_release(void *u){struct chip *k=u;dw4_menu_window_close(k->content);dw4_property_list_release(k->self->arena,al_handle(arena_chip(k)->_itemBaseList));free(k);}
static dw4_menu_window *chip_open(const dw4_xdatashop_context *c)
{
    if(!c->input || !c->preview)return NULL;
    struct chip *k=calloc(1,sizeof *k);if(!k)return NULL;
    k->c=*c;k->c.view.parent=NULL;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlXdataChip",chip_update,k,chip_release);if(!w){free(k);return NULL;}
    k->self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;arena_chip(k)->_retCode=-1;return w;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct xdata *x=w->user;int rc=0;
    if(dw4_menu_window_data(w)->_st0==3){if(!dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;return 0;}
    if(dw4_menu_window_data(w)->_st0==2) {
        if(recalc(x,0) || restore_hp_mp(x))rc=-1;else advance(w);
    }else {
        if(dw4_menu_window_data(w)->_st0!=1){if(dw4_menu_window_data(w)->_st0!=0)return 0;advance(w);phase(x,0);}
        if(arena_xdata(x)->_st1==0) {
            if(arena_xdata(x)->_st2==0){if(menu_child(x,0x47e,3,arena_xdata(x)->_xdataMenu))rc=-1;else next_sub(x);}
            if(!rc && arena_xdata(x)->_st2==1 && changed(x)) {
                arena_xdata(x)->_parameter=0;int32_t selected=arena_xdata(x)->_retCode;
                if(selected==1){arena_xdata(x)->_xdataMenu=1;phase(x,2);}
                else if(selected==0){arena_xdata(x)->_xdataMenu=0;phase(x,1);}
                else advance(w);
            }
        }else if(arena_xdata(x)->_st1==2) {
            if(arena_xdata(x)->_st2==0) {
                if(recalc(x,0))rc=-1;
                else {
                    dw4_menu_window *chip=chip_open(&x->c);
                    if(!chip)rc=fail(x,"chip window requires pad input and a preview owner");
                    else if(dw4_menu_window_add(x->self,chip)){dw4_menu_window_close(chip);rc=fail(x,"chip window could not be attached");}
                    else {arena_xdata(x)->_nowProcKazu=dw4_menu_window_count(x->self);next_sub(x);}
                }
            }
            if(!rc && arena_xdata(x)->_st2==1 && changed(x)){phase(x,0);arena_xdata(x)->_st3=1;}
        }else if(arena_xdata(x)->_st1==1)rc=stat_main(x);
    }
    if(rc)snprintf(error,cap,"%s",x->error[0]?x->error:"XDATA shop failed");
    return rc;
}
dw4_menu_window *dw4_xdatashop_window_open(const dw4_xdatashop_context *c)
{
    if(!c || !c->databases || !c->view.sd || !c->view.engine || !c->view.players || c->view.player<0 || c->view.player>3)return NULL;
    struct xdata *x=calloc(1,sizeof *x);if(!x)return NULL;
    x->c=*c;x->c.view.parent=NULL;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrl10",update,x,free);if(!w){free(x);return NULL;}
    x->self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;arena_xdata(x)->_retCode=-1;return w;
}
int dw4_xdatashop_window_state(const dw4_menu_window *w,dw4_xdatashop_state *out)
{
    if(!w || !out || w->update!=update)return -1;
    const struct xdata *x=w->user;
    *out=(dw4_xdatashop_state){dw4_menu_window_data(w)->_st0,arena_xdata(x)->_st1,arena_xdata(x)->_st2,arena_xdata(x)->_st3,arena_xdata(x)->_parameter,arena_xdata(x)->_xdataMenu};return 0;
}
