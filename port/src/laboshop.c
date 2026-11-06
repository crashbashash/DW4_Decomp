/* beNDMWShopCtrlDigilabo update 431760..432950 and its Evolve child (beNDMWShopCtrlEvolve
 * 42f710..430d20). Field names follow the other shop controllers: the primary state is +1c,
 * main/sub are +20/+24, +30 is _retCode (written into ret.selection by the child selectors), +50
 * the child-count snapshot. Completion of a child is a change in the child count, as in retail. */
#include "dw4/laboshop.h"
#include "shinkarecord.h"
#include "dw4/statusui.h"
#include "dw4/statuscontent.h"
#include "dw4/playerstats.h"
#include "dw4/playertransactions.h"
#include "dw4/statusequipmentmenu.h"
#include "dw4/scriptengine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct base {
    dw4_statusgear_context c;
    dw4_menu_window *self,*content;
    char error[256];
};
static beNDMWWindowCtrl *arena_base(const struct base *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWWindowCtrl,p->self->object);}

static int bfail(struct base *b,const char *what){snprintf(b->error,sizeof b->error,"LABO: %s",what);return -1;}
static int changed(const struct base *b){return dw4_menu_window_count(b->self)!=(size_t)arena_base(b)->_nowProcKazu;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static int cmd(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static int tell(struct base *b,const char *model,const char *sequence)
{return dw4_statusui_call(&b->c.view,0,"MODELCTRL",model,0,sequence,NULL,b->error,sizeof b->error)<0?-1:0;}
static int query(struct base *b,const char *model,const char *key,const char *value)
{return dw4_statusui_call(&b->c.view,1,"MODELCTRL",model,0,key,value,b->error,sizeof b->error);}
static int sound(struct base *b,const char *name)
{return dw4_statusui_call(&b->c.view,0,"SOUND",NULL,-1,"PLAY",name,b->error,sizeof b->error)<0?-1:0;}
static int update_stats(struct base *b)
{return dw4_statusui_call(&b->c.view,0,"SUBWND",NULL,b->c.view.player,"UPDATE",NULL,b->error,sizeof b->error)<0?-1:0;}
static int add_child(struct base *b,dw4_menu_window *w,const char *what)
{
    if(!w)return bfail(b,what);
    if(dw4_menu_window_add(b->self,w)){dw4_menu_window_close(w);return bfail(b,"child window could not be attached");}
    arena_base(b)->_nowProcKazu=dw4_menu_window_count(b->self);return 0;
}
typedef int (*selector_init)(void *,dw4_statusview_io,void *);
static int selector(struct base *b,int kind,int call,int rows,int selected,float x,float y,int variant)
{
    dw4_statusview_context c=b->c.view;c.parent=NULL;c.parent_window=b->self;c.callno=call;c.rows=rows;c.selected=selected;c.variant=variant;
    c.position[0]=x;c.position[1]=y;c.position[2]=0;c.enabled=NULL;c.selection_initialize=NULL;c.user=b;
    c.initialize=NULL;c.refresh=NULL;
    return add_child(b,dw4_statusview_window_open(kind,&c),"selector window could not be opened");
}
/* Select00 (STWINFONT29 notice, variant 1 uses the caller's font100), Select01 (two-choice STWINFONT29 menu),
 * Select03 (TALKFONT01 message) and Select02 (TALKFONT01 menu). */
static int notice(struct base *b,int call,int variant){return selector(b,DW4_STATUS_SHOPSELECT00,call,1,0,0,0,variant);}
static int menu(struct base *b,int call,int rows){return selector(b,DW4_STATUS_XDATAMENU,call,rows,0,0,0,0);}
static int talk_message(struct base *b,int call){return selector(b,DW4_STATUS_TALKSELECT03,call,1,0,0,0,0);}
static int talk_menu(struct base *b,int call,int rows){return selector(b,DW4_STATUS_TALKSELECT02,call,rows,0,0,0,0);}
static dw4_property_folder *folder(struct base *b)
{return dw4_playerrecords_get(b->c.view.players,"GETPLAYER",b->c.view.player);}
static int close_children(struct base *b)
{
    for(size_t i=0;i<dw4_menu_window_count(b->self);i++)dw4_menu_window_remove(b->self->children[i]);
    return 0;
}
/* The primary states shared by both windows: 2 closes the content owner and children, 3 waits for them. */
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
static const char *species_model(void *u,int32_t row){return dw4_database_string(dw4_databases_get(u,"shinka"),row,"MODEL_NAME");}
static const char *item_string(void *u,const dw4_item_record *i,const char *key){return dw4_statuscontent_item_string(u,i,key);}
static int sense(struct base *b,int32_t *species)
{return dw4_property_number(folder(b),"DIGIMONNO",species)?bfail(b,"DIGIMONNO unavailable"):0;}

/* ---- Evolve (42f710): the form list, the three confirmations and the commit (4313b0) ---- */
struct evolve {
    struct base b;
    int32_t rows;
    dw4_menu_window *result_owner;
    dw4_statuspage_input input;
};
static beNDMWShopCtrlEvolve *arena_evolve(const struct evolve *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlEvolve,p->b.self->object);}

static int ev_list(struct evolve *e)
{
    if(shinka_build(e->b.self->arena,&arena_evolve(e)->_shinkaCtrl,e->b.c.view.players,e->b.c.databases,e->b.c.view.player) || !shinka_count(e->b.self->arena,arena_evolve(e)->_shinkaCtrl))
        return bfail(&e->b,"the form list is unavailable");
    arena_evolve(e)->_maxPage=(int32_t)(shinka_count(e->b.self->arena,arena_evolve(e)->_shinkaCtrl)/8+(shinka_count(e->b.self->arena,arena_evolve(e)->_shinkaCtrl)%8!=0));
    if(arena_evolve(e)->_nowPage>=arena_evolve(e)->_maxPage)arena_evolve(e)->_nowPage=0;
    int remaining=(int)shinka_count(e->b.self->arena,arena_evolve(e)->_shinkaCtrl)-arena_evolve(e)->_nowPage*8;e->rows=remaining>=8?8:remaining;
    return 0;
}
static int ev_render(struct evolve *e,int rows,int detail)
{
    if(!e->b.content)return bfail(&e->b,"content window unavailable");
    return dw4_statuscontent_labo(e->b.c.view.players,e->b.c.databases,e->b.c.view.player,arena_evolve(e)->_nowPage,(int)arena_evolve(e)->_maxPage,arena_base(&(e->b))->_retCode,
        rows,detail,dw4_statusview_window_emit,e->b.content)?bfail(&e->b,"form list text refresh failed"):0;
}
static int ev_setup(void *u,dw4_statusview_io io,void *iou)
{
    struct evolve *e=u;
    static const char *const labels[16]={"font000","font001","font010","font011","font012","font013","font014",
        "font020","font021","font022","font023","font024","font025","font026","font027","font028"};
    static const char *const values[16]={"font030","font031","font040","font041","font042","font043","font044",
        "font050","font051","font052","font053","font054","font055","font056","font057","font058"};
    if(cmd(io,iou,DW4_VIEW_MODEL,NULL,"j_shwin",arena_evolve(e)->_maxPage>=2?"SQ_SINKAONOPEN":"SQ_SINKAOFFOPEN","SQ_CLOSE",0))return -1;
    if(arena_evolve(e)->_maxPage>=2 &&
       (cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-308,25,0>","SQ_CLOSE",0) ||
        cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_stcursorright","SQ_SELECT/V<-51,25,0>","SQ_CLOSE",0) ||
        cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT31","font000","RIGHT"," ",0) || cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT31","font001","RIGHT"," ",0)))return -1;
    if(cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x4E6) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT37","font000",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_TRACK_TEXT,"STWINFONT37","font001",NULL,NULL,0) ||
       cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x4C2))return -1;
    for(unsigned i=0;i<8;i++) {
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT20",font,"LEFT"," ",0) || cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT43",font,"LEFT"," ",0) ||
           cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT21",font,"RIGHT"," ",0))return -1;
    }
    for(unsigned i=0;i<16;i++)
        if(cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT22",labels[i],"LEFT"," ",0) || cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT22",values[i],"RIGHT"," ",0))return -1;
    return cmd(io,iou,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x4B2) ||
        cmd(io,iou,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0);
}
static int ev_band(void *u,dw4_statusview_io io,void *iou)
{(void)u;return cmd(io,iou,DW4_VIEW_MODEL,NULL,"i_messwn","SQ_STOPEN","SQ_STCLOSE",0);}
static int ev_page_io(void *u,const char *model,const char *sequence){struct evolve *e=u;return tell(&e->b,model,sequence);}
/* 4313b0: the recovered GAMERAM sequence as one atomic transaction, then SUBWND UPDATE. */
static int ev_commit(struct evolve *e,int32_t species)
{
    struct base *b=&e->b;
    if(dw4_playertransactions_evolve(b->c.view.players,b->c.view.player,species,species_model,(void *)b->c.databases,
           dw4_playerstats_item_attribute,item_string,(void *)b->c.databases,dw4_playerstats_recalculate,(void *)b->c.databases))
        return bfail(b,"evolution transaction failed");
    return update_stats(b);
}
static int ev_step(struct evolve *e,dw4_menu_window *w)
{
    struct base *b=&e->b;
    switch(arena_evolve(e)->_st1) {
    case 0:
        if(arena_evolve(e)->_st2==0) {
            if(ev_list(e) || selector(b,DW4_STATUS_SELECTE1,0,e->rows,arena_evolve(e)->_cursor<e->rows?arena_evolve(e)->_cursor:0,-283,92,0))return -1;
            arena_base(b)->_retCode=arena_evolve(e)->_cursor<e->rows?arena_evolve(e)->_cursor:0;arena_evolve(e)->_st2=1;
            return 0;
        }
        if(arena_evolve(e)->_st2==1) {
            if(ev_render(e,1,1))return -1;
            arena_evolve(e)->_st3=arena_base(b)->_retCode;arena_evolve(e)->_st2=2;return 0;
        }
        if(!changed(b)) {
            dw4_menu_window *child=dw4_menu_window_count(w)?w->children[0]:NULL;int32_t selected=arena_base(b)->_retCode;
            if(selected==-1 || !child)return 0;
            if(selected!=arena_evolve(e)->_st3){if(ev_render(e,0,1))return -1;arena_evolve(e)->_st3=selected;return 0;}
            if(dw4_statusview_selector_ready(child)==1) {
                int turn=dw4_statuspage_turn(&arena_evolve(e)->_nowPage,(int)arena_evolve(e)->_maxPage,0,&e->input,ev_page_io,e);
                if(turn==0)turn=dw4_statuspage_turn(&arena_evolve(e)->_nowPage,(int)arena_evolve(e)->_maxPage,1,&e->input,ev_page_io,e);
                if(turn<0)return bfail(b,"page request failed");
                if(turn) {
                    if(ev_list(e) || dw4_statusview_selector_restart(child,e->rows,NULL))return bfail(b,"selector repage failed");
                    arena_evolve(e)->_cursor=0;arena_evolve(e)->_st3=0;
                    if(ev_render(e,1,1))return -1;
                }
            }
            return 0;
        }
        if(arena_base(b)->_retCode==-1){dw4_menu_window_data(e->result_owner)->_retCode=-1;advance(w);return 0;}
        {
            arena_evolve(e)->_cursor=arena_base(b)->_retCode;
            size_t index=(size_t)arena_evolve(e)->_nowPage*8+(size_t)arena_evolve(e)->_cursor;int32_t cur;
            if(ev_list(e) || index>=(size_t)shinka_count(e->b.self->arena,arena_evolve(e)->_shinkaCtrl) || sense(b,&cur))return -1;
            int32_t species=shinka_row(e->b.self->arena,arena_evolve(e)->_shinkaCtrl,(int)index)->_id;
            if(species==cur){if(sound(b,"CURSOR_NG"))return -1;arena_evolve(e)->_st1=4;arena_evolve(e)->_st2=0;return 0;}
            int ok;
            if(dw4_playertransactions_weapon_check(b->c.view.players,b->c.view.player,species,dw4_playerstats_item_attribute,(void *)b->c.databases,&ok))
                return bfail(b,"weapon check failed");
            if(!ok){if(sound(b,"CURSOR_NG"))return -1;arena_evolve(e)->_st1=4;arena_evolve(e)->_st2=1;return 0;}
            arena_evolve(e)->_st1=3;arena_evolve(e)->_st2=0;return 0;
        }
    case 3: {
        size_t index=(size_t)arena_evolve(e)->_nowPage*8+(size_t)arena_evolve(e)->_cursor;
        if(arena_evolve(e)->_st2==0){if(menu(b,0x4E7,2))return -1;arena_evolve(e)->_st2=1;return 0;}
        if(arena_evolve(e)->_st2==1){if(!changed(b))return 0;if(arena_base(b)->_retCode!=0){arena_evolve(e)->_st1=0;arena_evolve(e)->_st2=0;return 0;}arena_evolve(e)->_st2=2;return 0;}
        if(arena_evolve(e)->_st2==2){if(notice(b,0x4E9,0))return -1;arena_evolve(e)->_st2=3;return 0;}
        if(arena_evolve(e)->_st2==3){if(!changed(b))return 0;arena_evolve(e)->_st2=4;return 0;}
        if(arena_evolve(e)->_st2==4){if(menu(b,0x4EA,2))return -1;arena_evolve(e)->_st2=5;return 0;}
        if(arena_evolve(e)->_st2==5){if(!changed(b))return 0;if(arena_base(b)->_retCode!=0){arena_evolve(e)->_st1=0;arena_evolve(e)->_st2=0;return 0;}arena_evolve(e)->_st2=6;return 0;}
        if(arena_evolve(e)->_st2==6) {
            if(ev_list(e) || index>=(size_t)shinka_count(e->b.self->arena,arena_evolve(e)->_shinkaCtrl))return -1;
            if(notice(b,0x4EC,1) || ev_commit(e,shinka_row(e->b.self->arena,arena_evolve(e)->_shinkaCtrl,(int)index)->_id))return -1;
            arena_evolve(e)->_st2=7;return 0;
        }
        if(!changed(b))return 0;
        dw4_menu_window_data(e->result_owner)->_retCode=1;advance(w);return 0;
    }
    case 4:
        if(arena_evolve(e)->_st2==0 || arena_evolve(e)->_st2==1) {
            if(notice(b,arena_evolve(e)->_st2?0x7E5:0x7E4,0))return -1;
            arena_evolve(e)->_st2+=2;return 0;
        }
        if(!changed(b))return 0;
        arena_evolve(e)->_st1=0;arena_evolve(e)->_st2=0;return 0;
    }
    return 0;
}
static int ev_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct evolve *e=w->user;struct base *b=&e->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        memset(&e->input,0,sizeof e->input);
        if(b->c.input && b->c.input(b->c.user,b->c.view.player,&e->input))rc=bfail(b,"pad input unavailable");
        if(!rc && dw4_menu_window_data(w)->_st0==0 && dw4_menu_window_data(w)->_st1==0) {
            /* 42f710 state 0: the message window becomes the bottom band (i_messwn SQ_STOPEN, closed with SQ_STCLOSE with
             * this window), replacing the lab menu's talk window. */
            if(dw4_statusui_open(&b->c.view,ev_band,e,&b->content,b->error,sizeof b->error))rc=-1;
            else dw4_menu_window_data(w)->_st1=1;
        }else if(!rc && dw4_menu_window_data(w)->_st0==0) {
            /* Then, once SQ_STOPEN is no longer the current sequence, the list window and its texts. */
            int running=query(b,"i_messwn","ISSEQNAME","SQ_STOPEN");
            if(running<0)rc=-1;
            else if(running!=1) {
                if(ev_list(e) || ev_setup(e,dw4_statusview_window_emit,b->content))rc=bfail(b,"form list window setup failed");
                else{advance(w);arena_evolve(e)->_st1=0;arena_evolve(e)->_st2=0;arena_evolve(e)->_nowPage=0;arena_evolve(e)->_cursor=0;}
            }
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1)rc=ev_step(e,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"LABO evolve window failed");
    return rc;
}
static void ev_release(void *u)
{struct evolve *e=u;shinka_drop(e->b.self->arena,&arena_evolve(e)->_shinkaCtrl);release(u);}
static dw4_menu_window *evolve_open(const dw4_statusgear_context *c,dw4_menu_window *parent)
{
    struct evolve *e=calloc(1,sizeof *e);if(!e)return NULL;
    e->b.c=*c;e->b.c.view.parent=NULL;e->b.c.view.parent_window=parent;e->result_owner=parent;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlEvolve",ev_update,e,ev_release);if(!w){free(e);return NULL;}
    e->b.self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=0;return w;
}

