#include "dw4/scriptengine.h"
#include "dw4/action2host.h"
#include "dw4/modelai.h"
#include "dw4/simulation.h"
#include "dw4/scriptservices.h"
#include "dw4/titleservices.h"
#include "dw4/lobbyui.h"
#include "dw4/mount.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct object_backend {dw4_script_object object;unsigned checks;const char *source;};
static int object_source(void *user,const char *path,const void **bytes,size_t *n)
{struct object_backend *b=user;(void)path;*bytes=b->source;*n=strlen(b->source);return 0;}
static int object_binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    struct object_backend *b=user;(void)error;(void)cap;
    assert(!strcmp(method,"sd") && n==4 && a[0].type==DW4_SCRIPT_STRING && a[3].type==DW4_SCRIPT_STRING);
    if(!strcmp(a[3].string,"GETDATABASE")){*r=dw4_script_object_value(&b->object);return 0;}
    assert(!strcmp(a[3].string,"CHECK"));const dw4_script_object *o=dw4_script_value_object(a+1);
    assert(o && o->kind==b->object.kind && o->pointer==b->object.pointer && o->owner==b->object.owner);
    b->checks++;*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;
}
static void object_values(void)
{
    int native=5;struct object_backend b={0};b.object=(dw4_script_object){DW4_SCRIPT_DATABASE,&native,&b};
    dw4_script *s=dw4_script_open(object_binding,&b);assert(s);
    const char *source="first=be:sd('DATABASE','shinka',0,'GETDATABASE') second=be:sd('DATABASE','shinka',0,'GETDATABASE') assert(type(first)=='userdata' and first==second) be:sd('DATABASE',first,0,'CHECK') [EOF]";
    b.source=source;dw4_script_source_set(s,object_source,&b,NULL);
    int ran=dw4_script_run_named(s,"objects.lua",NULL);if(ran)fprintf(stderr,"object bridge: %s\n",dw4_script_error(s));assert(!ran && b.checks==1);
    dw4_script_value value;assert(!dw4_script_get(s,"first",&value));const dw4_script_object *o=dw4_script_value_object(&value);assert(o && o->pointer==&native);
    assert(!dw4_script_set(s,"third",value));
    const char *check="assert(first==third) be:sd('DATABASE',first,0,'CHECK') [EOF]";
    b.source=check;assert(!dw4_script_run_named(s,"check.lua",NULL) && b.checks==2);
    dw4_script_value stale=value;dw4_script_objects_invalidate(s,&b);
    assert(dw4_script_set(s,"stale",stale));
    assert(dw4_script_get(s,"first",&value));assert(dw4_script_run_named(s,"check.lua",NULL) && b.checks==2);
    assert(strstr(dw4_script_error(s),"expired"));
    assert(!dw4_script_recreate(s));assert(!dw4_script_get(s,"first",&value) && value.type==DW4_SCRIPT_NIL);
    b.source=source;assert(!dw4_script_run_named(s,"objects.lua",NULL) && b.checks==3);
    dw4_script_close(s);puts("Lua objects: typed userdata identity/roundtrip, owner invalidation and VM recreation pass");
}
struct backend { unsigned tick,calls,queries,title,delay,events; int area; int order[8]; char log[4096]; };
static int binding(void *user,const char *name,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct backend *b=user; b->calls++;
    if (!strcmp(name,"SYSgetArea")) { r->type=DW4_SCRIPT_NUMBER; r->number=b->area; return 0; }
    if (!strcmp(name,"sd") || !strcmp(name,"querySD")) {
        assert(n>=4 && n<=6 && a[0].type==DW4_SCRIPT_STRING && a[3].type==DW4_SCRIPT_STRING);
        assert(a[1].type==DW4_SCRIPT_NIL || a[1].type==DW4_SCRIPT_STRING);
        assert(a[2].type==DW4_SCRIPT_NUMBER);
        const char *key=a[3].string;
        if (!strcmp(name,"querySD")) {
            b->queries++;
            r->type=DW4_SCRIPT_NUMBER;
            if (!strcmp(key,"ISDEMOCAMERA")) r->number=b->tick<2;
            else if (!strcmp(key,"ISSEQNAME")) r->number=b->tick<5;
            else { snprintf(error,cap,"unknown query"); return -1; }
            return 0;
        }
        size_t used=strlen(b->log);
        snprintf(b->log+used,sizeof(b->log)-used,"%s:%s@%u;",a[0].string,key,b->tick);
        if (!strcmp(key,"PAUSEOFF")) {
            assert(n==6 && a[5].type==DW4_SCRIPT_NUMBER && a[5].number==240); b->delay++;
        }
        if (!strcmp(a[0].string,"TITLE2")) { assert(!strcmp(key,"RUN")); assert(b->tick==5); b->title++; }
        if (!strcmp(key,"EVENT")) { assert(b->events<8); b->order[b->events++]=(int)a[2].number; }
        return 0;
    }
    snprintf(error,cap,"test service unsupported: %s",name); return -1;
}

/* Test-owned Lua 4 assembler. No retail bytecode is committed. */
struct fixture { unsigned char bytes[4096]; size_t n; uint32_t code[128]; size_t nc; };
static void u32(struct fixture *f,uint32_t v) {
    for (int i=0;i<4;i++) f->bytes[f->n++]=(unsigned char)(v>>(8*i));
}
static void str(struct fixture *f,const char *s) {
    size_t n=strlen(s)+1; u32(f,(uint32_t)n); memcpy(f->bytes+f->n,s,n); f->n+=n;
}
static void ins(struct fixture *f,uint32_t op,uint32_t u) { f->code[f->nc++]=op|(u<<6); }
static void num(struct fixture *f,int v) { ins(f,6,(uint32_t)(33554431+v)); }
static void call(struct fixture *f,int method) { ins(f,12,0); ins(f,16,(uint32_t)method); }
static void finish(struct fixture *f) { ins(f,2,0); }
static void encode(struct fixture *f) {
    const char *strings[]={"be","DMsetSD","DMchkSD","DMrun","DMsetLua","COUNTERset", "SYSgetArea",
        "STAGECTL","EVENT","ISDEMOCAMERA","!=0","event.lua","truth","FLGisOn",
        "DMswtSD","DMcase","DMswtEnd","DMmsgBox","DMgetCount","count","VALUE",
        "MODELCTRL","i_talkwn","ISRUN","ISSEQNAME","SQ_OPENL","SQ_CLOSEL","SYSgetRandom","roll","MDLsetSeq","MDLaddHp","dofile"};
    unsigned char header[]={27,'L','u','a',64,1,4,4,4,32,6,9,8};
    memcpy(f->bytes,header,sizeof(header)); f->n=sizeof(header);
    union { double d; uint64_t u; } test={.d=3.14159265358979323846E8};
    for (int i=0;i<8;i++) f->bytes[f->n++]=(unsigned char)(test.u>>(8*i));
    str(f,"=host-test"); u32(f,0); u32(f,0); f->bytes[f->n++]=0; u32(f,16);
    u32(f,0); u32(f,0); u32(f,sizeof(strings)/sizeof(*strings));
    for (size_t i=0;i<sizeof(strings)/sizeof(*strings);i++) str(f,strings[i]);
    u32(f,0); u32(f,0); ins(f,0,0); u32(f,(uint32_t)f->nc);
    for (size_t i=0;i<f->nc;i++) u32(f,f->code[i]);
}
static void sd_id(struct fixture *f,int id) {
    call(f,1); ins(f,7,7); ins(f,4,1); num(f,id); ins(f,7,8); finish(f);
}
static struct fixture marker(int value) {
    struct fixture f={0};num(&f,value);ins(&f,19,12);encode(&f);return f;
}
static void check_marker(dw4_script *s,int value) {
    dw4_script_value v;assert(!dw4_script_run(s,"event.lua"));
    assert(!dw4_script_get(s,"truth",&v) && v.type==DW4_SCRIPT_NUMBER && v.number==value);
}
/* Retail ownership regression fixtures use actual Lua side effects, not a
 * second implementation of the loader's selection algorithm. */
