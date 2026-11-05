#include "dw4/scriptengine.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
struct host {dw4_scriptengine *engine;dw4_scriptservices *sd;unsigned nested;};
static int source(void *u,const char *name,const void **bytes,size_t *size)
{
    (void)u;const char *code=NULL;
    if(!strcmp(name,"outer.lua"))code="first=be:TXTgetCallNo() be:SYSgetArea() after=be:TXTgetCallNo() [EOF]";
    else if(!strcmp(name,"nested.lua"))code="nested=be:TXTgetCallNo() [EOF]";
    else if(!strcmp(name,"cancel.lua"))code="be:SYSgetCountry() after_cancel=be:TXTgetCallNo() [EOF]";
    if(!code)return 2;
    *bytes=code;*size=strlen(code);return 0;
}
static int binding(void *u,const char *m,const dw4_script_value *a,size_t n,dw4_script_value *r,char *e,size_t cap)
{
    struct host *h=u;(void)a;(void)r;(void)e;(void)cap;assert(!n);
    assert(!dw4_scriptengine_can_start(h->engine));
    assert(dw4_scriptengine_reset_scene(h->engine,h->sd)==-1);
    if(!strcmp(m,"SYSgetArea")){
        assert(dw4_scriptengine_scope(h->engine)==100);
        assert(!dw4_scriptengine_text_event(h->engine,101,"nested.lua",-17));
        assert(dw4_scriptengine_scope(h->engine)==100);h->nested++;return 0;
    }
    if(!strcmp(m,"SYSgetCountry")){dw4_scriptengine_remove_scope(h->engine,102);return 0;}
    return -1;
}
static double get(dw4_script *vm,const char *key)
{dw4_script_value v;assert(!dw4_script_get(vm,key,&v) && v.type==DW4_SCRIPT_NUMBER);return v.number;}
int main(void)
{
    dw4_be_state state;dw4_be_init(&state);struct host h={.sd=dw4_scriptservices_open()};assert(h.sd);
    h.engine=dw4_scriptengine_open(&state,binding,&h);assert(h.engine);
    dw4_script *vm=dw4_scriptengine_vm(h.engine);dw4_script_source_set(vm,source,NULL,NULL);
    assert(!dw4_scriptengine_text_event(h.engine,100,"outer.lua",15));
    assert(h.nested==1 && get(vm,"first")==15 && get(vm,"nested")==-17 && get(vm,"after")==-17);
    assert(dw4_scriptengine_scope(h.engine)==0);
    assert(!dw4_scriptengine_reset_scene(h.engine,h.sd));dw4_script_source_set(vm,source,NULL,NULL);
    assert(!dw4_scriptengine_run(h.engine,"nested.lua") && get(vm,"nested")==-17);
    assert(!dw4_scriptengine_text_event(h.engine,101,"nested.lua",INT32_MIN) && get(vm,"nested")==INT32_MIN);
    assert(dw4_scriptengine_text_event(h.engine,102,"cancel.lua",30)==-1);
    assert(strstr(dw4_scriptengine_error(h.engine),"scope unloaded"));
    dw4_script_value v;assert(!dw4_script_get(vm,"after_cancel",&v) && v.type==DW4_SCRIPT_NIL);
    assert(dw4_scriptengine_scope(h.engine)==0 && !dw4_scriptengine_reset_scene(h.engine,h.sd));
    dw4_scriptengine_close(h.engine);dw4_scriptservices_close(h.sd);
    puts("text callbacks: signed/global call number, nested scope restoration, VM reset and unload guards pass");return 0;
}
