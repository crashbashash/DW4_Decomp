#include "menurecord.h"
#include "dw4/statusbit.h"
#include "dw4/statusbitctrl.h"
#include "dw4/statusui.h"
#include "dw4/playertransactions.h"
#include <stdlib.h>
#include <stdio.h>
struct bit {
    dw4_statusbit_context c;dw4_menu_window *root,*resources;
    int failed;char error[256];
};
static beNDMWStatusCtrlSendBit *send_record(const struct bit *b)
{return DW4_ARENA_OBJ(b->root->arena,beNDMWStatusCtrlSendBit,b->root->object);}
int dw4_statusbit_adjust(int32_t *amount,int32_t limit,int selected,const dw4_statuspage_input *pad)
{
    if(!amount || !pad || limit<0 || limit>9999999 || *amount<0 || *amount>limit || selected<0 || selected>6)return -1;
    int up=(pad->horizontal&1)||(pad->digital&0x10),down=(pad->horizontal&4)||(pad->digital&0x40);
    int step=1;for(int i=1;i<7-selected;i++)step*=10;
    int32_t previous=*amount;
    if(up){*amount+=step;if(*amount>limit)*amount=limit;}
    else if(down){*amount-=step;if(*amount<1)*amount=0;}
    return previous!=*amount;
}
int dw4_statusbit_edit(int32_t *amount,int32_t limit,int selected,int32_t *previous,int ready,const dw4_statuspage_input *pad)
{
    if(!amount || !previous || !pad || selected<0 || selected>6 || limit<0 || limit>9999999 || *amount<0 || *amount>limit)return -1;
    if(*previous!=selected){*previous=selected;return DW4_STATUSBIT_REDRAW;}
    if(!ready)return 0;
    int changed=dw4_statusbit_adjust(amount,limit,selected,pad);
    return changed<0?-1:changed?(DW4_STATUSBIT_REDRAW|DW4_STATUSBIT_SOUND):0;
}
int dw4_statusbit_close_step(dw4_statusctrl *s,int finished)
{
    if(!s || (s->state!=2 && s->state!=3))return -1;
    if(s->state==2){s->state=3;s->sub=s->delay=s->latch=0;}
    else if(finished)s->active=0;
    return 0;
}
static int cmd(struct bit *b,int op,const char *g,const char *n,const char *k,const char *v,int call)
{return dw4_statusui_emit(b->resources,op,g,n,k,v,call);}
static int setup(void *u,dw4_statusview_io io,void *user)
{
    struct bit *b=u;dw4_statusview_command c;char seq[32];
    {
        snprintf(seq,sizeof seq,"SQ_%dBITOPEN",menu_int_count(b->root,send_record(b)->_playerNoList));
        c=(dw4_statusview_command){DW4_VIEW_MODEL,NULL,"i_stmenu02",seq,"SQ_CLOSE",0};if(io(user,&c))return -1;
        for(unsigned i=0;i<2;i++){
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            c=(dw4_statusview_command){DW4_VIEW_TRACK_TEXT,"STWINFONT39",font,NULL,NULL,0};if(io(user,&c))return -1;
        }
        c=(dw4_statusview_command){DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,76};if(io(user,&c))return -1;
        for(int i=0;i<=menu_int_count(b->root,send_record(b)->_playerNoList);i++){
            char font[16];snprintf(font,sizeof font,"font%03d",i);
            if(i){c=(dw4_statusview_command){DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0};if(io(user,&c))return -1;}
            c=(dw4_statusview_command){DW4_VIEW_TEXT,"STWINFONT27",font,"RIGHT"," ",0};if(io(user,&c))return -1;
        }
        c=(dw4_statusview_command){DW4_VIEW_TEXT,"STWINFONT28","font000","CENTER"," ",0};if(io(user,&c))return -1;
    }
    return 0;
}
static int add(struct bit *b,int kind,int rows,int selected,float x,float y)
{
    dw4_statusview_context c=b->c.view;c.variant=kind==DW4_STATUS_SHOPSELECT34?3:c.variant;
    dw4_menu_window *w=dw4_statusui_selector_window(&c,b->root,kind,0,rows,selected,x,y,NULL);
    if(!w)return -1;
    if(dw4_menu_window_add(b->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int popup_setup(void *u,dw4_statusview_io io,void *user)
{
    int call=*(int *)u;dw4_statusview_command c={DW4_VIEW_TRACK_TEXT,"STWINFONT29","font000",NULL,NULL,0};
    if(io(user,&c))return -1;
    c=(dw4_statusview_command){DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,call};return io(user,&c);
}
static int popup(const dw4_statusbit_context *c,dw4_menu_window *root,int call)
{
    dw4_menu_window *w=dw4_statusui_selector_window(&c->view,root,DW4_STATUS_SHOPSELECT00,0,1,0,0,0,NULL);
    if(!w)return -1;
    if(dw4_statusview_window_prepare(w,popup_setup,&call) || dw4_menu_window_add(root,w)){dw4_menu_window_close(w);return -1;}
    return 0;
}
static int balances(struct bit *b)
{
    for(int i=0;i<=menu_int_count(b->root,send_record(b)->_playerNoList);i++){
        int32_t value;char font[16],text[16];int player=i?menu_int_data(b->root,send_record(b)->_playerNoList)[i-1]:b->c.view.player;
        dw4_property_folder *f=dw4_playerrecords_get(b->c.view.players,"GETPLAYER",player);
        if(dw4_property_number(f,"BIT",&value))return -1;
        snprintf(font,sizeof font,"font%03d",i);snprintf(text,sizeof text,"%d",value);
        if(cmd(b,DW4_VIEW_SET_TEXT,"STWINFONT27",font,NULL,text,0))return -1;
        if(i){dw4_unicode_object name;
            if(dw4_property_unicode_object(f,"PLAYERNAME",0,&name) || !name.present ||
               dw4_dialogue_set_unicode(b->c.dialogue,"STWINFONT14",font,name.codes,name.count))return -1;
        }
    }return 0;
}
static int refresh_stats(struct bit *b)
{
    char player[8];snprintf(player,sizeof player,"I<%d>",b->c.view.player);
    return dw4_statusui_call(&b->c.view,0,"SUBWND",NULL,-1,"UPDATE",player,b->error,sizeof b->error)<0?-1:0;
}
static int reset(struct bit *b)
{
    if(cmd(b,DW4_VIEW_ALIGN,"STWINFONT28","font000",NULL,"CENTER",0) ||
       cmd(b,DW4_VIEW_SET_TEXT,"STWINFONT28","font000",NULL,"0",0) ||
       cmd(b,DW4_VIEW_SWITCH,"STWINFONT28","font000",NULL,"DISPON",0) || balances(b))return -1;
    return add(b,DW4_STATUS_SELECTE1,menu_int_count(b->root,send_record(b)->_playerNoList),send_record(b)->_receipt,-121,109);
}
static int number_update(struct bit *b)
{
    dw4_statusctrl snapshot=menu_base_read(b->root);dw4_statusctrl *s=&snapshot;
    if(s->selection<0)return 0;
    if(s->selection>6)return -1;
    int ready=0;dw4_statuspage_input pad={0};
    if(s->latch==s->selection){
        ready=dw4_statusui_call(&b->c.view,1,"SELECTCTRL","i_stcursor03",b->c.view.player,"ISSELECTNOW",NULL,b->error,sizeof b->error);
        if(ready<0)return -1;
        ready=(uint8_t)ready;
        if(ready && b->c.input(b->c.user,b->c.view.player,&pad))return -1;
    }
    int effects=dw4_statusbit_edit(&send_record(b)->_editBit,send_record(b)->_editMax,s->selection,&s->latch,ready,&pad);if(effects<0)return -1;
    if((effects&DW4_STATUSBIT_REDRAW) && dw4_statuscontent_number(3,send_record(b)->_editBit,7-s->selection,dw4_statusview_window_emit,b->resources))return -1;
    if((effects&DW4_STATUSBIT_SOUND) && dw4_statusui_call(&b->c.view,0,"SOUND","CURSOR_MOVE",0,"PLAY",NULL,b->error,sizeof b->error)<0)return -1;
    menu_base_write(b->root,s);return 0;
}
static int send_io(void *u,dw4_statussendbit_ctrl *c,int op,int32_t value)
{
    struct bit *b=u;
    menu_base_write(b->root,&c->window);send_record(b)->_editBit=c->amount;send_record(b)->_editMax=c->limit;send_record(b)->_receipt=c->recipient;
    switch(op){
    case DW4_SEND_INIT:return dw4_statusui_open(&b->c.view,setup,b,&b->resources,b->error,sizeof b->error);
    case DW4_SEND_HIDE_DIGITS:
        for(unsigned i=0;i<7;i++){char encoded[64];snprintf(encoded,sizeof encoded,"STWINFONT28/font%03u/DISPOFF",i);
            if(dw4_statusui_call(&b->c.view,0,"TEXTCTL",NULL,-1,"SWITCH",encoded,b->error,sizeof b->error)<0)return -1;}return 0;
    case DW4_SEND_RESET:return reset(b);
    case DW4_SEND_COUNT:return dw4_menu_window_count(b->root)>INT32_MAX?-1:(int)dw4_menu_window_count(b->root);
    case DW4_SEND_CURSOR_OPEN:{char seq[32];snprintf(seq,sizeof seq,"SQ_OPEN%02d",send_record(b)->_receipt);
        return dw4_statusui_positioned(&b->c.view,"i_stcursor04",0,seq,-121,109,0,b->error,sizeof b->error);}
    case DW4_SEND_NUMBER_SELECTOR:return add(b,DW4_STATUS_SHOPSELECT34,7,6,147,-2);
    case DW4_SEND_NUMBER:return dw4_statuscontent_number(3,send_record(b)->_editBit,value,dw4_statusview_window_emit,b->resources);
    case DW4_SEND_LIMIT:{
        int32_t sender,receiver;if(send_record(b)->_receipt<0 || send_record(b)->_receipt>=menu_int_count(b->root,send_record(b)->_playerNoList))return -1;
        if(dw4_property_number(dw4_playerrecords_get(b->c.view.players,"GETPLAYER",b->c.view.player),"BIT",&sender) ||
           dw4_property_number(dw4_playerrecords_get(b->c.view.players,"GETPLAYER",menu_int_data(b->root,send_record(b)->_playerNoList)[send_record(b)->_receipt]),"BIT",&receiver) || sender<0 || receiver<0 || receiver>9999999)return -1;
        int32_t limit=sender>9999999?9999999:sender;return 9999999-receiver<limit?9999999-receiver:limit;
    }
    case DW4_SEND_EDIT:{int rc=number_update(b);c->amount=send_record(b)->_editBit;c->window.latch=dw4_menu_window_data(b->root)->_st3;return rc;}
    case DW4_SEND_CURSOR_CLOSE:return dw4_statusui_call(&b->c.view,0,"MODELCTRL","i_stcursor04",0,"SQ_CLOSE",NULL,b->error,sizeof b->error)<0?-1:0;
    case DW4_SEND_HIDE_PROMPT:return cmd(b,DW4_VIEW_SWITCH,"STWINFONT29","font100",NULL,"DISPOFF",0);
    case DW4_SEND_TRANSFER:{int result;if(send_record(b)->_receipt<0 || send_record(b)->_receipt>=menu_int_count(b->root,send_record(b)->_playerNoList))return -1;
        return dw4_playertransactions_give_bit(b->c.view.players,b->c.view.player,menu_int_data(b->root,send_record(b)->_playerNoList)[send_record(b)->_receipt],send_record(b)->_editBit,&result) || !result?-1:0;}
    case DW4_SEND_POPUP:return popup(&b->c,b->root,value);
    case DW4_SEND_ACK_HIDE:return cmd(b,DW4_VIEW_SWITCH,"STWINFONT29","font000",NULL,"DISPOFF",0);
    case DW4_SEND_REFRESH:return refresh_stats(b);
    case DW4_SEND_CLOSE:
        if(dw4_statusui_close(b->resources,b->error,sizeof b->error))return -1;
        for(size_t i=0;i<dw4_menu_window_count(b->root);i++)if(dw4_menu_window_data(b->root->children[i])->_st0<2)dw4_menu_window_remove(b->root->children[i]);
        return 0;
    case DW4_SEND_FINISHED:return !b->resources && !dw4_menu_window_count(b->root);
    default:return -1;
    }
}
static int send_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct bit *b=w->user;if(b->failed){snprintf(error,cap,"STATUS SendBit failed; scene reset required");return -1;}
    int rc=dw4_statusui_drain(&b->resources,b->error,sizeof b->error);
    if(!rc){
        dw4_menu_window_data(b->root)->_st3=dw4_menu_window_data(w)->_st3;
        dw4_statussendbit_ctrl c={menu_base_read(w),send_record(b)->_editBit,send_record(b)->_editMax,send_record(b)->_receipt};rc=dw4_statussendbitctrl_tick(&c,send_io,b);
        menu_base_write(b->root,&c.window);send_record(b)->_editBit=c.amount;send_record(b)->_editMax=c.limit;send_record(b)->_receipt=c.recipient;
        dw4_menu_window_data(w)->_st3=dw4_menu_window_data(b->root)->_st3;
    }
    if(rc){b->failed=1;snprintf(error,cap,"STATUS SendBit %d/%d: %.180s",dw4_menu_window_data(w)->_st0,dw4_menu_window_data(w)->_st2,b->error[0]?b->error:"required record/input/view failed");}return rc;
}
static void send_release(void *u){struct bit *b=u;dw4_menu_window_close(b->resources);menu_int_release(b->root,&send_record(b)->_playerNoList);free(b);}
static dw4_menu_window *send_open(const dw4_statusbit_context *c,const int32_t *recipients,int count)
{
    if(count<1 || count>3)return NULL;
    struct bit *b=calloc(1,sizeof *b);if(!b)return NULL;b->c=*c;

    b->root=dw4_menu_window_open_class("beNDMWStatusCtrlSendBit",send_update,b,send_release);
    if(!b->root){free(b);return NULL;}
    dw4_statusctrl initial={.active=1,.selection=-1};
    menu_base_write(b->root,&initial);dw4_menu_window_data(b->root)->_playerNo=c->view.player;
    if(menu_int_set(b->root,&send_record(b)->_playerNoList,recipients,count)){dw4_menu_window_close(b->root);return NULL;}return b->root;
}
struct wrapper {dw4_statusbit_context c;dw4_menu_window *root;int failed;char error[256];};
static beNDMWStatusCtrlBit *wrapper_record(const struct wrapper *b)
{return DW4_ARENA_OBJ(b->root->arena,beNDMWStatusCtrlBit,b->root->object);}
static int wrapper_io(void *u,dw4_statusbit_ctrl *c,int op,int32_t value)
{
    struct wrapper *b=u;
    switch(op){
    case DW4_BIT_COLLECT:{int32_t number;int count=0;int32_t players[3];
        if(dw4_property_number(dw4_playerrecords_get(b->c.view.players,"GETCOMMON",0),"NINZU",&number))return -1;
        for(int i=0;i<4;i++){int32_t use;
            if(dw4_property_number(dw4_playerrecords_get(b->c.view.players,"GETPLAYER",i),"ISUSE",&use))return -1;
            if(i!=b->c.view.player && (uint8_t)use)players[count++]=i;
        }if(menu_int_set(b->root,&wrapper_record(b)->_playerNoList,players,count))return -1;return count;
    }
    case DW4_BIT_SEND_CHILD:{dw4_menu_window *w=send_open(&b->c,menu_int_data(b->root,wrapper_record(b)->_playerNoList),c->recipients);if(!w)return -1;
        if(dw4_menu_window_add(b->root,w)){dw4_menu_window_close(w);return -1;}return 0;}
    case DW4_BIT_POPUP:return popup(&b->c,b->root,value);
    case DW4_BIT_COUNT:return dw4_menu_window_count(b->root)>INT32_MAX?-1:(int)dw4_menu_window_count(b->root);
    case DW4_BIT_CLOSE:
        for(size_t i=0;i<dw4_menu_window_count(b->root);i++)if(dw4_menu_window_data(b->root->children[i])->_st0<2)dw4_menu_window_remove(b->root->children[i]);
        return 0;
    case DW4_BIT_FINISHED:return dw4_menu_window_count(b->root)==0;
    default:return -1;
    }
}
static int wrapper_update(dw4_menu_window *w,char *error,size_t cap)
{
    struct wrapper *b=w->user;dw4_statusbit_ctrl projection={menu_base_read(w),menu_int_count(b->root,wrapper_record(b)->_playerNoList)};dw4_statusctrl *s=&projection.window;
    if(b->failed){snprintf(error,cap,"STATUS CtrlBit failed; scene reset required");return -1;}

    int rc=dw4_statusbitctrl_tick(&projection,wrapper_io,b);
    menu_base_write(w,&projection.window);

    if(rc){b->failed=1;snprintf(error,cap,"STATUS CtrlBit %d/%d: %.180s",s->state,s->delay,b->error[0]?b->error:"required record/child failed");}return rc;
}
static void wrapper_release(void *u)
{struct wrapper *b=u;menu_int_release(b->root,&wrapper_record(b)->_playerNoList);free(b);}
dw4_menu_window *dw4_statusbit_window_open(const dw4_statusbit_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->dialogue || !c->input || !c->view.refresh || c->view.player<0 || c->view.player>3)return NULL;
    struct wrapper *b=calloc(1,sizeof *b);if(!b)return NULL;b->c=*c;
    b->root=dw4_menu_window_open_class("beNDMWStatusCtrlBit",wrapper_update,b,wrapper_release);if(!b->root){free(b);return NULL;}
    dw4_statusctrl initial={.active=1,.selection=-1};
    menu_base_write(b->root,&initial);dw4_menu_window_data(b->root)->_playerNo=c->view.player;return b->root;
}
int dw4_statusbit_window_is(const dw4_menu_window *w)
{return w && w->update==wrapper_update;}
dw4_statusctrl dw4_statusbit_window_state(const dw4_menu_window *w)
{return dw4_statusbit_window_is(w)?menu_base_read(w):(dw4_statusctrl){0};}
int dw4_statussendbit_window_is(const dw4_menu_window *w)
{return w && w->update==send_update;}
dw4_statusctrl dw4_statussendbit_window_state(const dw4_menu_window *w)
{return dw4_statussendbit_window_is(w)?menu_base_read(w):(dw4_statusctrl){0};}
