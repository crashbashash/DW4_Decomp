#define _POSIX_C_SOURCE 200809L
#include "../src/menurecord.h"
#include "dw4/statusview.h"
#include "dw4/statuscontent.h"
#include "dw4/statusskill.h"
#include "dw4/statusdevice.h"
#include "dw4/statusequip.h"
#include "dw4/statusgear.h"
#include "dw4/statusdetail.h"
#include "dw4/statusflag.h"
#include "dw4/statusbit.h"
#include "dw4/statusdisk.h"
#include "dw4/statusfolder.h"
#include "dw4/statusmenu.h"
#include "dw4/modelview.h"
#include "dw4/png.h"
#include "dw4/textcodec.h"
#include "dw4/statusequipmentmenu.h"
#include "dw4/statusstats.h"
#include "dw4/statusui.h"
#include "dw4/database.h"
#include "dw4/playerinit.h"
#include "dw4/dialogue.h"
#include "dw4/controllers.h"
#include "dw4/gl_layer.h"
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct host {dw4_scriptservices *sd;int preparing;dw4_playerrecords *players;};
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int binding(void *u,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct host *h=u;*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    if(h->players){int rc=dw4_playerrecords_call(h->players,method,a,n,r,error,cap);if(rc!=1)return rc;}
    if(!strcmp(method,"SYSgetLightMode"))r->number=1;
    else if(!strcmp(method,"SYSisJoinPlayer"))r->number=n==1 && a[0].number==0;
    else if(!strcmp(method,"SYSgetPlayerName"))*r=str("m_agumon");
    else if(!strcmp(method,"SYSgetWeaponName"))*r=str("w_axe01");
    else if(!h->preparing)return dw4_scriptservices_call(h->sd,method,a,n,r,error,cap);
    return 0;
}
static int stat_update(void *user,int32_t player,char *error,size_t cap)
{return dw4_statusstats_refresh(user,player,error,cap);}
static int stat_preview(void *user,int32_t player,int on,char *error,size_t cap)
{return dw4_statusstats_compare(user,player,on,error,cap);}
static void stat_command(dw4_scriptservices *sd,const char *key,int player)
{
    char payload[8];snprintf(payload,sizeof payload,"I<%d>",player);
    dw4_script_value args[]={str("SUBWND"),{0},{DW4_SCRIPT_NUMBER,0,NULL,0},str(key),str(payload)},result={0};char error[256];
    int rc=dw4_scriptservices_call(sd,"sd",args,5,&result,error,sizeof error);if(rc)fprintf(stderr,"SUBWND %s: %s\n",key,error);assert(!rc);
}
static void content(dw4_dialogue *d,const char *g,const char *n,const char *value);
static int sound(void *u,const char *m,const dw4_script_value *a,size_t n,dw4_script_value *r,char *e,size_t c)
{(void)u;(void)m;(void)a;(void)n;(void)r;(void)e;(void)c;return 0;}
static const dw4_dialogue_text *text(dw4_dialogue *d,const char *g,const char *n)
{for(size_t i=0;i<dw4_dialogue_text_count(d);i++){const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);if(!strcmp(t->group,g) && !strcmp(t->name,n))return t;}return NULL;}
static void content(dw4_dialogue *d,const char *g,const char *n,const char *value)
{const dw4_dialogue_text *t=text(d,g,n);assert(t);size_t visible=t->count,expected;
 while(visible && !t->codes[visible-1])visible--;
 uint32_t *codes=calloc(strlen(value)+1,sizeof *codes);assert(codes);
 assert(!dw4_textcodec_decode(value,strlen(value),codes,strlen(value)+1,&expected));
 if(visible!=expected)fprintf(stderr,"content %s/%s: %zu codes, expected '%s'\n",g,n,visible,value);
 assert(visible==expected);
 for(size_t i=0;i<visible;i++)assert(t->codes[i]==codes[i]);
 free(codes);}
static void step(dw4_menu_window *w,dw4_controllers *models,dw4_dialogue *d,int64_t *ns)
{
    *ns+=16666667;dw4_controllers_sample(models,*ns);
    char error[256]={0};int rc=dw4_menu_window_tick(w,error,sizeof error);
    if(rc)fprintf(stderr,"view: %s\n",error);
    assert(!rc);
    if(dw4_controllers_tick(models,*ns)){fprintf(stderr,"model: %s\n",dw4_controllers_error(models));assert(0);}
    if(dw4_dialogue_tick(d)){fprintf(stderr,"dialogue: %s\n",dw4_dialogue_error(d));assert(0);}
}
struct page {dw4_playerrecords *players;dw4_databases *db;int mode,pages,rows;};
static int page_setup(void *user,dw4_statusview_io io,void *u)
{struct page *p=user;return dw4_statuscontent_skill_setup(p->players,p->db,0,p->mode,p->pages,&p->rows,io,u);}
static int equipment_setup(void *user,dw4_statusview_io io,void *u)
{struct page *p=user;
 dw4_statusview_command model={DW4_VIEW_MODEL,NULL,"i_stsoubi",p->mode==0?"SQ_POWEROPEN":p->mode==1?"SQ_MAINOPEN":"SQ_SUBOPEN","SQ_CLOSE",0};
 if(io(u,&model))return -1;
 for(unsigned i=0;i<8;i++){char font[16];snprintf(font,sizeof font,"font%03u",i<3?i:100+i-3);
     dw4_statusview_command c={DW4_VIEW_TRACK_TEXT,"STWINFONT11",font,NULL,NULL,0};if(io(u,&c))return -1;}
 dw4_statusview_command desc={DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0};if(io(u,&desc))return -1;
 return dw4_statuscontent_equipment(p->players,p->db,0,p->mode,0,0,io,u);}
static int device_setup(void *user,dw4_statusview_io io,void *u)
{(void)user;
 for(unsigned i=0;i<12;i++)for(unsigned j=0;j<2;j++){
     char font[16];snprintf(font,sizeof font,"font%03u",i);
     dw4_statusview_command c={DW4_VIEW_TEXT,j?"STWINFONT16":"STWINFONT14",font,j?"RIGHT":"LEFT"," ",0};if(io(u,&c))return -1;}
 for(unsigned i=0;i<2;i++){char font[16];snprintf(font,sizeof font,"font%03u",i);
     dw4_statusview_command c={DW4_VIEW_TEXT,"STWINFONT23",font,"RIGHT"," ",0};if(io(u,&c))return -1;}
 dw4_statusview_command desc={DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0};return io(u,&desc);}
struct skill_input {dw4_statuspage_input pad[4];int calls,fail;};
static int skill_input(void *u,int32_t player,dw4_statuspage_input *out)
{struct skill_input *p=u;p->calls++;*out=p->pad[player];return p->fail;}
static void skill_steps(dw4_menu_window *w,dw4_controllers *m,dw4_dialogue *d,int64_t *ns,int count)
{for(int i=0;i<count;i++)step(w,m,d,ns);}
static void skill_edge(dw4_menu_window *w,dw4_controllers *m,dw4_dialogue *d,int64_t *ns,uint32_t analog,uint32_t pressed)
{dw4_dialogue_input(d,0,analog,0,pressed);step(w,m,d,ns);
 if(analog){dw4_dialogue_input(d,0,analog,0,0);skill_steps(w,m,d,ns,2);}
 dw4_dialogue_input(d,0,0,0,0);skill_steps(w,m,d,ns,120);}
