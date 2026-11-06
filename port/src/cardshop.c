#include "menurecord.h"
#include "arenalist.h"
/* The card album window tree (SUBWND mode 10): ShopCtrlA0 update 42c810 (root), ShopCtrlA1 42d450
 * (a player's menu and the album viewer, with the helpers 42df70/42e330/42e9e0) and ShopCtrlA2
 * 42eb80 (the Booster Pack opening). Field names follow the other shop controllers: the window
 * state is the primary state (+1c), main/sub are +20/+24, +30 is _retCode (written into
 * ret.selection by the child selectors, and by A2 into its parent's), +50 the child-count
 * snapshot. Completion of a child is a change in the child count, as in retail. */
#include "dw4/cardshop.h"
#include "dw4/statusui.h"
#include "dw4/playertransactions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {PAGES=9,PER_PAGE=6,NCARD=50,BOOSTER=10};

struct base {
    dw4_cardshop_context c;
    dw4_menu_window *up;
    dw4_menu_window *self,*content;
    char error[256];
};
static beNDMWWindowCtrl *arena_base(const struct base *p)
{return DW4_ARENA_OBJ(p->self->arena,beNDMWWindowCtrl,p->self->object);}

static int bfail(struct base *b,const char *what){snprintf(b->error,sizeof b->error,"CARD: %s",what);return -1;}
static int changed(const struct base *b){return dw4_menu_window_count(b->self)!=(size_t)arena_base(b)->_nowProcKazu;}
static void advance(dw4_menu_window *w){dw4_menu_window_data(w)->_st0++;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
static int put(struct base *b,int op,const char *g,const char *n,const char *k,const char *v,int call)
{
    if(!b->content)return bfail(b,"no resource owner is open");
    return dw4_statusui_emit(b->content,op,g,n,k,v,call)?bfail(b,"resource could not be updated"):0;
}
static int tell(struct base *b,const char *model,int32_t ram,const char *sequence)
{return dw4_statusui_call(&b->c.view,0,"MODELCTRL",model,ram,sequence,NULL,b->error,sizeof b->error)<0?-1:0;}
/* ISSEQNAME: 1 while the sequence is current, 0 once it ended, negative on a service error. */
static int seq_running(struct base *b,const char *model,int32_t ram,const char *sequence)
{return dw4_statusui_call(&b->c.view,1,"MODELCTRL",model,ram,"ISSEQNAME",sequence,b->error,sizeof b->error);}
/* PresentModelAtOrigin: an active model receives the sequence, an inactive one is generated at the origin with it. */
static int present(struct base *b,const char *model,int32_t ram,const char *sequence)
{return dw4_statusui_positioned(&b->c.view,model,ram,sequence,0,0,0,b->error,sizeof b->error)<0?-1:0;}
static dw4_property_folder *folder(struct base *b,int32_t player){return dw4_playerrecords_get(b->c.view.players,"GETPLAYER",player);}
static int add_child(struct base *b,dw4_menu_window *w,const char *what)
{
    if(!w)return bfail(b,what);
    if(dw4_menu_window_add(b->self,w)){dw4_menu_window_close(w);return bfail(b,"child window could not be attached");}
    arena_base(b)->_nowProcKazu=dw4_menu_window_count(b->self);return 0;
}
typedef int (*init_fn)(void *,dw4_statusview_io,void *);
static int selector(struct base *b,int kind,int call,int rows,int selected,int variant,init_fn init)
{
    dw4_statusview_context c=b->c.view;c.parent=NULL;c.parent_window=b->self;c.callno=call;c.rows=rows;c.selected=selected;c.variant=variant;
    c.position[0]=c.position[1]=c.position[2]=0;c.enabled=NULL;c.selection_initialize=init;c.user=b;c.initialize=NULL;c.refresh=NULL;
    return add_child(b,dw4_statusview_window_open(kind,&c),"selector window could not be opened");
}
static int notice(struct base *b,int call,init_fn init){return selector(b,DW4_STATUS_TALKSELECT03,call,1,0,0,init);}
static int menu(struct base *b,int call){return selector(b,DW4_STATUS_TALKSELECT02,call,2,0,0,NULL);}
static int open_content(struct base *b,init_fn init)
{return dw4_statusui_open(&b->c.view,init,b,&b->content,b->error,sizeof b->error)?bfail(b,"resource owner could not be opened"):0;}
static int close_children(struct base *b)
{for(size_t i=0;i<dw4_menu_window_count(b->self);i++)dw4_menu_window_remove(b->self->children[i]);return 0;}
/* The primary states shared by all three windows: 2 closes the children and the resource owner, 3 waits. */
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
static void init_base(struct base *b,const dw4_cardshop_context *c)
{b->c=*c;b->up=c->view.parent_window;b->c.view.parent=NULL;}
static int valid(const dw4_cardshop_context *c)
{
    return c && c->databases && c->random && c->refresh && c->view.sd && c->view.engine && c->view.players &&
        c->view.player>=0 && c->view.player<4;
}
static const dw4_database *cards(struct base *b){return dw4_databases_get(b->c.databases,"card");}
static void release(void *u){struct base *b=u;dw4_menu_window_close(b->content);free(b);}

/* ---- the Booster Pack opening: ShopCtrlA2 (42eb80) ---- */
struct a2 {
    struct base b;
    int32_t picks[3],top;
};
static beNDMWShopCtrlA2 *arena_a2(const struct a2 *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlA2,p->b.self->object);}

