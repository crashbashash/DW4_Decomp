#include "dw4/playertransactions.h"
#include <string.h>
#include <stdlib.h>
static const char *const families[]={"TSUYOSA","KASHIKOSA","SEISHIN","SUBAYASA",
    "RES_FIRE","RES_ICE","RES_THUNDER","RES_DARK","CHIMEIRITSU","HPDRAIN","MPDRAIN","CHOHATURITSU"};
int dw4_weapon_eligible(int32_t species,const int32_t skills[9],uint32_t mask,int32_t skill,int32_t threshold)
{return skills && skill>=0 && skill<9 && (mask & (UINT32_C(1)<<((uint32_t)species&31))) && skills[skill]>=threshold;}
int dw4_equipment_assign(dw4_item_record *items,size_t count,int32_t *refs,size_t slots,
    size_t slot,int32_t candidate,dw4_item_attribute attr,void *user)
{
    if((count && !items) || !refs || slot>=slots || candidate < -1 ||
       (candidate>=0 && (size_t)candidate>=count))return -1;
    for(size_t i=0;i<slots;i++)if(refs[i]<-1 || (refs[i]>=0 && (size_t)refs[i]>=count))return -1;
    int family=-1;unsigned char *exclude=NULL;
    if(candidate>=0 && candidate!=refs[slot] && items[candidate].kind==3){
        if(!attr)return -1;
        for(unsigned i=0;i<sizeof families/sizeof *families;i++){
            int32_t v;if(attr(user,items+candidate,families[i],&v))return -1;
            if(v>0){family=(int)i;break;}
        }
        /* Retail accesses -1 if no family exists; malformed native data fails. */
        if(family<0)return -1;
        exclude=calloc(slots,1);if(!exclude)return -1;
        for(size_t i=0;i<slots;i++)if(refs[i]>=0){int32_t v;
            if(attr(user,items+refs[i],families[family],&v)){free(exclude);return -1;}
            exclude[i]=v>0;
        }
    }
    int32_t old=refs[slot];if(old>=0)items[old].equipped=0;refs[slot]=-1;
    if(candidate==old){free(exclude);return 0;}
    if(candidate>=0){
        for(size_t i=0;i<slots;i++)if(refs[i]>=0 && (refs[i]==candidate || (exclude && exclude[i]))){
            items[refs[i]].equipped=0;refs[i]=-1;
        }
        items[candidate].equipped=1;refs[slot]=candidate;
    }
    free(exclude);return 0;
}
static dw4_property_folder *stage(dw4_playerrecords **owner,dw4_property_folder *source)
{
    *owner=dw4_playerrecords_open();if(!*owner)return NULL;
    dw4_property_folder *s=dw4_playerrecords_get(*owner,"GETPLAYER",0);
    if(dw4_property_copy_values(s,source)){dw4_playerrecords_close(*owner);*owner=NULL;return NULL;}
    return s;
}
static const char *const equipment[]={"POWERSOCKET","POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
static const char *const refkeys[]={"POWERSOCKETREF","POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};
static const size_t lengths[]={3,5,1,5,1};
int dw4_playertransactions_device(dw4_playerrecords *players,int32_t slot,dw4_device_operation op,
    int32_t kind,int32_t record,int32_t revision,int32_t pocket,int *result)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",slot);size_t count;
    if(!f || !result || op<DW4_DEVICE_SET || op>DW4_DEVICE_ISEQUIP || kind<0 || kind>3)return -1;
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&count);
    if(dw4_property_item_count(f,"DEVICEFOLDER",&count) || count>36)return -1;
    size_t found=count;
    for(size_t i=0;i<count;i++)if(items[i].kind==kind && items[i].record==record &&
        (op!=DW4_DEVICE_CLR || !(uint8_t)items[i].equipped) &&
        (op!=DW4_DEVICE_ISEQUIP || (uint8_t)items[i].equipped)){found=i;break;}
    int answer=0;
    if(op==DW4_DEVICE_IS || op==DW4_DEVICE_ISEQUIP){*result=found<count;return 0;}
    if(op==DW4_DEVICE_ISMAX){*result=count==36;return 0;}
    if((op==DW4_DEVICE_SET && count==36) || (op==DW4_DEVICE_CLR && found==count)){*result=0;return 0;}
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    dw4_item_record copy[36];if(count)memcpy(copy,items,count*sizeof(*copy));
    if(op==DW4_DEVICE_SET){
        copy[count++]=(dw4_item_record){kind,record,0,kind==3?0:revision,kind<2?pocket:0};answer=1;
    }else{
        memmove(copy+found,copy+found+1,(count-found-1)*sizeof(*copy));count--;answer=1;
        /* Compaction preserves item identity in every equipment list. */
        for(unsigned k=0;k<5;k++){
            size_t n;const int32_t *v=dw4_property_array(s,refkeys[k],&n);int32_t refs[5];
            if(!v || n!=lengths[k])goto bad;
            for(size_t i=0;i<n;i++){
                if(v[i]==(int32_t)found)goto bad;
                refs[i]=v[i]>(int32_t)found?v[i]-1:v[i];
            }
            if(dw4_property_set_array(s,refkeys[k],refs,n))goto bad;
        }
    }
    if(dw4_property_set_items(s,"DEVICEFOLDER",copy,count) || dw4_property_commit_values(f,s))goto bad;
    dw4_playerrecords_close(owner);*result=answer;return 0;
bad:dw4_playerrecords_close(owner);return -1;
}
static int equipment_transaction(dw4_playerrecords *players,int32_t slot,const char *key,
    size_t position,int32_t candidate,dw4_item_attribute attr,void *attruser,
    dw4_player_recalculate recalc,void *recalcuser,int commit)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",slot);unsigned k=0;
    if(!f || !key || !recalc)return -1;
    for(;k<5 && strcmp(key,equipment[k]);k++);
    if(k==5)return -1;
    size_t count,n;const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&count);
    const int32_t *links=dw4_property_array(f,refkeys[k],&n);
    if(dw4_property_item_count(f,"DEVICEFOLDER",&count) || count>36 || !links || n!=lengths[k] || position>=n || candidate < -1 ||
       (candidate>=0 && ((size_t)candidate>=count || items[candidate].kind!=(k==0?0:k==2?1:k==4?2:3))))return -1;
    /* A candidate owned by another equipment list is not an accepted selection. */
    for(unsigned other=0;candidate>=0 && other<5;other++)if(other!=k){
        size_t len;const int32_t *r=dw4_property_array(f,refkeys[other],&len);
        if(!r || len!=lengths[other])return -1;
        for(size_t i=0;i<len;i++)if(r[i]==candidate)return -1;
    }
    dw4_item_record copy[36],projection[5]={0};int32_t refs[5];
    if(count)memcpy(copy,items,count*sizeof(*copy));
    memcpy(refs,links,n*sizeof(*refs));
    if(dw4_equipment_assign(copy,count,refs,n,position,candidate,attr,attruser))return -1;
    for(size_t i=0;i<n;i++)projection[i]=refs[i]<0?(dw4_item_record){.kind=-1}:copy[refs[i]];
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    if(dw4_property_set_items(s,"DEVICEFOLDER",copy,count) || dw4_property_set_array(s,refkeys[k],refs,n) ||
       dw4_property_set_items(s,key,projection,n) || recalc(recalcuser,s) ||
       (commit && dw4_property_commit_values(f,s))){
        dw4_playerrecords_close(owner);return -1;
    }
    dw4_playerrecords_close(owner);return 0;
}
int dw4_playertransactions_equip(dw4_playerrecords *p,int32_t slot,const char *key,size_t pos,
    int32_t candidate,dw4_item_attribute a,void *u,dw4_player_recalculate r,void *v)
{return equipment_transaction(p,slot,key,pos,candidate,a,u,r,v,1);}
int dw4_playertransactions_preview(dw4_playerrecords *p,int32_t slot,const char *key,size_t pos,
    int32_t candidate,dw4_item_attribute a,void *u,dw4_player_recalculate r,void *v)
{return equipment_transaction(p,slot,key,pos,candidate,a,u,r,v,0);}
int dw4_playertransactions_current_to_base(dw4_playerrecords *players,int32_t slot)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",slot);int32_t species,level,exp;
    if(!f || dw4_property_number(f,"DIGIMONNO",&species) || species<0 || species>=16 ||
       dw4_property_number(f,"LEVEL",&level) || dw4_property_number(f,"EXP",&exp))return -1;
    const char *keys[]={"BASE_LEVEL","BASE_EXP","BASE_SKILL","BASE_UPCNT"};
    const size_t counts[]={16,16,144,176};int32_t arrays[4][176];size_t n;
    for(unsigned k=0;k<4;k++){
        const int32_t *v=dw4_property_array(f,keys[k],&n);if(!v || n!=counts[k])return -1;
        memcpy(arrays[k],v,n*sizeof(*v));
    }
    arrays[0][species]=level;arrays[1][species]=exp;
    const int32_t *skills=dw4_property_array(f,"SKILL",&n);if(!skills || n!=9)return -1;
    memcpy(arrays[2]+species*9,skills,9*sizeof(*skills));
    const int32_t *up=dw4_property_array(f,"UPCNT",&n);if(!up || n!=11)return -1;
    memcpy(arrays[3]+species*11,up,11*sizeof(*up));
    dw4_playerrecords *owner=dw4_playerrecords_open();if(!owner)return -1;
    dw4_property_folder *s=dw4_playerrecords_get(owner,"GETPLAYER",0);
    int32_t use;if(dw4_property_number(f,"ISUSE",&use) || dw4_property_set_number(s,"ISUSE",use))goto bad;
    for(unsigned k=0;k<4;k++)if(dw4_property_set_array(s,keys[k],arrays[k],counts[k]))goto bad;
    if(dw4_property_commit_values(f,s))goto bad;
    dw4_playerrecords_close(owner);return 0;
