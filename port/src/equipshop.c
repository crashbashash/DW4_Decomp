/* beNDMWShopDevice update 43cc20, beNDMWShopJunk 42bc70 and beNDMWShopCtrlSales 438160. Field names follow the BANK
 * and DISK controllers: the window state is the primary state (+1c), main/sub are +20/+24, +28 the "last"/argument
 * word, +30 _retCode (written into ret.selection by the child selectors), +50 the child-count snapshot, +54 the page,
 * +58 the page count, +5c the last cursor and +60 the stock list. Completion of a child is a change in the child
 * count, as in retail. */
#include "dw4/equipshop.h"
#include "arenalist.h"
#include "dw4/bankshop.h"
#include "dw4/diskshop.h"
#include "dw4/statusui.h"
#include "dw4/statuscontent.h"
#include "dw4/playerstats.h"
#include "dw4/playertransactions.h"
#include "dw4/scriptengine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct base {
    dw4_equipshop_context c;
    dw4_menu_window *self,*content;
    char error[256];
};
static beNDMWWindowCtrl *arena_base(const struct base *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWWindowCtrl,p->self->object);}

static int bfail(struct base *b,const char *what){snprintf(b->error,sizeof b->error,"SHOP: %s",what);return -1;}
static int changed(const struct base *b){return dw4_menu_window_count(b->self)!=(size_t)arena_base(b)->_nowProcKazu;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static int cmd(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static int tell(struct base *b,const char *model,const char *sequence)
{return dw4_statusui_call(&b->c.view,0,"MODELCTRL",model,0,sequence,NULL,b->error,sizeof b->error)<0?-1:0;}
static int subwnd(struct base *b,const char *key)
{return dw4_statusui_call(&b->c.view,0,"SUBWND",NULL,b->c.view.player,key,NULL,b->error,sizeof b->error)<0?-1:0;}
static dw4_property_folder *folder(struct base *b)
{return dw4_playerrecords_get(b->c.view.players,"GETPLAYER",b->c.view.player);}
static int add_child(struct base *b,dw4_menu_window *w,const char *what)
{
    if(!w)return bfail(b,what);
    if(dw4_menu_window_add(b->self,w)){dw4_menu_window_close(w);return bfail(b,"child window could not be attached");}
    arena_base(b)->_nowProcKazu=dw4_menu_window_count(b->self);return 0;
}
typedef int (*selector_init)(void *,dw4_statusview_io,void *);
static int selector(struct base *b,int kind,int call,int rows,int selected,float x,float y,
    const uint8_t *enabled,selector_init init)
{
    dw4_statusview_context c=b->c.view;c.parent=NULL;c.parent_window=b->self;c.callno=call;c.rows=rows;c.selected=selected;c.variant=0;
    c.position[0]=x;c.position[1]=y;c.position[2]=0;c.enabled=enabled;c.selection_initialize=init;c.user=b;
    c.initialize=NULL;c.refresh=NULL;
    return add_child(b,dw4_statusview_window_open(kind,&c),"selector window could not be opened");
}
static int notice(struct base *b,int call){return selector(b,DW4_STATUS_SHOPSELECT00,call,1,0,0,0,NULL,NULL);}
static int menu(struct base *b,int call,int rows){return selector(b,DW4_STATUS_XDATAMENU,call,rows,0,0,0,NULL,NULL);}
/* 43a950 / 435250: the i_stcursor04 marker opens at (-121,128,0) with SQ_OPEN%02d, or closes when running. */
static int cursor(struct base *b,int index)
{
    if(index<0) {
        int running=dw4_statusui_call(&b->c.view,1,"MODELCTRL","i_stcursor04",0,"ISRUN",NULL,b->error,sizeof b->error);
        if(running<0)return -1;
        return running?tell(b,"i_stcursor04","SQ_CLOSE"):0;
    }
    char sequence[24];snprintf(sequence,sizeof sequence,"SQ_OPEN%02d",index);
    return dw4_statusui_positioned(&b->c.view,"i_stcursor04",0,sequence,-121,128,0,b->error,sizeof b->error);
}
static void close_children(struct base *b){for(size_t i=0;i<dw4_menu_window_count(b->self);i++)dw4_menu_window_remove(b->self->children[i]);}
/* Primary states shared by every window: 2 closes the content owner and children, 3 waits for them. */
static int finish(dw4_menu_window *w,struct base *b)
{
    int rc=0;
    if(dw4_menu_window_data(w)->_st0==3) {
        if(b->content && dw4_statusui_drain(&b->content,b->error,sizeof b->error))rc=-1;
        else if(!b->content && !dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;
    }else {
        close_children(b);
        if(b->content && dw4_statusui_close(b->content,b->error,sizeof b->error))rc=-1;
        else{dw4_menu_window_data(w)->_st0=3;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
    }
    return rc;
}
static void release(void *u){struct base *b=u;dw4_menu_window_close(b->content);free(b);}
static void init_base(struct base *b,const dw4_equipshop_context *c)
{b->c=*c;b->c.view.parent=NULL;}
static int valid(const dw4_equipshop_context *c)
{
    return c && c->databases && c->stock && c->input && c->preview && c->view.sd && c->view.engine && c->view.players &&
        c->view.player>=0 && c->view.player<4 && c->mode>=6 && c->mode<=9;
}
static dw4_diskshop_context disk_context(const struct base *b)
{return (dw4_diskshop_context){.view=b->c.view,.databases=b->c.databases,.input=b->c.input,.user=b->c.user};}
static dw4_bankshop_context bank_context(const struct base *b)
{return (dw4_bankshop_context){.view=b->c.view,.databases=b->c.databases,.input=b->c.input,.user=b->c.user};}

/* ---- ShopCtrlSales (438160) ---- */
struct sales {
    struct base b;
    int32_t rows,notice;
    dw4_statuspage_input input;
};
static beNDMWShopCtrlSales *arena_sales(const struct sales *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlSales,p->b.self->object);}

static const dw4_item_record *stock_list(struct sales *k,size_t *count)
{return dw4_item_list_view(k->b.self->arena,al_handle(arena_sales(k)->_salesItemList),count);}
static const uint8_t *sales_flags(const struct sales *k)
{return al_data(k->b.self->arena,arena_sales(k)->_decideList,1);}
static void sales_release(void *u)
{
    struct sales *k=u;dw4_arena *a=k->b.self->arena;
    dw4_property_list_release(a,al_handle(arena_sales(k)->_salesItemList));al_drop(a,&arena_sales(k)->_decideList);release(u);
}
/* 439aa0: page count (ceil of the last present slot + 1, or the list size when nothing is present), the current
 * page's row count (leading present slots, 1..12) and each row's decide byte (a null or sold-out row is 0). */
static int layout(struct sales *k)
{
    size_t count,n;const dw4_item_record *list=stock_list(k,&count);
    n=count;
    for(size_t i=0;i<count;i++)if(list[i].kind>=0)n=i+1;
    arena_sales(k)->_maxPage=(int32_t)(n/12+(n%12!=0));
    size_t rows=12;
    for(size_t i=0;i<12;i++) {
        size_t index=(size_t)arena_sales(k)->_nowPage*12+i;
        if(index>=count || list[index].kind<0){rows=i;break;}
    }
    if(rows<1)rows=1;
    k->rows=(int32_t)rows;
    uint8_t flags[12]={0};
    for(size_t i=0;i<rows;i++) {
        size_t index=(size_t)arena_sales(k)->_nowPage*12+i;
        flags[i]=index<count && list[index].kind>=0 && !(list[index].kind==3 && list[index].record==DW4_SHOPSTOCK_SOLD_OUT);
    }
    int32_t h=al_new(k->b.self->arena,"igBoolList",1,k->rows,flags);if(!h)return bfail(&k->b,"decide list allocation failed");
    al_drop(k->b.self->arena,&arena_sales(k)->_decideList);arena_sales(k)->_decideList=h;return 0;
}
static const dw4_item_record *slot_item(struct sales *k,int32_t selection,size_t *slot)
{
    size_t count;const dw4_item_record *list=stock_list(k,&count);
    if(selection<0)return NULL;
    size_t index=(size_t)arena_sales(k)->_nowPage*12+(size_t)selection;
    if(slot)*slot=index;
    return index<count && list[index].kind>=0?list+index:NULL;
}
static int preview_visit(void *u,dw4_property_folder *staged)
{struct sales *k=u;return k->b.c.preview(k->b.c.user,staged,k->b.error,sizeof k->b.error);}
/* 439f30: the highlighted item replaces the equipped one on a staged copy for the stat comparison, or the
 * comparison is switched off when nothing is highlighted. */
static int preview(struct sales *k,const dw4_item_record *item)
{
    if(!item)return subwnd(&k->b,"OFPREVIEW");
    if(dw4_playertransactions_equip_preview(k->b.c.view.players,k->b.c.view.player,item,dw4_playerstats_recalculate,
           (void *)k->b.c.databases,preview_visit,k))return bfail(&k->b,"equip preview failed");
    return 0;
}
static int render(struct sales *k,int rows,int description)
{
    struct base *b=&k->b;size_t count;const dw4_item_record *list=stock_list(k,&count);
    if(!b->content)return bfail(b,"content window unavailable");
    if(dw4_statuscontent_sales(b->c.databases,list,count,arena_sales(k)->_nowPage,arena_sales(k)->_maxPage,arena_base(b)->_retCode,rows,description,
           dw4_statusview_window_emit,b->content))return bfail(b,"goods list text refresh failed");
    if(description)return preview(k,slot_item(k,arena_base(b)->_retCode,NULL));
    return 0;
}
static int sales_setup(void *u,dw4_statusview_io io,void *iou)
{
    struct sales *k=u;
    static const int32_t scripts[4][2]={{0x675,0x641},{0x6D9,0x6A5},{0x73D,0x709},{0x7A1,0x76D}};
    const int32_t *s=scripts[k->b.c.mode-6];
    if(cmd(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin","SQ_AWINOPEN","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorright",arena_sales(k)->_maxPage<2?"SQ_HIDE/V<236,25,0>":"SQ_SELECT/V<236,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,s[0]) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,s[1]))return -1;
    for(unsigned i=0;i<12;i++) {
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) ||
           cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT17",font,"RIGHT"," ",0))return -1;
    }
    return cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT30","font000","RIGHT"," ",0) ||
        cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT30","font001","RIGHT"," ",0);
}
static int list_prompt(void *u,dw4_statusview_io io,void *iou)
{(void)u;return cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0);}
/* The ineligible-item warning: txt_shop 0x7F8 into a tracked STWINFONT29/font000 owned by the notice. */
static int warning_text(void *u,dw4_statusview_io io,void *iou)
{(void)u;return cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font000",NULL,NULL,0) ||
    cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x7F8);}
