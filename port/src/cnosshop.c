/* beNDMWShopCtrl40 update 429630..42a2d8. Field names follow the BANK controller: window state is the
 * primary state (+1c), main/sub are +20/+24, +30 is _retCode (written into ret.selection by the child
 * selectors), +50 the child-count snapshot and +54 the selected DEVICEFOLDER index. */
#include "dw4/cnosshop.h"
#include "dw4/statusdevice.h"
#include "dw4/statusui.h"
#include "dw4/statuscontent.h"
#include "dw4/playertransactions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cnos {
    dw4_cnosshop_context c;
    dw4_menu_window *self,*content;
    char error[256];
};
static beNDMWShopCtrl40 *arena_cnos(const struct cnos *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWShopCtrl40,p->self->object);}

static int fail(struct cnos *k,const char *what){snprintf(k->error,sizeof k->error,"CNOS: %s",what);return -1;}
static void phase(struct cnos *k,int32_t main){arena_cnos(k)->_st1=main;arena_cnos(k)->_st2=0;}
static int changed(const struct cnos *k){return dw4_menu_window_count(k->self)!=(size_t)arena_cnos(k)->_nowProcKazu;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static dw4_property_folder *folder(struct cnos *k)
{return dw4_playerrecords_get(k->c.view.players,"GETPLAYER",k->c.view.player);}
static int script(struct cnos *k,int32_t call)
{
    int rc=dw4_scriptengine_text_event(k->c.view.engine,k->c.view.scope,"txt_shop.lua",call);
    if(rc)snprintf(k->error,sizeof k->error,"txt_shop.lua %d: %.200s",call,dw4_scriptengine_error(k->c.view.engine));
    return rc;
}
static int hide_prompt(struct cnos *k)
{return dw4_statusui_call(&k->c.view,0,"TEXTCTL",NULL,-1,"SWITCH","STWINFONT29/font100/DISPOFF",k->error,sizeof k->error)<0?-1:0;}
static int add_child(struct cnos *k,dw4_menu_window *w,const char *what)
{
    if(!w)return fail(k,what);
    if(dw4_menu_window_add(k->self,w)){dw4_menu_window_close(w);return fail(k,"child window could not be attached");}
    arena_cnos(k)->_nowProcKazu=dw4_menu_window_count(k->self);return 0;
}
static int selector(struct cnos *k,int kind,int32_t call,int rows)
{return add_child(k,dw4_statusui_selector_window(&k->c.view,k->self,kind,call,rows,0,0,0,NULL),"selector window could not be opened");}
static dw4_menu_window *device(struct cnos *k)
{
    for(size_t i=0;i<dw4_menu_window_count(k->self);i++)if(dw4_statusdevice_window_is(k->self->children[i]))return k->self->children[i];
    return NULL;
}
/* State 0 prepares the prompt box with 3f5410's blank string and LEFT alignment; the 1450 script fills it. */
static int setup(void *u,dw4_statusview_io io,void *iou)
{
    dw4_statusview_command c={DW4_VIEW_TEXT,"STWINFONT29","font100","LEFT"," ",0};
    (void)u;return io(iou,&c);
}
/* coweapon / coarmor1 / coarmor2: ID and RATE of one table row (RANK is read by retail and discarded). */
static int table_row(void *u,int32_t row,int32_t *id,int32_t *rate)
{
    const dw4_database *d=u;
    return !d || dw4_database_number(d,row,"ID",id)<0 || dw4_database_number(d,row,"RATE",rate)<0?-1:0;
}
static int convert(struct cnos *k)
{
    static const char *const names[3]={"coweapon","coarmor1","coarmor2"};
    const dw4_database *db[3];void *users[3];dw4_cnos_table tables[3];
    for(int i=0;i<3;i++){
        db[i]=dw4_databases_get(k->c.databases,names[i]);
        if(!db[i]){snprintf(k->error,sizeof k->error,"CNOS: %s table is unavailable",names[i]);return -1;}
        users[i]=(void *)db[i];tables[i]=table_row;
    }
    int result=0;
    if(dw4_playertransactions_cnos_convert(k->c.view.players,k->c.view.player,(size_t)arena_cnos(k)->_selectCursor,tables,users,
           dw4_random_next(k->c.random),&result))return fail(k,"conversion transaction failed");
    if(!result)return fail(k,"BIT fell below the price after the quote");
    return dw4_statusui_call(&k->c.view,0,"SUBWND",NULL,k->c.view.player,"UPDATE",NULL,k->error,sizeof k->error)<0?-1:0;
}
static int main_step(struct cnos *k,dw4_menu_window *w)
{
    switch(arena_cnos(k)->_st1) {
    case 0:
        if(arena_cnos(k)->_st2==0) {
            /* ShopCtrl40 sets the list's +6d byte (only the placeholder equipment is selectable) and
             * clears +6f (no automatic close); the list publishes an absolute DEVICEFOLDER index. */
            dw4_statusdevice_context dc={.view=k->c.view,.databases=k->c.databases,.filter={.unknown_enable=1},
                .bank=0,.auto_close=0,.input=k->c.input,.user=k->c.user};
            dc.view.parent=NULL;dc.view.parent_window=k->self;dc.view.callno=0;
            if(add_child(k,dw4_statusdevice_window_open(&dc),"item list could not be opened") || script(k,1450))return -1;
            arena_cnos(k)->_st2=1;return 0;
        }else {
            dw4_menu_window *dev=device(k);
            if(!dev)return 0;
            if(arena_cnos(k)->_retCode==-1){phase(k,3);return 0;}
            if(dw4_statusdevice_window_ready(dev)!=1)return 0;
            dw4_property_folder *f=folder(k);int32_t bit;size_t n;
            const dw4_item_record *items=f?dw4_property_items(f,"DEVICEFOLDER",&n):NULL;
            if(!f || (!items && n) || dw4_property_number(f,"BIT",&bit))return fail(k,"BIT/DEVICEFOLDER records unavailable");
            /* Retail cannot reach an empty inventory (equipped gear stays), where the list's single blank
             * row would still publish index 0; a selection that is not a weapon/armor is ignored natively. */
            if((size_t)arena_cnos(k)->_retCode>=n || items[arena_cnos(k)->_retCode].kind<0 || items[arena_cnos(k)->_retCode].kind>2)
                return dw4_statusdevice_window_restart(dev)?fail(k,"item list could not restart"):0;
            arena_cnos(k)->_selectCursor=arena_cnos(k)->_retCode;
            phase(k,bit<DW4_CNOS_PRICE?2:1);
            return hide_prompt(k);
        }
    case 1:
        if(arena_cnos(k)->_st2==0){if(selector(k,DW4_STATUS_SHOPSELECT00,0x5AC,1))return -1;arena_cnos(k)->_st2=1;return 0;}
        if(arena_cnos(k)->_st2==1){
            if(!changed(k))return 0;
            if(selector(k,DW4_STATUS_XDATAMENU,0x5AD,2))return -1;
            arena_cnos(k)->_st2=2;return 0;
        }
        if(!changed(k))return 0;
        /* The first entry is yes: charge, reroll and refresh the balance. Either answer reselects the item. */
        if(arena_cnos(k)->_retCode==0 && convert(k))return -1;
        arena_cnos(k)->_retCode=arena_cnos(k)->_selectCursor;
        {
            dw4_menu_window *dev=device(k);
            if(dev) {
                if(dw4_statusdevice_window_restart(dev))return fail(k,"item list could not restart");
                phase(k,0);arena_cnos(k)->_st2=1;
                return hide_prompt(k);
            }
        }
        return 0;
    case 2:
        if(arena_cnos(k)->_st2==0){if(selector(k,DW4_STATUS_SHOPSELECT00,0x5AB,1))return -1;arena_cnos(k)->_st2=1;return 0;}
        if(changed(k))phase(k,3);
        return 0;
    case 3:
        if(arena_cnos(k)->_st2==0) {
            dw4_menu_window *dev=device(k);
            if(dev && dw4_statusdevice_window_close(dev))return fail(k,"item list could not be closed");
            arena_cnos(k)->_st2=1;return 0;
        }
        if(!device(k)){advance(w);phase(k,0);}
        return 0;
    }
    return 0;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct cnos *k=w->user;int rc=0;
    if(dw4_menu_window_data(w)->_st0==3) {
        if(k->content && dw4_statusui_drain(&k->content,k->error,sizeof k->error))rc=-1;
        else if(!k->content && !dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;
    }else if(dw4_menu_window_data(w)->_st0==2) {
        if(k->content && dw4_statusui_close(k->content,k->error,sizeof k->error))rc=-1;
        else{dw4_menu_window_data(w)->_st0=3;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
    }else {
        if(dw4_menu_window_data(w)->_st0==0) {
            if(dw4_statusui_open(&k->c.view,setup,k,&k->content,k->error,sizeof k->error))rc=-1;
            else{advance(w);phase(k,0);}
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1)rc=main_step(k,w);
    }
    if(rc)snprintf(error,cap,"%s",k->error[0]?k->error:"CNOS failed");
    return rc;
}
static void release(void *u){struct cnos *k=u;dw4_menu_window_close(k->content);free(k);}
dw4_menu_window *dw4_cnosshop_window_open(const dw4_cnosshop_context *c)
{
    if(!c || !c->databases || !c->input || !c->random || !c->view.sd || !c->view.engine || !c->view.players ||
       c->view.player<0 || c->view.player>3)return NULL;
    struct cnos *k=calloc(1,sizeof *k);if(!k)return NULL;
    /* _retCode starts at 0 (zeroed window memory): the first menu of this controller is the list itself,
     * and a -1 here would read as an immediate cancel before the list publishes anything. */
    k->c=*c;k->c.view.parent=NULL;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrl40",update,k,release);if(!w){free(k);return NULL;}
    k->self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;arena_cnos(k)->_retCode=0;return w;
}
int dw4_cnosshop_window_state(const dw4_menu_window *w,dw4_cnosshop_state *out)
{
    if(!w || !out || w->update!=update)return -1;
    const struct cnos *k=w->user;
    *out=(dw4_cnosshop_state){dw4_menu_window_data(w)->_st0,arena_cnos(k)->_st1,arena_cnos(k)->_st2,arena_cnos(k)->_selectCursor};return 0;
}
