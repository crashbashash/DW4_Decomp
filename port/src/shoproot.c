/* The generic shop root, beNDMWShopCtrl00 update 4267b0..426f94 (SUBWND modes 1 and 3..9). See include/dw4/shoproot.h. */
#include "dw4/shoproot.h"
#include "dw4/statusui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct root {
    dw4_shoproot_context c;
    dw4_menu_window *self;
    char error[256];
};
static int fail(struct root *r,const char *what){snprintf(r->error,sizeof r->error,"shop root: %s",what);return -1;}
/* ShopTitle00 (440fd0): j_shback and i_bgclear, each with SQ_OPEN and closed with SQ_CLOSE. */
static int shop_title00(void *u,dw4_statusview_io io,void *iou)
{
    (void)u;
    dw4_statusview_command a={DW4_VIEW_MODEL,NULL,"j_shback","SQ_OPEN","SQ_CLOSE",0},b={DW4_VIEW_MODEL,NULL,"i_bgclear","SQ_OPEN","SQ_CLOSE",0};
    return io(iou,&a)||io(iou,&b);
}
/* ShopTitle01 (441040): the i_sttitle header, the STWINFONT12/font000 text and txt_shop.lua call 1000 + 100 * entry code
 * (jump table 51cba0: entry codes 1..10 select 1100..2000; code 0 and codes above 10 send no call). */
static int shop_title01(void *u,dw4_statusview_io io,void *iou)
{
    struct root *r=u;
    dw4_statusview_command m={DW4_VIEW_MODEL,NULL,"i_sttitle","SQ_OPEN","SQ_CLOSE",0},t={DW4_VIEW_TRACK_TEXT,"STWINFONT12","font000",NULL,NULL,0};
    if(io(iou,&m) || io(iou,&t))return -1;
    if(dw4_menu_window_data(r->self)->_entCode<1 || dw4_menu_window_data(r->self)->_entCode>10)return 0;
    dw4_statusview_command s={DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1000+100*dw4_menu_window_data(r->self)->_entCode};
    return io(iou,&s);
}
static int content_child(struct root *r,int (*init)(void *,dw4_statusview_io,void *))
{
    dw4_statusview_context c=r->c.view;c.parent=NULL;c.parent_window=r->self;c.callno=0;c.initialize=init;c.user=r;c.refresh=NULL;
    dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_CONTENT,&c);
    if(!w)return fail(r,"widget could not be opened");
    if(dw4_menu_window_add(r->self,w)){dw4_menu_window_close(w);return fail(r,"widget could not be attached");}
    return 0;
}
static int kind_child(struct root *r,int kind)
{
    dw4_statusview_context c=r->c.view;c.parent=NULL;c.parent_window=r->self;c.callno=0;c.variant=0;c.initialize=NULL;
    c.refresh=dw4_statusstats_refresh;c.user=r->c.stats;
    dw4_menu_window *w=dw4_statusview_window_open(kind,&c);
    if(!w)return fail(r,"widget could not be opened");
    if(dw4_menu_window_add(r->self,w)){dw4_menu_window_close(w);return fail(r,"widget could not be attached");}
    return 0;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct root *r=w->user;int rc=0;
    if(dw4_menu_window_data(w)->_st0==0) {
        int bad;
        if(dw4_menu_window_data(r->self)->_entCode==2)
            /* The Digi-Lab's own root (beNDMWShopCtrlDigilabo state 0, 431760): ShopTitle00, StatusTitle03 (the
             * Select/Confirm/Cancel legend) and ShopTitle01 (header call 1200). The lab controller opens i_messwn and the
             * compact Title01 itself (433290/433120). */
            bad=content_child(r,shop_title00) || kind_child(r,DW4_STATUS_TITLE03) || content_child(r,shop_title01);
        else
            /* The five common widgets of ShopCtrl00, in the original order. */
            bad=content_child(r,shop_title00) || kind_child(r,DW4_STATUS_TITLE01) || kind_child(r,DW4_STATUS_TITLE02) ||
                kind_child(r,DW4_STATUS_TITLE03) || content_child(r,shop_title01);
        if(bad)rc=-1;
        else{dw4_menu_window_data(w)->_st0=1;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
    }else if(dw4_menu_window_data(w)->_st0==1) {
        if(dw4_menu_window_data(w)->_st1==0) {
            /* Wait only while the message window's opening sequence is the current one (returned byte exactly 1). */
            /* The Digi-Lab root has no such gate (its controller is the root itself in retail). */
            int q=dw4_menu_window_data(r->self)->_entCode==2?0:dw4_statusui_call(&r->c.view,1,"MODELCTRL","i_messwn",0,"ISSEQNAME","SQ_STOPEN",r->error,sizeof r->error);
            if(q<0)rc=-1;
            else if((uint8_t)q!=1) {
                dw4_menu_window *svc=r->c.service?r->c.service(r->c.user):NULL;
                if(!svc)rc=fail(r,"the selected service could not be created");
                else if(dw4_menu_window_add(w,svc)){dw4_menu_window_close(svc);rc=fail(r,"the service could not be attached");}
                else{DW4_ARENA_OBJ(w->arena,beNDMWShopCtrl00,w->object)->_nowProcKazu=dw4_menu_window_count(w);dw4_menu_window_data(w)->_st1=1;}
            }
        }else if(dw4_menu_window_data(w)->_st1==1) {
            /* Completion of the service is a change of the child count, never a result value. */
            if(dw4_menu_window_count(w)!=(size_t)DW4_ARENA_OBJ(w->arena,beNDMWShopCtrl00,w->object)->_nowProcKazu){dw4_menu_window_data(w)->_st0=2;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
        }
    }else if(dw4_menu_window_data(w)->_st0==2) {
        /* State 2: MODELCTRL i_bgclear OFFREEZE first, then the children are asked to close. */
        if(dw4_statusui_call(&r->c.view,0,"MODELCTRL","i_bgclear",0,"OFFREEZE",NULL,r->error,sizeof r->error)<0)rc=-1;
        for(size_t i=0;i<dw4_menu_window_count(w);i++)if(dw4_menu_window_data(w->children[i])->_st0<2)dw4_menu_window_remove(w->children[i]);
        dw4_menu_window_data(w)->_st0=3;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;
    }else if(!dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;

    if(rc)snprintf(error,cap,"%s",r->error[0]?r->error:"shop root failed");
    return rc;
}
static void release(void *u){free(u);}
dw4_menu_window *dw4_shoproot_window_open(const dw4_shoproot_context *c)
{
    if(!c || !c->service || !c->stats || !c->view.sd || !c->view.engine || !c->view.players || c->view.player<0 || c->view.player>3)return NULL;
    struct root *r=calloc(1,sizeof *r);if(!r)return NULL;
    r->c=*c;r->c.view.parent=NULL;r->c.view.parent_window=NULL;
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWShopCtrl00",update,r,release);if(!w){free(r);return NULL;}
    r->self=w;dw4_menu_window_data(w)->_retCode=-1;dw4_menu_window_data(w)->_entCode=c->entry;dw4_menu_window_data(w)->_playerNo=c->view.player;return w;
}
int dw4_shoproot_window_state(const dw4_menu_window *w,dw4_shoproot_state *out)
{
    if(!w || !out || w->update!=update)return -1;
    *out=(dw4_shoproot_state){dw4_menu_window_data(w)->_st0,dw4_menu_window_data(w)->_st1,dw4_menu_window_count(w)};return 0;
}