static void owned_skill(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    struct skill_input input={0};dw4_statusskill_context c={.view=*view,.databases=db,.input=skill_input,.user=&input};
    char error[256];dw4_property_folder *f=dw4_playerrecords_get(view->players,"GETPLAYER",0);
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","John",error,sizeof error));
    for(int mode=0;mode<3;mode++){
        int32_t used[16],levels[16];for(int i=0;i<16;i++){used[i]=i<10;levels[i]=i+10;}
        assert(!dw4_property_set_array(f,"BASE_ISUSE",used,16) && !dw4_property_set_array(f,"BASE_LEVEL",levels,16));
        int before=input.calls;dw4_menu_window *w=dw4_statusskill_window_open(&c);assert(w && input.calls==before);
        dw4_menu_window *s=dw4_statusskill_window_is(w)?w:NULL;assert(s);
        skill_steps(w,m,d,ns,120);assert(dw4_menu_window_count(w)==1 && menu_submenu_read(s,DW4_STATUS_SKILL).window.sub==2 && menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==0);
        for(int i=0;i<mode;i++)skill_edge(w,m,d,ns,4,0);
        assert(menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==mode);skill_edge(w,m,d,ns,0,0x4000);
        assert(menu_submenu_read(s,DW4_STATUS_SKILL).window.sub==3 && menu_submenu_read(s,DW4_STATUS_SKILL).window.delay==2 && menu_submenu_read(s,DW4_STATUS_SKILL).mode==mode && dw4_menu_window_count(w)==1);
        assert(text(d,"STWINFONT29","font000")->visible);
        if(!mode){
            assert(menu_submenu_read(s,DW4_STATUS_SKILL).pages==2 && menu_submenu_read(s,DW4_STATUS_SKILL).page==0);content(d,"STWINFONT14","font000","Dorumon");
            /* Player one cannot page player zero. Vertical analog blocks both
             * directions even when a horizontal/digital edge is also present. */
            input.pad[1].horizontal=2;skill_steps(w,m,d,ns,2);assert(menu_submenu_read(s,DW4_STATUS_SKILL).page==0);
            input.pad[0]=(dw4_statuspage_input){2,1,0};skill_steps(w,m,d,ns,2);assert(menu_submenu_read(s,DW4_STATUS_SKILL).page==0);
            input.pad[0]=(dw4_statuspage_input){2,0,0};step(w,m,d,ns);input.pad[0]=(dw4_statuspage_input){0};
            assert(dw4_statusview_selector_ready(w->children[0])==0);
            assert(dw4_statusview_selector_repage(w->children[0],8)==-1);
            skill_steps(w,m,d,ns,120);assert(menu_submenu_read(s,DW4_STATUS_SKILL).page==1 && menu_submenu_read(s,DW4_STATUS_SKILL).offset==8 && menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==0);
            content(d,"STWINFONT24","font000","2");content(d,"STWINFONT14","font000",dw4_databases_shinka_name((void *)db,8));
            assert(text(d,"STWINFONT14","font001")->visible && !text(d,"STWINFONT14","font002")->visible);
            skill_edge(w,m,d,ns,4,0);assert(menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==1);
            skill_edge(w,m,d,ns,4,0);assert(menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==1); /* short page count */
            input.pad[0]=(dw4_statuspage_input){10,0,0};step(w,m,d,ns);input.pad[0]=(dw4_statuspage_input){0};
            skill_steps(w,m,d,ns,120);assert(menu_submenu_read(s,DW4_STATUS_SKILL).page==0 && menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==0); /* left priority */
            content(d,"STWINFONT24","font000","1");assert(text(d,"STWINFONT14","font007")->visible);
        }
        /* Confirm and cancel both return through real cursor/model completion;
         * the parent menu retains the selected mode, not the page row. */
        skill_edge(w,m,d,ns,0,mode==1?0x4000:0x2000);
        assert(menu_submenu_read(s,DW4_STATUS_SKILL).window.sub==2 && menu_submenu_read(s,DW4_STATUS_SKILL).window.selection==mode && dw4_menu_window_count(w)==1);
        assert(!text(d,mode==2?"STWINFONT14":"STWINFONT18","font000")->visible);
        skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));
        assert(!text(d,"STWINFONT12","font000")->visible && !text(d,"STWINFONT29","font000")->visible);dw4_menu_window_close(w);
    }
    for(int total=0;total<=1;total++){
        int32_t used[16]={0};used[0]=total;assert(!dw4_property_set_array(f,"BASE_ISUSE",used,16));
        dw4_menu_window *w=dw4_statusskill_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
        skill_edge(w,m,d,ns,0,0x4000);dw4_menu_window *s=dw4_statusskill_window_is(w)?w:NULL;
        assert(menu_submenu_read(s,DW4_STATUS_SKILL).window.sub==3 && menu_submenu_read(s,DW4_STATUS_SKILL).pages==1 && menu_submenu_read(s,DW4_STATUS_SKILL).page==0);
        input.pad[0]=(dw4_statuspage_input){2,0,0};step(w,m,d,ns);input.pad[0]=(dw4_statuspage_input){0};assert(menu_submenu_read(s,DW4_STATUS_SKILL).page==0);
        assert(text(d,"STWINFONT14","font000")->visible==total);
        /* External REMOVE retains completion while owned page/cursor/title
         * models close; query APIs do not shortcut the model wait. */
        dw4_menu_window_remove(w);step(w,m,d,ns);assert(dw4_menu_window_data(w)->_isRun);
        skill_steps(w,m,d,ns,120);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);
    }
    /* Failed input cannot release Lua/menu completion or resume ticking. */
    dw4_menu_window *w=dw4_statusskill_window_open(&c);assert(w);input.fail=1;
    assert(dw4_menu_window_tick(w,error,sizeof error)==-1 && dw4_menu_window_data(w)->_isRun);int calls=input.calls;
    assert(dw4_menu_window_tick(w,error,sizeof error)==-1 && input.calls==calls && strstr(error,"scene reset"));
    dw4_menu_window_close(w);c.input=NULL;assert(!dw4_statusskill_window_open(&c));
}
static int device_candidate(void *u,dw4_statusequip *s,int chip,int32_t *out)
{(void)s;(void)chip;return dw4_statusdevice_window_candidate(u,out);}
static int unused_view(void *u,dw4_statusequip *s,int op,int32_t v)
{(void)u;(void)s;(void)op;(void)v;assert(0);return -1;}
static int unused_preview(void *u,dw4_property_folder *f)
{(void)u;(void)f;assert(0);return -1;}
struct equipment_preview {int off,previews;};
static int preview_off(void *u,dw4_statusequip *s,int op,int32_t v)
{(void)s;(void)v;assert(op==DW4_EQUIP_PREVIEW_OFF);((struct equipment_preview *)u)->off++;return 0;}
static int inspect_preview(void *u,dw4_property_folder *f)
{size_t n;const int32_t *ref=dw4_property_array(f,"POWERSOCKETREF",&n);assert(ref && n==3 && ref[0]==3);((struct equipment_preview *)u)->previews++;return 0;}
struct equipment_device {dw4_menu_window *w;struct equipment_preview *preview;};
static int equipment_candidate(void *u,dw4_statusequip *s,int chip,int32_t *out)
{return dw4_statusdevice_equipment_candidate(((struct equipment_device *)u)->w,s,chip,out);}
static int equipment_view(void *u,dw4_statusequip *s,int op,int32_t v)
{return preview_off(((struct equipment_device *)u)->preview,s,op,v);}
static void owned_device(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    struct skill_input input={0};dw4_statusctrl parent={.selection=-1};
    dw4_statusdevice_context c={.view=*view,.databases=db,.input=skill_input,.user=&input,
        .filter={.kinds={0},.nkinds=1,.equip_disable=1,.unknown_disable=1}};
    c.view.parent=&parent;char error[256];size_t count;
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","John",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(view->players,"GETPLAYER",0);
    const dw4_item_record *initial=dw4_property_items(f,"DEVICEFOLDER",&count);assert(count==3);
    dw4_item_record first=initial[0];int result;
    for(int i=0;i<22;i++)assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,first.kind,first.record,first.revision,first.pocket,&result) && result);
    int calls=input.calls;dw4_menu_window *w=dw4_statusdevice_window_open(&c);assert(w && input.calls==calls);
    dw4_menu_window *s=dw4_statusdevice_window_is(w)?w:NULL;int32_t candidate;
    assert(dw4_statusdevice_window_candidate(w,&candidate)==1);
    skill_steps(w,m,d,ns,120);assert(menu_device_read(s).page==0 && menu_device_read(s).pages==3 && parent.selection==-1 && dw4_menu_window_count(w)==1);
    assert(text(d,"STWINFONT14","font000")->color[0]==.5f); /* disabled equipped item */
    struct equipment_preview preview={0};struct equipment_device binding={w,&preview};
    dw4_statusequip_context hover={.players=view->players,.databases=db,.player=0,.kind=0,
        .view=equipment_view,.user=&binding,.candidate=equipment_candidate,.preview=inspect_preview,.preview_user=&preview};
    dw4_statusequip comparison={.window={.selection=0,.latch=999},.slot=0};
    const dw4_item_record *before=dw4_property_items(f,"DEVICEFOLDER",&count);
    assert(!dw4_statusequip_transaction_io(&hover,&comparison,DW4_EQUIP_VIRTUAL+32,0) && preview.off==1 && !preview.previews);
    assert(!dw4_statusequip_transaction_io(&hover,&comparison,DW4_EQUIP_VIRTUAL+32,0) && preview.off==1);
    assert(dw4_property_items(f,"DEVICEFOLDER",&count)==before);
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_statusdevice_window_ready(w) && parent.selection==-1);
    for(int i=0;i<3;i++)skill_edge(w,m,d,ns,4,0);
    assert(menu_device_read(s).window.selection==3);
    assert(!dw4_statusequip_transaction_io(&hover,&comparison,DW4_EQUIP_VIRTUAL+32,0) && preview.previews==1);
    assert(!dw4_statusequip_transaction_io(&hover,&comparison,DW4_EQUIP_VIRTUAL+32,0) && preview.previews==1);
    assert(dw4_property_items(f,"DEVICEFOLDER",&count)==before);
    input.pad[1].horizontal=2;skill_steps(w,m,d,ns,2);assert(menu_device_read(s).page==0);
    input.pad[0]=(dw4_statuspage_input){2,1,0};step(w,m,d,ns);assert(menu_device_read(s).page==0);
    for(int page=1;page<=2;page++){
        input.pad[0]=(dw4_statuspage_input){2,0,0};step(w,m,d,ns);input.pad[0]=(dw4_statuspage_input){0};
        skill_steps(w,m,d,ns,120);assert(menu_device_read(s).page==page && menu_device_read(s).window.selection==0);
    }
    content(d,"STWINFONT23","font000","3");content(d,"STWINFONT23","font001","3");
    assert(text(d,"STWINFONT14","font000")->visible && !text(d,"STWINFONT14","font001")->visible);
    skill_edge(w,m,d,ns,4,0);assert(menu_device_read(s).window.selection==0); /* one-row final page */
    assert(!dw4_statusdevice_window_candidate(w,&candidate) && candidate==24);
    skill_edge(w,m,d,ns,0,0x4000);assert(dw4_statusdevice_window_ready(w)==1 && dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w) && parent.selection==24);
    /* Duplicate item values retain the absolute inventory identity. Queries
     * leave scalar state, selection, clocks and actual close ownership intact. */
    for(int i=0;i<64;i++)assert(dw4_statusdevice_window_ready(w)==1 && !dw4_statusdevice_window_candidate(w,&candidate) && candidate==24);
    /* A detail owner removed the sole final-page item. Rebuild follows retail's
     * one-step page/row adjustment and replaces copied selector flags. */
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&count);assert(count==25);
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",items,24));
    assert(dw4_statusdevice_window_candidate(w,&candidate)==-1);
    assert(!dw4_statusdevice_window_restart(w));step(w,m,d,ns);skill_steps(w,m,d,ns,120);
    assert(menu_device_read(s).page==1 && menu_device_read(s).pages==2 && menu_device_read(s).row==0 && menu_device_read(s).window.selection==0 && !dw4_statusdevice_window_ready(w));
    content(d,"STWINFONT23","font000","2");content(d,"STWINFONT23","font001","2");
    skill_edge(w,m,d,ns,0,0x4000);assert(dw4_statusdevice_window_ready(w)==1 && parent.selection==12);
    dw4_statusequip_context transaction={.players=view->players,.databases=db,.player=0,.kind=0,
        .view=unused_view,.user=w,.candidate=device_candidate,.preview=unused_preview};
    dw4_statusequip equipment={.window={.selection=12},.slot=0};
    assert(dw4_statusequip_transaction_io(&transaction,&equipment,DW4_EQUIP_VIRTUAL+30,12)==1);
    assert(!dw4_statusequip_transaction_io(&transaction,&equipment,DW4_EQUIP_VIRTUAL+31,0));
    const int32_t *refs=dw4_property_array(f,"POWERSOCKETREF",&count);assert(refs[0]==12);
    dw4_menu_window_remove(w);step(w,m,d,ns);assert(dw4_menu_window_data(w)->_isRun);
    skill_steps(w,m,d,ns,120);assert(!dw4_menu_window_data(w)->_isRun && !text(d,"STWINFONT14","font000")->visible);dw4_menu_window_close(w);
    c.auto_close=1;c.filter=(dw4_statusdevice_filter){0};parent.selection=-1;
    w=dw4_statusdevice_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun && parent.selection==-1);dw4_menu_window_close(w);
    /* Empty DEVICE is an actual property with a retail one-row cursor;
     * unavailable BANK records are a failure, never an empty successful menu. */
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",NULL,0));w=dw4_statusdevice_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    assert(!text(d,"STWINFONT14","font000")->visible);assert(dw4_statusdevice_window_candidate(w,&candidate)==-1);
    skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    dw4_playerrecords *missing=dw4_playerrecords_open();assert(missing);
    c.bank=1;c.view.players=missing;w=dw4_statusdevice_window_open(&c);assert(w);
    assert(dw4_menu_window_tick(w,error,sizeof error)==-1 && dw4_menu_window_data(w)->_isRun && strstr(error,"BANKDEVICE"));
    calls=input.calls;assert(dw4_menu_window_tick(w,error,sizeof error)==-1 && input.calls==calls && strstr(error,"scene reset"));dw4_menu_window_close(w);dw4_playerrecords_close(missing);
}
struct gear_host {struct skill_input input;dw4_playerrecords *players;int appearance;};
static int gear_appearance(void *u,int32_t player,char *error,size_t cap)
{struct gear_host *h=u;(void)error;(void)cap;size_t n;const int32_t *r=dw4_property_array(dw4_playerrecords_get(h->players,"GETPLAYER",player),"POWERSOCKETREF",&n);assert(r && n==3 && r[0]==1);h->appearance++;return 0;}
static void gear_close(dw4_menu_window *w,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{dw4_menu_window_remove(w);step(w,m,d,ns);assert(dw4_menu_window_data(w)->_isRun);skill_steps(w,m,d,ns,160);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);}
static void owned_gear(dw4_statusview_context *view,const dw4_databases *db,dw4_statusstats *stats,
    dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    struct gear_host host={.players=view->players};dw4_statusgear_context c={.view=*view,.databases=db,.stats=stats,
        .input=skill_input,.appearance=gear_appearance,.user=&host};
    c.view.user=stats;c.view.refresh=dw4_statusstats_refresh;
    char error[256];size_t count;dw4_property_folder *f=dw4_playerrecords_get(view->players,"GETPLAYER",0);
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","John",error,sizeof error));
    dw4_menu_window *title=dw4_statusview_window_open(DW4_STATUS_TITLE01,&c.view);assert(title);step(title,m,d,ns);
    dw4_menu_window *w=dw4_statusgear_window_open(&c,0,0);assert(w);
    dw4_menu_window *s=dw4_statusgear_window_is(w)?w:NULL;assert(s);skill_steps(w,m,d,ns,120);
    assert(menu_equip_read(s).window.sub==0 && menu_equip_read(s).window.delay==2 && dw4_menu_window_count(w)==1);
    for(unsigned i=0;i<5;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",200+i);
        assert(!text(d,"STWINFONT11",font)->visible);
    }
    assert(!text(d,"STWINFONT29","font001")->visible && !text(d,"STWINFONT29","font002")->visible);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==1 && dw4_menu_window_count(w)==1);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==3 && menu_equip_read(s).window.delay==2);
    const dw4_item_record *before=dw4_property_items(f,"DEVICEFOLDER",&count);
    skill_edge(w,m,d,ns,4,0);assert(menu_equip_read(s).window.selection==1 && dw4_property_items(f,"DEVICEFOLDER",&count)==before);
    skill_edge(w,m,d,ns,0,0x4000);
    const int32_t *refs=dw4_property_array(f,"POWERSOCKETREF",&count);
    assert(refs[0]==1 && refs[1]==0 && host.appearance==1 && menu_equip_read(s).window.sub==0);
    skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    for(int kind=1;kind<=2;kind++){
        assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","John",error,sizeof error));
        assert(!dw4_statusstats_refresh(stats,0,error,sizeof error));
        int result;assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,kind,0,0,kind==1?2:0,&result) && result);
        w=dw4_statusgear_window_open(&c,kind,0);assert(w);s=dw4_statusgear_window_is(w)?w:NULL;skill_steps(w,m,d,ns,120);
        skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==1);
        skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==4 && menu_equip_read(s).window.delay==1);
        for(int i=0;i<3;i++)skill_edge(w,m,d,ns,4,0);
        before=dw4_property_items(f,"DEVICEFOLDER",&count);
        skill_edge(w,m,d,ns,0,0x4000);
        refs=dw4_property_array(f,kind==1?"MAINSLOTREF":"SUBSLOTREF",&count);
        const dw4_item_record *equipped=dw4_property_items(f,"DEVICEFOLDER",&count);
        assert(refs[0]==3 && equipped && count>3 && equipped[3].equipped && menu_equip_read(s).window.sub==0);
        if(kind==1){
            int chip=-1;
            const char *family[]={"TSUYOSA","KASHIKOSA","SEISHIN","SUBAYASA","RES_FIRE","RES_ICE","RES_THUNDER","RES_DARK","CHIMEIRITSU","HPDRAIN","MPDRAIN","CHOHATURITSU"};
            for(int row=0;row<256 && chip<0;row++){
                dw4_item_record item={.kind=3,.record=row};int32_t blue;
                if(dw4_playerstats_item_bool((void *)db,&item,"BLUEAB",&blue) || (uint8_t)blue!=1)continue;
                for(unsigned i=0;i<12;i++){int32_t value;if(!dw4_playerstats_item_attribute((void *)db,&item,family[i],&value) && value>0){chip=row;break;}}
            }
            assert(chip>=0 && !dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,3,chip,0,0,&result) && result);
            skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==1);
            skill_edge(w,m,d,ns,4,0);assert(menu_equip_read(s).window.selection==1);
            skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==2 && menu_equip_read(s).window.delay==2);
            skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.delay==5);
            skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.delay==7);
            for(int i=0;i<4;i++)skill_edge(w,m,d,ns,4,0);
            skill_edge(w,m,d,ns,0,0x4000);
            refs=dw4_property_array(f,"MAINPOCKETREF",&count);assert(refs[0]==4 && menu_equip_read(s).window.sub==2);
            skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.delay==5);
            skill_edge(w,m,d,ns,4,0);assert(menu_equip_read(s).window.selection==1);
            skill_edge(w,m,d,ns,0,0x4000);
            refs=dw4_property_array(f,"MAINPOCKETREF",&count);assert(refs[0]==-1 && menu_equip_read(s).window.sub==2);
            skill_edge(w,m,d,ns,0,0x2000);assert(menu_equip_read(s).window.sub==0);
        }
        skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==1);
        skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,4,0);assert(menu_equip_read(s).window.selection==2);
        refs=dw4_property_array(f,kind==1?"MAINSLOTREF":"SUBSLOTREF",&count);assert(refs[0]==3); /* private remove preview */
        skill_edge(w,m,d,ns,0,0x4000);
        refs=dw4_property_array(f,kind==1?"MAINSLOTREF":"SUBSLOTREF",&count);assert(refs[0]==-1);
        gear_close(w,m,d,ns);
    }
    /* A real inventory selection that fails LEVEL eligibility creates the
     * authored error selector and retries the retained DEVICE row. */
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","John",error,sizeof error));
    assert(!dw4_statusstats_refresh(stats,0,error,sizeof error));int high=-1;
    for(int row=0;row<256;row++){dw4_item_record item={.kind=1,.record=row};int32_t level;
        if(!dw4_playerstats_item_attribute((void *)db,&item,"LVPOINT",&level) && level>1){high=row;break;}}
    assert(high>=0);int result;
    assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,high,0,0,&result) && result);
    w=dw4_statusgear_window_open(&c,1,0);assert(w);s=dw4_statusgear_window_is(w)?w:NULL;skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,0,0x4000);skill_edge(w,m,d,ns,0,0x4000);
    for(int i=0;i<3;i++)skill_edge(w,m,d,ns,4,0);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.sub==4 && menu_equip_read(s).window.delay==13 && dw4_menu_window_count(w)==2);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_equip_read(s).window.delay==1 && dw4_menu_window_count(w)==1);
    refs=dw4_property_array(f,"MAINSLOTREF",&count);assert(refs[0]==-1);
    skill_edge(w,m,d,ns,0,0x2000);assert(menu_equip_read(s).window.sub==0 && dw4_menu_window_count(w)==1);
    gear_close(w,m,d,ns);
    dw4_menu_window_remove(title);skill_steps(title,m,d,ns,160);assert(!dw4_menu_window_data(title)->_isRun);dw4_menu_window_close(title);
}
/* The isolated detail fixtures control only the external DEVICE completion
 * leaf. owned_folder below exercises the actual retained owner and pruning. */