/* ---- Digilabo (431760): the lab menu, Evolve, the equipment check and the exit confirmation ---- */
struct labo {
    struct base b;
    /* The StatusTitle01 child (433120 creates it on first use). */
    dw4_menu_window *title;
};
static beNDMWShopCtrlDigilabo *arena_labo(const struct labo *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlDigilabo,p->b.self->object);}

/* 433290: i_messwn SQ_OPEN (the talk window), closed with SQ_CLOSE when the lab closes. */
static int lab_talk_window(struct labo *l)
{
    struct base *b=&l->b;
    return dw4_statusui_emit(b->content,DW4_VIEW_MODEL,NULL,"i_messwn","SQ_OPEN","SQ_CLOSE",0)?bfail(b,"talk window could not be opened"):0;
}
/* 433120: the lab's StatusTitle01 (created with the compact-base context 1 when it is missing, else switched back to the
 * compact base); 425e60 switches it to the full panel for the equipment check. */
static int lab_title(struct labo *l,int variant)
{
    struct base *b=&l->b;
    if(l->title)return dw4_statusview_window_title_variant(l->title,variant)?bfail(b,"player panel switch failed"):0;
    dw4_statusview_context c=b->c.view;c.parent=NULL;c.parent_window=b->self;c.callno=0;c.variant=variant;c.initialize=NULL;c.selection_initialize=NULL;
    c.refresh=dw4_statusstats_refresh;c.user=b->c.stats;
    dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_TITLE01,&c);
    if(add_child(b,w,"player panel could not be opened"))return -1;
    l->title=w;return 0;
}
static int lab_none(void *u,dw4_statusview_io io,void *iou){(void)u;(void)io;(void)iou;return 0;}
static int snapshot_state(struct labo *l)
{
    dw4_property_folder *f=folder(&l->b);size_t n;int32_t species,weapons[3],nw=0;
    const dw4_item_record *sockets=f?dw4_property_items(f,"POWERSOCKET",&n):NULL;
    if(!sockets || n!=3 || sense(&l->b,&species))return bfail(&l->b,"player record unavailable");
    for(size_t i=0;i<n;i++)if(sockets[i].kind>=0)weapons[nw++]=sockets[i].record;
    dw4_arena *a=l->b.self->arena;int32_t player=l->b.c.view.player;
    int32_t players=al_new(a,"igIntList",4,1,&player),species_list=al_new(a,"igIntList",4,1,&species);
    int32_t weapon_list=al_new(a,"igIntList",4,nw,weapons);
    int32_t nested=weapon_list?al_new(a,"igIntListList",4,1,&weapon_list):0;
    if(!players || !species_list || !nested){al_drop(a,&players);al_drop(a,&species_list);al_drop(a,&weapon_list);al_drop(a,&nested);return bfail(&l->b,"comparison snapshot allocation failed");}
    beNDMWShopCtrlDigilabo *d=arena_labo(l);
    al_drop(a,&d->_playerNoList);al_drop(a,&d->_digimonNoList);al_nested_ints_drop(a,&d->_wpuNoListList);
    d->_playerNoList=players;d->_digimonNoList=species_list;d->_wpuNoListList=nested;return 0;
}
/* 432d30: only after an evolution or a completed equipment check, compare the species and the weapon multiset. */
static int lab_changed(struct labo *l,int *out)
{
    *out=0;
    if(!arena_labo(l)->_isDigimonChange && !arena_labo(l)->_isWeaponChange)return 0;
    dw4_property_folder *f=folder(&l->b);size_t n;int32_t species;
    const dw4_item_record *sockets=f?dw4_property_items(f,"POWERSOCKET",&n):NULL;
    if(!sockets || n!=3 || sense(&l->b,&species))return bfail(&l->b,"player record unavailable");
    dw4_arena *a=l->b.self->arena;beNDMWShopCtrlDigilabo *d=arena_labo(l);
    int count=al_count(a,d->_playerNoList),index=0;
    for(;index<count;index++)if(al_words(a,d->_playerNoList)[index]==l->b.c.view.player)break;
    if(index==count || al_count(a,d->_digimonNoList)!=count || al_count(a,d->_wpuNoListList)!=count)return bfail(&l->b,"comparison snapshot unavailable");
    if(species!=al_words(a,d->_digimonNoList)[index]){*out=1;return 0;}
    int32_t weapons=al_words(a,d->_wpuNoListList)[index];int size=al_count(a,weapons);
    if(size<0 || size>3)return bfail(&l->b,"comparison weapon snapshot invalid");
    int32_t left[3]={-1,-1,-1};size_t nleft=(size_t)size,have=0;
    if(size)memcpy(left,al_words(a,weapons),(size_t)size*4);
    for(size_t i=0;i<n;i++){
        if(sockets[i].kind<0)continue;
        have++;
        size_t j=0;while(j<nleft && left[j]!=sockets[i].record)j++;
        if(j<nleft)left[j]=-1;
    }
    if(have!=nleft){*out=1;return 0;}
    for(size_t j=0;j<nleft;j++)if(left[j]!=-1){*out=1;return 0;}
    return 0;
}
static int recalc_all(struct labo *l)
{
    /* 432c90: RECALCPLAYER for every joined player. */
    return dw4_playertransactions_recalculate(l->b.c.view.players,l->b.c.view.player,dw4_playerstats_recalculate,(void *)l->b.c.databases)?
        bfail(&l->b,"recalculation failed"):0;
}
static int lab_step(struct labo *l,dw4_menu_window *w)
{
    struct base *b=&l->b;
    switch(arena_labo(l)->_st1) {
    case 0:
        /* 431760 main 0: 433290 (talk window) and 433120 (compact player panel), every time the menu starts. */
        if(arena_labo(l)->_st2==0){if(lab_talk_window(l) || lab_title(l,1))return -1;arena_labo(l)->_st2=1;return 0;}
        if(arena_labo(l)->_st2==1) {
            int running=query(b,"i_messwn","ISSEQNAME","SQ_OPEN");
            if(running<0)return -1;
            if(running==1)return 0;
            if(talk_menu(b,1,3))return -1;
            arena_labo(l)->_st2=2;return 0;
        }
        if(!changed(b))return 0;
        arena_labo(l)->_st1=arena_base(b)->_retCode==0?1:arena_base(b)->_retCode==1?2:6;arena_labo(l)->_st2=0;return 0;
    case 1:
        if(arena_labo(l)->_st2==0) {
            arena_base(&l->b)->_retCode=0;
            if(add_child(b,evolve_open(&b->c,b->self),"evolve window could not be opened"))return -1;
            arena_labo(l)->_st2=1;return 0;
        }
        if(!changed(b))return 0;
        if(lab_talk_window(l))return -1;
        if(arena_base(&l->b)->_retCode!=1){arena_labo(l)->_st1=0;arena_labo(l)->_st2=0;return 0;}
        arena_labo(l)->_isDigimonChange=1;arena_labo(l)->_st1=3;arena_labo(l)->_st2=0;return 0;
    case 2:
        /* main 2: the panel switches to the full STATUS panel (425e60), then StatusCtrlEquip opens with entry code 1
         * (431e5c), so the equipment menu creates the bottom band (StatusTitle02, i_messwn SQ_STOPEN, closed with
         * SQ_STCLOSE with that child) instead of its Title04 header, and the "Digi-Lab" header stays; afterwards 433290
         * reopens the talk window. */
        if(arena_labo(l)->_st2==0){if(lab_title(l,0))return -1;arena_labo(l)->_st2=1;return 0;}
        if(arena_labo(l)->_st2==1) {
            dw4_statusgear_context gear=b->c;gear.view.parent=NULL;gear.view.parent_window=b->self;gear.view.callno=0;
            gear.view.refresh=dw4_statusstats_refresh;gear.view.user=gear.stats;
            if(add_child(b,dw4_statusequipmentmenu_window_open_entry(&gear,1),"equipment window could not be opened"))return -1;
            arena_labo(l)->_st2=2;return 0;
        }
        if(!changed(b))return 0;
        /* Retail frame after the check: the compact base (the full panel is gone) and no equipment description behind the
         * lab menu. */
        if(lab_title(l,1) ||
           dw4_statusui_emit(b->content,DW4_VIEW_SWITCH,"STWINFONT29","font000",NULL,"DISPOFF",0))return bfail(b,"lab menu restore failed");
        if(lab_talk_window(l))return -1;
        arena_labo(l)->_isWeaponChange=1;arena_labo(l)->_st1=0;arena_labo(l)->_st2=0;return 0;
    case 3:
        if(arena_labo(l)->_st2==0){if(talk_message(b,0x4ED))return -1;arena_labo(l)->_st2=1;return 0;}
        if(arena_labo(l)->_st2==1){if(!changed(b))return 0;if(talk_menu(b,1262,2))return -1;arena_labo(l)->_st2=2;return 0;}
        if(!changed(b))return 0;
        arena_labo(l)->_st1=arena_base(b)->_retCode==0?2:0;arena_labo(l)->_st2=0;return 0;
    case 6:
        if(arena_labo(l)->_st2==0) {
            int any;
            if(lab_changed(l,&any))return -1;
            if(any){arena_labo(l)->_st2=2;return 0;}
            if(talk_message(b,0x4FB) || recalc_all(l))return -1;
            arena_labo(l)->_st2=1;return 0;
        }
        if(arena_labo(l)->_st2==1){if(!changed(b))return 0;advance(w);return 0;}
        if(arena_labo(l)->_st2==2){if(talk_message(b,0x4F3))return -1;arena_labo(l)->_st2=3;return 0;}
        if(arena_labo(l)->_st2==3){if(!changed(b))return 0;if(talk_menu(b,1268,2))return -1;arena_labo(l)->_st2=4;return 0;}
        if(arena_labo(l)->_st2==4) {
            if(!changed(b))return 0;
            if(arena_base(b)->_retCode!=0){arena_labo(l)->_st1=0;arena_labo(l)->_st2=0;return 0;}
            arena_labo(l)->_st2=5;return 0;
        }
        if(recalc_all(l))return -1;
        arena_labo(l)->_isDemoRun=1;advance(w);return 0;
    }
    return 0;
}
static int lab_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct labo *l=w->user;struct base *b=&l->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0==2 && arena_labo(l)->_isDemoRun) {
        /* 389ff0: the lab's closing script runs after the controller is done (queued for the next DM tick). */
        arena_labo(l)->_isDemoRun=0;
        if(dw4_scriptengine_queue_event(b->c.view.engine,"demo_digilab.lua"))
            rc=bfail(b,"the closing script demo_digilab.lua could not be queued");
    }
    if(!rc) {
        if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
        else {
            if(dw4_menu_window_data(w)->_st0==0) {
                /* The controller owns the talk window it opens (433290 presents it on the Digilabo window). */
                if(snapshot_state(l) || dw4_statusui_open(&b->c.view,lab_none,l,&b->content,b->error,sizeof b->error))rc=-1;
                else{advance(w);arena_labo(l)->_st1=0;arena_labo(l)->_st2=0;}
            }
            if(!rc && dw4_menu_window_data(w)->_st0==1)rc=lab_step(l,w);
        }
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"LABO failed");
    return rc;
}
static int valid(const dw4_statusgear_context *c)
{
    return c && c->databases && c->stats && c->view.sd && c->view.engine && c->view.players && c->view.player==0 && c->input;
}
static void lab_release(void *u)
{
    struct labo *l=u;beNDMWShopCtrlDigilabo *d=arena_labo(l);dw4_arena *a=l->b.self->arena;
    al_drop(a,&d->_playerNoList);al_drop(a,&d->_digimonNoList);al_nested_ints_drop(a,&d->_wpuNoListList);release(u);
}
dw4_menu_window *dw4_laboshop_window_open(const dw4_statusgear_context *c)
{
    if(!valid(c))return NULL;
    struct labo *l=calloc(1,sizeof *l);if(!l)return NULL;
    l->b.c=*c;l->b.c.view.parent=NULL;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlDigilabo",lab_update,l,lab_release);if(!w){free(l);return NULL;}
    l->b.self=w;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=0;return w;
}
int dw4_laboshop_window_state(const dw4_menu_window *w,dw4_laboshop_state *out)
{
    if(!w || !out || w->update!=lab_update)return -1;
    const struct labo *l=w->user;
    *out=(dw4_laboshop_state){dw4_menu_window_data(w)->_st0,arena_labo(l)->_st1,arena_labo(l)->_st2,arena_labo(l)->_isDigimonChange,arena_labo(l)->_isWeaponChange,arena_base(&l->b)->_retCode};return 0;
}
