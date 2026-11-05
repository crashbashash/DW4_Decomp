#include "dw4/playerstats.h"
#include <stdio.h>
#include <string.h>
static int32_t bits(uint32_t v){int32_t s;memcpy(&s,&v,4);return s;}
static int32_t add(int32_t a,int32_t b){return bits((uint32_t)a+(uint32_t)b);}
static int32_t sub(int32_t a,int32_t b){return bits((uint32_t)a-(uint32_t)b);}
static int32_t mul(int32_t a,int32_t b){return bits((uint32_t)a*(uint32_t)b);}
static int num(const dw4_database *d,int32_t row,const char *key,int32_t *v)
{return !d || dw4_database_number(d,row,key,v)<0?-1:0;}
static const dw4_database *itemdb(const dw4_databases *db,const dw4_item_record *i)
{
    static const char *const names[]={"weapon","armor1","armor2","abChip"};
    return i && i->kind>=0 && i->kind<4?dw4_databases_get(db,names[i->kind]):NULL;
}
int dw4_playerstats_item_attribute(void *db,const dw4_item_record *i,const char *key,int32_t *v)
{return !v || !key?-1:num(itemdb(db,i),i?i->record:-1,key,v);}
int dw4_playerstats_item_bool(void *db,const dw4_item_record *i,const char *key,int32_t *v)
{const dw4_database *d=itemdb(db,i);return !d || !v || !key || dw4_database_bool(d,i->record,key,v)!=0?-1:0;}
/* 447ed0: the listed HANBAI (shop price) or KAITORI (buy-back price) plus the enhancement and grade
 * surcharges of weapons and armor (revision*100 / *25, and for weapons and blue armor the pocket-grade
 * table at 4cfe90 / 4cfeb0). Yellow armor adds only the revision; chips are unmodified. A pocket
 * count outside the six table entries would read past the table in retail and is refused. */