struct retained_probe {int closes,queries,ready;};
static int retained_probe(void *u,int op)
{
    struct retained_probe *p=u;
    if(op==DW4_DETAIL_RETAINED_CLOSE){p->closes++;return 0;}
    assert(op==DW4_DETAIL_RETAINED_FINISHED && p->closes==1);p->queries++;return p->ready;
}
static void owned_detail(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    char error[256];int result;size_t count;
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","Alice",error,sizeof error));
    assert(!dw4_playerrecords_create(view->players,db,1,"p_agumon","Bob",error,sizeof error));
    dw4_property_folder *from=dw4_playerrecords_get(view->players,"GETPLAYER",0),*to=dw4_playerrecords_get(view->players,"GETPLAYER",1);
    /* Armor detail discards are permitted when unequipped, while trade reads
     * the actual ISJYOUDO boolean column for every item kind. */
    assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,0,12,0,&result) && result);
    dw4_statusdetail_context c={.view=*view,.databases=db,.dialogue=d,.selected=3};
    dw4_menu_window *w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    dw4_menu_window *s=dw4_statusdetail_window_is(w)?w:NULL;assert(menu_base_read(s).state==1 && dw4_menu_window_count(w)==1);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==1 && menu_base_read(s).delay==1);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==2);
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun);
    assert(!dw4_property_item_count(from,"DEVICEFOLDER",&count) && count==3);dw4_menu_window_close(w);
    /* Sorting enters the source immediate action and preserves equipped IDs. */
    assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,0,12,0,&result) && result);
    w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    int trade=-1;
    for(int row=0;row<256;row++){dw4_item_record v={.kind=1,.record=row};int32_t allowed;
        if(!dw4_playerstats_item_bool((void *)db,&v,"ISJYOUDO",&allowed) && (uint8_t)allowed){trade=row;break;}}
    assert(trade>=0);assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,trade,0,0,&result) && result);
    struct retained_probe retained={0};c.device=retained_probe;c.device_user=&retained;
    c.selected=4;w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);
    s=dw4_statusdetail_window_is(w)?w:NULL;assert(menu_base_read(s).sub==3 && menu_base_read(s).delay==1 && retained.closes==1 && retained.queries);
    assert(!dw4_property_item_count(to,"DEVICEFOLDER",&count) && count==3);
    retained.ready=1;step(w,m,d,ns);assert(menu_base_read(s).delay==2 && !dw4_menu_window_count(w));
    content(d,"STWINFONT14","font001","Bob");
    step(w,m,d,ns);assert(menu_base_read(s).delay==3 && dw4_menu_window_count(w)==1);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==4);
    assert(!dw4_property_item_count(to,"DEVICEFOLDER",&count) && count==4);
    const dw4_item_record *received=dw4_property_items(to,"DEVICEFOLDER",&count);assert(received[3].kind==1 && received[3].record==trade);
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun);
    assert(text(d,"STWINFONT14","font000")->color[0]==.9f);dw4_menu_window_close(w);
    /* Equipped discard uses the original error acknowledgement and leaves all
     * actual inventory payloads untouched. */
    c.selected=0;const dw4_item_record *before=dw4_property_items(from,"DEVICEFOLDER",&count);
    retained=(struct retained_probe){.ready=1};
    w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,0,0x4000);s=dw4_statusdetail_window_is(w)?w:NULL;assert(menu_base_read(s).delay==10);
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun && dw4_property_items(from,"DEVICEFOLDER",&count)==before);dw4_menu_window_close(w);
    /* Full recipient acknowledges original call 149 without replacing either
     * inventory payload; the selected sender identity stays present. */
    for(int i=0;i<32;i++)assert(!dw4_playertransactions_device(view->players,1,DW4_DEVICE_SET,1,trade,0,0,&result) && result);
    assert(!dw4_property_item_count(to,"DEVICEFOLDER",&count) && count==36);
    assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,trade,0,0,&result) && result);
    c.selected=4;before=dw4_property_items(from,"DEVICEFOLDER",&count);
    const dw4_item_record *recipient=dw4_property_items(to,"DEVICEFOLDER",&count);
    w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);
    skill_edge(w,m,d,ns,0,0x4000);s=dw4_statusdetail_window_is(w)?w:NULL;assert(menu_base_read(s).delay==4);
    assert(dw4_property_items(from,"DEVICEFOLDER",&count)==before && dw4_property_items(to,"DEVICEFOLDER",&count)==recipient);
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    assert(!dw4_property_set_number(to,"ISUSE",0));
    w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);
    s=dw4_statusdetail_window_is(w)?w:NULL;assert(menu_base_read(s).delay==4);
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun && dw4_property_items(from,"DEVICEFOLDER",&count)==before);dw4_menu_window_close(w);
    assert(!dw4_property_set_number(to,"ISUSE",1));
    /* Retail's absent retained owner closes an admitted give operation before
     * recipient publication; it cannot transfer through a fabricated owner. */
    c.device=NULL;c.device_user=NULL;before=dw4_property_items(from,"DEVICEFOLDER",&count);
    w=dw4_statusdetail_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);
    assert(!dw4_menu_window_data(w)->_isRun && dw4_property_items(from,"DEVICEFOLDER",&count)==before);dw4_menu_window_close(w);
}
static void owned_flag(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    dw4_statusflag_context c={.view=*view,.databases=db};
    dw4_property_folder *common=dw4_playerrecords_get(view->players,"GETCOMMON",0);
    const dw4_database *items=dw4_databases_get(db,"impItem");assert(items);
    for(int mode=0;mode<3;mode++){
        uint8_t flags[12]={0};if(mode==1){flags[2]=1;flags[7]=255;}if(mode==2)memset(flags,1,sizeof flags);
        assert(!dw4_property_set_bytes(common,"FLAGFOLDER",flags,12));
        dw4_menu_window *w=dw4_statusflag_window_open(&c);assert(w && !dw4_menu_window_count(w));
        skill_steps(w,m,d,ns,120);dw4_menu_window *state=dw4_statusflag_window_is(w)?w:NULL;
        assert(state && menu_base_read(state).state==1 && menu_base_read(state).sub==1 && dw4_menu_window_count(w)==1);
        if(mode){content(d,"STWINFONT14","font000",dw4_database_string(items,mode==1?2:0,"NAME"));
            content(d,"STWINFONT29","font000",dw4_database_string(items,mode==1?2:0,"TXT"));
            skill_edge(w,m,d,ns,4,0);assert(menu_base_read(state).selection==1);
            content(d,"STWINFONT29","font000",dw4_database_string(items,mode==1?7:1,"TXT"));}
        else assert(!text(d,"STWINFONT14","font000")->visible);
        if(mode==2)dw4_menu_window_remove(w);else skill_edge(w,m,d,ns,0,0x2000);
        skill_steps(w,m,d,ns,160);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));
        assert(!text(d,"STWINFONT13","font000")->visible && !text(d,"STWINFONT29","font100")->visible);
        dw4_menu_window_close(w);
    }
    uint8_t malformed[11]={0};assert(!dw4_property_set_bytes(common,"FLAGFOLDER",malformed,11));
    dw4_menu_window *w=dw4_statusflag_window_open(&c);assert(w);char error[256];
    assert(dw4_menu_window_tick(w,error,sizeof error)==-1 && dw4_menu_window_data(w)->_isRun);
    assert(dw4_menu_window_tick(w,error,sizeof error)==-1 && strstr(error,"scene reset"));dw4_menu_window_close(w);
    uint8_t flags[12]={0};assert(!dw4_property_set_bytes(common,"FLAGFOLDER",flags,12));
}
static void positioned_cursor(dw4_statusview_context *view,dw4_controllers *models)
{
    const dw4_modelctrl *cursor=NULL;
    for(size_t i=0;i<dw4_controllers_count(models);i++){
        const dw4_stageobject *info;int32_t slot;
        const dw4_modelctrl *model=dw4_controllers_model(models,i,&info,&slot);
        if(slot==0 && dw4_stageobject_name(info) && !strcmp(dw4_stageobject_name(info),"i_stcursor04"))cursor=model;
    }
    assert(cursor);char error[256];dw4_script_value args[]={str("MODELCTRL"),str("i_stcursor04"),{DW4_SCRIPT_NUMBER,0,NULL,0},str("REMOVE")},result;
    assert(!dw4_scriptservices_call(view->sd,"sd",args,4,&result,error,sizeof error));
    assert(!dw4_statusui_positioned(view,"i_stcursor04",0,"SQ_OPEN00",12,13,14,error,sizeof error));
    dw4_modelctrl_actor before,after;dw4_modelctrl_actor_state(cursor,&before);
    assert(before.position[0]==12 && before.position[1]==13 && before.position[2]==14);
    assert(!dw4_statusui_positioned(view,"i_stcursor04",0,"SQ_OPEN01",99,100,101,error,sizeof error));
    dw4_modelctrl_actor_state(cursor,&after);assert(!memcmp(before.position,after.position,sizeof before.position));
    assert(!dw4_scriptservices_call(view->sd,"sd",args,4,&result,error,sizeof error));
}
static void owned_bit(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    char error[256];struct skill_input input={0};positioned_cursor(view,m);
    dw4_statusbit_context c={.view=*view,.dialogue=d,.input=skill_input,.user=&input};
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","Alice",error,sizeof error));
    for(int i=1;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(view->players,"GETPLAYER",i),"ISUSE",0));
    dw4_menu_window *w=dw4_statusbit_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    dw4_menu_window *s=dw4_statusbit_window_is(w)?w:NULL;assert(menu_base_read(s).state==1 && dw4_menu_window_count(w)==1);
    assert(menu_base_read(s).sub==0 && !dw4_statussendbit_window_is(w->children[0]));
    skill_edge(w,m,d,ns,0,0x4000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    for(int i=1;i<4;i++)assert(!dw4_playerrecords_create(view->players,db,i,"p_agumon",i==1?"Bob":i==2?"Carol":"Dave",error,sizeof error));
    dw4_property_folder *from=dw4_playerrecords_get(view->players,"GETPLAYER",0),*to=dw4_playerrecords_get(view->players,"GETPLAYER",2);
    assert(!dw4_property_set_number(from,"BIT",12345) && !dw4_property_set_number(to,"BIT",9999900));
    /* Real STATUS initializes Title01 before opening CtrlBit. Currency reset
     * does not send a retail SUBWND UPDATE; model that parent setup explicitly. */
    assert(!view->refresh(view->user,view->player,error,sizeof error));
    w=dw4_statusbit_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    assert(dw4_statusbit_window_state(w).sub==1 && dw4_menu_window_count(w)==1);
    s=dw4_statussendbit_window_is(w->children[0])?w->children[0]:NULL;assert(s);
    assert(menu_base_read(s).delay==1 && menu_base_read(s).selection==0 && dw4_menu_window_count(w)==1);
    skill_edge(w,m,d,ns,4,0);assert(menu_base_read(s).selection==1);skill_edge(w,m,d,ns,0,0x4000);
    assert(menu_base_read(s).delay==2 && menu_base_read(s).selection==6 && dw4_menu_window_count(w)==1);
    assert(dw4_statusbit_window_state(w).state==1 && dw4_statusbit_window_state(w).sub==1 && dw4_statusbit_window_state(w).delay==1);
    input.pad[1].horizontal=1;step(w,m,d,ns);input.pad[1].horizontal=0;content(d,"STWINFONT28","font000","0");
    input.pad[0].horizontal=1;step(w,m,d,ns);input.pad[0].horizontal=0;content(d,"STWINFONT28","font000","1");
    skill_edge(w,m,d,ns,8,0);assert(menu_base_read(s).selection==5);
    input.pad[0].horizontal=1;step(w,m,d,ns);input.pad[0].horizontal=0;
    content(d,"STWINFONT28","font001","1");content(d,"STWINFONT28","font000","1");
    skill_edge(w,m,d,ns,8,0);assert(menu_base_read(s).selection==4);
    input.pad[0].horizontal=1;step(w,m,d,ns);input.pad[0].horizontal=0; /* clamps at recipient headroom 99 */
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==4);
    int32_t bit;assert(!dw4_property_number(from,"BIT",&bit) && bit==12246);assert(!dw4_property_number(to,"BIT",&bit) && bit==9999999);
    content(d,"STWINFONT06","font070","12345");
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==1 && menu_base_read(s).selection==1);
    content(d,"STWINFONT06","font070","12246");
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==2);
    input.pad[0].horizontal=1;step(w,m,d,ns);input.pad[0].horizontal=0;
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==1); /* zero amount returns without mutation */
    skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    w=dw4_statusbit_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);skill_edge(w,m,d,ns,0,0x4000);
    skill_edge(w,m,d,ns,0,0x2000);s=dw4_statussendbit_window_is(w->children[0])?w->children[0]:NULL;assert(s && menu_base_read(s).delay==1);
    dw4_menu_window_remove(w);skill_steps(w,m,d,ns,160);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);
    for(int i=2;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(view->players,"GETPLAYER",i),"ISUSE",0));
}
static void owned_disk(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    char error[256];size_t count;dw4_statusdisk_context c={.view=*view,.databases=db,.dialogue=d};
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","Alice",error,sizeof error));
    assert(!dw4_playerrecords_create(view->players,db,1,"p_agumon","Bob",error,sizeof error));
    for(int i=2;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(view->players,"GETPLAYER",i),"ISUSE",0));
    dw4_property_folder *from=dw4_playerrecords_get(view->players,"GETPLAYER",0),*to=dw4_playerrecords_get(view->players,"GETPLAYER",1);
    dw4_menu_window *w=dw4_statusdisk_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);
    dw4_menu_window *s=dw4_statusdisk_window_is(w)?w:NULL;assert(menu_base_read(s).sub==2 && menu_base_read(s).selection==0 && dw4_menu_window_count(w)==1);
    content(d,"STWINFONT14","font000",dw4_database_string(dw4_databases_get(db,"conItem"),0,"NAME"));
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==3);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==4 && menu_base_read(s).selection==0);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==2);
    const dw4_item_record *v=dw4_property_items(from,"DISKFOLDER",&count);assert(count==12 && v[0].record==1 && v[1].record==0 && v[11].record==11);
    dw4_menu_window_remove(w);skill_steps(w,m,d,ns,160);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    dw4_item_record items[12];memcpy(items,v,sizeof items);items[0].revision=5;assert(!dw4_property_set_items(from,"DISKFOLDER",items,12));
    v=dw4_property_items(to,"DISKFOLDER",&count);memcpy(items,v,sizeof items);items[1].revision=8;assert(!dw4_property_set_items(to,"DISKFOLDER",items,12));
    w=dw4_statusdisk_window_open(&c);assert(w);skill_steps(w,m,d,ns,120);s=dw4_statusdisk_window_is(w)?w:NULL;
    skill_edge(w,m,d,ns,0,0x4000);skill_edge(w,m,d,ns,4,0);
    /* Match 41acf0's explicit recipient-entry updates. The outgoing folder
     * still runs its authored close when the recipient panel is generated;
     * an extra wait for retired host trackers changes this retail boundary. */
    dw4_dialogue_input(d,0,0,0,0x4000);step(w,m,d,ns);dw4_dialogue_input(d,0,0,0,0);
    for(int i=0;i<500 && menu_base_read(s).sub==3;i++)step(w,m,d,ns);
    assert(menu_base_read(s).sub==5 && menu_base_read(s).delay==0);
    step(w,m,d,ns);assert(menu_base_read(s).sub==6 && menu_base_read(s).delay==0);
    step(w,m,d,ns);assert(menu_base_read(s).delay==1);
    step(w,m,d,ns);assert(menu_base_read(s).delay==2);
    step(w,m,d,ns);assert(menu_base_read(s).delay==4);
    dw4_script_value folder_args[]={str("MODELCTRL"),str("i_stfolder"),{DW4_SCRIPT_NUMBER,0,NULL,0},str("ISRUN")},folder_running;
    assert(!dw4_scriptservices_call(view->sd,"querySD",folder_args,4,&folder_running,error,sizeof error));
    assert(folder_running.type==DW4_SCRIPT_NUMBER && folder_running.number==1);
    content(d,"STWINFONT14","font001","Bob");
    skill_steps(w,m,d,ns,120);
    assert(menu_base_read(s).sub==6 && menu_base_read(s).delay==4 && menu_base_read(s).selection==0);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==7 && menu_base_read(s).selection==0);
    content(d,"STWINFONT38","font001","1");skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==8);
    v=dw4_property_items(from,"DISKFOLDER",&count);assert(v[0].revision==4);
    v=dw4_property_items(to,"DISKFOLDER",&count);assert(v[1].revision==9);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==2);
    for(int i=0;i<500 && !dw4_statusview_selector_ready(w->children[0]);i++)step(w,m,d,ns);
    assert(dw4_statusview_selector_ready(w->children[0]));
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==3);
    for(int i=0;i<500 && !dw4_statusview_selector_ready(w->children[0]);i++)step(w,m,d,ns);
    assert(dw4_statusview_selector_ready(w->children[0]));skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==6);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==6 && menu_base_read(s).delay==11); /* full recipient */
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).delay==4);
    skill_edge(w,m,d,ns,0,0x2000);assert(menu_base_read(s).sub==2);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);
    assert(menu_base_read(s).sub==5 && menu_base_read(s).delay==2); /* empty selected disk */
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_base_read(s).sub==2);
    skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
}
static void folder_panel_visible(dw4_controllers *models)
{
    int panel=0;
    for(size_t i=0;i<dw4_controllers_count(models);i++){
        const dw4_stageobject *info;int32_t slot;
        const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&slot);
        if(!slot && !strcmp(dw4_stageobject_name(info),"i_stfolder")){
            assert(dw4_modelctrl_drawable(m) && dw4_modelctrl_alpha(m)>0);panel=1;
        }
    }
    assert(panel);
}
static void owned_folder(dw4_statusview_context *view,const dw4_databases *db,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    char error[256];struct skill_input input={0};int result;size_t count;
    dw4_statusfolder_context c={.view=*view,.databases=db,.dialogue=d,.input=skill_input,.user=&input};
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","Alice",error,sizeof error));
    assert(!dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,0,0,0,&result) && result);
    dw4_menu_window *w=dw4_statusfolder_window_open(&c);assert(w);skill_steps(w,m,d,ns,160);
    dw4_menu_window *s=dw4_statusfolder_window_is(w)?w:NULL;assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.sub==0 && dw4_menu_window_count(w)==2);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.sub==1 && dw4_menu_window_count(w)==2);
    for(int i=0;i<3;i++)skill_edge(w,m,d,ns,4,0);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.delay==2 && dw4_menu_window_count(w)==3);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.delay==1 && dw4_menu_window_count(w)==2);
    skill_edge(w,m,d,ns,0,0x2000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.sub==0 && dw4_menu_window_count(w)==2);
    for(int child=1;child<=3;child++){
        skill_edge(w,m,d,ns,4,0);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.selection==child);
        skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.sub==child+1 && dw4_menu_window_count(w)==2);
        assert(child==1?dw4_statusflag_window_is(w->children[1]):
               child==2?dw4_statusdisk_window_is(w->children[1]):
                        dw4_statusbit_window_is(w->children[1]));
        if(child<3)folder_panel_visible(m);
        if(child==1)for(unsigned i=0;i<2;i++){
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            content(d,"STWINFONT23",font," ");assert(text(d,"STWINFONT23",font)->align==1);
        }
        if(child==2)for(unsigned i=0;i<12;i++){
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            content(d,"STWINFONT15",font,"0");assert(text(d,"STWINFONT15",font)->align==1);
        }
        skill_edge(w,m,d,ns,0,0x2000);skill_steps(w,m,d,ns,160);
        assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.sub==0 && menu_submenu_read(s,DW4_STATUS_FOLDER).window.selection==child && dw4_menu_window_count(w)==2);
    }
    skill_edge(w,m,d,ns,0,0x2000);skill_steps(w,m,d,ns,160);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);
    assert(!dw4_property_item_count(dw4_playerrecords_get(view->players,"GETPLAYER",0),"DEVICEFOLDER",&count) && count==4);
    /* Production FOLDER owns the retained DEVICE: giving closes/prunes that
     * actual sibling, publishes recipients, then recreates DEVICE only after
     * the detail acknowledgement closes. No completion leaf is controlled. */
    assert(!dw4_playerrecords_create(view->players,db,0,"p_dorumon","Alice",error,sizeof error));
    assert(!dw4_playerrecords_create(view->players,db,1,"p_agumon","Bob",error,sizeof error));
    for(int i=2;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(view->players,"GETPLAYER",i),"ISUSE",0));
    int trade=-1;
    for(int row=0;row<256;row++){dw4_item_record v={.kind=1,.record=row};int32_t allowed;
        if(!dw4_playerstats_item_bool((void *)db,&v,"ISJYOUDO",&allowed) && (uint8_t)allowed){trade=row;break;}}
    assert(trade>=0 && !dw4_playertransactions_device(view->players,0,DW4_DEVICE_SET,1,trade,0,0,&result) && result);
    w=dw4_statusfolder_window_open(&c);assert(w);skill_steps(w,m,d,ns,160);s=dw4_statusfolder_window_is(w)?w:NULL;
    skill_edge(w,m,d,ns,0,0x4000);
    for(int i=0;i<3;i++)skill_edge(w,m,d,ns,4,0);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.delay==2 && dw4_menu_window_count(w)==3);
    skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);
    assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.delay==4 && dw4_menu_window_count(w)==2);
    dw4_menu_window *detail=NULL;
    for(size_t i=0;i<dw4_menu_window_count(w);i++){
        assert(!dw4_statusdevice_window_is(w->children[i]));
        if(dw4_statusdetail_window_is(w->children[i]))detail=w->children[i];
    }
    assert(detail && dw4_statusdetail_window_state(detail).delay==3);
    content(d,"STWINFONT14","font001","Bob");
    skill_edge(w,m,d,ns,0,0x4000);
    assert(dw4_statusdetail_window_state(detail).delay==4);
    assert(!dw4_property_item_count(dw4_playerrecords_get(view->players,"GETPLAYER",0),"DEVICEFOLDER",&count) && count==3);
    assert(!dw4_property_item_count(dw4_playerrecords_get(view->players,"GETPLAYER",1),"DEVICEFOLDER",&count) && count==4);
    skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.delay==1 && dw4_menu_window_count(w)==2);
    int recreated=0;for(size_t i=0;i<dw4_menu_window_count(w);i++)recreated+=dw4_statusdevice_window_is(w->children[i]);
    assert(recreated==1);
    skill_edge(w,m,d,ns,0,0x2000);assert(menu_submenu_read(s,DW4_STATUS_FOLDER).window.sub==0);
    skill_edge(w,m,d,ns,0,0x2000);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);
}
static dw4_modelview *root_renderer;
static dw4_scriptservices *root_sd;
static dw4_controllers *root_models;
static const char *root_capture;
/* Optional private reference artifacts: argv[3] is an existing output directory.
 * Export each player separately, keeping the actual model/text submissions. */
