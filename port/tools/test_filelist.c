#include "dw4/filelist.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct host { int light,joined,fail,fail_route; unsigned calls,routed,once; };
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct host *h=user;h->calls++;
    if(h->fail){snprintf(error,cap,"intentional unavailable service: %s",method);return -1;}
    *r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    if(!strcmp(method,"SYSgetArea"))r->number=1;
    else if(!strcmp(method,"SYSgetLightMode"))r->number=h->light;
    else if(!strcmp(method,"SYSisJoinPlayer"))r->number=h->joined && n==1 && a[0].number==0;
    else if(!strcmp(method,"SYSgetPlayerName"))
        *r=(dw4_script_value){DW4_SCRIPT_STRING,0,"m_dorumon",9};
    else if(!strcmp(method,"SYSgetWeaponName"))
        *r=(dw4_script_value){DW4_SCRIPT_STRING,0,"w_axe01",7};
    /* Only asset selection queries above represent the input snapshot. All
     * scene/gameplay commands are controlled leaves in this loader test. */
    return 0;
}
static int route(void *user,const char *path,dw4_igb *g,int once) {
    struct host *h=user;assert(path && g->table_n);h->routed++;h->once+=once;
    return h->fail_route?-1:0;
}
static int bind_layers(void *user) {
    struct host *h=user;assert(h->routed);return h->fail_route?-1:0;
}
static void path(dw4_filelist *f,size_t i,const char *expected) {
    const char *got=dw4_filelist_path(f,i);
    if(!got || strcmp(got,expected))fprintf(stderr,"path %zu: %s != %s\n",i,got?got:"NULL",expected);
    assert(got && !strcmp(got,expected));
}
static void begin(dw4_filelist *f,dw4_scriptengine *e,const char *stage) {
    int rc=dw4_filelist_begin(f,e,stage,7);
    if(rc)fprintf(stderr,"begin: %s\n",dw4_filelist_error(f));
    assert(!rc);
}
static void shared(dw4_filelist *f) {
    int rc=dw4_filelist_shared(f);
    if(rc)fprintf(stderr,"shared: %s\n",dw4_filelist_error(f));
    assert(!rc);
}
int main(int argc,char **argv) {
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    struct host h={.light=1,.joined=1};dw4_be_state state;dw4_be_init(&state);
    dw4_filelist *f=dw4_filelist_open(&mount);assert(f);
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&h);assert(e);
    dw4_scriptengine_filelist(e,f);
    if(argc>2 && !strcmp(argv[2],"--queue")) {
        begin(f,e,"stagIS10");
        dw4_script_value r;char error[128];
        assert(!dw4_filelist_call(f,"CFLgetFolderName",NULL,0,&r,error,sizeof(error)));
        printf("folder:%s\n",r.string);
        const char *constants[]={"SYSgetArea","SYSgetCountry","SYSgetIsPackOnly"};
        for(unsigned i=0;i<3;i++) {
            assert(!dw4_filelist_call(f,constants[i],NULL,0,&r,error,sizeof(error)));
            printf("%s:%.0f\n",constants[i],r.number);
        }
        for(int i=3;i<argc;i++) {
            dw4_script_value a={DW4_SCRIPT_STRING,0,argv[i],strlen(argv[i])};
            int clear=!strcmp(argv[i],"<clear>");
            assert(!dw4_filelist_call(f,clear?"CFLclear":"CFLsetName",clear?NULL:&a,clear?0:1,&r,error,sizeof(error)));
        }
        for(size_t i=0;i<dw4_filelist_queue_count(f);i++)printf("queue:%s\n",dw4_filelist_queue_path(f,i));
        dw4_scriptengine_filelist(e,NULL);dw4_scriptengine_close(e);dw4_filelist_close(f);dw4_mount_close(&mount);
        return 0;
    }
    assert(dw4_filelist_first(f)==-1 && dw4_filelist_start(f)==-1);
    begin(f,e,"stagIS10");
    path(f,0,"BecText.igb");path(f,1,"_common/sbiallse.igb");
    path(f,2,"[0.805]");path(f,3,"[0.806]");
    assert(dw4_filelist_count(f)==4);
    shared(f);assert(dw4_filelist_count(f)==6);
    /* Beginning again without coordinated teardown must preserve residency. */
    assert(dw4_filelist_begin(f,e,"stagML11",7)==-1);
    assert(dw4_filelist_count(f)==6);
    path(f,4,"stagIS10/separate/AUS_pack.igb");path(f,5,"stagIS10/separate/USA_pack.igb");
    assert(!dw4_filelist_route_assets(f,route,&h));assert(h.routed==7 && h.once==2);
    assert(dw4_filelist_start(f)==-1 && dw4_filelist_first(f)==-1);
    assert(!dw4_filelist_bind_layers(f,bind_layers,&h));
    assert(!dw4_filelist_start(f) && !dw4_filelist_first(f));
    assert(!dw4_scriptengine_start_status(e)->func && !dw4_scriptengine_start_status(e)->boot);
    uint32_t random[624];memcpy(random,state.random.words,sizeof(random));
    assert(!dw4_scriptengine_reset_scene(e,NULL));h.routed=h.once=0;
    begin(f,e,"stagML11.igb");path(f,2,"[0.819]");path(f,3,"[0.820]");
    shared(f);assert(dw4_filelist_count(f)==8);
    path(f,4,"_common/m_dorumon.igb");path(f,5,"_common/w_axe01.igb");
    path(f,6,"stagML11/separate/USA_pack.igb");path(f,7,"stagML11/separate/LH_pack.igb");
    assert(!memcmp(random,state.random.words,sizeof(random)));
    assert(!dw4_filelist_route_assets(f,route,&h));
    assert(dw4_filelist_start(f)==-1 && dw4_filelist_first(f)==-1);
    assert(!dw4_filelist_bind_layers(f,bind_layers,&h));
    assert(!dw4_filelist_start(f) && !dw4_filelist_first(f));
    for(unsigned cycle=0;cycle<128;cycle++) {
        assert(!dw4_scriptengine_reset_scene(e,NULL));
        h.light=cycle&1;begin(f,e,"stagML11");shared(f);
        path(f,7,h.light?"stagML11/separate/LH_pack.igb":"stagML11/separate/LS_pack.igb");
        assert(dw4_filelist_count(f)==8);
    }
    /* Missing filename, unsupported original boot query, and native routing
     * failure all block later milestones; a fresh boundary permits recovery. */
    assert(!dw4_scriptengine_reset_scene(e,NULL));begin(f,e,"stagIS10");
    dw4_script_value a={DW4_SCRIPT_STRING,0,"missing.igb",11},r;char error[128];
    assert(!dw4_filelist_call(f,"CFLsetName",&a,1,&r,error,sizeof(error)));
    /* Original boot's CFLclear removes this stale queued filename. */
    shared(f);assert(dw4_filelist_count(f)==6);
    /* Remove only the in-memory manifest route: never mutate original data. */
    assert(!dw4_scriptengine_reset_scene(e,NULL));begin(f,e,"stagIS10");
    const dw4_manifest_file *found=dw4_manifest_find(&mount.man,"stagIS10/separate/USA_pack.igb");
    dw4_manifest_file *missing=found?mount.man.files+(found-mount.man.files):NULL;
    assert(missing);int saved_entry=missing->entry;missing->entry=-1;
    assert(dw4_filelist_shared(f)==-1 && strstr(dw4_filelist_error(f),"missing stage asset"));
    assert(dw4_filelist_route_assets(f,route,&h)==-1 && dw4_filelist_first(f)==-1);
    missing->entry=saved_entry;
    assert(!dw4_scriptengine_reset_scene(e,NULL));begin(f,e,"stagML11");h.fail=1;
    assert(dw4_filelist_shared(f)==-1 && strstr(dw4_filelist_error(f),"original func/boot failed"));
    assert(dw4_filelist_start(f)==-1 && dw4_filelist_first(f)==-1);h.fail=0;
    assert(!dw4_scriptengine_reset_scene(e,NULL));begin(f,e,"stagIS10");shared(f);h.fail_route=1;
    assert(dw4_filelist_route_assets(f,route,&h)==-1 && dw4_filelist_start(f)==-1);h.fail_route=0;
    assert(!dw4_scriptengine_reset_scene(e,NULL));begin(f,e,"stagIS10");shared(f);
    assert(!dw4_filelist_route_assets(f,route,&h));h.fail_route=1;
    assert(dw4_filelist_bind_layers(f,bind_layers,&h)==-1 && dw4_filelist_start(f)==-1 && dw4_filelist_first(f)==-1);
    h.fail_route=0;
    assert(!dw4_scriptengine_reset_scene(e,NULL));
    assert(dw4_filelist_begin(f,e,"missing-stage",7)==-1 && dw4_filelist_shared(f)==-1);
    assert(!dw4_scriptengine_reset_scene(e,NULL));begin(f,e,"stagIS10");shared(f);
    dw4_scriptengine_filelist(e,NULL);dw4_scriptengine_close(e);dw4_filelist_close(f);dw4_mount_close(&mount);
    puts("file-list: original title/lobby boot asset queues, startup gates, failure recovery and 128 reloads passed");
    return 0;
}
