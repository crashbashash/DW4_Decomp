/* Compare the retargeted FIGHTCALC record reads with the previous property API,
 * including publication and malformed input. --dump feeds the retail oracle. */
#include "../src/fightrecord.h"
#include "dw4/reflected.h"
#include "dw4/random.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static unsigned checks;
static void compare(dw4_property_folder *p)
{
    int32_t a=123456,b=a;
    int ra=dw4_property_number(p,"TSUYOSA",&a),rb=dw4_fight_record_number(p,"TSUYOSA",&b);
    assert(ra==rb && a==b);checks++;
    size_t na=99,nb=99;
    const int32_t *va=dw4_property_array(p,"SKILL",&na),*vb=dw4_fight_record_array(p,"SKILL",&nb);
    assert(na==nb && !!va==!!vb && (!va || !memcmp(va,vb,na*sizeof *va)));checks++;
    size_t n=0;const dw4_item_record *items=dw4_property_items(p,"WAZALIST",&n);
    for(int base=-2;base<34;base++){
        a=b=123456;ra=-1;
        for(size_t i=0;items && i<n;i++)if(items[i].revision==base){a=items[i].record;ra=0;break;}
        rb=dw4_fight_record_technique(p,base,&b);
        assert(ra==rb && a==b);checks++;
    }
}
static void fill(dw4_property_folder *p,dw4_random *rng)
{
    int32_t values[16];dw4_item_record items[16];
    size_t n=dw4_random_next(rng)%17;
    for(size_t i=0;i<n;i++){
        values[i]=(int32_t)dw4_random_next(rng);
        items[i]=(dw4_item_record){9,(int32_t)dw4_random_next(rng),0,(int32_t)(dw4_random_next(rng)%32),0};
        if(!(dw4_random_next(rng)%5))items[i]=(dw4_item_record){.kind=-1};
    }
    assert(!dw4_property_set_number(p,"TSUYOSA",(int32_t)dw4_random_next(rng)));
    assert(!dw4_property_set_array(p,"SKILL",values,n));
    assert(!dw4_property_set_items(p,"WAZALIST",items,n));
}
static void malformed(dw4_property_folder *p)
{
    int32_t values[]={1,2},out=333;size_t n=33;
    dw4_item_record item={9,17,0,12,0};
    assert(!dw4_property_set_array(p,"SKILL",values,2));
    assert(!dw4_property_set_items(p,"WAZALIST",&item,1));
    dw4_property_ref ref=dw4_property_reference(p,"SKILL",DW4_PROPERTY_ARRAY);
    beDataObjIntList *r=DW4_ARENA_OBJ(ref.arena,beDataObjIntList,ref.record);
    assert(r);
    igIntList *list=DW4_ARENA_OBJ(ref.arena,igIntList,((dw4_handle){(uint32_t)r->_data}));
    int32_t count=list->_count,data=list->_data;
    list->_count=-1;assert(!dw4_fight_record_array(p,"SKILL",&n) && !n);
    list->_count=list->_capacity+1;assert(!dw4_fight_record_array(p,"SKILL",&n) && !n);
    list->_count=count;list->_data=1;assert(!dw4_fight_record_array(p,"SKILL",&n) && !n);
    list->_data=data;
    ref=dw4_property_reference(p,"WAZALIST",DW4_PROPERTY_ITEMS);
    beDataObjObjectList *o=DW4_ARENA_OBJ(ref.arena,beDataObjObjectList,ref.record);
    beNDMWItemBaseList *il=DW4_ARENA_OBJ(ref.arena,beNDMWItemBaseList,((dw4_handle){(uint32_t)o->_data}));
    count=il->_count;il->_count=il->_capacity+1;
    assert(dw4_fight_record_technique(p,12,&out)==-1 && out==333);il->_count=count;
    int32_t *handles=dw4_arena_at(ref.arena,(dw4_handle){(uint32_t)il->_data},4),saved=*handles;
    *handles=1;assert(dw4_fight_record_technique(p,12,&out)==-1 && out==333);*handles=saved;
    checks+=5;
}
static void dump(dw4_property_folder *p)
{
    for(int round=0;round<24;round++){
        dw4_item_record items[16];int n=round%17;
        for(int i=0;i<n;i++)items[i]=(dw4_item_record){9,(round-10)*100+i,0,(i*7+round)%13-3,0};
        assert(!dw4_property_set_items(p,"WAZALIST",items,(size_t)n));
        printf("L %d",n);for(int i=0;i<n;i++)printf(" %d %d",items[i].record,items[i].revision);putchar('\n');
        for(int base=-4;base<12;base++){
            int32_t row=123456;int rc=dw4_fight_record_technique(p,base,&row);
            printf("Q %d %d %d\n",base,rc,row);
        }
    }
}
int main(int argc,char **argv)
{
    dw4_playerrecords *players=dw4_playerrecords_open(),*staged=dw4_playerrecords_open();assert(players && staged);
    dw4_property_folder *p=dw4_playerrecords_get(players,"GETPLAYER",0);
    if(argc==2 && !strcmp(argv[1],"--dump")){dump(p);goto done;}
    compare(NULL);compare(p);
    assert(!dw4_property_set_string(p,"TSUYOSA","wrong type"));compare(p);
    dw4_property_folder *other=dw4_playerrecords_get(players,"GETPLAYER",1);
    assert(!dw4_property_set_number(other,"SKILL",42) && !dw4_property_set_array(other,"WAZALIST",NULL,0));compare(other);
    dw4_random rng;dw4_random_init(&rng);
    for(int round=0;round<200;round++){
        for(int slot=2;slot<4;slot++){
            p=dw4_playerrecords_get(players,"GETPLAYER",slot);fill(p,&rng);compare(p);
            dw4_property_folder *s=dw4_playerrecords_get(staged,"GETPLAYER",slot);fill(s,&rng);
            assert(!dw4_property_commit_values(p,s));compare(p);compare(s);
        }
        if(!(round%20)){
            dw4_playerrecords *snap=dw4_playerrecords_snapshot(players);assert(snap);
            for(int slot=0;slot<4;slot++)compare(dw4_playerrecords_get(snap,"GETPLAYER",slot));
            dw4_playerrecords_close(snap);
        }
    }
    p=dw4_playerrecords_get(players,"GETPLAYER",2);malformed(p);compare(p);
    dw4_property_folder *common=dw4_playerrecords_get(players,"GETCOMMON",0);
    int32_t counters[16]={3,5,8};uint8_t flags[1024]={0},folder[12]={0};size_t n=0;
    p=dw4_playerrecords_get(staged,"GETPLAYER",0);
    assert(!dw4_property_set_array(p,"BASE_COUNTER",counters,16));
    assert(!dw4_property_set_bytes(p,"BASE_FLAG",flags,sizeof flags));
    assert(!dw4_property_set_bytes(p,"BASE_FLAGFOLDER",folder,sizeof folder));
    assert(!dw4_playerrecords_publish(players,staged,0));
    const int32_t *a=dw4_fight_record_array(common,"COUNTER",&n);assert(a && n==16 && a[2]==8);checks++;
    p=dw4_playerrecords_get(players,"GETPLAYER",0);counters[2]=-999;
    assert(!dw4_property_set_array(p,"BASE_COUNTER",counters,16));
    a=dw4_fight_record_array(common,"COUNTER",&n);assert(a && n==16 && a[2]==-999);checks++;
    dw4_playerrecords *snap=dw4_playerrecords_snapshot(players);assert(snap);
    a=dw4_fight_record_array(dw4_playerrecords_get(snap,"GETCOMMON",0),"COUNTER",&n);
    assert(a && n==16 && a[2]==-999);checks++;dw4_playerrecords_close(snap);
    printf("fight record retarget: %u comparisons, publication/snapshot, wrong types and invalid handles pass\n",checks);
done:
    dw4_playerrecords_close(players);dw4_playerrecords_close(staged);
    assert(!dw4_arena_live(dw4_session_arena(),DW4_REGION_PERSISTENT));dw4_session_arena_close();
    return 0;
}
