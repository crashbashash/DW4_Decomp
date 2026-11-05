#include "dw4/playerinit.h"
#include "dw4/playerhealth.h"
#include "dw4/playerstats.h"
#include "dw4/statuscontent.h"
#include "dw4/shopstock.h"
#include "dw4/playertransactions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint32_t raw(const dw4_igb_record *r,unsigned slot)
{for(uint32_t i=0;i<r->nvalues;i++)if(r->values[i].ordinal==slot)return r->values[i].raw;assert(0);return 0;}
static dw4_igb_record record(const dw4_igb *g,uint32_t id)
{dw4_igb_record r={0};uint32_t off;assert(dw4_igb_ref(g,id,&off,NULL)==2 && dw4_igb_decode(g,off,&r));return r;}
static uint32_t word(const uint8_t *p){return p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static const uint8_t *list(const dw4_igb *g,uint32_t id,uint32_t *n)
{dw4_igb_record r=record(g,id);*n=raw(&r,2);const uint8_t *v=dw4_igb_block(g,raw(&r,4),NULL);dw4_igb_record_free(&r);return v;}
static void check_tables(const dw4_stageobjects *s,const dw4_databases *db,int dump)
{
    size_t cells=0;
    for(size_t i=0;i<dw4_stageobjects_count(s);i++){
        const dw4_stageobject *info=dw4_stageobjects_at(s,i);if(strcmp(dw4_stageobject_class(info),"beDBManagerInfo"))continue;
        const dw4_igb *g=info->igb;dw4_igb_record r=record(g,dw4_stageobject_ref_id(info,"_dataBase"));
        const dw4_database *d=dw4_databases_get(db,dw4_stageobject_name(info));assert(d);
        for(unsigned k=0;k<3;k++){
            uint32_t cols,count;const uint8_t *keys=list(g,raw(&r,2+2*k),&cols),*values=list(g,raw(&r,3+2*k),&count);
            for(uint32_t j=0;j<count;j++){
                dw4_igb_record key=record(g,word(keys+4*(j%cols)));int32_t expected,v;
                if(k==0)expected=(int8_t)values[j];
                else if(k==1)expected=(int16_t)(values[j*2]|(uint32_t)values[j*2+1]<<8);
                else {uint32_t bits=word(values+j*4);memcpy(&expected,&bits,4);}
                assert(key.name && !dw4_database_number(d,j/cols,key.name,&v) && v==expected);cells++;
                if(dump)printf("N\t%s\t%u\t%s\t%d\n",dw4_stageobject_name(info),j/cols,key.name,expected);
                dw4_igb_record_free(&key);
            }
        }
        if(dump){uint32_t cols,count;const uint8_t *keys=list(g,raw(&r,12),&cols),*values=list(g,raw(&r,13),&count);
            for(uint32_t j=0;j<count;j++){dw4_igb_record key=record(g,word(keys+4*(j%cols))),v=record(g,word(values+4*j));
                if(!strcmp(key.name,"MODEL_NAME") || !strcmp(key.name,"MODEL") || !strcmp(key.name,"ZOKUSEI") || !strcmp(key.name,"SHUSEINOURYOKU"))printf("S\t%s\t%u\t%s\t%s\n",dw4_stageobject_name(info),j/cols,key.name,v.name?v.name:"");
                dw4_igb_record_free(&key);dw4_igb_record_free(&v);}}
        dw4_igb_record_free(&r);
    }
    if(!dump)printf("database: %zu authored signed numeric cells match raw IGB lists\n",cells);
}
static void array(dw4_property_folder *f,const char *key,size_t count,int ones)
{size_t n;const int32_t *a=dw4_property_array(f,key,&n);assert(a && n==count);for(size_t i=0;i<n;i++)assert(a[i]==ones);}
static void stats_cases(dw4_playerrecords *p,const dw4_databases *db)
{
    const int levels[]={1,5,6,10,11,20,21,30,31,50,51,70,71,110,111,150,151,230,231,999};
    const char *keys[]={"MHP","MMP","HP","MP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO","NEXTEXP","ATTACKDELAY","MEICHURITSU","CHIMEIRITSU","MAHIRITSU","KAIHIRITSU","BOUGYORITSU","MAHITEIKOU","DOKUTEIKOU","BITRITSU","EXPRITSU","LUCKRITSU","ATTACKZOKUSEI","HPDRAIN","MPDRAIN","CHOHATURITSU","WEAPONRECNO","WEAPONSKILLNO"};
    const char *eq[]={"POWERSOCKET","POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
    const char *tables[]={"weapon","abChip","armor1","abChip","armor2"};
    const int kinds[]={0,3,1,3,2};const size_t counts[]={3,5,1,5,1};char error[256];
    for(unsigned c=0;c<1760;c++){
        assert(!dw4_playerrecords_create(p,db,c%4,"p_dorumon","Stats",error,sizeof error));
        dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",c%4);
        unsigned species=c<320?c%16:(c-320)/90;int level=c<320?levels[c/16]:999;
        int32_t hp=c%3?40000:0,mp=c%5?30000:0;
        assert(!dw4_property_set_number(f,"DIGIMONNO",species) && !dw4_property_set_number(f,"LEVEL",level) &&
            !dw4_property_set_number(f,"HP",hp) && !dw4_property_set_number(f,"MP",mp));
        int base=c%4==1;
        printf("C\t%u\t%u\t%d\t%d\t%d\t%d\n",c,species,level,hp,mp,base);
        int32_t a[11];const char *arrays[]={"UPCNT","UPDATA","DOWNDATA","SKILL"};const size_t lengths[]={11,11,7,9};
        for(unsigned k=0;k<4;k++){
            int32_t threshold=0,skill=-1;
            if(c>=320 && k==3){char key[32];unsigned t=((c-320)%90)/15+1,rank=((c-320)%15)/3+1;int32_t base;
                snprintf(key,sizeof key,"TECH%u",t);assert(dw4_database_number(dw4_databases_get(db,"shinka"),species,key,&base)>=0);
                assert(dw4_database_number(dw4_databases_get(db,"pcTech"),base,"SKILL",&skill)>=0);
                snprintf(key,sizeof key,"TECH%u_SKILL%u",t,rank);assert(dw4_database_number(dw4_databases_get(db,"shinka"),species,key,&threshold)>=0);
                threshold+=(int32_t)((c-320)%3)-1;
            }
            printf("A\t%s",arrays[k]);for(size_t j=0;j<lengths[k];j++){
                a[j]=k==3?(int32_t)((c*71+j*191)%5000):(int32_t)((c*37+j*997)%1100)-300;
                if(k==3 && (int32_t)j==skill)a[j]=threshold;
                if(c%41==0 && k!=3)a[j]=j%2?INT32_MIN:INT32_MAX;
                printf("\t%d",a[j]);
            }puts("");assert(!dw4_property_set_array(f,arrays[k],a,lengths[k]));
        }
        for(unsigned k=0;k<5;k++){
            size_t rows=dw4_database_string_rows(dw4_databases_get(db,tables[k]));assert(rows);
            dw4_item_record v[5];
            for(size_t j=0;j<counts[k];j++){
                v[j]=(dw4_item_record){.kind=(c+j+k)%4==0?-1:kinds[k],.record=(int32_t)((c*7+j*13)%rows),.equipped=1,.revision=(int32_t)(c%201)-80};
                printf("E\t%u\t%zu\t%d\t%d\t%d\n",k,j,v[j].kind,v[j].record,v[j].revision);
            }assert(!dw4_property_set_items(f,eq[k],v,counts[k]));
        }
        assert(!(base?dw4_playerstats_recalculate_base:dw4_playerstats_recalculate)((void *)db,f));
        for(size_t k=0;k<(base?14u:sizeof keys/sizeof *keys);k++){int32_t v;assert(!dw4_property_number(f,keys[k],&v));printf("V\t%s\t%d\n",keys[k],v);}
        size_t n;const dw4_item_record *w=dw4_property_items(f,"WAZALIST",&n);assert(n<=6);
        printf("W");for(size_t j=0;j<n;j++)printf("\t%d\t%d",w[j].record,w[j].revision);puts("");
        if(!base){printf("M");for(size_t j=0;j<3 && dw4_property_string_at(f,"POWERSOCKETNAME",j);j++)printf("\t%s",dw4_property_string_at(f,"POWERSOCKETNAME",j));puts("");}
    }
    /* Production equipment commits and preview share the same calculator. */
    assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Stats",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);int32_t before,after;
    assert(!dw4_property_number(f,"WEAPONRECNO",&before));
    assert(!dw4_playertransactions_preview(p,0,"POWERSOCKET",0,1,dw4_playerstats_item_attribute,(void *)db,dw4_playerstats_recalculate,(void *)db));
    assert(!dw4_property_number(f,"WEAPONRECNO",&after) && before==after);
    assert(dw4_playertransactions_equip_database(p,0,"POWERSOCKET",0,1,NULL)==-1);
    assert(!dw4_property_number(f,"WEAPONRECNO",&after) && before==after);
    assert(!dw4_playertransactions_equip_database(p,0,"POWERSOCKET",0,1,db));
    size_t n;const dw4_item_record *w=dw4_property_items(f,"POWERSOCKET",&n);
    assert(n==3 && w[1].kind==-1 && !dw4_property_number(f,"WEAPONRECNO",&after) && after==w[0].record);
}
static void health_restore_test(void)
{
    dw4_playerrecords *p=dw4_playerrecords_open();assert(p);dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);
    char error[256];dw4_playerhealth h;assert(!dw4_property_set_number(f,"ISUSE",1));assert(!dw4_property_set_number(f,"LEVEL",3));
    assert(!dw4_property_set_number(f,"MHP",170) && !dw4_property_set_number(f,"MMP",60));
    assert(!dw4_property_set_number(f,"HP",200) && !dw4_property_set_number(f,"MP",-1));
    assert(!dw4_playerhealth_restore(p,0,&h,error,sizeof error) && h.hp==170 && h.mp==0 && h.hp_publish && h.hp_percent==100);
    assert(!dw4_property_set_number(f,"HP",0) && !dw4_property_set_number(f,"MP",100));
    assert(!dw4_playerhealth_restore(p,0,&h,error,sizeof error) && !h.hp_publish && h.hp==0 && h.mp==60);
    assert(!dw4_property_set_number(f,"MMP",0) && !dw4_property_set_number(f,"HP",200));
    assert(dw4_playerhealth_restore(p,0,&h,error,sizeof error));int32_t hp;assert(!dw4_property_number(f,"HP",&hp) && hp==200);
    dw4_playerrecords_close(p);
}
static int failing_recalc(void *u,dw4_property_folder *f){(void)u;(void)f;return -1;}
static int32_t num(dw4_property_folder *f,const char *key){int32_t v;assert(!dw4_property_number(f,key,&v));return v;}
/* Retail 4270a0/43fb70 price rule (docs/engine/xdata-controller.md) and the ShopCtrl10 confirmation write. */
static void xdata_test(dw4_playerrecords *p,const dw4_databases *db)
{
    /* Documented boundaries and the signed-wrap behaviour of stat-45. */
    const struct {int32_t stat,price;} cases[]={{45,0},{46,1},{50,1},{51,2},{2045,400},{2046,400},{44,1},{41,1},{40,1},{39,0},{0,1},
        {INT32_MAX,400},{INT32_MIN,400}};
    for(unsigned i=0;i<sizeof cases/sizeof *cases;i++)assert(dw4_xdata_price(cases[i].stat)==cases[i].price);
    const char *key;int32_t limit;int index;
    static const int32_t slots[]={2,3,4,5,6,0,1};
    for(int i=0;i<7;i++){assert(!dw4_xdata_stat(i,&key,&limit,&index) && index==slots[i] && limit==(i<5?9999:99999));}
    assert(dw4_xdata_stat(-1,NULL,NULL,NULL) && dw4_xdata_stat(7,NULL,NULL,NULL));
    char error[256];
    assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Xdata",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);
    assert(!dw4_playerstats_recalculate((void *)db,f));
    const char *keys[]={"TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","MHP","MMP"};
    for(int parameter=0;parameter<7;parameter++) {
        assert(!dw4_property_set_number(f,"XDATA",300));
        int32_t stat=num(f,keys[parameter]),price=dw4_xdata_price(stat);size_t n;
        int32_t before[11];const int32_t *u=dw4_property_array(f,"UPCNT",&n);assert(u && n==11);memcpy(before,u,sizeof before);
        /* A failed recalculation publishes nothing. */
        assert(dw4_playertransactions_xdata_upgrade(p,0,parameter,failing_recalc,NULL)==-1);
        assert(num(f,"XDATA")==300 && num(f,keys[parameter])==stat && !memcmp(dw4_property_array(f,"UPCNT",&n),before,sizeof before));
        assert(!dw4_playertransactions_xdata_upgrade(p,0,parameter,dw4_playerstats_recalculate,(void *)db));
        u=dw4_property_array(f,"UPCNT",&n);
        for(int k=0;k<11;k++)assert(u[k]==before[k]+(k==slots[parameter]));
        assert(num(f,"XDATA")==300-price && num(f,keys[parameter])==stat+1);
        assert(num(f,"HP")==num(f,"MHP") && num(f,"MP")==num(f,"MMP"));
    }
    /* Undefined selectors are refused without mutation. */
    int32_t before=num(f,"XDATA");
    assert(dw4_playertransactions_xdata_upgrade(p,0,7,dw4_playerstats_recalculate,(void *)db)==-1);
    assert(dw4_playertransactions_xdata_upgrade(p,0,-1,dw4_playerstats_recalculate,(void *)db)==-1 && num(f,"XDATA")==before);
}
static int preview_seen;static int32_t preview_record;
static int preview_visit(void *u,dw4_property_folder *f)
{
    (void)u;size_t n;const dw4_item_record *pocket=dw4_property_items(f,"POWERPOCKET",&n);
    preview_seen++;preview_record=pocket && n==5?pocket[0].record:-1;return 0;
}
/* XDATA chip transactions (43aae0): private-copy preview and atomic upgrade. */
static void chip_test(dw4_playerrecords *p,const dw4_databases *db)
{
    const dw4_database *chips=dw4_databases_get(db,"abChip");int32_t record=-1,cost=0;
    for(size_t r=0;r+1<dw4_database_string_rows(chips) && record<0;r++){
        int32_t next;if(dw4_database_number(chips,(int32_t)r,"NEXTX",&next)>=0 && next>0)record=(int32_t)r,cost=next;
    }
    assert(record>=0);
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Chip",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);size_t before;int added;
    assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,record,0,0,&added) && added);
    assert(!dw4_playertransactions_equip_database(p,0,"POWERPOCKET",0,(int32_t)before,db));
    assert(!dw4_property_set_number(f,"XDATA",1000));
    int32_t tsu=num(f,"TSUYOSA"),sei=num(f,"SEISHIN");
    /* Preview: the visitor sees the raised, re-projected record; nothing is published. */
    preview_seen=0;
    assert(!dw4_playertransactions_chip_preview(p,0,before,dw4_playerstats_recalculate,(void *)db,preview_visit,NULL));
    assert(preview_seen==1 && preview_record==record+1);
    size_t n;const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);
    assert(items[before].record==record && num(f,"XDATA")==1000 && num(f,"TSUYOSA")==tsu && num(f,"SEISHIN")==sei);
    assert(dw4_property_items(f,"POWERPOCKET",&n)[0].record==record);
    /* A failed recalculation or a non-chip index publishes nothing. */
    assert(dw4_playertransactions_chip_upgrade(p,0,before,dw4_playerstats_item_attribute,(void *)db,failing_recalc,NULL)==-1);
    assert(dw4_playertransactions_chip_upgrade(p,0,0,dw4_playerstats_item_attribute,(void *)db,dw4_playerstats_recalculate,(void *)db)==-1);
    assert(dw4_playertransactions_chip_upgrade(p,0,99,dw4_playerstats_item_attribute,(void *)db,dw4_playerstats_recalculate,(void *)db)==-1);
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==record && num(f,"XDATA")==1000);
    /* Upgrade: debit NEXTX, raise the record, follow it into the equipped projection, recalculate. */
    assert(!dw4_playertransactions_chip_upgrade(p,0,before,dw4_playerstats_item_attribute,(void *)db,dw4_playerstats_recalculate,(void *)db));
    items=dw4_property_items(f,"DEVICEFOLDER",&n);
    assert(items[before].record==record+1 && num(f,"XDATA")==1000-cost);
    assert(dw4_property_items(f,"POWERPOCKET",&n)[0].record==record+1);
    assert(num(f,"TSUYOSA")>=tsu && num(f,"SEISHIN")>=sei);
}
/* NPC bank transactions (beNDMWShopCtrl30 428790): atomic item and money transfers. */
static size_t item_count(dw4_property_folder *f,const char *key){size_t n;assert(!dw4_property_item_count(f,key,&n));return n;}
static void bank_test(dw4_playerrecords *p,const dw4_databases *db)
{
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Bank",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);int result=-1,added;
    /* Money: bounds, refusal and the invalid-flag/negative cases leave both balances alone. */
    assert(!dw4_property_set_number(f,"BIT",1000) && !dw4_property_set_number(f,"BANKBIT",500));
    assert(!dw4_playertransactions_bank_bit(p,0,0,300,&result) && result==1 && num(f,"BIT")==700 && num(f,"BANKBIT")==800);
    assert(!dw4_playertransactions_bank_bit(p,0,1,800,&result) && result==1 && num(f,"BIT")==1500 && num(f,"BANKBIT")==0);
    assert(!dw4_playertransactions_bank_bit(p,0,1,1,&result) && result==0 && num(f,"BIT")==1500 && num(f,"BANKBIT")==0);
    assert(!dw4_playertransactions_bank_bit(p,0,0,0,&result) && result==0);
    assert(!dw4_playertransactions_bank_bit(p,0,0,1501,&result) && result==0 && num(f,"BIT")==1500);
    assert(dw4_playertransactions_bank_bit(p,0,0,-1,&result)==-1 && dw4_playertransactions_bank_bit(p,0,2,1,&result)==-1);
    assert(!dw4_property_set_number(f,"BANKBIT",9999990));
    assert(!dw4_playertransactions_bank_bit(p,0,0,10,&result) && result==0 && num(f,"BANKBIT")==9999990);
    assert(!dw4_playertransactions_bank_bit(p,0,0,9,&result) && result==1 && num(f,"BANKBIT")==9999999 && num(f,"BIT")==1491);
    assert(!dw4_property_set_number(f,"BIT",9999995) && !dw4_playertransactions_bank_bit(p,0,1,5,&result) && result==0);
    assert(!dw4_playertransactions_bank_bit(p,0,1,4,&result) && result==1 && num(f,"BIT")==9999999);
    /* Items: two chips appended; the second is equipped so a deposit of the first shifts its reference. */
    size_t base=item_count(f,"DEVICEFOLDER");
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,1,0,0,&added) && added);
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,2,0,0,&added) && added);
    assert(!dw4_playertransactions_equip_database(p,0,"POWERPOCKET",0,(int32_t)base+1,db));
    size_t n;const int32_t *ref=dw4_property_array(f,"POWERPOCKETREF",&n);assert(ref && ref[0]==(int32_t)base+1);
    assert(!dw4_playertransactions_bank_item(p,0,0,base+1,&result) && result==0 && item_count(f,"BANKDEVICE")==0); /* equipped */
    assert(!dw4_playertransactions_bank_item(p,0,0,base,&result) && result==1);
    assert(item_count(f,"DEVICEFOLDER")==base+1 && item_count(f,"BANKDEVICE")==1);
    const dw4_item_record *bank=dw4_property_items(f,"BANKDEVICE",&n),*inv=dw4_property_items(f,"DEVICEFOLDER",&n);
    assert(bank[0].kind==3 && bank[0].record==1 && inv[base].record==2 && inv[base].equipped);
    ref=dw4_property_array(f,"POWERPOCKETREF",&n);assert(ref[0]==(int32_t)base && dw4_property_items(f,"POWERPOCKET",&n)[0].record==2);
    assert(dw4_playertransactions_bank_item(p,0,0,base+1,&result)==-1 && dw4_playertransactions_bank_item(p,0,1,1,&result)==-1);
    assert(!dw4_playertransactions_bank_item(p,0,1,0,&result) && result==1);
    inv=dw4_property_items(f,"DEVICEFOLDER",&n);
    assert(n==base+2 && item_count(f,"BANKDEVICE")==0 && inv[base+1].record==1 && inv[base].record==2);
    assert(dw4_playertransactions_bank_item(p,0,2,0,&result)==-1);
    /* Capacity: a full bank refuses a deposit, a full inventory refuses a withdrawal; nothing changes. */
    dw4_item_record fill[96];for(unsigned i=0;i<96;i++)fill[i]=(dw4_item_record){.kind=3,.record=1};
    assert(!dw4_property_set_items(f,"BANKDEVICE",fill,96));
    assert(!dw4_playertransactions_bank_item(p,0,0,base+1,&result) && result==0 && item_count(f,"BANKDEVICE")==96 && item_count(f,"DEVICEFOLDER")==base+2);
    assert(!dw4_property_set_items(f,"BANKDEVICE",fill,1));
    dw4_item_record full[36];memcpy(full,dw4_property_items(f,"DEVICEFOLDER",&n),n*sizeof *full);
    for(size_t i=n;i<36;i++)full[i]=(dw4_item_record){.kind=3,.record=1};
    assert(n<=36 && !dw4_property_set_items(f,"DEVICEFOLDER",full,36));
    assert(!dw4_playertransactions_bank_item(p,0,1,0,&result) && result==0 && item_count(f,"DEVICEFOLDER")==36 && item_count(f,"BANKDEVICE")==1);
}
/* CNOS reroll table fixture: three tiers (3 and 4 populated), ID column = count in the header row. */
static int cnos_rows(void *u,int32_t row,int32_t *id,int32_t *rate)
{
    (void)u;
    if(row==300){*id=3;*rate=0;return 0;}
    if(row==301){*id=10;*rate=100;return 0;}
    if(row==302){*id=20;*rate=200;return 0;}
    if(row==303){*id=30;*rate=300;return 0;}
    if(row==400){*id=0;*rate=0;return 0;} /* empty tier */
    if(row==500){*id=2;*rate=0;return 0;} /* declares two entries but the rows are missing */
    return -1;
}
/* CNOS item converter (429630): tiers, weighted draw and atomic conversion. */
static void cnos_test(dw4_playerrecords *p,const dw4_databases *db)
{
    static const int32_t level[]={-5,0,40,41,100,101,200,201,300,301,400,401,9999};
    static const int32_t tier[]={1,1,1,2,2,3,3,4,4,5,5,6,6};
    for(unsigned i=0;i<sizeof level/sizeof *level;i++)assert(dw4_cnos_tier(level[i])==tier[i]);
    int32_t record=-7;
    /* Running sums are 100, 300, 600: the first entry reaching the draw wins, a miss keeps the record. */
    static const struct {uint32_t draw;int hit;int32_t id;} rolls[]={{0,1,10},{100,1,10},{101,1,20},{300,1,20},{301,1,30},{600,1,30},{601,0,-7},{9999,0,-7}};
    for(unsigned i=0;i<sizeof rolls/sizeof *rolls;i++){
        record=-7;assert(dw4_cnos_roll(cnos_rows,NULL,3,rolls[i].draw,&record)==rolls[i].hit && record==rolls[i].id);
    }
    record=-7;assert(dw4_cnos_roll(cnos_rows,NULL,4,0,&record)==0 && record==-7); /* empty tier */
    assert(dw4_cnos_roll(cnos_rows,NULL,5,0,&record)==-1);   /* missing entry rows */
    assert(dw4_cnos_roll(cnos_rows,NULL,0,0,&record)==-1 && dw4_cnos_roll(cnos_rows,NULL,7,0,&record)==-1);
    assert(dw4_cnos_roll(NULL,NULL,3,0,&record)==-1 && dw4_cnos_roll(cnos_rows,NULL,3,0,NULL)==-1);
    /* Transaction. */
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Cnos",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);size_t before;int added;
    assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,0,276,0,0,&added) && added);
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,0,0,0,&added) && added); /* a chip: never convertible */
    assert(!dw4_property_set_number(f,"BIT",1000) && !dw4_property_set_number(f,"LEVEL",60));
    dw4_cnos_table tables[3]={cnos_rows,cnos_rows,cnos_rows};void *users[3]={NULL,NULL,NULL};int result=-1;
    size_t n;const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);
    assert(items[before].kind==0 && items[before].record==276);
    /* LEVEL 60 -> tier 2: the fixture has no tier-2 rows, so the table is invalid and nothing changes. */
    assert(dw4_playertransactions_cnos_convert(p,0,before,tables,users,150,&result)==-1);
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==276 && num(f,"BIT")==1000);
    assert(!dw4_property_set_number(f,"LEVEL",250)); /* tier 4: empty -> charged, unchanged */
    assert(!dw4_playertransactions_cnos_convert(p,0,before,tables,users,5,&result) && result==1);
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==276 && num(f,"BIT")==700);
    assert(!dw4_property_set_number(f,"LEVEL",101)); /* 101 is the first level of tier 3 */
    assert(!dw4_playertransactions_cnos_convert(p,0,before,tables,users,150,&result) && result==2);
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==20 && items[before].kind==0 && num(f,"BIT")==400);
    assert(!dw4_playertransactions_cnos_convert(p,0,before,tables,users,9999,&result) && result==1); /* miss */
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==20 && num(f,"BIT")==100);
    /* Below the price, refused untouched; a chip, a bad index and a bad kind are errors. */
    assert(!dw4_playertransactions_cnos_convert(p,0,before,tables,users,150,&result) && result==0);
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==20 && num(f,"BIT")==100);
    assert(!dw4_property_set_number(f,"BIT",1000));
    assert(dw4_playertransactions_cnos_convert(p,0,before+1,tables,users,150,&result)==-1);
    assert(dw4_playertransactions_cnos_convert(p,0,n,tables,users,150,&result)==-1);
    assert(dw4_playertransactions_cnos_convert(p,0,before,NULL,users,150,&result)==-1);
    assert(num(f,"BIT")==1000);
    /* An equipped item's projection follows the new record (no recalculation, as in retail). */
    const int32_t ref[1]={(int32_t)before};
    assert(!dw4_property_set_array(f,"MAINSLOTREF",ref,1));
    assert(!dw4_playertransactions_cnos_convert(p,0,before,tables,users,0,&result) && result==2);
    size_t m;const dw4_item_record *slot=dw4_property_items(f,"MAINSLOT",&m);assert(m==1 && slot[0].kind==0 && slot[0].record==10);
    items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items[before].record==10 && num(f,"BIT")==700);
}
/* DISK shop transactions (42a2e0 buy, 4353e0/436ac0 sell): atomic, capped, refusals leave records untouched. */
static void disk_test(dw4_playerrecords *p,const dw4_databases *db)
{
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Disk",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);int result=-1;
    assert(!dw4_property_set_number(f,"BIT",1000));
    size_t n;const dw4_item_record *d=dw4_property_items(f,"DISKFOLDER",&n);assert(d && n==12 && d[3].record==3 && d[3].revision==0);
    /* Buy two at 100. */
    assert(!dw4_playertransactions_disk_buy(p,0,3,2,100,&result) && result==1);
    d=dw4_property_items(f,"DISKFOLDER",&n);assert(num(f,"BIT")==800 && d[3].revision==2 && d[2].revision==0);
    /* Refusals: not enough BIT, more than nine held; both change nothing. */
    assert(!dw4_playertransactions_disk_buy(p,0,3,5,200,&result) && result==0 && num(f,"BIT")==800);
    assert(!dw4_playertransactions_disk_buy(p,0,3,8,1,&result) && result==0 && num(f,"BIT")==800);
    d=dw4_property_items(f,"DISKFOLDER",&n);assert(d[3].revision==2);
    /* Invalid arguments are -1 and equally harmless. */
    assert(dw4_playertransactions_disk_buy(p,0,99,1,1,&result)==-1 && dw4_playertransactions_disk_buy(p,0,3,0,1,&result)==-1 &&
           dw4_playertransactions_disk_buy(p,0,3,10,1,&result)==-1 && dw4_playertransactions_disk_buy(p,0,3,1,-1,&result)==-1);
    assert(num(f,"BIT")==800);
    /* The ninth disk is allowed exactly. */
    assert(!dw4_playertransactions_disk_buy(p,0,3,7,1,&result) && result==1 && num(f,"BIT")==793);
    d=dw4_property_items(f,"DISKFOLDER",&n);assert(d[3].revision==9);
    /* Sell: quantity beyond the held count refuses, otherwise credit quantity*price. */
    assert(!dw4_playertransactions_disk_sell(p,0,3,10,5,&result) && result==0 && num(f,"BIT")==793);
    assert(!dw4_playertransactions_disk_sell(p,0,3,4,50,&result) && result==1 && num(f,"BIT")==993);
    d=dw4_property_items(f,"DISKFOLDER",&n);assert(d[3].revision==5);
    assert(dw4_playertransactions_disk_sell(p,0,12,1,1,&result)==-1 && dw4_playertransactions_disk_sell(p,0,3,0,1,&result)==-1);
    /* Credits cap at 9,999,999 ("if (bit >= 0x989680) bit = 0x98967f"). */
    assert(!dw4_property_set_number(f,"BIT",9999990));
    assert(!dw4_playertransactions_disk_sell(p,0,3,1,50,&result) && result==1 && num(f,"BIT")==9999999);
    /* Device sale: an unequipped chip is removed with its credit, an equipped item is refused. */
    size_t before;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    int added;assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,1,0,0,&added) && added);
    assert(!dw4_property_set_number(f,"BIT",100));
    assert(!dw4_playertransactions_sell_item(p,0,before,25,&result) && result==1 && num(f,"BIT")==125);
    size_t after;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&after) && after==before);
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);size_t equipped=n;
    for(size_t i=0;i<n;i++)if(items[i].equipped){equipped=i;break;}
    if(equipped<n){assert(!dw4_playertransactions_sell_item(p,0,equipped,25,&result) && result==0 && num(f,"BIT")==125);}
    assert(dw4_playertransactions_sell_item(p,0,200,25,&result)==-1 && dw4_playertransactions_sell_item(p,0,0,-1,&result)==-1);
}

