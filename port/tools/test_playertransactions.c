#include "dw4/playertransactions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int attribute(void *u,const dw4_item_record *i,const char *key,int32_t *v)
{
    if(u)return -1;
    *v=(!strcmp(key,"TSUYOSA") && i->record<2) || (!strcmp(key,"SUBAYASA") && i->record>=2);
    return 0;
}
static int recalc(void *u,dw4_property_folder *f)
{
    const char *names[]={"new_weapon",NULL,NULL};
    assert(!dw4_property_set_strings(f,"POWERSOCKETNAME",names,3));
    assert(!dw4_property_set_number(f,"TSUYOSA",123));
    return u?-1:0;
}
static void init(dw4_property_folder *f)
{
    dw4_item_record items[]={{0,0,1,0,0},{0,0,1,0,0},{0,1,0,17,2},{3,0,0,0,0},{3,1,0,0,0},{3,2,0,0,0}};
    int32_t refs[]={0,1,-1},empty[]={-1,-1,-1,-1,-1};dw4_item_record none[5];
    for(unsigned i=0;i<5;i++)none[i]=(dw4_item_record){.kind=-1};
    const char *keys[]={"POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
    const char *links[]={"POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};size_t n[]={5,1,5,1};
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",items,6));
    assert(!dw4_property_set_items(f,"POWERSOCKET",items,3));
    assert(!dw4_property_set_array(f,"POWERSOCKETREF",refs,3));
    for(unsigned i=0;i<4;i++){assert(!dw4_property_set_array(f,links[i],empty,n[i]));assert(!dw4_property_set_items(f,keys[i],none,n[i]));}
    const char *names[]={"old0","old1",NULL};assert(!dw4_property_set_strings(f,"POWERSOCKETNAME",names,3));
    assert(!dw4_property_set_number(f,"TSUYOSA",99));
}
int main(void)
{
    for(unsigned cycle=0;cycle<128;cycle++){
        dw4_playerrecords *p=dw4_playerrecords_open();assert(p);
        for(int slot=0;slot<4;slot++){
            dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);init(f);
            dw4_property_folder *child=dw4_property_child(f,"unrelated",1);assert(child);
            assert(!dw4_property_set_number(child,"marker",42));
            size_t n;const dw4_item_record *before=dw4_property_items(f,"DEVICEFOLDER",&n);
            const char *oldname=dw4_property_string_at(f,"POWERSOCKETNAME",0);
            /* Failure after partial staged writes retains all original buffers. */
            assert(dw4_playertransactions_equip(p,slot,"POWERSOCKET",0,2,NULL,NULL,recalc,(void *)1)==-1);
            assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before && dw4_property_string_at(f,"POWERSOCKETNAME",0)==oldname);
            assert(!dw4_playertransactions_preview(p,slot,"POWERSOCKET",0,2,NULL,NULL,recalc,NULL));
            assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before && dw4_property_string_at(f,"POWERSOCKETNAME",0)==oldname);
            assert(!dw4_playertransactions_equip(p,slot,"POWERSOCKET",0,2,NULL,NULL,recalc,NULL));
            const int32_t *r=dw4_property_array(f,"POWERSOCKETREF",&n);assert(r[0]==2 && r[1]==1);
            const dw4_item_record *v=dw4_property_items(f,"DEVICEFOLDER",&n);assert(v[0].equipped==0 && v[1].equipped==1 && v[2].equipped==1);
            assert(dw4_property_child(f,"unrelated",0)==child);
            int32_t marker;assert(!dw4_property_number(child,"marker",&marker) && marker==42);
            /* Same record number, distinct identity: only the unowned copy is removed. */
            int result=-1;assert(!dw4_playertransactions_device(p,slot,DW4_DEVICE_CLR,0,0,0,0,&result) && result==1);
            r=dw4_property_array(f,"POWERSOCKETREF",&n);assert(r[0]==1 && r[1]==0);
            assert(!dw4_playertransactions_device(p,slot,DW4_DEVICE_CLR,0,0,0,0,&result) && !result);
            assert(!dw4_playertransactions_equip(p,slot,"POWERSOCKET",0,1,NULL,NULL,recalc,NULL));
            r=dw4_property_array(f,"POWERSOCKETREF",&n);assert(r[0]==-1);
            /* Chip family exclusion only removes the first positive family. */
            assert(!dw4_playertransactions_equip(p,slot,"POWERPOCKET",0,2,attribute,NULL,recalc,NULL));
            assert(!dw4_playertransactions_equip(p,slot,"POWERPOCKET",1,4,attribute,NULL,recalc,NULL));
            assert(!dw4_playertransactions_equip(p,slot,"POWERPOCKET",2,3,attribute,NULL,recalc,NULL));
            r=dw4_property_array(f,"POWERPOCKETREF",&n);assert(r[0]==-1 && r[1]==4 && r[2]==3);
            assert(dw4_playertransactions_equip(p,slot,"MAINPOCKET",0,3,attribute,NULL,recalc,NULL)==-1);
            v=dw4_property_items(f,"DEVICEFOLDER",&n);before=v;
            assert(dw4_playertransactions_equip(p,slot,"POWERPOCKET",0,2,attribute,(void *)1,recalc,NULL)==-1);
            assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
            while(n<36){assert(!dw4_playertransactions_device(p,slot,DW4_DEVICE_SET,2,77,123,99,&result) && result);n++;}
            assert(!dw4_playertransactions_device(p,slot,DW4_DEVICE_ISMAX,0,0,0,0,&result) && result);
            before=dw4_property_items(f,"DEVICEFOLDER",&n);
            assert(!dw4_playertransactions_device(p,slot,DW4_DEVICE_SET,0,88,0,0,&result) && !result);
            assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
            assert(before[35].revision==123 && before[35].pocket==0);
            /* Preserve signed bits and all other species across persistence. */
            int32_t base[176]={0},skills[9],up[11];
            for(int i=0;i<9;i++)skills[i]=i?i:-2147483647-1;
            for(int i=0;i<11;i++)up[i]=-i;
            assert(!dw4_property_set_array(f,"BASE_LEVEL",base,16));assert(!dw4_property_set_array(f,"BASE_EXP",base,16));
            assert(!dw4_property_set_array(f,"BASE_SKILL",base,144));assert(!dw4_property_set_array(f,"BASE_UPCNT",base,176));
            assert(!dw4_property_set_array(f,"SKILL",skills,9));assert(!dw4_property_set_array(f,"UPCNT",up,11));
            assert(!dw4_property_set_number(f,"LEVEL",-1));assert(!dw4_property_set_number(f,"EXP",2147483647));
            for(int species=0;species<16;species++){
                assert(!dw4_property_set_number(f,"DIGIMONNO",species));assert(!dw4_playertransactions_current_to_base(p,slot));
                r=dw4_property_array(f,"BASE_SKILL",&n);
                for(int done=0;done<=species;done++)assert(!memcmp(r+done*9,skills,sizeof skills));
                for(size_t i=(species+1)*9;i<n;i++)assert(!r[i]);
            }
            before=dw4_property_items(f,"DEVICEFOLDER",&n);
            assert(dw4_playertransactions_equip(p,slot,"BAD",0,0,NULL,NULL,recalc,NULL)==-1);
            assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
        }
        dw4_playerrecords_close(p);
    }
    /* Bundle type conflict does not publish earlier valid rows. */
    dw4_playerrecords *p=dw4_playerrecords_open(),*q=dw4_playerrecords_open();assert(p && q);
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0),*s=dw4_playerrecords_get(q,"GETPLAYER",0);
    assert(!dw4_property_set_number(f,"a",10));assert(!dw4_property_set_string(f,"b","old"));
    assert(!dw4_property_set_number(s,"a",20));assert(!dw4_property_set_number(s,"b",30));
    assert(dw4_property_commit_values(f,s)==-1);int32_t a;assert(!dw4_property_number(f,"a",&a) && a==10);
    dw4_playerrecords_close(q);dw4_playerrecords_close(p);
    puts("player transactions: staged failure, item identities, compaction, chip exclusion, cap, four-slot/16-species persistence and 128 lifetimes pass");
}