struct ownership_backend {
    dw4_scriptengine *engine; dw4_scriptservices *sd; dw4_script *vm;
    unsigned calls,sources,initializations; int busy,dm_clear,source_status,unload;
    const char *source_text; char path[512];
};
static int ownership_source(void *user,const char *path,const void **bytes,size_t *n) {
    struct ownership_backend *b=user;b->sources++;
    snprintf(b->path,sizeof(b->path),"%s",path);
    *bytes=b->source_text;*n=b->source_text?strlen(b->source_text):0;
    return b->source_status;
}
static int ownership_binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct ownership_backend *b=user;
    if(!strcmp(method,"SYSgetArea") && !n) {
        b->calls++;r->type=DW4_SCRIPT_NUMBER;r->number=0;
        if(b->unload){b->unload=0;dw4_script_remove_scope(b->vm,0);}
        if(b->busy) {
            assert(dw4_script_recreate(b->vm)==-1);
            assert(dw4_script_remove_all(b->vm)==-1);
            assert(dw4_scriptengine_reset_scene(b->engine,b->sd)==-1);
        }
        return 0;
    }
    if(!strcmp(method,"sd") || !strcmp(method,"querySD")) {
        assert(n>=4);r->type=DW4_SCRIPT_NUMBER;r->number=1;
        if(!strcmp(a[0].string,"TEXTCTL")) {
            assert(!strcmp(a[3].string,"INITIALIZE"));b->initializations++;
            assert(dw4_scriptengine_reset_scene(b->engine,b->sd)==-1);
        } else if(b->dm_clear) {
            b->calls++;
            if(b->calls==1) {
                assert(dw4_scriptengine_reset_scene(b->engine,b->sd)==-1);
                dw4_scriptengine_dm_remove_all(b->engine);
                assert(dw4_scriptengine_pending(b->engine)==1);
            }
        }
        return 0;
    }
    snprintf(error,cap,"intentional failure: %s",method);return -1;
}
static struct fixture ownership_marker(int value,int side_effect) {
    struct fixture f={0};
    if(side_effect){call(&f,6);finish(&f);}
    ins(&f,12,12);num(&f,10);ins(&f,26,0);num(&f,value);ins(&f,23,0);ins(&f,19,12);
    encode(&f);return f;
}
static void ownership_truth(dw4_script *s,int expected) {
    dw4_script_value v;
    assert(!dw4_script_get(s,"truth",&v) && v.type==DW4_SCRIPT_NUMBER && v.number==expected);
}
static void test_ownership(dw4_mount *mount) {
    struct ownership_backend b={.source_status=2};
    dw4_script *s=dw4_script_open(ownership_binding,&b);assert(s);b.vm=s;
    dw4_script_source_set(s,ownership_source,&b,"stagML11/lua");
    struct fixture one=ownership_marker(1,1),two=ownership_marker(2,1),ignored=marker(99);
    dw4_script_buffer first[]={ {"x.lua",one.bytes,one.n},{"x.lua",ignored.bytes,ignored.n} };
    dw4_script_buffer second[]={ {"other.lua",ignored.bytes,ignored.n},{"x.lua",two.bytes,two.n} };
    assert(dw4_script_collect_info(s,first,2)==2);
    assert(dw4_script_collect_info(s,second,2)==2);
    assert(!dw4_script_set(s,"truth",(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}));
    assert(!dw4_script_run_named(s,"x.lua","custom/lua"));ownership_truth(s,12);
    assert(b.calls==2 && !b.sources); /* every info; first duplicate only */
    struct fixture bad={0};call(&bad,5);finish(&bad);encode(&bad);
    dw4_script_buffer error={"x.lua",bad.bytes,bad.n};
    assert(dw4_script_collect_info(s,&error,1)==1);
    assert(dw4_script_run_named(s,"x.lua",NULL)==1 && !b.sources);
    ownership_truth(s,1212); /* side effects remain despite last error */
    assert(dw4_script_collect_info(s,second,2)==2);
    assert(!dw4_script_run_named(s,"x.lua",NULL));ownership_truth(s,1212122);
    assert(!dw4_script_error(s)[0]); /* later success determines final result */
    size_t sources=b.sources;
    assert(dw4_script_run_named(s,"missing.lua",NULL)==2 && b.sources==sources+1);
    assert(!strcmp(b.path,"stagML11/lua/missing.lua"));
    b.source_status=-1;
    assert(dw4_script_run_named(s,"missing.lua","custom/lua")==-1);
    assert(!strcmp(b.path,"custom/lua/missing.lua"));
    b.source_status=0;b.source_text="truth = 7; owned = { nested = {} }; function owned_fn() return 1 end; [EOF] invalid trailing bytes";
    assert(!dw4_script_run_named(s,"missing.lua",NULL));ownership_truth(s,7);
    assert(!dw4_script_call(s,"owned_fn",NULL,0));
    b.source_text="truth = 9";
    assert(dw4_script_run_named(s,"missing.lua",NULL)==-1);ownership_truth(s,7);
    b.source_text="truth = [EOF]";
    assert(dw4_script_run_named(s,"missing.lua",NULL)==3);
    assert(!dw4_script_recreate(s));
    dw4_script_value v;assert(!dw4_script_get(s,"owned",&v) && v.type==DW4_SCRIPT_NIL);
    assert(!dw4_script_get(s,"truth",&v) && v.type==DW4_SCRIPT_NIL);
    assert(dw4_script_call(s,"owned_fn",NULL,0)==-1);
    assert(!dw4_script_set(s,"truth",(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}));
    assert(!dw4_script_run_named(s,"x.lua",NULL));ownership_truth(s,122); /* infos survived recreation */
    assert(!dw4_script_remove_all(s) && !dw4_script_recreate(s));
    b.source_status=2;assert(dw4_script_run_named(s,"x.lua",NULL)==2);
    /* A failed collector preserves all existing infos, even part-way through. */
    uint32_t size;const uint8_t *data=dw4_mount_entry(mount,0,806,&size,NULL);assert(data);
    dw4_igb pack={0};assert(!dw4_igb_open(&pack,data,size,0));
    assert(dw4_script_collect_pack(s,&pack)==10);dw4_igb_close(&pack);
    assert(!dw4_script_run_named(s,"func.lua",NULL));
    assert(!dw4_script_call(s,"funcFirstLayerSet",NULL,0));
    uint8_t *damaged=malloc(size);assert(damaged);memcpy(damaged,data,size);
    for(size_t i=0;i+4<size;i++)if(!memcmp(damaged+i,"\033Lua",4)){damaged[i+4]=0;break;}
    assert(!dw4_igb_open(&pack,damaged,size,0));
    assert(dw4_script_collect_pack(s,&pack)==-1);dw4_igb_close(&pack);free(damaged);
    assert(!dw4_script_recreate(s) && !dw4_script_run_named(s,"func.lua",NULL));
    assert(!dw4_script_call(s,"funcFirstLayerSet",NULL,0));
    /* Duplicate a func row in the authored list, leaving boot as an orphan
     * record. A record-table scan would still incorrectly execute that boot. */
    damaged=malloc(size);assert(damaged);memcpy(damaged,data,size);
    assert(!dw4_igb_open(&pack,damaged,size,0) && !dw4_igb_refs_open(&pack));
    int patched=0;
    for(uint32_t id=0;id<pack.table_n;id++)if(pack.id_kind[id]==2) {
        dw4_igb_record row={0};assert(dw4_igb_decode(&pack,pack.id_off[id],&row));
        if(!strcmp(row.class_name,"beLuaDataList"))for(uint32_t j=0;j<row.nvalues;j++)
            if(row.values[j].ordinal==4 && row.values[j].type==DW4_IGB_TY_MEMREF) {
                uint32_t length;const uint8_t *ids=dw4_igb_block(&pack,row.values[j].raw,&length);
                assert(ids && length>=12);memcpy(damaged+(ids-pack.data),ids+8,4);patched=1;
            }
        dw4_igb_record_free(&row);
    }
    assert(patched && !dw4_script_remove_all(s) && !dw4_script_recreate(s));
    assert(dw4_script_collect_pack(s,&pack)==10);dw4_igb_close(&pack);free(damaged);
    assert(!dw4_script_run_named(s,"func.lua",NULL));
    assert(dw4_script_run_named(s,"boot.lua",NULL)==2);
    assert(!dw4_script_remove_all(s) && !dw4_script_recreate(s));
    assert(dw4_script_collect_info(s,first,2)==2 && dw4_script_collect_info(s,second,2)==2);
    assert(!dw4_script_set(s,"truth",(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}));
    b.unload=1;
    assert(!dw4_script_run_named(s,"x.lua",NULL));ownership_truth(s,12);
    assert(dw4_script_run_named(s,"x.lua",NULL)==2); /* active copied rows finished safely */
    dw4_script_close(s);

    dw4_be_state state;dw4_be_init(&state);state.flag[77]=1;
    (void)dw4_random_next(&state.random);dw4_random saved=state.random;
    b=(struct ownership_backend){.sd=dw4_scriptservices_open()};assert(b.sd);
    b.engine=dw4_scriptengine_open(&state,ownership_binding,&b);assert(b.engine);
    b.vm=dw4_scriptengine_vm(b.engine);s=b.vm;
    struct fixture func=marker(1),boot=ownership_marker(2,1),start=ownership_marker(3,0),last=ownership_marker(4,0);
    dw4_script_buffer startup[]={ {"first.lua",last.bytes,last.n},{"boot.lua",boot.bytes,boot.n},
        {"start.lua",start.bytes,start.n},{"func.lua",func.bytes,func.n} };
    assert(dw4_script_collect_info(s,startup,4)==4);
    assert(dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_FIRST)==-1);
    assert(!dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_SHARED));ownership_truth(s,12);
    assert(!dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_STAGE));ownership_truth(s,123);
    assert(b.initializations==1);
    assert(!dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_FIRST));ownership_truth(s,1234);
    assert(dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_FIRST)==-1);
    const dw4_script_start_status *status=dw4_scriptengine_start_status(b.engine);
    assert(!status->func && !status->boot && !status->text && !status->start && !status->first);
    b.busy=1;assert(!dw4_scriptengine_run(b.engine,"boot.lua"));b.busy=0;
    assert(!dw4_scriptengine_reset_scene(b.engine,b.sd));
    assert(state.flag[77]==1 && !memcmp(&saved,&state.random,sizeof(saved)));
    assert(!dw4_script_get(s,"truth",&v) && v.type==DW4_SCRIPT_NIL);
    /* Retail advances through script failures; host run fail-stop stays separate. */
    dw4_script_buffer failing[]={ {"func.lua",bad.bytes,bad.n},{"boot.lua",func.bytes,func.n},
        {"start.lua",bad.bytes,bad.n},{"first.lua",last.bytes,last.n} };
    assert(dw4_script_collect_info(s,failing,4)==4);
    assert(!dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_SHARED));ownership_truth(s,1);
    assert(!dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_STAGE));
    assert(!dw4_scriptengine_startup(b.engine,DW4_SCRIPT_START_FIRST));ownership_truth(s,14);
    status=dw4_scriptengine_start_status(b.engine);
    assert(status->func==1 && !status->boot && status->start==1 && !status->first);
    assert(!dw4_scriptengine_run(b.engine,"boot.lua"));
    assert(!dw4_scriptengine_reset_scene(b.engine,b.sd));
    /* DM RemoveAll requested during dispatch preserves the entire pass. */
    struct fixture dm={0};sd_id(&dm,1);sd_id(&dm,2);call(&dm,3);finish(&dm);encode(&dm);
    /* Reset retains retail mode: publish events through collected infos. */
    dw4_script_buffer event={"dm.lua",dm.bytes,dm.n};assert(dw4_script_collect_info(s,&event,1)==1);
    assert(!dw4_scriptengine_run(b.engine,"dm.lua"));b.dm_clear=1;b.calls=0;
    assert(!dw4_scriptengine_tick(b.engine) && b.calls==2 && !dw4_scriptengine_pending(b.engine));b.dm_clear=0;
    dw4_script_source_set(s,ownership_source,&b,"stage/lua");b.source_status=0;
    b.source_text="owned = {}; function owned_fn() return 1 end; [EOF]";
    assert(!dw4_script_run_named(s,"globals.lua",NULL));
    uint64_t token=dw4_scriptservices_register(b.sd,0,"TEST",NULL,-1,1,ownership_binding,&b);assert(token);
    dw4_script_value a[]={ {DW4_SCRIPT_STRING,0,"TEST",4},{DW4_SCRIPT_NIL,0,NULL,0},
        {DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"EVENT",5},{DW4_SCRIPT_NUMBER,60,NULL,0} },r={0};char diagnostic[512];
    assert(!dw4_scriptservices_call(b.sd,"sd",a,5,&r,diagnostic,sizeof(diagnostic)));
    assert(!dw4_scriptengine_queue_event(b.engine,"dm.lua"));
    /* Unpublished builder and switch latch also belong to DM. */
    struct fixture unfinished={0};call(&unfinished,14);ins(&unfinished,7,7);ins(&unfinished,4,1);num(&unfinished,-1);ins(&unfinished,7,8);finish(&unfinished);encode(&unfinished);
    dw4_script_buffer building={"building.lua",unfinished.bytes,unfinished.n};assert(dw4_script_collect_info(s,&building,1)==1);
    assert(!dw4_scriptengine_run(b.engine,"building.lua"));
    assert(dw4_scriptengine_pending(b.engine)==1 && dw4_scriptservices_pending(b.sd)==1);
    assert(!dw4_scriptengine_reset_scene(b.engine,b.sd));
    assert(!dw4_scriptengine_pending(b.engine) && !dw4_scriptservices_pending(b.sd));
    assert(dw4_scriptservices_call(b.sd,"querySD",a,4,&r,diagnostic,sizeof(diagnostic))==-1);
    assert(!dw4_script_get(s,"owned",&v) && v.type==DW4_SCRIPT_NIL && dw4_script_call(s,"owned_fn",NULL,0)==-1);
    uint64_t next=dw4_scriptservices_register(b.sd,0,"TEST",NULL,-1,1,ownership_binding,&b);assert(next>token);
    dw4_scriptservices_unregister(b.sd,token); /* stale token cannot erase replacement */
    assert(!dw4_scriptservices_call(b.sd,"querySD",a,4,&r,diagnostic,sizeof(diagnostic)));
    assert(!dw4_scriptengine_tick(b.engine));
    assert(!dw4_scriptengine_remove_all(b.engine,b.sd));
    assert(dw4_script_run(s,"dm.lua")==-1 && !dw4_script_recreate(s));
    dw4_scriptengine_close(b.engine);dw4_scriptservices_close(b.sd);
    puts("Lua ownership: ordered infos, fallback, startup/error advancement, globals, busy boundaries and SD/Lua/DM cleanup passed");
}
struct unload_backend { dw4_script *vm; int calls; };
static int unload_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct unload_backend *b=user;(void)a;(void)r;(void)error;(void)cap;
    if(strcmp(method,"SYSgetArea") || n){snprintf(error,cap,"unsupported %s",method);return -1;}
    b->calls++;
    dw4_script_remove_scope(b->vm,17);
    check_marker(b->vm,1); /* nested lookup sees restored session closure */
    return 0;
}
static void test_chunk_scopes(dw4_mount *m) {
    struct unload_backend b={0};dw4_script *s=dw4_script_open(unload_service,&b);assert(s);b.vm=s;
    struct fixture base=marker(1),stage=marker(2),replacement=marker(3);
    assert(!dw4_script_load(s,"event.lua",base.bytes,base.n));
    assert(!dw4_script_load_scoped(s,17,"event.lua",stage.bytes,stage.n));check_marker(s,2);
    assert(!dw4_script_load_scoped(s,18,"event.lua",replacement.bytes,replacement.n));check_marker(s,3);
    dw4_script_remove_scope(s,17);check_marker(s,3); /* hidden owner removal */
    dw4_script_remove_scope(s,18);check_marker(s,1);
    struct fixture logical={0};ins(&logical,12,31);ins(&logical,7,11);finish(&logical);encode(&logical);
    assert(!dw4_script_load(s,"logical.lua",logical.bytes,logical.n));
    assert(!dw4_script_load_scoped(s,17,"event.lua",stage.bytes,stage.n));
    assert(!dw4_script_run(s,"logical.lua"));
    dw4_script_value resolved;assert(!dw4_script_get(s,"truth",&resolved) && resolved.number==2);
    dw4_script_remove_scope(s,17);
    assert(!dw4_script_run(s,"logical.lua"));
    assert(!dw4_script_get(s,"truth",&resolved) && resolved.number==1);
    assert(!dw4_script_load_scoped(s,17,"event.lua",stage.bytes,stage.n));
    assert(!dw4_script_load_scoped(s,18,"event.lua",replacement.bytes,replacement.n));
    assert(!dw4_script_load_scoped(s,17,"event.lua",base.bytes,base.n));check_marker(s,1);
    for(size_t i=0;i<stage.n;i++)
        assert(dw4_script_load_scoped(s,17,"event.lua",stage.bytes,i));
    check_marker(s,1);dw4_script_remove_scope(s,17);check_marker(s,3);
    dw4_script_remove_scope(s,18);check_marker(s,1);
    struct fixture active={0};call(&active,6);finish(&active);
    num(&active,3);ins(&active,19,12);encode(&active);
    assert(!dw4_script_load_scoped(s,17,"event.lua",active.bytes,active.n));
    assert(!dw4_script_run(s,"event.lua") && b.calls==1);
    dw4_script_value v;assert(!dw4_script_get(s,"truth",&v) && v.number==3);
    check_marker(s,1); /* active closure completed safely after its ref was removed */
    for(unsigned i=0;i<128;i++) {
        assert(!dw4_script_load_scoped(s,17,"event.lua",stage.bytes,stage.n));
        check_marker(s,2);dw4_script_remove_scope(s,17);check_marker(s,1);
    }
    uint32_t size;const uint8_t *blob=dw4_mount_entry(m,0,806,&size,NULL);assert(blob);
    dw4_igb g={0};assert(!dw4_igb_open(&g,blob,size,0));
    assert(!dw4_script_load(s,"snd_j_startback.lua",base.bytes,base.n));
    assert(dw4_script_load_pack_scoped(s,17,&g)==10);
    assert(dw4_script_load_pack_named_scoped(s,18,&g,"snd_j_startback.lua")==1);
    /* Failed same-owner and new-owner publication must preserve all layers. */
    uint8_t *damaged=malloc(size);assert(damaged);memcpy(damaged,blob,size);
    size_t magic;
    for(magic=0;magic+21<size;magic++)if(!memcmp(damaged+magic,"\033Lua",4))break;
    assert(magic+21<size);damaged[magic+4]=0x51;
    dw4_igb bad={0};assert(!dw4_igb_open(&bad,damaged,size,0));
    assert(dw4_script_load_pack_scoped(s,17,&bad)<0);
    assert(dw4_script_load_pack_scoped(s,19,&bad)<0);
    dw4_igb_close(&bad);free(damaged);
    assert(!dw4_script_run(s,"func.lua")); /* failed pack kept the full owner */
    dw4_script_remove_scope(s,18);
    assert(dw4_script_run(s,"snd_j_startback.lua") && strstr(dw4_script_error(s),"sd"));
    assert(dw4_script_load_pack_named_scoped(s,18,&g,"snd_j_startback.lua")==1);
    dw4_igb_close(&g);
    dw4_script_remove_scope(s,17);dw4_script_remove_scope(s,19);
    /* Named-only owner survived pack removal; its original SOUND call reaches
     * this deliberately unsupported test binding. */
    assert(dw4_script_run(s,"snd_j_startback.lua") && strstr(dw4_script_error(s),"sd"));
    dw4_script_remove_scope(s,18);
    assert(!dw4_script_run(s,"snd_j_startback.lua"));
    dw4_script_remove_scope(s,0);dw4_script_remove_scope(s,0);
    assert(dw4_script_run(s,"event.lua") && strstr(dw4_script_error(s),"not loaded"));
    dw4_script_close(s);
    puts("Lua chunk scopes: overrides, hidden removal, replacement, failed packs, active unload and 128 reloads passed");
}
static void test_random(void) {
    dw4_be_state state;dw4_be_init(&state);
    dw4_random expected;dw4_random_init(&expected);
    const int moduli[]={1,99,419,0,-1,-2,10000};
    /* Recreating the VM must not reseed the engine-owned stream. Native draws
     * interleave with script calls on exactly the same state. */
    for(unsigned pass=0;pass<3;pass++) {
        dw4_scriptengine *e=dw4_scriptengine_open(&state,NULL,NULL);assert(e);
        for(unsigned i=0;i<sizeof(moduli)/sizeof(*moduli);i++) {
            assert(dw4_random_next(&state.random)==dw4_random_next(&expected));
            struct fixture f={0};call(&f,27);num(&f,moduli[i]);
            ins(&f,2,1);ins(&f,19,28);encode(&f);
            dw4_script *s=dw4_scriptengine_vm(e);
            assert(!dw4_script_load(s,"random.lua",f.bytes,f.n));
            assert(!dw4_scriptengine_run(e,"random.lua"));
            dw4_script_value result;
            assert(!dw4_script_get(s,"roll",&result) && result.type==DW4_SCRIPT_NUMBER);
            assert(result.number==dw4_random_mod(&expected,moduli[i]));
            assert(!memcmp(&state.random,&expected,sizeof(expected)));
        }
        dw4_scriptengine_close(e);
    }
    for(unsigned invalid=0;invalid<2;invalid++) {
        dw4_scriptengine *e=dw4_scriptengine_open(&state,NULL,NULL);assert(e);
        struct fixture f={0};call(&f,27);
        if(invalid)ins(&f,4,1); /* nil modulus */
        ins(&f,2,1);ins(&f,19,28);encode(&f);
        assert(!dw4_script_load(dw4_scriptengine_vm(e),"bad-random.lua",f.bytes,f.n));
        assert(dw4_scriptengine_run(e,"bad-random.lua"));
        assert(strstr(dw4_script_error(dw4_scriptengine_vm(e)),"SYSgetRandom"));
        assert(!memcmp(&state.random,&expected,sizeof(expected)));
        dw4_scriptengine_close(e);
    }
    puts("Lua RNG: modulus-one/zero/signed calls, shared native stream and VM recreation passed");
}
struct rail_result { unsigned calls; const char *sequence; };
static int rail_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct rail_result *rail=user;(void)r;(void)error;(void)cap;
    assert(!strcmp(method,"sd") && n==5);
    assert(!strcmp(a[0].string,"MODELCTRL") && !strcmp(a[1].string,"r_drail01"));
    assert(a[2].number==0 && a[4].number==0);
    assert(!strcmp(a[3].string,rail->sequence));rail->calls++;return 0;
}
static void test_original_random(dw4_mount *m) {
    uint32_t size;const uint8_t *blob=dw4_mount_entry(m,0,417,&size,NULL);assert(blob);
    /* Test-only corpus ordinal, matching lua/09-dungeon-4/06-dng412b3_e417/028-chunk-25.lua. Production
     * named loading continues to follow beLuaData references. */
    size_t start=0,used=0;unsigned ordinal=0;
    for(size_t off=0;off+21<=size;off++)if(!memcmp(blob+off,"\033Lua",4)) {
        assert(!dw4_script_chunk_size(blob+off,size-off,&used));
        if(ordinal++==28){start=off;break;}
        off+=used-1;
    }
    assert(start && used);
    dw4_be_state state;dw4_be_init(&state);
    dw4_random expected;dw4_random_init(&expected);
    struct rail_result rail={0};
    dw4_scriptengine *e=dw4_scriptengine_open(&state,rail_service,&rail);assert(e);
    dw4_script *s=dw4_scriptengine_vm(e);
    assert(!dw4_script_load(s,"rail-random.lua",blob+start,used));
    for(unsigned i=0;i<64;i++) {
        rail.sequence=dw4_random_mod(&expected,2)?"SQ_R1MOVE2":"SQ_R1MOVE1";
        assert(!dw4_script_set(s,"g_r01mode",(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}));
        assert(!dw4_scriptengine_run(e,"rail-random.lua") && rail.calls==i+1);
        assert(!memcmp(&state.random,&expected,sizeof(expected)));
        dw4_script_value mode;assert(!dw4_script_get(s,"g_r01mode",&mode) && mode.number==1);
        assert(!dw4_scriptengine_run(e,"rail-random.lua") && rail.calls==i+1);
        assert(!memcmp(&state.random,&expected,sizeof(expected))); /* gated call consumes nothing */
    }
    dw4_scriptengine_close(e);
    puts("Lua original rail RNG: 64 random branch commands and gated repeat calls passed; model leaf controlled");
}
static int delay_binding(void *user,const char *name,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    int *delay=user;(void)r;(void)error;(void)cap;
    assert(!strcmp(name,"sd") && !strcmp(a[3].string,"EVENT"));
    assert(n==(*delay>0?5:4));
    if(n==5)assert(a[4].type==DW4_SCRIPT_NUMBER && a[4].number==*delay);
    return 0;
}
static void test_action_random(void) {
    dw4_be_state state;dw4_be_init(&state);dw4_random expected=state.random;
    dw4_action2_host a,b;dw4_action2_host_init(&a);dw4_action2_host_init(&b);
    dw4_action2_host_random(&a,&state.random,&state.action_rhythm);
    dw4_action2_host_random(&b,&state.random,&state.action_rhythm);
    dw4_action2_component rhythm={DW4_A2_WAITCHECK,"R00S",0x41200000,0,""};
    dw4_action2_host_start_program(&a,&rhythm,1,0);
    assert(!a.error && state.action_rhythm==0x41200000);
    assert(!memcmp(&expected,&state.random,sizeof expected));
    for(unsigned i=0;i<32;i++) {
        dw4_action2_component wait={DW4_A2_WAITCHECK,"Random",i&1?0x41200000:0x42700000,0,""};
        uint32_t raw=dw4_random_next(&expected);
        unsigned rem=i&1?raw:raw%5000;
        ee_f32 frames=ee_f32_add(state.action_rhythm,ee_f32_div(ee_f32_from_u32(rem),0x42c80000));
        int64_t duration=dw4_model_ai_duration(frames);
        dw4_action2_host *host=i&1?&a:&b;
        dw4_action2_host_start_program(host,&wait,1,0);
        assert(!host->error && dw4_action2_host_timer_present(host));
        int timer=DW4_A2_BASE+0x900;
        uint64_t got=(uint32_t)host->api.base.peek(host,timer+A2_T_DURATION,4);
        got|=(uint64_t)(uint32_t)host->api.base.peek(host,timer+A2_T_DURATION+4,4)<<32;
        assert((int64_t)got==duration);
        assert(!memcmp(&expected,&state.random,sizeof expected));
    }
    dw4_action2_host_close(&a);dw4_action2_host_close(&b);
    puts("Action2 RNG: shared rhythm without draw, random/zero-span waits and shared stream passed");
}
static void test_original_model(dw4_mount *mount) {
    dw4_be_state state;dw4_be_init(&state);
    dw4_random expected=state.random;
    dw4_scriptengine *e=dw4_scriptengine_open(&state,NULL,NULL);assert(e);
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_igb pack={0};assert(blob && !dw4_igb_open(&pack,blob,size,0));
    assert(dw4_script_load_pack_named(dw4_scriptengine_vm(e),&pack,"aim_n_digilff.lua")==1);
    dw4_igb_close(&pack);
    dw4_script_model m={.ram_no=2,.hp=100,.max_hp=100,.info_name="n_digilff",
        .call_name="WPos",.target_enabled=1};
    for(unsigned i=0;i<128;i++) {
        int hp=m.hp;
        if(hp==100)hp=1;
        if(hp==1)hp++;
        else if(hp==3)hp--;
        else hp+=dw4_random_mod(&expected,2)==0?1:-1;
        assert(!dw4_scriptengine_model_event(e,42,"aim_n_digilff.lua",&m));
        assert(m.hp==hp && m.target[0]==(hp==1?130:hp==2?20:60));
        assert(m.target[1]==10 && m.target[2]==(hp==3?-10:-35));
        assert(!memcmp(&expected,&state.random,sizeof expected));
        /* Native AI and Lua waypoint draws use one stream. */
        assert(dw4_random_next(&expected)==dw4_random_next(&state.random));
    }
    /* Retail MDLisCallName returns numeric zero. Lua 4 treats it as truthy,
     * so this authored `if` still executes for a different call name. */
    m.call_name="Other";int hp=m.hp;
    hp=hp==1?2:hp==3?2:hp+(dw4_random_mod(&expected,2)==0?1:-1);
    assert(!dw4_scriptengine_model_event(e,42,"aim_n_digilff.lua",&m));
    assert(m.hp==hp && !memcmp(&expected,&state.random,sizeof expected));
    dw4_scriptengine_close(e);
    puts("Lua model: original guide WPos endpoint/middle branches and shared native stream passed");
}
struct model_backend { dw4_scriptengine *engine; int depth,calls,unload; };
static int model_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct model_backend *b=user;(void)r;(void)error;(void)cap;
    assert(dw4_scriptengine_scope(b->engine)==(b->depth?43:42));
    assert(!strcmp(method,"sd") && n==4 && a[2].number==(b->depth?7:2));
    assert(!strcmp(a[1].string,b->depth?"inner":"outer"));b->calls++;
    if(b->unload){dw4_scriptengine_remove_scope(b->engine,42);return 0;}
    if(!b->depth) {
        dw4_script_model inner={.ram_no=7,.hp=20,.max_hp=10,.info_name="inner"};
        b->depth=1;
        assert(!dw4_scriptengine_model_event(b->engine,43,"nested.lua",&inner));
        b->depth=0;assert(inner.hp==23); /* no maximum-HP clamp */
    }
    return 0;
}
static void test_model_lifetime(void) {
    dw4_be_state state;dw4_be_init(&state);
    struct model_backend b={0};
    dw4_scriptengine *e=dw4_scriptengine_open(&state,model_service,&b);assert(e);b.engine=e;
    struct fixture nested={0};call(&nested,29);ins(&nested,7,25);finish(&nested);
    call(&nested,30);num(&nested,3);finish(&nested);encode(&nested);
    assert(!dw4_script_load(dw4_scriptengine_vm(e),"nested.lua",nested.bytes,nested.n));
    dw4_script_model m={.ram_no=2,.hp=100,.info_name="outer"};
    assert(!dw4_scriptengine_model_event(e,42,"nested.lua",&m));
    assert(m.hp==103 && b.calls==2); /* outer snapshot restored after nested callback */
    struct fixture group={0};sd_id(&group,9);call(&group,3);finish(&group);encode(&group);
    assert(!dw4_script_load(dw4_scriptengine_vm(e),"group.lua",group.bytes,group.n));
    assert(!dw4_scriptengine_model_event(e,42,"group.lua",&m));
    assert(dw4_scriptengine_pending(e)==1);
    dw4_scriptengine_remove_scope(e,42);
    assert(!dw4_scriptengine_tick(e) && !dw4_scriptengine_pending(e) && b.calls==2);
    m.hp=2147483647;
    assert(!dw4_scriptengine_model_event(e,42,"nested.lua",&m));
    assert(m.hp==0 && b.calls==4); /* wrapping addition, then signed clamp */
    assert(!dw4_script_load_scoped(dw4_scriptengine_vm(e),42,"nested.lua",nested.bytes,nested.n));
    b.unload=1;int hp=m.hp;
    assert(dw4_scriptengine_model_event(e,42,"nested.lua",&m));
    assert(m.hp==hp && strstr(dw4_scriptengine_error(e),"scope unloaded"));
    dw4_scriptengine_close(e);
    struct backend receiver={0};
    e=dw4_scriptengine_open(&state,binding,&receiver);assert(e);
    assert(!dw4_script_load(dw4_scriptengine_vm(e),"group.lua",group.bytes,group.n));
    assert(!dw4_scriptengine_model_event(e,42,"group.lua",&m));
    assert(!dw4_scriptengine_run(e,"group.lua")); /* session scope zero */
    dw4_scriptengine_remove_scope(e,42);
    assert(!dw4_scriptengine_tick(e) && receiver.events==1 && !dw4_scriptengine_pending(e));
    dw4_scriptengine_close(e);
    puts("Lua model lifetime: nested context, HP overflow, scoped cancellation/session survival and active unload passed");
}
static void test_dm_delays(void) {
    const int delays[]={-10,0,1};
    for(size_t i=0;i<sizeof(delays)/sizeof(*delays);i++) {
        int delay=delays[i];dw4_be_state state;dw4_be_init(&state);
        dw4_scriptengine *e=dw4_scriptengine_open(&state,delay_binding,&delay);assert(e);
        struct fixture f={0};call(&f,1);ins(&f,7,7);ins(&f,4,1);num(&f,0);
        ins(&f,7,8);num(&f,delay);finish(&f);call(&f,3);finish(&f);encode(&f);
        assert(!dw4_script_load(dw4_scriptengine_vm(e),"delay.lua",f.bytes,f.n));
        assert(!dw4_scriptengine_run(e,"delay.lua") && !dw4_scriptengine_tick(e));
        printf("Lua DM delay %d: %s\n",delay,delay>0?"queued":"immediate");
        dw4_scriptengine_close(e);
    }
}
static void run(struct fixture *f) { call(f,3); finish(f); }
struct switch_backend { int selected,missing,window; unsigned queries; struct backend trace; };
static int switch_binding(void *user,const char *name,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct switch_backend *b=user;
    if (!strcmp(name,"querySD") && !strcmp(a[3].string,"VALUE")) {
        b->queries++;
        r->type=b->missing?DW4_SCRIPT_NIL:DW4_SCRIPT_NUMBER; r->number=b->selected; return 0;
    }
    if (!strcmp(name,"querySD") && !strcmp(a[0].string,"SUBWND")) {
        assert(n==4 && a[1].type==DW4_SCRIPT_NIL && a[2].number==0 && !strcmp(a[3].string,"ISRUN"));
        b->queries++; r->type=b->missing?DW4_SCRIPT_NIL:DW4_SCRIPT_NUMBER; r->number=b->window; return 0;
    }
    return binding(&b->trace,name,a,n,r,error,cap);
}
static void switch_query(struct fixture *f) {
    call(f,14); ins(f,7,7); ins(f,4,1); num(f,0); ins(f,7,20); finish(f);
}
static void case_id(struct fixture *f,int id) { call(f,15); num(f,id); finish(f); }
static void count_query(struct fixture *f) { call(f,18); ins(f,2,1); ins(f,19,19); }
static void test_switches(void) {
    const int selections[]={-7,0,2,99,2};
    for (size_t i=0;i<sizeof(selections)/sizeof(*selections);i++) {
        dw4_be_state state; dw4_be_init(&state);
        struct switch_backend b={.selected=selections[i],.missing=i==4};
        dw4_scriptengine *e=dw4_scriptengine_open(&state,switch_binding,&b); assert(e);
        dw4_script *s=dw4_scriptengine_vm(e);
        struct fixture f={0};
        case_id(&f,123); /* ignored outside a switch */
        switch_query(&f); switch_query(&f); /* nested switch ignored */
        case_id(&f,-7); sd_id(&f,1);
        case_id(&f,0); sd_id(&f,2);
        case_id(&f,2); sd_id(&f,3);
        case_id(&f,2); sd_id(&f,4); /* first matching case wins */
        call(&f,16); finish(&f);
        call(&f,17); ins(&f,7,12); num(&f,42); finish(&f);
        sd_id(&f,9); run(&f); count_query(&f); encode(&f);
        assert(!dw4_script_load(s,"switch.lua",f.bytes,f.n));
        assert(!dw4_scriptengine_run(e,"switch.lua"));
        dw4_script_value v;
        assert(!dw4_script_get(s,"count",&v) && v.number==1 && !b.queries);
        assert(!dw4_scriptengine_tick(e) && !dw4_scriptengine_pending(e));
        assert(b.queries==1);
        unsigned expected=i<3?2:1;
        assert(b.trace.events==expected && b.trace.order[expected-1]==9);
        if (i<3) assert(b.trace.order[0]==(int)i+1);
        printf("Lua switch %zu:",i);
        for (unsigned j=0;j<b.trace.events;j++) printf(" %d",b.trace.order[j]);
        printf("\n");
        struct fixture count={0}; count_query(&count); encode(&count);
        assert(!dw4_script_load(s,"count.lua",count.bytes,count.n));
        b.missing=0;
        for (int window=0;window<3;window++) {
            b.window=window;
            assert(!dw4_scriptengine_run(e,"count.lua"));
            assert(!dw4_script_get(s,"count",&v) && v.number==(window?-1:0));
        }
        dw4_scriptengine_close(e);
    }
    dw4_be_state state; dw4_be_init(&state); struct switch_backend b={0};
    dw4_scriptengine *e=dw4_scriptengine_open(&state,switch_binding,&b); assert(e);
    struct fixture open={0},close={0};
    switch_query(&open); case_id(&open,0); sd_id(&open,1); run(&open); encode(&open);
    call(&close,16); finish(&close); run(&close); encode(&close);
    dw4_script *s=dw4_scriptengine_vm(e);
    assert(!dw4_script_load(s,"open.lua",open.bytes,open.n));
    assert(!dw4_script_load(s,"close.lua",close.bytes,close.n));
    assert(!dw4_scriptengine_run(e,"open.lua") && !dw4_scriptengine_pending(e));
    assert(!dw4_scriptengine_tick(e) && !b.queries);
    assert(!dw4_scriptengine_run(e,"close.lua") && dw4_scriptengine_pending(e)==1);
    assert(!dw4_scriptengine_tick(e) && b.trace.events==1 && b.trace.order[0]==1);
    /* A blocked wait in a selected arm resumes without selecting again. */
    struct fixture wait={0}; switch_query(&wait); case_id(&wait,0);
    call(&wait,2); ins(&wait,7,7); ins(&wait,4,1); num(&wait,0);
    ins(&wait,7,9); ins(&wait,7,10); finish(&wait);
    sd_id(&wait,2); case_id(&wait,1); sd_id(&wait,3);
    call(&wait,16); finish(&wait); run(&wait); encode(&wait);
    assert(!dw4_script_load(s,"wait.lua",wait.bytes,wait.n));
    assert(!dw4_scriptengine_run(e,"wait.lua"));
    assert(!dw4_scriptengine_tick(e) && dw4_scriptengine_pending(e)==1);
    unsigned queries=b.queries;
    assert(!dw4_scriptengine_tick(e) && b.queries==queries && b.trace.events==1);
    b.trace.tick=2;
    assert(!dw4_scriptengine_tick(e) && !dw4_scriptengine_pending(e));
    assert(b.queries==queries && b.trace.events==2 && b.trace.order[1]==2);
    dw4_scriptengine_close(e);
}
static void test_counts(void) {
    const int counts[]={0,1,3},windows[]={0,1,2,256};
    for (size_t c=0;c<3;c++) for (int exists=0;exists<2;exists++) for (size_t w=0;w<4;w++) {
        dw4_be_state state; dw4_be_init(&state);
        struct switch_backend b={.missing=!exists,.window=windows[w]};
        dw4_scriptengine *e=dw4_scriptengine_open(&state,switch_binding,&b); assert(e);
        dw4_script *s=dw4_scriptengine_vm(e);
        struct fixture f={0};
        for (int i=0;i<counts[c];i++) { sd_id(&f,i); run(&f); }
        count_query(&f); encode(&f);
        assert(!dw4_script_load(s,"count.lua",f.bytes,f.n));
        assert(!dw4_scriptengine_run(e,"count.lua"));
        dw4_script_value v; assert(!dw4_script_get(s,"count",&v));
        int expected=counts[c]?counts[c]:(exists && (windows[w]&255)?-1:0);
        assert(v.type==DW4_SCRIPT_NUMBER && v.number==expected);
        assert(b.queries==(counts[c]?0u:1u));
        printf("Lua count %d %d %d: %d\n",counts[c],exists,windows[w],(int)v.number);
        dw4_scriptengine_close(e);
    }
}
static void test_events(void) {
    dw4_be_state state; dw4_be_init(&state); struct backend b={0};
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&b); assert(e);
    dw4_script *s=dw4_scriptengine_vm(e);
    struct fixture event={0},queue={0};
    call(&event,5); num(&event,9); num(&event,1); finish(&event); sd_id(&event,0); run(&event); encode(&event);
    call(&queue,4); ins(&queue,7,11); finish(&queue); run(&queue); encode(&queue);
    assert(!dw4_script_load(s,"event.lua",event.bytes,event.n));
    assert(!dw4_script_load(s,"queue.lua",queue.bytes,queue.n));
    assert(!dw4_script_run(s,"queue.lua"));
    assert(!b.calls && state.counter[9]==0 && dw4_scriptengine_pending(e)==1);
    assert(!dw4_scriptengine_tick(e));
    assert(state.counter[9]==1 && !b.events && dw4_scriptengine_pending(e)==1);
    assert(!dw4_scriptengine_tick(e));
    assert(b.events==1 && !dw4_scriptengine_pending(e));
    assert(!dw4_scriptengine_tick(e) && b.events==1);
    /* Replacing a named closure fails without losing the prior closure. */
    for (size_t i=0;i<event.n;i++) assert(dw4_script_load(s,"event.lua",event.bytes,i));
    assert(!dw4_script_run(s,"event.lua"));
    assert(!dw4_scriptengine_tick(e) && b.events==2);
    assert(dw4_script_run(s,"absent.lua") && strstr(dw4_script_error(s),"not loaded"));
    assert(!dw4_script_set(s,"counterValue",(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}));
    dw4_script_value v;
    assert(!dw4_script_get(s,"counterValue",&v) && v.type==DW4_SCRIPT_NUMBER && v.number==0);
    struct fixture truth={0};
    call(&truth,6); ins(&truth,2,1); /* one numeric result, area 0 */
    ins(&truth,38,33554431+3); /* numeric zero is truthy: jump to PUSHINT 1 */
    num(&truth,-1); ins(&truth,19,12); ins(&truth,42,33554431+2);
    num(&truth,1); ins(&truth,19,12); encode(&truth);
    assert(!dw4_script_load(s,"truth.lua",truth.bytes,truth.n));
    assert(!dw4_script_run(s,"truth.lua"));
    assert(!dw4_script_get(s,"truth",&v) && v.type==DW4_SCRIPT_NUMBER && v.number==1);
    struct fixture special={0}; call(&special,13); num(&special,1000); finish(&special); encode(&special);
    assert(!dw4_script_load(s,"special.lua",special.bytes,special.n));
    assert(dw4_script_run(s,"special.lua") && strstr(dw4_script_error(s),"FLGisOn"));
    struct fixture older={0}, newer={0};
    sd_id(&older,1); run(&older); encode(&older);
    sd_id(&newer,2); run(&newer); encode(&newer);
    assert(!dw4_script_load(s,"older.lua",older.bytes,older.n));
    assert(!dw4_script_load(s,"newer.lua",newer.bytes,newer.n));
    assert(!dw4_script_run(s,"older.lua") && !dw4_script_run(s,"newer.lua"));
    assert(!dw4_scriptengine_tick(e) && b.events==4);
    assert(b.order[2]==2 && b.order[3]==1); /* retail newest group first */
    assert(!dw4_scriptengine_queue_event(e,"event.lua"));
    assert(!dw4_scriptengine_tick(e) && b.events==4);
    assert(!dw4_scriptengine_tick(e) && b.events==5);
    dw4_scriptengine_close(e);
}
struct service_clock { uint64_t now; unsigned calls; struct backend *backend; };
static void advance_service(void *user,uint64_t ns) {
    struct service_clock *c=user;
    assert(ns>c->now);c->now=ns;c->calls++;
    c->backend->tick=c->calls; /* DM observes services after the world store. */
}
static void fail_service(void *user,uint64_t ns) {
    (void)ns;((dw4_simulation *)user)->failed=1;
}
static void test_simulation(void) {
    dw4_be_state state;dw4_be_init(&state);struct backend b={0};
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&b);assert(e);
    struct fixture event={0};
    call(&event,2);ins(&event,7,7);ins(&event,4,1);num(&event,3);
    ins(&event,7,9);ins(&event,7,10);finish(&event);
    sd_id(&event,3);run(&event);encode(&event);
    assert(!dw4_script_load(dw4_scriptengine_vm(e),"event.lua",event.bytes,event.n));
    assert(!dw4_scriptengine_run(e,"event.lua"));
    struct service_clock service={0,0,&b};dw4_simulation s;
    dw4_simulation_init(&s,e,&service,advance_service);
    uint64_t host=1000000000;
    assert(dw4_simulation_due(&s,host)==1);
    assert(!dw4_simulation_step(&s) && !b.events); /* receiver wait retains cursor */
    assert(dw4_scriptengine_pending(e)==1 && b.queries==1);
    for (unsigned reason=1;reason<=4;reason<<=1) {
        uint64_t world=dw4_clock_host_world(&s.clock);unsigned calls=service.calls;
        dw4_simulation_hold(&s,reason,host);
        host+=60000000000ULL;
        assert(!dw4_simulation_due(&s,host));
        assert(dw4_simulation_step(&s)<0 && !b.events && b.queries==1);
        assert(dw4_clock_host_world(&s.clock)==world && service.calls==calls);
        dw4_simulation_hold(&s,0,host);
        assert(!dw4_simulation_due(&s,host));
    }
    host+=16666667;
    assert(dw4_simulation_due(&s,host)==1);
    assert(!dw4_simulation_step(&s) && b.events==1);
    assert(strstr(b.log,"EVENT@2;") && b.queries==2);
    /* A 100 ms rendering stall advances six ticks, no time loss or draw calls. */
    host+=100000000;assert(dw4_simulation_due(&s,host)==6);
    while(s.due) assert(!dw4_simulation_step(&s));
    assert(s.ticks==8 && service.calls==8);
    assert(service.now==8ULL*1000000000/60);
    /* Discard queued active backlog and a fractional frame on hold entry. */
    host+=110000000;assert(dw4_simulation_due(&s,host)==6);
    dw4_simulation_hold(&s,DW4_HOLD_PAUSE|DW4_HOLD_DISCONNECT,host);
    dw4_simulation_hold(&s,DW4_HOLD_PAUSE,host+1000000000);
    assert(!dw4_simulation_due(&s,host+2000000000));
    dw4_simulation_hold(&s,0,host+2000000000);
    assert(!dw4_simulation_due(&s,host+2000000000));
    /* A failed service stops this tick before DM queries or dispatch. */
    assert(!dw4_scriptengine_run(e,"event.lua"));
    unsigned queries=b.queries;
    dw4_simulation_init(&s,e,&s,fail_service);s.due=1;
    assert(dw4_simulation_step(&s) && b.queries==queries && dw4_scriptengine_pending(e)==1);
    dw4_scriptengine_close(e);
    puts("Lua live simulation: 60 Hz, service/DM order, nested holds, resume and render stalls passed");
}
static void test_title(dw4_mount *m,int area) {
    uint32_t size; const uint8_t *blob=dw4_mount_entry(m,0,806,&size,NULL);
    dw4_igb g={0}; dw4_be_state state; dw4_be_init(&state);
    struct backend b={0}; b.area=area;
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&b); assert(e);
    dw4_script *s=dw4_scriptengine_vm(e);
    assert(blob && !dw4_igb_open(&g,blob,size,0));
    assert(dw4_script_load_pack(s,&g)==10 && !b.calls);
    assert(!dw4_script_run(s,"func.lua"));
    assert(!dw4_script_run(s,"first.lua"));
    assert(dw4_scriptengine_pending(e)==1 && !b.title && !b.delay);
    b.log[0]=0;
    for (b.tick=0;b.tick<6;b.tick++) {
        assert(!dw4_scriptengine_tick(e));
        if (b.tick<5) assert(!b.title && dw4_scriptengine_pending(e)==1);
    }
    assert(b.title==1 && b.delay==1 && !dw4_scriptengine_pending(e));
    assert(b.queries==8);
    assert(strstr(b.log,"CAMERA:SETBOXCAMERA@2;SOUND:PLAYatPAUSE@2;SOUND:PAUSEOFF@2;"));
    assert(strstr(b.log,"TITLE2:RUN@5;"));
    printf("Lua title trace area %d: %s\n",area,b.log);
    /* A malformed staged pack cannot replace any previously loaded closures. */
    uint8_t *damaged=malloc(size); assert(damaged); memcpy(damaged,blob,size);
    size_t magic;
    for (magic=0;magic+21<size;magic++) if (!memcmp(damaged+magic,"\033Lua",4)) break;
    assert(magic+21<size); damaged[magic+4]=0x51;
    dw4_igb bad={0}; assert(!dw4_igb_open(&bad,damaged,size,0));
    assert(dw4_script_load_pack(s,&bad)<0);
    dw4_igb_close(&bad); free(damaged);
    /* Original script events and globals survive after releasing pack views. */
    dw4_igb_close(&g);
    assert(!dw4_script_run(s,"snd_j_startback.lua"));
    assert(!dw4_script_call(s,"funcFirstLayerSet",NULL,0));
    /* Original gameStart loops execute; test backend reports the first missing
     * service once, including when the original _ERRORMESSAGE calls MsgBox. */
    int rc=dw4_scriptengine_run(e,"gameStart.lua");
    if (area==1) {
        if (!rc) fprintf(stderr,"gameStart did not fail: calls %u counter %d flag81 %u\n",b.calls,state.counter[2],(uint8_t)state.flag[82]);
        assert(rc && strstr(dw4_script_error(s),"SYSctlFlagFolder"));
        assert(state.counter[2]==0 && (uint8_t)state.flag[82]==0);
        assert((uint8_t)state.flag[24]==0 && (uint8_t)state.flag[34]==0);
    } else assert(rc && strstr(dw4_script_error(s),"SYSctlFlagFolder"));
    assert(dw4_scriptengine_tick(e)); /* failed event cannot dispatch partial work */
    dw4_scriptengine_close(e);
    printf("Lua title area %d: bytecode, queued waits, delay 240, native event and error checks passed\n",area);
}
struct integrated {
    dw4_scriptservices *sd;
    dw4_simulation *simulation;
    uint64_t now,pad_time,music_time;
    unsigned tick,pad,music,title,queries;
    int area;
    dw4_title_services *real;
};
static int integrated_receiver(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct integrated *b=user;(void)error;(void)cap;
    if(!strcmp(method,"querySD")) {
        b->queries++;r->type=DW4_SCRIPT_NUMBER;
        r->number=!strcmp(a[3].string,"ISDEMOCAMERA")?b->tick<3:b->tick<6;
    } else if(!strcmp(a[3].string,"PAUSEOFF")) {
        assert(n==5 && !strcmp(a[4].string,"ST_CHARA"));
        b->music++;b->music_time=b->now;
    } else if(!strcmp(a[3].string,"PADINPUT")) {
        assert(n==5 && !strcmp(a[4].string,"ENABLE"));
        b->pad++;b->pad_time=b->now;
    } else if(!strcmp(a[0].string,"TITLE2"))b->title++;
    return 0;
}
static int integrated_binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct integrated *b=user;
    if(!strcmp(method,"SYSgetArea")) { r->type=DW4_SCRIPT_NUMBER;r->number=b->area;return 0; }
    return dw4_scriptservices_call(b->sd,method,a,n,r,error,cap);
}
static void integrated_clock(void *user,uint64_t ns) {
    struct integrated *b=user;b->now=ns;
    dw4_title_services_tick(b->real,ns);
    if(dw4_scriptservices_tick(b->sd,ns))b->simulation->failed=1;
}
static void test_real_title(dw4_mount *mount,int area)
{
    dw4_be_state state;dw4_be_init(&state);
    dw4_simulation simulation;dw4_title_host host={0};
    dw4_title_host_close(&host);
    dw4_title_host_init(&host,0,1);
    dw4_frontlayer *layer=dw4_frontlayer_open(mount);assert(layer);
    struct integrated b={.sd=dw4_scriptservices_open(),.simulation=&simulation,.area=area};assert(b.sd);
    b.real=dw4_title_services_open(b.sd,1,&host,layer);assert(b.real);
    /* Sound/layer/input/title RUN are explicit controlled leaves here.
     * Both kinds of completion query go to real model/camera storage. */
    const char *categories[]={"SOUND","TITLE2","SWITCHCTRL","STAGECTL","LAYERCTL"};
    for(unsigned i=0;i<sizeof(categories)/sizeof(*categories);i++)
        assert(dw4_scriptservices_register(b.sd,0,categories[i],NULL,-1,1,integrated_receiver,&b));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,integrated_binding,&b);assert(e);
    uint32_t size;const uint8_t *data=dw4_mount_entry(mount,0,806,&size,NULL);dw4_igb g={0};
    assert(data && !dw4_igb_open(&g,data,size,0));
    assert(dw4_script_load_pack(dw4_scriptengine_vm(e),&g)==10);dw4_igb_close(&g);
    assert(!dw4_scriptengine_run(e,"func.lua") && !dw4_scriptengine_run(e,"first.lua"));
    dw4_simulation_init(&simulation,e,&b,integrated_clock);
    unsigned ready=0;Dw4TitleInput input={0};
    for(b.tick=1;b.tick<=320;b.tick++) {
        simulation.due=1;
        int rc=dw4_simulation_step(&simulation);
        if(rc)fprintf(stderr,"real first.lua: %s / %s\n",dw4_scriptengine_error(e),dw4_scriptservices_error(b.sd));
        assert(!rc);
        if(b.title && !ready)ready=b.tick;
        dw4_title_host_set_clock(&host,(int64_t)b.now);
        dw4_title_host_tick(&host,&input,0); /* model update follows DM, even before TITLE2 RUN */
        assert(!host.error && !b.queries);
        if(b.tick==65) {
            int age=dw4_title_host_model(&host,T_j_startback)->age;
            dw4_simulation_hold(&simulation,DW4_HOLD_FOCUS,0);
            assert(!dw4_simulation_due(&simulation,10000000000ULL));
            assert(dw4_simulation_step(&simulation) && age==dw4_title_host_model(&host,T_j_startback)->age);
            dw4_simulation_hold(&simulation,0,10000000000ULL);
        }
    }
    assert(ready==271 && b.title==1 && b.music==1 && b.pad==1);
    assert(b.music_time==5033333333ULL && !dw4_scriptengine_pending(e));
    assert(dw4_title_host_model(&host,T_j_startback)->query_sequence==DW4_TITLE_SQ_WAIT);
    /* Removing receivers invalidates later queries and cancels owned messages. */
    dw4_scriptservices_scope(b.sd,1);
    dw4_script_value delayed[]={ {DW4_SCRIPT_STRING,0,"MODELCTRL",9},
        {DW4_SCRIPT_STRING,0,"j_startback",11},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,"SQ_OPEN",7},
        {DW4_SCRIPT_NUMBER,10,NULL,0} },result={0};char diagnostic[256];
    assert(!dw4_scriptservices_call(b.sd,"sd",delayed,6,&result,diagnostic,sizeof(diagnostic)));
    assert(dw4_scriptservices_pending(b.sd)==1);
    dw4_title_services_close(b.real);b.real=NULL;
    dw4_scriptservices_remove_scope(b.sd,1);
    assert(!dw4_scriptservices_pending(b.sd));
    dw4_script_value a[]={ {DW4_SCRIPT_STRING,0,"MODELCTRL",9},
        {DW4_SCRIPT_STRING,0,"j_startback",11},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"ISRUN",5}, {DW4_SCRIPT_NIL,0,NULL,0} },r={0};char error[256];
    assert(!dw4_scriptservices_call(b.sd,"querySD",a,4,&r,error,sizeof(error)) && r.type==DW4_SCRIPT_NIL);
    dw4_title_host_close(&host);
    dw4_title_host_init(&host,0,1);
    b.real=dw4_title_services_open(b.sd,1,&host,layer);assert(b.real);
    dw4_title_services_tick(b.real,b.now+1000000000);
    assert(!dw4_scriptservices_tick(b.sd,b.now+1000000000));
    assert(!dw4_title_host_model(&host,T_j_startback)->active); /* stale GENERATE cannot cross re-entry */
    dw4_title_services_close(b.real);b.real=NULL;
    printf("Lua original first.lua area %d: actual camera/model waits, RUN tick %u, held state passed\n",area,ready);
    dw4_title_host_close(&host);dw4_scriptengine_close(e);dw4_scriptservices_close(b.sd);dw4_frontlayer_close(layer);
}
static void test_window_wait(dw4_mount *mount)
{
    uint32_t size;const uint8_t *data=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_scene scene;assert(data && !dw4_scene_load(&scene,data,size));
    dw4_lobbyui *ui=dw4_lobbyui_open(mount,&scene,data,size);assert(ui);
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    assert(dw4_scriptservices_register(sd,2,"MODELCTRL","i_talkwn",0,1,dw4_lobbyui_script_service,ui));
    dw4_be_state state;dw4_be_init(&state);
    dw4_scriptengine *e=dw4_scriptengine_open(&state,dw4_scriptservices_call,sd);assert(e);
    struct fixture f={0};call(&f,2);ins(&f,7,21);ins(&f,7,22);num(&f,0);
    ins(&f,7,24);ins(&f,7,25);ins(&f,7,10);finish(&f);run(&f);encode(&f);
    assert(!dw4_script_load(dw4_scriptengine_vm(e),"window-wait.lua",f.bytes,f.n));
    dw4_lobbyui_start(ui);
    assert(!dw4_scriptengine_run(e,"window-wait.lua"));
    for(unsigned i=0;i<16;i++) {
        assert(!dw4_scriptengine_tick(e) && dw4_scriptengine_pending(e)==1);
        dw4_lobbyui_tick(ui,0);
    }
    assert(!dw4_scriptengine_tick(e) && !dw4_scriptengine_pending(e));
    assert(dw4_lobbyui_message(ui)==39);
    dw4_script_value a[]={ {DW4_SCRIPT_STRING,0,"MODELCTRL",9},
        {DW4_SCRIPT_STRING,0,"i_talkwn",8},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"ISRUN",5}, {DW4_SCRIPT_NIL,0,NULL,0} },r={0};char error[256];
    for(unsigned i=0;i<3;i++)dw4_lobbyui_tick(ui,1); /* actual group close */
    for(unsigned i=0;i<16;i++) {
        assert(!dw4_scriptservices_call(sd,"querySD",a,4,&r,error,sizeof(error)) && r.number==1);
        dw4_lobbyui_tick(ui,0);
    }
    /* Next group starts immediately, so ISRUN stays true; CLOSEL ends.
     * A query must not mistake model survival for action completion. */
    a[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"ISSEQNAME",9};
    a[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,"SQ_CLOSEL",9};
    assert(!dw4_scriptservices_call(sd,"querySD",a,5,&r,error,sizeof(error)) && r.number==0);
    dw4_scriptengine_close(e);dw4_scriptservices_remove_scope(sd,2);
    dw4_scriptservices_close(sd);dw4_lobbyui_close(ui);dw4_scene_close(&scene);
    puts("Lua window wait: actual 16-update OPENL completion and draw-independent queries passed");
}
static void test_integrated_title(dw4_mount *m,int area) {
    dw4_be_state state;dw4_be_init(&state);
    dw4_simulation simulation;
    struct integrated b={.sd=dw4_scriptservices_open(),.simulation=&simulation,.area=area};assert(b.sd);
    const char *categories[]={"MODELCTRL","CAMERA","SOUND","TITLE2","SWITCHCTRL","STAGECTL","LAYERCTL"};
    for(size_t i=0;i<sizeof(categories)/sizeof(*categories);i++)
        assert(dw4_scriptservices_register(b.sd,0,categories[i],NULL,-1,1,integrated_receiver,&b));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,integrated_binding,&b);assert(e);
    uint32_t size;const uint8_t *data=dw4_mount_entry(m,0,806,&size,NULL);dw4_igb g={0};
    assert(data && !dw4_igb_open(&g,data,size,0));
    dw4_script *vm=dw4_scriptengine_vm(e);
    assert(dw4_script_load_pack(vm,&g)==10);dw4_igb_close(&g);
    assert(!dw4_scriptengine_run(e,"func.lua"));
    int rc=dw4_scriptengine_run(e,"first.lua");
    if(rc)fprintf(stderr,"integrated first.lua: %s\n",dw4_scriptengine_error(e));
    assert(!rc);
    assert(dw4_scriptservices_pending(b.sd)==1); /* original direct PADINPUT delay 30 */
    dw4_simulation_init(&simulation,e,&b,integrated_clock);
    for(b.tick=1;b.tick<=243;b.tick++) {
        simulation.due=1;assert(!dw4_simulation_step(&simulation));
        if(b.tick<30)assert(!b.pad);
        if(b.tick<243)assert(!b.music);
        if(b.tick==3) {
            /* Hold after publication: neither world time nor expiry advances. */
            uint64_t now=b.now;unsigned queries=b.queries;
            dw4_simulation_hold(&simulation,DW4_HOLD_FOCUS,0);
            assert(!dw4_simulation_due(&simulation,10000000000ULL));
            assert(dw4_simulation_step(&simulation) && b.now==now && b.queries==queries);
            dw4_simulation_hold(&simulation,0,10000000000ULL);
            assert(!dw4_simulation_due(&simulation,10000000000ULL));
        }
    }
    assert(b.pad==1 && b.pad_time==500000000 && b.music==1 && b.music_time==4050000000ULL);
    assert(b.title==1 && !dw4_scriptengine_pending(e) && !dw4_scriptservices_pending(b.sd));
    printf("Lua integrated title %d: real queued PADINPUT at 500000000 ns, PAUSEOFF at 4050000000 ns, held clocks passed\n",area);
    dw4_scriptengine_close(e);dw4_scriptservices_close(b.sd);
}
static void audit(dw4_mount *m) {
    dw4_script *s=dw4_script_open(NULL,NULL); assert(s);
    unsigned chunks=0,entries=0,retail_chunks=0;
    dw4_script *retail=dw4_script_open(NULL,NULL);assert(retail);
    for (uint32_t e=0;e<m->parts[0].count;e++) {
        uint32_t n; const uint8_t *p=dw4_mount_entry(m,0,(int)e,&n,NULL);
        if (!p) continue;
        unsigned found=0;
        for (size_t off=0;off+21<=n;off++) if (!memcmp(p+off,"\033Lua",4)) {
            size_t used;
            assert(!dw4_script_chunk_size(p+off,n-off,&used));
            char name[64]; snprintf(name,sizeof(name),"%u:%zu",e,off);
            assert(!dw4_script_load(s,name,p+off,used));
            chunks++; found++; off+=used-1;
        }
        entries+=found!=0;
        if(found) {
            dw4_igb pack={0};assert(!dw4_igb_open(&pack,p,n,0));
            assert(!dw4_script_remove_all(retail) && !dw4_script_recreate(retail));
            int collected=dw4_script_collect_pack(retail,&pack);assert(collected>0);
            retail_chunks+=(unsigned)collected;dw4_igb_close(&pack);
        }
    }
    assert(chunks>1000);
    printf("Lua corpus: loaded %u original chunks in %u NDMW entries, without executing\n",chunks,entries);
    printf("Lua retail corpus: collected %u referenced rows in %u ordered scene libraries, without executing\n",retail_chunks,entries);
    assert(retail_chunks==7300);dw4_script_close(retail);
    dw4_script_close(s);
}
int main(int argc,char **argv) {
    object_values();
    dw4_mount m={0}; assert(!dw4_mount_open(&m,argc>1?argv[1]:"../local/extracted"));
    test_ownership(&m);
    if(argc>2 && !strcmp(argv[2],"--ownership")){dw4_mount_close(&m);return 0;}
    test_chunk_scopes(&m);
    test_events();
    test_random();
    test_original_random(&m);
    test_action_random();
    test_original_model(&m);
    test_model_lifetime();
    test_dm_delays();
    test_switches();
    test_counts();
    test_simulation();
    test_title(&m,0); test_title(&m,1); audit(&m);
    test_integrated_title(&m,0);test_integrated_title(&m,1);
    test_real_title(&m,0);test_real_title(&m,1);test_window_wait(&m);
    dw4_mount_close(&m); return 0;
}
