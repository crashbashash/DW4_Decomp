#include "dw4/scriptengine.h"
#include "dw4/filelist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

enum { COMMAND_SD, COMMAND_WAIT, COMMAND_LUA, COMMAND_SWITCH, COMMAND_CASE,
       COMMAND_END, COMMAND_MSGBOX };
struct command { int kind,expected; size_t n; dw4_script_value a[6]; };
struct group { struct command *commands; size_t n,pc; uint64_t scope; int cancelled; };
struct model_call { dw4_script_model state;dw4_model_contact contact;int has_contact; uint64_t scope; int cancelled;
    struct model_call *previous; };
struct text_call { uint64_t scope; int cancelled; struct text_call *previous; };
struct dw4_scriptengine {
    dw4_script *vm;
    dw4_be_state *state;
    dw4_script_binding services;
    void *user;
    struct group building,*groups;
    size_t n;
    int ticking,failed,switching;
    char error[512];
    uint64_t scope;
    struct model_call *model;
    struct text_call *text;
    int32_t text_callno;
    unsigned startup;
    dw4_script_start_status start_status;
    int starting,called_remove_all;
    dw4_filelist *files;
    int record_flags;
};
static void free_command(struct command *c) {
    for (size_t i=0;i<c->n;i++) if (c->a[i].type==DW4_SCRIPT_STRING) free((void *)c->a[i].string);
}
static void free_group(struct group *g) {
    for (size_t i=0;i<g->n;i++) free_command(&g->commands[i]);
    free(g->commands); memset(g,0,sizeof(*g));
}
void dw4_scriptengine_dm_remove_all(dw4_scriptengine *e) {
    if(!e)return;
    if(e->ticking){e->called_remove_all=1;return;}
    free_group(&e->building);
    for(size_t i=0;i<e->n;i++)free_group(e->groups+i);
    free(e->groups);e->groups=NULL;e->n=0;e->switching=e->called_remove_all=0;
}
static int tick_finish(dw4_scriptengine *e,int rc) {
    e->ticking=0;
    if(e->called_remove_all)dw4_scriptengine_dm_remove_all(e);
    return rc;
}
static int append(dw4_scriptengine *e,int kind,int expected,const dw4_script_value *a,size_t n) {
    if(e->building.n && e->building.scope!=e->scope)return -1;
    if(!e->building.n)e->building.scope=e->scope;
    struct command c={0}; c.kind=kind; c.expected=expected; c.n=n;
    for (size_t i=0;i<n;i++) {
        c.a[i]=a[i];
        if (a[i].type==DW4_SCRIPT_STRING) {
            char *p=malloc(a[i].length+1);
            c.a[i].string=p;
            if (!p) { free_command(&c); return -1; }
            memcpy(p,a[i].string,a[i].length); p[a[i].length]=0;
        }
    }
    struct command *list=realloc(e->building.commands,(e->building.n+1)*sizeof(*list));
    if (!list) { free_command(&c); return -1; }
    e->building.commands=list; list[e->building.n++]=c; return 0;
}
static int publish(dw4_scriptengine *e) {
    /* Retail DMrun refuses publication until DMswtEnd closes the switch. */
    if (e->switching) return 0;
    if (!e->building.n) return 0;
    struct group *list=realloc(e->groups,(e->n+1)*sizeof(*list));
    if (!list) return -1;
    e->groups=list; list[e->n++]=e->building; memset(&e->building,0,sizeof(e->building)); return 0;
}
static int integer(dw4_script_value a,int *out) {
    if (a.type!=DW4_SCRIPT_NUMBER || !isfinite(a.number) || a.number<INT_MIN || a.number>INT_MAX) return -1;
    *out=(int)a.number; return 0;
}
static int service(dw4_scriptengine *e,const char *method,const dw4_script_value *a,size_t n,
                   dw4_script_value *r,char *err,size_t cap) {
    if (!e->services) { snprintf(err,cap,"engine service unavailable: %s",method); return -1; }
    return e->services(e->user,method,a,n,r,err,cap);
}
static int command_service(dw4_scriptengine *e,struct command *c,
                           dw4_script_value *r,char *err,size_t cap) {
    const char *method=c->kind==COMMAND_WAIT || c->kind==COMMAND_SWITCH ? "querySD":"sd";
    size_t n=c->n;
    /* Retail 0x37ee40 uses immediate dispatch for nonpositive DM delays.
     * The direct sd overload still queues even zero/negative delay values. */
    if(c->kind==COMMAND_SD && n>=5 && c->a[n-1].type==DW4_SCRIPT_NUMBER &&
       c->a[n-1].number<=0)n--;
    return service(e,method,c->a,n,r,err,cap);
}
static int native(void *user,const char *method,const dw4_script_value *a,size_t n,
                  dw4_script_value *r,char *error,size_t cap) {
    dw4_scriptengine *e=user; dw4_be_state *be=e->state;
    int id,v,rc;
    if(e->text && e->text->cancelled){snprintf(error,cap,"text event scope unloaded: %s",method);return -1;}
    if(e->model && e->model->cancelled) {
        snprintf(error,cap,"model event scope unloaded: %s",method);return -1;
    }
    if(!strcmp(method,"TXTgetCallNo")){if(n)goto bad;r->type=DW4_SCRIPT_NUMBER;r->number=e->text_callno;return 0;}
    if(e->model && e->model->has_contact) {
        int contact=dw4_model_contact_call(&e->model->contact,method,a,n,r,error,cap);
        if(contact<=0)return contact;
    }
    if (!strncmp(method,"MDL",3) && e->model) {
        struct model_call *m=e->model;
        if(!strcmp(method,"MDLgetRamNo") || !strcmp(method,"MDLgetRecNo") ||
           !strcmp(method,"MDLgetHp") || !strcmp(method,"MDLgetMHp")) {
            if(n)goto bad;
            r->type=DW4_SCRIPT_NUMBER;
            r->number=!strcmp(method,"MDLgetRamNo")?m->state.ram_no:
                !strcmp(method,"MDLgetRecNo")?m->state.rec_no:
                !strcmp(method,"MDLgetHp")?m->state.hp:m->state.max_hp;
            return 0;
        }
        if(!strcmp(method,"MDLgetInfoName")) {
            if(n)goto bad;
            if(m->state.info_name)*r=(dw4_script_value){DW4_SCRIPT_STRING,0,
                m->state.info_name,strlen(m->state.info_name)};
            return 0;
        }
        if(!strcmp(method,"MDLisCallName")) {
            if(n!=1 || (a[0].type!=DW4_SCRIPT_STRING && a[0].type!=DW4_SCRIPT_NIL))goto bad;
            r->type=DW4_SCRIPT_NUMBER;
            r->number=a[0].type==DW4_SCRIPT_NIL ? m->state.call_name==NULL :
                m->state.call_name && !strcmp(m->state.call_name,a[0].string);
            return 0;
        }
        if(!strcmp(method,"MDLaddHp")) {
            if(n!=1 || integer(a[0],&v))goto bad;
            uint32_t sum=(uint32_t)m->state.hp+(uint32_t)v;
            memcpy(&m->state.hp,&sum,4);
            if(m->state.hp<0)m->state.hp=0;
            return 0;
        }
        if(!strcmp(method,"MDLsetWorldPosTarget")) {
            float target[3];
            if(n==3) {
                for(unsigned i=0;i<3;i++) {
                    if(a[i].type!=DW4_SCRIPT_NUMBER || !isfinite(a[i].number) ||
                        fabs(a[i].number)>3.402823466e38)goto bad;
                    target[i]=(float)a[i].number;
                }
            } else if(n==1 && a[0].type==DW4_SCRIPT_STRING) {
                if(sscanf(a[0].string,"V<%f,%f,%f>",target,target+1,target+2)!=3)goto bad;
                for(unsigned i=0;i<3;i++)if(!isfinite(target[i]))goto bad;
            } else goto bad;
            if(m->state.target_enabled)memcpy(m->state.target,target,sizeof(target));
            return 0;
        }
        if(!strcmp(method,"MDLsetSeq") || !strcmp(method,"MDLsetSD")) {
            if(n<1 || n>2 || a[0].type!=DW4_SCRIPT_STRING ||
               (!strcmp(method,"MDLsetSeq") && n!=1))goto bad;
            dw4_script_value args[5]={ {DW4_SCRIPT_STRING,0,"MODELCTRL",9},
                {DW4_SCRIPT_STRING,0,m->state.info_name,m->state.info_name?strlen(m->state.info_name):0},
                {DW4_SCRIPT_NUMBER,m->state.ram_no,NULL,0},a[0] };
            if(!m->state.info_name)args[1].type=DW4_SCRIPT_NIL;
            if(n==2)args[4]=a[1];
            return service(e,"sd",args,n+3,r,error,cap);
        }
    }
    if (!strcmp(method,"DMsetSD")) {
        if (n<4 || n>6) goto bad;
        rc=append(e,COMMAND_SD,0,a,n); goto allocation;
    }
    if (!strcmp(method,"DMchkSD")) {
        if (n<5 || n>6 || a[n-1].type!=DW4_SCRIPT_STRING) goto bad;
        const char *op=a[n-1].string;
        if (!strcmp(op,"!=0") || !strcmp(op,"==1")) v=0;
        else if (!strcmp(op,"==0") || !strcmp(op,"!=1")) v=1;
        else { snprintf(error,cap,"unsupported DM condition: %s",op); return -1; }
        rc=append(e,COMMAND_WAIT,v,a,n-1); goto allocation;
    }
    if (!strcmp(method,"DMsetLua")) {
        if (n!=1 || a[0].type!=DW4_SCRIPT_STRING) goto bad;
        rc=append(e,COMMAND_LUA,0,a,n); goto allocation;
    }
    if (!strcmp(method,"DMswtSD")) {
        if (n<4 || n>5) goto bad;
        /* The retail builder has one switch latch, not a nesting stack. */
        if (e->switching) return 0;
        rc=append(e,COMMAND_SWITCH,0,a,n);
        if (!rc) e->switching=1;
        goto allocation;
    }
    if (!strcmp(method,"DMcase")) {
        if (n!=1 || integer(a[0],&v)) goto bad;
        if (!e->switching) return 0;
        rc=append(e,COMMAND_CASE,v,NULL,0); goto allocation;
    }
    if (!strcmp(method,"DMswtEnd")) {
        if (n) goto bad;
        if (!e->switching) return 0;
        rc=append(e,COMMAND_END,0,NULL,0);
        if (!rc) e->switching=0;
        goto allocation;
    }
    if (!strcmp(method,"DMmsgBox")) {
        if (n!=2 || a[0].type!=DW4_SCRIPT_STRING || integer(a[1],&v)) goto bad;
        /* Kind 6 is stored but skipped by retail 0x37ed70's jump table. */
        rc=append(e,COMMAND_MSGBOX,0,a,n); goto allocation;
    }
    if (!strcmp(method,"DMgetCount")) {
        if (n) goto bad;
        r->type=DW4_SCRIPT_NUMBER; r->number=(double)e->n;
        if (e->n) return 0;
        dw4_script_value query[]={
            {DW4_SCRIPT_STRING,0,"SUBWND",6}, {DW4_SCRIPT_NIL,0,NULL,0},
            {DW4_SCRIPT_NUMBER,0,NULL,0}, {DW4_SCRIPT_STRING,0,"ISRUN",5}
        }, result={0};
        if (service(e,"querySD",query,4,&result,error,cap)) return -1;
        if (result.type==DW4_SCRIPT_NIL) return 0;
        if (integer(result,&v)) { snprintf(error,cap,"SUBWND ISRUN returned a non-numeric result"); return -1; }
        r->number=(uint8_t)v ? -1 : 0;
        return 0;
    }
    if (!strcmp(method,"DMrun")) {
        if (n) goto bad;
        rc=publish(e); goto allocation;
    }
    if (!strcmp(method,"CFLclear") && !n) {
        dw4_be_cfl_clear(be);
        return e->files?dw4_filelist_call(e->files,method,a,n,r,error,cap):0;
    }
    if(e->files && (!strcmp(method,"CFLsetName") || !strcmp(method,"CFLgetFolderName") ||
        !strcmp(method,"SYSgetArea") || !strcmp(method,"SYSgetCountry") || !strcmp(method,"SYSgetIsPackOnly")))
        return dw4_filelist_call(e->files,method,a,n,r,error,cap);
    if (!strcmp(method,"FLGset")) {
        if (n!=2 || integer(a[0],&id) || integer(a[1],&v)) goto bad;
        if(e->record_flags)return service(e,method,a,n,r,error,cap);
        if (id>=0 && id<DW4_BE_MAX_FLAGS) be->flag[id]=(int8_t)(uint8_t)v;
        return 0;
    }
    if (!strcmp(method,"FLGisOn")) {
        if (n!=1 || integer(a[0],&id)) goto bad;
        if(e->record_flags)return service(e,method,a,n,r,error,cap);
        /* Retail lbu: -1 is 255, not false. Dynamic special flag ids
         * require session services; the frontend cannot answer them. */
        if (id<0 || id>=DW4_BE_MAX_FLAGS || id==1000) return service(e,method,a,n,r,error,cap);
        r->type=DW4_SCRIPT_NUMBER; r->number=(uint8_t)be->flag[id]; return 0;
    }
    if (!strcmp(method,"COUNTERset")) {
        if (n!=2 || integer(a[0],&id) || integer(a[1],&v)) goto bad;
        if (id<0 || id>=DW4_BE_MAX_COUNTERS) return service(e,method,a,n,r,error,cap);
        dw4_be_counter_set(be,id,v); return 0;
    }
    if (!strcmp(method,"COUNTERget")) {
        if (n!=1 || integer(a[0],&id)) goto bad;
        if (id<0 || id>=DW4_BE_MAX_COUNTERS) return service(e,method,a,n,r,error,cap);
        r->type=DW4_SCRIPT_NUMBER; r->number=be->counter[id]; return 0;
    }
    if (!strcmp(method,"SYSgetDifficulty") && !n) {
        r->type=DW4_SCRIPT_NUMBER; r->number=be->difficulty; return 0;
    }
    /* SYSgetTarget (value function 0x00371ef0: jr ra; li v0,1): the USA PS2 build is target 1. A Commander Room Digi-Elf
     * (bML02012) chooses a page by it ("== 3" selects another platform's line). */
    if (!strcmp(method,"SYSgetTarget") && !n) {
        r->type=DW4_SCRIPT_NUMBER; r->number=1; return 0;
    }
    if (!strcmp(method,"SYSgetRandom")) {
        if (n!=1 || integer(a[0],&v)) goto bad;
        r->type=DW4_SCRIPT_NUMBER;
        r->number=dw4_random_mod(&be->random,v); return 0;
    }
    if (!strcmp(method,"SYSsetDifficulty")) {
        if (n!=1 || integer(a[0],&v)) goto bad;
        be->difficulty=v; return 0;
    }
    if (!strcmp(method,"LISsetDifficultMax")) {
        if (n!=1 || integer(a[0],&v)) goto bad;
        dw4_be_lis_set_difficult_max(be,v); return 0;
    }
    return service(e,method,a,n,r,error,cap);
bad:
    snprintf(error,cap,"invalid arguments for %s",method); return -1;
allocation:
    if (rc) snprintf(error,cap,"script command allocation failed");
    return rc;
}
void dw4_scriptengine_record_flags(dw4_scriptengine *e,int enabled)
{if(e)e->record_flags=!!enabled;}
dw4_scriptengine *dw4_scriptengine_open(dw4_be_state *state,dw4_script_binding services,void *user) {
    if (!state) return NULL;
    dw4_scriptengine *e=calloc(1,sizeof(*e));
    if (!e) return NULL;
    e->state=state; e->services=services; e->user=user;
    e->vm=dw4_script_open(native,e);
    if (!e->vm) { free(e); return NULL; }
    return e;
}
void dw4_scriptengine_close(dw4_scriptengine *e) {
    if (!e) return;
    if(e->starting || e->ticking || e->model || e->text || dw4_script_busy(e->vm))return;
    dw4_script_close(e->vm); free_group(&e->building);
    for (size_t i=0;i<e->n;i++) free_group(&e->groups[i]);
    free(e->groups); free(e);
}
dw4_script *dw4_scriptengine_vm(dw4_scriptengine *e) { return e?e->vm:NULL; }
void dw4_scriptengine_filelist(dw4_scriptengine *e,dw4_filelist *files) { if(e)e->files=files; }
int dw4_scriptengine_can_start(const dw4_scriptengine *e) {
    return e && !e->startup && !e->starting && !e->ticking && !e->model && !e->text &&
        !e->n && !e->building.n && !dw4_script_busy(e->vm);
}
int dw4_scriptengine_remove_all(dw4_scriptengine *e,dw4_scriptservices *sd) {
    if(!e || e->starting || e->ticking || e->model || e->text || dw4_script_busy(e->vm) || dw4_scriptservices_busy(sd)) {
        if(e)snprintf(e->error,sizeof(e->error),"scene cleanup requires a boundary between callbacks/ticks");
        return -1;
    }
    if(sd && dw4_scriptservices_remove_all(sd))return -1;
    if(dw4_script_remove_all(e->vm))return -1;
    dw4_scriptengine_dm_remove_all(e);e->scope=0;
    e->failed=e->switching=0;e->startup=0;e->error[0]=0;
    memset(&e->start_status,0,sizeof(e->start_status));return 0;
}
int dw4_scriptengine_reset_scene(dw4_scriptengine *e,dw4_scriptservices *sd) {
    if(dw4_scriptengine_remove_all(e,sd))return -1;
    if(dw4_script_recreate(e->vm)) {
        e->failed=1;snprintf(e->error,sizeof(e->error),"%s",dw4_script_error(e->vm));return -1;
    }
    return 0;
}
const dw4_script_start_status *dw4_scriptengine_start_status(const dw4_scriptengine *e) {
    return e?&e->start_status:NULL;
}
int dw4_scriptengine_startup(dw4_scriptengine *e,dw4_script_start phase) {
    if(!e || (unsigned)phase!=e->startup || (unsigned)phase>DW4_SCRIPT_START_FIRST ||
       e->starting || e->ticking || e->model || e->text || dw4_script_busy(e->vm))return -1;
    if(phase==DW4_SCRIPT_START_SHARED) {
        if(dw4_script_recreate(e->vm))return -1;
        e->failed=0;
        e->starting=1;
        e->start_status.func=dw4_script_run_named(e->vm,"func.lua",NULL);
        e->start_status.boot=dw4_script_run_named(e->vm,"boot.lua",NULL);
    } else if(phase==DW4_SCRIPT_START_STAGE) {
        e->starting=1;
        dw4_script_value a[]={ {DW4_SCRIPT_STRING,0,"TEXTCTL",7},
            {DW4_SCRIPT_NIL,0,NULL,0},{DW4_SCRIPT_NUMBER,-1,NULL,0},
            {DW4_SCRIPT_STRING,0,"INITIALIZE",10} },r={0};
        e->start_status.text=service(e,"sd",a,4,&r,e->error,sizeof(e->error));
        e->start_status.start=dw4_script_run_named(e->vm,"start.lua",NULL);
    } else if(phase==DW4_SCRIPT_START_FIRST) {
        e->starting=1;
        e->start_status.first=dw4_script_run_named(e->vm,"first.lua",NULL);
    } else return -1;
    e->startup++;e->starting=0;return 0;
}
size_t dw4_scriptengine_pending(const dw4_scriptengine *e) { return e?e->n:0; }
void dw4_scriptengine_describe(const dw4_scriptengine *e,FILE *out) {
    for(size_t i=0;e && i<e->n;i++){
        const struct group *g=&e->groups[i];
        fprintf(out,"  group %zu: pc %zu of %zu scope %llu%s; next:",i,g->pc,g->n,(unsigned long long)g->scope,g->cancelled?" (cancelled)":"");
        if(g->pc<g->n){const struct command *c=&g->commands[g->pc];fprintf(out," kind %d expected %d",c->kind,c->expected);
            for(size_t q=0;q<c->n && q<6;q++){if(c->a[q].type==DW4_SCRIPT_STRING)fprintf(out," %.*s",(int)c->a[q].length,c->a[q].string);else fprintf(out," #%g",c->a[q].number);}}
        fputc(10,out);
    }
}
const char *dw4_scriptengine_error(const dw4_scriptengine *e) { return e?e->error:"no script engine"; }
int dw4_scriptengine_run(dw4_scriptengine *e,const char *name) {
    if (!e || e->failed) return -1;
    if (dw4_script_run(e->vm,name)) {
        snprintf(e->error,sizeof(e->error),"%s",dw4_script_error(e->vm));
        if(getenv("DW4_BE_TRACE"))fprintf(stderr,"script run %s failed: %s\n",name,e->error);
        free_group(&e->building); e->failed=1; return -1;
    }
    return 0;
}
static int model_event(dw4_scriptengine *e,uint64_t scope,
    const char *script,dw4_script_model *state,dw4_model_contact *contact) {
    if(!e || !state || !script || e->failed)return -1;
    struct model_call call={.state=*state,.scope=scope,.previous=e->model};
    if(contact){call.contact=*contact;call.has_contact=1;}
    char *info=NULL,*name=NULL;
    /* Copy selector names before any reentrant service can unload its owner. */
    if(state->info_name){info=malloc(strlen(state->info_name)+1);if(!info)goto failed;strcpy(info,state->info_name);}
    if(state->call_name){name=malloc(strlen(state->call_name)+1);if(!name)goto failed;strcpy(name,state->call_name);}
    call.state.info_name=info;call.state.call_name=name;
    uint64_t previous_scope=e->scope;e->scope=scope;e->model=&call;
    int rc=dw4_scriptengine_run(e,script);
    e->model=call.previous;e->scope=previous_scope;
    if(!rc && !call.cancelled) {
        state->hp=call.state.hp;
        if(contact)contact->damage_turn=call.contact.damage_turn;
        memcpy(state->target,call.state.target,sizeof(state->target));
    } else if(call.cancelled && !rc) {
        snprintf(e->error,sizeof(e->error),"model event scope unloaded: %s",script);rc=-1;
    }
    free(info);free(name);return rc;
failed:
    free(info);free(name);snprintf(e->error,sizeof(e->error),"model event allocation failed");
    e->failed=1;return -1;
}
int dw4_scriptengine_model_event(dw4_scriptengine *e,uint64_t scope,const char *script,dw4_script_model *state)
{return model_event(e,scope,script,state,NULL);}
int dw4_scriptengine_has_script(const dw4_scriptengine *e,const char *name){return e && dw4_script_has_info(e->vm,name);}
int dw4_scriptengine_contact_event(dw4_scriptengine *e,uint64_t scope,const char *script,dw4_script_model *state,dw4_model_contact *contact)
{return contact?model_event(e,scope,script,state,contact):-1;}
int dw4_scriptengine_text_event(dw4_scriptengine *e,uint64_t scope,const char *script,int32_t callno) {
    if(!e || !script || e->failed)return -1;
    struct text_call call={.scope=scope,.previous=e->text};
    uint64_t previous_scope=e->scope;e->scope=scope;e->text=&call;
    /* Retail 3f5920 stores a global; nested text callbacks leave their last
     * value published rather than restoring the outer call number. */
    e->text_callno=callno;
    int rc=dw4_scriptengine_run(e,script);
    e->text=call.previous;e->scope=previous_scope;
    if(call.cancelled && !rc){snprintf(e->error,sizeof(e->error),"text event scope unloaded: %s",script);rc=-1;}
    return rc;
}
void dw4_scriptengine_remove_scope(dw4_scriptengine *e,uint64_t scope) {
    if(!e)return;
    dw4_script_remove_scope(e->vm,scope);
    if(e->building.n && e->building.scope==scope){free_group(&e->building);e->switching=0;}
    for(size_t i=0;i<e->n;i++)if(e->groups[i].scope==scope)e->groups[i].cancelled=1;
    for(struct text_call *t=e->text;t;t=t->previous)if(t->scope==scope)t->cancelled=1;
    for(struct model_call *m=e->model;m;m=m->previous)if(m->scope==scope)m->cancelled=1;
}
int dw4_scriptengine_queue_event(dw4_scriptengine *e,const char *name) {
    if (!e || e->failed || e->building.n || !name) return -1;
    dw4_script_value a={DW4_SCRIPT_STRING,0,name,strlen(name)};
    if (append(e,COMMAND_LUA,0,&a,1) || publish(e)) {
        free_group(&e->building); e->failed=1;
        snprintf(e->error,sizeof(e->error),"script event allocation failed");return -1;
    }
    return 0;
}
int dw4_scriptengine_tick(dw4_scriptengine *e) {
    if (!e || e->ticking || e->failed) return -1;
    e->error[0]=0; e->ticking=1;
    /* Retail 0x37ed70 snapshots the list count and traverses groups backwards.
     * Newly published event groups are eligible on the following tick. */
    size_t count=e->n;
    for (size_t g=count;g>0;g--) {
        size_t index=g-1;
        while (!e->groups[index].cancelled && e->groups[index].pc<e->groups[index].n) {
            struct command *c=&e->groups[index].commands[e->groups[index].pc];
            dw4_script_value result={0};
            int rc;
            if (c->kind==COMMAND_CASE) {
                /* Reaching the next case ends the selected arm. */
                do { e->groups[index].pc++; }
                while (e->groups[index].pc<e->groups[index].n &&
                       e->groups[index].commands[e->groups[index].pc].kind!=COMMAND_END);
                if (e->groups[index].pc<e->groups[index].n) e->groups[index].pc++;
                continue;
            }
            if (c->kind==COMMAND_END || c->kind==COMMAND_MSGBOX) {
                e->groups[index].pc++; continue;
            }
            if (c->kind==COMMAND_LUA) {
                uint64_t scope=e->scope;e->scope=e->groups[index].scope;
                rc=dw4_scriptengine_run(e,c->a[0].string);
                e->scope=scope;
                if (rc) snprintf(e->error,sizeof(e->error),"%s",dw4_script_error(e->vm));
            } else {
                uint64_t scope=e->scope;e->scope=e->groups[index].scope;
                rc=command_service(e,c,&result,e->error,sizeof(e->error));e->scope=scope;
            }
            if (rc) { if(getenv("DW4_BE_TRACE")){fprintf(stderr,"command failed (kind %d): %s |",(int)c->kind,e->error);for(size_t q=0;q<c->n && q<6;q++){if(c->a[q].type==DW4_SCRIPT_STRING)fprintf(stderr," %.*s",(int)c->a[q].length,c->a[q].string);else fprintf(stderr," #%g",c->a[q].number);}fputc(10,stderr);}free_group(&e->building); e->failed=1; return tick_finish(e,-1); }
            /* A callback can publish and realloc groups; reacquire by index. */
            c=&e->groups[index].commands[e->groups[index].pc];
            if (c->kind==COMMAND_SWITCH && result.type!=DW4_SCRIPT_NIL) {
                int selected;
                if (integer(result,&selected)) {
                    snprintf(e->error,sizeof(e->error),"switch querySD returned a non-integer result");
                    e->failed=1; return tick_finish(e,-1);
                }
                /* Retail scans to the first matching integer case or end. */
                do { e->groups[index].pc++; }
                while (e->groups[index].pc<e->groups[index].n &&
                    e->groups[index].commands[e->groups[index].pc].kind!=COMMAND_END &&
                    !(e->groups[index].commands[e->groups[index].pc].kind==COMMAND_CASE &&
                      e->groups[index].commands[e->groups[index].pc].expected==selected));
                if (e->groups[index].pc<e->groups[index].n) e->groups[index].pc++;
                continue;
            }
            if (c->kind==COMMAND_WAIT && (result.type==DW4_SCRIPT_NIL ||
                (result.type==DW4_SCRIPT_NUMBER && result.number!=c->expected))) break;
            if (c->kind==COMMAND_WAIT && result.type!=DW4_SCRIPT_NUMBER) {
                snprintf(e->error,sizeof(e->error),"querySD returned a non-numeric result");
                e->failed=1; return tick_finish(e,-1);
            }
            e->groups[index].pc++;
        }
    }
    /* Remove completed groups after all original groups have advanced. */
    for (size_t i=e->n;i>0;i--) if (e->groups[i-1].cancelled || e->groups[i-1].pc==e->groups[i-1].n) {
        free_group(&e->groups[i-1]);
        memmove(e->groups+i-1,e->groups+i,(e->n-i)*sizeof(*e->groups)); e->n--;
    }
    return tick_finish(e,0);
}

uint64_t dw4_scriptengine_scope(const dw4_scriptengine *e) {return e?e->scope:0;}
