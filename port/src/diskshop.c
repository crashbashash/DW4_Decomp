/* beNDMWShopCtrl50 update 42a2e0..42b7f8 and its sell branch. Field names follow the BANK controller: the window
 * state is the primary state (+1c), main/sub are +20/+24, +28 the "last"/argument word, +30 _retCode (written into
 * ret.selection by the child selectors), +50 the child-count snapshot, +54 cursor, +58 selected record, +5c held
 * count, +60 quantity, +64 unit price. Completion of a child is a change in the child count, as in retail. */
#include "dw4/diskshop.h"
#include "arenalist.h"
#include "dw4/statusui.h"
#include "dw4/statuscontent.h"
#include "dw4/playertransactions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct base {
    dw4_diskshop_context c;
    dw4_menu_window *self,*content;
    char error[256];
};
static beNDMWWindowCtrl *arena_base(const struct base *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWWindowCtrl,p->self->object);}

static int bfail(struct base *b,const char *what){snprintf(b->error,sizeof b->error,"DISK: %s",what);return -1;}
static int changed(const struct base *b){return dw4_menu_window_count(b->self)!=(size_t)arena_base(b)->_nowProcKazu;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static int cmd(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static int put(struct base *b,int op,const char *g,const char *n,const char *k,const char *v,int call)
{return dw4_statusui_emit(b->content,op,g,n,k,v,call)?bfail(b,"content resource could not be updated"):0;}
static int tell(struct base *b,const char *model,const char *sequence)
{return dw4_statusui_call(&b->c.view,0,"MODELCTRL",model,0,sequence,NULL,b->error,sizeof b->error)<0?-1:0;}
static int update_stats(struct base *b)
{return dw4_statusui_call(&b->c.view,0,"SUBWND",NULL,b->c.view.player,"UPDATE",NULL,b->error,sizeof b->error)<0?-1:0;}
static dw4_property_folder *folder(struct base *b)
{return dw4_playerrecords_get(b->c.view.players,"GETPLAYER",b->c.view.player);}
static int add_child(struct base *b,dw4_menu_window *w,const char *what)
{
    if(!w)return bfail(b,what);
    if(dw4_menu_window_add(b->self,w)){dw4_menu_window_close(w);return bfail(b,"child window could not be attached");}
    arena_base(b)->_nowProcKazu=dw4_menu_window_count(b->self);return 0;
}
typedef int (*selector_init)(void *,dw4_statusview_io,void *);
static int selector(struct base *b,int kind,int call,int rows,int selected,float x,float y,int variant,
    const uint8_t *enabled,selector_init init)
{
    dw4_statusview_context c=b->c.view;c.parent=NULL;c.parent_window=b->self;c.callno=call;c.rows=rows;c.selected=selected;c.variant=variant;
    c.position[0]=x;c.position[1]=y;c.position[2]=0;c.enabled=enabled;c.selection_initialize=init;c.user=b;
    c.initialize=NULL;c.refresh=NULL;
    return add_child(b,dw4_statusview_window_open(kind,&c),"selector window could not be opened");
}
static int notice(struct base *b,int call){return selector(b,DW4_STATUS_SHOPSELECT00,call,1,0,0,0,0,NULL,NULL);}
static int menu(struct base *b,int call,int rows){return selector(b,DW4_STATUS_XDATAMENU,call,rows,0,0,0,0,NULL,NULL);}
/* 42bae0 / 435250: the i_stcursor04 marker opens at (-121,128,0) with SQ_OPEN%02d, or closes when running. */
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
static const dw4_database *con(const struct base *b){return dw4_databases_get(b->c.databases,"conItem");}
static int con_number(const struct base *b,int32_t row,const char *key,int32_t *out)
{return dw4_database_number(con(b),row,key,out)<0?-1:0;}
/* The twelve DISKFOLDER entries, validated as the other disk code does. */
static const dw4_item_record *disks(struct base *b)
{
    size_t n;const dw4_item_record *v=dw4_property_items(folder(b),"DISKFOLDER",&n);
    if(!v || n!=12){bfail(b,"DISKFOLDER unavailable");return NULL;}
    for(size_t i=0;i<n;i++)if(v[i].kind!=4 || v[i].revision<0 || v[i].revision>9){bfail(b,"DISKFOLDER record is invalid");return NULL;}
    return v;
}
static int bit(struct base *b,int32_t *out)
{return dw4_property_number(folder(b),"BIT",out)?bfail(b,"BIT unavailable"):0;}
/* The shared quantity labels (0x5DE / 0x5E1) are hidden by 42b9d0 and 438050. */
static int set_quantity_texts(struct base *b,const char *group,int32_t quantity,int32_t unit)
{
    char text[16];
    snprintf(text,sizeof text,"%d",quantity);
    if(put(b,DW4_VIEW_SET_TEXT,group,"font010",NULL,text,0))return -1;
    snprintf(text,sizeof text,"%d",(int32_t)((uint32_t)quantity*(uint32_t)unit));
    return put(b,DW4_VIEW_SET_TEXT,group,"font021",NULL,text,0);
}
static int hide_quantity_texts(struct base *b,const char *group)
{
    static const char *const fonts[]={"font020","font010","font021"};
    for(unsigned i=0;i<3;i++)if(put(b,DW4_VIEW_SWITCH,group,fonts[i],NULL,"DISPOFF",0))return -1;
    return 0;
}
static int close_children(struct base *b)
{
    for(size_t i=0;i<dw4_menu_window_count(b->self);i++)dw4_menu_window_remove(b->self->children[i]);
    return 0;
}
/* The primary states shared by all four windows: 2 closes the content owner and children, 3 waits. */
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
static void init_base(struct base *b,const dw4_diskshop_context *c)
{b->c=*c;b->c.view.parent=NULL;}
static int valid(const dw4_diskshop_context *c)
{
    return c && c->databases && c->view.sd && c->view.engine && c->view.players && c->view.player>=0 && c->view.player<4;
}

/* ---- Sell branch: DeviceSell (4353e0) ---- */
struct devsell {
    struct base b;

    dw4_item_record items[36];size_t count;
    dw4_statuspage_input input;
};
static beNDMWShopCtrlDeviceSell *arena_devsell(const struct devsell *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlDeviceSell,p->b.self->object);}

static const uint8_t *dev_flags(const struct devsell *d)
{return al_data(d->b.self->arena,arena_devsell(d)->_decideList,1);}
static void dev_release(void *u)
{struct devsell *d=u;al_drop(d->b.self->arena,&arena_devsell(d)->_decideList);release(u);}
static int dev_items(struct devsell *d)
{
    size_t n;const dw4_item_record *v=dw4_property_items(folder(&d->b),"DEVICEFOLDER",&n);
    if((!v && n) || n>36)return bfail(&d->b,"DEVICEFOLDER unavailable");
    if(n)memcpy(d->items,v,n*sizeof *v);
    d->count=n;return 0;
}
/* 4367c0: page count, the current page's row count and its decide list (unequipped with a positive KAITORI). */
static int dev_layout(struct devsell *d,int *rows)
{
    if(dev_items(d))return -1;
    arena_devsell(d)->_maxPage=(int32_t)(d->count/12+(d->count%12!=0));
    int remaining=(int)d->count-arena_devsell(d)->_nowPage*12;
    *rows=remaining>=12?12:remaining;
    uint8_t flags[12]={0};
    for(unsigned i=0;i<12;i++) {
        size_t index=(size_t)arena_devsell(d)->_nowPage*12+i;int32_t price;
        if(index>=d->count)continue;
        if(dw4_statuscontent_kaitori(d->b.c.databases,d->items+index,&price))return bfail(&d->b,"KAITORI unavailable");
        flags[i]=!d->items[index].equipped && price>0;
    }
    if(*rows<1)return bfail(&d->b,"the sell list is empty");
    int32_t h=al_new(d->b.self->arena,"igBoolList",1,*rows,flags);if(!h)return bfail(&d->b,"decide list allocation failed");
    al_drop(d->b.self->arena,&arena_devsell(d)->_decideList);arena_devsell(d)->_decideList=h;return 0;
}
static int dev_render(struct devsell *d,int rows,int description)
{
    if(!d->b.content)return bfail(&d->b,"content window unavailable");
    return dw4_statuscontent_sell_device(d->b.c.databases,d->items,d->count,dev_flags(d),arena_devsell(d)->_nowPage,(int)arena_devsell(d)->_maxPage,arena_base(&(d->b))->_retCode,
        rows,description,dw4_statusview_window_emit,d->b.content)?bfail(&d->b,"sell list text refresh failed"):0;
}
static int dev_setup(void *u,dw4_statusview_io io,void *iou)
{
    struct devsell *d=u;
    if(cmd(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin","SQ_AWINOPEN","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorright",arena_devsell(d)->_maxPage<2?"SQ_HIDE/V<236,25,0>":"SQ_SELECT/V<236,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x676) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x3E8))return -1;
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
static int dev_page_io(void *u,const char *model,const char *sequence){struct devsell *d=u;return tell(&d->b,model,sequence);}
static int dev_step(struct devsell *d,dw4_menu_window *w)
{
    struct base *b=&d->b;
    switch(arena_devsell(d)->_st1) {
    case 4:
        if(arena_devsell(d)->_st2==0) {
            int rows;
            if(dev_layout(d,&rows) || selector(b,DW4_STATUS_SELECTE1,0,rows,arena_devsell(d)->_cursor,-121,128,0,dev_flags(d),list_prompt))return -1;
            arena_base(b)->_retCode=arena_devsell(d)->_cursor;arena_devsell(d)->_st2=1;
        }
        if(arena_devsell(d)->_st2==1) {
            int rows;
            if(dev_layout(d,&rows) || dev_render(d,rows,1))return -1;
            arena_devsell(d)->_st2=2;arena_devsell(d)->_st3=0;return 0;
        }
        if(!changed(b)) {
            dw4_menu_window *child=dw4_menu_window_count(w)?w->children[0]:NULL;int32_t selected=arena_base(b)->_retCode;
            if(selected==-1 || !child)return 0;
            if(selected!=arena_devsell(d)->_st3){int rows;if(dev_layout(d,&rows) || dev_render(d,rows,1))return -1;arena_devsell(d)->_st3=selected;return 0;}
            if(dw4_statusview_selector_ready(child)==1) {
                int turn=dw4_statuspage_turn(&arena_devsell(d)->_nowPage,(int)arena_devsell(d)->_maxPage,0,&d->input,dev_page_io,d);
                if(turn==0)turn=dw4_statuspage_turn(&arena_devsell(d)->_nowPage,(int)arena_devsell(d)->_maxPage,1,&d->input,dev_page_io,d);
                if(turn<0)return bfail(b,"page request failed");
                if(turn) {
                    int rows;
                    if(dev_layout(d,&rows) || dw4_statusview_selector_restart(child,rows,dev_flags(d)))return bfail(b,"selector repage failed");
                    arena_devsell(d)->_st2=1;
                }
            }
            return 0;
        }
        if(arena_base(b)->_retCode!=-1) {
            arena_devsell(d)->_cursor=arena_base(b)->_retCode;arena_devsell(d)->_st1=5;arena_devsell(d)->_st2=0;
            return cursor(b,arena_devsell(d)->_cursor);
        }
        advance(w);return 0;
    case 5: {
        if(arena_devsell(d)->_st2==0){if(notice(b,0x619))return -1;arena_devsell(d)->_st2=1;return 0;}
        if(arena_devsell(d)->_st2==1){if(!changed(b))return 0;if(menu(b,0x61A,2))return -1;arena_devsell(d)->_st2=2;return 0;}
        if(!changed(b))return 0;
        size_t index=(size_t)arena_devsell(d)->_cursor+(size_t)arena_devsell(d)->_nowPage*12;
        int exit=0;
        if(arena_base(b)->_retCode==0) {
            if(dev_items(d))return -1;
            if(index<d->count) {
                int32_t price;int result;
                if(dw4_statuscontent_kaitori(b->c.databases,d->items+index,&price))return bfail(b,"KAITORI unavailable");
                if(dw4_playertransactions_sell_item(b->c.view.players,b->c.view.player,index,price,&result) || !result)
                    return bfail(b,"sell transaction failed");
                if(update_stats(b) || dev_items(d))return -1;
                if(d->count==0)exit=1;
                else {
                    if(index>=d->count){if(arena_devsell(d)->_cursor==0){if(arena_devsell(d)->_nowPage>0)arena_devsell(d)->_nowPage--;}else arena_devsell(d)->_cursor--;}
                    if(arena_devsell(d)->_nowPage==0 && tell(b,"i_stcursorleft","SQ_HIDE"))return -1;
                    if((size_t)(arena_devsell(d)->_nowPage+1)*12>=d->count && tell(b,"i_stcursorright","SQ_HIDE"))return -1;
                }
            }else exit=1;
        }
        if(exit)advance(w);
        arena_devsell(d)->_st1=4;arena_devsell(d)->_st2=0;return cursor(b,-1);
    }
    }
    return 0;
}
static int dev_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct devsell *d=w->user;struct base *b=&d->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        memset(&d->input,0,sizeof d->input);
        if(b->c.input && b->c.input(b->c.user,b->c.view.player,&d->input))rc=bfail(b,"pad input unavailable");
        if(!rc && dw4_menu_window_data(w)->_st0==0) {
            int rows;
            if(dev_layout(d,&rows) || dw4_statusui_open(&b->c.view,dev_setup,d,&b->content,b->error,sizeof b->error))rc=-1;
            else{advance(w);arena_devsell(d)->_st1=4;arena_devsell(d)->_st2=0;arena_devsell(d)->_nowPage=0;arena_devsell(d)->_cursor=0;}
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1)rc=dev_step(d,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"DISK device sell failed");
    return rc;
}
static dw4_menu_window *devsell_open(const dw4_diskshop_context *c)
{
    if(!c->input)return NULL;
    struct devsell *d=calloc(1,sizeof *d);if(!d)return NULL;
    init_base(&d->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlDeviceSell",dev_update,d,dev_release);if(!w){free(d);return NULL;}
    d->b.self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=-1;return w;
}

/* ---- Sell branch: DiskSell (436ac0) ---- */
struct disksell {
    struct base b;

};
static beNDMWShopCtrlDiskSell *arena_disksell(const struct disksell *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlDiskSell,p->b.self->object);}