static const char *species_model(void *u,int32_t row){return dw4_database_string(dw4_databases_get(u,"shinka"),row,"MODEL_NAME");}
static const char *item_model(void *u,const dw4_item_record *i,const char *key){return dw4_statuscontent_item_string(u,i,key);}
/* DIGILAB evolution: GAMERAM CURRENT2BASE/BASE2CURRENT/WEAPONEQUIPSTRONG and the list clearing of 4313b0. */
static void evolve_test(dw4_playerrecords *p,const dw4_databases *db)
{
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Evolve",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);
    int32_t cur=num(f,"DIGIMONNO");size_t n;const int32_t *use=dw4_property_array(f,"BASE_ISUSE",&n);assert(use && n==16);
    /* A second form becomes available (DIGILAB lists BASE_ISUSE members). */
    int32_t target=(cur+1)%16,unlocked[16];memcpy(unlocked,use,sizeof unlocked);unlocked[target]=1;
    assert(!dw4_property_set_array(f,"BASE_ISUSE",unlocked,16));
    /* The current form has progressed; its saved base lags until CURRENT2BASE. */
    int32_t up[11]={0};up[0]=5;up[2]=3;assert(!dw4_property_set_number(f,"LEVEL",12) && !dw4_property_set_number(f,"EXP",345) && !dw4_property_set_array(f,"UPCNT",up,11));
    int32_t skills[9];for(unsigned i=0;i<9;i++)skills[i]=(int32_t)i+2;assert(!dw4_property_set_array(f,"SKILL",skills,9));
    /* Equip a chip so the list clearing is observable. */
    const dw4_database *chips=dw4_databases_get(db,"abChip");int32_t chip=-1;
    for(size_t r=0;r<dw4_database_string_rows(chips) && chip<0;r++){int32_t next;if(dw4_database_number(chips,(int32_t)r,"NEXTX",&next)>=0 && next>0)chip=(int32_t)r;}
    assert(chip>=0);size_t before;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));int added;
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,chip,0,0,&added) && added);
    assert(!dw4_playertransactions_equip_database(p,0,"POWERPOCKET",0,(int32_t)before,db));
    /* WEAPONEQUIPCHECK uses the current species' SKILL and other species' BASE_SKILL. */
    int ok=-1;assert(!dw4_playertransactions_weapon_check(p,0,cur,dw4_playerstats_item_attribute,(void *)db,&ok) && ok==1);
    assert(dw4_playertransactions_weapon_check(p,0,16,dw4_playerstats_item_attribute,(void *)db,&ok)==-1);
    assert(!dw4_playertransactions_weapon_check(p,0,target,dw4_playerstats_item_attribute,(void *)db,&ok) && (ok==0 || ok==1));
    int32_t before_level=num(f,"LEVEL");
    /* Refusals and a failing recalculation publish nothing. */
    assert(dw4_playertransactions_evolve(p,0,16,species_model,(void *)db,dw4_playerstats_item_attribute,item_model,(void *)db,dw4_playerstats_recalculate,(void *)db)==-1);
    assert(dw4_playertransactions_evolve(p,0,target,species_model,(void *)db,dw4_playerstats_item_attribute,item_model,(void *)db,failing_recalc,NULL)==-1);
    assert(num(f,"DIGIMONNO")==cur && num(f,"LEVEL")==before_level);
    assert(!dw4_playertransactions_evolve(p,0,target,species_model,(void *)db,dw4_playerstats_item_attribute,item_model,(void *)db,dw4_playerstats_recalculate,(void *)db));
    const char *model=species_model((void *)db,target);int32_t row=0;
    for(int32_t r=0;r<16;r++){const char *m=species_model((void *)db,r);if(m && !strcmp(m,model)){row=r;break;}}
    assert(num(f,"DIGIMONNO")==row && !strcmp(dw4_property_string(f,"DIGIMONNAME"),model));
    /* CURRENT2BASE saved the old form; BASE2CURRENT loaded the new one. */
    const int32_t *bl=dw4_property_array(f,"BASE_LEVEL",&n);assert(bl && bl[cur]==12);
    const int32_t *be=dw4_property_array(f,"BASE_EXP",&n);assert(be && be[cur]==345);
    const int32_t *bu=dw4_property_array(f,"BASE_UPCNT",&n);assert(bu && bu[cur*11]==5 && bu[cur*11+2]==3);
    const int32_t *bs=dw4_property_array(f,"BASE_SKILL",&n);assert(bs && !memcmp(bs+cur*9,skills,sizeof skills));
    assert(num(f,"LEVEL")==bl[row] && num(f,"EXP")==be[row]);
    const int32_t *sk=dw4_property_array(f,"SKILL",&n);assert(sk && n==9 && !memcmp(sk,bs+row*9,sizeof skills));
    /* Chip lists emptied and un-equipped; at most one weapon is equipped and it is POWERSOCKET[0]. */
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(items && n==before+1);
    const dw4_item_record *pocket=dw4_property_items(f,"POWERPOCKET",&n);assert(pocket && n==5);
    for(size_t i=0;i<n;i++)assert(pocket[i].kind==-1);
    assert(!items[before].equipped);
    unsigned equipped=0;for(size_t i=0;i<before;i++)equipped+=items[i].kind==0 && items[i].equipped;
    const dw4_item_record *sock=dw4_property_items(f,"POWERSOCKET",&n);assert(sock && n==3 && sock[1].kind==-1 && sock[2].kind==-1);
    assert(equipped<=1 && (equipped==1)==(sock[0].kind==0));
    assert((equipped==1)==(dw4_property_string_at(f,"POWERSOCKETNAME",0)!=NULL));
    /* Evolving back restores the saved progress of the first form. */
    assert(!dw4_playertransactions_evolve(p,0,cur,species_model,(void *)db,dw4_playerstats_item_attribute,item_model,(void *)db,dw4_playerstats_recalculate,(void *)db));
    assert(num(f,"LEVEL")==12 && num(f,"EXP")==345);
    const int32_t *up2=dw4_property_array(f,"UPCNT",&n);assert(up2 && up2[0]==5 && up2[2]==3);
    /* Without any owned weapon nothing is eligible and evolving leaves every socket and weapon name empty. */
    {static const int32_t none[5]={-1,-1,-1,-1,-1};
     assert(!dw4_property_set_items(f,"DEVICEFOLDER",NULL,0) && !dw4_property_set_array(f,"POWERSOCKETREF",none,3));
     assert(!dw4_playertransactions_weapon_check(p,0,target,dw4_playerstats_item_attribute,(void *)db,&ok) && ok==0);
     assert(!dw4_playertransactions_evolve(p,0,target,species_model,(void *)db,dw4_playerstats_item_attribute,item_model,(void *)db,dw4_playerstats_recalculate,(void *)db));
     sock=dw4_property_items(f,"POWERSOCKET",&n);assert(sock && n==3 && sock[0].kind==-1 && !dw4_property_string_at(f,"POWERSOCKETNAME",0));}
    /* The preview helper reads BASE data for every form. */
    int32_t form[16];assert(!dw4_playerstats_form(db,f,target,form) && form[0]>0 && form[1]>0);
    assert(dw4_playerstats_form(db,f,16,form)==-1);
}

