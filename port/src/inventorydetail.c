#include "dw4/playertransactions.h"
#include <string.h>
static const char *const keys[]={"POWERSOCKETREF","POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};
static const size_t sizes[]={3,5,1,5,1};
static const dw4_item_record *disks(dw4_property_folder *f,size_t *n)
{
    const dw4_item_record *v=dw4_property_items(f,"DISKFOLDER",n);
    if(!v || *n!=12)return NULL;
    for(size_t i=0;i<*n;i++)if(v[i].kind!=4 || v[i].revision<0 || v[i].revision>9)return NULL;
    return v;
}
int dw4_playertransactions_swap_disk(dw4_playerrecords *p,int32_t player,size_t a,size_t b)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;const dw4_item_record *v=disks(f,&n);
    if(!v || a>=10 || b>=10)return -1;
    if(a==b)return 0;
    dw4_item_record out[12];memcpy(out,v,sizeof out);out[a]=v[b];out[b]=v[a];
    return dw4_property_set_items(f,"DISKFOLDER",out,12);
}
int dw4_playertransactions_give_disk(dw4_playerrecords *p,int32_t from,int32_t to,size_t index,int32_t amount,int *result)
{
    dw4_property_folder *a=dw4_playerrecords_get(p,"GETPLAYER",from),*b=dw4_playerrecords_get(p,"GETPLAYER",to);
    size_t na,nb;const dw4_item_record *va=disks(a,&na),*vb=disks(b,&nb);int32_t au,bu;
    if(!result || !va || !vb || a==b || index>=10 || amount<0 || dw4_property_number(a,"ISUSE",&au) || dw4_property_number(b,"ISUSE",&bu))return -1;
    size_t dest=0;while(dest<nb && vb[dest].record!=va[index].record)dest++;
    if(dest==nb)return -1;
    if(!(uint8_t)au || !(uint8_t)bu || !amount || amount>va[index].revision || amount>9-vb[dest].revision){*result=0;return 0;}
    dw4_playerrecords *staged=dw4_playerrecords_open();if(!staged)return -1;
    dw4_property_folder *sa=dw4_playerrecords_get(staged,"GETPLAYER",0),*sb=dw4_playerrecords_get(staged,"GETPLAYER",1);
    dw4_item_record av[12],bv[12];memcpy(av,va,sizeof av);memcpy(bv,vb,sizeof bv);av[index].revision-=amount;bv[dest].revision+=amount;
    int rc=dw4_property_set_number(sa,"ISUSE",au) || dw4_property_set_number(sb,"ISUSE",bu) ||
        dw4_property_set_items(sa,"DISKFOLDER",av,12) || dw4_property_set_items(sb,"DISKFOLDER",bv,12) || dw4_property_commit_pair(a,sa,b,sb);
    dw4_playerrecords_close(staged);if(rc)return -1;*result=1;return 0;
}
int dw4_playertransactions_give_bit(dw4_playerrecords *p,int32_t from,int32_t to,int32_t amount,int *result)
{
    dw4_property_folder *a=dw4_playerrecords_get(p,"GETPLAYER",from),*b=dw4_playerrecords_get(p,"GETPLAYER",to);
    int32_t av,bv,au,bu;
    if(!result || !a || !b || a==b || dw4_property_number(a,"BIT",&av) || dw4_property_number(b,"BIT",&bv) ||
       dw4_property_number(a,"ISUSE",&au) || dw4_property_number(b,"ISUSE",&bu) || av<0 || bv<0 || bv>9999999 || amount<0)return -1;
    if(!(uint8_t)au || !(uint8_t)bu || !amount || amount>av || amount>9999999-bv){*result=0;return 0;}
    dw4_playerrecords *staged=dw4_playerrecords_open();if(!staged)return -1;
    dw4_property_folder *sa=dw4_playerrecords_get(staged,"GETPLAYER",0),*sb=dw4_playerrecords_get(staged,"GETPLAYER",1);
    int rc=dw4_property_set_number(sa,"ISUSE",au) || dw4_property_set_number(sb,"ISUSE",bu) ||
        dw4_property_set_number(sa,"BIT",av-amount) || dw4_property_set_number(sb,"BIT",bv+amount) || dw4_property_commit_pair(a,sa,b,sb);
    dw4_playerrecords_close(staged);if(rc)return -1;*result=1;return 0;
}
static int inventory(dw4_property_folder *f,const dw4_item_record **v,size_t *n)
{
    if(!f || dw4_property_item_count(f,"DEVICEFOLDER",n) || *n>36)return -1;
    *v=dw4_property_items(f,"DEVICEFOLDER",n);return 0;
}
static int references(dw4_property_folder *f,int32_t out[5][5],size_t count)
{
    for(unsigned k=0;k<5;k++){
        size_t n;const int32_t *v=dw4_property_array(f,keys[k],&n);
        if(!v || n!=sizes[k])return -1;
        for(size_t i=0;i<n;i++){if(v[i]<-1 || (v[i]>=0 && (size_t)v[i]>=count))return -1;out[k][i]=v[i];}
    }
    return 0;
}
static int removable(dw4_property_folder *f,const dw4_item_record *v,size_t n,size_t index,int32_t refs[5][5])
{
    if(index>=n || references(f,refs,n))return -1;
    if((uint8_t)v[index].equipped)return 0;
    for(unsigned k=0;k<5;k++)for(size_t i=0;i<sizes[k];i++)if(refs[k][i]==(int32_t)index)return 0;
    return 1;
}
static int remove_staged(dw4_property_folder *f,const dw4_item_record *v,size_t n,size_t index,int32_t refs[5][5])
{
    dw4_item_record out[36];if(n)memcpy(out,v,n*sizeof *out);
    memmove(out+index,out+index+1,(n-index-1)*sizeof *out);
    if(dw4_property_set_items(f,"DEVICEFOLDER",out,n-1))return -1;
    for(unsigned k=0;k<5;k++){
        for(size_t i=0;i<sizes[k];i++)if(refs[k][i]>(int32_t)index)refs[k][i]--;
        if(dw4_property_set_array(f,keys[k],refs[k],sizes[k]))return -1;
    }
    return 0;
}
int dw4_playertransactions_remove_item(dw4_playerrecords *players,int32_t player,size_t index,int *result)
{
    dw4_property_folder *live=dw4_playerrecords_get(players,"GETPLAYER",player);const dw4_item_record *v;size_t n;
    int32_t refs[5][5];if(!result || inventory(live,&v,&n))return -1;
    int ok=removable(live,v,n,index,refs);if(ok<0)return -1;if(!ok){*result=0;return 0;}
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || remove_staged(f,v,n,index,refs) || dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
int dw4_playertransactions_give_item(dw4_playerrecords *players,int32_t from,int32_t to,size_t index,int *result)
{
    dw4_property_folder *a=dw4_playerrecords_get(players,"GETPLAYER",from),*b=dw4_playerrecords_get(players,"GETPLAYER",to);
    const dw4_item_record *va,*vb;size_t na,nb;int32_t refs[5][5],usea,useb;
    if(!result || from==to || inventory(a,&va,&na) || inventory(b,&vb,&nb) ||
       dw4_property_number(a,"ISUSE",&usea) || dw4_property_number(b,"ISUSE",&useb))return -1;
    int ok=removable(a,va,na,index,refs);if(ok<0)return -1;
    if(!ok || !(uint8_t)usea || !(uint8_t)useb || nb==36){*result=0;return 0;}
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *sa=dw4_playerrecords_get(s,"GETPLAYER",0),*sb=dw4_playerrecords_get(s,"GETPLAYER",1);
    dw4_item_record out[36];if(nb)memcpy(out,vb,nb*sizeof *out);out[nb]=va[index];
    int rc=dw4_property_copy_values(sa,a) || dw4_property_copy_values(sb,b) ||
        remove_staged(sa,va,na,index,refs) || dw4_property_set_items(sb,"DEVICEFOLDER",out,nb+1) ||
        dw4_property_commit_pair(a,sa,b,sb);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
/* Retail ShopCtrl30 item bank (428790): the bank holds 0x60 records, the inventory 0x24. */
int dw4_playertransactions_bank_item(dw4_playerrecords *players,int32_t player,int withdraw,size_t index,int *result)
{
    dw4_property_folder *live=dw4_playerrecords_get(players,"GETPLAYER",player);const dw4_item_record *v,*b;size_t n,m;
    int32_t refs[5][5];
    if(!result || (withdraw!=0 && withdraw!=1) || inventory(live,&v,&n) || dw4_property_item_count(live,"BANKDEVICE",&m) || m>96)return -1;
    b=dw4_property_items(live,"BANKDEVICE",&m);
    dw4_item_record bank[96],out[36];
    if(withdraw) {
        if(index>=m)return -1;
        if(n>=36){*result=0;return 0;}
    }else {
        int ok=removable(live,v,n,index,refs);if(ok<0)return -1;
        if(!ok || m>=96){*result=0;return 0;}
    }
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);int rc=dw4_property_copy_values(f,live);
    if(!rc && withdraw) {
        if(n)memcpy(out,v,n*sizeof *out);
        out[n]=b[index];
        memcpy(bank,b,index*sizeof *bank);
        memmove(bank+index,b+index+1,(m-index-1)*sizeof *bank);
        rc=dw4_property_set_items(f,"DEVICEFOLDER",out,n+1) || dw4_property_set_items(f,"BANKDEVICE",bank,m-1);
    }else if(!rc) {
        if(m)memcpy(bank,b,m*sizeof *bank);
        bank[m]=v[index];
        rc=remove_staged(f,v,n,index,refs) || dw4_property_set_items(f,"BANKDEVICE",bank,m+1);
    }
    if(!rc)rc=dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
/* ShopCtrl30 money bank / ShopCtrlEditBit limits: BIT and BANKBIT stay within 0..9,999,999. */
int dw4_playertransactions_bank_bit(dw4_playerrecords *players,int32_t player,int withdraw,int32_t amount,int *result)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);int32_t bit,bank;
    if(!result || (withdraw!=0 && withdraw!=1) || !f || dw4_property_number(f,"BIT",&bit) || dw4_property_number(f,"BANKBIT",&bank) ||
       bit<0 || bit>9999999 || bank<0 || bank>9999999 || amount<0)return -1;
    int32_t from=withdraw?bank:bit,to=withdraw?bit:bank;
    if(!amount || amount>from || amount>9999999-to){*result=0;return 0;}
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *g=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(g,f) || dw4_property_set_number(g,"BIT",withdraw?bit+amount:bit-amount) ||
        dw4_property_set_number(g,"BANKBIT",withdraw?bank-amount:bank+amount) || dw4_property_commit_values(f,g);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
static int special(const dw4_item_record *v)
{return (v->kind==0 && v->record==276) || (v->kind==1 && v->record==31) || (v->kind==2 && v->record==44);}
int dw4_inventory_sort_part(const dw4_item_record *v,size_t n,int chips,int32_t *order)
{
    if(n>36 || (n && (!v || !order)) || (chips!=0 && chips!=1))return -1;
    for(size_t i=0;i<n;i++)order[i]=(int32_t)i;
    /* Strict comparisons preserve the source helpers' first-equal identity. */
    for(size_t i=1;i<n;i++){
        int32_t x=order[i];size_t j=i;
        while(j && (chips?v[x].record<v[order[j-1]].record:v[x].revision>v[order[j-1]].revision)){
            order[j]=order[j-1];j--;
        }order[j]=x;
    }
    if(!chips){
        int32_t normals[36],unknown[36];size_t count=0,tail=0;
        for(size_t i=0;i<n;i++)if(!special(v+order[i]))normals[count++]=order[i];
        for(size_t i=n;i>0;i--)if(special(v+order[i-1]))unknown[tail++]=order[i-1];
        memcpy(order,normals,count*sizeof *order);memcpy(order+count,unknown,tail*sizeof *order);
    }
    return 0;
}
int dw4_playertransactions_sort_device(dw4_playerrecords *players,int32_t player)
{
    dw4_property_folder *live=dw4_playerrecords_get(players,"GETPLAYER",player);const dw4_item_record *v;size_t n;
    int32_t refs[5][5],order[36],map[36];uint8_t used[36]={0};size_t count=0;
    if(inventory(live,&v,&n) || references(live,refs,n))return -1;
    /* Power[0], its pockets, Power[1..2], Main and its pockets, Sub. */
    const int k[]={0,1,1,1,1,1,0,0,2,3,3,3,3,3,4};
    const int pos[]={0,0,1,2,3,4,1,2,0,0,1,2,3,4,0};
    for(unsigned i=0;i<15;i++)if(refs[k[i]][pos[i]]>=0){
        int32_t id=refs[k[i]][pos[i]];if(used[id])return -1;
        used[id]=1;order[count++]=id;
    }
    for(int kind=0;kind<4;kind++){
        dw4_item_record part[36];int32_t ids[36],sorted[36];size_t length=0;
        for(size_t i=0;i<n;i++)if(!used[i] && v[i].kind==kind){part[length]=v[i];ids[length++]=(int32_t)i;}
        if(dw4_inventory_sort_part(part,length,kind==3,sorted))return -1;
        for(size_t i=0;i<length;i++){int32_t id=ids[sorted[i]];used[id]=1;order[count++]=id;}
    }
    if(count!=n)return -1;
    dw4_item_record out[36];for(size_t i=0;i<n;i++){out[i]=v[order[i]];map[order[i]]=(int32_t)i;}
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || dw4_property_set_items(f,"DEVICEFOLDER",out,n);
    for(unsigned k=0;!rc && k<5;k++){
        for(size_t i=0;i<sizes[k];i++)if(refs[k][i]>=0)refs[k][i]=map[refs[k][i]];
        rc=dw4_property_set_array(f,keys[k],refs[k],sizes[k]);
    }
    if(!rc)rc=dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);return rc?-1:0;
}
/* Retail ShopCtrl50/Sell (42a2e0, 434790, 4353e0, 436ac0): BIT is credited with 32-bit signed add and
 * capped at 9,999,999 ("if (bit >= 0x989680) bit = 0x98967f"). */