bad:dw4_playerrecords_close(owner);return -1;
}

int dw4_playertransactions_recalculate(dw4_playerrecords *p,int32_t slot,dw4_player_recalculate r,void *u)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);if(!f || !r)return -1;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    if(r(u,s) || dw4_property_commit_values(f,s)){dw4_playerrecords_close(owner);return -1;}
    dw4_playerrecords_close(owner);return 0;
}
int32_t dw4_xdata_price(int32_t stat)
{
    uint32_t wrapped=(uint32_t)stat-45u;int32_t n;memcpy(&n,&wrapped,4);
    int32_t q=n/5+(n%5!=0);
    return q>400?400:q<0?1:q;
}
int dw4_xdata_stat(int32_t parameter,const char **key,int32_t *limit,int *upcnt_index)
{
    static const char *const keys[]={"TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","MHP","MMP"};
    static const int index[]={2,3,4,5,6,0,1};
    if(parameter<0 || parameter>6)return -1;
    if(key)*key=keys[parameter];
    if(limit)*limit=parameter<5?9999:99999;
    if(upcnt_index)*upcnt_index=index[parameter];
    return 0;
}
int dw4_playertransactions_xdata_upgrade(dw4_playerrecords *p,int32_t slot,int32_t parameter,
    dw4_player_recalculate recalc,void *recalcuser)
{
    const char *key;int index;int32_t stat,balance;size_t n;
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);
    /* Retail's undefined out-of-range selector is refused rather than reproduced. */
    if(!f || !recalc || dw4_xdata_stat(parameter,&key,NULL,&index) ||
       dw4_property_number(f,key,&stat) || dw4_property_number(f,"XDATA",&balance))return -1;
    const int32_t *up=dw4_property_array(f,"UPCNT",&n);if(!up || n!=11)return -1;
    int32_t counts[11];memcpy(counts,up,sizeof counts);
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    uint32_t debited=(uint32_t)balance-(uint32_t)dw4_xdata_price(stat);int32_t after;memcpy(&after,&debited,4);
    uint32_t bumped=(uint32_t)counts[index]+1u;memcpy(counts+index,&bumped,4);
    int32_t mhp,mmp;
    if(dw4_property_set_number(s,"XDATA",after) || dw4_property_set_array(s,"UPCNT",counts,11) || recalc(recalcuser,s) ||
       dw4_property_number(s,"MHP",&mhp) || dw4_property_number(s,"MMP",&mmp) ||
       dw4_property_set_number(s,"HP",mhp) || dw4_property_set_number(s,"MP",mmp) ||
       dw4_property_commit_values(f,s)){dw4_playerrecords_close(owner);return -1;}
    dw4_playerrecords_close(owner);return 0;
}