static int a2_models(void *u,dw4_statusview_io io,void *iou)
{
    /* The pack opens with SQ_OPEN00..08 by the number of packs held (the context, 1..9). */
    struct a2 *a=u;char seq[24];snprintf(seq,sizeof seq,"SQ_OPEN%02d",(arena_a2(a)->_entCode-1)%100);
    dw4_statusview_command c={DW4_VIEW_MODEL,NULL,"j_shbooster",seq,"SQ_CLOSE",0};return io(iou,&c);
}
/* The three cards (selector-owned resources, 3f5410 / PresentModelAtOrigin on the notice): name text, model, rarity colour. */
static int a2_cards(void *u,dw4_statusview_io io,void *iou)
{
    struct a2 *a=u;const dw4_database *db=cards(&a->b);
    static const char *const fonts[3]={"font02","font03","font04"},*const seqs[3]={"SQ_CARD06OPEN","SQ_CARD07OPEN","SQ_CARD08OPEN"};
    for(int d=0;d<3;d++){
        int32_t row=a->picks[d],rare=0;const char *name=dw4_database_string(db,row,"NAME"),*model=dw4_database_string(db,row,"CARDINFO");
        if(!name || !model || dw4_database_number(db,row,"RARE",&rare)<0)return -1;
        dw4_statusview_command t={DW4_VIEW_TEXT,"TALKFONT01",fonts[d],"LEFT",name,0};if(io(iou,&t))return -1;
        dw4_statusview_command m={DW4_VIEW_MODEL,NULL,model,seqs[d],"SQ_CLOSE",d};if(io(iou,&m))return -1;
        dw4_statusview_command k={DW4_VIEW_COLOR,"TALKFONT01",fonts[d],"COLOR",rare==2?"V<0,1,0>":rare==1?"V<1,1,0>":"V<1,1,1>",0};if(io(iou,&k))return -1;
    }
    return 0;
}
static int a2_draw(struct a2 *a)
{
    struct base *b=&a->b;const dw4_database *db=cards(b);
    size_t rows=db?dw4_database_string_rows(db):0;
    if(!rows || rows>256)return bfail(b,"card database unavailable");
    int32_t kak[256],rare[256];
    for(size_t i=0;i<rows;i++){
        if(dw4_database_number(db,(int32_t)i,"KAKURITSU",&kak[i])<0 || dw4_database_number(db,(int32_t)i,"RARE",&rare[i])<0)
            return bfail(b,"card odds unavailable");
    }
    uint32_t rolls[3];for(int d=0;d<3;d++)rolls[d]=dw4_random_next(b->c.random);
    if(dw4_playertransactions_booster_open(b->c.view.players,arena_base(&a->b)->_playerNo,kak,rare,rows,rolls,a->picks,&a->top))
        return bfail(b,"Booster Pack transaction failed");
    return 0;
}
static int a2_run(struct a2 *a,dw4_menu_window *w)
{
    struct base *b=&a->b;
    if(arena_a2(a)->_st1==7) {
        switch(arena_a2(a)->_st2) {
        case 0:
            if(open_content(b,a2_models) || notice(b,0x7DD,NULL))return -1;
            arena_a2(a)->_st2=1;return 0;
        case 1:if(changed(b))arena_a2(a)->_st2=2;return 0;
        case 2:if(menu(b,0x7D8))return -1;arena_a2(a)->_st2=3;return 0;
        default:
            if(!changed(b))return 0;
            switch(arena_base(b)->_retCode) {
            case 0:
                if(b->content && dw4_statusui_close(b->content,b->error,sizeof b->error))return -1;
                arena_a2(a)->_st1=8;arena_a2(a)->_st2=0;return 0;
            case 1:if(b->up)dw4_menu_window_data(b->up)->_retCode=6;advance(w);return 0;
            default:if(b->up)dw4_menu_window_data(b->up)->_retCode=4;advance(w);return 0;
            }
        }
    }
    if(arena_a2(a)->_st1==8) {
        if(arena_a2(a)->_st2==0) {
            if(b->content && dw4_statusui_drain(&b->content,b->error,sizeof b->error))return -1;
            if(b->content)return 0;
            if(a2_draw(a))return -1;
            if(notice(b,a->top==2?0x7DA:a->top==1?0x7DB:0x7DC,a2_cards))return -1;
            arena_a2(a)->_st2=1;return 0;
        }
        if(!changed(b))return 0;
        /* 8.1: the three name colours go back to the default before the window closes. */
        static const char *const fonts[3]={"TALKFONT01/font02","TALKFONT01/font03","TALKFONT01/font04"};
        for(int d=0;d<3;d++)
            if(dw4_statusui_call(&b->c.view,0,"TEXTCTL",NULL,-1,"DEFAULTCOLOR",fonts[d],b->error,sizeof b->error)<0)return -1;
        if(b->up)dw4_menu_window_data(b->up)->_retCode=4;
        advance(w);return 0;
    }
    return 0;
}
static int a2_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct a2 *a=w->user;struct base *b=&a->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        if(dw4_menu_window_data(w)->_st0==0){advance(w);arena_a2(a)->_st1=7;arena_a2(a)->_st2=0;}
        if(dw4_menu_window_data(w)->_st0==1)rc=a2_run(a,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"CARD Booster Pack failed");
    return rc;
}
static dw4_menu_window *a2_open(const dw4_cardshop_context *c,int32_t player,int32_t count)
{
    struct a2 *a=calloc(1,sizeof *a);if(!a)return NULL;
    init_base(&a->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlA2",a2_update,a,release);if(!w){free(a);return NULL;}
    dw4_menu_window_data(w)->_entCode=count;
    a->b.self=w;dw4_menu_window_data(w)->_playerNo=player;dw4_menu_window_data(w)->_retCode=0;return w;
}

/* ---- a player's menu and the album viewer: ShopCtrlA1 (42d450) ---- */
struct a1 {
    struct base b;
};
static beNDMWShopCtrlA1 *arena_a1(const struct a1 *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlA1,p->b.self->object);}