int dw4_playerstats_item_price(void *db,const dw4_item_record *i,int sell,int32_t *v)
{
    static const int32_t grade[2][6]={{0,500,1500,6000,12000,24000},{0,250,750,3000,6000,12000}};
    int32_t base;
    if(!i || !v || dw4_playerstats_item_attribute(db,i,sell?"KAITORI":"HANBAI",&base))return -1;
    int32_t per=sell?25:100;
    if(i->kind==2)base=add(base,mul(i->revision,per));
    else if(i->kind==0 || i->kind==1) {
        if(i->pocket<0 || i->pocket>5)return -1;
        base=add(add(base,mul(i->revision,per)),grade[sell?1:0][i->pocket]);
    }
    *v=base;return 0;
}
static const int32_t limits[]={5,10,20,30,50,70,110,150,230,999};
static const int32_t origins[]={1,5,10,20,30,50,70,110,150,230};
static const int32_t hpbase[]={0,40,140,640,1440,3840,7440,17840,25040,34640};
static const int32_t hprate[]={10,20,50,80,120,180,260,180,120,80};
static const int32_t statbase[]={0,40,85,165,235,355,455,615,735,895};
static const int32_t statrate[]={10,9,8,7,6,5,4,3,2,1};
/* Recovered 4cf130..4cf220; multiply/add truncate to EE signed words before DIV. */
static int growth(const dw4_database *sh,int species,int level,const int32_t *up,unsigned which,int32_t *v)
{
    static const char *const initial[]={"MHP_INI","MMP_INI","STR_INI","AC_INI","INT_INI","MND_INI","DEX_INI"};
    static const char *const grow[]={"MHP_GROW","MMP_GROW","STR_GROW","AC_GROW","INT_GROW","MND_GROW","DEX_GROW"};
    unsigned seg=0;while(limits[seg]<level)seg++;
    int32_t a,b;if(num(sh,species,initial[which],&a) || num(sh,species,grow[which],&b))return -1;
    int32_t term=add(which<2?hpbase[seg]:statbase[seg],mul(which<2?hprate[seg]:statrate[seg],sub(level,origins[seg])));
    *v=add(add(up[which],a),mul(b,term)/100);
    if(*v>(which<2?99999:9999))*v=which<2?99999:9999;
    return 0;
}
struct equipment {const dw4_databases *db;const dw4_item_record *list[5];size_t count[5];};
static int bonus(const struct equipment *e,int32_t *v,const char *key,unsigned list,int revision)
{
    size_t n=(list==0 || list==2 || list==4)?1:e->count[list];
    for(size_t j=0;j<n;j++){
        const dw4_item_record *i=e->list[list]+j;if(i->kind==-1)continue;
        int32_t b;if(dw4_playerstats_item_attribute((void *)e->db,i,key,&b))return -1;
        *v=add(*v,b);
        if(revision){
            if(list!=4)*v=add(*v,i->revision);
            else {const char *s=dw4_database_string(itemdb(e->db,i),i->record,"SHUSEINOURYOKU");
                if(s && !strcmp(s,key))*v=add(*v,i->revision);}
        }
    }
    return 0;
}
static int bounded(dw4_property_folder *f,const char *key,int32_t v,int low,int high)
{if(v<low)v=low;if(v>high)v=high;return dw4_property_set_number(f,key,v);}
static int recalculate(void *receiver,dw4_property_folder *f,int equipment)
{
    const dw4_databases *db=receiver;const dw4_database *sh=dw4_databases_get(db,"shinka"),*tech=dw4_databases_get(db,"pcTech");
    int32_t species,level,oldhp,oldmp;size_t n;
    if(!f || !sh || !tech || dw4_property_number(f,"DIGIMONNO",&species) || species<0 || species>=16 ||
       dw4_property_number(f,"LEVEL",&level) || level<1 || level>999 || dw4_property_number(f,"HP",&oldhp) || dw4_property_number(f,"MP",&oldmp))return -1;
    const int32_t *up=dw4_property_array(f,"UPCNT",&n);if(!up || n!=11)return -1;
    const int32_t *plus=dw4_property_array(f,"UPDATA",&n);if(!plus || n!=11)return -1;
    const int32_t *minus=dw4_property_array(f,"DOWNDATA",&n);if(!minus || n!=7)return -1;
    const int32_t *skills=dw4_property_array(f,"SKILL",&n);if(!skills || n!=9)return -1;
    struct equipment e={.db=db};
    static const char *const keys[]={"POWERSOCKET","POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
    static const size_t counts[]={3,5,1,5,1};static const int kinds[]={0,3,1,3,2};
    for(unsigned k=0;k<5;k++){
        e.list[k]=dw4_property_items(f,keys[k],e.count+k);if(!e.list[k] || e.count[k]!=counts[k])return -1;
        for(size_t j=0;j<e.count[k];j++)if(e.list[k][j].kind!=-1 && e.list[k][j].kind!=kinds[k])return -1;
    }
    const char *fields[]={"MHP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO"};
    const char *attr[]={"MAXHP","MAXMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","RES_FIRE","RES_ICE","RES_THUNDER","RES_DARK"};
    for(unsigned k=0;k<11;k++){
        int32_t v;
        if(k<7){if(growth(sh,species,level,up,k,&v))return -1;}
        else {if(num(sh,species,attr[k],&v))return -1;v=add(add(v,up[k]),plus[k]);}
        if(k==0)v=add(v,plus[6]);
        if(k==2 || k==3 || k==6){unsigned index=k==6?0:k+2;v=sub(add(v,plus[index]),minus[index]);}
        /* 3fab90's third argument gates every equipment-bonus helper (eleven stat sites). */
        if(!equipment){}
        else if(k<2 || k==3){if(bonus(&e,&v,attr[k],2,k==3) || bonus(&e,&v,attr[k],4,k==3))return -1;}
        else if(k==2){if(bonus(&e,&v,attr[k],0,1) || bonus(&e,&v,attr[k],1,0) || bonus(&e,&v,attr[k],4,1))return -1;}
        else {
            if(k<7 && (bonus(&e,&v,attr[k],0,0) || bonus(&e,&v,attr[k],1,0)))return -1;
            if(bonus(&e,&v,attr[k],2,0) || bonus(&e,&v,attr[k],3,0) || bonus(&e,&v,attr[k],4,k!=5))return -1;
        }
        /* HP/MP have only an upper cap, including after equipment bonuses. */
        if(k<2){if(v>99999)v=99999;if(dw4_property_set_number(f,fields[k],v))return -1;
            if((k==0?(oldhp==0 || v<oldhp):(oldhp==0 || v<oldmp)) && dw4_property_set_number(f,k==0?"HP":"MP",v))return -1;
        }else if(bounded(f,fields[k],v,1,9999))return -1;
    }
    dw4_item_record waza[6];size_t nw=0;char key[32];
    for(unsigned k=1;k<=6;k++){
        int32_t base,skill,need;snprintf(key,sizeof key,"TECH%u",k);if(num(sh,species,key,&base) || num(tech,base,"SKILL",&skill) || skill<0 || skill>=9)return -1;
        snprintf(key,sizeof key,"TECH%u_LEVEL",k);if(num(sh,species,key,&need))return -1;
        if(need>level)continue;
        for(int tier=4;tier>=0;tier--){snprintf(key,sizeof key,"TECH%u_SKILL%d",k,tier+1);if(num(sh,species,key,&need))return -1;
            if(need<=skills[skill]){waza[nw++]=(dw4_item_record){.kind=9,.record=add(base,tier),.revision=base};break;}}
    }
    if(dw4_property_set_items(f,"WAZALIST",waza,nw) || dw4_property_set_number(f,"NEXTEXP",level==999?0:add(mul(level,200),mul(mul(add(level,140),level),level))))return -1;
    /* Both tail sections (delay/accuracy/extras, then element/weapon/models) are gated by
     * the same flag; with it clear 3fab90 returns here. */
    if(!equipment)return 0;
    int32_t v=minus[6];if(bonus(&e,&v,"DELAY",0,0) || dw4_property_set_number(f,"ATTACKDELAY",v>70?70:v))return -1;
    v=0;if(bonus(&e,&v,"MEICHURITSU",0,0) || dw4_property_set_number(f,"MEICHURITSU",v))return -1;
    v=sub(plus[1],minus[1]);if(bonus(&e,&v,"CHIMEIRITSU",0,0) || bonus(&e,&v,"CHIMEIRITSU",1,0) || bounded(f,"CHIMEIRITSU",v,1,INT32_MAX))return -1;
    v=0;if(bonus(&e,&v,"MAHIRITSU",0,0) || dw4_property_set_number(f,"MAHIRITSU",v))return -1;
    v=sub(plus[3],minus[3]);if(bonus(&e,&v,"CHOHATURITSU",3,0) || bounded(f,"KAIHIRITSU",v,1,INT32_MAX) || bounded(f,"CHOHATURITSU",v,1,INT32_MAX))return -1;
    const char *extras[]={"BOUGYORITSU","MAHITEIKOU","DOKUTEIKOU","BITRITSU","EXPRITSU","LUCKRITSU","HPDRAIN","MPDRAIN"};
    const unsigned owners[]={2,2,2,4,4,4,1,1};
    for(unsigned k=0;k<8;k++){v=k==1?sub(plus[2],minus[2]):0;if(bonus(&e,&v,extras[k],owners[k],0) || bounded(f,extras[k],v,k==1?1:INT32_MIN,INT32_MAX))return -1;}
    int32_t element=-1;const char *elements[]={"fire","ice","thunder","dark"};
    for(size_t j=0;j<e.count[1] && element<0;j++)if(e.list[1][j].kind!=-1){const char *s=dw4_database_string(itemdb(db,e.list[1]+j),e.list[1][j].record,"ZOKUSEI");
        for(unsigned k=0;s && k<4;k++)if(!strcmp(s,elements[k])){element=k;break;}}
    const dw4_item_record *weapon=e.list[0];int32_t rec=0,skill=0;
    if(weapon->kind!=-1){rec=weapon->record;if(dw4_playerstats_item_attribute(receiver,weapon,"SKILL",&skill))return -1;}
    const char *models[3];size_t nm=0;
    for(size_t j=0;j<3;j++)if(e.list[0][j].kind!=-1){const char *s=dw4_database_string(itemdb(db,e.list[0]+j),e.list[0][j].record,"MODEL");models[nm++]=s?s:"";}
    return dw4_property_set_number(f,"ATTACKZOKUSEI",element) || dw4_property_set_number(f,"WEAPONRECNO",rec) || dw4_property_set_number(f,"WEAPONSKILLNO",skill) || dw4_property_set_strings(f,"POWERSOCKETNAME",models,nm)?-1:0;
}
int dw4_playerstats_recalculate(void *receiver,dw4_property_folder *f){return recalculate(receiver,f,1);}
int dw4_playerstats_recalculate_base(void *receiver,dw4_property_folder *f){return recalculate(receiver,f,0);}
int dw4_playertransactions_equip_database(dw4_playerrecords *p,int32_t slot,const char *key,size_t pos,int32_t candidate,const dw4_databases *db)
{return dw4_playertransactions_equip(p,slot,key,pos,candidate,dw4_playerstats_item_attribute,(void *)db,dw4_playerstats_recalculate,(void *)db);}
int dw4_playerstats_form(const dw4_databases *db,const dw4_property_folder *f,int32_t species,int32_t out[16])
{
    size_t n;const dw4_database *sh=dw4_databases_get(db,"shinka");
    const int32_t *level=dw4_property_array(f,"BASE_LEVEL",&n);if(!sh || !out || !level || n!=16 || species<0 || species>=16)return -1;
    const int32_t *up=dw4_property_array(f,"BASE_UPCNT",&n);if(!up || n!=176)return -1;
    const int32_t *skill=dw4_property_array(f,"BASE_SKILL",&n);if(!skill || n!=144)return -1;
    for(unsigned which=0;which<7;which++)if(growth(sh,species,level[species],up+species*11,which,out+which))return -1;
    memcpy(out+7,skill+species*9,9*sizeof *out);return 0;
}