static const char *root_export;
static unsigned root_frame;
static int capture_menus;
static void capture_view(dw4_dialogue *d,int player,const char *label);
static struct reference_clock {char name[128],view[64];int32_t slot;int64_t ns;} reference_clocks[256];
static unsigned reference_count;
static const char *reference_view;
static int64_t reference_time(void *user,const dw4_stageobject *info,int32_t slot,int64_t ns)
{
    (void)user;
    for(unsigned i=0;i<reference_count;i++)if(slot==reference_clocks[i].slot && !strcmp(dw4_stageobject_name(info),reference_clocks[i].name) &&
        (!reference_clocks[i].view[0] || (reference_view && !strcmp(reference_view,reference_clocks[i].view))))return reference_clocks[i].ns;
    return ns;
}
static int draw_root(const dw4_ui_draw **draw,size_t *count,char *error,size_t cap)
{return dw4_modelview_draw_clocks(root_renderer,640,448,draw,count,error,cap,reference_count?reference_time:NULL,NULL);}
static void export_root_draws(FILE *out,const char *part,const dw4_ui_draw *draw,size_t count)
{
    const dw4_tex *textures[128];size_t nt=0;
    for(size_t i=0;i<count;i++){
        const dw4_tex *tex=draw[i].tex;assert(tex);
        size_t t;for(t=0;t<nt;t++)if(textures[t]==tex)break;
        if(t==nt){
            assert(nt<128);textures[nt++]=tex;
            char path[4096];snprintf(path,sizeof path,"%s/root-%u-%s-%zu.png",root_export,root_frame,part,t);
            assert(!dw4_png_write(path,tex->rgba,tex->w,tex->h));
        }
        for(unsigned v=0;v<3;v++){
            float q=draw[i].stq?draw[i].v[v][4]:1;assert(q!=0);
            fprintf(out,"%s\t%zu\t%zu\t%.6f\t%.6f\t%.6f\t%.6f\t%.9g\t%u\t%u\t%u\t%u\t%d\t%d\t%.9g\t%u\t%u\t%u\t%u\t%u\n",
                part,t,i,draw[i].v[v][0],draw[i].v[v][1],draw[i].v[v][2]/q,draw[i].v[v][3]/q,
                q,draw[i].rgba[v][0],draw[i].rgba[v][1],draw[i].rgba[v][2],draw[i].rgba[v][3],tex->w,tex->h,draw[i].z[v],draw[i].depth_mode,draw[i].depth_write,draw[i].filter,draw[i].blend,draw[i].color_mask);
        }
    }
}
/* Real authored model/font draws, using the same two passes as normal boot.
 * Opt-in because GPU availability and wall-clock timings are host-dependent. */
