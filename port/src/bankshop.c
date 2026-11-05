/* beNDMWShopCtrl30 update 428790..429628 over native selector windows, with beNDMWShopCtrlEditBit
 * 4332d0 as its money editor. Field names follow the XDATA controller: window state is the primary
 * state (28), main/sub/flag are 32/36/40, 48 is _retCode (written into ret.selection by the child
 * selectors), 84 is the first menu's result and 80 the child-count snapshot. */
#include "dw4/bankshop.h"
#include "dw4/statusbit.h"
#include "dw4/statusdevice.h"
#include "dw4/statusui.h"
#include "dw4/statuscontent.h"
#include "dw4/playertransactions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ---- ShopCtrlEditBit 4332d0: deposit (mode 0) and withdraw (mode 1) amount editor ---- */
struct edit {
    dw4_bankshop_context c;
    dw4_menu_window *outer;
    dw4_menu_window *self,*content;
    char error[256];
};
static beNDMWShopCtrlEditBit *arena_edit(const struct edit *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWShopCtrlEditBit,p->self->object);}

static int edit_fail(struct edit *e,const char *what){snprintf(e->error,sizeof e->error,"BANK editor: %s",what);return -1;}
static int edit_changed(const struct edit *e){return dw4_menu_window_count(e->self)!=(size_t)arena_edit(e)->_nowProcKazu;}
static int command(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
/* Retail issues the model, the tracked label fonts and the label/prompt scripts in this order. */
static int edit_setup(void *u,dw4_statusview_io io,void *iou)
{
    struct edit *e=u;
    /* Mode 2 (the junk-shop donation) has one tracked label and no prompt: 1378 only. */
    if(command(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin",arena_edit(e)->_entCode==2?"SQ_JUNKOPEN":arena_edit(e)->_entCode?"SQ_BITDRAWOUTOPEN":"SQ_BITPUTINOPEN","SQ_CLOSE",0))return -1;
    for(int i=0;i<(arena_edit(e)->_entCode==2?1:arena_edit(e)->_entCode?3:2);i++) {
        char font[16];snprintf(font,sizeof font,"font%03d",i);
        if(command(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT36",font,NULL,NULL,0))return -1;
    }
    if(arena_edit(e)->_entCode==2)return command(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1378);
    if(command(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,arena_edit(e)->_entCode?1375:1301) ||
       command(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
       command(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,arena_edit(e)->_entCode?1367:1360))return -1;
    return 0;
}
static int edit_digits(struct edit *e,int family,int32_t value,int width)
{return dw4_statuscontent_digits(family,value,width,dw4_statusview_window_emit,e->content)?edit_fail(e,"digit text could not be written"):0;}
static dw4_menu_window *edit_child(struct edit *e,int kind,int32_t call,int variant)
{
    dw4_statusview_context v=e->c.view;v.parent=NULL;v.parent_window=e->self;v.callno=call;v.rows=kind==DW4_STATUS_SHOPSELECT34?7:kind==DW4_STATUS_XDATAMENU?2:1;
    v.selected=kind==DW4_STATUS_SHOPSELECT34?6:0;v.variant=variant;v.position[0]=v.position[1]=v.position[2]=0;
    v.enabled=NULL;v.selection_initialize=NULL;
    dw4_menu_window *w=dw4_statusview_window_open(kind,&v);
    if(!w){edit_fail(e,"selector window could not be opened");return NULL;}
    if(dw4_menu_window_add(e->self,w)){dw4_menu_window_close(w);edit_fail(e,"selector window could not be attached");return NULL;}
    arena_edit(e)->_nowProcKazu=dw4_menu_window_count(e->self);return w;
}
static int edit_main(struct edit *e)
{
    dw4_property_folder *f=dw4_playerrecords_get(e->c.view.players,"GETPLAYER",e->c.view.player);
    switch(arena_edit(e)->_st1) {
    case 0:
        if(!edit_child(e,DW4_STATUS_SHOPSELECT34,0,arena_edit(e)->_entCode==1?1:0))return -1; /* mode 2 placement is unverified: deposit's */
        arena_edit(e)->_st1=1;return 0;
    case 1: {
        int32_t bit,bank;
        if(!f || dw4_property_number(f,"BIT",&bit) || dw4_property_number(f,"BANKBIT",&bank) ||
           bit<0 || bit>9999999 || bank<0 || bank>9999999)return edit_fail(e,"BIT/BANKBIT records unavailable");
        arena_edit(e)->_editBit=0;
        if(arena_edit(e)->_entCode==2) {
            /* 4332d0 case 2: the wallet is the limit (the 999,999,999 ceiling cannot bind below 9,999,999). */
            if(edit_digits(e,0,0,1))return -1;
            arena_edit(e)->_editMax=bit>=999999999-bit?999999999-bit:bit;
        }else if(!arena_edit(e)->_entCode) {
            /* Deposit: the amount is shown in font00x, the bank balance in font01x. */
            if(edit_digits(e,0,0,1))return -1;
            arena_edit(e)->_editMax=bit>=9999999-bank?9999999-bank:bit;
            if(edit_digits(e,1,bank,1))return -1;
        }else {
            /* Withdraw: the amount in font01x, the wallet in font00x and the bank balance in font02x. */
            if(edit_digits(e,1,0,1))return -1;
            arena_edit(e)->_editMax=bank<9999999-bit?bank:9999999-bit;
            if(edit_digits(e,0,bit,1) || edit_digits(e,2,bank,1))return -1;
        }
        arena_edit(e)->_st1=2;arena_edit(e)->_st3=0;return 0;
    }
    case 2:
        if(!edit_changed(e)) {
            int32_t selected=arena_edit(e)->_retCode;
            if(selected==-1)return 0;
            int ready=0;dw4_statuspage_input pad={0};
            if(arena_edit(e)->_st3==selected) {
                ready=dw4_statusui_call(&e->c.view,1,"SELECTCTRL","i_stcursor03",e->c.view.player,"ISSELECTNOW",NULL,e->error,sizeof e->error);
                if(ready<0)return -1;
                ready=(uint8_t)ready;
                if(ready && e->c.input(e->c.user,e->c.view.player,&pad))return edit_fail(e,"pad input unavailable");
            }
            int effects=dw4_statusbit_edit(&arena_edit(e)->_editBit,arena_edit(e)->_editMax,selected,&arena_edit(e)->_st3,ready,&pad);
            if(effects<0)return edit_fail(e,"digit state is invalid");
            if((effects&DW4_STATUSBIT_REDRAW) && edit_digits(e,arena_edit(e)->_entCode==1?1:0,arena_edit(e)->_editBit,7-selected))return -1;
            if((effects&DW4_STATUSBIT_SOUND) &&
               dw4_statusui_call(&e->c.view,0,"SOUND","CURSOR_MOVE",0,"PLAY",NULL,e->error,sizeof e->error)<0)return -1;
            return 0;
        }
        if(arena_edit(e)->_retCode!=-1 && arena_edit(e)->_editBit>0) {
            dw4_menu_window_data(e->outer)->_retCode=arena_edit(e)->_editBit;arena_edit(e)->_st1=3;
            return dw4_statusui_call(&e->c.view,0,"TEXTCTL",NULL,-1,"SWITCH","STWINFONT29/font100/DISPOFF",e->error,sizeof e->error)<0?-1:0;
        }
        dw4_menu_window_data(e->outer)->_retCode=-1;return 1; /* cancelled or nothing entered: close */
    case 3:
        if(!edit_child(e,DW4_STATUS_SHOPSELECT00,arena_edit(e)->_entCode==2?0x7A9:arena_edit(e)->_entCode?0x559:0x552,0))return -1;
        arena_edit(e)->_st1=4;return 0;
    case 4:
        if(!edit_changed(e))return 0;
        if(arena_edit(e)->_entCode!=2)return 1;
        arena_edit(e)->_st1=5;return 0;
    case 5: /* donation: a yes/no question follows the acknowledgement */
        if(!edit_child(e,DW4_STATUS_XDATAMENU,0x7AA,0))return -1;
        arena_edit(e)->_st1=6;return 0;
    case 6:
        if(!edit_changed(e))return 0;
        if(arena_edit(e)->_retCode!=0)dw4_menu_window_data(e->outer)->_retCode=-1;
        return 1;
    }
    return 0;
}
static int edit_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct edit *e=w->user;int rc=0;
    if(dw4_menu_window_data(w)->_st0==3) {
        if(e->content && dw4_statusui_drain(&e->content,e->error,sizeof e->error))rc=-1;
        else if(!e->content && !dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;
    }else if(dw4_menu_window_data(w)->_st0==2) {
        if(e->content && dw4_statusui_close(e->content,e->error,sizeof e->error))rc=-1;
        else {
            static const char *const formats[]={"font%03d","font01%d","font02%d"};
            for(int i=0;!rc && i<7;i++)for(int k=0;k<3 && !rc;k++) {
                char name[48],font[16];snprintf(font,sizeof font,formats[k],i);snprintf(name,sizeof name,"STWINFONT25/%s/DISPOFF",font);
                if(dw4_statusui_call(&e->c.view,0,"TEXTCTL",NULL,-1,"SWITCH",name,e->error,sizeof e->error)<0)rc=-1;
            }
            if(!rc){dw4_menu_window_data(w)->_st0=3;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
        }
    }else {
        if(dw4_menu_window_data(w)->_st0==0) {
            dw4_statusview_context v=e->c.view;v.initialize=edit_setup;v.user=e;
            e->content=dw4_statusview_window_open(DW4_STATUS_CONTENT,&v);
            if(!e->content || dw4_menu_window_tick(e->content,e->error,sizeof e->error))rc=edit_fail(e,"content window failed");
            else{dw4_menu_window_data(w)->_st0=1;arena_edit(e)->_st1=0;}
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1) {
            int r=edit_main(e);
            if(r<0)rc=-1;else if(r==1){dw4_menu_window_data(w)->_st0=2;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
        }
    }
    if(rc)snprintf(error,cap,"%s",e->error[0]?e->error:"BANK editor failed");
    return rc;
}
static void edit_release(void *u){struct edit *e=u;dw4_menu_window_close(e->content);free(e);}
dw4_menu_window *dw4_bankshop_editor_open(const dw4_bankshop_context *c,dw4_menu_window *outer,int32_t mode)
{
    if(mode<0 || mode>2)return NULL;
    struct edit *e=calloc(1,sizeof *e);if(!e)return NULL;
    e->c=*c;e->c.view.parent=NULL;e->outer=outer;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlEditBit",edit_update,e,edit_release);if(!w){free(e);return NULL;}
    e->self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;arena_edit(e)->_entCode=mode;arena_edit(e)->_retCode=-1;return w;
}

/* ---- ShopCtrl30 ---- */
struct bank {
    dw4_bankshop_context c;
    dw4_menu_window *self;
    char error[256];
};
static beNDMWShopCtrl30 *arena_bank(const struct bank *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWShopCtrl30,p->self->object);}

static int fail(struct bank *b,const char *what){snprintf(b->error,sizeof b->error,"BANK: %s",what);return -1;}
static void phase(struct bank *b,int32_t main){arena_bank(b)->_st1=main;arena_bank(b)->_st2=0;arena_bank(b)->_st3=0;}
static int changed(const struct bank *b){return dw4_menu_window_count(b->self)!=(size_t)arena_bank(b)->_nowProcKazu;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static dw4_property_folder *folder(struct bank *b)
{return dw4_playerrecords_get(b->c.view.players,"GETPLAYER",b->c.view.player);}
static int script(struct bank *b,int32_t call)
{
    int rc=dw4_scriptengine_text_event(b->c.view.engine,b->c.view.scope,"txt_shop.lua",call);
    if(rc)snprintf(b->error,sizeof b->error,"txt_shop.lua %d: %.200s",call,dw4_scriptengine_error(b->c.view.engine));
    return rc;
}
static int hide_prompt(struct bank *b)
{return dw4_statusui_call(&b->c.view,0,"TEXTCTL",NULL,-1,"SWITCH","STWINFONT29/font100/DISPOFF",b->error,sizeof b->error)<0?-1:0;}
static int add_child(struct bank *b,dw4_menu_window *w,const char *what)
{
    if(!w)return fail(b,what);
    if(dw4_menu_window_add(b->self,w)){dw4_menu_window_close(w);return fail(b,"child window could not be attached");}
    arena_bank(b)->_nowProcKazu=dw4_menu_window_count(b->self);return 0;
}
static int selector(struct bank *b,int kind,int32_t call,int rows,int selected)
{
    return add_child(b,dw4_statusui_selector_window(&b->c.view,b->self,kind,call,rows,selected,0,0,NULL),"selector window could not be opened");
}
static dw4_menu_window *device(struct bank *b)
{
    for(size_t i=0;i<dw4_menu_window_count(b->self);i++)if(dw4_statusdevice_window_is(b->self->children[i]))return b->self->children[i];
    return NULL;
}
static int counts(struct bank *b,size_t *inventory,size_t *bank)
{
    dw4_property_folder *f=folder(b);
    if(!f || dw4_property_item_count(f,"DEVICEFOLDER",inventory) || dw4_property_item_count(f,"BANKDEVICE",bank) ||
       *inventory>36 || *bank>96)return fail(b,"DEVICEFOLDER/BANKDEVICE records unavailable");
    return 0;
}
/* Items: deposit (main 2) or withdraw (main 3) over the shared DEVICE list. */
static int item_main(struct bank *b)
{
    int withdraw=arena_bank(b)->_st1==3;
    switch(arena_bank(b)->_st2) {
    case 0: {
        dw4_statusdevice_context dc={.view=b->c.view,.databases=b->c.databases,.filter={.equip_disable=1},
            .bank=withdraw,.auto_close=0,.input=b->c.input,.user=b->c.user};
        dc.view.parent=NULL;dc.view.parent_window=b->self;dc.view.callno=0;
        dw4_menu_window *w=dw4_statusdevice_window_open(&dc);
        if(add_child(b,w,"item list could not be opened") || script(b,withdraw?1364:1357))return -1;
        arena_bank(b)->_st2=1;return 0;
    }
    case 1: {
        dw4_menu_window *dev=device(b);
        if(!dev)return 0;
        if(arena_bank(b)->_retCode==-1) {
            if(dw4_statusdevice_window_close(dev))return fail(b,"item list could not be closed");
            arena_bank(b)->_st2=5;arena_bank(b)->_st3=0;return hide_prompt(b);
        }
        if(dw4_statusdevice_window_ready(dev)!=1)return 0;
        size_t inventory,bank;if(counts(b,&inventory,&bank))return -1;
        size_t index=(size_t)arena_bank(b)->_retCode;int result=0;
        if(!withdraw) {
            if(bank>=96){arena_bank(b)->_st2=2;arena_bank(b)->_st3=0x54E;return 0;}
            const dw4_item_record *items=dw4_property_items(folder(b),"DEVICEFOLDER",&inventory);
            if(!items || index>=inventory)return fail(b,"selected item is unavailable");
            if(!items[index].equipped && dw4_playertransactions_bank_item(b->c.view.players,b->c.view.player,0,index,&result))
                return fail(b,"deposit transaction failed");
        }else {
            if(inventory>=36){arena_bank(b)->_st2=2;arena_bank(b)->_st3=0x555;return 0;}
            if(index>=bank)return fail(b,"selected item is unavailable");
            if(dw4_playertransactions_bank_item(b->c.view.players,b->c.view.player,1,index,&result))
                return fail(b,"withdraw transaction failed");
            if(counts(b,&inventory,&bank))return -1;
            if(bank==0) {
                arena_bank(b)->_st2=2;arena_bank(b)->_st3=0x55E;
                return dw4_statusdevice_window_refresh(dev,1)?fail(b,"item list refresh failed"):0;
            }
        }
        return dw4_statusdevice_window_restart(dev)?fail(b,"item list could not restart"):0;
    }
    case 2:
        if(hide_prompt(b) || selector(b,DW4_STATUS_SHOPSELECT00,arena_bank(b)->_st3,1,0))return -1;
        arena_bank(b)->_st2=3;return 0;
    case 3: {
        if(!changed(b))return 0;
        dw4_menu_window *dev=device(b);
        if(!dev)return 0;
        if(dw4_statusdevice_window_close(dev))return fail(b,"item list could not be closed");
        arena_bank(b)->_st2=5;arena_bank(b)->_st3=0;return 0;
    }
    case 5:
        if(!device(b))phase(b,0);
        return 0;
    }
    return 0;
}
/* Money: the editor publishes an amount (or -1) as this window's result. */
static int money_main(struct bank *b)
{
    if(arena_bank(b)->_st2==0) {
        dw4_menu_window *w=dw4_bankshop_editor_open(&b->c,b->self,arena_bank(b)->_bankMenu);
        if(add_child(b,w,"amount editor could not be opened"))return -1;
        arena_bank(b)->_st2=1;return 0;
    }
    if(!changed(b))return 0;
    if(arena_bank(b)->_retCode!=-1) {
        int result=0;
        if(dw4_playertransactions_bank_bit(b->c.view.players,b->c.view.player,arena_bank(b)->_bankMenu,arena_bank(b)->_retCode,&result) || !result)
            return fail(b,"money transaction failed");
        if(dw4_statusui_call(&b->c.view,0,"SUBWND",NULL,b->c.view.player,"UPDATE",NULL,b->error,sizeof b->error)<0)return -1;
    }
    phase(b,0);return 0;
}
static int main_step(struct bank *b,dw4_menu_window *w)
{
    switch(arena_bank(b)->_st1) {
    case 0:
        if(arena_bank(b)->_st2==0){if(selector(b,DW4_STATUS_XDATAMENU,0x546,3,arena_bank(b)->_bankMenu))return -1;arena_bank(b)->_st2=1;}
        if(arena_bank(b)->_st2==1 && changed(b)) {
            int32_t selected=arena_bank(b)->_retCode;
            if(selected==0 || selected==1){arena_bank(b)->_bankMenu=selected;phase(b,1);}
            else advance(w);
        }
        return 0;
    case 1:
        if(arena_bank(b)->_st2==0){if(selector(b,DW4_STATUS_XDATAMENU,0x54B,2,0))return -1;arena_bank(b)->_st2=1;}
        if(arena_bank(b)->_st2==1 && changed(b)) {
            int32_t selected=arena_bank(b)->_retCode;
            if(selected==0) {
                size_t inventory,bank;if(counts(b,&inventory,&bank))return -1;
                if(!arena_bank(b)->_bankMenu)phase(b,2);
                else if(!bank){phase(b,6);arena_bank(b)->_st3=0x55E;}
                else phase(b,3);
            }else if(selected==1)phase(b,arena_bank(b)->_bankMenu?5:4);
            else phase(b,0);
        }
        return 0;
    case 2:case 3:return item_main(b);
    case 4:case 5:return money_main(b);
    case 6:
        if(arena_bank(b)->_st2==0){if(selector(b,DW4_STATUS_SHOPSELECT00,arena_bank(b)->_st3,1,0))return -1;arena_bank(b)->_st2=1;}
        else if(changed(b))phase(b,0);
        return 0;
    }
    return 0;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct bank *b=w->user;int rc=0;
    if(dw4_menu_window_data(w)->_st0==3){if(!dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;return 0;}
    if(dw4_menu_window_data(w)->_st0==2)advance(w);
    else {
        if(dw4_menu_window_data(w)->_st0!=1){if(dw4_menu_window_data(w)->_st0!=0)return 0;advance(w);phase(b,0);}
        rc=main_step(b,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"BANK failed");
    return rc;
}
dw4_menu_window *dw4_bankshop_window_open(const dw4_bankshop_context *c)
{
    if(!c || !c->databases || !c->input || !c->view.sd || !c->view.engine || !c->view.players || c->view.player<0 || c->view.player>3)return NULL;
    struct bank *b=calloc(1,sizeof *b);if(!b)return NULL;
    b->c=*c;b->c.view.parent=NULL;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrl30",update,b,free);if(!w){free(b);return NULL;}
    b->self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;arena_bank(b)->_retCode=-1;return w;
}
int dw4_bankshop_window_state(const dw4_menu_window *w,dw4_bankshop_state *out)
{
    if(!w || !out || w->update!=update)return -1;
    const struct bank *b=w->user;
    *out=(dw4_bankshop_state){dw4_menu_window_data(w)->_st0,arena_bank(b)->_st1,arena_bank(b)->_st2,arena_bank(b)->_st3,arena_bank(b)->_bankMenu};return 0;
}