/* Raise one chip's catalogue record on a staged folder and rebuild every equipment projection. */
/* Publish DEVICEFOLDER and re-project every equipment list from its references. */
static int device_publish(dw4_property_folder *s,const dw4_item_record *copy,size_t count)
{
    if(dw4_property_set_items(s,"DEVICEFOLDER",copy,count))return -1;
    for(unsigned k=0;k<5;k++){
        size_t n;const int32_t *refs=dw4_property_array(s,refkeys[k],&n);
        if(!refs || n!=lengths[k])return -1;
        dw4_item_record projection[5];
        for(size_t i=0;i<n;i++)projection[i]=refs[i]<0 || (size_t)refs[i]>=count?(dw4_item_record){.kind=-1}:copy[refs[i]];
        if(dw4_property_set_items(s,equipment[k],projection,n))return -1;
    }
    return 0;
}
static int chip_bump(dw4_property_folder *s,size_t index)
{
    size_t count;const dw4_item_record *items=dw4_property_items(s,"DEVICEFOLDER",&count);
    if(!items || count>36 || index>=count || items[index].kind!=3)return -1;
    dw4_item_record copy[36];if(count)memcpy(copy,items,count*sizeof *copy);
    uint32_t record=(uint32_t)copy[index].record+1u;memcpy(&copy[index].record,&record,4);
    return device_publish(s,copy,count);
}
int dw4_playertransactions_chip_preview(dw4_playerrecords *p,int32_t slot,size_t index,
    dw4_player_recalculate recalc,void *recalcuser,dw4_player_preview_visit visit,void *visituser)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);if(!f || !recalc || !visit)return -1;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    int rc=chip_bump(s,index) || recalc(recalcuser,s) || visit(visituser,s);
    dw4_playerrecords_close(owner);return rc?-1:0;
}
int dw4_playertransactions_chip_upgrade(dw4_playerrecords *p,int32_t slot,size_t index,
    dw4_item_attribute attr,void *attruser,dw4_player_recalculate recalc,void *recalcuser)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);size_t count;int32_t cost,balance;
    const dw4_item_record *items=f?dw4_property_items(f,"DEVICEFOLDER",&count):NULL;
    if(!items || !attr || !recalc || count>36 || index>=count || items[index].kind!=3 ||
       attr(attruser,items+index,"NEXTX",&cost) || dw4_property_number(f,"XDATA",&balance))return -1;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    uint32_t debited=(uint32_t)balance-(uint32_t)cost;int32_t after;memcpy(&after,&debited,4);
    int rc=dw4_property_set_number(s,"XDATA",after) || chip_bump(s,index) || recalc(recalcuser,s) ||
        dw4_property_commit_values(f,s);
    dw4_playerrecords_close(owner);return rc?-1:0;
}
/* ShopCtrlSales buy (438160): BIT is debited and the listed item object joins DEVICEFOLDER (36 slots) in one
 * publication. Retail checks the balance and the 0x24 capacity before offering the purchase; both are
 * refused here as well (*result 0), so a stale caller cannot overdraw or overflow. */
