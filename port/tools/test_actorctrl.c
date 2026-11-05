#include "dw4/modelctrl.h"
#include "dw4/modelsubcom.h"
#include "dw4/reflected.h"
#include "../src/arenalist.h"
#include "dw4/mount.h"
#include "dw4/scriptengine.h"
#include "dw4/scriptservices.h"
#include "dw4/actoranim.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
static void trace(void *user,const char *seq,const char *type,const char *name,int64_t ns) {
    printf("TRACE %s %lld %s %s %s\n",(char *)user,(long long)ns,seq,type,name);
}
static dw4_script_value str(const char *s) {return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int command(dw4_modelctrl *m,const char *key,const char *value) {
    dw4_script_value a[]={str("MODELCTRL"),str("n_digilff"),{DW4_SCRIPT_NUMBER,0,NULL,0},str(key),value?str(value):(dw4_script_value){0}},r;
    char error[256];return dw4_modelctrl_service(m,"sd",a,value?5:4,&r,error,sizeof error);
}
static double query(dw4_modelctrl *m,const char *key,const char *value) {
    dw4_script_value a[]={str("MODELCTRL"),str("n_digilff"),{DW4_SCRIPT_NUMBER,0,NULL,0},str(key),value?str(value):(dw4_script_value){0}},r;
    char error[256];assert(!dw4_modelctrl_service(m,"querySD",a,value?5:4,&r,error,sizeof error));
    assert(r.type==DW4_SCRIPT_NUMBER);return r.number;
}
static void arrival(dw4_mount *mount,const char *name,const char *sequence,int emit) {
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);assert(blob);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,name);assert(m);
    dw4_modelctrl *other=dw4_modelctrl_instance(m);assert(other);
    dw4_modelctrl_sample(m,0);
    if(emit)dw4_modelctrl_observe(m,trace,(void *)name);
    assert(!dw4_modelctrl_start(m,sequence));
    dw4_modelctrl_record records=dw4_modelctrl_records(m);
    const beModelCtrlInfoWork *work=DW4_ARENA_OBJ(records.arena,beModelCtrlInfoWork,records.work);
    const beModelCtrlData *data=DW4_ARENA_OBJ(records.arena,beModelCtrlData,al_handle(work->_comData));
    assert(data && !strcmp(al_text(records.arena,data->_name),dw4_modelctrl_sequence(m)) && al_count(records.arena,data->_comList)>0);
    assert(!command(m,"MOVETRANS","V<10,40,-5>/V<0,0,0>"));
    assert(!command(m,"OFCTRL",NULL));
    dw4_modelctrl_actor a={0},b={0};dw4_modelctrl_actor_state(m,&a);
    assert(a.position[0]==10 && a.position[1]==40 && a.position[2]==-5);
    assert(command(m,"MOVETRANS","V<nan,0,0>/V<0,0,0>")==-1);
    dw4_modelctrl_actor_state(m,&a);assert(a.position[0]==10);
    for(int i=1;i<=180;i++) {
        int64_t ns=(int64_t)i*1000000000/60;
        assert(!dw4_modelctrl_tick(m,ns));
        dw4_modelctrl_actor_state(m,&a);
        assert(isfinite(a.position[0]) && isfinite(a.rotation[1]));
        if(emit) {
            printf("QUERY %s %lld %.0f %.0f %.0f\n",name,(long long)ns,
                query(m,"ISRUN",NULL),query(m,"ISSEQNAME",sequence),query(m,"ISSEQNAME","SQ_MISSING"));
            printf("STATE %s %lld ",name,(long long)ns);
            const unsigned char *bytes=(const unsigned char *)a.channel;
            for(size_t j=0;j<sizeof a.channel;j++)printf("%02x",bytes[j]);
            putchar('\n');
        }
        if(i==1)assert(a.channel[2].speed==0); /* turn before walking */
        if(i==25)assert(a.motion && !strcmp(a.motion,"walk01") && a.channel[2].speed!=0);
    }
    assert(!dw4_modelctrl_active(other));
    assert(!command(other,"SQ_WALK02",NULL));assert(!dw4_modelctrl_active(other));
    assert(query(other,"ISRUN",NULL)==0 && query(other,"ISSEQNAME","SQ_WALK02")==0);
    dw4_modelctrl_actor_state(other,&b);assert(!b.motion && !b.channel[3].active);
    assert(a.position[0]!=10 || a.position[2]!=-5);
    if(!strcmp(name,"n_digilff"))assert(!strcmp(dw4_modelctrl_sequence(m),"SQ_TALK") && !strcmp(a.motion,"talk01"));
    else assert(!strcmp(dw4_modelctrl_sequence(m),"SQ_WALK03") && !strcmp(a.motion,"walk01"));
    int64_t ns=a.motion_ns;
    for(int i=0;i<5;i++){dw4_modelctrl_actor_state(m,&a);assert(a.motion_ns==ns);}
    assert(!command(m,"ONCTRL",NULL));dw4_modelctrl_actor_state(m,&a);assert(a.enabled);
    assert(!command(m,"MOVETRANS","V<240,40,-150>/V<0,180,0>"));
    dw4_modelctrl_actor_state(m,&a);assert(a.position[0]==240 && a.rotation[1]==180);
    /* MOVETRANS sets a transform; retail does not erase retained MOVE state. */
    if(!strcmp(name,"n_digilfm"))assert(a.channel[2].speed!=0);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
    for(int i=181;i<200;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*1000000000/60));
    dw4_modelctrl_actor_state(m,&a);assert(a.channel[2].speed==0 && !strcmp(a.motion,"wait01"));
    assert(dw4_modelctrl_start(m,"SQ_FALL")==-1);assert(!strcmp(dw4_modelctrl_sequence(m),"SQ_WAIT02"));
    dw4_modelctrl_close(m);
    assert(!dw4_modelctrl_start(other,"SQ_WAIT02"));dw4_modelctrl_close(other);
}
static void control_test(dw4_mount *mount,int emit) {
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
    if(emit)dw4_modelctrl_observe(m,trace,"control");
    const char *sequences[]={"SQ_WAIT","SQ_TALK","SQ_WAIT02"};
    for(unsigned i=0;i<3;i++) {
        dw4_modelctrl_sample(m,(int64_t)i*1000000000);
        assert(!dw4_modelctrl_start(m,sequences[i]));dw4_modelctrl_actor a;dw4_modelctrl_actor_state(m,&a);
        if(emit)printf("CONTROL %u %d %08x\n",i,a.control,a.muteki);
        if(i==0)assert(a.control==4 && a.motion && !strcmp(a.motion,"wait01"));
        if(i==1)assert(a.control==0 && a.muteki==0x42f00000 && a.motion && !strcmp(a.motion,"talk01"));
        assert(a.wall_check && a.floor_check);
    }
    dw4_modelctrl_close(m);
}
static void transform_test(dw4_mount *mount,int emit) {
    static const char *values[]={"V<60,10,-10>/V<0,117,0>","V<63.12,10,-55.8>/V<0,78.8,0>",
        "V<69.11,10,-13.79>/V<0,-90,0>","V<240,40,-150>/V<0,0,0>","V<258.187,40,174>/V<0,180,0>"};
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
    for(int active=0;active<=1;active++) {
        if(active)assert(!dw4_modelctrl_start(m,"SQ_WALK"));
        for(unsigned i=0;i<sizeof values/sizeof *values;i++) {
            assert(!command(m,"MOVETRANS",values[i]));dw4_modelctrl_actor a;dw4_modelctrl_actor_state(m,&a);
            if(emit){
                printf("TRANS %d %u ",active,i);
                for(unsigned j=0;j<3;j++){uint32_t v;memcpy(&v,a.position+j,4);printf("%08x ",v);}
                for(unsigned j=0;j<3;j++){uint32_t v;memcpy(&v,a.rotation+j,4);printf("%08x ",v);}
                putchar('\n');
            }
            if(!active)assert(a.position[0]==0 && a.rotation[1]==0);
            else assert(a.channel[2].active && a.motion && !strcmp(a.motion,"walk01"));
        }
    }
    dw4_modelctrl_close(m);
}
static void muteki_test(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);assert(blob);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
    dw4_modelctrl_sample(m,0);assert(!dw4_modelctrl_start(m,"SQ_TALK"));
    dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(m,&actor);assert(actor.muteki==0x42f00000);
    for(int i=0;i<4;i++)assert(!dw4_modelctrl_tick(m,0));
    dw4_modelctrl_actor_state(m,&actor);assert(actor.muteki==0x42f00000);
    assert(!dw4_modelctrl_tick(m,1000000000));dw4_modelctrl_actor_state(m,&actor);
    assert(actor.muteki==0x42ea0000); /* 117: Frame clamps a long gap to three. */
    assert(!command(m,"ONFREEZE",NULL));
    for(int i=1;i<=120;i++)assert(!dw4_modelctrl_tick(m,1000000000LL+(int64_t)i*1000000000/60));
    dw4_modelctrl_actor_state(m,&actor);assert(actor.muteki==0x42ea0000);
    assert(!command(m,"OFFREEZE",NULL));
    assert(!command(m,"SQ_WAIT02",NULL)); /* Changing sequence retains the count. */
    dw4_modelctrl_actor_state(m,&actor);assert(actor.muteki==0x42ea0000);
    for(int i=1;i<=125;i++)assert(!dw4_modelctrl_tick(m,3000000000LL+(int64_t)i*1000000000/60));
    dw4_modelctrl_actor_state(m,&actor);assert(!actor.muteki);
    assert(!dw4_modelctrl_start(m,"SQ_TALK"));dw4_modelctrl_remove(m);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));dw4_modelctrl_actor_state(m,&actor);assert(!actor.muteki);
    /* SQ_SILENT's permanent -1 ends when a name-based sequence set selects another sequence
     * (396a80 398358: negative MUTEKI becomes zero); SQ_TALK's positive count still persists. */
    assert(!dw4_modelctrl_start(m,"SQ_SILENT"));dw4_modelctrl_actor_state(m,&actor);assert(actor.muteki==0xbf800000);
    for(int i=1;i<=3;i++)assert(!dw4_modelctrl_tick(m,5000000000LL+(int64_t)i*1000000000/60));
    dw4_modelctrl_actor_state(m,&actor);assert(actor.muteki==0xbf800000); /* permanent while silent */
    assert(!command(m,"SQ_WAIT02",NULL));dw4_modelctrl_actor_state(m,&actor);assert(!actor.muteki);
    dw4_modelctrl_close(m);
    puts("Actor MUTEKI: talk count expires, repeated/frozen ticks hold, sequence changes retain positive counts, clear negative ones and removal clears");
}
static int lua_source(void *user,const char *name,const void **bytes,size_t *size) {
    (void)user;(void)name;
    static const char source[]=
        "be:DMsetSD('MODELCTRL','n_digilff',2,'GENERATE','SQ_WAIT02') "
        "be:DMsetSD('MODELCTRL','n_digilff',2,'MOVETRANS','V<60,10,-10>/V<0,117,0>',5) "
        "be:DMsetSD('MODELCTRL','n_digilff',2,'SQ_WALK02',20) "
        "be:DMchkSD('MODELCTRL','n_digilff',2,'ISSEQNAME','SQ_WALK02','==0') "
        "be:DMchkSD('MODELCTRL','n_digilff',2,'ISSEQNAME','SQ_WALK02','!=0') "
        "be:DMsetSD('MODELCTRL','n_digilff',2,'OFCTRL') be:DMrun() [EOF]";
    *bytes=source;*size=sizeof source-1;return 0;
}
static void lua_test(dw4_mount *mount) {
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    uint64_t token=dw4_scriptservices_register(sd,11,"MODELCTRL","n_digilff",2,0,dw4_modelctrl_service,m);assert(token);
    dw4_be_state state;dw4_be_init(&state);
    dw4_scriptengine *e=dw4_scriptengine_open(&state,dw4_scriptservices_call,sd);assert(e);
    dw4_script_source_set(dw4_scriptengine_vm(e),lua_source,NULL,NULL);
    assert(!dw4_script_run_named(dw4_scriptengine_vm(e),"actor-dm.lua",NULL));
    assert(dw4_scriptengine_pending(e)==1);
    for(int i=1;i<140;i++) {
        int64_t ns=(int64_t)i*1000000000/60;dw4_modelctrl_sample(m,ns);
        assert(!dw4_scriptservices_tick(sd,(uint64_t)ns));assert(!dw4_scriptengine_tick(e));
        assert(!dw4_modelctrl_tick(m,ns));dw4_scriptservices_active(sd,token,dw4_modelctrl_active(m));
        if(i==10){
            dw4_modelctrl_actor a,b;dw4_modelctrl_actor_state(m,&a);
            assert(a.position[0]==60 && a.position[2]==-10 && a.rotation[1]==117);
            for(int hold=0;hold<10;hold++)dw4_modelctrl_actor_state(m,&b);
            assert(!memcmp(&a,&b,sizeof a));assert(dw4_scriptengine_pending(e)==1);
        }
        if(i==25)assert(!strcmp(dw4_modelctrl_sequence(m),"SQ_WALK02"));
    }
    assert(!dw4_scriptengine_pending(e));assert(!dw4_scriptservices_pending(sd));
    assert(!strcmp(dw4_modelctrl_sequence(m),"SQ_TALK"));
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(m,&a);assert(!a.enabled && !strcmp(a.motion,"talk01"));
    dw4_scriptengine_close(e);dw4_scriptservices_remove_scope(sd,11);dw4_modelctrl_close(m);dw4_scriptservices_close(sd);
    puts("Actor Lua/SD/DM: delayed transforms, numeric sequence waits and held snapshots passed");
}
static int callback_mode;
static dw4_modelctrl *callback_owner;
static dw4_script_model *callback_model;
static dw4_scriptengine *callback_engine;
static int callback_source(void *user,const char *name,const void **bytes,size_t *size) {
    (void)user;(void)name;
    static const char *sources[]={
        "be:MDLaddHp(1) be:MDLsetSeq('SQ_WAIT02') [EOF]",
        "be:MDLaddHp(1) be:MDLsetSD('REMOVE') [EOF]",
        "be:MDLaddHp(1) be:SYSctlFlagFolder('CLR') [EOF]",
        "be:MDLaddHp(1) be:DMsetSD('MODELCTRL','n_digilff',2,'SQ_WAIT02') be:DMrun() [EOF]"};
    *bytes=sources[callback_mode];*size=strlen(*bytes);return 0;
}
static int callback_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    (void)user;
    if(!strcmp(method,"SYSctlFlagFolder")) {
        if(callback_mode==2)dw4_scriptengine_remove_scope(callback_engine,17);
        return 0;
    }
    if(!strcmp(method,"sd")) {
        callback_model->hp=99; /* native mutation wins over cached callback HP */
        return dw4_modelctrl_service(callback_owner,method,a,n,r,error,cap);
    }
    return -1;
}
static void aim_test(dw4_mount *mount,int emit) {
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
    dw4_modelctrl *other=dw4_modelctrl_instance(m);assert(other);
    dw4_modelctrl_aim aim;dw4_modelctrl_aim_state(m,&aim);assert(aim.index==-1 && !aim.name);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
    assert(dw4_modelctrl_start(m,"SQ_WALKON")==-1); /* unbound callback fails preflight */
    assert(!strcmp(dw4_modelctrl_sequence(m),"SQ_WAIT02"));
    dw4_be_state state;dw4_be_init(&state);dw4_random expected=state.random;
    dw4_scriptengine *e=dw4_scriptengine_open(&state,NULL,NULL);assert(e);
    dw4_igb pack={0};assert(!dw4_igb_open(&pack,blob,size,0));
    assert(dw4_script_load_pack_named_scoped(dw4_scriptengine_vm(e),17,&pack,"aim_n_digilff.lua")==1);
    dw4_igb_close(&pack);
    dw4_script_model model={.ram_no=2,.hp=100,.max_hp=100,.info_name="n_digilff"};
    dw4_modelctrl_script(m,e,17,&model);
    for(unsigned i=0;i<128;i++) {
        int hp=model.hp;hp=hp==100?1:hp;
        hp=hp==1?2:hp==3?2:hp+(dw4_random_mod(&expected,2)==0?1:-1);
        assert(!dw4_modelctrl_start(m,"SQ_WALKON"));
        assert(model.hp==hp);dw4_modelctrl_aim_state(m,&aim);
        assert(aim.index==1 && !strcmp(aim.name,"MAP01"));
        assert(aim.target[0]==(hp==1?130:hp==2?20:60) && aim.target[1]==10 && aim.target[2]==(hp==3?-10:-35));
        assert(!memcmp(&expected,&state.random,sizeof expected));
        if(emit)printf("AIM %u %d %d %.0f %.0f %.0f %08x %08x %08x %08x\n",
            i,model.hp,aim.index,aim.target[0],aim.target[1],aim.target[2],
            aim.bounds[0],aim.bounds[1],aim.bounds[2],aim.rot_limit);
        dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(m,&actor);
        assert(actor.control==2 && !strcmp(actor.motion,"wait01"));
        dw4_modelctrl_aim_state(other,&aim);assert(aim.index==-1);
        assert(dw4_random_next(&expected)==dw4_random_next(&state.random));
    }
    /* Repeated snapshots cannot acquire targets or consume RNG. */
    dw4_random held=state.random;
    for(unsigned i=0;i<10;i++)dw4_modelctrl_aim_state(m,&aim);
    assert(!memcmp(&held,&state.random,sizeof held));
    /* A single-choice distant zone still draws once; ISSEQNAME and snapshots
     * never draw. Exactly-at-duration does not expire the quantized timer. */
    dw4_modelctrl_random(m,&state.random,&state.action_rhythm);
    assert(!command(m,"MOVETRANS","V<1000,10,1000>/V<0,0,0>"));
    assert(!command(m,"ONCTRL",NULL));dw4_modelctrl_sample(m,0);
    dw4_random_next(&expected);
    assert(!dw4_modelctrl_tick(m,0));dw4_modelctrl_aim_state(m,&aim);
    assert(aim.timer_present && !strcmp(aim.sequence,"SQ_WAIT") && !strcmp(dw4_modelctrl_sequence(m),"SQ_WAIT"));
    assert(!memcmp(&expected,&state.random,sizeof expected));
    int64_t duration=aim.timer_duration;
    assert(!dw4_modelctrl_tick(m,duration));
    assert(!memcmp(&expected,&state.random,sizeof expected));
    assert(!command(m,"OFCTRL",NULL));
    assert(!dw4_modelctrl_tick(m,duration+262144));
    assert(!memcmp(&expected,&state.random,sizeof expected));
    assert(!command(m,"ONCTRL",NULL));dw4_random_next(&expected);
    assert(!dw4_modelctrl_tick(m,duration+524288));
    assert(!memcmp(&expected,&state.random,sizeof expected));
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
    assert(!dw4_modelctrl_tick(m,duration+786432));dw4_modelctrl_aim_state(m,&aim);assert(!aim.timer_present);
    dw4_modelctrl_remove(m);assert(!dw4_modelctrl_active(m));
    dw4_modelctrl_script(m,NULL,0,NULL);
    assert(dw4_modelctrl_start(m,"SQ_WALKON")==-1);
    dw4_modelctrl_close(m);
    model.hp=100;dw4_modelctrl_script(other,e,17,&model);
    assert(!dw4_modelctrl_start(other,"SQ_WALKON"));
    dw4_modelctrl_aim_state(other,&aim);assert(model.hp==2 && aim.target[0]==20);
    dw4_modelctrl_script(other,NULL,0,NULL);
    dw4_scriptengine_close(e);dw4_modelctrl_close(other);
    for(callback_mode=0;callback_mode<4;callback_mode++) {
        dw4_be_init(&state);model.hp=1;
        m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
        e=dw4_scriptengine_open(&state,callback_service,NULL);assert(e);
        callback_owner=m;callback_model=&model;callback_engine=e;
        dw4_script_source_set(dw4_scriptengine_vm(e),callback_source,NULL,NULL);
        dw4_modelctrl_script(m,e,17,&model);
        int rc=dw4_modelctrl_start(m,"SQ_WALKON");
        if(callback_mode==2) {
            assert(rc && model.hp==1); /* removed scope cannot commit HP/target */
            dw4_modelctrl_aim_state(m,&aim);assert(aim.target[0]==0);
        } else {
            assert(!rc);
            if(callback_mode==0)assert(model.hp==99 && !strcmp(dw4_modelctrl_sequence(m),"SQ_WAIT02"));
            if(callback_mode==1)assert(model.hp==99 && !dw4_modelctrl_active(m));
            if(callback_mode==3) {
                assert(model.hp==2 && dw4_scriptengine_pending(e)==1);
                dw4_scriptengine_remove_scope(e,17);
                assert(!dw4_scriptengine_tick(e) && !dw4_scriptengine_pending(e) && model.hp==2);
            }
        }
        dw4_modelctrl_script(m,NULL,0,NULL);dw4_scriptengine_close(e);dw4_modelctrl_close(m);
    }
    puts("Actor AIMAP: 128 original WPos callbacks, isolated map state, shared RNG, scoped groups and reentry passed");
}
static void player_entry_test(dw4_mount *mount)
{
    static const char *assets[]={"m_dorumon.igb","m_agumon.igb","m_vmon.igb","m_girumon.igb"};
    static const char *names[]={"p_dorumon","p_agumon","p_vmon","p_girumon"};
    for(unsigned species=0;species<4;species++) {
        uint32_t size;const uint8_t *blob=dw4_mount_data(mount,assets[species],&size);assert(blob);
        dw4_modelctrl *m=dw4_modelctrl_open(blob,size,names[species]);assert(m);
        assert(!dw4_modelctrl_label(m,"SQ_ENTR","slash") && !dw4_modelctrl_label(m,"SQ_WAIT","slash"));
        dw4_modelctrl_sample(m,0);assert(!dw4_modelctrl_start(m,"SQ_ENTR"));
        dw4_modelctrl_actor actor={0};dw4_modelctrl_actor_state(m,&actor);
        assert(actor.enabled && !actor.motion_loop && actor.motion_duration_ns>0 && !strcmp(actor.motion,"waitS"));
        int64_t duration=actor.motion_duration_ns;
        dw4_scene scene={0};assert(!dw4_scene_load_actor_preview(&scene,blob,size));
        dw4_actoranim *pose=NULL;
        for(unsigned node=0;node<scene.nnode && !pose;node++)if(scene.node[node].name &&
            strstr(scene.node[node].name,"Skin0Shape1") && dw4_scene_node_texture(&scene,node))
            pose=dw4_actoranim_open_motion(blob,size,&scene,node,"waitS");
        assert(pose && duration==dw4_actoranim_duration_ns(pose));
        dw4_actoranim_close(pose);dw4_scene_close(&scene);
        unsigned finish=0;
        for(unsigned i=1;i<=180;i++) {
            int64_t now=(int64_t)i*1000000000/60;
            assert(!dw4_modelctrl_tick(m,now));
            const char *seq=dw4_modelctrl_sequence(m);
            if(((now>>18)<<18)<duration)assert(!strcmp(seq,"SQ_ENTR"));
            else {assert(!strcmp(seq,"SQ_WAIT"));finish=i;break;}
        }
        assert(finish && finish<180);dw4_modelctrl_actor_state(m,&actor);assert(actor.motion_loop);
        dw4_modelctrl_close(m);
    }
    puts("Player entry: four owned animation banks, slash-label OS/Motion wait, inclusive duration completion and default control pass");
}
static int near_target(void *user,const float position[3],float target[3])
{(void)position;memcpy(target,user,3*sizeof(float));return 0;}
static void gate_near_test(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    static const char *names[]={"g_cyexit","g_cytelep1","g_cytrerp2"};
    for(unsigned k=0;k<3;k++) {
        dw4_modelctrl *m=dw4_modelctrl_open(blob,size,names[k]);assert(m);
        dw4_random random;dw4_random_init(&random);uint32_t rhythm=0;
        float target[3]={0};dw4_modelctrl_random(m,&random,&rhythm);
        assert(!dw4_modelctrl_nearest(m,near_target,target));
        assert(!dw4_modelctrl_start(m,"SQ_POWERON"));
        for(int i=0;i<=45;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*1000000000/60));
        assert(!strcmp(dw4_modelctrl_action(m),"ONSW01"));
        int64_t before=dw4_modelctrl_time(m);assert(!dw4_modelctrl_tick(m,46LL*1000000000/60));
        assert(dw4_modelctrl_time(m)!=before);
        target[0]=20;
        for(int i=47;i<=85;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*1000000000/60));
        assert(!strcmp(dw4_modelctrl_action(m),"OFSW01"));
        assert(!dw4_modelctrl_start(m,"SQ_POWEROF"));target[0]=0;
        for(int i=86;i<=140;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*1000000000/60));
        assert(!strcmp(dw4_modelctrl_action(m),"WAIT01"));
        assert(!dw4_modelctrl_nearest(m,NULL,NULL));dw4_modelctrl_close(m);
    }
    puts("Gate NEAR maps: three original banks, proximity rise/loop/fall, powered-off admission and lifetime pass");
}
static void arena_records(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_data(mount,"m_dorumon.igb",&size);assert(blob);
    dw4_arena *a=dw4_session_arena();uint32_t baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    for(int cycle=0;cycle<32;cycle++){
        dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"p_dorumon");assert(m);
        dw4_modelctrl_record r=dw4_modelctrl_records(m);assert(r.arena==a && r.ram.off && r.work.off && r.data.off && r.node.off);
        beBaseInfoRam *ram=DW4_ARENA_OBJ(a,beBaseInfoRam,r.ram);
        beNDMWMdlPlayerInfoWork *w=DW4_ARENA_OBJ(a,beNDMWMdlPlayerInfoWork,r.work);
        beModelCtrlInfoRamData *d=DW4_ARENA_OBJ(a,beModelCtrlInfoRamData,r.data);
        assert(w && d->_work==(int32_t)r.work.off && d->_node==(int32_t)r.node.off);
        assert(al_count(a,w->_moveObjectList)==4 && al_count(a,w->_timerList)==DW4_STATUS_TIMER_SLOTS && al_count(a,w->_isFirstList)==11);
        w->_isOnCtrl=1;w->_ctrlSt0=2;w->_isWallCheck=1;
        int32_t *timers=al_words(a,w->_timerList);timers[DW4_STATUS_BIND]=91;
        const dw4_status *status=dw4_modelctrl_status(m);assert(status && status->timer[DW4_STATUS_BIND]==91);
        dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(m,&actor);assert(actor.enabled && actor.control==2 && actor.wall_check);
        beModelCtrlMoveObject *ch=DW4_ARENA_OBJ(a,beModelCtrlMoveObject,al_handle(al_words(a,w->_moveObjectList)[2]));ch->_isRun=1;ch->_speed=3.5f;
        dw4_modelctrl_actor_state(m,&actor);float speed;memcpy(&speed,&actor.channel[2].speed,4);assert(speed==3.5f && actor.channel[2].active);
        ram->_isRun=1;assert(dw4_modelctrl_active(m));ram->_isRun=0;assert(!dw4_modelctrl_active(m));
        dw4_script_model binding={.ram_no=3,.rec_no=4,.hp=34,.max_hp=50,.info_name="p_dorumon"};
        dw4_modelctrl_script(m,NULL,0,&binding);
        beDataObjInt *hp=DW4_ARENA_OBJ(a,beDataObjInt,al_handle(w->_hp));assert(hp && hp->_data==34 && ram->_ramNo==3 && w->_recNo==4);
        binding.rec_no=42;dw4_modelctrl_health(m,30,50);assert(hp->_data==30 && w->_recNo==42 && binding.hp==30);
        timers[DW4_STATUS_BIND]=0;hp->_data=9;ram->_isRun=1;
        assert(!dw4_modelctrl_status_tick(m,&binding.hp,NULL) && binding.hp==9 && hp->_data==9);
        ram->_isRun=0;
        const float offset[]={1,2,3},size[]={4,5,6};
        assert(!dw4_modelsubcom_hitbox(a,al_handle(w->_subCommand),70009,0x3e800000,0x3f800000,offset,size));
        beModelCtrlSubCom *sc=DW4_ARENA_OBJ(a,beModelCtrlSubCom,al_handle(w->_subCommand));
        beModelCtrlSCHitBox *box=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,al_handle(al_words(a,sc->_comList)[0]));
        unsigned n;const dw4_modelctrl_hitbox *projection=dw4_modelctrl_hitboxes(m,&n);
        assert(n==1 && projection[0].kind==70009 && projection[0].end_frames==1.25f);
        dw4_modelctrl_hitbox copied=projection[0];box->_kind=70010;box->_endFrame=2.5f;
        projection=dw4_modelctrl_hitboxes(m,&n);assert(copied.kind==70009 && projection[0].kind==70010 && projection[0].end_frames==2.5f);
        igAnimation *animation=DW4_ARENA_OBJ(a,igAnimation,r.action.animation);
        igAnimationState *animstate=DW4_ARENA_OBJ(a,igAnimationState,r.action.motion);
        animation->_duration=12345;animstate->_blendDuration=234;animstate->_timeBias=-262144;
        dw4_modelctrl_actor_state(m,&actor);assert(actor.motion_duration_ns==12345 && actor.blend_ns==234 && actor.motion_ns==-262144);
        beAction2InfoWork *aw=DW4_ARENA_OBJ(a,beAction2InfoWork,r.action.work);
        ram->_isRun=1;aw->_fadeSt0=2;aw->_fadeValue=.25f;assert(dw4_modelctrl_alpha(m)==.25f);ram->_isRun=0;
        dw4_modelctrl *other=dw4_modelctrl_instance(m);assert(other);dw4_modelctrl_record twin=dw4_modelctrl_records(other);
        assert(twin.work.off!=r.work.off && !dw4_modelctrl_status(other)->timer[DW4_STATUS_BIND]);
        dw4_modelctrl_close(m);dw4_modelctrl_close(other);assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
    }
    puts("Model arena: independent typed RAM/Work/node/channel/status closures, authoritative field reads and complete teardown pass");
}
static void bind_movement_test(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_data(mount,"m_dorumon.igb",&size);assert(blob);
    dw4_arena *a=dw4_session_arena();unsigned baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"p_dorumon");assert(m);
    dw4_modelctrl_record r=dw4_modelctrl_records(m);
    beNDMWMdlPEBaseInfoWork *w=DW4_ARENA_OBJ(a,beNDMWMdlPEBaseInfoWork,r.work);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT"));dw4_modelctrl_health(m,10,10);
    dw4_modelctrl_sample(m,0);assert(!dw4_modelctrl_tick(m,0));
    assert(!command(m,"SETBIND","I<600>"));int hp=10;
    assert(!dw4_modelctrl_status_tick(m,&hp,NULL));
    /* Compare all payload bytes at zero delta: only active/speed may change,
     * including on an already inactive channel with retained speed. */
    for(int control=0;control<2;control++)for(int freeze=0;freeze<2;freeze++){
        w->_ctrlSt0=0;w->_isOnCtrl=control;w->_isOnFreeze=freeze;
        beModelCtrlMoveObject before[4];
        for(int i=0;i<4;i++){
            beModelCtrlMoveObject *ch=DW4_ARENA_OBJ(a,beModelCtrlMoveObject,al_handle(al_words(a,w->_moveObjectList)[i]));
            ch->_isRun=0;ch->_speed=3.5f+i;before[i]=*ch;
        }
        assert(!dw4_modelctrl_tick(m,0));
        for(int i=0;i<4;i++){
            beModelCtrlMoveObject *ch=DW4_ARENA_OBJ(a,beModelCtrlMoveObject,al_handle(al_words(a,w->_moveObjectList)[i]));
            if(control && !freeze && i!=1)before[i]._speed=0;
            assert(!memcmp(ch,before+i,sizeof *ch));
        }
    }
    w->_isOnFreeze=0;w->_isOnCtrl=1;
    /* Vertical motion remains live while every horizontal/turn channel stops. */
    for(int i=0;i<4;i++){
        beModelCtrlMoveObject *ch=DW4_ARENA_OBJ(a,beModelCtrlMoveObject,al_handle(al_words(a,w->_moveObjectList)[i]));
        ch->_isRun=1;ch->_mode=4;ch->_speed=2;ch->_acc=0;ch->_endTime=0;
    }
    dw4_modelctrl_actor before,after;dw4_modelctrl_actor_state(m,&before);
    assert(!dw4_modelctrl_tick(m,16666667));dw4_modelctrl_actor_state(m,&after);
    assert(after.position[0]==before.position[0] && after.position[2]==before.position[2]);
    assert(after.position[1]>before.position[1]+1.9f && after.channel[1].active);
    for(int i=0;i<4;i++)if(i!=1)assert(!after.channel[i].active && !after.channel[i].speed);
    assert(!command(m,"CLEARSTATUS",NULL));assert(!dw4_modelctrl_status(m)->timer[DW4_STATUS_BIND]);
    dw4_modelctrl_close(m);assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
    puts("BIND: arena channel writes, control/freeze gates, vertical movement and cleanup pass");
}
int main(int argc,char **argv) {
    dw4_mount mount={0};assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    arena_records(&mount);
    bind_movement_test(&mount);
    int emit=argc>2 && !strcmp(argv[2],"--trace");
    arrival(&mount,"n_digilff","SQ_WALK02",emit);
    arrival(&mount,"n_digilfm","SQ_WALK03",emit);
    control_test(&mount,emit);transform_test(&mount,emit);aim_test(&mount,emit);
    if(!emit){lua_test(&mount);player_entry_test(&mount);gate_near_test(&mount);muteki_test(&mount);}
    dw4_mount_close(&mount);puts("Actor controllers: original Digi-Elf turn/walk/talk, labels, retained movement and lifetime passed");return 0;
}
