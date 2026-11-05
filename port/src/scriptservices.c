#include "dw4/scriptservices.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

struct receiver {
    uint64_t token,scope;
    char *category,*name;
    int32_t id;
    int active;
    dw4_script_binding handler;
    void *user;
};
struct message {
    struct message *next;
    uint64_t scope,due;
    size_t n;
    dw4_script_value a[5];
};
struct dw4_scriptservices {
    struct receiver *receivers;
    size_t count;
    char **categories;
    size_t categories_count;
    struct message *messages;
    size_t queue_capacity;
    uint64_t serial,scope,now;
    unsigned depth;
    int failed,ticking;
    char error[512];
};
static char *copy(const char *s,size_t n) {
    char *p=malloc(n+1);
    if(p) { memcpy(p,s,n);p[n]=0; }
    return p;
}
static int text_value(dw4_script_value v) {
    return v.type==DW4_SCRIPT_STRING && v.string &&
           !memchr(v.string,0,v.length);
}
static int equals(dw4_script_value v,const char *s) {
    return s && v.length==strlen(s) && !memcmp(v.string,s,v.length);
}
static int integer(dw4_script_value v,int32_t *out) {
    if(v.type!=DW4_SCRIPT_NUMBER || !isfinite(v.number) ||
       v.number<INT32_MIN || v.number>INT32_MAX) return -1;
    *out=(int32_t)v.number;return 0;
}
/* Compare signed 64-bit timestamps without implementation-defined casts. */
static int before(uint64_t a,uint64_t b) {
    return (a^((uint64_t)1<<63))<(b^((uint64_t)1<<63));
}
static void free_message(struct message *m) {
    for(size_t i=0;i<m->n;i++)
        if(m->a[i].type==DW4_SCRIPT_STRING) free((void *)m->a[i].string);
    free(m);
}
dw4_scriptservices *dw4_scriptservices_open(void) {
    dw4_scriptservices *s=calloc(1,sizeof(*s));
    if(s)s->queue_capacity=32; /* 0x38c0f0..0x38c224's reusable record list */
    return s;
}
void dw4_scriptservices_cancel(dw4_scriptservices *s,uint64_t scope) {
    if(!s)return;
    struct message **p=&s->messages;
    while(*p) {
        struct message *m=*p;
        if(m->scope==scope) { *p=m->next;free_message(m); }
        else p=&m->next;
    }
}
void dw4_scriptservices_unregister(dw4_scriptservices *s,uint64_t token) {
    if(!s)return;
    for(size_t i=0;i<s->count;i++)if(s->receivers[i].token==token) {
        free(s->receivers[i].category);free(s->receivers[i].name);
        memmove(s->receivers+i,s->receivers+i+1,(s->count-i-1)*sizeof(*s->receivers));
        s->count--;return;
    }
}
void dw4_scriptservices_remove_scope(dw4_scriptservices *s,uint64_t scope) {
    if(!s)return;
    dw4_scriptservices_cancel(s,scope);
    for(size_t i=s->count;i>0;i--)if(s->receivers[i-1].scope==scope)
        dw4_scriptservices_unregister(s,s->receivers[i-1].token);
}
int dw4_scriptservices_busy(const dw4_scriptservices *s) {return s && (s->depth || s->ticking);}
int dw4_scriptservices_remove_all(dw4_scriptservices *s) {
    if(!s || dw4_scriptservices_busy(s))return -1;
    while(s->messages) { struct message *m=s->messages;s->messages=m->next;free_message(m); }
    while(s->count)dw4_scriptservices_unregister(s,s->receivers[0].token);
    for(size_t i=0;i<s->categories_count;i++)free(s->categories[i]);
    free(s->categories);free(s->receivers);
    s->categories=NULL;s->receivers=NULL;s->categories_count=0;
    s->scope=0;s->queue_capacity=32;s->failed=0;s->error[0]=0;
    return 0;
}
void dw4_scriptservices_close(dw4_scriptservices *s) {
    if(!s)return;
    if(!dw4_scriptservices_remove_all(s))free(s);
}
uint64_t dw4_scriptservices_register(dw4_scriptservices *s,uint64_t scope,
    const char *category,const char *name,int32_t id,int active,
    dw4_script_binding handler,void *user) {
    if(!s || !category || !*category || !handler || s->serial==UINT64_MAX)return 0;
    struct receiver r={0};r.category=copy(category,strlen(category));
    if(name)r.name=copy(name,strlen(name));
    if(!r.category || (name && !r.name))goto fail;
    if(dw4_scriptservices_category(s,category))goto fail;
    struct receiver *list=realloc(s->receivers,(s->count+1)*sizeof(*list));
    if(!list)goto fail;
    r.token=++s->serial;r.scope=scope;r.id=id;r.active=!!active;r.handler=handler;r.user=user;
    s->receivers=list;list[s->count++]=r;return r.token;
fail:
    free(r.category);free(r.name);return 0;
}
int dw4_scriptservices_category(dw4_scriptservices *s,const char *category)
{
    if(!s || !category || !*category)return -1;
    for(size_t i=0;i<s->categories_count;i++)if(!strcmp(category,s->categories[i]))return 0;
    char *name=copy(category,strlen(category));if(!name)return -1;
    char **list=realloc(s->categories,(s->categories_count+1)*sizeof *list);
    if(!list){free(name);return -1;}
    s->categories=list;list[s->categories_count++]=name;return 0;
}
void dw4_scriptservices_active(dw4_scriptservices *s,uint64_t token,int active) {
    if(s)for(size_t i=0;i<s->count;i++)if(s->receivers[i].token==token)s->receivers[i].active=!!active;
}
void dw4_scriptservices_scope(dw4_scriptservices *s,uint64_t scope) { if(s)s->scope=scope; }
static int dispatch_result_impl(dw4_scriptservices *s,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *result,char *error,size_t cap,int any);
/* DW4_SD_TRACE=1 prints every dispatched SD/querySD call and its outcome to stderr (script bring-up aid). */
static int dispatch_result(dw4_scriptservices *s,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *result,char *error,size_t cap,int any) {
    static int trace=-1;if(trace<0)trace=getenv("DW4_SD_TRACE")!=NULL;
    int rc=dispatch_result_impl(s,method,a,n,result,error,cap,any);
    if(trace){
        fprintf(stderr,"SD %s",method);
        for(size_t i=0;i<n;i++){
            if(a[i].type==DW4_SCRIPT_STRING && a[i].string)fprintf(stderr," %.*s",(int)a[i].length,a[i].string);
            else if(a[i].type==DW4_SCRIPT_NUMBER)fprintf(stderr," %g",a[i].number);else fprintf(stderr," nil");
        }
        if(rc)fprintf(stderr," => ERROR %s\n",error);
        else if(result && result->type==DW4_SCRIPT_NUMBER && !strcmp(method,"querySD"))fprintf(stderr," => %g\n",result->number);
        else fprintf(stderr,"\n");
    }
    return rc;
}
static int dispatch_result_impl(dw4_scriptservices *s,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *result,char *error,size_t cap,int any) {
    int32_t id;
    if(n<4 || n>5 || !text_value(a[0]) ||
       (a[1].type!=DW4_SCRIPT_NIL && !text_value(a[1])) ||
       integer(a[2],&id) || !text_value(a[3])) {
        snprintf(error,cap,"invalid SD selector or arguments");return -1;
    }
    size_t k;
    for(k=0;k<s->categories_count;k++)if(equals(a[0],s->categories[k]))break;
    if(k==s->categories_count) {
        snprintf(error,cap,"engine category unavailable: %.*s (%.*s)",
                 (int)a[0].length,a[0].string,(int)a[3].length,a[3].string);return -1;
    }
    if(s->depth>=64) { snprintf(error,cap,"recursive SD service call limit");return -1; }
    /* Snapshot tokens, not host pointers: callbacks may add/remove receivers.
     * New receivers are eligible on the next dispatch, never midway through it. */
    uint64_t *tokens=malloc((s->count?s->count:1)*sizeof(*tokens));
    if(!tokens) { snprintf(error,cap,"SD receiver snapshot allocation failed");return -1; }
    size_t count=0;
    for(size_t i=0;i<s->count;i++) {
        struct receiver *r=&s->receivers[i];
        if(!equals(a[0],r->category) ||
           (a[1].type==DW4_SCRIPT_STRING && r->name && !equals(a[1],r->name)))continue;
        if(id==-2 ? r->active : (id!=-1 && r->id!=-1 && id!=r->id))continue;
        tokens[count++]=r->token;
        if(id==-2)break;
    }
    *result=any?(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0}:(dw4_script_value){0};s->depth++;
    int rc=0;
    for(size_t i=0;i<count && !rc;i++)for(size_t j=0;j<s->count;j++) {
        struct receiver r=s->receivers[j];
        if(r.token!=tokens[i])continue;
        dw4_script_value value={0};
        rc=r.handler(r.user,method,a,n,&value,error,cap);
        /* Retail DM reads result index zero, not the last receiver's result. */
        if(any){if(!rc && value.type==DW4_SCRIPT_NUMBER){
            int32_t byte;
            if(integer(value,&byte)){snprintf(error,cap,"ISRUN query returned an invalid byte result");rc=-1;}
            else if((uint8_t)byte)result->number=1;
        }}
        else if(!rc && result->type==DW4_SCRIPT_NIL && value.type!=DW4_SCRIPT_NIL)*result=value;
        break;
    }
    s->depth--;free(tokens);return rc;
}
static int dispatch(dw4_scriptservices *s,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *result,char *error,size_t cap)
{return dispatch_result(s,method,a,n,result,error,cap,0);}
int dw4_scriptservices_any(dw4_scriptservices *s,const dw4_script_value *a,size_t n,
    dw4_script_value *result,char *error,size_t cap)
{
    if(!s || s->failed){snprintf(error,cap,"SD services stopped");return -1;}
    return dispatch_result(s,"querySD",a,n,result,error,cap,1);
}
int dw4_scriptservices_call(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap) {
    dw4_scriptservices *s=user;
    if(!s || s->failed) { snprintf(error,cap,"SD services stopped: %s",s?s->error:"no service owner");return -1; }
    *r=(dw4_script_value){0};
    if(!strcmp(method,"querySD"))return dispatch(s,method,a,n,r,error,cap);
    if(strcmp(method,"sd")) { snprintf(error,cap,"engine service unavailable: %s",method);return -1; }
    /* Retail overloads: fifth string is optional data; fifth number is a
     * delay without optional data; sixth number is delay with optional data. */
    int delayed=n==6 || (n==5 && a[4].type==DW4_SCRIPT_NUMBER);
    if(!delayed) {
        dw4_script_value unused={0};return dispatch(s,method,a,n,&unused,error,cap);
    }
    dw4_script_value canonical[5];
    if(n!=5 && n!=6)goto bad;
    memcpy(canonical,a,4*sizeof(*a));
    size_t used=4;
    if(n==6)canonical[used++]=a[4];
    dw4_script_value delay=a[n-1];
    /* Original Lua binding converts delays to signed 64-bit integers. */
    if(delay.type!=DW4_SCRIPT_NUMBER || !isfinite(delay.number) ||
       delay.number < -9223372036854775808.0 || delay.number >= 9223372036854775808.0)goto bad;
    int32_t id;
    if(!text_value(a[0]) || (a[1].type!=DW4_SCRIPT_NIL && !text_value(a[1])) ||
       integer(a[2],&id) || !text_value(a[3]))goto bad;
    struct message *m=calloc(1,sizeof(*m));
    if(!m)goto allocation;
    m->scope=s->scope;m->due=s->now+(uint64_t)(int64_t)delay.number*UINT64_C(16666666);
    m->n=used;
    for(size_t i=0;i<used;i++) {
        m->a[i]=canonical[i];
        if(canonical[i].type==DW4_SCRIPT_STRING) {
            if(!canonical[i].string) { m->a[i].string=NULL;free_message(m);goto bad; }
            m->a[i].string=copy(canonical[i].string,canonical[i].length);
            if(!m->a[i].string) { free_message(m);goto allocation; }
        }
    }
    struct message **p=&s->messages;
    while(*p && !before(m->due,(*p)->due))p=&(*p)->next;
    m->next=*p;*p=m;
    size_t count=dw4_scriptservices_pending(s);
    if(count>s->queue_capacity)s->queue_capacity=count;
    return 0;
bad:
    snprintf(error,cap,"invalid delayed SD arguments");return -1;
allocation:
    snprintf(error,cap,"SD message allocation failed");return -1;
}
int dw4_scriptservices_tick(dw4_scriptservices *s,uint64_t world) {
    if(!s || s->failed || s->ticking)return -1;
    s->now=world;s->ticking=1;
    /* Retail snapshots reusable-list size, then consumes due messages from the head.
     * Newly scheduled messages may run in this pass within that same budget. */
    size_t budget=s->queue_capacity;
    while(budget-- && s->messages && !before(world,s->messages->due)) {
        struct message *m=s->messages;s->messages=m->next;
        dw4_script_value result={0};
        /* A callback's follow-up messages belong to the original publisher,
         * even if another owner published more recently. Restore the ambient
         * scope after dispatch, including failure and explicit nested changes. */
        uint64_t scope=s->scope;s->scope=m->scope;
        int rc=dispatch(s,"sd",m->a,m->n,&result,s->error,sizeof(s->error));
        s->scope=scope;
        free_message(m);
        if(rc) { s->failed=1;s->ticking=0;return -1; }
    }
    s->ticking=0;return 0;
}
size_t dw4_scriptservices_pending(const dw4_scriptservices *s) {
    size_t n=0;if(s)for(struct message *m=s->messages;m;m=m->next)n++;return n;
}
const char *dw4_scriptservices_error(const dw4_scriptservices *s) { return s?s->error:"no SD services"; }

