#include "menurecord.h"
#include "dw4/statusdevice.h"
#include "dw4/playerstats.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct device {
    dw4_statusdevice_context c;
    dw4_statusdevice *state; /* borrowed only during update */
    dw4_menu_window *root,*content;
    dw4_statusdevice_rows rows;
    dw4_item_record items[96];size_t count;
    dw4_statuspage_input input;
    int failed;
    char error[256];
};
static beNDMWStatusCtrlD0 *record(const struct device *d)
{return DW4_ARENA_OBJ(d->root->arena,beNDMWStatusCtrlD0,d->root->object);}
static dw4_script_value str(const char *s)
{return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int sequence(void *u,const char *model,const char *key)
{
    struct device *d=u;
    dw4_script_value a[]={str("MODELCTRL"),str(model),{DW4_SCRIPT_NUMBER,0,NULL,0},str(key)},r;
    return dw4_scriptservices_call(d->c.view.sd,"sd",a,4,&r,d->error,sizeof d->error);
}
static int inventory(struct device *d)
{
    dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",d->c.view.player);size_t n;
    const char *key=record(d)->_isBankFolder?"BANKDEVICE":"DEVICEFOLDER";
    if(!f || dw4_property_item_count(f,key,&n) || n>(record(d)->_isBankFolder?96u:36u)){snprintf(d->error,sizeof d->error,"STATUS %s records unavailable",key);return -1;}
    const dw4_item_record *items=dw4_property_items(f,key,&n);
    if(n)memcpy(d->items,items,n*sizeof *items);
    d->count=n;return 0;
}
static int decisions(struct device *d)
{
    dw4_statusdevice_filter filter={.ab_type=record(d)->_isAbType,
        .equip_disable=record(d)->_isEquipDisable,.unknown_enable=record(d)->_isUnknownEnable,
        .unknown_disable=record(d)->_isUnknownDisable,
        .nkinds=menu_int_count(d->root,record(d)->_kindList)};
    const int32_t *kinds=menu_int_data(d->root,record(d)->_kindList);
    if(filter.nkinds<0 || filter.nkinds>4)return -1;
    if(filter.nkinds)memcpy(filter.kinds,kinds,(size_t)filter.nkinds*4);
    if(inventory(d) || dw4_statusdevice_decide(d->items,d->count,d->state->page,&filter,
        dw4_playerstats_item_bool,(void *)d->c.databases,&d->rows) ||
       menu_list_set(d->root,&record(d)->_decideList,"igBoolList",1,d->rows.enabled,d->rows.count))return -1;
    d->state->pages=d->rows.pages;return 0;
}
static int command(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static int setup(void *u,dw4_statusview_io io,void *user)
{
    struct device *d=u;
    if(d->c.prompt>0 && (command(io,user,DW4_VIEW_TEXT,"STWINFONT29","font100","LEFT"," ",0) ||
       command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,d->c.prompt)))return -1;
    if(command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) ||
       command(io,user,DW4_VIEW_SCRIPT,NULL,record(d)->_isBankFolder?"txt_shop.lua":"txt_status.lua",NULL,NULL,record(d)->_isBankFolder?1303:70))return -1;
    for(unsigned i=0;i<12;i++){
        char name[16];snprintf(name,sizeof name,"font%03u",i);
        if(command(io,user,DW4_VIEW_TEXT,"STWINFONT14",name,"LEFT"," ",0) ||
           command(io,user,DW4_VIEW_TEXT,"STWINFONT16",name,"RIGHT"," ",0))return -1;
    }
    for(unsigned i=0;i<2;i++){
        char name[16];snprintf(name,sizeof name,"font%03u",i);
        if(command(io,user,DW4_VIEW_TEXT,record(d)->_isBankFolder?"STWINFONT40":"STWINFONT23",name,"RIGHT"," ",0))return -1;
    }
    if(command(io,user,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0) ||
       command(io,user,DW4_VIEW_MODEL,NULL,"i_stfolder","SQ_AWINONOPEN","SQ_CLOSE",0) ||
       command(io,user,DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,25,0>","SQ_CLOSE",0) ||
       command(io,user,DW4_VIEW_MODEL,NULL,"i_stcursorright",d->state->pages<2?"SQ_HIDE/V<85,25,0>":"SQ_SELECT/V<85,25,0>","SQ_CLOSE",0))return -1;
    return 0;
}
static int add_selector(struct device *d,int selected)
{
    if(dw4_menu_window_count(d->root))return -1;
    dw4_statusview_context c=d->c.view;c.parent=NULL;c.parent_window=d->root;c.callno=0;
    c.rows=d->rows.rows;c.selected=selected;c.position[0]=-121;c.position[1]=128;c.position[2]=0;
    c.enabled=menu_bool_data(d->root,record(d)->_decideList);c.selection_initialize=NULL;
    dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_SELECTE1,&c);if(!w)return -1;
    if(dw4_menu_window_add(d->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int close_content(struct device *d)
{
    if(!d->content || dw4_menu_window_data(d->content)->_st0>=2)return 0;
    dw4_menu_window_remove(d->content);return dw4_menu_window_tick(d->content,d->error,sizeof d->error);
}
static int io(void *u,dw4_statusdevice *c,int op,int32_t value)
{
    struct device *d=u;
    switch(op){
    case DW4_DEVICE_INIT:{
        if(decisions(d))return -1;
        dw4_statusview_context context=d->c.view;context.initialize=setup;context.user=d;
        d->content=dw4_statusview_window_open(DW4_STATUS_CONTENT,&context);
        if(!d->content || dw4_menu_window_tick(d->content,d->error,sizeof d->error))return -1;
        return add_selector(d,0);
    }
    case DW4_DEVICE_COUNT:return dw4_menu_window_count(d->root)>INT32_MAX?-1:(int)dw4_menu_window_count(d->root);
    case DW4_DEVICE_REFRESH:
        if(inventory(d))return -1;
        return dw4_statuscontent_device(d->c.databases,d->items,d->count,menu_bool_data(d->root,record(d)->_decideList),c->page,c->pages,
            c->window.selection<0?0:c->window.selection,record(d)->_isBankFolder,value&1,value&2,dw4_statusview_window_emit,d->content);
    case DW4_DEVICE_TOP:return dw4_menu_window_count(d->root)==1?dw4_statusview_selector_ready(d->root->children[0]):-1;
    case DW4_DEVICE_PREVIOUS:case DW4_DEVICE_NEXT:return dw4_statuspage_turn(&c->page,c->pages,op==DW4_DEVICE_NEXT,&d->input,sequence,d);
    case DW4_DEVICE_REPAGE:
        if(decisions(d) || dw4_menu_window_count(d->root)!=1)return -1;
        return dw4_statusview_selector_restart(d->root->children[0],d->rows.rows,menu_bool_data(d->root,record(d)->_decideList));
    case DW4_DEVICE_INVENTORY_COUNT:return inventory(d)?-1:(int)d->count;
    case DW4_DEVICE_RESELECT:
        if(decisions(d))return -1;
        if(!c->page && sequence(d,"i_stcursorleft","SQ_HIDE"))return -1;
        if(d->count<=(size_t)(c->page+1)*12 && sequence(d,"i_stcursorright","SQ_HIDE"))return -1;
        return add_selector(d,c->row);
    case DW4_DEVICE_PUBLISH:
        if(d->c.view.parent)d->c.view.parent->selection=value;
        else dw4_menu_window_data(d->c.view.parent_window)->_retCode=value;
        return 0;
    case DW4_DEVICE_CLOSE_MODELS:return close_content(d);
    case DW4_DEVICE_CLEAR_TEXT:return 0; /* CONTENT close clears owned text. */
    case DW4_DEVICE_CLOSE_CHILDREN:
        for(size_t i=0;i<dw4_menu_window_count(d->root);i++)if(dw4_menu_window_data(d->root->children[i])->_st0<2)dw4_menu_window_remove(d->root->children[i]);
        return 0;
    case DW4_DEVICE_COLORS:
        /* Reset original row colors even after their resource set was hidden. */
        for(int i=0;i<value;i++)for(int j=0;j<2;j++){
            char font[16],encoded[80];snprintf(font,sizeof font,"font%03d",i);
            snprintf(encoded,sizeof encoded,"%s/%s",j?"STWINFONT16":"STWINFONT14",font);
            dw4_script_value a[]={str("TEXTCTL"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},str("DEFAULTCOLOR"),str(encoded)},r;
            if(dw4_scriptservices_call(d->c.view.sd,"sd",a,5,&r,d->error,sizeof d->error))return -1;
        }
        return 0;
    case DW4_DEVICE_FINISHED:return !d->content && !dw4_menu_window_count(d->root);
    default:return -1;
    }
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct device *d=w->user;dw4_statusdevice projection=menu_device_read(w);d->state=&projection;dw4_statusctrl *s=&d->state->window;int rc=0;
    if(d->failed){snprintf(error,cap,"STATUS DEVICE failed; scene reset required");d->state=NULL;return -1;}
    if(d->content && dw4_menu_window_data(d->content)->_st0>=2){
        if(dw4_menu_window_tick(d->content,d->error,sizeof d->error))rc=-1;
        else if(!dw4_menu_window_data(d->content)->_isRun){dw4_menu_window_close(d->content);d->content=NULL;}
    }
    if(!rc){
        memset(&d->input,0,sizeof d->input);
        if(d->c.input(d->c.user,d->c.view.player,&d->input))rc=-1;
        else rc=dw4_statusdevice_tick(d->state,io,d);
    }
    if(rc){d->failed=1;snprintf(error,cap,"STATUS DEVICE %d/%d/%d: %.180s",s->state,s->sub,s->delay,d->error[0]?d->error:"required view/input service failed");}
    menu_device_write(w,&projection);d->state=NULL;return rc;
}
static void release(void *u)
{struct device *d=u;dw4_menu_window_close(d->content);menu_int_release(d->root,&record(d)->_kindList);menu_int_release(d->root,&record(d)->_decideList);free(d);}
dw4_menu_window *dw4_statusdevice_window_open(const dw4_statusdevice_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || (!c->view.parent && !c->view.parent_window) || !c->databases || !c->input || c->view.player<0 || c->view.player>3 || c->filter.nkinds<0 || c->filter.nkinds>4 || c->bank<0 || c->bank>1 || c->auto_close<0 || c->auto_close>1)return NULL;
    struct device *d=calloc(1,sizeof(*d));if(!d)return NULL;
    d->c=*c;
    d->root=dw4_menu_window_open_class("beNDMWStatusCtrlD0",update,d,release);if(!d->root){free(d);return NULL;}
    dw4_statusdevice initial={.auto_close=c->auto_close,.window={.active=1,.selection=0}};
    menu_device_write(d->root,&initial);dw4_menu_window_data(d->root)->_playerNo=c->view.player;
    record(d)->_isBankFolder=(unsigned char)c->bank;record(d)->_isAbType=c->filter.ab_type;
    record(d)->_isEquipDisable=c->filter.equip_disable;record(d)->_isUnknownEnable=c->filter.unknown_enable;
    record(d)->_isUnknownDisable=c->filter.unknown_disable;
    if(menu_int_set(d->root,&record(d)->_kindList,c->filter.kinds,c->filter.nkinds)){
        dw4_menu_window_close(d->root);return NULL;
    }return d->root;
}
int dw4_statusdevice_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statusdevice dw4_statusdevice_window_state(const dw4_menu_window *w)
{return dw4_statusdevice_window_is(w)?menu_device_read(w):(dw4_statusdevice){0};}
int dw4_statusdevice_window_ready(const dw4_menu_window *w)
{
    if(!dw4_statusdevice_window_is(w) || ((const struct device *)w->user)->failed)return -1;
    return dw4_menu_window_data(w)->_isRun && dw4_menu_window_data(w)->_st0==1 && dw4_menu_window_data(w)->_st1==2;
}
int dw4_statusdevice_window_restart(dw4_menu_window *w)
{
    if(dw4_statusdevice_window_ready(w)!=1 || dw4_statusdevice_window_state(w).auto_close)return -1;
    dw4_menu_window_data(w)->_st2=1;dw4_menu_window_data(w)->_st3=0;return 0;
}
/* Retail ShopCtrl30 drives the bank list directly: 418ac0 refreshes the rows (bit 1) and/or
 * description (bit 2), and an owner closes the list by advancing its primary state. */
int dw4_statusdevice_window_refresh(dw4_menu_window *w,int bits)
{
    dw4_statusdevice snapshot=dw4_statusdevice_window_state(w);
    if(!dw4_statusdevice_window_is(w) || ((struct device *)w->user)->failed || (bits & ~3))return -1;
    struct device *d=w->user;d->state=&snapshot;
    int rc=io(d,&snapshot,DW4_DEVICE_REFRESH,bits)<0?-1:0;
    menu_device_write(w,&snapshot);d->state=NULL;return rc;
}
int dw4_statusdevice_window_close(dw4_menu_window *w)
{
    if(!dw4_statusdevice_window_is(w) || ((struct device *)w->user)->failed || dw4_menu_window_data(w)->_st0!=1)return -1;
    dw4_menu_window_data(w)->_st0=2;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;return 0;
}
int dw4_statusdevice_window_candidate(const dw4_menu_window *w,int32_t *out)
{
    dw4_statusdevice snapshot=dw4_statusdevice_window_state(w);const dw4_statusdevice *s=&snapshot;
    if(!dw4_statusdevice_window_is(w) || !out || ((const struct device *)w->user)->failed)return -1;
    if(dw4_menu_window_data(w)->_st0==0 || s->window.selection<0)return 1;
    const struct device *d=w->user;size_t n;
    dw4_property_folder *f=dw4_playerrecords_get(d->c.view.players,"GETPLAYER",d->c.view.player);
    const char *key=record(d)->_isBankFolder?"BANKDEVICE":"DEVICEFOLDER";
    int32_t index=s->page*12+s->window.selection;
    if(dw4_property_item_count(f,key,&n) || index<0 || (size_t)index>=n)return -1;
    *out=index;return 0;
}
int dw4_statusdevice_equipment_candidate(void *u,dw4_statusequip *equipment,int chip,int32_t *out)
{
    dw4_menu_window *w=u;dw4_statusdevice snapshot=dw4_statusdevice_window_state(w);const dw4_statusdevice *s=&snapshot;
    if(!dw4_statusdevice_window_is(w) || !equipment || !out || ((const struct device *)w->user)->failed)return -1;
    if(!dw4_menu_window_data(w)->_isRun || dw4_menu_window_data(w)->_st0!=1 || (dw4_menu_window_data(w)->_st1!=1 && dw4_menu_window_data(w)->_st1!=2))return 1;
    int rc=dw4_statusdevice_window_candidate(w,out);if(rc)return rc;
    if(dw4_menu_window_data(w)->_st1==2)return 0;
    const struct device *d=w->user;int selected=s->window.selection;
    if(selected<0 || selected>=menu_int_count(d->root,record(d)->_decideList))return -1;
    rc=dw4_statusdevice_hover(s,&equipment->window.latch,menu_bool_data(d->root,record(d)->_decideList),out);
    if(!rc && chip && d->items[*out].kind!=3)return -1;
    return rc;
}
