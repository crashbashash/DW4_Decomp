#include "dw4/statusstats.h"
#include "../src/statuswork.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
struct sink {unsigned calls;int fail;};
static int io(void *u,const dw4_statusstats_command *c)
{(void)c;struct sink *s=u;s->calls++;return s->fail;}
static const char *name(void *u,int32_t id)
{(void)id;return u;}
int main(void)
{
    dw4_playerrecords *players=dw4_playerrecords_open();assert(players);
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",3);
    uint16_t codes[]={65,0x2192,0xfffe};dw4_unicode_object objects[]={{codes,3,1},{NULL,0,1},{NULL,0,0}},v;
    assert(!dw4_property_set_unicode_objects(f,"PLAYERNAME",objects,3));codes[0]=66;
    assert(!dw4_property_unicode_object(f,"PLAYERNAME",0,&v) && v.codes[0]==65 && v.count==3);
    assert(!dw4_property_unicode_object(f,"PLAYERNAME",1,&v) && v.present && !v.count);
    assert(!dw4_property_unicode_object(f,"PLAYERNAME",2,&v) && !v.present);
    assert(dw4_property_unicode_object(f,"PLAYERNAME",3,&v));
    assert(dw4_property_set_string(f,"PLAYERNAME","wrong type"));
    dw4_unicode_object invalid={NULL,1,1};assert(dw4_property_set_unicode_objects(f,"PLAYERNAME",&invalid,1));
    assert(!dw4_property_unicode_object(f,"PLAYERNAME",0,&v) && v.codes[0]==65);
    struct sink s={0};dw4_statusstats_snapshot snapshot={0};char error[256];
    assert(dw4_statusstats_preview(&snapshot,players,3,1,io,&s,error,sizeof error) && !s.calls);
    assert(dw4_statusstats_update(&snapshot,players,3,name,"Species",io,&s,error,sizeof error) && !s.calls);
    const char *keys[]={"LEVEL","DIGIMONNO","XDATA","BIT","EXP","NEXTEXP","MHP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO","HP","MP"};
    for(size_t i=0;i<sizeof keys/sizeof *keys;i++)assert(!dw4_property_set_number(f,keys[i],(int32_t)i));
    assert(dw4_statusstats_update(&snapshot,players,3,name,NULL,io,&s,error,sizeof error) && !s.calls);
    assert(!dw4_statusstats_update(&snapshot,players,3,name,"Species",io,&s,error,sizeof error) && s.calls==19);
    assert(snapshot.valid && snapshot.player==3 && snapshot.value[11]==17 && snapshot.value[12]==18);
    s.calls=0;assert(dw4_statusstats_preview(&snapshot,players,2,1,io,&s,error,sizeof error) && !s.calls);
    /* Failed display does not allow preview-off to mutate records afterward. */
    assert(!dw4_property_set_number(f,"HP",777));s.fail=1;
    assert(dw4_statusstats_preview(&snapshot,players,3,0,io,&s,error,sizeof error) && !snapshot.valid);
    int32_t hp;assert(!dw4_property_number(f,"HP",&hp) && hp==777);
    s.calls=0;s.fail=0;assert(dw4_statusstats_preview(&snapshot,players,3,0,io,&s,error,sizeof error) && !s.calls);
    assert(!dw4_statusstats_update(&snapshot,players,3,name,"Species",io,&s,error,sizeof error));
    s.fail=1;assert(dw4_statusstats_update(&snapshot,players,3,name,"Species",io,&s,error,sizeof error) && !snapshot.valid);
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    for(int i=0;i<128;i++){
        dw4_statusstats owner={0},borrower={0};assert(!dw4_statusstats_bind(&owner,(dw4_handle){0}));
        beNDMWStatusInfoWork *w=DW4_ARENA_OBJ(a,beNDMWStatusInfoWork,owner.work);
        assert(dw4_arena_object_is(a,al_handle(w->_parameter),dw4_metaobject_find("igIntList")->vtable));
        assert(dw4_arena_object_is(a,al_handle(w->_preview),dw4_metaobject_find("igIntList")->vtable));
        assert(!dw4_statusstats_bind(&borrower,owner.work));
        assert(!al_reserve(a,w->_parameter,4,13));al_list(a,w->_parameter)->_count=13;
        int32_t *v=al_words(a,w->_parameter);for(int j=0;j<13;j++)v[j]=j+i;
        dw4_statusstats_snapshot copied=dw4_statusstats_state(&owner);v[11]=777;
        assert(copied.value[11]==i+11 && dw4_statusstats_state(&borrower).value[11]==777);
        dw4_statusstats_close(&borrower);assert(dw4_statusstats_state(&owner).valid);
        dw4_statusstats_close(&owner);assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==before);
    }
    dw4_playerrecords_close(players);
    puts("STATUS stats: Unicode ownership/types, dependency preflight, snapshot isolation and failed-sink holds pass");
    return 0;
}