int dw4_playertransactions_shop_buy(dw4_playerrecords *p,int32_t slot,const dw4_item_record *item,int32_t price,int *result)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);size_t count=0;int32_t bit;
    const dw4_item_record *items=NULL;
    if(!result || !item || !f || dw4_property_item_count(f,"DEVICEFOLDER",&count) || count>36 ||
       (count && !(items=dw4_property_items(f,"DEVICEFOLDER",&count))) ||
       item->kind<0 || item->kind>3 || item->record<0 || price<0 || dw4_property_number(f,"BIT",&bit))return -1;
    if(count>=36 || bit<price){*result=0;return 0;}
    dw4_item_record copy[36];if(count)memcpy(copy,items,count*sizeof *copy);
    copy[count]=*item;copy[count].equipped=0;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    int rc=dw4_property_set_number(s,"BIT",bit-price) || device_publish(s,copy,count+1) || dw4_property_commit_values(f,s);
    dw4_playerrecords_close(owner);if(rc)return -1;*result=1;return 0;
}
/* 439f30 with the preview flag: the candidate replaces the first entry of its slot list (weapon: POWERSOCKET,
 * blue armor: MAINSLOT, yellow armor: SUBSLOT; a chip replaces nothing), the player is recalculated and the
 * staged folder is handed to visit. Retail mutates the live lists and restores them afterwards; the staged
 * copy gives the same observable result and leaves the records untouched. */