static double render_ms(void)
{struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec*1000.0+t.tv_nsec/1e6;}
static void check_root_gpu(const dw4_ui_draw *models,size_t nm,const dw4_ui_draw *text,size_t nt)
{
    const char *size=getenv("DW4_STATUS_GPU_CHECK");if(!size)return;
    int w,h;assert(sscanf(size,"%dx%d",&w,&h)==2 && w>0 && h>0 && w<=4096 && h<=4096);
    dw4_ui_draw *parts[2];size_t counts[2]={nm,nt};const dw4_ui_draw *source[2]={models,text};
    for(unsigned p=0;p<2;p++){
        parts[p]=malloc(counts[p]*sizeof *parts[p]);assert(parts[p]);
        memcpy(parts[p],source[p],counts[p]*sizeof *parts[p]);
        for(size_t i=0;i<counts[p];i++)for(unsigned v=0;v<3;v++){
            parts[p][i].v[v][0]*=w/640.f;parts[p][i].v[v][1]*=h/448.f;
        }
    }
    dw4_fb cpu={0},gpu={0};assert(!dw4_fb_init(&cpu,w,h) && !dw4_fb_init(&gpu,w,h));
    dw4_gl_layer *g=dw4_gl_layer_open(w,h);assert(g);
    double elapsed[2]={0};
    for(unsigned frame=0;frame<8;frame++)for(unsigned backend=0;backend<2;backend++){
        dw4_fb *fb=backend?&gpu:&cpu;dw4_fb_clear(fb,20,30,40);dw4_render_zbuf_clear(fb);
        double start=render_ms();
        for(unsigned p=0;p<2;p++){
            if(backend)assert(!dw4_gl_layer_ui(g,fb,parts[p],(int)counts[p]));
            else dw4_render_ui_draws(fb,parts[p],(int)counts[p],8);
        }
        if(frame>=2)elapsed[backend]+=render_ms()-start;
    }
    size_t pixels=(size_t)w*h,far=0;double sum=0;
    for(size_t i=0;i<pixels;i++){
        int max=0;for(unsigned c=0;c<3;c++){
            int d=abs(cpu.rgba[4*i+c]-gpu.rgba[4*i+c]);sum+=d;if(d>max)max=d;
        }if(max>4)far++;
    }
    double mean=sum/(pixels*3),percent=100.0*far/pixels;
    fprintf(stderr,"STATUS GPU %s %dx%d: CPU %.3f ms GPU %.3f ms; RGB mean %.4f >4/channel %.3f%% (%s)\n",
        reference_view?reference_view:"root",w,h,elapsed[0]/6,elapsed[1]/6,mean,percent,dw4_gl_layer_info(g));
    const char *out=getenv("DW4_STATUS_GPU_OUT");if(out){char path[4096];
        snprintf(path,sizeof path,"%s/%s-cpu.png",out,reference_view?reference_view:"root");assert(!dw4_png_write(path,cpu.rgba,w,h));
        snprintf(path,sizeof path,"%s/%s-gpu.png",out,reference_view?reference_view:"root");assert(!dw4_png_write(path,gpu.rgba,w,h));
    }
    /* These pixel differences are diagnostics, not a retail fidelity pass.
     * GS/GL edge inclusion and nearest-sample boundary rounding differ. The
     * independent material tests and live route validate rendering contracts;
     * retain all image outliers for the separate full-frame fidelity work. */
    dw4_gl_layer_close(g);dw4_fb_free(&cpu);dw4_fb_free(&gpu);free(parts[0]);free(parts[1]);
}
static void render_root(dw4_dialogue *dialogue)
{
    const dw4_ui_draw *draw;size_t count;char error[256]={0};
    dw4_script_value args[]={str("LAYERCTL"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},str("SWITCH"),str("ALL/SET")},result;
    assert(!dw4_scriptservices_call(root_sd,"sd",args,5,&result,error,sizeof error));
    struct snapshot {dw4_scene *scene;void *nodes;size_t bytes;long long engine;double time;} scenes[32];size_t nscene=0;
    size_t models=dw4_controllers_count(root_models);int64_t *times=malloc(models*sizeof *times);assert(times);
    FILE *clocks=NULL;
    if(root_export){char path[4096];snprintf(path,sizeof path,"%s/root-%u-clocks.tsv",root_export,root_frame);
        clocks=fopen(path,"w");assert(clocks);fputs("name\tslot\tsequence\tns\tx\ty\tz\tpack\tid\tactive\tdrawable\n",clocks);}
    for(size_t i=0;i<models;i++){
        const dw4_stageobject *info;const dw4_modelctrl *model=dw4_controllers_model(root_models,i,&info,NULL);assert(model);times[i]=dw4_modelctrl_time(model);
        if(clocks && (dw4_modelctrl_drawable(model) || strstr(dw4_stageobject_name(info),"cursor"))){
            int32_t slot;dw4_controllers_model(root_models,i,NULL,&slot);dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(model,&actor);
            fprintf(clocks,"%s\t%d\t%s\t%lld\t%.6f\t%.6f\t%.6f\t%s\t%u\t%d\t%d\n",dw4_stageobject_name(info),slot,dw4_modelctrl_sequence(model)?dw4_modelctrl_sequence(model):"inactive",(long long)times[i],actor.position[0],actor.position[1],actor.position[2],info->path,info->id,dw4_modelctrl_active(model),dw4_modelctrl_drawable(model));}
        int duplicate=0;for(size_t j=0;j<nscene;j++)if(scenes[j].scene==info->scene)duplicate=1;
        if(!duplicate){assert(nscene<32);struct snapshot *p=scenes+nscene++;p->scene=info->scene;p->bytes=(size_t)p->scene->nnode*sizeof *p->scene->node;
            p->nodes=malloc(p->bytes);assert(p->nodes);memcpy(p->nodes,p->scene->node,p->bytes);p->engine=p->scene->engine_time;p->time=p->scene->time_ns;}
    }
    if(clocks)assert(!fclose(clocks));
    assert(!draw_root(&draw,&count,error,sizeof error));
    for(size_t i=0;i<nscene;i++){assert(!memcmp(scenes[i].nodes,scenes[i].scene->node,scenes[i].bytes) && scenes[i].scene->engine_time==scenes[i].engine && scenes[i].scene->time_ns==scenes[i].time);free(scenes[i].nodes);}
    for(size_t i=0;i<models;i++)assert(dw4_modelctrl_time(dw4_controllers_model(root_models,i,NULL,NULL))==times[i]);
    free(times);
    dw4_ui_draw *saved=malloc(count*sizeof *saved);assert(saved);memcpy(saved,draw,count*sizeof *saved);size_t original_count=count;
    assert(!draw_root(&draw,&count,error,sizeof error) && count==original_count && !memcmp(saved,draw,count*sizeof *saved));free(saved);
    args[4]=str("ALL/CLR");assert(!dw4_scriptservices_call(root_sd,"sd",args,5,&result,error,sizeof error));
    assert(!draw_root(&draw,&count,error,sizeof error) && !count);
    args[4]=str("ALL/SET");assert(!dw4_scriptservices_call(root_sd,"sd",args,5,&result,error,sizeof error));
    assert(!draw_root(&draw,&count,error,sizeof error) && count==original_count);
    fprintf(stderr,"STATUS root meshes: %zu triangles\n",count);assert(count>=2);
    assert(draw[0].color_mask==15 && draw[1].color_mask==15 && draw[0].depth_write && draw[1].depth_write);
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));dw4_fb_clear(&fb,0,0,0);
    dw4_render_zbuf_clear(&fb);
    int wrap=dw4_render_tex_wrap,linear=dw4_render_tex_linear,aref=dw4_render_aref;
    dw4_render_tex_wrap=dw4_render_tex_linear=1;dw4_render_aref=12;
    FILE *export=NULL;
    if(root_export){char path[4096];snprintf(path,sizeof path,"%s/root-%u.tsv",root_export,root_frame);
        export=fopen(path,"w");assert(export);fputs("part\ttexture\ttriangle\tx\ty\tu\tv\tq\tr\tg\tb\ta\tw\th\tz\tdepth\tdepth_write\tfilter\tblend\tcolor_mask\n",export);
        export_root_draws(export,"model",draw,count);}
    dw4_ui_draw *gpu_models=NULL;size_t gpu_count=count;
    if(getenv("DW4_STATUS_GPU_CHECK")){gpu_models=malloc(count*sizeof *gpu_models);assert(gpu_models);memcpy(gpu_models,draw,count*sizeof *gpu_models);}
    dw4_render_ui_draws(&fb,draw,(unsigned)count,1);
    assert(!dw4_dialogue_draw(dialogue,640,448,&draw,&count));fprintf(stderr,"STATUS root text: %zu triangles\n",count);
    if(export){export_root_draws(export,"text",draw,count);assert(!fclose(export));}
    dw4_render_ui_draws(&fb,draw,(unsigned)count,1);
    if(gpu_models){check_root_gpu(gpu_models,gpu_count,draw,count);free(gpu_models);}
    if(root_capture)assert(!dw4_png_write(root_capture,fb.rgba,fb.w,fb.h));
    if(root_export){char path[4096];snprintf(path,sizeof path,"%s/root-%u.png",root_export,root_frame);
        assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));root_frame++;}
    dw4_render_tex_wrap=wrap;dw4_render_tex_linear=linear;dw4_render_aref=aref;
    dw4_fb_free(&fb);
}
static void capture_view(dw4_dialogue *d,int player,const char *label)
{
    if(!strcmp(label,"key-folder") || !strcmp(label,"disk-folder")){
        folder_panel_visible(root_models);
    }
    if(root_export){char path[4096];snprintf(path,sizeof path,"%s/frames.tsv",root_export);
        FILE *out=fopen(path,root_frame?"a":"w");assert(out);
        if(!root_frame)fputs("frame\tplayer\tview\n",out);
        fprintf(out,"%u\t%d\t%s\n",root_frame,player,label);assert(!fclose(out));}
    reference_view=label;render_root(d);reference_view=NULL;
}
static void owned_root(dw4_statusview_context *view,const dw4_databases *db,dw4_statusstats *stats,dw4_controllers *m,dw4_dialogue *d,int64_t *ns)
{
    char error[256];struct gear_host host={.players=view->players};
    dw4_statusmenu_context c={.gear={.view=*view,.databases=db,.stats=stats,.input=skill_input,.appearance=gear_appearance,.user=&host},.dialogue=d};
    for(int player=0;player<4;player++){
        c.gear.view.player=player;
        assert(!dw4_playerrecords_create(view->players,db,player,"p_dorumon",root_export?"aa":"Root",error,sizeof error));
        dw4_menu_window *w=dw4_statusmenu_window_open(&c);assert(w && !dw4_menu_window_count(w));
        const beNDMWStatusCtrl00 *s=dw4_statusmenu_window_state(w);assert(s);
        skill_steps(w,m,d,ns,160);assert(s->_st0==1 && s->_st1==0 && dw4_menu_window_count(w)==5);
        assert(dw4_statusstats_state(stats).valid && dw4_statusstats_state(stats).player==player);
        int cursor_visible=0;
        for(size_t i=0;i<dw4_controllers_count(m);i++){
            const dw4_stageobject *info;int32_t slot;
            const dw4_modelctrl *ctrl=dw4_controllers_model(m,i,&info,&slot);
            if(slot==player && !strcmp(dw4_stageobject_name(info),"i_stcursor02")){
                assert(dw4_modelctrl_drawable(ctrl));cursor_visible=1;}
        }
        assert(cursor_visible);
        capture_view(d,player,"root");
        for(int choice=0;choice<3;choice++){
            dw4_dialogue_input(d,player,0,0,0x4000);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,160);
            assert(s->_st1==choice+1 && dw4_menu_window_count(w)==5);
            if(capture_menus)capture_view(d,player,choice==0?"equipment-selector":choice==1?"folder-selector":"skill-selector");
            if(!choice){
                dw4_menu_window *menu=w->children[4];dw4_menu_window *equipment=dw4_statusequipmentmenu_window_is(menu)?menu:NULL;assert(equipment && menu_submenu_read(equipment,DW4_STATUS_EQUIP).window.sub==0);
                for(int kind=0;kind<3;kind++){
                    dw4_dialogue_input(d,player,0,0,0x4000);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,160);
                    assert(menu_submenu_read(equipment,DW4_STATUS_EQUIP).window.sub==kind+1 && dw4_menu_window_count(menu)==2 && dw4_statusgear_window_is(menu->children[1]));
                    if(capture_menus)capture_view(d,player,kind==0?"weapon-slot":kind==1?"armor-slot":"sub-slot");
                    dw4_dialogue_input(d,player,0,0,0x2000);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,160);
                    assert(menu_submenu_read(equipment,DW4_STATUS_EQUIP).window.sub==0 && menu_submenu_read(equipment,DW4_STATUS_EQUIP).window.selection==kind && dw4_menu_window_count(menu)==2);
                    if(kind<2){dw4_dialogue_input(d,player,4,0,0);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,120);assert(menu_submenu_read(equipment,DW4_STATUS_EQUIP).window.selection==kind+1);}
                }
            }
            if(capture_menus && player==0 && choice==1){
                dw4_menu_window *menu=w->children[4];dw4_menu_window *folder=dw4_statusfolder_window_is(menu)?menu:NULL;assert(folder);
                skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(folder,DW4_STATUS_FOLDER).window.sub==1);
                capture_view(d,player,"device-list");
                skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(folder,DW4_STATUS_FOLDER).window.delay==2);
                capture_view(d,player,"device-actions");
                skill_edge(w,m,d,ns,0,0x2000);skill_edge(w,m,d,ns,0,0x2000);assert(menu_submenu_read(folder,DW4_STATUS_FOLDER).window.sub==0);
                for(int row=1;row<=3;row++){
                    skill_edge(w,m,d,ns,4,0);assert(menu_submenu_read(folder,DW4_STATUS_FOLDER).window.selection==row);
                    skill_edge(w,m,d,ns,0,0x4000);assert(menu_submenu_read(folder,DW4_STATUS_FOLDER).window.sub==row+1);
                    capture_view(d,player,row==1?"key-folder":row==2?"disk-folder":"currency-no-recipient");
                    if(row==2){
                        skill_edge(w,m,d,ns,0,0x4000);capture_view(d,player,"disk-actions");
                        skill_edge(w,m,d,ns,4,0);skill_edge(w,m,d,ns,0,0x4000);capture_view(d,player,"disk-refusal");
                        skill_edge(w,m,d,ns,0,0x4000);
                    }
                    skill_edge(w,m,d,ns,0,0x2000);assert(menu_submenu_read(folder,DW4_STATUS_FOLDER).window.sub==0);
                }
            }
            if(capture_menus && player==0 && choice==2){
                dw4_menu_window *menu=w->children[4];dw4_menu_window *skill=dw4_statusskill_window_is(menu)?menu:NULL;assert(skill);
                for(int mode=0;mode<3;mode++){
                    assert(menu_submenu_read(skill,DW4_STATUS_SKILL).window.selection==mode);skill_edge(w,m,d,ns,0,0x4000);
                    assert(menu_submenu_read(skill,DW4_STATUS_SKILL).window.sub==3 && menu_submenu_read(skill,DW4_STATUS_SKILL).mode==mode);
                    capture_view(d,player,mode==0?"skill-species":mode==1?"skill-thresholds":"skill-techniques");
                    skill_edge(w,m,d,ns,0,0x2000);assert(menu_submenu_read(skill,DW4_STATUS_SKILL).window.sub==2 && menu_submenu_read(skill,DW4_STATUS_SKILL).window.selection==mode);
                    if(mode<2)skill_edge(w,m,d,ns,4,0);
                }
            }
            dw4_dialogue_input(d,player,0,0,0x2000);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,160);
            assert(s->_st1==0 && dw4_menu_window_count(w)==5 && s->_statusMenu==choice);
            if(choice<2){dw4_dialogue_input(d,player,4,0,0);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,120);assert(s->_retCode==choice+1);}
        }
        dw4_dialogue_input(d,player,0,0,0x2000);step(w,m,d,ns);dw4_dialogue_input(d,player,0,0,0);skill_steps(w,m,d,ns,240);
        assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);
        w=dw4_statusmenu_window_open(&c);assert(w);skill_steps(w,m,d,ns,160);dw4_menu_window_remove(w);skill_steps(w,m,d,ns,240);assert(!dw4_menu_window_data(w)->_isRun && !dw4_menu_window_count(w));dw4_menu_window_close(w);
    }
}
int main(int argc,char **argv)
{
    int root_only=argc==5 && !strcmp(argv[4],"--root-only");
    assert(argc<=4 || root_only);
    capture_menus=getenv("DW4_STATUS_CAPTURE_MENUS")!=NULL;assert(!capture_menus || (root_only && argc>3));
    const char *clocks_path=getenv("DW4_STATUS_REFERENCE_CLOCKS");
    if(clocks_path){
        assert(root_only);FILE *clocks=fopen(clocks_path,"r");assert(clocks);
        char line[512];while(fgets(line,sizeof line,clocks)){
            assert(reference_count<256);struct reference_clock *r=reference_clocks+reference_count;long long ns;
            int fields=sscanf(line,"%127s %d %lld %63s",r->name,&r->slot,&ns,r->view);
            assert((fields==3 || fields==4) && r->slot>=0 && r->slot<4);
            r->ns=ns;reference_count++;
        }
        assert(!fclose(clocks) && reference_count);
    }
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    struct host h={.sd=dw4_scriptservices_open(),.preparing=1};assert(h.sd);
    dw4_be_state state;dw4_be_init(&state);dw4_scriptengine *engine=dw4_scriptengine_open(&state,binding,&h);assert(engine);
    dw4_filelist *files=dw4_filelist_open(&mount);assert(files);dw4_scriptengine_filelist(engine,files);
    assert(!dw4_filelist_begin(files,engine,"stagML11",7));assert(!dw4_filelist_shared(files));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(files,dw4_stageobjects_route,objects));
    assert(!dw4_filelist_bind_layers(files,dw4_stageobjects_bind_layers,objects));
    char db_error[256];dw4_databases *databases=dw4_databases_open(objects,db_error,sizeof db_error);
    if(!databases)fprintf(stderr,"database: %s\n",db_error);
    assert(databases && dw4_databases_get(databases,"shinka"));
    assert(!dw4_stageobjects_publish(objects,h.sd,7));
    dw4_controllers *models=dw4_controllers_open(h.sd,7,objects,NULL,0,&state.random,&state.action_rhythm,NULL);assert(models);
    char render_error[256]={0};dw4_modelview *renderer=dw4_modelview_open(objects,models,render_error,sizeof render_error);
    if(!renderer)fprintf(stderr,"model renderer: %s\n",render_error);
    assert(renderer);root_renderer=renderer;root_sd=h.sd;root_models=models;root_capture=argc>2?argv[2]:NULL;root_export=argc>3?argv[3]:NULL;
    const dw4_ui_draw *render_draws;size_t render_count;
    assert(!dw4_modelview_draw(renderer,640,448,&render_draws,&render_count,render_error,sizeof render_error) && !render_count);
    dw4_dialogue *d=dw4_dialogue_open(h.sd,7,objects);assert(d);
    assert(dw4_scriptservices_register(h.sd,7,"SOUND",NULL,-1,1,sound,NULL));h.preparing=0;
    dw4_playerrecords *players=dw4_playerrecords_open();assert(players);
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",0);
    dw4_statusstats stats={.players=players,.sd=h.sd,.dialogue=d,
        .name=dw4_databases_shinka_name,.database=databases};
    dw4_subwindow_factory stat_factory={.user=&stats,.update=stat_update,.preview=stat_preview};
    assert(!dw4_subwindows_factory(dw4_dialogue_subwindows(d),&stat_factory));
    if(root_only){
        dw4_statusview_context fresh={.sd=h.sd,.engine=engine,.players=players,.scope=7,.player=0,
            .refresh=dw4_statusstats_refresh,.user=&stats};int64_t fresh_ns=0;
        h.players=players;owned_root(&fresh,databases,&stats,models,d,&fresh_ns);h.players=NULL;
        goto cleanup;
    }
    /* Production records reach the actual authored Title01 font/model owner. */
    const char *starter[]={"p_dorumon","p_agumon","p_vmon","p_girumon"};
    for(int i=0;i<4;i++){
        char error[256];assert(!dw4_playerrecords_create(players,databases,0,starter[i],"John",error,sizeof error));
        stat_command(h.sd,"UPDATE",0);
        content(d,"STWINFONT02","font000","John");content(d,"STWINFONT04","font000","1");
        int32_t species,hp,mp;assert(!dw4_property_number(f,"DIGIMONNO",&species));
        assert(!dw4_property_number(f,"HP",&hp) && !dw4_property_number(f,"MP",&mp));
        content(d,"STWINFONT04","font001",dw4_databases_shinka_name(databases,species));
        char value[32];snprintf(value,sizeof value,"%d",hp);content(d,"STWINFONT06","font000",value);
        snprintf(value,sizeof value,"%d",mp);content(d,"STWINFONT06","font001",value);
        content(d,"STWINFONT06","font071","341");
    }
    const char *keys[]={"DIGIMONNO","LEVEL","HP","MP","MHP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO","XDATA","BIT","EXP","NEXTEXP"};
    const int32_t values[]={0,10,90,30,100,40,11,12,13,14,15,16,17,18,19,20,21,100,250};
    for(size_t i=0;i<sizeof values/sizeof *values;i++)assert(!dw4_property_set_number(f,keys[i],values[i]));
    uint16_t name[]={ 'J','o','h','n' };dw4_unicode_object object={name,4,1};
    assert(!dw4_property_set_unicode_objects(f,"PLAYERNAME",&object,1));
    name[0]='X'; /* PLAYERNAME owns its original codes. */
    dw4_statusctrl parent={.last_selection=1,.selection=-1};
    dw4_statusview_context context={.sd=h.sd,.engine=engine,.players=players,.scope=7,.player=0,.callno=30,.parent=&parent,.refresh=dw4_statusstats_refresh,.user=&stats};
    int64_t ns=0;
    const char *groups[]={NULL,"STWINFONT06",NULL,"STWINFONT34","STWINFONT12","STWINFONT08"};
    const char *names[]={NULL,"font030",NULL,"font000","font000","font001"};
    for(int kind=0;kind<=5;kind++){
        dw4_menu_window *w=dw4_statusview_window_open(kind,&context);assert(w);
        step(w,models,d,&ns);assert(dw4_menu_window_data(w)->_isRun);
        const dw4_dialogue_text *t=groups[kind]?text(d,groups[kind],names[kind]):NULL;
        if(t)assert(t->visible && t->count>0);
        if(kind==DW4_STATUS_TITLE01){
            content(d,"STWINFONT02","font000","John");
            content(d,"STWINFONT04","font000","10");content(d,"STWINFONT04","font001","Agumon");
            content(d,"STWINFONT06","font000","90");content(d,"STWINFONT06","font001","30");
            content(d,"STWINFONT06","font010","100");content(d,"STWINFONT06","font071","150");
            char error[256];assert(dw4_statusstats_state(&stats).valid);
            assert(!dw4_property_set_number(f,"MHP",110));assert(!dw4_property_set_number(f,"MMP",35));
            assert(!dw4_property_set_number(f,"HP",80));assert(!dw4_property_set_number(f,"MP",20));
            stat_command(h.sd,"ONPREVIEW",0);
            content(d,"STWINFONT06","font010","110");content(d,"STWINFONT06","font011","35");
            const dw4_dialogue_text *up=text(d,"STWINFONT06","font010"),*down=text(d,"STWINFONT06","font011"),*same=text(d,"STWINFONT06","font040");
            assert(up->color[0]==0 && up->color[1]==.96f && up->color[2]==1);
            assert(down->color[0]==.94f && down->color[1]==.4f && down->color[2]==.25f);
            assert(same->color[0]==.9f && same->color[1]==.9f && same->color[2]==.9f);
            stat_command(h.sd,"OFPREVIEW",0);
            content(d,"STWINFONT06","font010","100");assert(up->color[0]==.9f && down->color[2]==.9f);
            int32_t v;assert(!dw4_property_number(f,"HP",&v) && v==90);assert(!dw4_property_number(f,"MP",&v) && v==30);
            /* The actual Work list is authoritative; a returned snapshot is isolated. */
            beNDMWStatusInfoWork *sw=DW4_ARENA_OBJ(stats.arena,beNDMWStatusInfoWork,stats.work);
            igIntList *sl=DW4_ARENA_OBJ(stats.arena,igIntList,(dw4_handle){(uint32_t)sw->_parameter});
            int32_t *baseline=dw4_arena_at(stats.arena,(dw4_handle){(uint32_t)sl->_data},13*4);
            dw4_statusstats_snapshot copied=dw4_statusstats_state(&stats);
            baseline[0]=101;baseline[11]=91;
            stat_command(h.sd,"OFPREVIEW",0);content(d,"STWINFONT06","font010","101");
            assert(!dw4_property_number(f,"HP",&v) && v==91 && copied.value[11]==90);
            baseline[0]=100;baseline[11]=90;stat_command(h.sd,"OFPREVIEW",0);
            /* Preview-off leaves equipment's altered stat records to its owner. */
            assert(!dw4_property_number(f,"MHP",&v) && v==110);
            const dw4_database *shinka=dw4_databases_get(databases,"shinka");
            assert(dw4_database_string_rows(shinka)==16);
            for(int32_t row=0;row<16;row++){
                assert(!dw4_property_set_number(f,"DIGIMONNO",row));
                stat_command(h.sd,"UPDATE",0);
                content(d,"STWINFONT04","font001",dw4_database_string(shinka,row,"NAME"));
            }
            assert(!dw4_property_set_number(f,"DIGIMONNO",16));
            assert(dw4_statusstats_refresh(&stats,0,error,sizeof error)==-1);
            assert(strstr(error,"shinka NAME"));
            assert(!dw4_property_set_number(f,"DIGIMONNO",0));
        }
        if(kind==DW4_STATUS_SELECT00){
            for(int i=0;i<100;i++)step(w,models,d,&ns);
            assert(dw4_menu_window_data(w)->_isRun && parent.selection==1);
            /* Cancel through the real SELECTCTRL/model sequence, not REMOVE. */
            dw4_dialogue_input(d,0,0,0,0x2000);
            step(w,models,d,&ns);
            for(int i=0;i<200 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
            assert(parent.selection==-1);
        }else{
            for(int i=0;i<60;i++)step(w,models,d,&ns);
            dw4_menu_window_remove(w);step(w,models,d,&ns);
            assert(dw4_menu_window_data(w)->_st0==3 && dw4_menu_window_data(w)->_isRun); /* completion waits on real models */
            for(int i=0;i<200 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
        }
        assert(!dw4_menu_window_data(w)->_isRun);if(t)assert(!t->visible);
        dw4_menu_window_close(w);
    }
    for(int row=0;row<=2;row+=2){
        parent.last_selection=row;parent.selection=-1;
        dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_SELECT00,&context);assert(w);
        for(int i=0;i<100;i++)step(w,models,d,&ns);
        assert(dw4_menu_window_data(w)->_isRun && parent.selection==row);
        dw4_dialogue_input(d,0,0,0,0x4000);step(w,models,d,&ns);
        for(int i=0;i<200 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
        assert(!dw4_menu_window_data(w)->_isRun && parent.selection==row);
        dw4_menu_window_close(w);
    }
    /* Original submenu menu text + real cursor confirm/close for every call. */
    const int calls[]={31,61,91};
    for(unsigned j=0;j<3;j++){
        context.callno=calls[j];context.selected=j==1?3:2;
        dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_SELECT01,&context);assert(w);
        for(int i=0;i<100;i++)step(w,models,d,&ns);
        const dw4_dialogue_text *row=text(d,"STWINFONT09",j==1?"font003":"font002");assert(row && row->visible && row->count);
        assert(parent.selection==context.selected);
        dw4_dialogue_input(d,0,0,0,0x4000);step(w,models,d,&ns);
        for(int i=0;i<200 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
        assert(!dw4_menu_window_data(w)->_isRun && parent.selection==context.selected && !row->visible);dw4_menu_window_close(w);
    }
    /* E0/E1 have caller-owned row counts/positions and copied disabled flags. */
    uint8_t enabled[]={1,0,1};context.rows=3;context.selected=2;context.enabled=enabled;context.callno=0;
    context.position[0]=-83;context.position[1]=148;
    for(int kind=DW4_STATUS_SELECTE0;kind<=DW4_STATUS_SELECTE1;kind++){
        enabled[2]=1;
        dw4_menu_window *w=dw4_statusview_window_open(kind,&context);assert(w);enabled[2]=0;
        for(int i=0;i<100;i++)step(w,models,d,&ns);
        assert(dw4_menu_window_data(w)->_isRun && parent.selection==2);
        dw4_dialogue_input(d,0,0,0,0x4000);step(w,models,d,&ns);
        for(int i=0;i<200 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
        assert(!dw4_menu_window_data(w)->_isRun && parent.selection==2);dw4_menu_window_close(w);
    }
    context.enabled=NULL;context.rows=0;
    assert(!dw4_statusview_window_open(DW4_STATUS_SELECTE0,&context));
    /* Production database strings and original skill labels reach authored
     * page rows. Repeated refresh retains one close resource per model/font. */
    char creation_error[256];assert(!dw4_playerrecords_create(players,databases,0,"p_dorumon","John",creation_error,sizeof creation_error));
    struct page page={players,databases,0,1,0};context.user=&page;context.initialize=page_setup;
    for(int mode=0;mode<3;mode++){
        page.mode=mode;page.pages=1;
        dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_CONTENT,&context);assert(w);
        step(w,models,d,&ns);assert(dw4_menu_window_data(w)->_st0==1 && page.rows>=1);
        dw4_statusctrl page_parent={.selection=-1};dw4_statusview_context cursor=context;
        cursor.parent=&page_parent;cursor.rows=page.rows;cursor.selected=0;
        cursor.position[0]=-121;cursor.position[1]=128;cursor.position[2]=0;
        dw4_menu_window *selector=dw4_statusview_window_open(DW4_STATUS_SELECTE1,&cursor);assert(selector);
        assert(!dw4_menu_window_add(w,selector));for(int i=0;i<100;i++)step(w,models,d,&ns);
        assert(page_parent.selection==0 && dw4_menu_window_count(w)==1);
        if(mode==0){content(d,"STWINFONT14","font000","Dorumon");content(d,"STWINFONT42","font000","Lv");content(d,"STWINFONT18","font000","1");}
        if(mode==1)content(d,"STWINFONT18","font008","1");
        for(int i=0;i<128;i++)assert(!dw4_statuscontent_skill(players,databases,0,mode,0,1,0,mode==0,1,dw4_statusview_window_emit,w));
        const dw4_dialogue_text *desc=text(d,"STWINFONT29","font000");assert(desc && desc->count);
        if(mode==0){
            int32_t use[16],levels[16];for(int i=0;i<16;i++){use[i]=1;levels[i]=i+10;}
            assert(!dw4_property_set_array(f,"BASE_ISUSE",use,16));assert(!dw4_property_set_array(f,"BASE_LEVEL",levels,16));
        }
        if(mode==1)assert(!dw4_statuscontent_skill_clear_colors(dw4_statusview_window_emit,w));
        dw4_dialogue_input(d,0,0,0,0x4000);step(w,models,d,&ns);
        for(int i=0;i<240 && dw4_menu_window_count(w);i++)step(w,models,d,&ns);
        assert(!dw4_menu_window_count(w) && dw4_menu_window_data(w)->_isRun && page_parent.selection==0);
        dw4_menu_window_remove(w);for(int i=0;i<240 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
        assert(!dw4_menu_window_data(w)->_isRun && !desc->visible);dw4_menu_window_close(w);
    }
    page.mode=0;page.pages=2;
    dw4_menu_window *two_pages=dw4_statusview_window_open(DW4_STATUS_CONTENT,&context);assert(two_pages);
    step(two_pages,models,d,&ns);assert(page.rows==8);
    content(d,"STWINFONT24","font000","1");content(d,"STWINFONT24","font001","2");
    assert(!dw4_statuscontent_skill(players,databases,0,0,1,2,0,1,1,dw4_statusview_window_emit,two_pages));
    content(d,"STWINFONT14","font000",dw4_databases_shinka_name(databases,8));content(d,"STWINFONT18","font000","18");
    content(d,"STWINFONT24","font000","2");
    dw4_menu_window_remove(two_pages);for(int i=0;i<240 && dw4_menu_window_data(two_pages)->_isRun;i++)step(two_pages,models,d,&ns);
    assert(!dw4_menu_window_data(two_pages)->_isRun && !text(d,"STWINFONT24","font000")->visible);dw4_menu_window_close(two_pages);
    context.initialize=equipment_setup;
    for(int kind=0;kind<3;kind++){
        page.mode=kind;
        dw4_menu_window *w=dw4_statusview_window_open(DW4_STATUS_CONTENT,&context);assert(w);step(w,models,d,&ns);
        for(int i=0;i<128;i++){
            assert(!dw4_statuscontent_equipment(players,databases,0,kind,0,0,dw4_statusview_window_emit,w));
            assert(!dw4_statuscontent_equipment(players,databases,0,kind,0,1,dw4_statusview_window_emit,w));
        }
        if(kind==0){size_t count;const dw4_item_record *items=dw4_property_items(f,"POWERSOCKET",&count);
            content(d,"STWINFONT11","font000",dw4_statuscontent_item_string(databases,items,"NAME"));}
        dw4_menu_window_remove(w);for(int i=0;i<240 && dw4_menu_window_data(w)->_isRun;i++)step(w,models,d,&ns);
        assert(!dw4_menu_window_data(w)->_isRun);dw4_menu_window_close(w);
    }
    context.initialize=device_setup;
    dw4_menu_window *inventory=dw4_statusview_window_open(DW4_STATUS_CONTENT,&context);assert(inventory);step(inventory,models,d,&ns);
    size_t item_count;const dw4_item_record *starter_items=dw4_property_items(f,"POWERSOCKET",&item_count);
    dw4_item_record device[25];for(unsigned i=0;i<25;i++){device[i]=starter_items[i%3];device[i].equipped=i%2;device[i].pocket=i%6;}
    uint8_t flags[12];for(unsigned i=0;i<12;i++)flags[i]=i%2;
    for(int i=0;i<128;i++)assert(!dw4_statuscontent_device(databases,device,25,flags,i%3,3,0,0,1,1,dw4_statusview_window_emit,inventory));
    assert(!dw4_statuscontent_device(databases,device,25,flags,2,3,0,0,1,1,dw4_statusview_window_emit,inventory));
    content(d,"STWINFONT23","font000","3");content(d,"STWINFONT23","font001","3");
    assert(text(d,"STWINFONT14","font000")->visible && !text(d,"STWINFONT14","font001")->visible);
    assert(text(d,"STWINFONT14","font000")->color[0]==.5f);
    char long_text[1025];memset(long_text,'A',sizeof long_text-1);long_text[sizeof long_text-1]=0;
    dw4_statusview_command long_command={DW4_VIEW_SET_TEXT,"STWINFONT29","font000",NULL,long_text,0};
    assert(!dw4_statusview_window_emit(inventory,&long_command));content(d,"STWINFONT29","font000",long_text);
    /* Invalid identities fail before touching fonts; sink failures retain the
     * owned window's completion until coordinated scene reset. */
    device[24].record=INT32_MAX;
    assert(dw4_statuscontent_device(databases,device,25,flags,2,3,0,0,1,1,dw4_statusview_window_emit,inventory)==-1);
    dw4_menu_window_remove(inventory);for(int i=0;i<5 && dw4_menu_window_data(inventory)->_isRun;i++)step(inventory,models,d,&ns);
    assert(!dw4_menu_window_data(inventory)->_isRun);dw4_menu_window_close(inventory);
    context.user=&stats;context.initialize=NULL;
    owned_folder(&context,databases,models,d,&ns);
    owned_disk(&context,databases,models,d,&ns);
    owned_bit(&context,databases,models,d,&ns);
    owned_flag(&context,databases,models,d,&ns);
    owned_detail(&context,databases,models,d,&ns);
    owned_gear(&context,databases,&stats,models,d,&ns);
    owned_device(&context,databases,models,d,&ns);
    owned_skill(&context,databases,models,d,&ns);
    h.players=players;owned_root(&context,databases,&stats,models,d,&ns);h.players=NULL;
    context.user=&page;context.initialize=page_setup;
    inventory=dw4_statusview_window_open(DW4_STATUS_CONTENT,&context);assert(inventory);step(inventory,models,d,&ns);
    dw4_statusview_command missing={DW4_VIEW_SCRIPT,NULL,"missing_status_content.lua",NULL,NULL,0};
    assert(dw4_statusview_window_emit(inventory,&missing));
    char failure[256];assert(dw4_menu_window_tick(inventory,failure,sizeof failure)==-1 && dw4_menu_window_data(inventory)->_isRun);
    assert(strstr(failure,"scene reset"));dw4_menu_window_close(inventory);
    assert(dw4_statusstats_state(&stats).valid);
    context.refresh=NULL;assert(!dw4_statusview_window_open(DW4_STATUS_TITLE01,&context));
    /* No font substitution: the original three STATUS strings are retained. */
    const dw4_dialogue_text *choice=text(d,"STWINFONT08","font000");assert(choice && choice->count);
cleanup:
    assert(!dw4_scriptengine_reset_scene(engine,h.sd));
    dw4_modelview_close(renderer);dw4_dialogue_close(d);dw4_controllers_close(models);dw4_stageobjects_close(objects);
    dw4_databases_close(databases);
    dw4_filelist_close(files);dw4_scriptengine_close(engine);dw4_scriptservices_close(h.sd);
    dw4_statusstats_close(&stats);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts(root_only?"STATUS root: four fresh prepared player roots, visible cursors, equipment/skill routing, cancel and external close pass":
        "STATUS views: original Lua/fonts and production stats pass; owned DEVICE paging/decisions/identity/transaction/restart; all three skill modes, FOLDER routing, disk reorder/quantity transfers currency digit editing and the complete STATUS root for all four players pass with real SELECTCTRL/model waits, cancel, external close and failure holds");return 0;
}
