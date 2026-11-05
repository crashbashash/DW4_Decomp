#include "dw4/playerrecords.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
static dw4_property_folder *player(dw4_playerrecords *r,int p){return dw4_playerrecords_get(r,"GETPLAYER",p);}
int main(void)
{
    dw4_playerrecords *original=dw4_playerrecords_open(),*staged=dw4_playerrecords_open();assert(original && staged);
    dw4_property_folder *p=player(staged,0);
    uint8_t flags[1024]={0},folder[12]={0};int32_t counters[16]={0};flags[500]=1;folder[3]=2;counters[8]=17;
    assert(!dw4_property_set_bytes(p,"BASE_FLAG",flags,sizeof flags));
    assert(!dw4_property_set_bytes(p,"BASE_FLAGFOLDER",folder,sizeof folder));
    assert(!dw4_property_set_array(p,"BASE_COUNTER",counters,16));
    assert(!dw4_property_set_number(p,"ISUSE",1) && !dw4_property_set_number(p,"BITS",1000));
    assert(!dw4_property_set_string(p,"NAME","Original"));
    int32_t ints[]={INT32_MIN,17,INT32_MAX};assert(!dw4_property_set_array(p,"ARRAY",ints,3));
    const char *strings[]={NULL,"","payload"};assert(!dw4_property_set_strings(p,"STRINGS",strings,3));
    uint16_t codes[]={0x65e5,0,0x263a};dw4_unicode_object unicode[]={{NULL,0,0},{NULL,0,1},{codes,3,1}};
    assert(!dw4_property_set_unicode_objects(p,"UNICODE",unicode,3));
    dw4_item_record items[]={{1,42,1,3,2},{4,2,0,0,0}};assert(!dw4_property_set_items(p,"ITEMS",items,2));
    uint32_t bits[]={0x80000000,0x7fc12345,0x3f800000};float floats[3];memcpy(floats,bits,sizeof floats);
    assert(!dw4_property_set_floats(p,"FLOATS",floats,3));
    dw4_property_folder *child=dw4_property_child(p,"NESTED",1);assert(child);
    dw4_property_folder *deep=dw4_property_child(child,"DEEP",1);assert(deep && !dw4_property_set_string(deep,"VALUE","owned"));
    assert(dw4_property_child(child,"EMPTY",1));
    assert(!dw4_playerrecords_publish(original,staged,0));dw4_playerrecords_close(staged);
    assert(!dw4_playerrecords_join(original,2,1));
    for(int i=1;i<4;i++)assert(!dw4_property_set_number(player(original,i),"MARKER",i*91));
    dw4_playerrecords *copy=dw4_playerrecords_snapshot(original);assert(copy);
    dw4_property_folder *common=dw4_playerrecords_get(copy,"GETCOMMON",0),*base=player(copy,0);
    size_t n;int32_t value;
    assert(!dw4_property_number(common,"NINZU",&value) && value==2);
    assert(!dw4_property_number(base,"BITS",&value) && value==1000);
    assert(!strcmp(dw4_property_string(base,"NAME"),"Original"));
    assert(!memcmp(dw4_property_array(base,"ARRAY",&n),ints,sizeof ints) && n==3);
    assert(!dw4_property_string_at(base,"STRINGS",0) && !strcmp(dw4_property_string_at(base,"STRINGS",1),"") && !strcmp(dw4_property_string_at(base,"STRINGS",2),"payload"));
    dw4_unicode_object object;
    assert(!dw4_property_unicode_object(base,"UNICODE",0,&object) && !object.present);
    assert(!dw4_property_unicode_object(base,"UNICODE",1,&object) && object.present && !object.count);
    assert(!dw4_property_unicode_object(base,"UNICODE",2,&object) && object.present && object.count==3 && !memcmp(object.codes,codes,sizeof codes));
    assert(!memcmp(dw4_property_items(base,"ITEMS",&n),items,sizeof items) && n==2);
    assert(!memcmp(dw4_property_floats(base,"FLOATS",&n),bits,sizeof bits) && n==3);
    assert(dw4_property_bytes(common,"FLAG",&n)==dw4_property_bytes(base,"BASE_FLAG",NULL) && n==1024);
    assert(dw4_property_bytes(common,"FLAG",NULL)[500]==1);
    assert(dw4_property_array(common,"COUNTER",&n)==dw4_property_array(base,"BASE_COUNTER",NULL) && n==16);
    assert(dw4_property_bytes(common,"FLAGFOLDER",&n)==dw4_property_bytes(base,"BASE_FLAGFOLDER",NULL) && n==12);
    child=dw4_property_child(base,"NESTED",0);deep=dw4_property_child(child,"DEEP",0);
    assert(child && deep && dw4_property_child(child,"EMPTY",0));
    assert(!strcmp(dw4_property_string(deep,"VALUE"),"owned"));
    assert(!dw4_property_set_number(base,"BITS",9));
    assert(!dw4_property_number(player(original,0),"BITS",&value) && value==1000);
    flags[500]=0;assert(!dw4_property_set_bytes(player(original,0),"BASE_FLAG",flags,sizeof flags));
    assert(dw4_property_bytes(common,"FLAG",NULL)[500]==1);
    dw4_playerrecords_close(original);
    assert(!strcmp(dw4_property_string(deep,"VALUE"),"owned") && dw4_property_bytes(common,"FLAG",NULL)[500]==1);
    for(int i=1;i<4;i++)assert(!dw4_property_number(player(copy,i),"MARKER",&value) && value==i*91);
    flags[500]=2;assert(!dw4_property_set_bytes(base,"BASE_FLAG",flags,sizeof flags));
    assert(dw4_property_bytes(common,"FLAG",NULL)[500]==2);
    dw4_playerrecords *again=dw4_playerrecords_snapshot(copy);assert(again);dw4_playerrecords_close(copy);
    assert(dw4_property_bytes(dw4_playerrecords_get(again,"GETCOMMON",0),"FLAG",NULL)[500]==2);
    dw4_playerrecords_close(again);assert(!dw4_playerrecords_snapshot(NULL));
    puts("session snapshot: nine payload kinds, nested/empty folders, null/empty Unicode, float bits, all four players, aliases and source/candidate lifetime isolation pass");return 0;
}
