#include "menurecord.h"
#include "dw4/statusgear.h"
#include "dw4/statusui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct gear {
    dw4_statusgear_context c;dw4_statusequip *state; /* borrowed only during update */dw4_statusequip_context records;
    dw4_menu_window *root,*base,*message,*cursor;
    int kind,failed;
    char cursor_sequence[64],error[256];
};
static int bind_records(struct gear *e)
{
    beNDMWStatusCtrlBaseEquip *d=DW4_ARENA_OBJ(e->root->arena,beNDMWStatusCtrlBaseEquip,e->root->object);
    const char *keys[]={NULL,"POWERSOCKET","MAINSLOT","SUBSLOT","POWERPOCKET","MAINPOCKET","DEVICEFOLDER"};
    dw4_property_type types[]={DW4_PROPERTY_FOLDER,DW4_PROPERTY_ITEMS,DW4_PROPERTY_ITEMS,DW4_PROPERTY_ITEMS,DW4_PROPERTY_ITEMS,DW4_PROPERTY_ITEMS,DW4_PROPERTY_ITEMS};
    int32_t *fields[]={&d->_playerList,&d->_powerSocket,&d->_mainSlot,&d->_subSlot,&d->_wpuPocket,&d->_apuPocket,&d->_deviceFolder};
    return menu_records_bind(e->root,dw4_playerrecords_get(e->c.view.players,"GETPLAYER",e->c.view.player),keys,types,fields,7);
}
static void unbind_records(struct gear *e)
{
    beNDMWStatusCtrlBaseEquip *d=DW4_ARENA_OBJ(e->root->arena,beNDMWStatusCtrlBaseEquip,e->root->object);
    int32_t *fields[]={&d->_playerList,&d->_powerSocket,&d->_mainSlot,&d->_subSlot,&d->_wpuPocket,&d->_apuPocket,&d->_deviceFolder};
    for(int i=0;i<7;i++)menu_record_release(e->root,fields[i]);
}
static int command(dw4_statusview_io io,void *u,int op,const char *g,const char *name,const char *key,const char *value,int slot)
{dw4_statusview_command c={op,g,name,key,value,slot};return io(u,&c);}
static const dw4_item_record *items(struct gear *e,const char *key,size_t *n)
{return dw4_property_items(dw4_playerrecords_get(e->c.view.players,"GETPLAYER",e->c.view.player),key,n);}
static int base_setup(void *u,dw4_statusview_io io,void *user)
{
    struct gear *e=u;static const char *seq[]={"SQ_POWEROPEN","SQ_MAINOPEN","SQ_SUBOPEN"};
    if(command(io,user,DW4_VIEW_MODEL,NULL,"i_stsoubi",seq[e->kind],"SQ_CLOSE",0))return -1;
    if(e->kind<2){size_t n;const dw4_item_record *v=items(e,e->kind?"MAINSLOT":"POWERSOCKET",&n);
        if(!v || !n)return -1;
        char sequence[32];int count=v[0].kind==-1?0:v[0].pocket;
        snprintf(sequence,sizeof sequence,"SQ_%dLINEOPEN",count>=1 && count<=5?count:0);
        if(command(io,user,DW4_VIEW_MODEL,NULL,"i_stpocket",sequence,"SQ_CLOSE",0))return -1;
    }
    for(int i=0;i<8;i++){
        char font[16];snprintf(font,sizeof font,"font%03d",i<3?i:100+i-3);
        if(command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT11",font,NULL,NULL,0))return -1;
    }
    for(int i=0;i<2;i++){
        char font[16];snprintf(font,sizeof font,"font%03d",i);
        if(command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT10",font,NULL,NULL,0))return -1;
    }
    return 0;
}
static int message_setup(void *u,dw4_statusview_io io,void *user)
{
    (void)u;
    for(int i=0;i<4;i++){
        char font[16];snprintf(font,sizeof font,"font%03d",i==3?100:i);
        if(command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT29",font,NULL,NULL,0))return -1;
    }
    return 0;
}
static int blank_fields(struct gear *e)
{
    /* Original 411750 initializes these twelve entries, including the repeated
     * prompt. Other tracked description/action fonts are initialized on use. */
    if(dw4_statusui_emit(e->base,DW4_VIEW_TEXT,"STWINFONT29","font100","LEFT"," ",0))return -1;
    for(unsigned i=0;i<2;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(dw4_statusui_emit(e->base,DW4_VIEW_TEXT,"STWINFONT10",font,"LEFT"," ",0))return -1;
    }
    for(unsigned i=0;i<8;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i<3?i:100+i-3);
        if(dw4_statusui_emit(e->base,DW4_VIEW_TEXT,"STWINFONT11",font,"LEFT"," ",0))return -1;
    }
    return dw4_statusui_emit(e->base,DW4_VIEW_TEXT,"STWINFONT29","font100","LEFT"," ",0);
}
static int cursor_setup(void *u,dw4_statusview_io io,void *user)
{struct gear *e=u;return command(io,user,DW4_VIEW_MODEL,NULL,"i_stcursor04",e->cursor_sequence,"SQ_CLOSE",0);}
static int sd(struct gear *e,int query,const char *cat,const char *name,int slot,const char *key,const char *value)
{return dw4_statusui_call(&e->c.view,query,cat,name,slot,key,value,e->error,sizeof e->error);}
static int script(struct gear *e,int call)
{return dw4_statusui_emit(e->message,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,call);}
static int text(struct gear *e,const char *name,int on,const char *value)
{
    if(value && dw4_statusui_emit(e->message,DW4_VIEW_SET_TEXT,"STWINFONT29",name,NULL,value,0))return -1;
    return dw4_statusui_emit(e->message,DW4_VIEW_SWITCH,"STWINFONT29",name,NULL,on?"DISPON":"DISPOFF",0);
}
static dw4_menu_window *device(struct gear *e)
{for(size_t i=0;i<dw4_menu_window_count(e->root);i++)if(dw4_statusdevice_window_is(e->root->children[i]))return e->root->children[i];return NULL;}
static int add(struct gear *e,dw4_menu_window *w)
{if(!w)return -1;if(dw4_menu_window_add(e->root,w)){dw4_menu_window_close(w);return -1;}return 0;}
static int pocket_select_setup(void *u,dw4_statusview_io io,void *user)
{(void)u;return command(io,user,DW4_VIEW_TRACK_TEXT,"STWINFONT29","font100",NULL,NULL,0) ||
    command(io,user,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,138)?-1:0;}
static int selector(struct gear *e,int kind,int call,int rows,int selected,float x,float y,const uint8_t *flags)
{
    dw4_statusview_context c=e->c.view;c.parent=NULL;c.parent_window=e->root;c.callno=call;c.rows=rows;c.selected=selected;
    c.position[0]=x;c.position[1]=y;c.position[2]=0;c.enabled=flags;
    c.selection_initialize=kind==DW4_STATUS_SELECTE1 && call==138?pocket_select_setup:NULL;
    return add(e,dw4_statusview_window_open(kind,&c));
}
static int inventory(struct gear *e,int chip)
{
    dw4_statusdevice_context c={.view=e->c.view,.databases=e->c.databases,.input=e->c.input,.user=e->c.user,
        .filter={.kinds={chip?3:e->kind},.nkinds=1,.ab_type=chip?e->kind:0,.equip_disable=1,.unknown_disable=1},
        .auto_close=chip,.prompt=chip?0:e->kind==0?139:141};
    c.view.parent=NULL;c.view.parent_window=e->root;return add(e,dw4_statusdevice_window_open(&c));
}
static int candidate(void *u,dw4_statusequip *s,int chip,int32_t *out)
{
    struct gear *e=u;dw4_menu_window *w=device(e);
    if(w && dw4_menu_window_data(w)->_st0>=2)return dw4_statusdevice_window_candidate(w,out);
    if(!w && chip && s->window.sub==2 && s->window.delay==7 && s->window.selection>=0){*out=s->window.selection;return 0;}
    return w?dw4_statusdevice_equipment_candidate(w,s,chip,out):-1;
}
static int preview(void *u,dw4_property_folder *f)
{struct gear *e=u;return dw4_statusstats_compare_folder(e->c.stats,f,e->error,sizeof e->error);}
static int cursor(struct gear *e,int selected)
{
    int running=sd(e,1,"MODELCTRL","i_stcursor04",0,"ISRUN",NULL);if(running<0)return -1;
    if(selected<0)return running?sd(e,0,"MODELCTRL","i_stcursor04",0,"SQ_CLOSE",NULL):0;
    if(selected>11)return -1;
    char sequence[32];snprintf(sequence,sizeof sequence,"SQ_OPEN%02d",selected);
    if(running)return sd(e,0,"MODELCTRL","i_stcursor04",0,sequence,NULL);
    snprintf(e->cursor_sequence,sizeof e->cursor_sequence,"%s/V<-83,148,0>",sequence);
    if(!e->cursor)return dw4_statusui_open(&e->c.view,cursor_setup,e,&e->cursor,e->error,sizeof e->error);
    return dw4_statusui_emit(e->cursor,DW4_VIEW_MODEL,NULL,"i_stcursor04",e->cursor_sequence,"SQ_CLOSE",0);
}
static int base_open(struct gear *e)
{
    if(e->base)return -1;
    return dw4_statusui_open(&e->c.view,base_setup,e,&e->base,e->error,sizeof e->error);
}
static int base_projection(struct gear *e,int description)
{return dw4_statuscontent_equipment(e->c.view.players,e->c.databases,e->c.view.player,e->kind,
    description?e->state->window.selection:e->state->slot,description,dw4_statusview_window_emit,description?e->message:e->base);}
static int pocket_description(struct gear *e)
{
    size_t n;const dw4_item_record *v=items(e,e->kind?"MAINPOCKET":"POWERPOCKET",&n);
    int selected=e->state->window.selection;
    if(!v || n!=5 || selected< -1 || selected>=5)return -1;
    const char *value=selected<0 || v[selected].kind==-1?NULL:dw4_statuscontent_item_string(e->c.databases,v+selected,"TXT");
    if(selected>=0 && v[selected].kind!=-1 && !value)return -1;
    return text(e,"font000",value!=NULL,value);
}
static int view(void *u,dw4_statusequip *c,int op,int32_t value)
{
    struct gear *e=u;dw4_statusctrl *s=&c->window;size_t n;
    switch(op){
    case DW4_EQUIP_PREPARE:return 0; /* record adapter preflights every list */
    case DW4_EQUIP_COUNT:return dw4_menu_window_count(e->root)>INT32_MAX?-1:(int)dw4_menu_window_count(e->root);
    case DW4_EQUIP_SELECTOR:{
        uint8_t flags[3]={1,1,1};
        if(value){
            const int32_t *refs=dw4_property_array(dw4_playerrecords_get(e->c.view.players,"GETPLAYER",e->c.view.player),"POWERSOCKETREF",&n);
            if(!refs || n!=3 || c->slot<0 || c->slot>=3)return -1;
            flags[c->slot]=0;
            if(!c->slot){flags[1]=refs[1]>=0;flags[2]=refs[2]>=0;}
            else if(refs[c->slot]<0)flags[0]=0;
        }
        return selector(e,DW4_STATUS_SELECTE1,0,c->slots,c->slot,-83,148,value?flags:NULL);
    }
    case DW4_EQUIP_CURSOR:return cursor(e,value);
    case DW4_EQUIP_BLANK:
        return blank_fields(e);
    case DW4_EQUIP_PREVIEW_OFF:return dw4_statusstats_compare(e->c.stats,e->c.view.player,0,e->error,sizeof e->error);
    case DW4_EQUIP_REFRESH:return dw4_statusstats_refresh(e->c.stats,e->c.view.player,e->error,sizeof e->error);
    case DW4_EQUIP_COLORS:
        for(int i=0;i<value;i++){char font[16];snprintf(font,sizeof font,"font%03d",i);
            if(dw4_statusui_emit(e->message,DW4_VIEW_COLOR,"STWINFONT29",font,"DEFAULTCOLOR",NULL,0))return -1;}return 0;
    case DW4_EQUIP_HIDE:return text(e,"font000",0,NULL);
    case DW4_EQUIP_FIND:return device(e)!=NULL;
    case DW4_EQUIP_READY:return device(e)?dw4_statusdevice_window_ready(device(e)):-1;
    case DW4_EQUIP_SELECTOR_CLOSE:if(!device(e))return -1;dw4_menu_window_remove(device(e));return 0;
    case DW4_EQUIP_SELECTOR_RESTART:return device(e)?dw4_statusdevice_window_restart(device(e)):-1;
    case DW4_EQUIP_ERROR:return selector(e,DW4_STATUS_SHOPSELECT00,0,1,0,0,0,NULL);
    case DW4_EQUIP_SCRIPT:return script(e,value);
    case DW4_EQUIP_CLOSE_MODELS:
        return dw4_statusui_close(e->base,e->error,sizeof e->error) || dw4_statusui_close(e->cursor,e->error,sizeof e->error) ||
            dw4_statusui_close(e->message,e->error,sizeof e->error)?-1:0;
    case DW4_EQUIP_CLEAR_TEXT:return 0; /* close emitted original text hides */
    case DW4_EQUIP_CLOSE_CHILDREN:
        for(size_t i=0;i<dw4_menu_window_count(e->root);i++)if(dw4_menu_window_data(e->root->children[i])->_st0<2)dw4_menu_window_remove(e->root->children[i]);
        return 0;
    case DW4_EQUIP_FINISHED:return !e->base && !e->cursor && !e->message && !dw4_menu_window_count(e->root);
    case DW4_EQUIP_PLAYER_MODEL:return e->c.appearance(e->c.user,e->c.view.player,e->error,sizeof e->error);
    case DW4_EQUIP_VIRTUAL+23:return value?base_open(e):dw4_statusui_close(e->base,e->error,sizeof e->error);
    case DW4_EQUIP_VIRTUAL+24:return base_projection(e,0);
    case DW4_EQUIP_VIRTUAL+26:return base_projection(e,1);
    case DW4_EQUIP_VIRTUAL+22:return dw4_statuscontent_pockets(e->c.view.players,e->c.databases,e->c.view.player,e->kind,dw4_statusview_window_emit,e->base);
    case DW4_EQUIP_VIRTUAL+27:{
        dw4_statusequip_actions a;
        if(dw4_statusequip_action_rows(e->c.view.players,e->c.view.player,e->kind,c->mode,c->slot,s->latch,&a))return -1;
        return selector(e,DW4_STATUS_SELECTE0,a.callno,a.rows,0,0,0,a.enabled);
    }
    case DW4_EQUIP_VIRTUAL+29:return inventory(e,0);
    case DW4_EQUIP_VIRTUAL+33:{
        const dw4_item_record *v=items(e,e->kind?"MAINSLOT":"POWERSOCKET",&n);
        if(!v || !n || v[c->slot].kind==-1 || v[c->slot].pocket<1 || v[c->slot].pocket>5)return -1;
        return selector(e,DW4_STATUS_SELECTE1,138,v[c->slot].pocket,c->pocket,-83,55,NULL);
    }
    case DW4_EQUIP_VIRTUAL+34:return pocket_description(e);
    case DW4_EQUIP_VIRTUAL+35:{
        const dw4_item_record *v=items(e,e->kind?"MAINPOCKET":"POWERPOCKET",&n);
        if(!v || n!=5 || c->pocket<0 || c->pocket>=5)return -1;
        uint8_t flags[2]={1,v[c->pocket].kind!=-1};
        return selector(e,DW4_STATUS_SELECTE0,0,2,0,0,0,flags);
    }
    case DW4_EQUIP_VIRTUAL+36:return inventory(e,1);
    default:snprintf(e->error,sizeof e->error,"STATUS equipment view operation %d unavailable",op);return -1;
    }
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct gear *e=w->user;dw4_statusequip projection=menu_equip_read(w);e->state=&projection;dw4_statusctrl *s=&e->state->window;int rc=0;
    if(e->failed){snprintf(error,cap,"STATUS equipment failed; scene reset required");e->state=NULL;return -1;}
    if(dw4_statusui_drain(&e->base,e->error,sizeof e->error) || dw4_statusui_drain(&e->message,e->error,sizeof e->error) ||
       dw4_statusui_drain(&e->cursor,e->error,sizeof e->error))rc=-1;
    /* Retire a previous resource set before shared names are regenerated. */
    if(!rc && e->base && dw4_menu_window_data(e->base)->_st0>=2 && dw4_menu_window_data(w)->_st0<2){menu_equip_write(w,&projection);e->state=NULL;return 0;}
    if(!rc)rc=bind_records(e);
    if(!rc){
        if(!e->message && dw4_menu_window_data(w)->_st0<2)rc=dw4_statusui_open(&e->c.view,message_setup,e,&e->message,e->error,sizeof e->error);
        if(!rc)rc=dw4_statusequip_tick(e->state,dw4_statusequip_transaction_io,&e->records);
    }
    if(!rc)rc=bind_records(e);
    if(rc){e->failed=1;snprintf(error,cap,"STATUS equipment %d/%d/%d: %.160s",s->state,s->sub,s->delay,e->error[0]?e->error:"required service failed");}
    menu_equip_write(w,&projection);e->state=NULL;return rc;
}
static void release(void *u)
{struct gear *e=u;dw4_menu_window_close(e->base);dw4_menu_window_close(e->message);dw4_menu_window_close(e->cursor);unbind_records(e);free(e);}
dw4_menu_window *dw4_statusgear_window_open(const dw4_statusgear_context *c,int kind,int mode)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || !c->stats ||
       c->stats->players!=c->view.players || !dw4_statusstats_state(c->stats).valid || dw4_statusstats_state(c->stats).player!=c->view.player ||
       !c->input || !c->appearance || c->view.player<0 || c->view.player>3 || kind<0 || kind>2 || mode<0 || mode>1)return NULL;
    struct gear *e=calloc(1,sizeof(*e));if(!e)return NULL;
    e->c=*c;e->kind=kind;
    e->records=(dw4_statusequip_context){c->view.players,c->databases,c->view.player,kind,view,e,candidate,preview,e};
    e->root=dw4_menu_window_open_class(kind==0?"beNDMWStatusPowerSocket":kind==1?"beNDMWStatusMainSlot":"beNDMWStatusSubSlot",update,e,release);if(!e->root){free(e);return NULL;}
    dw4_statusequip initial={.mode=mode,.slots=kind?1:3,.window={.active=1,.selection=0}};
    menu_equip_write(e->root,&initial);dw4_menu_window_data(e->root)->_playerNo=c->view.player;return e->root;
}
int dw4_statusgear_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statusequip dw4_statusgear_window_state(const dw4_menu_window *w)
{return dw4_statusgear_window_is(w)?menu_equip_read(w):(dw4_statusequip){0};}