int dw4_playertransactions_equip_preview(dw4_playerrecords *p,int32_t slot,const dw4_item_record *candidate,
    dw4_player_recalculate recalc,void *recalcuser,dw4_player_preview_visit visit,void *visituser)
{
    static const char *const keys[]={"POWERSOCKET","MAINSLOT","SUBSLOT"};
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);
    if(!f || !candidate || !recalc || !visit || candidate->kind<0 || candidate->kind>3)return -1;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    int rc=0;
    if(candidate->kind<3) {
        size_t n;const dw4_item_record *list=dw4_property_items(s,keys[candidate->kind],&n);
        if(!list || !n || n>5)rc=-1;
        else {
            dw4_item_record copy[5];memcpy(copy,list,n*sizeof *copy);copy[0]=*candidate;
            rc=dw4_property_set_items(s,keys[candidate->kind],copy,n);
        }
    }
    rc=rc || recalc(recalcuser,s) || visit(visituser,s);
    dw4_playerrecords_close(owner);return rc?-1:0;
}
/* Junk shop donation (beNDMWShopJunk 42bc70 main 1): the amount leaves BIT and joins the common COUNTER[1]
 * investment that selects the junk stock tier. Both records are published together. */
int dw4_playertransactions_junk_donate(dw4_playerrecords *p,int32_t slot,int32_t amount,int *result)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot),*common=dw4_playerrecords_get(p,"GETCOMMON",0);
    int32_t bit,counters[16];size_t n;
    const int32_t *counter=common?dw4_property_array(common,"COUNTER",&n):NULL;
    if(!result || !f || !counter || n!=16 || dw4_property_number(f,"BIT",&bit))return -1;
    if(amount<=0 || bit<amount){*result=0;return 0;}
    memcpy(counters,counter,sizeof counters);
    uint32_t raised=(uint32_t)counters[1]+(uint32_t)amount;memcpy(counters+1,&raised,4);
    dw4_playerrecords *owner,*owner_common;dw4_property_folder *s=stage(&owner,f),*c=NULL;
    if(!s)return -1;
    c=stage(&owner_common,common);if(!c){dw4_playerrecords_close(owner);return -1;}
    int rc=dw4_property_set_number(s,"BIT",bit-amount) || dw4_property_set_array(c,"COUNTER",counters,16) ||
        dw4_property_commit_values(f,s) || dw4_property_commit_values(common,c);
    dw4_playerrecords_close(owner_common);dw4_playerrecords_close(owner);
    if(rc)return -1;
    *result=1;return 0;
}
/* CNOS (beNDMWShopCtrl40 429630): thresholds are signed compares of LEVEL. */
int32_t dw4_cnos_tier(int32_t level)
{return level<0x29?1:level<0x65?2:level<0xC9?3:level<0x12D?4:level<0x191?5:6;}
int dw4_cnos_roll(dw4_cnos_table table,void *user,int32_t tier,uint32_t draw,int32_t *record)
{
    int32_t count,ignored;
    if(!table || !record || tier<1 || tier>6 || table(user,tier*100,&count,&ignored))return -1;
    int32_t sum=0;
    for(int32_t i=1;i<=count;i++){
        int32_t id,rate;
        if(table(user,tier*100+i,&id,&rate))return -1;
        sum=(int32_t)((uint32_t)sum+(uint32_t)rate);
        if(sum>=(int32_t)draw){*record=id;return 1;} /* retail compares signed; draw < 10000 */
    }
    return 0;
}
int dw4_playertransactions_cnos_convert(dw4_playerrecords *p,int32_t slot,size_t index,
    dw4_cnos_table tables[3],void *users[3],uint32_t draw,int *result)
{
    if(result)*result=0;
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);size_t count;int32_t bit,level;
    const dw4_item_record *items=f?dw4_property_items(f,"DEVICEFOLDER",&count):NULL;
    if(!items || !tables || !users || !result || count>36 || index>=count || items[index].kind<0 || items[index].kind>2 ||
       dw4_property_number(f,"BIT",&bit) || dw4_property_number(f,"LEVEL",&level))return -1;
    int k=items[index].kind;
    if(bit<DW4_CNOS_PRICE)return 0; /* refused before anything is changed */
    dw4_item_record copy[36];if(count)memcpy(copy,items,count*sizeof *copy);
    int32_t record=copy[index].record;
    int hit=dw4_cnos_roll(tables[k],users[k],dw4_cnos_tier(level),draw%10000u,&record);
    if(hit<0)return -1;
    memcpy(&copy[index].record,&record,4);
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    int rc=dw4_property_set_number(s,"BIT",bit-DW4_CNOS_PRICE) || device_publish(s,copy,count) ||
        dw4_property_commit_values(f,s);
    dw4_playerrecords_close(owner);
    if(rc)return -1;
    *result=hit?2:1; /* 2 rerolled to a new record, 1 charged with the item unchanged */
    return 0;
}

