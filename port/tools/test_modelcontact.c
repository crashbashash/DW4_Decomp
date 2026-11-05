/* Scoped hit context and original Central NPC entry; geometry is a fixture. */
#include "dw4/scriptengine.h"
#include "dw4/filelist.h"
#include "dw4/controllers.h"
#include "dw4/dialogue.h"
#include "dw4/hitbox.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
struct host {dw4_scriptengine *engine;dw4_scriptservices *sd;dw4_modelctrl *target;dw4_script_model *native_state;int cancel,checks,off;};
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static dw4_model_contact contact(float x,int shooter)
{
    dw4_model_contact c={.bullet_kind=60000,.bullet_box=4,.shoot_ram_no=shooter,.damage_turn=1};
    c.world[0]=c.world[5]=c.world[10]=c.world[15]=1;c.world[12]=x;c.world[13]=20;c.world[14]=30;return c;
}
static const char *outer="local before=be:MDLgetPosStr(0,0,0) assert(before=='V<10.000000,20.000000,30.000000>') assert(be:BLTgetShootRamNo()==2) assert(be:MDLgetBulletKind()==60000) assert(be:MDLgetBulletBoxNo()==4) assert(be:MDLgetRotStr(0,180,0)=='V<0.000000,180.000000,0.000000>') be:MDLsetDMGTurn(0) be:MDLaddHp(-3) be:sd('FIXTURE',nil,-1,'NEST') assert(be:BLTgetShootRamNo()==2 and be:MDLgetPosStr(0,0,0)==before) be:sd('FIXTURE',nil,-1,'CHECK') [EOF]";
static const char *inner="assert(be:BLTgetShootRamNo()==1) assert(be:MDLgetRamNo()==7) assert(be:MDLgetPosStr(0,0,0)=='V<40.000000,20.000000,30.000000>') be:MDLsetDMGTurn(2) be:MDLaddHp(5) [EOF]";
static const char *probe_script="assert(be:MDLisCallName('Hit')==1 and be:MDLgetBulletKind()==60000 and be:MDLgetBulletBoxNo()==0 and be:BLTgetShootRamNo()==2) g_hits=(g_hits or 0)+1 be:MDLaddHp(-3) be:sd('FIXTURE',nil,-1,'HP') be:MDLsetDMGTurn(g_turn) [EOF]";
static int source(void *u,const char *path,const void **bytes,size_t *n)
{(void)u;*bytes=strstr(path,"hit_probe")?probe_script:strstr(path,"inner")?inner:outer;*n=strlen(*bytes);return 0;}
static int bridge(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct host *h=user;
    if(!strcmp(method,"sd") && n==4 && !strcmp(a[0].string,"FIXTURE")) {
        if(!strcmp(a[3].string,"HP")){assert(h->native_state);h->native_state->hp=77;return 0;}
        if(!strcmp(a[3].string,"NEST")) {
            dw4_script_model m={.ram_no=7,.hp=9,.info_name="inner"};dw4_model_contact c=contact(40,1);
            assert(!dw4_scriptengine_contact_event(h->engine,43,"inner.lua",&m,&c));assert(m.hp==14 && !c.damage_turn);
        }else {h->checks++;if(h->cancel)dw4_scriptengine_remove_scope(h->engine,42);}
        return 0;
    }
    snprintf(error,cap,"unexpected fixture method: %s",method);(void)r;return -1;
}
static void hit_owner(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,824,&size,NULL);assert(blob);
    struct host h={0};dw4_be_state state;dw4_be_init(&state);
    h.engine=dw4_scriptengine_open(&state,bridge,&h);assert(h.engine);
    dw4_script_source_set(dw4_scriptengine_vm(h.engine),source,NULL,NULL);
    assert(!dw4_script_set(dw4_scriptengine_vm(h.engine),"g_turn",(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}));
    h.target=dw4_modelctrl_open(blob,size,"n_digilfm");assert(h.target);
    dw4_script_model model={.ram_no=0,.rec_no=-1,.hp=100,.max_hp=100,.info_name="probe"};h.native_state=&model;
    dw4_modelctrl_script(h.target,h.engine,42,&model);assert(!dw4_modelctrl_start(h.target,"SQ_WAIT02"));
    dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(h.target,&actor);float world[16];dw4_modelctrl_actor_matrix(&actor,world);
    const float *boxes;size_t count;assert(dw4_modelctrl_talk_boxes(h.target,&boxes,&count)==1 && count==1);
    dw4_model_talk_probe probe={.shoot_ram_no=2,.world_ns=1};memcpy(probe.source_world,world,sizeof world);probe.source_world[12]=10;
    dw4_hitbox_fixed_world(boxes,world,probe.box);
    assert(dw4_modelctrl_talk_hit(h.target,world,&probe)==1 && model.hp==77); /* Native HP wins over snapshot97. */
    dw4_modelctrl_actor_state(h.target,&actor);assert(actor.rotation[1]==0); /* DMGTurn0. */
    world[12]=1000;assert(dw4_modelctrl_talk_hit(h.target,world,&probe)==1); /* Same-frame cached body. */
    probe.world_ns++;assert(!dw4_modelctrl_talk_hit(h.target,world,&probe)); /* New timestamp reprojects. */
    world[12]=0;probe.world_ns++;
    assert(!dw4_script_set(dw4_scriptengine_vm(h.engine),"g_turn",(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0}));
    assert(dw4_modelctrl_talk_hit(h.target,world,&probe)==1);
    dw4_modelctrl_actor_state(h.target,&actor);assert(actor.rotation[1]>89.99f && actor.rotation[1]<90.01f);
    dw4_script_value hits;assert(!dw4_script_get(dw4_scriptengine_vm(h.engine),"g_hits",&hits) && hits.number==3);
    dw4_modelctrl_remove(h.target);assert(!dw4_modelctrl_talk_hit(h.target,world,&probe));
    dw4_modelctrl_close(h.target);dw4_scriptengine_close(h.engine);
    puts("talk hit owner: native HP precedence, same-frame geometry cache, next-frame reprojection, damage-turn switch and removed gating pass");
}
static void lifetime(void)
{
    dw4_be_state state;dw4_be_init(&state);struct host h={0};
    h.engine=dw4_scriptengine_open(&state,bridge,&h);assert(h.engine);
    dw4_script_source_set(dw4_scriptengine_vm(h.engine),source,NULL,NULL);
    dw4_script_model m={.ram_no=3,.hp=100,.info_name="outer"};dw4_model_contact c=contact(10,2),before=c;
    assert(!dw4_scriptengine_contact_event(h.engine,42,"outer.lua",&m,&c));assert(m.hp==97 && !c.damage_turn && h.checks==1);
    assert(!memcmp(c.world,before.world,sizeof c.world) && c.shoot_ram_no==2);
    h.cancel=1;m.hp=100;c=before;
    assert(dw4_scriptengine_contact_event(h.engine,42,"outer.lua",&m,&c)<0);
    assert(m.hp==100 && c.damage_turn==1 && h.checks==2);
    assert(strstr(dw4_scriptengine_error(h.engine),"scope unloaded"));
    dw4_scriptengine_close(h.engine);
    puts("contact context: original native API strings/scalars, nested model/shooter isolation and cancelled HP/turn commit pass");
}
static int leaf(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct host *h=user;(void)r;
    if(n==4 && !strcmp(a[0].string,"PLAYER") && !strcmp(a[3].string,"OFCTRL")){h->off++;return 0;}
    snprintf(error,cap,"unexpected original NPC world leaf %s",method);return -1;
}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct host *h=user;
    if(!strcmp(method,"SYSgetLightMode")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;}
    if(!strcmp(method,"SYSisJoinPlayer")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,a[0].number==0,NULL,0};return 0;}
    if(!strcmp(method,"SYSgetPlayerName")){*r=str("m_dorumon");return 0;}
    if(!strcmp(method,"SYSgetWeaponName")){*r=str("w_axe01");return 0;}
    dw4_scriptservices_scope(h->sd,dw4_scriptengine_scope(h->engine));
    return dw4_scriptservices_call(h->sd,method,a,n,r,error,cap);
}
static int target_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{struct host *h=user;return dw4_modelctrl_service(h->target,method,a,n,r,error,cap);}
static void original(dw4_mount *mount)
{
    struct host h={.sd=dw4_scriptservices_open()};dw4_be_state state;dw4_be_init(&state);
    h.engine=dw4_scriptengine_open(&state,binding,&h);dw4_filelist *files=dw4_filelist_open(mount);assert(h.sd && h.engine && files);
    dw4_scriptengine_filelist(h.engine,files);assert(!dw4_filelist_begin(files,h.engine,"stagML12",7) && !dw4_filelist_shared(files));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(files,dw4_stageobjects_route,objects) && !dw4_filelist_bind_layers(files,dw4_stageobjects_bind_layers,objects));
    assert(!dw4_stageobjects_publish(objects,h.sd,7));
    const char *exclude[]={"n_digilfm"};
    dw4_controllers *models=dw4_controllers_open(h.sd,7,objects,exclude,1,&state.random,&state.action_rhythm,h.engine);assert(models);
    const dw4_stageobject *info=dw4_stageobjects_find(objects,"beModelCtrlInfo","n_digilfm",0);assert(info);
    h.target=dw4_modelctrl_open_info((info)->igb,info->id);assert(h.target);
    dw4_script_model m={.ram_no=0,.rec_no=-1,.hp=100,.max_hp=100,.info_name="n_digilfm"};
    dw4_modelctrl_script(h.target,h.engine,7,&m);
    assert(dw4_scriptservices_register(h.sd,7,"MODELCTRL","n_digilfm",0,1,target_service,&h));
    dw4_dialogue *dialogue=dw4_dialogue_open(h.sd,7,objects);assert(dialogue);
    assert(dw4_scriptservices_register(h.sd,7,"PLAYER",NULL,-1,1,leaf,&h));assert(!dw4_scriptservices_category(h.sd,"ENEMY"));
    dw4_script_value args[]={str("MODELCTRL"),str("n_digilfm"),{DW4_SCRIPT_NUMBER,0,NULL,0},str("GENERATE")},r;char error[256];
    assert(!dw4_scriptservices_call(h.sd,"sd",args,4,&r,error,sizeof error));
    dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(h.target,&actor);float world[16];dw4_modelctrl_actor_matrix(&actor,world);
    const float *boxes;size_t count;assert(dw4_modelctrl_talk_boxes(h.target,&boxes,&count)==1 && count==1);
    for(unsigned k=0;k<3;k++)assert(boxes[k]<boxes[k+3]);
    dw4_model_talk_probe probe={.shoot_ram_no=2,.world_ns=100};memcpy(probe.source_world,world,sizeof world);
    dw4_hitbox_fixed_world(boxes,world,probe.box);
    /* An actual geometry miss and disabled target must not execute a script. */
    dw4_model_talk_probe miss=probe;for(unsigned k=0;k<6;k++)miss.box[k]+=10000;
    assert(!dw4_modelctrl_talk_hit(h.target,world,&miss) && !h.off && !dw4_scriptengine_pending(h.engine));
    args[3]=str("OFCTRL");assert(!dw4_scriptservices_call(h.sd,"sd",args,4,&r,error,sizeof error));
    assert(!dw4_modelctrl_talk_hit(h.target,world,&probe) && !h.off);
    args[3]=str("ONCTRL");assert(!dw4_scriptservices_call(h.sd,"sd",args,4,&r,error,sizeof error));
    int rc=dw4_modelctrl_talk_hit(h.target,world,&probe);
    if(rc!=1)fprintf(stderr,"original hit callback: %s\n",dw4_modelctrl_error(h.target));
    assert(rc==1 && h.off==1 && dw4_scriptengine_pending(h.engine));
    assert(!dw4_script_get(dw4_scriptengine_vm(h.engine),"g_messPlayerNo",&r) && r.type==DW4_SCRIPT_NUMBER && r.number==2);
    assert(!dw4_script_get(dw4_scriptengine_vm(h.engine),"g_npcRamNo",&r) && r.type==DW4_SCRIPT_NUMBER && r.number==0);
    assert(!strcmp(dw4_modelctrl_sequence(h.target),"SQ_TALK"));
    dw4_modelctrl_actor_state(h.target,&actor);assert(actor.muteki==0x42f00000);
    assert(!dw4_modelctrl_talk_hit(h.target,world,&probe) && h.off==1); /* Talk invulnerability. */
    assert(!dw4_scriptengine_remove_all(h.engine,h.sd));dw4_dialogue_close(dialogue);dw4_controllers_close(models);dw4_stageobjects_close(objects);
    dw4_modelctrl_close(h.target);
    dw4_scriptengine_close(h.engine);dw4_filelist_close(files);dw4_scriptservices_close(h.sd);
    puts("original Central NPC Hit: authored geometry miss/control/muteki gates, native talk sequence/layers, shooter/RAM capture and queued dialogue pass; probe input/player control are fixture leaves");
}
static void registry(dw4_mount *mount)
{
    struct host h={.sd=dw4_scriptservices_open()};dw4_be_state state;dw4_be_init(&state);
    h.engine=dw4_scriptengine_open(&state,binding,&h);dw4_filelist *files=dw4_filelist_open(mount);assert(h.sd && h.engine && files);
    dw4_scriptengine_filelist(h.engine,files);assert(!dw4_filelist_begin(files,h.engine,"stagML12",7) && !dw4_filelist_shared(files));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(files,dw4_stageobjects_route,objects) && !dw4_filelist_bind_layers(files,dw4_stageobjects_bind_layers,objects));
    assert(!dw4_stageobjects_publish(objects,h.sd,7));
    const char *exclude[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky"};
    dw4_controllers *models=dw4_controllers_open(h.sd,7,objects,exclude,5,&state.random,&state.action_rhythm,h.engine);assert(models);
    dw4_dialogue *dialogue=dw4_dialogue_open(h.sd,7,objects);assert(dialogue);
    assert(dw4_scriptservices_register(h.sd,7,"PLAYER",NULL,-1,1,leaf,&h));assert(!dw4_scriptservices_category(h.sd,"ENEMY"));
    /* Registration happens with the accepted prepared rows, before any Work is generated. */
    size_t talkers=dw4_controllers_talk_count(models);assert(talkers>0);
    size_t npc=SIZE_MAX;
    for(size_t i=0;i<dw4_controllers_count(models);i++) {
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&slot);
        const float *b;size_t nb;
        if(!strcmp(dw4_stageobject_name(info),"n_digilfm") && !slot && dw4_modelctrl_talk_boxes(m,&b,&nb)==1)npc=i;
    }
    assert(npc!=SIZE_MAX);
    const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *m=dw4_controllers_model(models,npc,&info,&slot);
    const float *boxes;size_t count;assert(dw4_modelctrl_talk_boxes(m,&boxes,&count)==1);
    float world[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    dw4_model_talk_probe probe={.shoot_ram_no=0,.world_ns=1};memcpy(probe.source_world,world,sizeof world);
    /* Ungenerated Work is registered but ineligible. */
    dw4_hitbox_fixed_world(boxes,world,probe.box);
    assert(dw4_controllers_talk(models,&probe)==0 && !h.off);
    dw4_script_value args[]={str("MODELCTRL"),str("n_digilfm"),{DW4_SCRIPT_NUMBER,0,NULL,0},str("GENERATE")},r;char error[256];
    assert(!dw4_scriptservices_call(h.sd,"sd",args,4,&r,error,sizeof error));
    dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(m,&actor);dw4_modelctrl_actor_matrix(&actor,world);
    memcpy(probe.source_world,world,sizeof world);dw4_hitbox_fixed_world(boxes,world,probe.box);probe.world_ns=2;
    dw4_model_talk_probe miss=probe;miss.world_ns=3;for(unsigned k=0;k<6;k++)miss.box[k]+=10000;
    assert(dw4_controllers_talk(models,&miss)==0 && !h.off); /* every receiver tests its own boxes */
    probe.world_ns=4;
    int hits=dw4_controllers_talk(models,&probe);
    if(hits<0)fprintf(stderr,"registry talk: %s\n",dw4_controllers_error(models));
    assert(hits==1 && h.off==1 && !strcmp(dw4_modelctrl_sequence(m),"SQ_TALK"));
    assert(!dw4_script_get(dw4_scriptengine_vm(h.engine),"g_messPlayerNo",&r) && r.number==0);
    assert(!dw4_scriptengine_remove_all(h.engine,h.sd));dw4_dialogue_close(dialogue);dw4_controllers_close(models);
    dw4_stageobjects_close(objects);dw4_scriptengine_close(h.engine);dw4_filelist_close(files);dw4_scriptservices_close(h.sd);
    puts("talk registry: accepted-row registration, ungenerated Work ineligible, per-receiver authored geometry dispatch and original Hit pass");
}
int main(int argc,char **argv)
{
    lifetime();dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    original(&mount);registry(&mount);hit_owner(&mount);dw4_mount_close(&mount);return 0;
}