static int page_io(void *u,const char *model,const char *sequence){struct sales *k=u;return tell(&k->b,model,sequence);}
/* 439d60: weapons need the Digimon in their SOUBI mask and the SKILL level; armor needs the LVPOINT level;
 * chips are always allowed. */
static int eligible(struct sales *k,const dw4_item_record *item,int *out)
{
    dw4_property_folder *f=folder(&k->b);
    if(!f || !item)return bfail(&k->b,"player or item unavailable");
    *out=0;
    if(item->kind==3){*out=1;return 0;}
    if(item->kind==0) {
        int32_t species,mask,skill,need;size_t n;
        const int32_t *levels=dw4_property_array(f,"SKILL",&n);
        if(dw4_property_number(f,"DIGIMONNO",&species) || species<0 || species>31 || !levels ||
           dw4_playerstats_item_attribute((void *)k->b.c.databases,item,"SOUBI",&mask) ||
           dw4_playerstats_item_attribute((void *)k->b.c.databases,item,"SKILL",&skill) ||
           dw4_playerstats_item_attribute((void *)k->b.c.databases,item,"SKILLPOINT",&need))return bfail(&k->b,"weapon requirements unavailable");
        *out=(((uint32_t)1u<<species)&(uint32_t)mask)!=0 && skill>=0 && (size_t)skill<n && levels[skill]>=need;
        return 0;
    }
    if(item->kind==1 || item->kind==2) {
        int32_t level,need;
        if(dw4_property_number(f,"LEVEL",&level) || dw4_playerstats_item_attribute((void *)k->b.c.databases,item,"LVPOINT",&need))
            return bfail(&k->b,"armor requirements unavailable");
        *out=level>=need;return 0;
    }
    return bfail(&k->b,"unknown item kind");
}
static int32_t notice_call(int kind){return kind==0?0x677:kind<=2?0x6DB:0x73F;}
static int32_t menu_call(int kind){return kind==0?0x678:kind<=2?0x6DC:0x740;}
static int sales_step(struct sales *k,dw4_menu_window *w)
{
    struct base *b=&k->b;
    switch(arena_sales(k)->_st1) {
    case 0:
        if(arena_sales(k)->_st2==0) {
            if(layout(k))return -1;
            if(selector(b,DW4_STATUS_SELECTE1,0,k->rows,arena_sales(k)->_cursor,-121,128,sales_flags(k),list_prompt))return -1;
            arena_base(b)->_retCode=arena_sales(k)->_cursor;arena_sales(k)->_st2=1;
        }
        if(arena_sales(k)->_st2==1) {
            if(layout(k))return -1;
            if(render(k,k->rows,1))return -1;
            arena_sales(k)->_st2=2;arena_sales(k)->_st3=0;return 0;
        }
        if(!changed(b)) {
            dw4_menu_window *child=dw4_menu_window_count(w)?w->children[0]:NULL;int32_t selected=arena_base(b)->_retCode;
            if(selected==-1 || !child)return 0;
            if(selected!=arena_sales(k)->_st3){if(render(k,0,1))return -1;arena_sales(k)->_st3=selected;return 0;}
            if(arena_sales(k)->_maxPage>=1 && dw4_statusview_selector_ready(child)==1) { /* an empty stock has no pages to turn */
                int turn=dw4_statuspage_turn(&arena_sales(k)->_nowPage,arena_sales(k)->_maxPage,0,&k->input,page_io,k);
                if(turn==0)turn=dw4_statuspage_turn(&arena_sales(k)->_nowPage,arena_sales(k)->_maxPage,1,&k->input,page_io,k);
                if(turn<0)return bfail(b,"page request failed");
                if(turn) {
                    if(layout(k))return -1;
                    if(dw4_statusview_selector_restart(child,k->rows,sales_flags(k)))return bfail(b,"selector repage failed");
                    arena_sales(k)->_st2=1;
                }
            }
            return 0;
        }
        /* The list closed: the comparison is switched off, then the selection decides the next phase. */
        if(preview(k,NULL))return -1;
        if(arena_base(b)->_retCode!=-1) {
            size_t slot=0;const dw4_item_record *item=slot_item(k,arena_base(b)->_retCode,&slot);
            int32_t price,bit;size_t held;
            dw4_property_folder *f=folder(b);
            if(!item || dw4_playerstats_item_price((void *)b->c.databases,item,0,&price) || !f ||
               dw4_property_number(f,"BIT",&bit) || dw4_property_item_count(f,"DEVICEFOLDER",&held))
                return bfail(b,"the selected goods record is unavailable");
            arena_sales(k)->_cursor=arena_base(b)->_retCode;arena_sales(k)->_st2=0;
            if(held>=36){arena_sales(k)->_st1=2;k->notice=0x686;}
            else if(bit<price){arena_sales(k)->_st1=2;k->notice=0x622;}
            else{arena_sales(k)->_st1=1;if(cursor(b,arena_sales(k)->_cursor))return -1;}
            return 0;
        }
        advance(w);return 0; /* cancel: the shop closes */
    case 1: {
        size_t slot;const dw4_item_record *item=slot_item(k,arena_sales(k)->_cursor,&slot);
        if(!item)return bfail(b,"the selected goods record is unavailable");
        if(arena_sales(k)->_st2==0) {
            int ok;
            if(eligible(k,item,&ok))return -1;
            if(ok?notice(b,notice_call(item->kind)):selector(b,DW4_STATUS_SHOPSELECT00,0,1,0,0,0,NULL,warning_text))return -1;
            arena_sales(k)->_st2=1;return 0;
        }
        if(arena_sales(k)->_st2==1){if(!changed(b))return 0;if(menu(b,menu_call(item->kind),2))return -1;arena_sales(k)->_st2=2;return 0;}
        if(!changed(b))return 0;
        if(arena_base(b)->_retCode==0) {
            int32_t price;int result;
            if(dw4_playerstats_item_price((void *)b->c.databases,item,0,&price))return bfail(b,"price unavailable");
            dw4_item_record bought=*item;
            if(dw4_playertransactions_shop_buy(b->c.view.players,b->c.view.player,&bought,price,&result) || !result)
                return bfail(b,"purchase transaction failed");
            if(dw4_shopstock_sell_out(b->c.stock,b->c.mode,slot))return bfail(b,"the stock slot could not be updated");
            if(subwnd(b,"UPDATE"))return -1;
        }
        arena_sales(k)->_st1=0;arena_sales(k)->_st2=0;return cursor(b,-1);
    }
    case 2:
        if(arena_sales(k)->_st2==0){if(notice(b,k->notice))return -1;arena_sales(k)->_st2=1;return 0;}
        if(changed(b)){arena_sales(k)->_st1=0;arena_sales(k)->_st2=0;}
        return 0;
    }
    return 0;
}
static int sales_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct sales *k=w->user;struct base *b=&k->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        memset(&k->input,0,sizeof k->input);
        if(b->c.input(b->c.user,b->c.view.player,&k->input))rc=bfail(b,"pad input unavailable");
        if(!rc && dw4_menu_window_data(w)->_st0==0) {
            if(layout(k))return -1;
            /* Without a stock object retail closes at once; the prepared stock always exists. */
            if(dw4_statusui_open(&b->c.view,sales_setup,k,&b->content,b->error,sizeof b->error))rc=-1;
            else{advance(w);arena_sales(k)->_st1=0;arena_sales(k)->_st2=0;arena_sales(k)->_cursor=0;}
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1)rc=sales_step(k,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"shop goods list failed");
    return rc;
}
static dw4_menu_window *sales_open(const struct base *parent)
{
    struct sales *k=calloc(1,sizeof *k);if(!k)return NULL;
    init_base(&k->b,&parent->c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlSales",sales_update,k,sales_release);if(!w){free(k);return NULL;}
    k->b.self=w;arena_sales(k)->_salesItemList=(int32_t)dw4_shopstock_acquire(parent->c.stock,parent->c.mode).off;
    if(!arena_sales(k)->_salesItemList){dw4_menu_window_close(w);return NULL;}dw4_menu_window_data(w)->_playerNo=parent->c.view.player;dw4_menu_window_data(w)->_retCode=-1;return w;
}

/* ---- Roots: Device (43cc20) and Junk (42bc70) ---- */
struct root {
    struct base b;
     /* _junkGift read when the shop opened (Junk) */
};
static beNDMWWindowCtrl *arena_root(const struct root *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWWindowCtrl,p->b.self->object);}