/* ---- WPU/APU/CHIP/JUNK shops: price, stock selection, purchase, preview and donation ---- */
static int preview_slot_record;
static int equip_visit(void *u,dw4_property_folder *f)
{
    (void)u;size_t n;const dw4_item_record *w=dw4_property_items(f,"POWERSOCKET",&n);
    preview_slot_record=w && n==3?w[0].record:-1;return 0;
}
static void shop_test(dw4_playerrecords *p,const dw4_databases *db)
{
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Shop",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0),*common=dw4_playerrecords_get(p,"GETCOMMON",0);
    /* Level and investment rows (3d8740 tables). */
    assert(dw4_shopstock_level_row(9,29)==0 && dw4_shopstock_level_row(10,29)==1 && dw4_shopstock_level_row(51,29)==8 &&
           dw4_shopstock_level_row(52,29)==9 && dw4_shopstock_level_row(198,29)==29 && dw4_shopstock_level_row(999,24)==24 &&
           dw4_shopstock_level_row(-5,29)==0);
    assert(dw4_shopstock_investment_row(0)==-1 && dw4_shopstock_investment_row(999)==-1 && dw4_shopstock_investment_row(1000)==0 &&
           dw4_shopstock_investment_row(5999)==0 && dw4_shopstock_investment_row(6000)==1 &&
           dw4_shopstock_investment_row(3956000)==8 && dw4_shopstock_investment_row(99999999)==8);
    /* 448190 / 4480a0 draws: level 1 gives pocket offset 1, so v == draw%620. */
    assert(dw4_shopstock_pocket_roll(1,1)==5 && dw4_shopstock_pocket_roll(0,1)==4 && dw4_shopstock_pocket_roll(3,1)==4 &&
           dw4_shopstock_pocket_roll(4,1)==3 && dw4_shopstock_pocket_roll(7,1)==3 && dw4_shopstock_pocket_roll(8,1)==2 &&
           dw4_shopstock_pocket_roll(15,1)==2 && dw4_shopstock_pocket_roll(16,1)==1 && dw4_shopstock_pocket_roll(31,1)==1 &&
           dw4_shopstock_pocket_roll(32,1)==0 && dw4_shopstock_pocket_roll(619,1)==0);
    /* A higher level shifts the draw: level 100 subtracts (10+10)/10 = 2. */
    assert(dw4_shopstock_pocket_roll(2,100)==5 && dw4_shopstock_pocket_roll(1,100)==4);
    assert(dw4_shopstock_revision_roll(0,0,50)==51 && dw4_shopstock_revision_roll(6000,0,50)==51 &&
           dw4_shopstock_revision_roll(3000,10,50)==0 /* chance 3001: no enhancement */ &&
           dw4_shopstock_revision_roll(10,5,50)==6-1 /* span 6, chance 11 -> 6-1 */ &&
           dw4_shopstock_revision_roll(20,0,50)==0 /* span 1 - 2 clamps to 0 */);
    /* 447ed0: grade and enhancement surcharges. */
    const dw4_database *wd=dw4_databases_get(db,"weapon");int32_t hanbai=0,kaitori=0;int32_t record=-1;
    for(int32_t r=0;r<200 && record<0;r++)
        if(dw4_database_number(wd,r,"HANBAI",&hanbai)==0 && dw4_database_number(wd,r,"KAITORI",&kaitori)==0 && hanbai>0)record=r;
    assert(record>=0);
    dw4_item_record weapon={.kind=0,.record=record,.revision=2,.pocket=3};int32_t price;
    assert(!dw4_playerstats_item_price((void *)db,&weapon,0,&price) && price==hanbai+200+6000);
    assert(!dw4_playerstats_item_price((void *)db,&weapon,1,&price) && price==kaitori+50+3000);
    weapon.pocket=0;weapon.revision=0;
    assert(!dw4_playerstats_item_price((void *)db,&weapon,0,&price) && price==hanbai);
    weapon.pocket=6;assert(dw4_playerstats_item_price((void *)db,&weapon,0,&price)==-1);
    dw4_item_record yellow={.kind=2,.record=0,.revision=3,.pocket=5};int32_t y;
    if(!dw4_playerstats_item_attribute((void *)db,&yellow,"HANBAI",&y)){assert(!dw4_playerstats_item_price((void *)db,&yellow,0,&price) && price==y+300);}
    dw4_item_record chip={.kind=3,.record=0,.revision=9,.pocket=9};
    if(!dw4_playerstats_item_attribute((void *)db,&chip,"HANBAI",&y)){assert(!dw4_playerstats_item_price((void *)db,&chip,0,&price) && price==y);}
    /* The stock tables live in the Shop hub's packs; tools/test_hubshops.c covers dw4_shopstock_prepare against them. */
    int32_t counters[16];size_t n;memcpy(counters,dw4_property_array(common,"COUNTER",&n),sizeof counters);assert(n==16);
    /* Purchase: atomic debit and append; refusals change nothing. */
    assert(!dw4_property_set_number(f,"BIT",1000));
    size_t held;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&held));
    dw4_item_record bought={.kind=3,.record=1,.revision=0,.pocket=0};int result;
    assert(!dw4_playertransactions_shop_buy(p,0,&bought,300,&result) && result==1 && num(f,"BIT")==700);
    size_t after;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&after) && after==held+1);
    size_t nitems;const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&nitems);
    assert(items[held].kind==3 && items[held].record==1 && !items[held].equipped);
    assert(!dw4_playertransactions_shop_buy(p,0,&bought,701,&result) && result==0 && num(f,"BIT")==700);
    assert(dw4_playertransactions_shop_buy(p,0,&bought,-1,&result)==-1 && dw4_playertransactions_shop_buy(p,0,NULL,1,&result)==-1);
    dw4_item_record bad={.kind=4,.record=0};assert(dw4_playertransactions_shop_buy(p,0,&bad,1,&result)==-1);
    while(after<36){assert(!dw4_playertransactions_shop_buy(p,0,&bought,0,&result) && result==1);after++;}
    assert(!dw4_playertransactions_shop_buy(p,0,&bought,0,&result) && result==0 && num(f,"BIT")==700);
    /* Equip preview: the candidate replaces the first weapon on a staged copy only. */
    dw4_item_record cand={.kind=0,.record=record,.revision=1,.pocket=1};
    const dw4_item_record *sock=dw4_property_items(f,"POWERSOCKET",&nitems);int32_t live=sock[0].record;
    preview_slot_record=-2;
    assert(!dw4_playertransactions_equip_preview(p,0,&cand,dw4_playerstats_recalculate,(void *)db,equip_visit,NULL) && preview_slot_record==record);
    sock=dw4_property_items(f,"POWERSOCKET",&nitems);assert(sock[0].record==live);
    dw4_item_record chipc={.kind=3,.record=1};preview_slot_record=-2;
    assert(!dw4_playertransactions_equip_preview(p,0,&chipc,dw4_playerstats_recalculate,(void *)db,equip_visit,NULL) && preview_slot_record==live);
    assert(dw4_playertransactions_equip_preview(p,0,&cand,failing_recalc,NULL,equip_visit,NULL)==-1);
    sock=dw4_property_items(f,"POWERSOCKET",&nitems);assert(sock[0].record==live);
    /* Donation: BIT and the common investment move together. */
    assert(!dw4_property_set_number(f,"BIT",5000));counters[1]=100;assert(!dw4_property_set_array(common,"COUNTER",counters,16));
    assert(!dw4_playertransactions_junk_donate(p,0,1500,&result) && result==1 && num(f,"BIT")==3500);
    assert(dw4_property_array(common,"COUNTER",&n)[1]==1600);
    assert(!dw4_playertransactions_junk_donate(p,0,3501,&result) && result==0 && !dw4_playertransactions_junk_donate(p,0,0,&result) && result==0);
    assert(num(f,"BIT")==3500 && dw4_property_array(common,"COUNTER",&n)[1]==1600);
    assert(dw4_playertransactions_junk_donate(p,0,5,NULL)==-1);
}
/* SYSctlDiskFolder / SYSctlDeviceFolder (GAMERAM 3fca10 CTRLITEM DISK and DEVICE) through the engine call. */
static int folder_call(dw4_playerrecords *p,const char *method,const dw4_script_value *a,size_t n,int32_t *answer)
{
    dw4_script_value r;char e[256];int rc=dw4_playertransactions_folder_call(p,method,a,n,&r,e,sizeof e);
    if(!rc)*answer=(int32_t)r.number;return rc;
}
#define NUM(x) {DW4_SCRIPT_NUMBER,(x),NULL,0}
#define STR(x) {DW4_SCRIPT_STRING,0,(x),sizeof(x)-1}
static int32_t disk_op(dw4_playerrecords *p,const char *op,int32_t record,int32_t amount)
{
    dw4_script_value a[4]={{DW4_SCRIPT_STRING,0,op,strlen(op)},NUM(0),NUM(record),NUM(amount)};int32_t r=-9;
    assert(!folder_call(p,"SYSctlDiskFolder",a,4,&r));return r;
}
static int32_t device_op(dw4_playerrecords *p,const char *op,const char *kind,int32_t record,int32_t revision,int32_t pocket)
{
    dw4_script_value a[6]={{DW4_SCRIPT_STRING,0,op,strlen(op)},NUM(0),{DW4_SCRIPT_STRING,0,kind,strlen(kind)},NUM(record),NUM(revision),NUM(pocket)};
    int32_t r=-9;assert(!folder_call(p,"SYSctlDeviceFolder",a,6,&r));return r;
}
static void folder_services_test(dw4_playerrecords *p,const dw4_databases *db)
{
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","Fold",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);size_t n;
    const dw4_item_record *d=dw4_property_items(f,"DISKFOLDER",&n);assert(n==12);
    int32_t held=d[11].revision;assert(d[11].record==11 && held==0);
    /* Disk 11: SET adds up to nine (false when already nine), CLR subtracts down to zero. */
    assert(disk_op(p,"ISMAX",11,0)==0 && disk_op(p,"IS",11,0)==0 && disk_op(p,"CLR",11,9)==0);
    assert(disk_op(p,"SET",11,4)==1 && dw4_property_items(f,"DISKFOLDER",&n)[11].revision==4 && disk_op(p,"IS",11,0)==1);
    assert(disk_op(p,"SET",11,100)==1 && dw4_property_items(f,"DISKFOLDER",&n)[11].revision==9);
    assert(disk_op(p,"SET",11,1)==0 && disk_op(p,"ISMAX",11,0)==1 && dw4_property_items(f,"DISKFOLDER",&n)[11].revision==9);
    assert(disk_op(p,"CLR",11,3)==1 && dw4_property_items(f,"DISKFOLDER",&n)[11].revision==6 && disk_op(p,"ISMAX",11,0)==0);
    assert(disk_op(p,"CLR",11,9)==1 && dw4_property_items(f,"DISKFOLDER",&n)[11].revision==0);
    assert(disk_op(p,"CLR",11,9)==0 && disk_op(p,"IS",11,0)==0 && dw4_property_items(f,"DISKFOLDER",&n)[10].revision==d[10].revision);
    /* Operations the DISK kind does not implement answer false and change nothing. */
    assert(disk_op(p,"ISEQUIP",11,0)==0 && disk_op(p,"GET",11,0)==0 && disk_op(p,"ADD",11,5)==0 && dw4_property_items(f,"DISKFOLDER",&n)[11].revision==0);
    /* A missing record, a negative amount, an unknown operation and bad arity are refused, not guessed. */
    int32_t r;dw4_script_value bad[4]={STR("SET"),NUM(0),NUM(99),NUM(1)};assert(folder_call(p,"SYSctlDiskFolder",bad,4,&r)==-1);
    dw4_script_value neg[4]={STR("SET"),NUM(0),NUM(11),NUM(-1)};assert(folder_call(p,"SYSctlDiskFolder",neg,4,&r)==-1);
    dw4_script_value unk[4]={STR("NOPE"),NUM(0),NUM(11),NUM(1)};assert(folder_call(p,"SYSctlDiskFolder",unk,4,&r)==-1);
    dw4_script_value few[3]={STR("SET"),NUM(0),NUM(11)};assert(folder_call(p,"SYSctlDiskFolder",few,3,&r)==-1);
    dw4_script_value who[4]={STR("SET"),NUM(4),NUM(11),NUM(1)};assert(folder_call(p,"SYSctlDiskFolder",who,4,&r)==-1);
    assert(dw4_property_items(f,"DISKFOLDER",&n)[11].revision==0);
    /* SYSctlFlagFolder: the session FLAGFOLDER (twelve bytes): SET only from 0, CLR only from set, IS reads. */
    {
        dw4_script_value set[2]={STR("SET"),NUM(5)},clr[2]={STR("CLR"),NUM(5)},is[2]={STR("IS"),NUM(5)},is4[2]={STR("IS"),NUM(4)};
        int32_t v;
        assert(!folder_call(p,"SYSctlFlagFolder",is,2,&v) && v==0);
        assert(!folder_call(p,"SYSctlFlagFolder",clr,2,&v) && v==0);
        assert(!folder_call(p,"SYSctlFlagFolder",set,2,&v) && v==1 && !folder_call(p,"SYSctlFlagFolder",is,2,&v) && v==1);
        assert(!folder_call(p,"SYSctlFlagFolder",set,2,&v) && v==0 && !folder_call(p,"SYSctlFlagFolder",is4,2,&v) && v==0);
        size_t fn;const uint8_t *bytes=dw4_property_bytes(dw4_playerrecords_get(p,"GETCOMMON",0),"FLAGFOLDER",&fn);
        assert(fn==12 && bytes[5]==1 && bytes[4]==0);
        assert(!folder_call(p,"SYSctlFlagFolder",clr,2,&v) && v==1 && !folder_call(p,"SYSctlFlagFolder",is,2,&v) && v==0);
        dw4_script_value out[2]={STR("SET"),NUM(12)},neg[2]={STR("SET"),NUM(-1)},nope[2]={STR("NOPE"),NUM(1)},few[1]={STR("SET")};
        assert(folder_call(p,"SYSctlFlagFolder",out,2,&v)==-1 && folder_call(p,"SYSctlFlagFolder",neg,2,&v)==-1);
        assert(folder_call(p,"SYSctlFlagFolder",nope,2,&v)==-1 && folder_call(p,"SYSctlFlagFolder",few,1,&v)==-1);
    }
    /* Device folder: kind names select weapon/armor1/armor2/abChip; unknown names are no-ops. */
    size_t before;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    assert(device_op(p,"IS","weapon",200,0,0)==0 && device_op(p,"SET","weapon",200,10,1)==1);
    const dw4_item_record *it=dw4_property_items(f,"DEVICEFOLDER",&n);
    assert(n==before+1 && it[before].kind==0 && it[before].record==200 && it[before].revision==10 && it[before].pocket==1 && !it[before].equipped);
    assert(device_op(p,"IS","weapon",200,0,0)==1 && device_op(p,"IS","armor1",200,0,0)==0);
    assert(device_op(p,"SET","armor1",10,20,1)==1 && dw4_property_items(f,"DEVICEFOLDER",&n)[before+1].kind==1);
    assert(device_op(p,"SET","armor2",32,110,0)==1 && dw4_property_items(f,"DEVICEFOLDER",&n)[before+2].kind==2);
    assert(device_op(p,"SET","abChip",5,0,0)==1 && dw4_property_items(f,"DEVICEFOLDER",&n)[before+3].kind==3);
    assert(device_op(p,"SET","sword",1,1,1)==0 && device_op(p,"GET","weapon",200,0,0)==0 && dw4_property_item_count(f,"DEVICEFOLDER",&n)==0 && n==before+4);
    assert(device_op(p,"CLR","weapon",200,0,0)==1 && dw4_property_item_count(f,"DEVICEFOLDER",&n)==0 && n==before+3);
    /* ISMAX ignores the kind (a Lua number is accepted there) and is true only at 36 entries. */
    dw4_script_value ismax[6]={STR("ISMAX"),NUM(0),NUM(0),NUM(0),NUM(0),NUM(0)};assert(!folder_call(p,"SYSctlDeviceFolder",ismax,6,&r) && r==0);
    while(dw4_property_item_count(f,"DEVICEFOLDER",&n)==0 && n<36)assert(device_op(p,"SET","weapon",269,0,0)==1);
    assert(n==36 && !folder_call(p,"SYSctlDeviceFolder",ismax,6,&r) && r==1 && device_op(p,"SET","weapon",269,0,0)==0 && dw4_property_item_count(f,"DEVICEFOLDER",&n)==0 && n==36);
    dw4_script_value baddev[6]={STR("SET"),NUM(7),STR("weapon"),NUM(1),NUM(1),NUM(1)};assert(folder_call(p,"SYSctlDeviceFolder",baddev,6,&r)==-1);
    printf("folder services: SYSctlDiskFolder (SET/CLR/IS/ISMAX, saturation, refusals) and SYSctlDeviceFolder (kinds, capacity) match the recovered receiver\n");
}
/* Booster Pack opening (ShopCtrlA2 42eb80): odds boundaries, last-card fallback, pack consumption, atomicity. */
static int32_t pack_count(dw4_property_folder *f)
{size_t n;const dw4_item_record *v=dw4_property_items(f,"DISKFOLDER",&n);assert(v && n==12);for(size_t i=0;i<n;i++)if(v[i].record==10)return v[i].revision;assert(0);return -1;}
static void booster_test(dw4_playerrecords *p,const dw4_databases *db)
{
    char error[256];assert(!dw4_playerrecords_create(p,db,0,"p_agumon","Booster",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);
    size_t n;const dw4_item_record *disks=dw4_property_items(f,"DISKFOLDER",&n);assert(disks && n==12);
    dw4_item_record custom[12];memcpy(custom,disks,sizeof custom);size_t slot=0;while(slot<12 && custom[slot].record!=10)slot++;assert(slot<12);
    custom[slot].revision=3;assert(!dw4_property_set_items(f,"DISKFOLDER",custom,12));
    static const int32_t k[4]={500,300,150,50},rare[4]={0,1,2,1};
    size_t nc;const uint8_t *before=dw4_property_bytes(f,"CARDLIST",&nc);assert(before && nc==50);
    uint8_t base[50];memcpy(base,before,sizeof base);
    /* rolls: 0 -> card 0, 499 -> card 0, 500 -> card 1, 799 -> card 1, 800 -> card 2, 950 -> card 3, 1500 uses 500 -> card 1. */
    int32_t picks[3],top=-1;uint32_t a[3]={0,499,500};
    assert(!dw4_playertransactions_booster_open(p,0,k,rare,4,a,picks,&top));
    assert(picks[0]==0 && picks[1]==0 && picks[2]==1 && top==1 && pack_count(f)==2);
    uint32_t b[3]={799,800,950};assert(!dw4_playertransactions_booster_open(p,0,k,rare,4,b,picks,&top));
    assert(picks[0]==1 && picks[1]==2 && picks[2]==3 && top==2 && pack_count(f)==1);
    const uint8_t *after=dw4_property_bytes(f,"CARDLIST",&nc);for(int i=0;i<4;i++)assert(after[i]==1);
    for(int i=4;i<50;i++)assert(after[i]==base[i]);
    uint32_t c[3]={1500,0,0};assert(!dw4_playertransactions_booster_open(p,0,k,rare,4,c,picks,&top));assert(picks[0]==1 && pack_count(f)==0);
    /* A count of zero stays zero (retail does not refuse); odds that never reach r fall back to the last card. */
    static const int32_t low[2]={100,100},lr[2]={0,2};uint32_t z[3]={900,900,900};
    assert(!dw4_playertransactions_booster_open(p,0,low,lr,2,z,picks,&top));assert(picks[0]==1 && picks[1]==1 && top==2 && pack_count(f)==0);
    /* Bad input changes nothing. */
    int32_t cards_before[50];for(int i=0;i<50;i++)cards_before[i]=dw4_property_bytes(f,"CARDLIST",&nc)[i];
    assert(dw4_playertransactions_booster_open(p,0,k,rare,0,a,picks,&top)==-1);
    assert(dw4_playertransactions_booster_open(p,7,k,rare,4,a,picks,&top)==-1);
    assert(dw4_playertransactions_booster_open(p,0,NULL,rare,4,a,picks,&top)==-1);
    for(int i=0;i<50;i++)assert(dw4_property_bytes(f,"CARDLIST",&nc)[i]==cards_before[i]);
}
int main(int argc,char **argv)
{
    health_restore_test();
    int dump=argc>2 && !strcmp(argv[2],"--dump"),stats=argc>2 && !strcmp(argv[2],"--stats");
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../../local/extracted"));
    uint32_t size;const uint8_t *b=dw4_mount_data(&m,"stagML11/separate/USA_pack.igb",&size);assert(b);
    dw4_igb g={0};assert(!dw4_igb_open(&g,b,size,0) && !dw4_igb_refs_open(&g));
    dw4_stageobjects *s=dw4_stageobjects_open();assert(s && !dw4_stageobjects_route(s,"USA",&g,0));
    char error[256];dw4_databases *db=dw4_databases_open(s,error,sizeof error);assert(db);if(!stats)check_tables(s,db,dump);
    dw4_playerrecords *p=dw4_playerrecords_open();assert(p);
    if(stats){stats_cases(p,db);dw4_playerrecords_close(p);dw4_databases_close(db);dw4_stageobjects_close(s);dw4_igb_close(&g);dw4_mount_close(&m);return 0;}
    const char *models[]={"p_dorumon","p_agumon","p_vmon","p_girumon"},*names[]={"A","John","12345678","&!?+-*/="};
    const char *keys[]={"UNIQUE","XDATA","BIT","DIGIMONNO","LEVEL","EXP","ISUSE","HP","MHP","MP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO","NEXTEXP","ATTACKDELAY","MEICHURITSU","CHIMEIRITSU","MAHIRITSU","KAIHIRITSU","BOUGYORITSU","MAHITEIKOU","DOKUTEIKOU","BITRITSU","EXPRITSU","LUCKRITSU","ATTACKZOKUSEI","HPDRAIN","MPDRAIN","CHOHATURITSU","WEAPONRECNO","WEAPONSKILLNO","BANKBIT"};
    for(int cycle=0;cycle<16;cycle++){
        int slot=cycle%4,species=cycle/4;dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);
        char chosen[9];snprintf(chosen,sizeof chosen,"%s",names[slot]);
        assert(!dw4_playerrecords_create(p,db,slot,models[species],chosen,error,sizeof error));chosen[0]='X';
        assert(f==dw4_playerrecords_get(p,"GETPLAYER",slot));
        array(f,"BASE_LEVEL",16,1);array(f,"BASE_EXP",16,0);array(f,"BASE_SKILL",144,1);array(f,"BASE_UPCNT",176,0);
        array(f,"SKILL",9,1);array(f,"UPCNT",11,0);array(f,"UPDATA",11,0);array(f,"DOWNDATA",7,0);
        array(f,"BASE_COUNTER",16,0);
        const char *bytekeys[]={"BASE_FLAG","BASE_FLAGFOLDER","CARDLIST"};const size_t bytecounts[]={1024,12,50};
        for(unsigned k=0;k<3;k++){
            size_t length;const uint8_t *v=dw4_property_bytes(f,bytekeys[k],&length);assert(v && length==bytecounts[k]);
            if(dump)printf("B\t%d\t%s\t%s\t%s",slot,models[species],names[slot],bytekeys[k]);
            for(size_t i=0;i<length;i++){assert(v[i]==(k==0 && i==960));if(dump)printf("\t%u",v[i]);}
            if(dump)puts("");
        }
        size_t diskcount;const dw4_item_record *disks=dw4_property_items(f,"DISKFOLDER",&diskcount);assert(disks && diskcount==12);
        for(unsigned i=0;i<12;i++){
            assert(disks[i].kind==4 && disks[i].record==(int32_t)i && !disks[i].equipped && !disks[i].revision);
            if(dump)printf("D\t%d\t%s\t%s\t%u\t%d\t%d\t%d\t%d\n",slot,models[species],names[slot],i,disks[i].kind,disks[i].record,disks[i].equipped,disks[i].revision);
        }
        assert(!dw4_property_item_count(f,"BANKDEVICE",&diskcount) && !diskcount);
        int32_t no;assert(!dw4_property_number(f,"DIGIMONNO",&no));size_t n;const int32_t *use=dw4_property_array(f,"BASE_ISUSE",&n);assert(n==16);
        for(int i=0;i<16;i++)assert(use[i]==(i==no));
        dw4_unicode_object u;assert(!dw4_property_unicode_object(f,"PLAYERNAME",0,&u) && u.present && u.count==8);
        const char *converted=slot==3?"&!?+-":names[slot];
        for(unsigned i=0;i<8;i++)assert(u.codes[i]==(i<strlen(converted)?(unsigned char)converted[i]:0));
        for(size_t i=0;i<sizeof keys/sizeof *keys;i++){int32_t v;assert(!dw4_property_number(f,keys[i],&v));if(dump)printf("P\t%d\t%s\t%s\t%s\t%d\n",slot,models[species],names[slot],keys[i],v);}
        if(dump){printf("U\t%d\t%s\t%s",slot,models[species],names[slot]);for(int i=0;i<8;i++)printf("\t%u",u.codes[i]);puts("");}
        size_t ni;const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&ni);assert(items && ni==3);
        const dw4_item_record *sockets=dw4_property_items(f,"POWERSOCKET",&n);assert(sockets && n==3);
        const int32_t *refs=dw4_property_array(f,"POWERSOCKETREF",&n);assert(refs && n==3);
        for(unsigned i=0;i<3;i++)assert(refs[i]==(int32_t)i);
        const char *emptykeys[]={"POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
        const char *refkeys[]={"POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};
        const size_t sizes[]={5,1,5,1};
        for(unsigned k=0;k<4;k++){
            const dw4_item_record *empty=dw4_property_items(f,emptykeys[k],&n);assert(empty && n==sizes[k]);
            refs=dw4_property_array(f,refkeys[k],&n);assert(refs && n==sizes[k]);
            for(size_t i=0;i<n;i++)assert(empty[i].kind==-1 && refs[i]==-1);
        }
        for(int i=0;i<3;i++){assert(!memcmp(items+i,sockets+i,sizeof(*items)) && items[i].equipped==1 && !items[i].revision && !items[i].pocket);
            assert(dw4_property_string_at(f,"POWERSOCKETNAME",i));if(dump)printf("I\t%d\t%s\t%s\t%d\t%d\n",slot,models[species],names[slot],i,items[i].record);}
        int32_t count;assert(!dw4_property_number(dw4_playerrecords_get(p,"GETCOMMON",0),"NINZU",&count) && count==(cycle<4?cycle+1:4));
        const uint16_t *old=u.codes;
        const char *bad[]={"","123456789","\x80"};for(unsigned i=0;i<3;i++)assert(dw4_playerrecords_create(p,db,slot,models[species],bad[i],error,sizeof error)==-1);
        assert(dw4_playerrecords_create(p,NULL,slot,models[species],names[slot],error,sizeof error)==-1);
        assert(dw4_playerrecords_create(p,db,4,models[species],names[slot],error,sizeof error)==-1);
        assert(dw4_playerrecords_create(p,db,slot,"unknown",names[slot],error,sizeof error)==-1);
        assert(!dw4_property_unicode_object(f,"PLAYERNAME",0,&u) && u.codes==old);
    }
    xdata_test(p,db);
    chip_test(p,db);
    booster_test(p,db);
    folder_services_test(p,db);
    evolve_test(p,db);
    disk_test(p,db);
    cnos_test(p,db);
    bank_test(p,db);
    shop_test(p,db);
    assert(!dw4_playerrecords_join(p,0,0));int32_t joined;
    assert(!dw4_property_number(dw4_playerrecords_get(p,"GETCOMMON",0),"NINZU",&joined) && joined==3);
    assert(!dw4_playerrecords_join(p,0,1));
    /* Shared common views resolve player-zero base payloads across replacement
     * and private record publication. Other players never retarget them. */
    dw4_property_folder *common=dw4_playerrecords_get(p,"GETCOMMON",0),*first=dw4_playerrecords_get(p,"GETPLAYER",0);
    size_t n;const uint8_t *shared=dw4_property_bytes(common,"FLAG",&n);assert(n==1024 && shared==dw4_property_bytes(first,"BASE_FLAG",NULL));
    uint8_t flags[1024]={0};flags[7]=255;assert(!dw4_property_set_bytes(common,"FLAG",flags,1024));
    assert(dw4_property_bytes(first,"BASE_FLAG",NULL)[7]==255);
    dw4_playerrecords *staging=dw4_playerrecords_open();assert(staging);
    dw4_property_folder *updates=dw4_playerrecords_get(staging,"GETCOMMON",0);
    assert(!dw4_property_set_bytes(updates,"FLAG",flags,1024) && !dw4_property_commit_values(common,updates));
    assert(dw4_property_bytes(first,"BASE_FLAG",NULL)[7]==255 && dw4_property_bytes(common,"FLAG",NULL)==dw4_property_bytes(first,"BASE_FLAG",NULL));
    dw4_playerrecords_close(staging);
    float checkpoint[]={-0.0f,1.25f,-2.5f};assert(!dw4_property_set_floats(common,"BKCHIPPOS",checkpoint,3));
    assert(!memcmp(dw4_property_floats(common,"BKCHIPPOS",&n),checkpoint,sizeof checkpoint) && n==3);
    staging=dw4_playerrecords_open();assert(staging);updates=dw4_playerrecords_get(staging,"GETCOMMON",0);
    assert(!dw4_property_copy_values(updates,common));
    assert(dw4_property_bytes(updates,"FLAG",&n)[7]==255 && n==1024);
    assert(!memcmp(dw4_property_floats(updates,"BKCHIPPOS",&n),checkpoint,sizeof checkpoint));
    dw4_playerrecords_close(staging);
    dw4_databases_close(db);dw4_stageobjects_close(s);dw4_igb_close(&g);dw4_mount_close(&m);
    for(int i=0;i<4;i++){dw4_unicode_object u;assert(!dw4_property_unicode_object(dw4_playerrecords_get(p,"GETPLAYER",i),"PLAYERNAME",0,&u) && u.codes[0]);}
    dw4_playerrecords_close(p);if(!dump)puts("character creation: four starters in four slots; copied names/base stats/starter equipment, atomic failures and database teardown pass");return 0;
}
