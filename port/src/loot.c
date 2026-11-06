#include "dw4/loot.h"
#include "dw4/shopstock.h"
#include <string.h>
/* Loot delivery rules. The item databases are reached through the caller's accessors so the rules
 * run on fixed tables in tests. */
static const char *const category_name[DW4_LOOT_CATEGORIES]={"conItem","insItem","impItem","weapon","armor1","armor2","abChip"};
/* The table at 0x4c8f30 (pairs: category string, model or NULL for "read MODEL from the record"). */
static const char *const category_model[DW4_LOOT_CATEGORIES]={NULL,NULL,"g_000key","g_000weapon","g_000armor","g_000armor","g_000access"};
/* The table at 0x4cfc10, in order. */
static const char *const model_name[DW4_LOOT_MODELS]={"g_000bit","g_000xdata1","g_000xdata2","g_000access","g_000armor",
    "g_000boost1","g_000item","g_000key","g_000penx","g_000weapon"};
int dw4_loot_category(const char *name)
{
    if(name)for(int i=0;i<DW4_LOOT_CATEGORIES;i++)if(!strcmp(name,category_name[i]))return i;
    return -1;
}
const char *dw4_loot_category_name(int c){return c>=0 && c<DW4_LOOT_CATEGORIES?category_name[c]:NULL;}
int dw4_loot_model_kind(const char *model)
{
    if(model)for(int i=0;i<DW4_LOOT_MODELS;i++)if(!strcmp(model,model_name[i]))return i;
    return -1;
}
const char *dw4_loot_model_name(int k){return k>=0 && k<DW4_LOOT_MODELS?model_name[k]:NULL;}
int dw4_loot_named(int k){return k>=DW4_LOOT_ACCESS && k<DW4_LOOT_MODELS;}   /* vfunc_36: kind < 3 clears _isNamed */
const char *dw4_loot_model(const dw4_loot_db *db,int category,int32_t record)
{
    if(category<0 || category>=DW4_LOOT_CATEGORIES)return NULL;
    if(category_model[category])return category_model[category];
    return db && db->string?db->string(db->user,category,record,"MODEL"):NULL;
}
int dw4_loot_roll(int category,int32_t record,int32_t level,dw4_random *random,dw4_item_record *out)
{
    if(!out || category<0 || category>=DW4_LOOT_CATEGORIES)return -1;
    *out=(dw4_item_record){.kind=-1,.record=record};
    switch(category){
    case DW4_LOOT_WEAPON:case DW4_LOOT_ARMOR1:case DW4_LOOT_ARMOR2:
        if(level<1 || !random)return -1;
        out->kind=category-DW4_LOOT_WEAPON;
        /* FUN_004482e0 / 448430: FUN_00448190 (pocket) then FUN_004480a0 (revision); FUN_00448580 (yellow armour): revision only. */
        if(category!=DW4_LOOT_ARMOR2)out->pocket=dw4_shopstock_pocket_roll(dw4_random_next(random),(uint32_t)level);
        {uint32_t first=dw4_random_next(random),second=dw4_random_next(random);
         out->revision=dw4_shopstock_revision_roll(first,second,(uint32_t)level);}
        return 0;
    case DW4_LOOT_CHIP:out->kind=3;return 0;   /* FUN_00448660: kind 3, record, not equipped */
    default:return 0;                           /* disk, instant and important items carry only their record */
    }
}
int dw4_loot_make(const dw4_loot_db *db,const char *category,int32_t record,int32_t level,dw4_random *random,dw4_loot_drop *out)
{
    int c=dw4_loot_category(category);
    if(!out || c<0)return -1;
    memset(out,0,sizeof *out);
    out->category=c;out->record=record;
    out->model_kind=dw4_loot_model_kind(dw4_loot_model(db,c,record));
    if(out->model_kind<0)return -1;
    return dw4_loot_roll(c,record,level,random,&out->item);
}
void dw4_loot_bit_band(int32_t level,int32_t *low,int32_t *high)
{
    static const struct {int32_t below,lo,hi;} band[]={{19,10,55},{39,55,100},{60,87,195},{94,162,350},{108,232,520},{144,340,700},{203,446,860}};
    for(unsigned i=0;i<sizeof band/sizeof *band;i++)if(level<band[i].below){*low=band[i].lo;*high=band[i].hi;return;}
    *low=566;*high=1160;
}
int32_t dw4_loot_bit_amount(int32_t level,uint32_t draw,int32_t bitritsu)
{
    int32_t lo,hi;dw4_loot_bit_band(level,&lo,&hi);
    int32_t base=lo+(int32_t)(draw%(uint32_t)(hi-lo));
    return base*(bitritsu+100)/100;
}
int dw4_loot_upcnt_index(int32_t record)
{
    static const int index[22]={2,2,3,3,0,0,0,0,4,4,5,5,6,6,7,7,8,8,9,9,10,10};
    return record>=4 && record<=25?index[record-4]:-1;
}
static int32_t dw4_loot_wrap_add(int32_t a,int32_t b){uint32_t s=(uint32_t)a+(uint32_t)b;int32_t r;memcpy(&r,&s,4);return r;}
int dw4_loot_instant(const dw4_loot_ctx *c,int32_t record,int slot,int32_t *amount)
{
    if(amount)*amount=0;
    if(!c || !c->players || slot<0 || slot>3 || record<0 || record>25)return -1;
    dw4_property_folder *rx=dw4_playerrecords_get(c->players,"GETPLAYER",slot);   /* s2: the receiving player */
    if(!rx)return -1;
    if(record==0){
        dw4_property_folder *first=dw4_playerrecords_get(c->players,"GETPLAYER",0);   /* GETPLAYER1: LEVEL and BITRITSU */
        int32_t level,ritsu,bit;
        if(!c->random || !first || dw4_property_number(first,"LEVEL",&level) || dw4_property_number(first,"BITRITSU",&ritsu) ||
           dw4_property_number(rx,"BIT",&bit))return -1;
        int32_t add=dw4_loot_bit_amount(level,dw4_random_next(c->random),ritsu);
        if(dw4_property_set_number(rx,"BIT",dw4_loot_wrap_add(bit,add)))return -1;   /* no cap here; the shops cap BIT at their next visit */
        if(amount)*amount=add;
        return 1;
    }
    int32_t up;
    if(!c->db.number || c->db.number(c->db.user,DW4_LOOT_INS,record,"UP",&up))return -1;
    if(record<=3){
        int32_t xdata;
        if(dw4_property_number(rx,"XDATA",&xdata) || dw4_property_set_number(rx,"XDATA",dw4_loot_wrap_add(xdata,up)))return -1;
        return 1;
    }
    {   /* 4..25: UPCNT[index] += UP, then RECALCPLAYER */
        int idx=dw4_loot_upcnt_index(record);size_t n;
        const int32_t *cur=dw4_property_array(rx,"UPCNT",&n);
        if(!cur || n!=11 || idx<0)return -1;
        int32_t counts[11];memcpy(counts,cur,sizeof counts);
        counts[idx]=dw4_loot_wrap_add(counts[idx],up);
        if(dw4_property_set_array(rx,"UPCNT",counts,11))return -1;
        if(c->recalculate && dw4_playertransactions_recalculate(c->players,slot,c->recalculate,c->recalculate_user))return -1;
        return 1;
    }
}
int dw4_loot_press(const dw4_loot_ctx *c,const dw4_loot_drop *d,int slot)
{
    if(!c || !c->players || !d || slot<0 || slot>3 || !dw4_loot_named(d->model_kind))return -1;
    int result=0;
    switch(d->model_kind){
    case DW4_LOOT_ACCESS:case DW4_LOOT_ARMOR:case DW4_LOOT_WEAPONMODEL:   /* kind-3 cases 0, 1, 6: DEVICEFOLDER holds at most 36 */
        if(d->item.kind<0)return -1;
        if(dw4_playertransactions_shop_buy(c->players,slot,&d->item,0,&result))return -1;
        return result?1:0;
    case DW4_LOOT_BOOST1:case DW4_LOOT_ITEM:case DW4_LOOT_PENX:   /* cases 2, 3, 5: the Disk of this record, nine at most */
        if(dw4_playertransactions_disk_folder(c->players,slot,DW4_DISK_SET,d->record,1,&result))return 0;   /* no such disk in the folder: refused */
        return result?1:0;
    case DW4_LOOT_KEY:{   /* case 4: FLAGFOLDER[record] = 1 on the common record */
        dw4_property_folder *common=dw4_playerrecords_get(c->players,"GETCOMMON",0);size_t n=0;
        const uint8_t *bytes=common?dw4_property_bytes(common,"FLAGFOLDER",&n):NULL;
        if(!bytes || n>64)return -1;
        if(d->record>=0 && (size_t)d->record<n){
            uint8_t copy[64];memcpy(copy,bytes,n);copy[d->record]=1;
            if(dw4_property_set_bytes(common,"FLAGFOLDER",copy,n))return -1;
        }
        return 1;
    }
    default:return -1;
    }
}
int dw4_loot_nearest(const float (*players)[3],const int joined[4],const float p[3],float *distance_sq)
{
    int best=-1;float bd=0;
    for(int i=0;i<4;i++){
        if(!joined[i])continue;
        float dx=p[0]-players[i][0],dy=p[1]-players[i][1],dz=p[2]-players[i][2],d=dx*dx+dy*dy+dz*dz;
        if(best<0 || d<bd){best=i;bd=d;}   /* FUN_003a5cc0 replaces the best only when strictly nearer */
    }
    if(distance_sq)*distance_sq=bd;
    return best;
}
void dw4_loot_state_reset(dw4_loot_state *s){if(s){memset(s,0,sizeof *s);s->lock[0]=s->lock[1]=s->lock[2]=s->lock[3]=-1;}}   /* labels, counters and the label hook */
void dw4_loot_state_label(dw4_loot_state *s,dw4_loot_label hook,void *user){if(s){s->label=hook;s->label_user=user;}}
int dw4_loot_effect(int32_t record,const char **panel,const char **sequence)
{
    /* The table at 0x4cfb40: record 1..25, (panel, sequence) pairs. */
    static const struct {const char *panel,*sequence;} table[25]={
        {"i_getitempnl02","SQ_X5UP"},{"i_getitempnl02","SQ_X20UP"},{"i_getitempnl02","SQ_X100UP"},
        {"i_getitempnl01","SQ_STRUP"},{"i_getitempnl01","SQ_STRUP2"},{"i_getitempnl01","SQ_DEFUP"},{"i_getitempnl01","SQ_DEFUP2"},
        {"i_getitempnl03","SQ_MHPUP"},{"i_getitempnl03","SQ_MHPUP2"},{"i_getitempnl03","SQ_MMPUP"},{"i_getitempnl03","SQ_MMPUP2"},
        {"i_getitempnl01","SQ_WISUP"},{"i_getitempnl01","SQ_WISUP2"},{"i_getitempnl01","SQ_SPIUP"},{"i_getitempnl01","SQ_SPIUP2"},
        {"i_getitempnl01","SQ_SPDUP"},{"i_getitempnl01","SQ_SPDUP2"},{"i_getitempnl01","SQ_FIREUP"},{"i_getitempnl01","SQ_FIREUP2"},
        {"i_getitempnl01","SQ_ICEUP"},{"i_getitempnl01","SQ_ICEUP2"},{"i_getitempnl01","SQ_THUNDUP"},{"i_getitempnl01","SQ_THUNDUP2"},
        {"i_getitempnl01","SQ_DARKUP"},{"i_getitempnl01","SQ_DARKUP2"}};
    if(record<1 || record>25)return -1;
    if(panel)*panel=table[record-1].panel;
    if(sequence)*sequence=table[record-1].sequence;
    return 0;
}
const char *dw4_loot_label_font(int slot)
{
    static const char *const font[4]={"font00","font01","font02","font03"};   /* the table at 0x4cfc40 */
    return slot>=0 && slot<4?font[slot]:NULL;
}
void dw4_loot_label_color(const dw4_loot_drop *d,float rgb[3])
{
    rgb[0]=rgb[1]=rgb[2]=0.9f;
    if(!d)return;
    int kind=d->category==DW4_LOOT_WEAPON?0:d->category==DW4_LOOT_ARMOR1?1:d->category==DW4_LOOT_ARMOR2?2:-1;   /* item object kind 0..2: weapon, blue and yellow armour */
    if(kind<0)return;                                                  /* chips (3) and disks / instant / important items (4..6) stay white */
    if((kind==0 && d->record==0x114) || (kind==1 && d->record==0x1F) || (kind==2 && d->record==0x2C))return;
    int v=d->item.revision;
    if(v>=1000){rgb[0]=1.0f;rgb[1]=0.0f;rgb[2]=0.9f;}
    else if(v>=501){rgb[0]=1.0f;rgb[1]=0.6f;rgb[2]=0.1f;}
    else if(v>=101){rgb[0]=0.9f;rgb[1]=0.8f;rgb[2]=0.1f;}
    else if(v>=31){rgb[0]=0.4f;rgb[1]=1.0f;rgb[2]=0.6f;}
    else if(v>0){rgb[0]=0.1f;rgb[1]=0.9f;rgb[2]=1.0f;}
}
/* beNDMWMdlItem::vfunc_45 for the labelled drop: delivers it to the player (label dropped, `picked` told) or refuses it. Returns 1 delivered, 0 refused, -1 on a record error. */
static int loot_deliver(dw4_loot_state *s,const dw4_loot_ctx *c,size_t i,dw4_loot_drop *d,int slot,dw4_loot_picked picked,void *picked_user)
{
    int rc=dw4_loot_press(c,d,slot);
    if(rc<0)return -1;
    if(rc==1){d->collected=1;s->lock[slot]=-1;s->named++;if(s->label)s->label(s->label_user,i,slot,0);if(picked)picked(picked_user,i,slot,0);}
    else s->refused++;
    return rc;
}
int dw4_loot_cross(dw4_loot_state *s,const dw4_loot_ctx *c,size_t count,dw4_loot_drop *(*at)(void *,size_t),void *at_user,int slot,dw4_loot_picked picked,void *picked_user)
{
    if(!s || !c || !at || slot<0 || slot>3)return -1;
    if(s->lock[slot]<0 || (size_t)s->lock[slot]>=count)return 0;   /* no label of this player's: no item answers the message */
    size_t i=(size_t)s->lock[slot];dw4_loot_drop *d=at(at_user,i);
    if(!d || d->collected)return 0;
    return loot_deliver(s,c,i,d,slot,picked,picked_user);
}
int dw4_loot_step(dw4_loot_state *s,const dw4_loot_ctx *c,size_t count,dw4_loot_drop *(*at)(void *,size_t),void *at_user,
    const float (*players)[3],const int joined[4],const int pressed[4],dw4_loot_picked picked,void *picked_user)
{
    if(!s || !c || !at || !players || !joined || !pressed)return -1;
    int collected=0,used[4]={0,0,0,0};
    for(int p=0;p<4;p++){   /* a label is released when its player leaves the radius (vfunc_38 state 1) */
        if(s->lock[p]<0)continue;
        dw4_loot_drop *d=(size_t)s->lock[p]<count?at(at_user,(size_t)s->lock[p]):NULL;
        float dsq=0;
        if(d && !d->collected && joined[p]){
            float dx=d->position[0]-players[p][0],dy=d->position[1]-players[p][1],dz=d->position[2]-players[p][2];dsq=dx*dx+dy*dy+dz*dz;
        }
        if(!d || d->collected || !joined[p] || !(dsq<DW4_LOOT_RADIUS_SQ)){if(s->label)s->label(s->label_user,(size_t)s->lock[p],p,0);s->lock[p]=-1;}
    }
    for(size_t i=0;i<count;i++){
        dw4_loot_drop *d=at(at_user,i);float dsq;
        if(!d || d->collected)continue;
        int near=dw4_loot_nearest(players,joined,d->position,&dsq);
        if(near<0 || !(dsq<DW4_LOOT_RADIUS_SQ))continue;
        if(!dw4_loot_named(d->model_kind)){
            if(d->category!=DW4_LOOT_INS)continue;
            int32_t bit=0;int rc=dw4_loot_instant(c,d->record,near,&bit);
            if(rc<0)return -1;
            if(rc==1){d->collected=1;collected++;s->unnamed++;if(picked)picked(picked_user,i,near,bit);}
            continue;
        }
        if(s->lock[near]<0){s->lock[near]=(int)i;if(s->label)s->label(s->label_user,i,near,1);}
        if(s->lock[near]==(int)i && pressed[near] && !used[near]){
            used[near]=1;   /* one Cross press is one DROPITEM message: it delivers (or is refused by) the labelled drop only */
            int rc=loot_deliver(s,c,i,d,near,picked,picked_user);
            if(rc<0)return -1;
            collected+=rc;
        }
    }
    return collected;
}
