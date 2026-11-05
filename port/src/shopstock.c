#include "dw4/shopstock.h"
#include "statuswork.h"
#include <stdio.h>
#include <string.h>

void dw4_shopstock_init(dw4_shopstock *s){if(s)memset(s,0,sizeof *s);}
/* Construction is private; only complete typed stock is published. */
struct stock_build {dw4_item_record list[4][DW4_SHOPSTOCK_SLOTS];size_t count[4];int32_t gift;};
static beNDMWStatusInfoWork *stock_work(const dw4_shopstock *s)
{return s && s->work.off?DW4_ARENA_OBJ(s->arena,beNDMWStatusInfoWork,s->work):NULL;}
static int32_t *stock_field(beNDMWStatusInfoWork *w,int mode)
{switch(mode){case 6:return &w->_weaponSalesList;case 7:return &w->_armorSalesList;case 8:return &w->_chipSalesList;case 9:return &w->_junkSalesList;default:return NULL;}}
size_t dw4_shopstock_count(const dw4_shopstock *s,int32_t mode)
{beNDMWStatusInfoWork *w=stock_work(s);int32_t *f=w?stock_field(w,mode):NULL;return f?(size_t)al_count(s->arena,*f):0;}
int32_t dw4_shopstock_gift(const dw4_shopstock *s){beNDMWStatusInfoWork *w=stock_work(s);return w?w->_junkGift:0;}
dw4_handle dw4_shopstock_acquire(const dw4_shopstock *s,int32_t mode)
{beNDMWStatusInfoWork *w=stock_work(s);int32_t *f=w?stock_field(w,mode):NULL;dw4_handle h=f?al_handle(*f):(dw4_handle){0};return h.off && dw4_arena_object_addref(s->arena,h)>0?h:(dw4_handle){0};}
void dw4_shopstock_close(dw4_shopstock *s)
{if(s && s->work.off){status_work_drop(s->arena,s->work);memset(s,0,sizeof *s);}}
static int stock_fail(char *error,size_t cap,const char *what){if(error && cap)snprintf(error,cap,"shop stock: %s",what);return -1;}
unsigned dw4_shopstock_level_row(int32_t level,unsigned maximum)
{
    static const int cut[]={10,17,22,27,32,37,42,47,52,61,68,73,78,83,88,93,98,103,108,113,118,128,138,148,158,168,178,188,198};
    unsigned row=0;while(row<maximum && row<29 && level>=cut[row])row++;return row;
}
int dw4_shopstock_investment_row(int32_t value)
{
    static const int cut[]={1000,6000,26000,86000,206000,456000,956000,1956000,3956000};
    int row=-1;while(row<8 && value>=cut[row+1])row++;
    return value<cut[0]?-1:row;
}
/* 448190: the pocket count; the result of the signed compares below is 0..5 (1 when 16..31). */
int32_t dw4_shopstock_pocket_roll(uint32_t draw,uint32_t level)
{
    uint32_t tens=level/10;int32_t offset=(int32_t)((tens+10u)/10u);
    int32_t v=(int32_t)(draw%620u)+1-offset;
    if(v==1)return 5;
    if(v<4)return 4;
    if(v<8)return 3;
    if(v<16)return 2;
    if(v<32)return 1;
    return 0;
}
/* 4480a0: the enhancement (revision). `first` is the %6000 draw, `second` the %level draw. */
int32_t dw4_shopstock_revision_roll(uint32_t first,uint32_t second,uint32_t level)
{
    int32_t chance=(int32_t)(first%6000u)+1,span=(int32_t)(second%level)+1,v;
    if(chance==1)v=(int32_t)level+1;
    else if(chance<0xBB9)v=span-chance/10;
    else v=0;
    return v<0?0:v;
}
static int roll_item(dw4_item_record *out,int kind,int32_t record,uint32_t level,dw4_random *random)
{
    *out=(dw4_item_record){.kind=kind,.record=record};
    if(kind==3)return 0;
    if(!level || !random)return -1;
    if(kind<2)out->pocket=dw4_shopstock_pocket_roll(dw4_random_next(random),level);
    uint32_t first=dw4_random_next(random),second=dw4_random_next(random);
    out->revision=dw4_shopstock_revision_roll(first,second,level);
    return 0;
}
static dw4_item_record null_slot(void){return (dw4_item_record){.kind=-1};}
static int push(struct stock_build *s,unsigned list,dw4_item_record item)
{
    if(s->count[list]>=DW4_SHOPSTOCK_SLOTS)return -1;
    s->list[list][s->count[list]++]=item;return 0;
}
static int cap_player(dw4_playerrecords *p,int index)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",index);int32_t v;
    if(!f || dw4_property_number(f,"ISUSE",&v))return -1;
    if(!(uint8_t)v)return 0;
    if(dw4_property_number(f,"BIT",&v))return -1;
    if(v>9999999 && dw4_property_set_number(f,"BIT",9999999))return -1;
    if(dw4_property_number(f,"XDATA",&v))return -1;
    if(v>9999 && dw4_property_set_number(f,"XDATA",9999))return -1;
    return 1;
}
static const dw4_database *table(const dw4_databases *db,const char *name){return dw4_databases_get(db,name);}
static int build_stock(struct stock_build *s,int existing,int32_t mode,const dw4_databases *db,dw4_playerrecords *p,
    dw4_random *random,char *error,size_t cap)
{
    if(!s || !db || !p || !random || mode<6 || mode>9)return stock_fail(error,cap,"invalid request");
    int joined=0;
    for(int i=0;i<4;i++){int r=cap_player(p,i);if(r<0)return stock_fail(error,cap,"player record unavailable");joined+=r;}
    dw4_property_folder *zero=dw4_playerrecords_get(p,"GETPLAYER",0);int32_t level;
    if(!zero || dw4_property_number(zero,"LEVEL",&level) || level<1 || level>999)return stock_fail(error,cap,"player zero LEVEL unavailable");
    unsigned list=(unsigned)(mode-6);
    if(existing)return 0;
    char column[16];int32_t id;
    if(mode==9) {
        const int32_t *counter;size_t n;
        counter=dw4_property_array(dw4_playerrecords_get(p,"GETCOMMON",0),"COUNTER",&n);
        if(!counter || n<2)return stock_fail(error,cap,"common COUNTER unavailable");
        int row=dw4_shopstock_investment_row(counter[1]);
        s->gift=counter[1];
        if(row<0)return 0;
        const dw4_database *d=table(db,"shopJunk");if(!d)return stock_fail(error,cap,"shopJunk table unavailable");
        for(unsigned i=0;i<36;i++) {
            snprintf(column,sizeof column,"%02u",i);
            int r=dw4_database_number(d,row,column,&id);
            if(r<0)return stock_fail(error,cap,"shopJunk row unavailable");
            if(r || id<0)continue; /* an absent column and a stored -1 are both retail's 64-bit -1 sentinel */
            snprintf(column,sizeof column,"%02ukind",i);
            int32_t kind;dw4_item_record item;
            if(dw4_database_number(d,row,column,&kind)<0)return stock_fail(error,cap,"shopJunk kind unavailable");
            if(kind<0 || kind>2)continue;
            if(roll_item(&item,kind,id,(uint32_t)level,random) || push(s,list,item))return stock_fail(error,cap,"junk item could not be built");
        }
        return 0;
    }
    const char *name=mode==6?"shopWeapon":mode==7?"shopArmor":"shopChip";
    const dw4_database *d=table(db,name);if(!d)return stock_fail(error,cap,"shop table unavailable");
    int32_t row;
    if(mode==6) {
        int32_t base=150,species;
        if(joined<2) {
            if(dw4_property_number(zero,"DIGIMONNO",&species))return stock_fail(error,cap,"DIGIMONNO unavailable");
            switch(species) {
            case 1:case 4:case 12:base=25;break;
            case 2:case 7:case 14:base=50;break;
            case 3:case 9:base=75;break;
            case 6:case 10:base=100;break;
            case 8:case 11:case 13:base=125;break;
            default:base=0;break;
            }
        }
        row=base+(int32_t)dw4_shopstock_level_row(level,24);
    }else row=(int32_t)dw4_shopstock_level_row(level,29);
    for(unsigned i=0;i<36;i++) {
        snprintf(column,sizeof column,"%02u",i);
        int r=dw4_database_number(d,row,column,&id);
        if(r<0)return stock_fail(error,cap,"shop row unavailable");
        dw4_item_record item;
        if(r || id<0) {
            /* Retail builds blue armor even for the missing sentinel in APU columns 0..11; a table without
             * them cannot be priced, so it is refused rather than inventing a record. */
            if(mode==7 && i<12)return stock_fail(error,cap,"shopArmor lacks a blue-armor column");
            item=null_slot();
        }else if(roll_item(&item,mode==6?0:mode==7?(i<12?1:2):3,id,(uint32_t)level,random))return stock_fail(error,cap,"shop item could not be built");
        if(push(s,list,item))return stock_fail(error,cap,"stock list is full");
    }
    return 0;
}
int dw4_shopstock_prepare(dw4_shopstock *s,int32_t mode,const dw4_databases *db,dw4_playerrecords *players,dw4_random *random,char *error,size_t cap)
{
    if(!s || mode<6 || mode>9)return stock_fail(error,cap,"invalid request");
    if(!s->work.off){s->arena=dw4_session_arena();
        s->work=s->arena?status_work_new(s->arena):(dw4_handle){0};
        if(!s->work.off)return stock_fail(error,cap,"work allocation failed");}
    struct stock_build b={0};b.gift=dw4_shopstock_gift(s);int existing=dw4_shopstock_count(s,mode)>0;
    if(build_stock(&b,existing,mode,db,players,random,error,cap))return -1;
    beNDMWStatusInfoWork *work=stock_work(s);
    if(existing)return 0;
    dw4_handle items=dw4_item_list_new(s->arena,b.list[mode-6],b.count[mode-6]);
    if(!items.off)return stock_fail(error,cap,"item list allocation failed");
    beNDMWStatusInfoWork *w=stock_work(s);int32_t *field=stock_field(w,mode),old=*field;
    *field=(int32_t)items.off;w->_junkGift=b.gift;dw4_property_list_release(s->arena,al_handle(old));return 0;
}
const dw4_item_record *dw4_shopstock_list(const dw4_shopstock *s,int32_t mode,size_t *count)
{
    if(count)*count=0;
    beNDMWStatusInfoWork *w=stock_work(s);int32_t *f=w?stock_field(w,mode):NULL;
    return f?dw4_item_list_view(s->arena,al_handle(*f),count):NULL;
}
int dw4_shopstock_sell_out(dw4_shopstock *s,int32_t mode,size_t slot)
{
    beNDMWStatusInfoWork *w=stock_work(s);int32_t *f=w?stock_field(w,mode):NULL;
    dw4_item_record sold={.kind=3,.record=DW4_SHOPSTOCK_SOLD_OUT};return f?dw4_item_list_set(s->arena,al_handle(*f),slot,&sold):-1;
}