static int a1_packs(struct a1 *a,int32_t *count)
{
    size_t n;const dw4_item_record *v=dw4_property_items(folder(&a->b,arena_base(&a->b)->_playerNo),"DISKFOLDER",&n);
    if(!v || n!=12)return bfail(&a->b,"DISKFOLDER unavailable");
    *count=0;for(size_t i=0;i<n;i++)if(v[i].record==BOOSTER)*count=v[i].revision;
    return 0;
}
static const uint8_t *owned(struct a1 *a)
{size_t n;const uint8_t *v=dw4_property_bytes(folder(&a->b,arena_base(&a->b)->_playerNo),"CARDLIST",&n);if(!v || n!=NCARD){bfail(&a->b,"CARDLIST unavailable");return NULL;}return v;}
static const char *album_model(const struct a1 *a,int pos)
{
    const char *s=al_text(a->b.self->arena,al_words(a->b.self->arena,arena_a1(a)->_cardInfoList)[pos]);return s?s:"";
}
static int32_t *album_slots(const struct a1 *a)
{return al_words(a->b.self->arena,arena_a1(a)->_cardRamNoList);}
static void album_clear(struct a1 *a,int pos)
{
    int32_t *v=al_words(a->b.self->arena,arena_a1(a)->_cardInfoList);
    al_free(a->b.self->arena,v[pos]);v[pos]=0;album_slots(a)[pos]=-1;
}
static int album_set(struct a1 *a,int pos,const char *model,int32_t ram)
{
    int32_t name=al_string(a->b.self->arena,model);if(!name)return bfail(&a->b,"card name allocation failed");
    album_clear(a,pos);al_words(a->b.self->arena,arena_a1(a)->_cardInfoList)[pos]=name;album_slots(a)[pos]=ram;return 0;
}
static void a1_release(void *u)
{
    struct a1 *a=u;al_strings_drop(a->b.self->arena,&arena_a1(a)->_cardInfoList);
    al_drop(a->b.self->arena,&arena_a1(a)->_cardRamNoList);release(u);
}
/* 42df70 (the first page) and 42e330 (a page change): each of the six positions shows its card when owned, otherwise the blank
 * card back j_shcard00 on the position's own ram slot; positions past card 49 are cleared. */