/* ---- DIGILAB evolution (see playertransactions.h) ---- */
static int skills_for(dw4_property_folder *f,int32_t species,int32_t current,int32_t out[9])
{
    size_t n;const int32_t *v=dw4_property_array(f,species==current?"SKILL":"BASE_SKILL",&n);
    if(species<0 || species>=16 || !v || n<(species==current?9u:144u))return -1;
    memcpy(out,v+(species==current?0:species*9),9*sizeof *out);return 0;
}
static int weapon_usable(const dw4_item_record *item,int32_t species,const int32_t skills[9],dw4_item_attribute attr,void *au,int32_t *tsuyosa)
{
    int32_t soubi,skill,point;
    if(attr(au,item,"SOUBI",&soubi) || attr(au,item,"SKILL",&skill) || attr(au,item,"SKILLPOINT",&point))return -1;
    if(!dw4_weapon_eligible(species,skills,(uint32_t)soubi,skill,point))return 0;
    if(tsuyosa && attr(au,item,"TSUYOSA",tsuyosa))return -1;
    return 1;
}
int dw4_playertransactions_weapon_check(dw4_playerrecords *p,int32_t slot,int32_t species,
    dw4_item_attribute attr,void *au,int *eligible)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);size_t count=0;int32_t current,skills[9];
    if(!f || !attr || !eligible || dw4_property_item_count(f,"DEVICEFOLDER",&count) || count>36 ||
       dw4_property_number(f,"DIGIMONNO",&current) || skills_for(f,species,current,skills))return -1;
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&count);
    if(count && !items)return -1;
    *eligible=0;
    for(size_t i=0;i<count;i++){
        if(items[i].kind!=0)continue;
        int u=weapon_usable(items+i,species,skills,attr,au,NULL);
        if(u<0)return -1;
        if(u){*eligible=1;break;}
    }
    return 0;
}
static int species_row(dw4_species_model model,void *mu,const char *name)
{
    for(int32_t r=0;r<16;r++){const char *m=model(mu,r);if(m && !strcmp(m,name))return r;}
    return 0;
}
/* 3f8760 on a private copy. */
static int to_base(dw4_property_folder *s)
{
    int32_t species,level,exp;size_t n;
    if(dw4_property_number(s,"DIGIMONNO",&species) || species<0 || species>=16 ||
       dw4_property_number(s,"LEVEL",&level) || dw4_property_number(s,"EXP",&exp))return -1;
    const char *keys[]={"BASE_LEVEL","BASE_EXP","BASE_SKILL","BASE_UPCNT"};
    const size_t counts[]={16,16,144,176};int32_t arrays[4][176];
    for(unsigned k=0;k<4;k++){const int32_t *v=dw4_property_array(s,keys[k],&n);if(!v || n!=counts[k])return -1;memcpy(arrays[k],v,n*sizeof *v);}
    arrays[0][species]=level;arrays[1][species]=exp;
    const int32_t *skills=dw4_property_array(s,"SKILL",&n);if(!skills || n!=9)return -1;memcpy(arrays[2]+species*9,skills,9*sizeof *skills);
    const int32_t *up=dw4_property_array(s,"UPCNT",&n);if(!up || n!=11)return -1;memcpy(arrays[3]+species*11,up,11*sizeof *up);
    for(unsigned k=0;k<4;k++)if(dw4_property_set_array(s,keys[k],arrays[k],counts[k]))return -1;
    return 0;
}
/* 3f82a0: the species' saved level, EXP, skills and upgrade counts become current; DIGIMONNAME is its MODEL_NAME. */
static int from_base(dw4_property_folder *s,int32_t species,const char *model)
{
    size_t n;const int32_t *lv=dw4_property_array(s,"BASE_LEVEL",&n);if(!lv || n!=16 || species<0 || species>=16)return -1;
    int32_t level=lv[species];
    const int32_t *ex=dw4_property_array(s,"BASE_EXP",&n);if(!ex || n!=16)return -1;int32_t exp=ex[species];
    const int32_t *bs=dw4_property_array(s,"BASE_SKILL",&n);if(!bs || n!=144)return -1;int32_t skills[9];memcpy(skills,bs+species*9,sizeof skills);
    const int32_t *bu=dw4_property_array(s,"BASE_UPCNT",&n);if(!bu || n!=176)return -1;int32_t up[11];memcpy(up,bu+species*11,sizeof up);
    return dw4_property_set_number(s,"DIGIMONNO",species) || dw4_property_set_string(s,"DIGIMONNAME",model) ||
        dw4_property_set_number(s,"LEVEL",level) || dw4_property_set_number(s,"EXP",exp) ||
        dw4_property_set_array(s,"SKILL",skills,9) || dw4_property_set_array(s,"UPCNT",up,11)?-1:0;
}
/* GAMERAM BASE2CURRENT after a card load (3f82a0 through 3f80e0): the saved species' level, EXP, skills and upgrade counts become
 * current (DIGIMONNO is the first row whose MODEL_NAME is the record's DIGIMONNAME, else row 0), then RECALCPLAYER; one commit. */