static int disk_setup(void *u,dw4_statusview_io io,void *iou)
{
    (void)u;
    if(cmd(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin","SQ_WAIT","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorright","SQ_HIDE/V<236,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x3E9))return -1;
    for(unsigned i=0;i<12;i++) {
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) ||
           cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT15",font,"CENTER"," ",0) ||
           cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT17",font,"RIGHT"," ",0))return -1;
    }
    return 0;
}
static int disk_render(struct disksell *d,int rows,int description)
{
    const dw4_item_record *v=disks(&d->b);
    if(!v)return -1;
    return dw4_statuscontent_sell_disk(d->b.c.databases,v,12,arena_base(&(d->b))->_retCode,rows,description,&arena_disksell(d)->_tanka,
        dw4_statusview_window_emit,d->b.content)?bfail(&d->b,"disk list text refresh failed"):0;
}
static int disk_step(struct disksell *d,dw4_menu_window *w)
{
    struct base *b=&d->b;
    switch(arena_disksell(d)->_st1) {
    case 6:
        if(arena_disksell(d)->_st2==0) {
            const dw4_item_record *v=disks(b);uint8_t enabled[12];
            if(!v || tell(b,"j_shwin","SQ_EWINOPEN") || cursor(b,-1))return -1;
            for(unsigned i=0;i<12;i++)enabled[i]=v[i].revision>0;
            if(selector(b,DW4_STATUS_SELECTE1,0,12,arena_disksell(d)->_cursor,-121,128,0,enabled,list_prompt))return -1;
            arena_base(b)->_retCode=arena_disksell(d)->_cursor;
            if(put(b,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x676))return -1;
            arena_disksell(d)->_st2=1;
        }
        if(arena_disksell(d)->_st2==1){if(disk_render(d,1,1))return -1;arena_disksell(d)->_st2=2;arena_disksell(d)->_st3=0;return 0;}
        if(!changed(b)) {
            if(arena_base(b)->_retCode!=-1 && arena_disksell(d)->_st3!=arena_base(b)->_retCode){if(disk_render(d,0,1))return -1;arena_disksell(d)->_st3=arena_base(b)->_retCode;}
            return 0;
        }
        if(arena_base(b)->_retCode!=-1) {
            const dw4_item_record *v=disks(b);
            if(!v)return -1;
            arena_disksell(d)->_cursor=arena_base(b)->_retCode;arena_disksell(d)->_st1=7;arena_disksell(d)->_st2=0;arena_disksell(d)->_maxSell=v[arena_disksell(d)->_cursor].revision;
            if(cursor(b,arena_disksell(d)->_cursor))return -1;
            if(arena_disksell(d)->_maxSell==0){arena_disksell(d)->_st1=6;arena_disksell(d)->_st2=0;}
            return 0;
        }
        advance(w);return cursor(b,-1);
    case 7:
        if(arena_disksell(d)->_st2==0) {
            if(tell(b,"j_shwin","SQ_BWINOPEN") || selector(b,DW4_STATUS_SHOPSELECT52,0,arena_disksell(d)->_maxSell,arena_disksell(d)->_maxSell-1,52,-104,arena_disksell(d)->_maxSell,NULL,
                   NULL))return -1;
            if(put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) || put(b,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x624) ||
               put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT30","font010",NULL,NULL,0) || put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT30","font021",NULL,NULL,0) ||
               put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT30","font020",NULL,NULL,0) || put(b,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x5E1))return -1;
            arena_base(b)->_retCode=arena_disksell(d)->_maxSell-1;
            if(set_quantity_texts(b,"STWINFONT30",arena_disksell(d)->_maxSell-arena_base(b)->_retCode,arena_disksell(d)->_tanka))return -1;
            arena_disksell(d)->_st2=1;arena_disksell(d)->_st3=0;return 0;
        }
        if(!changed(b)) {
            if(arena_base(b)->_retCode!=-1) {
                if(arena_disksell(d)->_st3!=arena_base(b)->_retCode && set_quantity_texts(b,"STWINFONT30",arena_disksell(d)->_maxSell-arena_base(b)->_retCode,arena_disksell(d)->_tanka))return -1;
                arena_disksell(d)->_st3=arena_base(b)->_retCode;
            }
            return 0;
        }
        if(arena_base(b)->_retCode!=-1){arena_disksell(d)->_kazu=arena_disksell(d)->_maxSell-arena_base(b)->_retCode;arena_disksell(d)->_st1=8;arena_disksell(d)->_st2=0;return 0;}
        if(hide_quantity_texts(b,"STWINFONT30"))return -1;
        arena_disksell(d)->_st1=6;arena_disksell(d)->_st2=0;return 0;
    case 8:
        if(arena_disksell(d)->_st2==0){if(notice(b,0x619))return -1;arena_disksell(d)->_st2=1;return 0;}
        if(arena_disksell(d)->_st2==1){if(!changed(b))return 0;if(menu(b,0x61A,2))return -1;arena_disksell(d)->_st2=2;return 0;}
        if(!changed(b))return 0;
        if(hide_quantity_texts(b,"STWINFONT30"))return -1;
        if(arena_base(b)->_retCode==0) {
            int result;
            if(dw4_playertransactions_disk_sell(b->c.view.players,b->c.view.player,(size_t)arena_disksell(d)->_cursor,arena_disksell(d)->_kazu,arena_disksell(d)->_tanka,&result) || !result)
                return bfail(b,"disk sell transaction failed");
            if(update_stats(b))return -1;
        }
        arena_disksell(d)->_st1=6;arena_disksell(d)->_st2=0;return 0;
    }
    return 0;
}
static int disk_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct disksell *d=w->user;struct base *b=&d->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        if(dw4_menu_window_data(w)->_st0==0) {
            if(dw4_statusui_open(&b->c.view,disk_setup,d,&b->content,b->error,sizeof b->error))rc=-1;
            else{advance(w);arena_disksell(d)->_st1=6;arena_disksell(d)->_st2=0;arena_disksell(d)->_cursor=0;}
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1)rc=disk_step(d,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"DISK disk sell failed");
    return rc;
}
static dw4_menu_window *disksell_open(const dw4_diskshop_context *c)
{
    struct disksell *d=calloc(1,sizeof *d);if(!d)return NULL;
    init_base(&d->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlDiskSell",disk_update,d,release);if(!w){free(d);return NULL;}
    d->b.self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=-1;return w;
}

/* ---- Sell branch: ShopCtrlSell (434790) ---- */
struct sell {struct base b;};
static beNDMWShopCtrlSell *arena_sell(const struct sell *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlSell,p->b.self->object);}

