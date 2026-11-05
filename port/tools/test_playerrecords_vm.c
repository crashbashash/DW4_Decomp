#include "dw4/playerrecords.h"
#include "dw4/reflected.h"
#include "dw4/scriptengine.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int binding(void *u,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *e,size_t cap)
{int rc=dw4_playerrecords_call(u,method,a,n,r,e,cap);return rc==1?-1:rc;}
static int source(void *u,const char *name,const void **bytes,size_t *size)
{if(strcmp(name,"records.lua"))return 2;*bytes=u;*size=strlen(u);return 0;}
static void retained_payloads(void)
{
    dw4_arena *a=dw4_session_arena();uint32_t baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    for(int cycle=0;cycle<128;cycle++){
        dw4_playerrecords *o=dw4_playerrecords_open();assert(o);
        dw4_property_folder *f=dw4_playerrecords_get(o,"GETPLAYER",0);
        int32_t values[]={3,-1,7},next[]={9};const char *strings[]={"retained",NULL,""};
        dw4_item_record item={.kind=0,.record=17};
        assert(!dw4_property_set_array(f,"LEASE",values,3));
        assert(!dw4_property_set_strings(f,"TEXT",strings,3));
        assert(!dw4_property_set_items(f,"ITEMS",&item,1));
        dw4_handle array=dw4_property_list_acquire(f,"LEASE",DW4_PROPERTY_ARRAY);
        dw4_handle text=dw4_property_list_acquire(f,"TEXT",DW4_PROPERTY_STRINGS);
        dw4_handle items=dw4_property_list_acquire(f,"ITEMS",DW4_PROPERTY_ITEMS);
        dw4_handle folder=dw4_property_folder_acquire(f);assert(array.off && text.off && items.off && folder.off);
        assert(!dw4_property_list_acquire(f,"LEASE",DW4_PROPERTY_ITEMS).off);
        igIntList *l=DW4_ARENA_OBJ(a,igIntList,array);int32_t *v=dw4_arena_at(a,(dw4_handle){(uint32_t)l->_data},12);
        igStringRefList *sl=DW4_ARENA_OBJ(a,igStringRefList,text);int32_t *sv=dw4_arena_at(a,(dw4_handle){(uint32_t)sl->_data},12);
        const char *retained=dw4_arena_at(a,(dw4_handle){(uint32_t)sv[0]},1);
        beNDMWItemBaseList *il=DW4_ARENA_OBJ(a,beNDMWItemBaseList,items);
        int32_t *iv=dw4_arena_at(a,(dw4_handle){(uint32_t)il->_data},4);dw4_handle leaf={(uint32_t)iv[0]};
        assert(dw4_arena_object_addref(a,leaf)==2);
        assert(!dw4_property_set_array(f,"LEASE",next,1));
        assert(!dw4_property_set_strings(f,"TEXT",NULL,0));assert(!dw4_property_set_items(f,"ITEMS",NULL,0));
        dw4_playerrecords_close(o);
        assert(l->_count==3 && !memcmp(v,values,sizeof values) && !strcmp(retained,"retained"));
        assert(DW4_ARENA_OBJ(a,beNDMWItemBase,leaf)->_recNo==17);
        dw4_item_record sold={.kind=3,.record=185};assert(!dw4_item_list_set(a,items,0,&sold));
        size_t count=0;const dw4_item_record *view=dw4_item_list_view(a,items,&count);
        assert(view && count==1 && view[0].kind==3 && view[0].record==185 && DW4_ARENA_OBJ(a,beNDMWItemBase,leaf)->_recNo==17);
        dw4_property_list_release(a,folder);dw4_property_list_release(a,array);dw4_property_list_release(a,text);
        dw4_property_list_release(a,items);assert(!dw4_arena_at(a,items,1));
        assert(dw4_arena_object_refcount(a,leaf)==1);dw4_property_list_release(a,leaf);
        assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
    }
}
int main(void)
{
    retained_payloads();
    dw4_playerrecords *o=dw4_playerrecords_open();assert(o);
    dw4_property_folder *f=dw4_playerrecords_get(o,"GETPLAYER",0);
    assert(!dw4_property_set_number(f,"ISUSE",1));assert(!dw4_property_set_number(f,"LEVEL",17));
    assert(!dw4_property_set_string(f,"DIGIMONNAME","m_agumon"));
    const char *names[]={"m_wp00",NULL,NULL};assert(!dw4_property_set_strings(f,"POWERSOCKETNAME",names,3));
    dw4_be_state state;dw4_be_init(&state);
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    dw4_scriptengine *engine=dw4_scriptengine_open(&state,binding,o);assert(engine);
    dw4_scriptengine_record_flags(engine,1);
    const char *code="joined=be:SYSisJoinPlayer(0) level=be:SYSgetPlayerLevel(0) name=be:SYSgetPlayerName(0) weapon=be:SYSgetWeaponName(0,0) empty=be:SYSgetWeaponName(0,2) be:FLGset(501,255) flag=be:FLGisOn(501) be:SYSsetGateStage('stagML12',3) gate=be:SYSgetGateStageName() [EOF]";
    for(unsigned i=0;i<128;i++){
        dw4_script *vm=dw4_scriptengine_vm(engine);
        dw4_script_source_set(vm,source,(void *)code,NULL);
        int rc=dw4_script_run_named(vm,"records.lua",NULL);
        if(rc)fprintf(stderr,"records.lua: %s\n",dw4_script_error(vm));
        assert(!rc);dw4_script_value v;
        assert(!dw4_script_get(vm,"joined",&v) && v.type==DW4_SCRIPT_NUMBER && v.number==1);
        assert(!dw4_script_get(vm,"level",&v) && v.number==17);
        assert(!dw4_script_get(vm,"name",&v) && v.type==DW4_SCRIPT_STRING && !strcmp(v.string,"m_agumon"));
        assert(!dw4_script_get(vm,"weapon",&v) && !strcmp(v.string,"m_wp00"));
        assert(!dw4_script_get(vm,"empty",&v) && v.type==DW4_SCRIPT_NIL);
        assert(!dw4_script_get(vm,"flag",&v) && v.type==DW4_SCRIPT_NUMBER && v.number==255);
        size_t count;const uint8_t *flags=dw4_property_bytes(dw4_playerrecords_get(o,"GETCOMMON",0),"FLAG",&count);
        assert(count==1024 && flags[501]==255);
        assert(!dw4_script_get(vm,"gate",&v) && v.type==DW4_SCRIPT_STRING && !strcmp(v.string,"stagML12"));
        int32_t gate;assert(!dw4_property_number(dw4_playerrecords_get(o,"GETCOMMON",0),"GATESTAGENO",&gate) && gate==3);
        assert(!dw4_scriptengine_reset_scene(engine,sd));
        assert(dw4_playerrecords_get(o,"GETPLAYER1",-1)==f);
        assert(!dw4_script_get(vm,"joined",&v) && v.type==DW4_SCRIPT_NIL);
    }
    dw4_scriptengine_close(engine);dw4_scriptservices_close(sd);dw4_playerrecords_close(o);
    puts("player records: 128 actual Lua/SD scene resets preserve records and clear VM globals");return 0;
}
