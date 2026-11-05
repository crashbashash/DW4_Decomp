#include "dw4/playertransactions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static void seed(dw4_property_folder *f,const dw4_item_record *v,size_t n)
{
    const char *keys[]={"POWERSOCKETREF","POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};
    const size_t sizes[]={3,5,1,5,1};int32_t empty[5]={-1,-1,-1,-1,-1};
    assert(!dw4_property_set_number(f,"ISUSE",1) && !dw4_property_set_items(f,"DEVICEFOLDER",v,n));
    for(unsigned k=0;k<5;k++)assert(!dw4_property_set_array(f,keys[k],empty,sizes[k]));
}
int main(void)
{
    for(unsigned cycle=0;cycle<128;cycle++){
        dw4_playerrecords *p=dw4_playerrecords_open();assert(p);
        dw4_property_folder *a=dw4_playerrecords_get(p,"GETPLAYER",0),*b=dw4_playerrecords_get(p,"GETPLAYER",1);
        dw4_item_record values[]={
            {0,7,0,50,2},{0,7,0,50,2},{1,8,1,0,0},{0,276,0,1000,0},
            {3,9,0,0,0},{0,9,1,10,0},{3,1,0,0,0},{0,8,0,100,0}};
        seed(a,values,8);seed(b,NULL,0);int result;size_t n;
        int32_t weapon[]={5,-1,-1},mainref[]={2};
        assert(!dw4_property_set_array(a,"POWERSOCKETREF",weapon,3) && !dw4_property_set_array(a,"MAINSLOTREF",mainref,1));
        const dw4_item_record *old=dw4_property_items(a,"DEVICEFOLDER",&n);
        assert(!dw4_playertransactions_remove_item(p,0,2,&result) && !result && dw4_property_items(a,"DEVICEFOLDER",&n)==old);
        assert(!dw4_playertransactions_remove_item(p,0,1,&result) && result);
        const dw4_item_record *v=dw4_property_items(a,"DEVICEFOLDER",&n);assert(n==7 && v[0].record==7 && v[1].record==8);
        const int32_t *refs=dw4_property_array(a,"POWERSOCKETREF",&n);assert(refs[0]==4);
        refs=dw4_property_array(a,"MAINSLOTREF",&n);assert(refs[0]==1);
        assert(!dw4_playertransactions_give_item(p,0,1,0,&result) && result);
        v=dw4_property_items(b,"DEVICEFOLDER",&n);assert(n==1 && !memcmp(v,values,sizeof *v));
        refs=dw4_property_array(a,"POWERSOCKETREF",&n);assert(refs[0]==3);
        assert(!dw4_playertransactions_sort_device(p,0));
        v=dw4_property_items(a,"DEVICEFOLDER",&n);assert(n==6);
        /* Equipped identities precede unowned sorted partitions. */
        assert(v[0].kind==0 && v[0].record==9 && v[1].kind==1 && v[1].record==8);
        assert(v[2].record==8 && v[3].record==276 && v[4].record==1 && v[5].record==9);
        refs=dw4_property_array(a,"POWERSOCKETREF",&n);assert(refs[0]==0);
        refs=dw4_property_array(a,"MAINSLOTREF",&n);assert(refs[0]==1);
        dw4_item_record full[36];for(unsigned i=0;i<36;i++)full[i]=(dw4_item_record){3,(int32_t)i,0,0,0};
        assert(!dw4_property_set_items(b,"DEVICEFOLDER",full,36));old=dw4_property_items(a,"DEVICEFOLDER",&n);
        assert(!dw4_playertransactions_give_item(p,0,1,2,&result) && !result && dw4_property_items(a,"DEVICEFOLDER",&n)==old);
        assert(dw4_playertransactions_give_item(p,0,0,2,&result)==-1);
        /* Both destinations are preflighted before the first publication. */
        dw4_playerrecords *s=dw4_playerrecords_open();assert(s);
        dw4_property_folder *sa=dw4_playerrecords_get(s,"GETPLAYER",0),*sb=dw4_playerrecords_get(s,"GETPLAYER",1);
        assert(!dw4_property_set_number(a,"MARKER",1));assert(!dw4_property_set_string(b,"BAD","unchanged"));
        assert(!dw4_property_set_number(sa,"MARKER",2) && !dw4_property_set_number(sb,"BAD",3));
        assert(dw4_property_commit_pair(a,sa,b,sb)==-1);int32_t marker;
        assert(!dw4_property_number(a,"MARKER",&marker) && marker==1 && !strcmp(dw4_property_string(b,"BAD"),"unchanged"));
        dw4_playerrecords_close(s);
        assert(!dw4_property_set_number(a,"BIT",1000) && !dw4_property_set_number(b,"BIT",9999000));
        assert(!dw4_playertransactions_give_bit(p,0,1,999,&result) && result);
        assert(!dw4_property_number(a,"BIT",&marker) && marker==1);
        assert(!dw4_property_number(a,"ISUSE",&marker) && marker==1 && !dw4_property_number(b,"ISUSE",&marker) && marker==1);
        assert(!dw4_property_number(b,"BIT",&marker) && marker==9999999);
        assert(!dw4_playertransactions_give_bit(p,0,1,1,&result) && !result);
        assert(!dw4_property_number(a,"BIT",&marker) && marker==1);
        assert(!dw4_property_number(a,"ISUSE",&marker) && marker==1 && !dw4_property_number(b,"ISUSE",&marker) && marker==1);
        assert(!dw4_playertransactions_give_bit(p,0,1,0,&result) && !result);
        assert(dw4_playertransactions_give_bit(p,0,0,1,&result)==-1);
        assert(dw4_playertransactions_give_bit(p,0,1,-1,&result)==-1);
        dw4_item_record ad[12],bd[12];for(int i=0;i<12;i++)ad[i]=bd[i]=(dw4_item_record){4,i,0,0,0};
        ad[1].revision=9;bd[1].revision=8;
        assert(!dw4_property_set_items(a,"DISKFOLDER",ad,12) && !dw4_property_set_items(b,"DISKFOLDER",bd,12));
        assert(!dw4_playertransactions_swap_disk(p,0,0,1));
        assert(dw4_playertransactions_swap_disk(p,0,0,10)==-1);
        assert(!dw4_playertransactions_give_disk(p,0,1,0,1,&result) && result);
        const dw4_item_record *disk=dw4_property_items(a,"DISKFOLDER",&n);assert(n==12 && disk[0].record==1 && disk[0].revision==8 && disk[11].record==11);
        disk=dw4_property_items(b,"DISKFOLDER",&n);assert(disk[1].revision==9);
        assert(!dw4_property_number(a,"ISUSE",&marker) && marker==1 && !dw4_property_number(b,"ISUSE",&marker) && marker==1);
        assert(!dw4_playertransactions_give_disk(p,0,1,0,1,&result) && !result);
        assert(dw4_playertransactions_give_disk(p,0,1,10,1,&result)==-1);
        dw4_playerrecords_close(p);
    }
    puts("inventory detail: 128 exact-identity remove/give/sort lifetimes; equipped guards, full-recipient holds, reference remapping and two-destination rollback pass");return 0;
}
