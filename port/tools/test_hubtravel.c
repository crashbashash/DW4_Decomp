/* Headless original-bytecode route/choice integration. No replacement Lua.
 * World movement/audio are explicit leaves; scene publication is not claimed. */
#include "dw4/filelist.h"
#include "dw4/controllers.h"
#include "dw4/dialogue.h"
#include "dw4/stagetravel.h"
#include "dw4/materialcontact.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
struct host {dw4_scriptservices *sd;int preparing;unsigned off,on;dw4_material_contact contact;};
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int leaf(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    (void)method;(void)r;struct host *h=user;
    if(n==4 && !strcmp(a[0].string,"PLAYER")) {
        if(!strcmp(a[3].string,"OFCTRL")){h->off++;return 0;}
        if(!strcmp(a[3].string,"ONCTRL")){h->on++;return 0;}
        /* mate01 sets no g_StChangeKind, so funcStageChange takes its non-"trans" arm: the player waits in SQ_DEMOWAIT, then SQ_EXIT. */
        if(!strcmp(a[3].string,"SQ_DEMOWAIT") || !strcmp(a[3].string,"SQ_EXIT"))return 0;
    }
    if(n==5 && !strcmp(a[0].string,"SOUND"))return 0;
    snprintf(error,cap,"unexpected route world leaf %s n=%zu %s",a[0].string?a[0].string:"",n,n>3 && a[3].string?a[3].string:"");return -1;
}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    struct host *h=user;*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    int contact=dw4_material_contact_call(&h->contact,method,a,n,r,error,cap);
    if(contact<=0)return contact;
    if(!strcmp(method,"SYSgetLightMode"))r->number=1;
    else if(!strcmp(method,"SYSisJoinPlayer"))r->number=n==1 && a[0].number==0;
    else if(!strcmp(method,"SYSgetPlayerName"))*r=str("m_dorumon");
    else if(!strcmp(method,"SYSgetWeaponName"))*r=str("w_axe01");
    else if(!strcmp(method,"SYSctlPlayer")) {
        if(n!=4 || strcmp(a[0].string,"HP") || strcmp(a[1].string,"GETHP"))return -1;
        r->number=100;
    } else if(!h->preparing)return dw4_scriptservices_call(h->sd,method,a,n,r,error,cap);
    else {snprintf(error,cap,"unexpected asset-selection query: %s",method);return -1;}
    return 0;
}
static void tick(struct host *h,dw4_scriptengine *e,dw4_controllers *c,dw4_dialogue *d,unsigned frame)
{
    int64_t ns=(int64_t)frame*1000000000/60;
    dw4_controllers_sample(c,ns);
    int rc=dw4_scriptservices_tick(h->sd,ns) || dw4_scriptengine_tick(e) ||
        dw4_controllers_tick(c,ns) || dw4_dialogue_tick(d);
    if(rc)fprintf(stderr,"tick %u: %s / %s / %s / %s\n",frame,
        dw4_scriptengine_error(e),dw4_scriptservices_error(h->sd),dw4_controllers_error(c),dw4_dialogue_error(d));
    assert(!rc);
}
static void route(dw4_mount *mount,const char *stage,const char *event,const char *destination,int point,int cancel)
{
    struct host h={.sd=dw4_scriptservices_open(),.preparing=1};assert(h.sd);
    dw4_be_state state;dw4_be_init(&state);state.flag[424]=0; /* the Commander Room gate is open while flag 424 is clear */
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&h);assert(e);
    dw4_filelist *f=dw4_filelist_open(mount);assert(f);dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,stage,7));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *o=dw4_stageobjects_open();assert(o);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,o));
    assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,o));
    assert(!dw4_stageobjects_publish(o,h.sd,7));
    dw4_controllers *c=dw4_controllers_open(h.sd,7,o,NULL,0,&state.random,&state.action_rhythm,NULL);assert(c);
    dw4_dialogue *d=dw4_dialogue_open(h.sd,7,o);assert(d);
    dw4_stageinput input={0};dw4_stagetravel travel={.input=&input};
    const char *cats[]={"PLAYER","SOUND"};
    for(unsigned i=0;i<2;i++)assert(dw4_scriptservices_register(h.sd,7,cats[i],NULL,-1,1,leaf,&h));
    assert(dw4_scriptservices_register(h.sd,7,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,&travel));
    assert(dw4_scriptservices_register(h.sd,7,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,&travel));
    assert(!dw4_scriptservices_category(h.sd,"ENEMY"));assert(!dw4_scriptservices_category(h.sd,"PLAYER2"));
    h.preparing=0;
    static const uint8_t exists[4]={1,0,0,0};
    dw4_material_contact_begin(&h.contact,0,0,0,exists);
    /* Original material script must reject incomplete player membership. */
    assert(!dw4_scriptengine_run(e,event));assert(!h.off && !dw4_scriptengine_pending(e));
    dw4_material_contact_begin(&h.contact,0,1,0,exists);assert(!dw4_scriptengine_run(e,event));assert(h.off==1);h.contact.active=0;
    for(unsigned frame=0;frame<80;frame++){
        if(cancel==2 && frame==65)dw4_dialogue_input(d,0,4,0,0);
        tick(&h,e,c,d,frame);
    }
    assert(!travel.pending && !input.disabled);
    int visible=0;
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++) {
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        visible+=t->visible && !strcmp(t->group,"STCHGFONT00") && t->count>0;
    }
    assert(visible); /* Real original confirmation, not a captured success result. */
    dw4_dialogue_input(d,0,0,0,cancel==1?0x2000:0x4000);
    for(unsigned frame=80;frame<500;frame++)tick(&h,e,c,d,frame);
    assert(!dw4_scriptengine_pending(e) && !dw4_scriptservices_pending(h.sd));
    char next[128];int32_t spawn=-1;
    assert(dw4_stagetravel_pending(&travel,next,sizeof next,&spawn)==!cancel);
    if(cancel)assert(!h.on && !input.disabled && travel.generate_pos==0);
    else {
        if(strcmp(next,destination) || spawn!=point || !input.disabled || h.on)fprintf(stderr,"route actual %s point %d disabled %d on %u; expected %s point %d\n",next,spawn,input.disabled,h.on,destination,point);
        assert(!strcmp(next,destination) && spawn==point && input.disabled && !h.on);
        assert(dw4_stagetravel_pending(&travel,next,1,&spawn)==-1 && travel.pending);
        dw4_stagetravel_ack(&travel);assert(!travel.pending && travel.generate_pos==point);
    }
    printf("hub route: %s/%s -> %s point %d (%s)\n",stage,event,destination,point,cancel==2?"decline":cancel?"cancel":"accept");
    assert(!dw4_scriptengine_remove_all(e,h.sd));
    dw4_dialogue_close(d);dw4_controllers_close(c);dw4_stageobjects_close(o);
    dw4_scriptengine_close(e);dw4_filelist_close(f);dw4_scriptservices_close(h.sd);
}
static void request_lifetime(void)
{
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    dw4_stageinput input={0};dw4_stagetravel travel={.input=&input};
    assert(dw4_scriptservices_register(sd,12,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,&travel));
    assert(dw4_scriptservices_register(sd,12,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,&travel));
    dw4_scriptservices_scope(sd,12);
    char destination[]="stagML12";dw4_script_value result;char error[128];
    dw4_script_value point[]={str("PLAYERPOINT"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},str("SETGENERATEPOS"),str("I<3>"),{DW4_SCRIPT_NUMBER,90,NULL,0}};
    dw4_script_value args[]={str("STAGECTL"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},str("NEXTSTAGE"),str(destination),{DW4_SCRIPT_NUMBER,90,NULL,0}};
    assert(!dw4_scriptservices_call(sd,"sd",point,6,&result,error,sizeof error));
    assert(!dw4_scriptservices_call(sd,"sd",args,6,&result,error,sizeof error));
    memset(destination,'X',8); /* SD owns the delayed copy. */
    assert(!dw4_scriptservices_tick(sd,89ULL*1000000000/60) && !travel.pending && !travel.generate_pos);
    assert(!dw4_scriptservices_tick(sd,90ULL*1000000000/60));
    char next[128];int32_t spawn;
    assert(dw4_stagetravel_pending(&travel,next,sizeof next,&spawn)==1 && !strcmp(next,"stagML12") && spawn==3);
    dw4_stagetravel_ack(&travel);
    args[4]=str("stagML13");
    assert(!dw4_scriptservices_call(sd,"sd",args,6,&result,error,sizeof error));
    dw4_scriptservices_remove_scope(sd,12);
    assert(!dw4_scriptservices_tick(sd,1000ULL*1000000000/60) && !travel.pending);
    /* Malformed host input cannot replace a retained request or spawn. */
    args[4]=str("stagML11");
    assert(!dw4_stagetravel_service(&travel,"sd",args,5,&result,error,sizeof error));
    char invalid[]={'a',0,'b'};args[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,invalid,sizeof invalid};
    assert(dw4_stagetravel_service(&travel,"sd",args,5,&result,error,sizeof error)==-1);
    assert(dw4_stagetravel_pending(&travel,next,sizeof next,&spawn)==1 && !strcmp(next,"stagML11") && spawn==3);
    dw4_scriptservices_close(sd);
    puts("hub requests: copied delayed values, same-deadline spawn order, snapshot/retry retention and unload cancellation pass");
}
int main(int argc,char **argv)
{
    request_lifetime();
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../local/extracted"));
    static const struct {const char *from,*event,*to;int point;} rows[]={
        {"stagML11","matz00.lua","StagML12",0},
        {"stagML11","matz01.lua","StagML13",0},
        {"stagML12","matz00.lua","StagML11",1},
        {"stagML12","matz01.lua","StagML13",1},
        {"stagML13","matz01.lua","StagML12",1},
        {"stagML13","matz00.lua","StagML11",2},
        /* The gate pads with a fixed destination (flag 424 clear for the Commander Room); check-hubgates covers them in the
         * prepared runtime with their labels and flag guards. */
        {"stagML11","mate01.lua","stagML02",0},
        {"stagML12","mate00.lua","stagML13",2},
        {"stagML13","mate00.lua","stagML12",5},
    };
    for(unsigned i=0;i<sizeof rows/sizeof *rows;i++)for(int cancel=0;cancel<3;cancel++)
        route(&m,rows[i].from,rows[i].event,rows[i].to,rows[i].point,cancel);
    dw4_mount_close(&m);puts("hub travel: original route scripts, native choice/models/fonts, accept/cancel and deferred requests pass");return 0;
}
