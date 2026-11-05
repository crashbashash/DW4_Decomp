#include <string.h>
#include "dw4/fightmagic.h"
static int num(dw4_property_folder *f,const char *name,int32_t *v){return dw4_property_number(f,name,v);}
static int tcol(const dw4_fight_ctx *c,int32_t row,const char *col,int32_t *v){return dw4_dbt_number(c->tech,row,col,v)?-1:0;}
static int skill_value(dw4_property_folder *f,int32_t index,int32_t *v)
{
    size_t n=0;const int32_t *s=dw4_property_array(f,"SKILL",&n);
    if(!s || index<0 || (size_t)index>=n)return -1;
    *v=s[index];return 0;
}
static int tech_row(dw4_property_folder *p,int32_t base_no,int32_t *row)
{
    size_t n=0;const dw4_item_record *w=dw4_property_items(p,"WAZALIST",&n);
    for(size_t i=0;w && i<n;i++)if(w[i].revision==base_no){*row=w[i].record;return 0;}
    return -1;
}
int dw4_fight_attack_element(const dw4_fight_ctx *c,int32_t attack,int32_t *element)
{
    static const char *const names[5]={"fire","ice","thunder","dark","poison"};
    if(!c || !element)return -1;
    if(attack/10000!=4)return num(c->player,"ATTACKZOKUSEI",element);   /* default arm: the weapon element property */
    int32_t row;
    if(!dw4_dbtable_valid(c->tech) || tech_row(c->player,attack%10000,&row))return -1;
    const char *z=dw4_dbt_string(c->tech,row,"ZOKUSEI");
    *element=-1;
    for(int i=0;z && i<5;i++)if(!strcmp(z,names[i])){*element=i;break;}
    return 0;
}
/* Raise rows 50..54: the two words retail reads from its tables at index = row (59..95 step 9, and 100..6400, the row's HP column); the item version
 * (attack -50) reads table index 0 of a second pair, 59 and 100. */
static const int32_t raise_a[5]={59,68,77,86,95},raise_b[5]={100,400,1600,3200,6400};
int dw4_fight_p2p_magic(const dw4_fight_ctx *c,int32_t caster,int32_t target,int32_t attack,dw4_magic *out)
{
    if(!c || !out || !dw4_dbtable_valid(c->tech))return -1;
    memset(out,0,sizeof *out);
    if(caster!=target)return 0;
    int32_t base=attack%10000,row=-1,sk,s,t,kash,x;   /* C remainder: a negative attack keeps its sign (-50) */
    if(base==-50){*out=(dw4_magic){DW4_MAGIC_RAISE,-1,0,1,0,2,{raise_a[0],raise_b[0],0,0,0}};return 0;}
    switch(base){
    case 40:case 45:
        if(tech_row(c->player,base,&row) || tcol(c,row,"SKILL",&sk) || skill_value(c->player,sk,&s) || tcol(c,row,"HP",&t) || num(c->player,"KASHIKOSA",&kash))return -1;
        /* HP delta = row HP + SKILL[row SKILL] + KASHIKOSA, applied to the caster; Heal (45) also to the area */
        *out=(dw4_magic){DW4_MAGIC_HEAL,row,1,base==45,0,1,{t+s+kash,0,0,0,0}};return 0;
    case 55:case 60:
        if(tech_row(c->player,base,&row))return -1;
        *out=(dw4_magic){DW4_MAGIC_CURE,row,1,base==60,0,1,{row-base+5,0,0,0,0}};return 0;
    case 50:
        if(tech_row(c->player,base,&row) || row<50 || row>54)return -1;
        *out=(dw4_magic){DW4_MAGIC_RAISE,row,0,1,0,2,{raise_a[row-50],raise_b[row-50],0,0,0}};return 0;
    case 65:
        if(tech_row(c->player,base,&row) || tcol(c,row,"TIME",&t) || num(c->player,"KASHIKOSA",&kash) || tcol(c,row,"SKILL",&sk) || skill_value(c->player,sk,&s))return -1;
        *out=(dw4_magic){DW4_MAGIC_SPEEDUP,row,0,1,1,5,{0,0,0,0,0}};
        out->v[0]=t+kash;
        if(tcol(c,row,"SUBAYASA",&x))return -1;
        out->v[1]=s/5+x;
        if(tcol(c,row,"CHIMEIRITSU",&out->v[2]) || tcol(c,row,"MHIRITSU",&out->v[3]) || tcol(c,row,"KAIHIRITSU",&out->v[4]))return -1;
        return 0;
    case 80:
        if(tech_row(c->player,base,&row) || tcol(c,row,"TIME",&t) || num(c->player,"KASHIKOSA",&kash) || tcol(c,row,"SKILL",&sk) || skill_value(c->player,sk,&s))return -1;
        *out=(dw4_magic){DW4_MAGIC_POWERUP,row,0,1,1,4,{0,0,0,0,0}};
        out->v[0]=t+kash;
        {int32_t a,b,m;if(tcol(c,row,"TSUYOSA",&a) || tcol(c,row,"MAMORI",&b) || tcol(c,row,"MAXHP",&m))return -1;
         out->v[1]=s/5+a;out->v[2]=s/5+b;out->v[3]=s/5+m;}
        return 0;
    case 75:
        if(tech_row(c->player,base,&row))return -1;
        *out=(dw4_magic){DW4_MAGIC_REFRACT,row,0,1,1,5,{0,0,0,0,0}};
        if(tcol(c,row,"TIME",&out->v[0]) || tcol(c,row,"FIRE",&out->v[1]) || tcol(c,row,"ICE",&out->v[2]) || tcol(c,row,"THUNDER",&out->v[3]) || tcol(c,row,"DARK",&out->v[4]))return -1;
        return 0;
    }
    return 0;
}
int dw4_fight_apply_hp(dw4_property_folder *p,int32_t delta)
{
    int32_t hp,mhp;
    if(!p || num(p,"HP",&hp) || num(p,"MHP",&mhp))return -1;
    if(!hp)return 0;
    hp+=delta;if(hp<0)hp=0;if(hp>mhp)hp=mhp;
    return dw4_property_set_number(p,"HP",hp)?-1:1;
}
int dw4_fight_p2p_cure_poison(const dw4_fight_ctx *c,const dw4_magic *m,int32_t poison_endurance,int *cured)
{
    if(!c || !m || !cured || m->kind!=DW4_MAGIC_CURE)return -1;
    unsigned r=dw4_random_next(c->rng)%10;
    *cured=m->v[0]-poison_endurance>=(int32_t)r;
    return 0;
}