static int32_t credit(int32_t bit,int32_t amount)
{
    int32_t v=(int32_t)((uint32_t)bit+(uint32_t)amount);
    return v>=10000000?9999999:v;
}
static int bit_and_disks(dw4_property_folder *f,int32_t *bit,const dw4_item_record **v)
{
    size_t n;*v=dw4_property_items(f,"DISKFOLDER",&n);
    if(!*v || n!=12)return -1;
    for(size_t i=0;i<n;i++)if((*v)[i].kind!=4 || (*v)[i].revision<0 || (*v)[i].revision>9)return -1;
    return dw4_property_number(f,"BIT",bit);
}
int dw4_playertransactions_disk_buy(dw4_playerrecords *p,int32_t player,int32_t record,int32_t quantity,int32_t price,int *result)
{
    dw4_property_folder *live=dw4_playerrecords_get(p,"GETPLAYER",player);int32_t bit;const dw4_item_record *v;
    if(!result || !live || bit_and_disks(live,&bit,&v) || quantity<1 || quantity>9 || price<0)return -1;
    size_t index=0;while(index<12 && v[index].record!=record)index++;
    if(index==12)return -1;
    int64_t total=(int64_t)price*quantity;
    if(total>bit || v[index].revision+quantity>9){*result=0;return 0;}
    dw4_item_record out[12];memcpy(out,v,sizeof out);out[index].revision+=quantity;
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || dw4_property_set_number(f,"BIT",bit-(int32_t)total) ||
        dw4_property_set_items(f,"DISKFOLDER",out,12) || dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
int dw4_playertransactions_disk_sell(dw4_playerrecords *p,int32_t player,size_t index,int32_t quantity,int32_t price,int *result)
{
    dw4_property_folder *live=dw4_playerrecords_get(p,"GETPLAYER",player);int32_t bit;const dw4_item_record *v;
    if(!result || !live || bit_and_disks(live,&bit,&v) || index>=12 || quantity<1 || price<0)return -1;
    if(quantity>v[index].revision){*result=0;return 0;}
    dw4_item_record out[12];memcpy(out,v,sizeof out);out[index].revision-=quantity;
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || dw4_property_set_number(f,"BIT",credit(bit,(int32_t)((uint32_t)price*(uint32_t)quantity))) ||
        dw4_property_set_items(f,"DISKFOLDER",out,12) || dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
/* ShopCtrlA2 (42eb80) state 8, the Booster Pack opening: the disk entry with record 10 (448050) loses one pack (a count
 * of zero stays zero, as in retail; the caller checks first), then three cards are drawn. A draw takes r=(roll%1000)*1000
 * and the first card whose running KAKURITSU*1000 sum exceeds r (the last card when none does) is marked owned in the
 * 50-byte CARDLIST (an id beyond it is not stored); the highest RARE is reported. Pack and cards are published together. */
int dw4_playertransactions_booster_open(dw4_playerrecords *p,int32_t player,const int32_t *kakuritsu,const int32_t *rare,
    size_t count,const uint32_t rolls[3],int32_t picks[3],int32_t *max_rare)
{
    dw4_property_folder *live=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n,nc;
    if(!live || !kakuritsu || !rare || !count || !rolls || !picks || !max_rare)return -1;
    const dw4_item_record *v=dw4_property_items(live,"DISKFOLDER",&n);const uint8_t *cards=dw4_property_bytes(live,"CARDLIST",&nc);
    if(!v || n!=12 || !cards || nc!=50)return -1;
    dw4_item_record out[12];memcpy(out,v,sizeof out);uint8_t owned[50];memcpy(owned,cards,sizeof owned);
    size_t pack=0;while(pack<12 && out[pack].record!=10)pack++;
    if(pack==12)return -1;
    if(out[pack].revision>0)out[pack].revision--;
    int32_t top=0;
    for(unsigned d=0;d<3;d++){
        uint32_t r=(rolls[d]%1000U)*1000U,sum=0;size_t idx=0;int found=0;
        for(size_t i=0;i<count;i++){sum+=(uint32_t)kakuritsu[i]*1000U;if(r<sum){found=1;idx=i;break;}}
        if(!found)idx=count-1;
        if(idx<50)owned[idx]=1;
        if(top<rare[idx])top=rare[idx];
        picks[d]=(int32_t)idx;
    }
    *max_rare=top;
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || dw4_property_set_items(f,"DISKFOLDER",out,12) ||
        dw4_property_set_bytes(f,"CARDLIST",owned,50) || dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);return rc?-1:0;
}
/* GAMERAM 3fca10 CTRLITEM DISK (SYSctlDiskFolder 3722c0): the entry whose record equals `record`
 * (448050) holds the count in its +0x14 word. SET adds amount saturating at nine and answers
 * false when already nine; CLR subtracts amount clamped at zero and answers false when already zero;
 * IS is "held > 0"; ISMAX is "held == 9". Only SET and CLR change the folder. */
int dw4_playertransactions_disk_folder(dw4_playerrecords *p,int32_t player,dw4_disk_operation op,int32_t record,int32_t amount,int *result)
{
    dw4_property_folder *live=dw4_playerrecords_get(p,"GETPLAYER",player);int32_t bit;const dw4_item_record *v;
    if(!result || !live || op<DW4_DISK_SET || op>DW4_DISK_ISMAX || bit_and_disks(live,&bit,&v))return -1;
    size_t index=0;while(index<12 && v[index].record!=record)index++;
    if(index==12)return -1; /* retail indexes the list with -1 here; refused natively */
    int32_t held=v[index].revision;
    if(op==DW4_DISK_IS){*result=held!=0;return 0;}
    if(op==DW4_DISK_ISMAX){*result=held==9;return 0;}
    if(amount<0)return -1;
    if((op==DW4_DISK_SET && held==9) || (op==DW4_DISK_CLR && held==0)){*result=0;return 0;}
    dw4_item_record out[12];memcpy(out,v,sizeof out);
    int32_t next=op==DW4_DISK_SET?(amount>9-held?9:held+amount):(amount>held?0:held-amount);
    out[index].revision=next;
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || dw4_property_set_items(f,"DISKFOLDER",out,12) || dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
int dw4_playertransactions_sell_item(dw4_playerrecords *p,int32_t player,size_t index,int32_t price,int *result)
{
    dw4_property_folder *live=dw4_playerrecords_get(p,"GETPLAYER",player);const dw4_item_record *v;size_t n;
    int32_t refs[5][5],bit;if(!result || price<0 || inventory(live,&v,&n) || dw4_property_number(live,"BIT",&bit))return -1;
    int ok=removable(live,v,n,index,refs);if(ok<0)return -1;if(!ok){*result=0;return 0;}
    dw4_playerrecords *s=dw4_playerrecords_open();if(!s)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(s,"GETPLAYER",0);
    int rc=dw4_property_copy_values(f,live) || remove_staged(f,v,n,index,refs) ||
        dw4_property_set_number(f,"BIT",credit(bit,price)) || dw4_property_commit_values(live,f);
    dw4_playerrecords_close(s);if(rc)return -1;*result=1;return 0;
}