static int album_page(struct a1 *a,int page,int first)
{
    struct base *b=&a->b;const dw4_database *db=cards(b);const uint8_t *have=owned(a);
    if(!db || !have)return bfail(b,"card album data unavailable");
    char digit[2]={(char)('1'+page),0};
    if(!first && put(b,DW4_VIEW_SET_TEXT,"STWINFONT33","font000",NULL,digit,0))return -1;
    for(int p=0;p<PER_PAGE;p++){
        int idx=page*PER_PAGE+p;
        if(idx>=NCARD){
            if(!first && album_model(a,p)[0] && tell(b,album_model(a,p),album_slots(a)[p],"SQ_CLOSE"))return -1;
            album_clear(a,p);continue;
        }
        if(have[idx]){
            const char *model=dw4_database_string(db,idx,"CARDINFO"),*seq=dw4_database_string(db,idx,"SQALBUM");
            if(!model || !seq)return bfail(b,"card model unavailable");
            if(!first && album_slots(a)[p]!=-1 && album_model(a,p)[0] && tell(b,album_model(a,p),album_slots(a)[p],"SQ_CLOSE"))return -1;
            if(album_set(a,p,model,0) || present(b,model,0,seq))return -1;
        }else {
            const char *seq=dw4_database_string(db,p,"SQALBUM");
            if(!seq)return bfail(b,"card back sequence unavailable");
            if(!first && album_slots(a)[p]!=-1 && album_model(a,p)[0] && tell(b,album_model(a,p),album_slots(a)[p],"SQ_CLOSE"))return -1;
            if(album_set(a,p,"j_shcard00",p) || present(b,"j_shcard00",p,seq))return -1;
        }
    }
    return 0;
}
/* 42e9e0: every shown position gets SQ_CLOSE and the lists are cleared. */
static int album_close(struct a1 *a)
{
    for(int p=0;p<PER_PAGE;p++){
        if(album_slots(a)[p]!=-1 && album_model(a,p)[0] && tell(&a->b,album_model(a,p),album_slots(a)[p],"SQ_CLOSE"))return -1;
        album_clear(a,p);
    }
    return 0;
}
static int a1_run(struct a1 *a,dw4_menu_window *w)
{
    struct base *b=&a->b;
    switch(arena_a1(a)->_st1) {
    case 4:
        if(arena_a1(a)->_st2==0) {
            int q=seq_running(b,"j_shbase",arena_base(&a->b)->_playerNo,"SQ_OPEN");if(q<0)return -1;
            if(q!=1){if(menu(b,2005))return -1;arena_a1(a)->_st2=1;}
            return 0;
        }
        if(!changed(b))return 0;
        switch(arena_base(b)->_retCode){case 0:arena_a1(a)->_st1=5;arena_a1(a)->_st2=0;return 0;case 1:arena_a1(a)->_st1=6;arena_a1(a)->_st2=0;return 0;default:advance(w);return 0;}
    case 5:
        if(arena_a1(a)->_st2==0) {
            int32_t count;if(a1_packs(a,&count))return -1;
            if(count>0){
                dw4_cardshop_context c=b->c;c.view.parent=NULL;c.view.parent_window=b->self;c.view.player=arena_base(&a->b)->_playerNo;
                dw4_menu_window *w2=a2_open(&c,arena_base(&a->b)->_playerNo,count);
                if(add_child(b,w2,"Booster Pack window could not be opened"))return -1;
            }else{
                if(notice(b,0x7D7,NULL) || dw4_statusui_call(&b->c.view,0,"SOUND",NULL,-1,"PLAY","CURSOR_NG",b->error,sizeof b->error)<0)return -1;
            }
            arena_a1(a)->_st2=1;return 0;
        }
        if(!changed(b))return 0;
        arena_a1(a)->_st1=arena_base(b)->_retCode==6?6:4;arena_a1(a)->_st2=0;return 0;
    default:
        if(arena_a1(a)->_st2==0) {
            if(tell(b,"i_staccount",0,"SQ_CLOSE") || tell(b,"i_messwn",0,"SQ_CLOSE") ||
               put(b,DW4_VIEW_SWITCH,"STWINFONT34","font002",NULL,"DISPOFF",0) ||
               selector(b,DW4_STATUS_CARDPAGE,0,9,0,0,NULL) || album_page(a,0,1))return -1;
            arena_a1(a)->_st3=0;arena_a1(a)->_st2=1;return 0;
        }
        if(arena_a1(a)->_st2==1) {
            int q=seq_running(b,"j_shcardwin",0,"SQ_OPEN");if(q<0)return -1;
            if(q!=1){
                if(put(b,DW4_VIEW_SET_TEXT,"STWINFONT33","font000",NULL,"1",0) || put(b,DW4_VIEW_SET_TEXT,"STWINFONT33","font001",NULL,"9",0))return -1;
                arena_a1(a)->_st2=2;
            }
            return 0;
        }
        if(!changed(b)) {
            int32_t sel=arena_base(b)->_retCode;
            if(sel!=-1 && arena_a1(a)->_st3!=sel){if(album_page(a,sel,0))return -1;arena_a1(a)->_st3=sel;}
            return 0;
        }
        if(album_close(a) || put(b,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,0) ||
           put(b,DW4_VIEW_SWITCH,"STWINFONT34","font002",NULL,"DISPON",0) ||
           present(b,"i_staccount",0,"SQ_OPEN") || present(b,"i_messwn",0,"SQ_OPEN"))return -1;
        arena_a1(a)->_st1=4;arena_a1(a)->_st2=0;return 0;
    }
}
static int no_resources(void *u,dw4_statusview_io io,void *iou){(void)u;(void)io;(void)iou;return 0;}
static int a1_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct a1 *a=w->user;struct base *b=&a->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else {
        if(dw4_menu_window_data(w)->_st0==0){
            advance(w);arena_a1(a)->_st1=4;arena_a1(a)->_st2=0;
            for(int p=0;p<PER_PAGE;p++)album_slots(a)[p]=-1;
            rc=open_content(b,no_resources);
        }
        if(!rc && dw4_menu_window_data(w)->_st0==1)rc=a1_run(a,w);
    }
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"CARD player window failed");
    return rc;
}
static dw4_menu_window *a1_open(const dw4_cardshop_context *c,int32_t player)
{
    struct a1 *a=calloc(1,sizeof *a);if(!a)return NULL;
    init_base(&a->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlA1",a1_update,a,a1_release);if(!w){free(a);return NULL;}
    a->b.self=w;dw4_menu_window_data(w)->_playerNo=player;dw4_menu_window_data(w)->_retCode=0;int32_t slots[PER_PAGE];for(int i=0;i<PER_PAGE;i++)slots[i]=-1;
    arena_a1(a)->_cardInfoList=al_new(w->arena,"igStringRefList",4,PER_PAGE,NULL);
    arena_a1(a)->_cardRamNoList=al_new(w->arena,"igIntList",4,PER_PAGE,slots);
    if(!arena_a1(a)->_cardInfoList || !arena_a1(a)->_cardRamNoList){dw4_menu_window_close(w);return NULL;}
    return w;
}

/* ---- the root: ShopCtrlA0 (42c810) ---- */
struct root {
    struct base b;
    dw4_menu_window *title;
};
static beNDMWShopCtrlA0 *arena_root(const struct root *p)
{return DW4_ARENA_OBJ(p->b.self->arena,beNDMWShopCtrlA0,p->b.self->object);}

static int root_models(void *u,dw4_statusview_io io,void *iou)
{
    (void)u;
    dw4_statusview_command a={DW4_VIEW_MODEL,NULL,"j_shback","SQ_OPENCARD","SQ_CLOSE",0},c={DW4_VIEW_MODEL,NULL,"i_bgclear","SQ_OPEN","SQ_CLOSE",0};
    return io(iou,&a)||io(iou,&c);
}
/* ShopTitle03 (441250): the i_messwn message window. */
static int shop_title03(void *u,dw4_statusview_io io,void *iou)
{(void)u;dw4_statusview_command m={DW4_VIEW_MODEL,NULL,"i_messwn","SQ_OPEN","SQ_CLOSE",0};return io(iou,&m);}
/* ShopTitle01 (441040): the i_sttitle header and txt_shop 2000 (the entry code 10 picks the call). */
static int shop_title01(void *u,dw4_statusview_io io,void *iou)
{
    (void)u;
    dw4_statusview_command m={DW4_VIEW_MODEL,NULL,"i_sttitle","SQ_OPEN","SQ_CLOSE",0},t={DW4_VIEW_TRACK_TEXT,"STWINFONT12","font000",NULL,NULL,0},
        s={DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x7D0};
    return io(iou,&m)||io(iou,&t)||io(iou,&s);
}
static int content_child(struct root *r,init_fn init)
{
    struct base *b=&r->b;dw4_statusview_context c=b->c.view;c.parent=NULL;c.initialize=init;c.user=r;c.refresh=NULL;
    return add_child(b,dw4_statusview_window_open(DW4_STATUS_CONTENT,&c),"title window could not be opened");
}
static int kind_child(struct root *r,int kind,int variant)
{
    struct base *b=&r->b;dw4_statusview_context c=b->c.view;c.parent=NULL;c.callno=0;c.variant=variant;
    if(kind==DW4_STATUS_TITLE01){c.refresh=b->c.refresh;c.user=b->c.user;}
    dw4_menu_window *w=dw4_statusview_window_open(kind,&c);
    int rc=add_child(b,w,"title window could not be opened");
    if(!rc && kind==DW4_STATUS_TITLE01)arena_root(r)->_account=(int32_t)w->object.off;
    return rc;
}
/* 43dc10 case -1: the chooser lists each joined player's name (TALKFONT01) and species (TALKFONT04). */
static int player_names(void *u,dw4_statusview_io io,void *iou)
{
    struct base *b=u;struct root *r=(struct root *)b;
    for(int k=0;k<menu_int_count(r->b.self,arena_root(r)->_playerNoList);k++){
        dw4_property_folder *f=folder(b,menu_int_data(r->b.self,arena_root(r)->_playerNoList)[k]);int32_t digimon;char name[16]={0},font[16];dw4_unicode_object n;
        if(!f || dw4_property_number(f,"DIGIMONNO",&digimon) || dw4_property_unicode_object(f,"PLAYERNAME",0,&n) || !n.present)return -1;
        for(unsigned i=0;i<8 && i<n.count && n.codes[i];i++)name[i]=dw4_name_char(n.codes[i]);
        const char *species=dw4_databases_shinka_name((void *)b->c.databases,digimon);if(!species)return -1;
        snprintf(font,sizeof font,"font%02d",k+1);
        dw4_statusview_command a={DW4_VIEW_TEXT,"TALKFONT01",font,"LEFT",name,0},c={DW4_VIEW_TEXT,"TALKFONT04",font,"LEFT",species,0};
        if(io(iou,&a)||io(iou,&c))return -1;
    }
    return 0;
}
static int root_run(struct root *r,dw4_menu_window *w)
{
    struct base *b=&r->b;
    if(arena_root(r)->_st1==0){
        int q=seq_running(b,"i_messwn",0,"SQ_OPEN");if(q<0)return -1;
        if(q!=1){arena_root(r)->_st1=1;arena_root(r)->_st2=0;}
        return 0;
    }
    if(arena_root(r)->_st1==1){
        if(arena_root(r)->_st2==0){
            if(menu(b,2003) || put(b,DW4_VIEW_COLOR,"STWINFONT34","font002","CANCELCOLOR",NULL,0))return -1;
            arena_root(r)->_st2=1;return 0;
        }
        if(!changed(b))return 0;
        if(arena_base(b)->_retCode==0){arena_root(r)->_st1=2;arena_root(r)->_st2=0;}else advance(w);
        return 0;
    }
    if(arena_root(r)->_st1==2){
        if(arena_root(r)->_st2==0){
            if(selector(b,DW4_STATUS_TALKSELECT02,-1,menu_int_count(r->b.self,arena_root(r)->_playerNoList),0,menu_int_count(r->b.self,arena_root(r)->_playerNoList),player_names) ||
               put(b,DW4_VIEW_COLOR,"STWINFONT34","font002","DEFAULTCOLOR",NULL,0))return -1;
            arena_root(r)->_st2=1;return 0;
        }
        if(!changed(b))return 0;
        int32_t sel=arena_base(b)->_retCode;
        if(sel<0 || sel>=menu_int_count(r->b.self,arena_root(r)->_playerNoList)){arena_root(r)->_st1=1;arena_root(r)->_st2=0;return 0;}
        if(menu_int_data(r->b.self,arena_root(r)->_playerNoList)[sel]!=arena_root(r)->_playerNo)return bfail(b,"the player panel of a second joined player is not supported");
        dw4_cardshop_context c=b->c;c.view.parent=NULL;c.view.parent_window=b->self;c.view.player=arena_root(r)->_playerNo;
        if(add_child(b,a1_open(&c,arena_root(r)->_playerNo),"player window could not be opened"))return -1;
        arena_root(r)->_st1=3;return 0;
    }
    if(arena_root(r)->_st1==3&&changed(b)){arena_root(r)->_st1=2;arena_root(r)->_st2=0;}
    return 0;
}
static int root_open(struct root *r,dw4_menu_window *w)
{
    struct base *b=&r->b;
    if(arena_root(r)->_st1==0){
        if(open_content(b,root_models))return -1;
        arena_root(r)->_st1=1;return 0;
    }
    int q=seq_running(b,"j_shback",0,"SQ_OPENCARD");if(q<0)return -1;
    if(q==1)return 0;
    /* 0.1: ShopTitle03, StatusTitle03 (the Select/Confirm/Cancel legend), ShopTitle01, the joined players, StatusTitle01 (the player panel). */
    int32_t players[4];int nplayers=0;
    for(int p=0;p<4;p++){
        int32_t use;if(dw4_property_number(folder(b,p),"ISUSE",&use))return bfail(b,"ISUSE unavailable");
        if((uint8_t)use)players[nplayers++]=p;
    }
    if(menu_int_set(w,&arena_root(r)->_playerNoList,players,nplayers))return -1;
    if(!nplayers)return bfail(b,"no joined player");
    arena_root(r)->_playerNo=players[0];
    if(content_child(r,shop_title03) || kind_child(r,DW4_STATUS_TITLE03,0) ||
       put(b,DW4_VIEW_COLOR,"STWINFONT34","font002","CANCELCOLOR",NULL,0) ||
       content_child(r,shop_title01) || kind_child(r,DW4_STATUS_TITLE01,1))return -1;
    advance(w);arena_root(r)->_st1=0;arena_root(r)->_st2=0;return 0;
}
static int root_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct root *r=w->user;struct base *b=&r->b;int rc=0;
    if(dw4_menu_window_data(w)->_st0>=2)rc=finish(w,b);
    else if(dw4_menu_window_data(w)->_st0==0)rc=root_open(r,w);
    else rc=root_run(r,w);
    if(rc)snprintf(error,cap,"%s",b->error[0]?b->error:"CARD failed");
    return rc;
}
static void root_release(void *u)
{
    struct root *r=u;menu_int_release(r->b.self,&arena_root(r)->_playerNoList);
    arena_root(r)->_account=0;release(u);
}
dw4_menu_window *dw4_cardshop_window_open(const dw4_cardshop_context *c)
{
    if(!valid(c))return NULL;
    struct root *r=calloc(1,sizeof *r);if(!r)return NULL;
    init_base(&r->b,c);
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrlA0",root_update,r,root_release);if(!w){free(r);return NULL;}
    r->b.self=w;dw4_menu_window_data(w)->_entCode=10;dw4_menu_window_data(w)->_playerNo=c->view.player;dw4_menu_window_data(w)->_retCode=0;return w;
}
int dw4_cardshop_window_state(const dw4_menu_window *w,dw4_cardshop_state *out)
{
    if(!w || !out || w->update!=root_update)return -1;
    const struct root *r=w->user;*out=(dw4_cardshop_state){dw4_menu_window_data(w)->_st0,arena_root(r)->_st1,arena_root(r)->_st2,arena_root(r)->_playerNo};return 0;
}