size_t dw4_scriptservices_count(const dw4_scriptservices *s,const char *category,const char *name,size_t *active)
{
    size_t total=0,live=0;
    for(size_t i=0;s && i<s->count;i++) {
        const struct receiver *r=&s->receivers[i];
        if(strncmp(r->category,category,strlen(category)) || strlen(r->category)!=strlen(category))continue;
        if(name && (!r->name || strcmp(r->name,name)))continue;
        total++;if(r->active)live++;
    }
    if(active)*active=live;
    return total;
}

static int category_is(const struct receiver *r,const char *category,const char *name)
{return !strcmp(r->category,category) && (!name || (r->name && !strcmp(r->name,name)));}
/* First registered receiver of that category/name that is not active; its id, or -1 when every one runs. */
int32_t dw4_scriptservices_first_inactive(const dw4_scriptservices *s,const char *category,const char *name)
{
    for(size_t i=0;s && i<s->count;i++)if(category_is(&s->receivers[i],category,name) && !s->receivers[i].active)return s->receivers[i].id;
    return -1;
}
/* 1 active, 0 inactive, -1 no such receiver. */
int dw4_scriptservices_is_active(const dw4_scriptservices *s,const char *category,const char *name,int32_t id)
{
    for(size_t i=0;s && i<s->count;i++)if(category_is(&s->receivers[i],category,name) && s->receivers[i].id==id)return s->receivers[i].active!=0;
    return -1;
}