static int open_sales(struct root *r)
{return add_child(&r->b,sales_open(&r->b),"goods list could not be opened");}
static int device_step(struct root *r,dw4_menu_window *w)
{
    struct base *b=&r->b;
    static const int32_t menus[3]={0x672,0x6D6,0x73A};
    switch(arena_root(r)->_st1) {
    case 0:
        if(arena_root(r)->_st2==0){if(menu(b,menus[b->c.mode-6],3))return -1;arena_root(r)->_st2=1;return 0;}
        if(!changed(b))return 0;
        if(arena_base(b)->_retCode==0 || arena_base(b)->_retCode==1){arena_root(r)->_st1=arena_base(b)->_retCode+1;arena_root(r)->_st2=0;}
        else advance(w);
        return 0;
    case 1:
        if(arena_root(r)->_st2==0){if(open_sales(r))return -1;arena_root(r)->_st2=1;return 0;}
        if(changed(b)){arena_root(r)->_st1=0;arena_root(r)->_st2=0;}
        return 0;
    case 2:
        if(arena_root(r)->_st2==0) {
            dw4_diskshop_context ds=disk_context(b);
            if(add_child(b,dw4_diskshop_sell_window_open(&ds),"sell window could not be opened"))return -1;
            arena_root(r)->_st2=1;return 0;
        }
        if(changed(b)){arena_root(r)->_st1=0;arena_root(r)->_st2=0;}
        return 0;
    }
    return 0;
}
/* 42bc70 main 1: after a donation, a stock-tier threshold crossed by the new investment runs junkexit.lua and
 * announces it (main 3); otherwise the menu returns. */