int dw4_playertransactions_base_to_current(dw4_playerrecords *p,int32_t slot,dw4_species_model model,void *mu,
    dw4_player_recalculate recalc,void *ru)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);
    if(!f || !model || !recalc)return -1;
    const char *name=dw4_property_string(f,"DIGIMONNAME");if(!name || !*name)return -1;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    if(from_base(s,species_row(model,mu,name),name) || recalc(ru,s) || dw4_property_commit_values(f,s)){dw4_playerrecords_close(owner);return -1;}
    dw4_playerrecords_close(owner);return 0;
}
int dw4_playertransactions_evolve(dw4_playerrecords *p,int32_t slot,int32_t species,dw4_species_model model,void *mu,
    dw4_item_attribute attr,dw4_item_string str,void *iu,dw4_player_recalculate recalc,void *ru)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",slot);
    if(!f || !model || !attr || !str || !recalc || species<0 || species>=16)return -1;
    const char *name=model(mu,species);if(!name || !*name)return -1;
    dw4_playerrecords *owner;dw4_property_folder *s=stage(&owner,f);if(!s)return -1;
    size_t count;int32_t cur,skills[9];dw4_item_record copy[36];int32_t refs[5][5];int best=-1;int32_t best_t=0;
    if(to_base(s) || from_base(s,species_row(model,mu,name),name) || recalc(ru,s))goto bad;
    if(dw4_property_item_count(s,"DEVICEFOLDER",&count) || count>36 || dw4_property_number(s,"DIGIMONNO",&cur) || skills_for(s,cur,cur,skills))goto bad;
    const dw4_item_record *items=dw4_property_items(s,"DEVICEFOLDER",&count);
    if(count && !items)goto bad;
    if(count)memcpy(copy,items,count*sizeof *copy);
    for(size_t i=0;i<count;i++)if(copy[i].kind==0)copy[i].equipped=0;
    for(size_t i=0;i<count;i++){
        if(copy[i].kind!=0)continue;
        int32_t t=0;int u=weapon_usable(copy+i,cur,skills,attr,iu,&t);
        if(u<0)goto bad;
        if(u && (best<0 || best_t<t)){best=(int)i;best_t=t;}
    }
    /* 431670: every other list is emptied and its items un-equipped. */
    for(unsigned k=1;k<5;k++){
        size_t n;const int32_t *v=dw4_property_array(s,refkeys[k],&n);if(!v || n!=lengths[k])goto bad;
        for(size_t i=0;i<n;i++){if(v[i]>=0 && (size_t)v[i]<count)copy[v[i]].equipped=0;refs[k][i]=-1;}
        if(dw4_property_set_array(s,refkeys[k],refs[k],n))goto bad;
    }
    refs[0][0]=best;refs[0][1]=refs[0][2]=-1;
    if(best>=0)copy[best].equipped=1;
    if(dw4_property_set_array(s,refkeys[0],refs[0],3) || device_publish(s,copy,count))goto bad;
    {const char *weapon=best>=0?str(iu,copy+best,"MODEL"):NULL;
     if(best>=0 && (!weapon || !*weapon))goto bad;
     if(dw4_property_set_strings(s,"POWERSOCKETNAME",best>=0?&weapon:NULL,best>=0?1:0))goto bad;}
    if(recalc(ru,s) || dw4_property_commit_values(f,s))goto bad;
    dw4_playerrecords_close(owner);return 0;
bad:dw4_playerrecords_close(owner);return -1;
}