static int sell_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct sell *s=w->user;struct base *b=&s->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        if(dw4_menu_window_data(w)->_st0==0) {
            /* 434790 state 0: device and disk availability pick the first menu, or the nothing-to-sell notice. */
            const dw4_item_record *v=disks(b);size_t n;int any=0;
            if(!v || dw4_property_item_count(folder(b),"DEVICEFOLDER",&n)){rc=-1;if(v)bfail(b,"DEVICEFOLDER unavailable");}
            else {
                for(size_t i=0;i<12;i++)if(v[i].revision>0)any=1;
                arena_sell(s)->_entCode=n==0?1:!any?2:0;
                advance(w);arena_sell(s)->_st1=(n==0 && !any)?3:0;arena_sell(s)->_st2=0;
            }
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1) {
            switch(arena_sell(s)->_st1) {
            case 0:
                if(arena_sell(s)->_st2==0) {
                    uint8_t flags[2]={arena_sell(s)->_entCode!=1,arena_sell(s)->_entCode!=2};
                    if(selector(b,DW4_STATUS_SHOPSELECTB0,0,2,0,0,0,0,arena_sell(s)->_entCode?flags:NULL,NULL)){rc=-1;break;}
                    arena_sell(s)->_st2=1;
                }else if(changed(b)) {
                    if(arena_base(b)->_retCode==0 || arena_base(b)->_retCode==1){arena_sell(s)->_st1=arena_base(b)->_retCode+1;arena_sell(s)->_st2=0;}
                    else advance(w);
                }
                break;
            case 1: case 2:
                if(arena_sell(s)->_st2==0) {
                    dw4_menu_window *child=arena_sell(s)->_st1==1?devsell_open(&b->c):disksell_open(&b->c);
                    if(add_child(b,child,"sell list could not be opened")){rc=-1;break;}
                    arena_sell(s)->_st2=1;
                }else if(changed(b)){dw4_menu_window_data(w)->_st0=0;} /* retail unk1c=0: recompute availability and reopen the menu */
                break;
            case 3:
                if(arena_sell(s)->_st2==0){if(notice(b,0x628)){rc=-1;break;}arena_sell(s)->_st2=1;}
                else if(changed(b))advance(w);
                break;
            }
        }
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"DISK sell failed");
    return rc;
}
dw4_menu_window *dw4_diskshop_sell_window_open(const dw4_diskshop_context *c)
{
    struct sell *s=calloc(1,sizeof *s);if(!s)return NULL;
    init_base(&s->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlSell",sell_update,s,release);if(!w){free(s);return NULL;}
    s->b.self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=-1;return w;
}

/* ---- ShopCtrl50 ---- */
struct buy {
    struct base b;
    int32_t notice;
    int quantity_texts;
};
static beNDMWShopCtrl50 *arena_buy(const struct buy *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrl50,p->b.self->object);}