static int junk_donated(struct root *r,int32_t amount)
{
    static const int32_t thresholds[]={1000,6000,26000,86000,206000,456000,956000,1956000,3956000};
    struct base *b=&r->b;int result;
    const int32_t *counter;size_t n;
    if(dw4_playertransactions_junk_donate(b->c.view.players,b->c.view.player,amount,&result) || !result)
        return bfail(b,"donation transaction failed");
    if(subwnd(b,"UPDATE"))return -1;
    counter=dw4_property_array(dw4_playerrecords_get(b->c.view.players,"GETCOMMON",0),"COUNTER",&n);
    if(!counter || n<2)return bfail(b,"common COUNTER unavailable");
    arena_root(r)->_st1=0;arena_root(r)->_st2=0;
    for(size_t i=0;i<sizeof thresholds/sizeof *thresholds;i++) {
        if(DW4_ARENA_OBJ(r->b.self->arena,beNDMWShopJunk,r->b.self->object)->_totalGift<thresholds[i] && counter[1]>=thresholds[i]) {
            if(dw4_scriptengine_run(b->c.view.engine,"junkexit.lua")) {
                snprintf(b->error,sizeof b->error,"SHOP: junkexit.lua: %.200s",dw4_scriptengine_error(b->c.view.engine));
                return -1;
            }
            arena_root(r)->_st1=3;return 0;
        }
    }
    return 0;
}
static int junk_step(struct root *r,dw4_menu_window *w)
{
    struct base *b=&r->b;
    switch(arena_root(r)->_st1) {
    case 0:
        if(arena_root(r)->_st2==0){if(menu(b,0x79E,3))return -1;arena_root(r)->_st2=1;return 0;}
        if(!changed(b))return 0;
        if(arena_base(b)->_retCode==0 || arena_base(b)->_retCode==1){arena_root(r)->_st1=arena_base(b)->_retCode+1;arena_root(r)->_st2=0;}
        else advance(w);
        return 0;
    case 1:
        if(arena_root(r)->_st2==0) {
            dw4_bankshop_context bc=bank_context(b);
            arena_base(b)->_retCode=-1;
            if(add_child(b,dw4_bankshop_editor_open(&bc,b->self,2),"donation editor could not be opened"))return -1;
            arena_root(r)->_st2=1;return 0;
        }
        if(!changed(b))return 0;
        if(arena_base(b)->_retCode!=-1)return junk_donated(r,arena_base(b)->_retCode);
        arena_root(r)->_st1=0;arena_root(r)->_st2=0;return 0;
    case 2:
        if(arena_root(r)->_st2==0){if(open_sales(r))return -1;arena_root(r)->_st2=1;return 0;}
        if(changed(b)){arena_root(r)->_st1=0;arena_root(r)->_st2=0;}
        return 0;
    case 3:
        if(arena_root(r)->_st2==0){if(notice(b,0x7B2))return -1;arena_root(r)->_st2=1;return 0;}
        if(changed(b))advance(w);
        return 0;
    }
    return 0;
}
static int root_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct root *r=w->user;struct base *b=&r->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        if(dw4_menu_window_data(w)->_st0==0){
            advance(w);arena_root(r)->_st1=0;arena_root(r)->_st2=0;
            if(b->c.mode==9)DW4_ARENA_OBJ(r->b.self->arena,beNDMWShopJunk,r->b.self->object)->_totalGift=dw4_shopstock_gift(b->c.stock);
        }
        if(dw4_menu_window_data(w)->_st0==1)rc=b->c.mode==9?junk_step(r,w):device_step(r,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"shop failed");
    return rc;
}
static int32_t *root_stock(struct root *r)
{return r->b.c.mode==9?&DW4_ARENA_OBJ(r->b.self->arena,beNDMWShopJunk,r->b.self->object)->_junkItemList:&DW4_ARENA_OBJ(r->b.self->arena,beNDMWShopDevice,r->b.self->object)->_salesList;}
static void root_release(void *u)
{struct root *r=u;dw4_property_list_release(r->b.self->arena,al_handle(*root_stock(r)));release(u);}
dw4_menu_window *dw4_equipshop_window_open(const dw4_equipshop_context *c)
{
    if(!valid(c))return NULL;
    struct root *r=calloc(1,sizeof *r);if(!r)return NULL;
    init_base(&r->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class(c->mode==9?"beNDMWShopJunk":"beNDMWShopDevice",root_update,r,root_release);if(!w){free(r);return NULL;}
    r->b.self=w;*root_stock(r)=(int32_t)dw4_shopstock_acquire(c->stock,c->mode).off;
    if(!*root_stock(r)){dw4_menu_window_close(w);return NULL;}dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=-1;return w;
}
int dw4_equipshop_window_state(const dw4_menu_window *w,dw4_equipshop_state *out)
{
    if(!w || !out || w->update!=root_update)return -1;
    const struct root *r=w->user;
    *out=(dw4_equipshop_state){dw4_menu_window_data(w)->_st0,arena_root(r)->_st1,arena_root(r)->_st2,0,0,0};
    for(size_t i=0;i<dw4_menu_window_count(w);i++) {
        const dw4_menu_window *c=w->children[i];
        if(c->update==sales_update){const struct sales *k=c->user;out->page=arena_sales(k)->_nowPage;out->cursor=arena_sales(k)->_cursor;out->notice=k->notice;}
    }
    return 0;
}
