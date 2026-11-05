#include "dw4/dialogue.h"
#include "dw4/controllers.h"
#include "dw4/scriptengine.h"
#include "dw4/lobbyui.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
struct host {dw4_scriptservices *sd;int preparing;unsigned errors;};
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct host *h=user;*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    if(!strcmp(method,"SYSgetLightMode"))r->number=1;
    else if(!strcmp(method,"SYSisJoinPlayer"))r->number=n==1 && a[0].number==0;
    else if(!strcmp(method,"SYSgetPlayerName"))*r=str("m_dorumon");
    else if(!strcmp(method,"SYSgetWeaponName"))*r=str("w_axe01");
    else if(!h->preparing)return dw4_scriptservices_call(h->sd,method,a,n,r,error,cap);
    return 0;
}
static int sound(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    (void)method;(void)r;(void)error;(void)cap;
    if(n==5 && a[4].type==DW4_SCRIPT_STRING && !strcmp(a[4].string,"CURSOR_NG"))(*(unsigned *)user)++;
    return 0;
}
static double command(struct host *h,const char *method,const char *category,const char *name,int slot,const char *key,const char *value)
{
    dw4_script_value a[]={str(category),name?str(name):(dw4_script_value){0},{DW4_SCRIPT_NUMBER,slot,NULL,0},str(key),{0}},r;
    if(value)a[4]=str(value);
    char error[256];
    int rc=dw4_scriptservices_call(h->sd,method,a,value?5:4,&r,error,sizeof error);
    if(rc)fprintf(stderr,"%s %s: %s\n",category,key,error);
    assert(!rc);return r.number;
}
static int source(void *user,const char *name,const void **bytes,size_t *size)
{
    (void)name;const char *text=user;*bytes=text;*size=strlen(text);return 0;
}
static const dw4_dialogue_text *text(dw4_dialogue *d,const char *group,const char *name)
{
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++) {
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(!strcmp(t->group,group) && !strcmp(t->name,name))return t;
    }
    assert(0);return NULL;
}
static int subwindow(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    (void)method;(void)n;(void)error;(void)cap;int *state=user;
    if(!strcmp(a[3].string,"REMOVE"))*state=2;
    *r=(dw4_script_value){DW4_SCRIPT_NUMBER,*state!=0,NULL,0};return 0;
}
struct menu_fixture {unsigned begins,ends,released,updates,activates;int32_t mode,player;int fail_prepare,fail_begin,fail_end,fail_activate;dw4_subwindows *owner;};
static void menu_release(void *user){((struct menu_fixture *)user)->released++;}
static int menu_update(dw4_menu_window *w,char *error,size_t cap)
{
    (void)error;(void)cap;((struct menu_fixture *)w->user)->updates++;
    if(dw4_menu_window_data(w)->_st0>=2 && !dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;
    return 0;
}
static int menu_prepare(void *user,int32_t mode,int32_t player,dw4_menu_window **out,char *error,size_t cap)
{
    struct menu_fixture *f=user;f->mode=mode;f->player=player;
    *out=dw4_menu_window_open(menu_update,f,menu_release);if(!*out)return -1;
    if(f->fail_prepare){snprintf(error,cap,"missing player record");return -1;}
    dw4_menu_window *child=dw4_menu_window_open(menu_update,f,menu_release);
    if(!child || dw4_menu_window_add(*out,child)){dw4_menu_window_close(child);return -1;}
    return 0;
}
static int menu_begin(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)error;(void)cap;struct menu_fixture *f=user;assert(mode==f->mode && player==f->player);f->begins++;if(f->fail_begin){snprintf(error,cap,"scene freeze failed");return -1;}return 0;}
static int menu_activate(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{struct menu_fixture *f=user;assert(mode==f->mode && player==f->player);f->activates++;
 assert(dw4_subwindows_tick(f->owner)==-1);
 if(f->fail_activate){snprintf(error,cap,"activation freeze failed");return -1;}return 0;}
static int menu_end(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)error;(void)cap;struct menu_fixture *f=user;assert(mode==f->mode && player==f->player);f->ends++;if(f->fail_end){snprintf(error,cap,"player restoration failed");return -1;}return 0;}
static void tick(struct host *h,dw4_scriptengine *e,dw4_controllers *c,dw4_dialogue *d,unsigned frame)
{
    int64_t ns=(int64_t)frame*1000000000/60;
    dw4_controllers_sample(c,ns);
    assert(!dw4_scriptservices_tick(h->sd,ns));assert(!dw4_scriptengine_tick(e));
    if(dw4_controllers_tick(c,ns)){fprintf(stderr,"controller: %s\n",dw4_controllers_error(c));assert(0);}
    if(dw4_dialogue_tick(d)){fprintf(stderr,"dialogue: %s\n",dw4_dialogue_error(d));assert(0);}
}
int main(int argc,char **argv)
{
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../local/extracted"));
    struct host h={.sd=dw4_scriptservices_open(),.preparing=1};assert(h.sd);
    dw4_be_state state;dw4_be_init(&state);dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&h);assert(e);
    dw4_filelist *files=dw4_filelist_open(&m);assert(files);dw4_scriptengine_filelist(e,files);
    assert(!dw4_filelist_begin(files,e,"stagML11",7));assert(!dw4_filelist_shared(files));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(files,dw4_stageobjects_route,objects));
    assert(!dw4_filelist_bind_layers(files,dw4_stageobjects_bind_layers,objects));
    assert(!dw4_stageobjects_publish(objects,h.sd,7));
    dw4_controllers *controllers=dw4_controllers_open(h.sd,7,objects,NULL,0,&state.random,&state.action_rhythm,NULL);assert(controllers);
    dw4_dialogue *d=dw4_dialogue_open(h.sd,7,objects);assert(d);
    assert(dw4_dialogue_text_count(d)==286);assert(!dw4_dialogue_claimed(d));
    assert(dw4_scriptservices_register(h.sd,7,"SOUND",NULL,-1,1,sound,&h.errors));h.preparing=0;
    const dw4_dialogue_text *t=text(d,"TALKFONT02","font00");
    assert(t->x==-2.12f && t->width==4.96f); /* authored layout, no host constants */
    command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT02/font00/I<39>");
    assert(t->count && !t->visible);uint32_t first=t->codes[0];
    command(&h,"sd","TEXTCTL",NULL,-1,"COLOR","TALKFONT02/font00/V<0.9,0.9,0.47>");
    command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/SET");assert(t->visible && t->color[2]==.47f);
    dw4_script_value bad[]={str("TEXTCTL"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},str("TEXTSET"),str("TALKFONT02/font00/I<999999>")},r;
    char error[256];assert(dw4_scriptservices_call(h.sd,"sd",bad,5,&r,error,sizeof error)==-1);
    assert(t->codes[0]==first); /* invalid replacements preserve owned text */
    command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/CLR");
    /* Rendering samples the owned text and alignment without advancing waits. */
    uint32_t blob_size;const uint8_t *blob=dw4_mount_entry(&m,0,820,&blob_size,NULL);
    dw4_scene scene;dw4_fb fb;assert(blob && !dw4_scene_load(&scene,blob,blob_size));
    assert(!dw4_fb_init(&fb,640,448));
    dw4_lobbyui *ui=dw4_lobbyui_open(&m,&scene,blob,blob_size);assert(ui);
    dw4_lobbyui_dialogue(ui,d);
    command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT02/font00/AB");
    command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/SET");
    command(&h,"sd","LAYERCTL",NULL,-1,"SWITCH","FONT/SET");
    assert(dw4_lobbyui_draw(ui,&fb)>0);
    unsigned draws;const dw4_ui_draw *draw=dw4_lobbyui_draws(ui,&draws);assert(draws==4);
    float left=draw[0].v[0][0];assert(draw[0].rgba[0][0]==114 && draw[0].rgba[0][2]==59);
    command(&h,"sd","TEXTCTL",NULL,-1,"ALIGN","TALKFONT02/font00/RIGHT");
    assert(dw4_lobbyui_draw(ui,&fb)>0);draw=dw4_lobbyui_draws(ui,&draws);
    assert(draws==4 && draw[0].v[0][0]==left); /* ALIGN applies at the next TEXTSET. */
    command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT02/font00/AB");
    assert(dw4_lobbyui_draw(ui,&fb)>0);draw=dw4_lobbyui_draws(ui,&draws);
    assert(draws==4 && draw[0].v[0][0]>left+400);
    command(&h,"sd","TEXTCTL",NULL,-1,"ALIGN","TALKFONT02/font00/LEFT");
    command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/CLR");
    assert(dw4_lobbyui_draw(ui,&fb)==0);
    /* Authored layer masks and ancestor transforms are sampled at draw time. */
    command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT02/font00/AB");
    command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/DISPON");
    assert(dw4_lobbyui_draw(ui,&fb)==4);
    command(&h,"sd","LAYERCTL",NULL,-1,"SWITCH","FONT/CLR");
    assert(dw4_lobbyui_draw(ui,&fb)==0 && t->visible);
    command(&h,"sd","LAYERCTL",NULL,-1,"SWITCH","FONT/SET");
    dw4_stageobject const *font_info=dw4_stageobjects_find(objects,"beFontInfo",NULL,0);
    assert(font_info);dw4_scene *font_scene=font_info->scene;
    unsigned node=UINT32_MAX;
    for(unsigned i=0;i<font_scene->nnode;i++)if(font_scene->node[i].id==112){node=i;break;}
    assert(node!=UINT32_MAX);
    dw4_scene_node *parent=&font_scene->node[font_scene->node[node].parent];
    parent->has_matrix=1;memset(parent->m,0,sizeof parent->m);
    parent->m[0]=parent->m[5]=parent->m[10]=parent->m[15]=1;parent->m[12]=1;
    assert(dw4_lobbyui_draw(ui,&fb)==4);draw=dw4_lobbyui_draws(ui,&draws);
    assert(fabsf(draw[0].v[0][0]-left-100)<.001f);
    parent->has_matrix=0;
    command(&h,"sd","TEXTCTL",NULL,-1,"SETPOSITION","TALKFONT02/font00/V<1,2,3>");
    assert(dw4_lobbyui_draw(ui,&fb)==4);draw=dw4_lobbyui_draws(ui,&draws);
    assert(draw[0].v[0][0]>400 && t->x==1 && t->y==2);
    command(&h,"sd","TEXTCTL",NULL,-1,"SETPOSITION","TALKFONT02/font00/V<-2.12,-1.2,0>");
    uint16_t object[]={'A',0xffff,0x2261,0,'B'};
    assert(!dw4_dialogue_replace_unknown(d,object,5,'?'));
    assert(object[0]=='A' && object[1]=='?' && object[2]==0x2261 && object[4]=='B');
    assert(!dw4_dialogue_set_unicode(d,"TALKFONT02","font00",object,5));
    assert(t->count==3 && t->codes[2]==0x2261);
    const dw4_ui_draw *native_draw;size_t native_count;
    assert(!dw4_dialogue_draw(d,1280,896,&native_draw,&native_count) && native_count==6);
    float high_x=native_draw[0].v[0][0],high_y=native_draw[0].v[0][1];
    assert(!dw4_dialogue_draw(d,640,448,&native_draw,&native_count) && native_count==6);
    assert(high_x==2*native_draw[0].v[0][0] && high_y==2*native_draw[0].v[0][1]);
    object[0]='Z'; /* Text and geometry do not borrow the caller's object. */
    assert(t->codes[0]=='A' && dw4_lobbyui_draw(ui,&fb)==6);
    command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT02/font00/AB\nCD");
    assert(dw4_lobbyui_draw(ui,&fb)==8);draw=dw4_lobbyui_draws(ui,&draws);
    assert(fabsf(draw[4].v[0][1]-draw[0].v[0][1]-28)<.001f);
    command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/DISPOFF");
    dw4_lobbyui_dialogue(ui,NULL);dw4_lobbyui_close(ui);dw4_fb_free(&fb);dw4_scene_close(&scene);
    unsigned frame=0;
    /* Execute original funcOneMessage bytecode for all greeting pages. The
     * fixture only chooses context and publishes the original helper's queue. */
    for(unsigned page=39;page<=53;page++) {
        char fixture[256];snprintf(fixture,sizeof fixture,"g_talk='talk' g_messPlayerNo=0 funcOneMessage('TALKFONT02/font00/I<%u>') be:DMrun() [EOF]",page);
        dw4_script_source_set(dw4_scriptengine_vm(e),source,fixture,NULL);
        int rc=dw4_script_run_named(dw4_scriptengine_vm(e),"dialogue-fixture.lua",NULL);
        if(rc)fprintf(stderr,"helper: %s\n",dw4_script_error(dw4_scriptengine_vm(e)));
        assert(!rc);
        for(unsigned i=0;i<8;i++)tick(&h,e,controllers,d,++frame);
        assert(t->visible && command(&h,"querySD","SELECTCTRL","i_talkky",0,"ISEND",NULL)==0);
        for(unsigned i=0;i<8;i++){assert(t->count);assert(command(&h,"querySD","SELECTCTRL","i_talkky",0,"ISEND",NULL)==0);}
        dw4_dialogue_input(d,0,0,0,0x4000);tick(&h,e,controllers,d,++frame);
        unsigned limit=frame+80;
        while(dw4_scriptengine_pending(e) && frame<limit)tick(&h,e,controllers,d,++frame);
        assert(!dw4_scriptengine_pending(e) && !t->visible);
        assert(command(&h,"querySD","SELECTCTRL","i_talkky",0,"ISEND",NULL)==1);
    }
    /* The original vararg choice helper owns its delay-12 font/window queue. */
    dw4_script_source_set(dw4_scriptengine_vm(e),source,
        "g_talk='talk' g_messPlayerNo=0 funcChoiceMessage('TALKFONT02/font01/I<54>','TALKFONT02/font02/I<55>') be:DMrun() [EOF]",NULL);
    assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"choice-fixture.lua",NULL));
    for(unsigned i=0;i<35;i++)tick(&h,e,controllers,d,++frame);
    assert(text(d,"TALKFONT02","font01")->visible && text(d,"TALKFONT02","font02")->visible);
    assert(command(&h,"querySD","SELECTCTRL","i_messcr",0,"ISEND",NULL)==0);
    dw4_dialogue_input(d,0,4,0,0);tick(&h,e,controllers,d,++frame);
    assert(command(&h,"querySD","SELECTCTRL","i_messcr",0,"GETSELECT",NULL)==1);
    for(unsigned i=0;i<20;i++)tick(&h,e,controllers,d,++frame);
    dw4_dialogue_input(d,0,0,0,0x4000);tick(&h,e,controllers,d,++frame);
    unsigned choice_limit=frame+100;
    while(dw4_scriptengine_pending(e) && frame<choice_limit)tick(&h,e,controllers,d,++frame);
    assert(!dw4_scriptengine_pending(e));
    assert(!text(d,"TALKFONT02","font01")->visible && !text(d,"TALKFONT02","font02")->visible);
    /* The talker's pad answers its choice (co-op: g_messPlayerNo is the pressing slot, retail BLTgetShootRamNo): with g_messPlayerNo=1 the choice helper
     * drives i_messcr[1] and i_talkky[1], which read pad 1 only; pad 0's stick and Cross change nothing. */
    dw4_script_source_set(dw4_scriptengine_vm(e),source,
        "g_talk='talk' g_messPlayerNo=1 funcChoiceMessage('TALKFONT02/font01/I<54>','TALKFONT02/font02/I<55>') be:DMrun() [EOF]",NULL);
    assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"choice-slot1-fixture.lua",NULL));
    for(unsigned i=0;i<35;i++)tick(&h,e,controllers,d,++frame);
    assert(text(d,"TALKFONT02","font01")->visible && text(d,"TALKFONT02","font02")->visible);
    assert(command(&h,"querySD","SELECTCTRL","i_messcr",1,"ISEND",NULL)==0 && command(&h,"querySD","SELECTCTRL","i_messcr",0,"ISEND",NULL)!=0);
    for(unsigned i=0;i<4;i++){dw4_dialogue_input(d,0,4,0x4000,i?0:0x4000);tick(&h,e,controllers,d,++frame);}   /* pad 0: stick down and Cross */
    assert(command(&h,"querySD","SELECTCTRL","i_messcr",1,"GETSELECT",NULL)==0 && command(&h,"querySD","SELECTCTRL","i_messcr",1,"ISEND",NULL)==0);
    dw4_dialogue_input(d,0,0,0,0);
    dw4_dialogue_input(d,1,4,0,0);tick(&h,e,controllers,d,++frame);   /* pad 1: stick down */
    assert(command(&h,"querySD","SELECTCTRL","i_messcr",1,"GETSELECT",NULL)==1);
    for(unsigned i=0;i<20;i++)tick(&h,e,controllers,d,++frame);
    dw4_dialogue_input(d,1,0,0,0x4000);tick(&h,e,controllers,d,++frame);   /* pad 1: Cross */
    unsigned slot1_limit=frame+100;
    while(dw4_scriptengine_pending(e) && frame<slot1_limit)tick(&h,e,controllers,d,++frame);
    assert(!dw4_scriptengine_pending(e) && !text(d,"TALKFONT02","font01")->visible);
    /* Scene text survives repeated mutation, and reopening has no stale geometry. */
    for(unsigned cycle=0;cycle<32;cycle++) {
        assert(!dw4_dialogue_set_unicode(d,"ALL","font00",NULL,0));
        command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","ALL/font00/CLR");
        command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT03/font00/Speaker");
        command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT03/font00/SET");
        assert(!dw4_dialogue_draw(d,640,448,&native_draw,&native_count) && native_count==14);
        assert(native_draw[0].tex && native_draw[0].tex->rgba);
        command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT03/font00/CLR");
    }
    /* Independent player slot and circle-over-cross cancellation. */
    command(&h,"sd","SELECTCTRL","i_messky",1,"GENERATE",NULL);
    for(unsigned i=0;i<3;i++)tick(&h,e,controllers,d,++frame);
    dw4_dialogue_input(d,0,0,0,0x4000);tick(&h,e,controllers,d,++frame);
    assert(command(&h,"querySD","SELECTCTRL","i_messky",1,"ISEND",NULL)==0);
    dw4_dialogue_input(d,1,0,0,0x6000);tick(&h,e,controllers,d,++frame);
    assert(command(&h,"querySD","SELECTCTRL","i_messky",1,"GETSELECT",NULL)==-1);
    for(unsigned i=0;i<80;i++)tick(&h,e,controllers,d,++frame);
    assert(command(&h,"querySD","SELECTCTRL","i_messky",1,"ISEND",NULL)==1);
    /* The production owner runs an actual owned window tree. Menu-specific
     * update/player/layer leaves are controlled; no inventory gameplay claim. */
    dw4_subwindows *sub=dw4_dialogue_subwindows(d);assert(sub && dw4_subwindows_count(sub)==1);
    dw4_script_value generate[]={str("SUBWND"),{0},{DW4_SCRIPT_NUMBER,0,NULL,0},str("GENERATE"),str("STATUS/I<0>")};
    assert(dw4_scriptservices_call(h.sd,"sd",generate,5,&r,error,sizeof error)==-1);
    assert(strstr(error,"player inventory/save records"));assert(!dw4_subwindows_at(sub,0).active);
    struct menu_fixture fixture={.owner=sub};dw4_subwindow_factory factory={.prepare=menu_prepare,.begin=menu_begin,.end=menu_end,.user=&fixture,.activate=menu_activate};
    assert(!dw4_subwindows_factory(sub,&factory));
    fixture.fail_prepare=1;
    assert(dw4_scriptservices_call(h.sd,"sd",generate,5,&r,error,sizeof error)==-1);
    assert(fixture.released==1 && !dw4_subwindows_at(sub,0).active);fixture.fail_prepare=0;
    const char *modes[]={"STATUS","XDATA","LABO","BANK","CNOS","DISK","WPU","APU","CHIP","JUNK","CARD"};
    for(unsigned cycle=0;cycle<44;cycle++) {
        unsigned released=fixture.released;char payload[64];snprintf(payload,sizeof payload,"%s/I<%u>",modes[cycle%11],cycle%4);
        command(&h,"sd","SUBWND",NULL,0,"GENERATE",payload);
        assert(dw4_subwindows_at(sub,0).active && dw4_subwindows_at(sub,0).state==0);
        assert(fixture.mode==(int32_t)(cycle%11) && fixture.player==(int32_t)(cycle%4));
        assert(fixture.activates==cycle+1 && fixture.begins==cycle);
        assert(dw4_subwindows_factory(sub,NULL)==-1 && dw4_dialogue_subwindow(d,subwindow,NULL)==-1);
        command(&h,"sd","SUBWND",NULL,0,"GENERATE","bad payload ignored while active");
        assert(fixture.activates==cycle+1);
        /* REMOVE before the first model update defers through the SD queue. */
        command(&h,"sd","SUBWND",NULL,0,"REMOVE",NULL);
        assert(dw4_scriptservices_pending(h.sd)==1);
        unsigned updates=fixture.updates;
        dw4_script_source_set(dw4_scriptengine_vm(e),source,"assert(be:DMgetCount()==-1) [EOF]",NULL);
        for(unsigned query=0;query<20;query++)assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"menu-held.lua",NULL));
        assert(fixture.updates==updates && dw4_scriptservices_pending(h.sd)==1);
        tick(&h,e,controllers,d,++frame);assert(dw4_subwindows_at(sub,0).active);
        for(unsigned guard=0;guard<8 && dw4_subwindows_at(sub,0).active;guard++)tick(&h,e,controllers,d,++frame);
        assert(!dw4_subwindows_at(sub,0).active && !dw4_scriptservices_pending(h.sd));
        assert(fixture.released==released+2 && fixture.ends==cycle+1 && fixture.begins==cycle+1);
        dw4_script_source_set(dw4_scriptengine_vm(e),source,"assert(be:DMgetCount()==0) [EOF]",NULL);
        assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"menu-closed.lua",NULL));
    }
    assert(!dw4_subwindows_factory(sub,NULL));
    /* SUBWND's completion follows a borrowed real owner's state, including
     * its asynchronous REMOVE. This fixture does not implement status gameplay. */
    int window=1;assert(!dw4_dialogue_subwindow(d,subwindow,&window));
    dw4_script_source_set(dw4_scriptengine_vm(e),source,"assert(be:DMgetCount()==-1) [EOF]",NULL);
    assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"count-active.lua",NULL));
    command(&h,"sd","SUBWND",NULL,0,"REMOVE",NULL);assert(window==2);
    assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"count-closing.lua",NULL));
    window=0;dw4_script_source_set(dw4_scriptengine_vm(e),source,"assert(be:DMgetCount()==0) [EOF]",NULL);
    assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"count-closed.lua",NULL));
    for(unsigned cycle=0;cycle<32;cycle++) {
        dw4_dialogue_close(d);d=dw4_dialogue_open(h.sd,7,objects);assert(d);
        assert(!dw4_dialogue_claimed(d));
        command(&h,"sd","TEXTCTL",NULL,-1,"TEXTSET","TALKFONT02/font00/reloaded");
        command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/SET");
        assert(!dw4_dialogue_draw(d,640,448,&native_draw,&native_count) && native_count==16);
        command(&h,"sd","TEXTCTL",NULL,-1,"SWITCH","TALKFONT02/font00/CLR");
    }
    /* Teardown owns pending and installed trees; lifecycle failure must not
     * release Lua completion or allow another factory to overwrite the owner. */
    for(unsigned failure=0;failure<4;failure++) {
        sub=dw4_dialogue_subwindows(d);struct menu_fixture failed={.owner=sub};
        factory=(dw4_subwindow_factory){.prepare=menu_prepare,.begin=menu_begin,.end=menu_end,.user=&failed,.activate=menu_activate};
        assert(!dw4_subwindows_factory(sub,&factory));
        if(failure==3){
            failed.fail_activate=1;
            assert(dw4_scriptservices_call(h.sd,"sd",generate,5,&r,error,sizeof error)==-1);
            assert(strstr(error,"activation freeze failed") && failed.activates==1 && !failed.begins);
            assert(dw4_subwindows_tick(sub)==-1);
        }else command(&h,"sd","SUBWND",NULL,0,"GENERATE","STATUS/I<0>");
        if(failure==1) {
            failed.fail_begin=1;assert(dw4_subwindows_tick(sub)==-1);
            assert(strstr(dw4_subwindows_error(sub),"freeze failed"));
        } else if(failure==2) {
            assert(!dw4_subwindows_tick(sub));failed.fail_end=1;
            command(&h,"sd","SUBWND",NULL,0,"REMOVE",NULL);
            assert(!dw4_subwindows_tick(sub));assert(dw4_subwindows_tick(sub)==-1);
            assert(strstr(dw4_subwindows_error(sub),"restoration failed"));
        }
        assert(dw4_subwindows_at(sub,0).active && dw4_subwindows_factory(sub,NULL)==-1);
        dw4_script_source_set(dw4_scriptengine_vm(e),source,"assert(be:DMgetCount()==-1) [EOF]",NULL);
        assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"menu-failed-or-pending.lua",NULL));
        dw4_scriptservices_cancel(h.sd,7);dw4_dialogue_close(d);assert(failed.released==2);
        d=dw4_dialogue_open(h.sd,7,objects);assert(d);
    }
    assert(!dw4_scriptengine_reset_scene(e,h.sd));
    dw4_dialogue_close(d);dw4_controllers_close(controllers);dw4_stageobjects_close(objects);
    dw4_scriptengine_filelist(e,NULL);dw4_filelist_close(files);dw4_scriptengine_close(e);dw4_scriptservices_close(h.sd);dw4_mount_close(&m);
    puts("Dialogue: original 15-page and choice helper bytecode, real model completion, text ownership, independent pad slots and subwindow waits passed");return 0;
}
