#include "dw4/scriptservices.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static dw4_script_value str(const char *s) {
    return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};
}
static dw4_script_value num(double n) { return (dw4_script_value){DW4_SCRIPT_NUMBER,n,NULL,0}; }
struct service {
    dw4_scriptservices *sd;
    uint64_t token,remove;
    unsigned calls;
    int value,fail,reenter;
    char optional[64];
};
static int handler(void *user,const char *method,const dw4_script_value *a,size_t n,
                   dw4_script_value *r,char *error,size_t cap) {
    struct service *b=user;b->calls++;
    assert(dw4_scriptservices_busy(b->sd) && dw4_scriptservices_remove_all(b->sd)==-1);
    if(b->fail) { snprintf(error,cap,"test receiver rejected %s",a[3].string);return -1; }
    if(b->remove) { dw4_scriptservices_unregister(b->sd,b->remove);b->remove=0; }
    if(!strcmp(method,"querySD")) { *r=num(b->value);return 0; }
    if(n==5 && a[4].type==DW4_SCRIPT_STRING)
        snprintf(b->optional,sizeof(b->optional),"%.*s",(int)a[4].length,a[4].string);
    if(b->reenter) {
        b->reenter=0;
        dw4_script_value v[]={str("MODELCTRL"),str("second"),num(8),str("NESTED")};
        assert(!dw4_scriptservices_call(b->sd,"sd",v,4,r,error,cap));
    }
    return 0;
}
static int send(dw4_scriptservices *s,const char *method,const char *name,int id,
                const char *key,const char *value,double delay,int delayed,double *result) {
    dw4_script_value a[]={str("MODELCTRL"),{0},num(id),str(key),{0},num(delay)},r={0};
    if(name)a[1]=str(name);
    if(value)a[4]=str(value);
    size_t n=value?5:4;
    if(delayed) { if(!value)a[4]=num(delay);n=value?6:5; }
    char error[512]={0};
    int rc=dw4_scriptservices_call(s,method,a,n,&r,error,sizeof(error));
    if(result)*result=r.type==DW4_SCRIPT_NUMBER?r.number:NAN;
    return rc;
}
struct timed_service {
    dw4_scriptservices *sd;
    unsigned calls;
    int cancel,fail,chain;
};
static int timed_handler(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    struct timed_service *t=user;
    (void)method;(void)n;(void)r;
    t->calls++;
    assert(dw4_scriptservices_busy(t->sd) && dw4_scriptservices_remove_all(t->sd)==-1);
    /* A nested tick must neither change the sampled clock nor recurse. */
    assert(dw4_scriptservices_tick(t->sd,999999999999ULL));
    if(!strcmp(a[3].string,"OVERRIDE")) {
        dw4_scriptservices_scope(t->sd,3);
        assert(!send(t->sd,"sd","first",7,"CHILD",NULL,30,1,NULL));
    }
    if(t->chain || !strcmp(a[3].string,"PARENT")) {
        assert(!send(t->sd,"sd","first",7,"CHILD",NULL,t->chain?0:30,1,NULL));
        if(t->cancel)dw4_scriptservices_remove_scope(t->sd,1);
    }
    if(t->fail) { snprintf(error,cap,"timed failure");return -1; }
    return 0;
}
static void timed_lifetimes(void) {
    for(unsigned reload=0;reload<128;reload++)
    for(int cancel=0;cancel<2;cancel++) {
        dw4_scriptservices *s=dw4_scriptservices_open();assert(s);
        struct timed_service t={.sd=s,.cancel=cancel};
        assert(dw4_scriptservices_register(s,1,"MODELCTRL","first",7,1,timed_handler,&t));
        dw4_scriptservices_scope(s,1);
        assert(!send(s,"sd","first",7,"PARENT",NULL,0,1,NULL));
        dw4_scriptservices_scope(s,2); /* unrelated publisher changes ambient owner */
        assert(!dw4_scriptservices_tick(s,100) && t.calls==1);
        assert(dw4_scriptservices_pending(s)==(cancel?0:1));
        if(!cancel) {
            dw4_scriptservices_cancel(s,2); /* must not cancel the callback's child */
            assert(dw4_scriptservices_pending(s)==1);
            assert(!dw4_scriptservices_tick(s,100+30*16666666ULL) && t.calls==2);
            assert(!send(s,"sd","first",7,"OVERRIDE",NULL,0,1,NULL));
            assert(!dw4_scriptservices_tick(s,100+30*16666666ULL));
            dw4_scriptservices_cancel(s,1);dw4_scriptservices_cancel(s,2);
            assert(dw4_scriptservices_pending(s)==1);
            dw4_scriptservices_cancel(s,3);assert(!dw4_scriptservices_pending(s));
        }
        /* Ambient scope 2 was restored even after removal during dispatch. */
        assert(!send(s,"sd","first",7,"AMBIENT",NULL,0,1,NULL));
        dw4_scriptservices_cancel(s,1);assert(dw4_scriptservices_pending(s)==1);
        dw4_scriptservices_cancel(s,2);assert(!dw4_scriptservices_pending(s));
        dw4_scriptservices_close(s);
    }
    dw4_scriptservices *s=dw4_scriptservices_open();assert(s);
    struct timed_service t={.sd=s,.chain=1};
    assert(dw4_scriptservices_register(s,1,"MODELCTRL","first",7,1,timed_handler,&t));
    dw4_scriptservices_scope(s,1);
    assert(!send(s,"sd","first",7,"PARENT",NULL,0,1,NULL));
    assert(!dw4_scriptservices_tick(s,0) && t.calls==32 && dw4_scriptservices_pending(s)==1);
    assert(!dw4_scriptservices_tick(s,0) && t.calls==64 && dw4_scriptservices_pending(s)==1);
    dw4_scriptservices_cancel(s,1);assert(!dw4_scriptservices_pending(s));
    t.chain=0;t.fail=1;
    assert(!send(s,"sd","first",7,"PARENT",NULL,0,1,NULL));
    assert(!send(s,"sd","first",7,"PEER",NULL,0,1,NULL));
    assert(dw4_scriptservices_tick(s,0) && t.calls==65);
    assert(dw4_scriptservices_pending(s)==2); /* peer and queued child survive failure */
    dw4_scriptservices_cancel(s,1);assert(!dw4_scriptservices_pending(s));
    assert(dw4_scriptservices_tick(s,100) && t.calls==65);
    assert(!dw4_scriptservices_remove_all(s));t.fail=0;
    assert(dw4_scriptservices_register(s,1,"MODELCTRL","first",7,1,timed_handler,&t));
    assert(!send(s,"sd","first",7,"RECOVERED",NULL,1,1,NULL));
    assert(!dw4_scriptservices_tick(s,16666665) && t.calls==65);
    assert(!dw4_scriptservices_tick(s,16666666) && t.calls==66);
    dw4_scriptservices_close(s);
}
int main(void) {
    timed_lifetimes();
    dw4_scriptservices *s=dw4_scriptservices_open();assert(s);
    struct service first={.sd=s,.value=7},second={.sd=s,.value=9},wild={.sd=s,.value=11};
    first.token=dw4_scriptservices_register(s,1,"MODELCTRL","first",7,1,handler,&first);
    second.token=dw4_scriptservices_register(s,2,"MODELCTRL","second",8,0,handler,&second);
    wild.token=dw4_scriptservices_register(s,2,"MODELCTRL",NULL,-1,1,handler,&wild);
    assert(first.token && second.token && wild.token);
    {
        dw4_script_value query[]={str("MODELCTRL"),(dw4_script_value){0},num(-1),str("ISRUN")},r;
        char error[128];first.value=wild.value=0;second.value=1;
        assert(!dw4_scriptservices_call(s,"querySD",query,4,&r,error,sizeof error) && r.number==0);
        assert(!dw4_scriptservices_any(s,query,4,&r,error,sizeof error) && r.type==DW4_SCRIPT_NUMBER && r.number==1);
        second.value=0;
        assert(!dw4_scriptservices_any(s,query,4,&r,error,sizeof error) && !r.number);
        second.value=256;assert(!dw4_scriptservices_any(s,query,4,&r,error,sizeof error) && !r.number);
        second.value=-1;assert(!dw4_scriptservices_any(s,query,4,&r,error,sizeof error) && r.number==1);
        assert(!dw4_scriptservices_category(s,"ENEMY"));query[0]=str("ENEMY");
        assert(!dw4_scriptservices_any(s,query,4,&r,error,sizeof error) && r.type==DW4_SCRIPT_NUMBER && !r.number);
        first.value=7;second.value=9;wild.value=11;
    }
    double result;
    assert(!send(s,"querySD","first",7,"ISRUN",NULL,0,0,&result) && result==7);
    assert(!send(s,"querySD","first",8,"ISRUN",NULL,0,0,&result) && result==11);
    assert(!send(s,"querySD",NULL,8,"ISRUN",NULL,0,0,&result) && result==9);
    assert(!send(s,"querySD",NULL,-2,"ISRUN",NULL,0,0,&result) && result==9);
    dw4_scriptservices_active(s,second.token,1);
    assert(!send(s,"querySD",NULL,-2,"ISRUN",NULL,0,0,&result) && isnan(result));
    assert(!send(s,"sd","",7,"EVENT",NULL,0,0,NULL)); /* empty differs from nil */
    first.remove=wild.token;first.reenter=1;
    unsigned before=second.calls;
    assert(!send(s,"sd",NULL,-1,"EVENT",NULL,0,0,NULL));
    assert(second.calls==before+2); /* nested and outer; removed wildcard skipped */
    first.calls=second.calls=0;
    char owned[]="owned";
    dw4_script_value a[]={str("MODELCTRL"),str("first"),num(7),str("EVENT"),str(owned),num(240)},r={0};
    char error[512]={0};
    assert(!dw4_scriptservices_tick(s,100));
    dw4_scriptservices_scope(s,1);
    assert(!dw4_scriptservices_call(s,"sd",a,6,&r,error,sizeof(error)));
    owned[0]='X';
    assert(!dw4_scriptservices_tick(s,100+3999999840ULL-1) && !first.calls);
    assert(!dw4_scriptservices_tick(s,100+3999999840ULL) && first.calls==1);
    assert(!strcmp(first.optional,"owned"));
    /* Delayed lookup sees replacement receivers; never captures freed user pointers. */
    assert(!send(s,"sd","first",7,"EVENT",NULL,1,1,NULL));
    dw4_scriptservices_unregister(s,first.token);
    first.token=dw4_scriptservices_register(s,1,"MODELCTRL","first",7,1,handler,&first);
    assert(first.token);
    assert(!dw4_scriptservices_tick(s,100+3999999840ULL+16666666) && first.calls==2);
    assert(!send(s,"sd","first",7,"EVENT",NULL,0,1,NULL));
    assert(dw4_scriptservices_pending(s)==1); /* direct zero delay is still queued */
    dw4_scriptservices_cancel(s,1);assert(!dw4_scriptservices_pending(s));
    assert(!send(s,"sd","first",7,"EVENT",NULL,1,1,NULL));
    dw4_scriptservices_remove_scope(s,1);assert(!dw4_scriptservices_pending(s));
    assert(!send(s,"querySD","first",7,"ISRUN",NULL,0,0,&result) && isnan(result));
    a[0]=str("UNKNOWN");
    assert(dw4_scriptservices_call(s,"querySD",a,4,&r,error,sizeof(error)) && strstr(error,"UNKNOWN"));
    /* Failure is permanent and stops subsequent due messages. */
    second.fail=1;
    assert(!send(s,"sd","second",8,"EVENT",NULL,0,1,NULL));
    assert(dw4_scriptservices_tick(s,5000000000ULL));
    assert(strstr(dw4_scriptservices_error(s),"rejected EVENT"));
    second.fail=0;assert(dw4_scriptservices_tick(s,6000000000ULL));
    dw4_scriptservices_close(s);
    puts("SD services: receiver selection, timed/immediate reentrancy, scoped follow-ups, 128 recreations, expiry, replacement, cancellation and failure passed");
    return 0;
}