static int buy_list_setup(void *u,dw4_statusview_io io,void *iou)
{
    struct buy *k=u;
    if(cmd(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin","SQ_WAIT","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorright","SQ_HIDE/V<236,25,0>","SQ_CLOSE",0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x5DD))return -1;
    for(int i=0;i<10;i++) {
        char font[16],price[16];int32_t hanbai;
        snprintf(font,sizeof font,"font%03d",i);
        const char *name=dw4_database_string(con(&k->b),i,"NAME");
        if(!name || con_number(&k->b,i,"HANBAI",&hanbai))return bfail(&k->b,"conItem row is unavailable");
        snprintf(price,sizeof price,"%d",hanbai);
        if(cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT",name,0) ||
           cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT17",font,"RIGHT",price,0))return -1;
    }
    return cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0);
}
static int buy_prompt(void *u,dw4_statusview_io io,void *iou)
{(void)u;return cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
    cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x611);}
static int quantity_prompt(void *u,dw4_statusview_io io,void *iou)
{(void)u;return cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
    cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x624);}
static int held(struct buy *k,int32_t item)
{
    const dw4_item_record *v=disks(&k->b);
    if(!v)return -1;
    for(size_t i=0;i<12;i++)if(v[i].record==item)return v[i].revision;
    return 0;
}
static int buy_describe(struct buy *k)
{
    struct base *b=&k->b;const char *txt=dw4_database_string(con(b),arena_base(b)->_retCode,"TXT");
    if(!txt)return bfail(b,"conItem description unavailable");
    return put(b,DW4_VIEW_SET_TEXT,"STWINFONT29","font000",NULL,txt,0) || put(b,DW4_VIEW_SWITCH,"STWINFONT29","font000",NULL,"DISPON",0);
}
/* 42b880: quantity and total, with HANBAI read for the listed disk each time. */
static int buy_quantity_texts(struct buy *k)
{
    int32_t hanbai;
    if(con_number(&k->b,arena_buy(k)->_conItemNo,"HANBAI",&hanbai))return bfail(&k->b,"HANBAI unavailable");
    return set_quantity_texts(&k->b,"STWINFONT32",(9-arena_buy(k)->_diskCnt)-arena_base(&(k->b))->_retCode,hanbai);
}
static int buy_hide_texts(struct buy *k){return k->quantity_texts?hide_quantity_texts(&k->b,"STWINFONT32"):0;}
static int buy_step(struct buy *k,dw4_menu_window *w)
{
    struct base *b=&k->b;
    switch(arena_buy(k)->_st1) {
    case -1: /* retail unk1c=0: queued models close and text clears before the menu returns */
        if(arena_buy(k)->_st2==0){
            if(b->content && dw4_statusui_close(b->content,b->error,sizeof b->error))return -1;
            k->quantity_texts=0;arena_buy(k)->_st2=1;
        }
        if(dw4_statusui_drain(&b->content,b->error,sizeof b->error))return -1;
        if(b->content)return 0;
        arena_buy(k)->_st1=0;arena_buy(k)->_st2=0;return 0;
    case 0:
        if(arena_buy(k)->_st2==0){if(menu(b,0x60E,3))return -1;arena_buy(k)->_st2=1;return 0;}
        if(!changed(b))return 0;
        if(arena_base(b)->_retCode==0){arena_buy(k)->_st1=1;arena_buy(k)->_st2=0;arena_buy(k)->_cursor=0;}
        else if(arena_base(b)->_retCode==1){arena_buy(k)->_st1=4;arena_buy(k)->_st2=0;}
        else advance(w);
        return 0;
    case 1:
        if(arena_buy(k)->_st2==0) {
            if(!b->content){if(dw4_statusui_open(&b->c.view,buy_list_setup,k,&b->content,b->error,sizeof b->error))return -1;}
            else if(tell(b,"j_shwin","SQ_WAIT") || dw4_statusui_positioned(&b->c.view,"i_stcursorleft",0,"SQ_HIDE",-146,25,0,b->error,sizeof b->error) ||
                    dw4_statusui_positioned(&b->c.view,"i_stcursorright",0,"SQ_HIDE",236,25,0,b->error,sizeof b->error) ||
                    put(b,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x5DD))return -1;
            arena_buy(k)->_st2=1;
        }
        if(arena_buy(k)->_st2==1) {
            if(cursor(b,-1) || tell(b,"j_shwin","SQ_CWINOPEN") ||
               selector(b,DW4_STATUS_SELECTE1,0,10,arena_buy(k)->_cursor,-121,128,0,NULL,buy_prompt))return -1;
            arena_base(b)->_retCode=arena_buy(k)->_cursor;arena_buy(k)->_st2=2;
        }
        if(arena_buy(k)->_st2==2) {
            if(arena_base(b)->_retCode!=-1 && buy_describe(k))return -1;
            arena_buy(k)->_st3=arena_base(b)->_retCode;arena_buy(k)->_st2=3;
        }
        if(!changed(b)) {
            if(arena_base(b)->_retCode!=-1 && arena_base(b)->_retCode!=arena_buy(k)->_st3)arena_buy(k)->_st2=2;
            return 0;
        }
        if(arena_base(b)->_retCode!=-1) {
            arena_buy(k)->_cursor=arena_base(b)->_retCode;arena_buy(k)->_conItemNo=arena_base(b)->_retCode;
            if(cursor(b,arena_buy(k)->_cursor))return -1;
            int owned=held(k,arena_buy(k)->_conItemNo);
            if(owned<0)return -1;
            arena_buy(k)->_diskCnt=owned;arena_buy(k)->_st2=0;
            if(owned==9){arena_buy(k)->_st1=5;k->notice=0x623;}else arena_buy(k)->_st1=2;
            return 0;
        }
        arena_buy(k)->_st1=-1;arena_buy(k)->_st2=0;return 0;
    case 2:
        if(arena_buy(k)->_st2==0) {
            if(tell(b,"j_shwin","SQ_DWINOPEN") ||
               selector(b,DW4_STATUS_SHOPSELECT52,0,9-arena_buy(k)->_diskCnt,8-arena_buy(k)->_diskCnt,52,-69,9-arena_buy(k)->_diskCnt,NULL,quantity_prompt))return -1;
            if(put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT32","font010",NULL,NULL,0) || put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT32","font021",NULL,NULL,0) ||
               put(b,DW4_VIEW_TRACK_TEXT,"STWINFONT32","font020",NULL,NULL,0) || put(b,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x5DE))return -1;
            k->quantity_texts=1;arena_base(b)->_retCode=8-arena_buy(k)->_diskCnt;
            if(buy_quantity_texts(k))return -1;
            arena_buy(k)->_st2=1;arena_buy(k)->_st3=0;return 0;
        }
        if(!changed(b)) {
            if(arena_base(b)->_retCode!=-1) {
                if(arena_buy(k)->_st3!=arena_base(b)->_retCode && buy_quantity_texts(k))return -1;
                arena_buy(k)->_st3=arena_base(b)->_retCode;
            }
            return 0;
        }
        if(arena_base(b)->_retCode!=-1){arena_buy(k)->_kazu=(9-arena_buy(k)->_diskCnt)-arena_base(b)->_retCode;arena_buy(k)->_st1=3;arena_buy(k)->_st2=0;return 0;}
        if(buy_hide_texts(k))return -1;
        arena_buy(k)->_st1=1;arena_buy(k)->_st2=1;return 0;
    case 3:
        if(arena_buy(k)->_st2==0) {
            int32_t balance;
            if(con_number(b,arena_buy(k)->_conItemNo,"HANBAI",&arena_buy(k)->_tanka) || bit(b,&balance))return -1;
            if(balance>=(int32_t)((uint32_t)arena_buy(k)->_tanka*(uint32_t)arena_buy(k)->_kazu))arena_buy(k)->_st2=1;
            else{arena_buy(k)->_st1=5;k->notice=0x622;arena_buy(k)->_st2=0;return 0;}
        }
        if(arena_buy(k)->_st2==1){if(notice(b,0x613))return -1;arena_buy(k)->_st2=2;return 0;}
        if(arena_buy(k)->_st2==2){if(!changed(b))return 0;if(menu(b,0x614,2))return -1;arena_buy(k)->_st2=3;return 0;}
        if(!changed(b))return 0;
        if(buy_hide_texts(k))return -1;
        if(arena_base(b)->_retCode==0) {
            int result;
            if(dw4_playertransactions_disk_buy(b->c.view.players,b->c.view.player,arena_buy(k)->_conItemNo,arena_buy(k)->_kazu,arena_buy(k)->_tanka,&result) || !result)
                return bfail(b,"buy transaction failed");
            if(update_stats(b))return -1;
        }
        arena_buy(k)->_st1=1;arena_buy(k)->_st2=1;return 0;
    case 4:
        if(arena_buy(k)->_st2==0){if(add_child(b,dw4_diskshop_sell_window_open(&b->c),"sell window could not be opened"))return -1;arena_buy(k)->_st2=1;return 0;}
        if(changed(b)){arena_buy(k)->_st1=0;arena_buy(k)->_st2=0;}
        return 0;
    case 5:
        if(arena_buy(k)->_st2==0){if(notice(b,k->notice))return -1;arena_buy(k)->_st2=1;return 0;}
        if(!changed(b))return 0;
        if(buy_hide_texts(k))return -1;
        arena_buy(k)->_st1=1;arena_buy(k)->_st2=0;return 0;
    }
    return 0;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct buy *k=w->user;struct base *b=&k->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        if(dw4_menu_window_data(w)->_st0==0){advance(w);arena_buy(k)->_st1=0;arena_buy(k)->_st2=0;}
        if(dw4_menu_window_data(w)->_st0==1)rc=buy_step(k,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"DISK failed");
    return rc;
}
dw4_menu_window *dw4_diskshop_window_open(const dw4_diskshop_context *c)
{
    if(!valid(c) || !c->input)return NULL;
    struct buy *k=calloc(1,sizeof *k);if(!k)return NULL;
    init_base(&k->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrl50",update,k,release);if(!w){free(k);return NULL;}
    k->b.self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=-1;return w;
}
int dw4_diskshop_window_state(const dw4_menu_window *w,dw4_diskshop_state *out)
{
    if(!w || !out || w->update!=update)return -1;
    const struct buy *k=w->user;
    *out=(dw4_diskshop_state){dw4_menu_window_data(w)->_st0,arena_buy(k)->_st1,arena_buy(k)->_st2,arena_buy(k)->_conItemNo,arena_buy(k)->_diskCnt,arena_buy(k)->_kazu};return 0;
}
