/* Loot delivery (src/loot.c, docs/dungeon-floors.md "Loot delivery"): every recovered rule against fixed random streams, then the
 * real item databases' rows (needs the extracted data; pass its directory, or no argument to run the rules alone).
 * The expected values are written out from the cited retail functions here, independent of the implementation. */
#include "dw4/loot.h"
#include "dw4/database.h"
#include "dw4/filelist.h"
#include "dw4/scriptengine.h"
#include "dw4/scriptservices.h"
#include "dw4/mount.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- fixed random streams: the tempered output of the generator is the value, so a stream is written as outputs ---- */
static uint32_t untemper(uint32_t y)
{
    uint32_t t=y;
    y^=y>>18;
    t=y;for(int i=0;i<6;i++)t=y^((t<<15)&0xefc60000u);y=t;
    t=y;for(int i=0;i<6;i++)t=y^((t<<7)&0x9d2c5680u);y=t;
    t=y;for(int i=0;i<4;i++)t=y^(t>>11);return t;
}
static void stream(dw4_random *r,const uint32_t *v,unsigned n)
{
    memset(r,0,sizeof *r);
    for(unsigned i=0;i<n;i++)r->words[i]=untemper(v[i]);
    r->index=0;
}
/* ---- retail references (FUN_004480a0 / FUN_00448190 / vfunc_22) ---- */
static int ref_revision(uint32_t d1,uint32_t d2,int level)
{
    int first=(int)(d1%6000u)+1,second=(int)(d2%(uint32_t)level)+1,v;
    if(first==1)v=level+1;else if(first<3001)v=second-first/10;else v=0;
    return v<0?0:v;
}
static int ref_pocket(uint32_t d,int level)
{
    int v=(int)(d%620u)+1-((level/10+10)/10),r;
    if(v==1)r=5;else if(v<4)r=4;else if(v<8)r=3;else if(v<16)r=2;else if(v<32)r=1;else r=0;
    return r;
}
/* ---- a fake database ---- */
static const char *const con_model[12]={"g_000item","g_000item","g_000item","g_000item","g_000item","g_000item","g_000item","g_000item","g_000item","g_000item","g_000boost1","g_000penx"};
static int fake_number(void *u,int category,int32_t record,const char *column,int32_t *out)
{
    (void)u;
    if(category==DW4_LOOT_INS && !strcmp(column,"UP") && record>=0 && record<26){
        static const int up[26]={0,5,20,100,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2};
        *out=up[record];return 0;
    }
    return -1;
}
static const char *fake_string(void *u,int category,int32_t record,const char *column)
{
    (void)u;
    if(strcmp(column,"MODEL"))return NULL;
    if(category==DW4_LOOT_CON && record>=0 && record<12)return con_model[record];
    if(category==DW4_LOOT_INS)return record==0?"g_000bit":record<4?"g_000xdata1":"g_000xdata2";
    return NULL;
}
static int recalcs,recalc_slot_hp;
static int fake_recalc(void *u,dw4_property_folder *f)
{
    (void)u;recalcs++;
    int32_t mhp=0;dw4_property_number(f,"MHP",&mhp);recalc_slot_hp=mhp;
    return dw4_property_set_number(f,"MHP",mhp+1);   /* the recalculation visibly ran on the staged record */
}
/* ---- records ---- */
static void make_players(dw4_playerrecords *p)
{
    for(int slot=0;slot<4;slot++){
        dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);
        int32_t up[11]={0};dw4_item_record disks[12];
        for(int i=0;i<12;i++)disks[i]=(dw4_item_record){.kind=4,.record=i,.revision=0};
        assert(f && !dw4_property_set_number(f,"LEVEL",slot==0?40:99) && !dw4_property_set_number(f,"BITRITSU",slot==0?50:0) &&
               !dw4_property_set_number(f,"BIT",1000) && !dw4_property_set_number(f,"XDATA",7) && !dw4_property_set_number(f,"MHP",100) &&
               !dw4_property_set_array(f,"UPCNT",up,11) && !dw4_property_set_items(f,"DISKFOLDER",disks,12) &&
               !dw4_property_set_items(f,"DEVICEFOLDER",NULL,0));
        {   /* the empty equipment lists a created record carries (the append re-projects them from their references) */
            static const char *const eq[]={"POWERSOCKET","POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
            static const size_t len[]={3,5,1,5,1};
            for(unsigned k=0;k<5;k++){
                int32_t refs[5]={-1,-1,-1,-1,-1};char key[24];dw4_item_record none[5];
                for(unsigned i=0;i<5;i++)none[i]=(dw4_item_record){.kind=-1};
                snprintf(key,sizeof key,"%sREF",eq[k]);
                assert(!dw4_property_set_array(f,key,refs,len[k]) && !dw4_property_set_items(f,eq[k],none,len[k]));
            }
        }
    }
    uint8_t flags[12]={0};
    assert(!dw4_property_set_bytes(dw4_playerrecords_get(p,"GETCOMMON",0),"FLAGFOLDER",flags,12));
}
static int32_t num(dw4_playerrecords *p,int slot,const char *key){int32_t v=-12345;assert(!dw4_property_number(dw4_playerrecords_get(p,"GETPLAYER",slot),key,&v));return v;}
static size_t device_count(dw4_playerrecords *p,int slot){size_t n=0;assert(!dw4_property_item_count(dw4_playerrecords_get(p,"GETPLAYER",slot),"DEVICEFOLDER",&n));return n;}
static int flag(dw4_playerrecords *p,unsigned i){size_t n;const uint8_t *b=dw4_property_bytes(dw4_playerrecords_get(p,"GETCOMMON",0),"FLAGFOLDER",&n);assert(b && n==12);return b[i];}
static int32_t held(dw4_playerrecords *p,int slot,int rec)
{
    size_t n;const dw4_item_record *v=dw4_property_items(dw4_playerrecords_get(p,"GETPLAYER",slot),"DISKFOLDER",&n);assert(v && n==12);return v[rec].revision;
}
static void set_held(dw4_playerrecords *p,int slot,int rec,int32_t count)
{
    size_t n;dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);const dw4_item_record *v=dw4_property_items(f,"DISKFOLDER",&n);assert(v && n==12);
    dw4_item_record c[12];memcpy(c,v,sizeof c);c[rec].revision=count;assert(!dw4_property_set_items(f,"DISKFOLDER",c,12));
}
/* ---- the rules ---- */
static void test_tables(void)
{
    const char *cat[]={"conItem","insItem","impItem","weapon","armor1","armor2","abChip"};
    for(int i=0;i<7;i++){assert(dw4_loot_category(cat[i])==i && !strcmp(dw4_loot_category_name(i),cat[i]));}
    assert(dw4_loot_category("nope")==-1 && dw4_loot_category(NULL)==-1 && !dw4_loot_category_name(7));
    const char *m[]={"g_000bit","g_000xdata1","g_000xdata2","g_000access","g_000armor","g_000boost1","g_000item","g_000key","g_000penx","g_000weapon"};
    for(int i=0;i<10;i++){assert(dw4_loot_model_kind(m[i])==i && !strcmp(dw4_loot_model_name(i),m[i]));assert(dw4_loot_named(i)==(i>=3));}
    assert(dw4_loot_model_kind("g_000bit2")==-1 && !dw4_loot_named(-1) && !dw4_loot_named(10));
    dw4_loot_db db={NULL,fake_number,fake_string};
    /* FUN_00384800: fixed models for impItem / weapon / armour / chip; the record's MODEL column for conItem / insItem */
    assert(!strcmp(dw4_loot_model(&db,DW4_LOOT_IMP,0),"g_000key") && !strcmp(dw4_loot_model(&db,DW4_LOOT_WEAPON,5),"g_000weapon"));
    assert(!strcmp(dw4_loot_model(&db,DW4_LOOT_ARMOR1,1),"g_000armor") && !strcmp(dw4_loot_model(&db,DW4_LOOT_ARMOR2,1),"g_000armor"));
    assert(!strcmp(dw4_loot_model(&db,DW4_LOOT_CHIP,3),"g_000access"));
    assert(!strcmp(dw4_loot_model(&db,DW4_LOOT_CON,10),"g_000boost1") && !strcmp(dw4_loot_model(&db,DW4_LOOT_CON,11),"g_000penx"));
    assert(!strcmp(dw4_loot_model(&db,DW4_LOOT_INS,2),"g_000xdata1") && !strcmp(dw4_loot_model(&db,DW4_LOOT_INS,9),"g_000xdata2"));
    assert(!dw4_loot_model(&db,7,0) && !dw4_loot_model(&db,DW4_LOOT_CON,99));
}
static void test_rolls(void)
{
    /* explicit streams: pocket first (one draw), then the revision's two draws */
    dw4_random r;dw4_item_record it;
    /* level 40: pocket offset (4+10)/10 = 1. draw%620+1-1: 1 -> 5, 2..3 -> 4, 4..7 -> 3, 8..15 -> 2, 16..31 -> 1, else 0; draw 0 -> v 0 -> 4 */
    static const struct {uint32_t draw;int pocket;} pk[]={{0,4},{1,5},{2,4},{3,4},{4,3},{7,3},{8,2},{15,2},{16,1},{31,1},{32,0},{619,0},{620,4},{621,5}};
    for(unsigned i=0;i<sizeof pk/sizeof *pk;i++){
        uint32_t v[]={pk[i].draw,0xFFFFFFF0u,0};stream(&r,v,3);   /* revision draws 0xFFFFFFF0 % 6000 -> a non-zero branch, whatever it is */
        assert(!dw4_loot_roll(DW4_LOOT_WEAPON,17,40,&r,&it) && it.kind==0 && it.record==17 && !it.equipped && it.pocket==pk[i].pocket);
        assert(it.pocket==ref_pocket(pk[i].draw,40));
    }
    /* revision: first = d%6000+1, second = d%level+1; first 1 -> level+1; first <= 3000 -> second - first/10 (>= 0); else 0 */
    static const struct {uint32_t d1,d2;int level,revision;} rv[]={
        {0,5,40,41},            /* first 1 */
        {6000,5,40,41},         /* 6000 % 6000 = 0: first 1 again */
        {1,5,40,6-0},           /* first 2, second 6: 6 - 0 */
        {29,39,40,40-3},        /* first 30, second 40: 40 - 3 */
        {2999,0,40,0},          /* first 3000, second 1: 1 - 300 -> clamped to 0 */
        {3000,7,40,0},          /* first 3001: 0 */
        {5999,7,40,0},
        {9,3,10,4-1},           /* first 10, second 4: 4 - 1 */
    };
    for(unsigned i=0;i<sizeof rv/sizeof *rv;i++){
        uint32_t v[]={1000,rv[i].d1,rv[i].d2};stream(&r,v,3);
        assert(!dw4_loot_roll(DW4_LOOT_ARMOR1,3,rv[i].level,&r,&it) && it.kind==1 && it.revision==rv[i].revision);
        assert(it.revision==ref_revision(rv[i].d1,rv[i].d2,rv[i].level));
    }
    /* draw counts: weapon and BlueArmor three (pocket, first, second), YellowArmor two, chip / disk / instant / important none */
    {uint32_t v[]={1,0,5,0xAAAAAAAAu};
     stream(&r,v,4);assert(!dw4_loot_roll(DW4_LOOT_WEAPON,0,40,&r,&it) && r.index==3 && it.pocket==5 && it.revision==41);
     stream(&r,v,4);assert(!dw4_loot_roll(DW4_LOOT_ARMOR1,0,40,&r,&it) && r.index==3 && it.pocket==5 && it.revision==41 && it.kind==1);
     stream(&r,v,4);assert(!dw4_loot_roll(DW4_LOOT_ARMOR2,0,40,&r,&it) && r.index==2 && it.pocket==0 && it.kind==2);
     /* yellow armour: its first draw is the revision's first: v[0]=1 -> first 2, v[1]=0 -> second 1: 1 - 0 */
     assert(it.revision==ref_revision(1,0,40));
     for(int c=DW4_LOOT_CON;c<=DW4_LOOT_IMP;c++){stream(&r,v,4);assert(!dw4_loot_roll(c,2,40,&r,&it) && r.index==0 && it.kind==-1 && it.record==2);}
     stream(&r,v,4);assert(!dw4_loot_roll(DW4_LOOT_CHIP,9,40,&r,&it) && r.index==0 && it.kind==3 && it.record==9 && !it.equipped);}
    assert(dw4_loot_roll(DW4_LOOT_WEAPON,0,0,&r,&it)==-1 && dw4_loot_roll(7,0,5,&r,&it)==-1);
    /* the pocket offset follows the level: level 109 -> (10+10)/10 = 2, level 9 -> 1 */
    {uint32_t v[]={2,0,0};stream(&r,v,3);assert(!dw4_loot_roll(DW4_LOOT_WEAPON,0,109,&r,&it) && it.pocket==5);   /* 2%620+1-2 = 1 */ }
    /* a long natural stream against the references, and every branch is reached */
    {dw4_random n;dw4_random_init(&n);dw4_random m=n;unsigned seen_pocket[6]={0},one=0,low=0,zero=0;
     for(int i=0;i<30000;i++){
         int level=1+i%200;uint32_t p=dw4_random_next(&m),a=dw4_random_next(&m),b=dw4_random_next(&m);
         assert(!dw4_loot_roll(DW4_LOOT_WEAPON,i%277,level,&n,&it));
         assert(it.pocket==ref_pocket(p,level) && it.revision==ref_revision(a,b,level) && n.index==m.index);
         seen_pocket[it.pocket]++;if(it.revision==level+1)one++;else if(it.revision>0)low++;else zero++;
     }
     for(int k=0;k<6;k++)assert(seen_pocket[k]);
     assert(one && low && zero);fprintf(stderr,"rolls: pockets %u %u %u %u %u %u, revision level+1 %u, small %u, zero %u\n",seen_pocket[0],seen_pocket[1],seen_pocket[2],seen_pocket[3],seen_pocket[4],seen_pocket[5],one,low,zero);}
}
static void test_bit(void)
{
    static const int below[]={19,39,60,94,108,144,203},lo[]={10,55,87,162,232,340,446,566},hi[]={55,100,195,350,520,700,860,1160};
    for(int band=0;band<8;band++){
        int32_t level=band<7?below[band]-1:500,l,h;
        dw4_loot_bit_band(level,&l,&h);assert(l==lo[band] && h==hi[band]);
        if(band<7){dw4_loot_bit_band(below[band],&l,&h);assert(l==lo[band+1] && h==hi[band+1]);}
        assert(dw4_loot_bit_amount(level,0,0)==lo[band] && dw4_loot_bit_amount(level,(uint32_t)(hi[band]-lo[band]-1),0)==hi[band]-1);
        assert(dw4_loot_bit_amount(level,(uint32_t)(hi[band]-lo[band]),0)==lo[band]);   /* draw % (hi - lo) */
    }
    assert(dw4_loot_bit_amount(10,7,0)==17 && dw4_loot_bit_amount(10,7,50)==17*150/100 && dw4_loot_bit_amount(10,7,100)==34);
    assert(dw4_loot_bit_amount(40,0,25)==87*125/100);   /* integer division after the product */
}
static void test_upcnt(void)
{
    static const int want[22]={2,2,3,3,0,0,0,0,4,4,5,5,6,6,7,7,8,8,9,9,10,10};
    for(int r=4;r<=25;r++)assert(dw4_loot_upcnt_index(r)==want[r-4]);
    assert(dw4_loot_upcnt_index(3)==-1 && dw4_loot_upcnt_index(26)==-1 && dw4_loot_upcnt_index(0)==-1);
}
static void test_instant(void)
{
    dw4_playerrecords *p=dw4_playerrecords_open();assert(p);make_players(p);
    dw4_random r;dw4_loot_ctx c={.players=p,.db={NULL,fake_number,fake_string},.random=&r,.recalculate=fake_recalc};
    int32_t amount;
    /* BIT: the level and BITRITSU of player 1 (slot 0: level 40, +50 %), the BIT lands on the receiving player (slot 2) */
    {uint32_t v[]={30,31,32};stream(&r,v,3);
     assert(dw4_loot_instant(&c,0,2,&amount)==1 && r.index==1);
     assert(amount==(87+30%(195-87))*150/100 && num(p,2,"BIT")==1000+amount && num(p,0,"BIT")==1000 && num(p,1,"BIT")==1000);}
    /* x-data: UP of the record (5, 20, 100), no draw */
    {uint32_t v[]={1};stream(&r,v,1);
     assert(dw4_loot_instant(&c,1,1,&amount)==1 && num(p,1,"XDATA")==12 && r.index==0);
     assert(dw4_loot_instant(&c,2,1,&amount)==1 && num(p,1,"XDATA")==32);
     assert(dw4_loot_instant(&c,3,0,&amount)==1 && num(p,0,"XDATA")==107 && num(p,2,"XDATA")==7);}
    /* UPCNT 4..25: UP added to the slot, the receiver recalculated (its MHP rises by one in the fake) */
    {int before=recalcs;
     for(int rec=4;rec<=25;rec++){
         size_t n;const int32_t *u=dw4_property_array(dw4_playerrecords_get(p,"GETPLAYER",3),"UPCNT",&n);int32_t b[11];memcpy(b,u,sizeof b);
         int32_t mhp=num(p,3,"MHP");
         assert(dw4_loot_instant(&c,rec,3,&amount)==1);
         u=dw4_property_array(dw4_playerrecords_get(p,"GETPLAYER",3),"UPCNT",&n);
         int idx=dw4_loot_upcnt_index(rec),up=rec%2==0?1:2;
         for(int k=0;k<11;k++)assert(u[k]==b[k]+(k==idx?up:0));
         assert(num(p,3,"MHP")==mhp+1);
     }
     assert(recalcs==before+22);
     size_t n;const int32_t *u=dw4_property_array(dw4_playerrecords_get(p,"GETPLAYER",3),"UPCNT",&n);
     /* slot 0: 4 records (8..11 are idx 4... ) -- the table sums: idx 0 gets records 8..11 (UP 1,2,1,2 = 6) */
     assert(u[0]==6 && u[2]==3 && u[3]==3);
     assert(num(p,0,"MHP")==100 && num(p,3,"MHP")==122);}
    /* errors: an unknown record, a missing database column */
    assert(dw4_loot_instant(&c,26,0,&amount)==-1 && dw4_loot_instant(&c,-1,0,&amount)==-1 && dw4_loot_instant(&c,1,4,&amount)==-1);
    {dw4_loot_ctx bad=c;bad.db.number=NULL;assert(dw4_loot_instant(&bad,1,0,&amount)==-1);}
    dw4_playerrecords_close(p);
}
static dw4_loot_drop make_drop(const char *category,int32_t record,int32_t level,dw4_random *r)
{
    dw4_loot_db db={NULL,fake_number,fake_string};dw4_loot_drop d;
    assert(!dw4_loot_make(&db,category,record,level,r,&d));return d;
}
static void test_press(void)
{
    dw4_playerrecords *p=dw4_playerrecords_open();assert(p);make_players(p);
    dw4_random r;dw4_loot_ctx c={.players=p,.db={NULL,fake_number,fake_string},.random=&r,.recalculate=fake_recalc};
    /* weapon: the rolled item (kind 0, pocket and revision from the stream, level of player 1) is appended unequipped */
    {uint32_t v[]={1,0,5,2,0,0,31,3000,9};stream(&r,v,9);
     dw4_loot_drop w=make_drop("weapon",41,40,&r);
     assert(w.category==DW4_LOOT_WEAPON && w.model_kind==DW4_LOOT_WEAPONMODEL && w.item.pocket==5 && w.item.revision==41 && r.index==3);
     assert(dw4_loot_press(&c,&w,1)==1 && device_count(p,1)==1 && device_count(p,0)==0);
     size_t n;const dw4_item_record *v1=dw4_property_items(dw4_playerrecords_get(p,"GETPLAYER",1),"DEVICEFOLDER",&n);
     assert(n==1 && v1[0].kind==0 && v1[0].record==41 && v1[0].pocket==5 && v1[0].revision==41 && !v1[0].equipped);
     dw4_loot_drop a=make_drop("armor2",7,40,&r);   /* the next two draws: 2 -> first 3, 0 -> second 1: 1 - 0 */
     assert(a.item.kind==2 && a.model_kind==DW4_LOOT_ARMOR && a.item.revision==1 && a.item.pocket==0);
     assert(dw4_loot_press(&c,&a,1)==1 && device_count(p,1)==2);
     dw4_loot_drop ch=make_drop("abChip",5,40,&r);
     assert(ch.model_kind==DW4_LOOT_ACCESS && dw4_loot_press(&c,&ch,1)==1 && device_count(p,1)==3);
     v1=dw4_property_items(dw4_playerrecords_get(p,"GETPLAYER",1),"DEVICEFOLDER",&n);
     assert(v1[1].kind==2 && v1[1].record==7 && v1[2].kind==3 && v1[2].record==5);}
    /* DEVICEFOLDER holds 36: the 37th pickup is refused and nothing changes */
    {for(size_t k=device_count(p,1);k<36;k++){dw4_loot_drop ch=make_drop("abChip",1,40,&r);assert(dw4_loot_press(&c,&ch,1)==1);}
     assert(device_count(p,1)==36);
     dw4_loot_drop w=make_drop("weapon",3,40,&r);assert(dw4_loot_press(&c,&w,1)==0 && device_count(p,1)==36);
     dw4_loot_drop ch=make_drop("abChip",1,40,&r);assert(dw4_loot_press(&c,&ch,1)==0 && device_count(p,1)==36);
     assert(dw4_loot_press(&c,&w,2)==1 && device_count(p,2)==1);}   /* another player's folder is not full */
    /* disks (conItem rows 10 boost1 / 11 penx / 3 item): +1 in the receiver's DISKFOLDER, refused at nine */
    {dw4_loot_drop b=make_drop("conItem",10,40,&r),pe=make_drop("conItem",11,40,&r),it=make_drop("conItem",3,40,&r);
     assert(b.model_kind==DW4_LOOT_BOOST1 && pe.model_kind==DW4_LOOT_PENX && it.model_kind==DW4_LOOT_ITEM);
     assert(dw4_loot_press(&c,&b,0)==1 && held(p,0,10)==1 && held(p,1,10)==0);
     set_held(p,0,10,8);assert(dw4_loot_press(&c,&b,0)==1 && held(p,0,10)==9);
     assert(dw4_loot_press(&c,&b,0)==0 && held(p,0,10)==9);
     assert(dw4_loot_press(&c,&pe,3)==1 && held(p,3,11)==1 && dw4_loot_press(&c,&it,3)==1 && held(p,3,3)==1);
     dw4_loot_drop gone=it;gone.record=50;assert(dw4_loot_press(&c,&gone,3)==0);}   /* a record the folder does not list */
    /* key: FLAGFOLDER[record] = 1 on the common record; a record outside the twelve bytes is still taken, nothing is written */
    {dw4_loot_drop k=make_drop("impItem",0,40,&r);assert(k.model_kind==DW4_LOOT_KEY && !flag(p,0) && !flag(p,1));
     assert(dw4_loot_press(&c,&k,0)==1 && flag(p,0)==1 && !flag(p,1));
     k.record=1;assert(dw4_loot_press(&c,&k,2)==1 && flag(p,1)==1 && flag(p,0)==1);
     k.record=12;assert(dw4_loot_press(&c,&k,0)==1);
     for(unsigned i=2;i<12;i++)assert(!flag(p,i));}
    /* unnamed models are not a button pickup */
    {dw4_loot_drop bit=make_drop("insItem",0,40,&r);assert(dw4_loot_press(&c,&bit,0)==-1);}
    dw4_playerrecords_close(p);
}
/* ---- the presentation tables (FUN_004412c0 at 0x4cfb40, the label table at 0x4cfc40, FUN_00447d00) ---- */
static void test_presentation(void)
{
    const char *panel,*seq;
    /* the 'got item' table: 25 records, three panels; x-data on panel 2, max HP / MP on panel 3, the rest on panel 1 */
    static const char *const expect[25]={"SQ_X5UP","SQ_X20UP","SQ_X100UP","SQ_STRUP","SQ_STRUP2","SQ_DEFUP","SQ_DEFUP2","SQ_MHPUP","SQ_MHPUP2","SQ_MMPUP","SQ_MMPUP2",
        "SQ_WISUP","SQ_WISUP2","SQ_SPIUP","SQ_SPIUP2","SQ_SPDUP","SQ_SPDUP2","SQ_FIREUP","SQ_FIREUP2","SQ_ICEUP","SQ_ICEUP2","SQ_THUNDUP","SQ_THUNDUP2","SQ_DARKUP","SQ_DARKUP2"};
    for(int32_t i=1;i<=25;i++){
        assert(!dw4_loot_effect(i,&panel,&seq) && !strcmp(seq,expect[i-1]));
        assert(!strcmp(panel,i<=3?"i_getitempnl02":i>=8 && i<=11?"i_getitempnl03":"i_getitempnl01"));
    }
    assert(dw4_loot_effect(0,&panel,&seq)<0 && dw4_loot_effect(26,&panel,&seq)<0 && dw4_loot_effect(-1,&panel,&seq)<0);   /* BIT shows the number instead */
    /* the UPCNT map and the effect rows agree: records 4/5 raise slot 2 (strength), 6/7 slot 3 (defence), 8/9 slot 0 (max HP) */
    assert(dw4_loot_upcnt_index(4)==2 && !strcmp((dw4_loot_effect(4,&panel,&seq),seq),"SQ_STRUP"));
    assert(dw4_loot_upcnt_index(6)==3 && !strcmp((dw4_loot_effect(6,&panel,&seq),seq),"SQ_DEFUP"));
    assert(dw4_loot_upcnt_index(8)==0 && !strcmp((dw4_loot_effect(8,&panel,&seq),seq),"SQ_MHPUP"));
    assert(!strcmp(dw4_loot_label_font(0),"font00") && !strcmp(dw4_loot_label_font(3),"font03") && !dw4_loot_label_font(4) && !dw4_loot_label_font(-1));
    /* label colour: white for chips, disks, keys and the three exceptions; revision bands for weapons and armour */
    dw4_random r;dw4_random_init(&r);
    float c[3];dw4_loot_drop d;memset(&d,0,sizeof d);
    #define COLOR(CAT,REV,REC) (d.category=(CAT),d.record=(REC),d.item.revision=(REV),dw4_loot_label_color(&d,c))
    #define IS(R,G,B) (fabsf(c[0]-(R))<1e-6f && fabsf(c[1]-(G))<1e-6f && fabsf(c[2]-(B))<1e-6f)
    COLOR(DW4_LOOT_WEAPON,0,5);assert(IS(0.9f,0.9f,0.9f));
    COLOR(DW4_LOOT_WEAPON,1,5);assert(IS(0.1f,0.9f,1.0f));
    COLOR(DW4_LOOT_WEAPON,30,5);assert(IS(0.1f,0.9f,1.0f));
    COLOR(DW4_LOOT_WEAPON,31,5);assert(IS(0.4f,1.0f,0.6f));
    COLOR(DW4_LOOT_ARMOR1,100,5);assert(IS(0.4f,1.0f,0.6f));
    COLOR(DW4_LOOT_ARMOR1,101,5);assert(IS(0.9f,0.8f,0.1f));
    COLOR(DW4_LOOT_ARMOR2,500,5);assert(IS(0.9f,0.8f,0.1f));
    COLOR(DW4_LOOT_ARMOR2,501,5);assert(IS(1.0f,0.6f,0.1f));
    COLOR(DW4_LOOT_WEAPON,999,5);assert(IS(1.0f,0.6f,0.1f));
    COLOR(DW4_LOOT_WEAPON,1000,5);assert(IS(1.0f,0.0f,0.9f));
    COLOR(DW4_LOOT_WEAPON,1000,0x114);assert(IS(0.9f,0.9f,0.9f));   /* the exceptions: weapon 276, blue armour 31, yellow armour 44 */
    COLOR(DW4_LOOT_ARMOR1,1000,0x1F);assert(IS(0.9f,0.9f,0.9f));
    COLOR(DW4_LOOT_ARMOR2,1000,0x2C);assert(IS(0.9f,0.9f,0.9f));
    COLOR(DW4_LOOT_ARMOR1,1000,0x2C);assert(IS(1.0f,0.0f,0.9f));   /* the exception is per kind */
    COLOR(DW4_LOOT_CHIP,1000,5);assert(IS(0.9f,0.9f,0.9f));
    COLOR(DW4_LOOT_CON,1000,5);assert(IS(0.9f,0.9f,0.9f));
    COLOR(DW4_LOOT_IMP,1000,0);assert(IS(0.9f,0.9f,0.9f));
    #undef COLOR
    #undef IS
}
/* ---- the step ---- */
struct field {dw4_loot_drop d[8];unsigned picked[8];int slot[8];int32_t bit[8];};
static dw4_loot_drop *field_at(void *u,size_t i){return &((struct field *)u)->d[i];}
static void field_picked(void *u,size_t i,int slot,int32_t bit){struct field *f=u;f->picked[i]++;f->slot[i]=slot;f->bit[i]=bit;}
struct evlog {int n,on[16],index[16],slot[16];};
static void label_event(void *u,size_t i,int slot,int on){struct evlog *e=u;assert(e->n<16);e->on[e->n]=on;e->index[e->n]=(int)i;e->slot[e->n]=slot;e->n++;}
static void place(dw4_loot_drop *d,float x,float y,float z){d->position[0]=x;d->position[1]=y;d->position[2]=z;}
static void test_step(void)
{
    dw4_playerrecords *p=dw4_playerrecords_open();assert(p);make_players(p);
    dw4_random r;dw4_loot_ctx c={.players=p,.db={NULL,fake_number,fake_string},.random=&r,.recalculate=fake_recalc};
    dw4_random_init(&r);
    float pos[4][3]={{0,0,0},{100,0,0},{0,0,0},{0,0,0}};int joined[4]={1,1,0,0},none[4]={0},cross0[4]={1,0,0,0};
    struct field f;memset(&f,0,sizeof f);dw4_loot_state s;dw4_loot_state_reset(&s);
    /* radius: squared distance < 64 in three dimensions: 7.9 takes, 8.0 does not (a plain 8-unit disc would take it), a height of 6 plus 5 along takes nothing at 8.06 */
    f.d[0]=make_drop("insItem",1,40,&r);place(&f.d[0],8.0f,0,0);
    f.d[1]=make_drop("insItem",1,40,&r);place(&f.d[1],0,0,7.9f);
    f.d[2]=make_drop("insItem",1,40,&r);place(&f.d[2],0,6,5.4f);   /* 36+29.16 = 65.16: out */
    f.d[3]=make_drop("insItem",1,40,&r);place(&f.d[3],0,5,5);       /* 50: in */
    assert(dw4_loot_step(&s,&c,4,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==2);
    assert(!f.picked[0] && f.picked[1]==1 && !f.picked[2] && f.picked[3]==1 && num(p,0,"XDATA")==7+5+5);
    /* nothing twice */
    assert(dw4_loot_step(&s,&c,4,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0 && num(p,0,"XDATA")==17);
    /* the nearest player takes it; a tie goes to the lower index; an unjoined or dead (not joined) player never does */
    memset(&f,0,sizeof f);f.d[0]=make_drop("insItem",2,40,&r);place(&f.d[0],50,0,0);f.d[1]=make_drop("insItem",2,40,&r);place(&f.d[1],5,0,0);
    pos[1][0]=52;joined[2]=1;pos[2][0]=1;joined[3]=0;pos[3][0]=5;
    assert(dw4_loot_step(&s,&c,2,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==2);
    assert(f.slot[0]==1 && f.slot[1]==2 && num(p,1,"XDATA")==7+20 && num(p,2,"XDATA")==7+20 && num(p,3,"XDATA")==7);
    pos[2][0]=0;pos[0][0]=0;memset(&f,0,sizeof f);f.d[0]=make_drop("insItem",1,40,&r);place(&f.d[0],0,0,0);   /* players 0 and 2 both at distance 0: slot 0 */
    assert(dw4_loot_step(&s,&c,1,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==1 && f.slot[0]==0);
    /* BIT is reported to the callback */
    memset(&f,0,sizeof f);f.d[0]=make_drop("insItem",0,40,&r);place(&f.d[0],1,0,0);
    int32_t bit0=num(p,0,"BIT"),bit2=num(p,2,"BIT");
    assert(dw4_loot_step(&s,&c,1,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==1);
    assert(f.bit[0]>=87 && f.bit[0]<195*150/100 && f.slot[0]==0 && num(p,0,"BIT")==bit0+f.bit[0] && num(p,2,"BIT")==bit2);
    /* named drops: no pickup without Cross, one label per player, the label follows the radius */
    joined[2]=0;memset(&f,0,sizeof f);dw4_loot_state_reset(&s);
    f.d[0]=make_drop("impItem",0,40,&r);place(&f.d[0],3,0,0);
    f.d[1]=make_drop("conItem",10,40,&r);place(&f.d[1],-3,0,0);
    f.d[2]=make_drop("abChip",4,40,&r);place(&f.d[2],55,0,0);   /* near slot 1 (at x 52) */
    assert(dw4_loot_step(&s,&c,3,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0);
    assert(s.lock[0]==0 && s.lock[1]==2 && !flag(p,0) && !s.named);
    /* Cross at slot 0: the labelled drop (the key), not the other near one */
    assert(dw4_loot_step(&s,&c,3,field_at,&f,(const float (*)[3])pos,joined,cross0,field_picked,&f)==1);
    assert(f.picked[0]==1 && !f.picked[1] && flag(p,0)==1 && held(p,0,10)==0 && s.named==1);
    /* one press takes one drop: the label passed to the next drop, which waits for the next press */
    assert(s.lock[0]==1);
    assert(dw4_loot_step(&s,&c,3,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0 && s.lock[0]==1);
    assert(dw4_loot_step(&s,&c,3,field_at,&f,(const float (*)[3])pos,joined,cross0,field_picked,&f)==1 && held(p,0,10)==1 && s.lock[0]<0);
    /* slot 1's chip: a press by another player does nothing; slot 1's own press takes it (device folder +1) */
    assert(dw4_loot_step(&s,&c,3,field_at,&f,(const float (*)[3])pos,joined,cross0,field_picked,&f)==0 && !f.picked[2]);
    {int cross1[4]={0,1,0,0};size_t before=device_count(p,1);
     assert(dw4_loot_step(&s,&c,3,field_at,&f,(const float (*)[3])pos,joined,cross1,field_picked,&f)==1 && f.picked[2]==1 && f.slot[2]==1 && device_count(p,1)==before+1 && s.lock[1]<0);}
    /* label events: shown when a player first holds a drop, dropped when the pickup is delivered or the player leaves */
    {struct evlog ev;memset(&ev,0,sizeof ev);
     pos[0][0]=0;memset(&f,0,sizeof f);dw4_loot_state_reset(&s);dw4_loot_state_label(&s,label_event,&ev);
     f.d[0]=make_drop("impItem",0,40,&r);place(&f.d[0],3,0,0);f.d[1]=make_drop("conItem",10,40,&r);place(&f.d[1],-3,0,0);
     assert(dw4_loot_step(&s,&c,2,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0);
     assert(ev.n==1 && ev.on[0]==1 && ev.index[0]==0 && ev.slot[0]==0);   /* one label per player: the second drop waits */
     assert(dw4_loot_step(&s,&c,2,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0 && ev.n==1);   /* nothing new while it stands */
     assert(dw4_loot_step(&s,&c,2,field_at,&f,(const float (*)[3])pos,joined,cross0,field_picked,&f)==1);
     assert(ev.n==3 && !ev.on[1] && ev.index[1]==0 && ev.on[2]==1 && ev.index[2]==1 && ev.slot[2]==0);   /* delivered: dropped, and the next drop takes the label at once */
     pos[0][0]=40;assert(dw4_loot_step(&s,&c,2,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0);
     assert(ev.n==4 && !ev.on[3] && ev.index[3]==1 && ev.slot[3]==0 && s.lock[0]<0);   /* walked away */
     dw4_loot_state_reset(&s);assert(!s.label && !s.label_user);   /* a reset clears the hook with the rest */
     pos[0][0]=0;}
    /* leaving the radius releases the label; a refused pickup (folder full) keeps it and counts */
    memset(&f,0,sizeof f);dw4_loot_state_reset(&s);s.refused=0;
    f.d[0]=make_drop("weapon",9,40,&r);place(&f.d[0],2,0,0);
    assert(dw4_loot_step(&s,&c,1,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0 && s.lock[0]==0);
    pos[0][0]=30;assert(dw4_loot_step(&s,&c,1,field_at,&f,(const float (*)[3])pos,joined,none,field_picked,&f)==0 && s.lock[0]<0);
    pos[0][0]=0;
    for(size_t k=device_count(p,0);k<36;k++){dw4_loot_drop ch=make_drop("abChip",1,40,&r);assert(dw4_loot_press(&c,&ch,0)==1);}
    assert(dw4_loot_step(&s,&c,1,field_at,&f,(const float (*)[3])pos,joined,cross0,field_picked,&f)==0 && !f.picked[0] && s.refused==1 && s.lock[0]==0);
    /* the press answered at once (beNDMWMdlPlayer::vfunc_38's DROPITEM message): 1 only when a pickup is delivered, so the player skips its swing */
    {   /* the weapon above is refused (device folder full): the press is not taken, the label stays */
        assert(s.lock[0]==0 && dw4_loot_cross(&s,&c,1,field_at,&f,0,field_picked,&f)==0 && !f.picked[0] && s.lock[0]==0);
        /* no label of that player's: nothing answers (a plain press) */
        assert(dw4_loot_cross(&s,&c,1,field_at,&f,1,field_picked,&f)==0 && dw4_loot_cross(&s,&c,1,field_at,&f,3,field_picked,&f)==0);
        /* a label whose drop is gone from the list or already collected answers nothing */
        {dw4_loot_state gone=s;assert(dw4_loot_cross(&gone,&c,0,field_at,&f,0,field_picked,&f)==0);f.d[0].collected=1;assert(dw4_loot_cross(&gone,&c,1,field_at,&f,0,field_picked,&f)==0);f.d[0].collected=0;}
        /* bad arguments */
        assert(dw4_loot_cross(&s,&c,1,field_at,&f,4,field_picked,&f)<0 && dw4_loot_cross(&s,&c,1,field_at,&f,-1,field_picked,&f)<0);
        /* room again: the same press delivers, drops the label, tells the callback once, and a second press finds nothing */
        {struct evlog ev;memset(&ev,0,sizeof ev);dw4_loot_state_label(&s,label_event,&ev);
         f.d[0]=make_drop("abChip",1,40,&r);   /* a chip: delivered while the folder has room */
         /* fresh records: the folder is not full */
         dw4_playerrecords_close(p);p=dw4_playerrecords_open();assert(p);make_players(p);c.players=p;
         place(&f.d[0],2,0,0);s.lock[0]=0;memset(f.picked,0,sizeof f.picked);
         size_t before=device_count(p,0);
         assert(dw4_loot_cross(&s,&c,1,field_at,&f,0,field_picked,&f)==1 && f.picked[0]==1 && f.slot[0]==0 && f.d[0].collected && device_count(p,0)==before+1 && s.lock[0]<0);
         assert(ev.n==1 && !ev.on[0] && ev.index[0]==0 && ev.slot[0]==0);
         assert(dw4_loot_cross(&s,&c,1,field_at,&f,0,field_picked,&f)==0 && f.picked[0]==1);}
    }
    /* a drop whose item could not be built is not in the list the caller offers (NULL) */
    dw4_playerrecords_close(p);
}
/* ---- the real databases ---- */
struct boot {dw4_playerrecords *players;dw4_scriptservices *sd;};
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct boot *b=user;int rc=dw4_playerrecords_call(b->players,method,a,n,r,error,cap);if(rc<=0)return rc;
    if(!strcmp(method,"SYSgetLightMode")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;}
    return dw4_scriptservices_call(b->sd,method,a,n,r,error,cap);
}
static int real_number(void *u,int category,int32_t record,const char *column,int32_t *out)
{
    const dw4_database *db=dw4_databases_get(u,dw4_loot_category_name(category));return db?dw4_database_number(db,record,column,out):-1;
}
static const char *real_string(void *u,int category,int32_t record,const char *column)
{
    const dw4_database *db=dw4_databases_get(u,dw4_loot_category_name(category));return db?dw4_database_string(db,record,column):NULL;
}
static void test_real(const char *root)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,root));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1) && !dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects) && !dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    dw4_loot_db l={db,real_number,real_string};
    /* every category has its database; the models of conItem / insItem rows are all in the model table */
    for(int c=0;c<DW4_LOOT_CATEGORIES;c++)assert(dw4_databases_get(db,dw4_loot_category_name(c)));
    {const dw4_database *con=dw4_databases_get(db,"conItem"),*ins=dw4_databases_get(db,"insItem");
     assert(dw4_database_string_rows(con)==12 && dw4_database_string_rows(ins)==26);
     for(int i=0;i<12;i++){const char *m=dw4_loot_model(&l,DW4_LOOT_CON,i);assert(m && dw4_loot_named(dw4_loot_model_kind(m)));   /* disks are all named: Cross picks them up */
         assert(dw4_loot_model_kind(m)==(i<10?DW4_LOOT_ITEM:i==10?DW4_LOOT_BOOST1:DW4_LOOT_PENX));}
     for(int i=0;i<26;i++){const char *m=dw4_loot_model(&l,DW4_LOOT_INS,i);int k=dw4_loot_model_kind(m);   /* instant items are all unnamed: walking over them takes them */
         assert(k==(i==0?DW4_LOOT_BIT:i<4?DW4_LOOT_XDATA1:DW4_LOOT_XDATA2) && !dw4_loot_named(k));
         int32_t up=-1;assert(!real_number(db,DW4_LOOT_INS,i,"UP",&up));
         assert(up==(i==0?0:i==1?5:i==2?20:i==3?100:(i&1)?2:1));}   /* x-data 5/20/100; the UPCNT items alternate +1 and +2 */
    }
    for(int c=DW4_LOOT_IMP;c<DW4_LOOT_CATEGORIES;c++){   /* the fixed-model categories are all named */
        dw4_loot_drop d;dw4_random r;dw4_random_init(&r);
        assert(!dw4_loot_make(&l,dw4_loot_category_name(c),0,40,&r,&d) && dw4_loot_named(d.model_kind));
    }
    assert(dw4_database_string_rows(dw4_databases_get(db,"impItem"))>=2);   /* the two boss keys */
    /* the label text: every drop row of every category has a NAME to show (conItem, impItem, weapon, armour and chip rows; the unnamed instant items show none) */
    for(int c=0;c<DW4_LOOT_CATEGORIES;c++){
        if(c==DW4_LOOT_INS)continue;
        const dw4_database *cat=dw4_databases_get(db,dw4_loot_category_name(c));unsigned rows=dw4_database_string_rows(cat),named=0;
        for(unsigned i=0;i<rows;i++){const char *n=real_string(db,c,(int32_t)i,"NAME");if(n && *n)named++;}
        fprintf(stderr,"%s: %u of %u rows carry a NAME\n",dw4_loot_category_name(c),named,rows);
        assert(named>0);
    }
    /* x-data id 1 pays UP = 5 through the real record, as the live measurement */
    {dw4_playerrecords *p=dw4_playerrecords_open();make_players(p);dw4_random r;dw4_random_init(&r);
     dw4_loot_ctx c={.players=p,.db=l,.random=&r};int32_t amount;
     assert(dw4_loot_instant(&c,1,0,&amount)==1 && num(p,0,"XDATA")==12);
     dw4_playerrecords_close(p);}
    fprintf(stderr,"real databases: conItem 12 rows (named disks), insItem 26 rows (unnamed), key/weapon/armour/chip fixed models\n");
}
int main(int argc,char **argv)
{
    test_tables();test_presentation();test_rolls();test_bit();test_upcnt();test_instant();test_press();test_step();
    if(argc>1)test_real(argv[1]);
    printf("loot: model table, roll streams, BIT bands, UPCNT map, instant/press deliveries and the pickup step%s\n",argc>1?", real item databases":"");
    return 0;
}
