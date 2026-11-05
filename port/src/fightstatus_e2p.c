/* Enemy-to-player status rules (see include/dw4/fightstatus_e2p.h and docs/combat.md). Ported from the reviewed source of
 * beNDMWGameRam::vfunc_34 (src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp, cases 7-12 of the FIGHTCALC second switch).
 *
 * Strings resolved from the retail ELF (virtual address -> text):
 *   eneatk columns: 0x5191d0 TYPE, 0x5191f0 KOUKA, 0x519200 KOUKARANK, 0x519210 KOUKATIME, 0x519228 GEDOKU, 0x518970 MAHIRITSU
 *   enemy columns:  0x518970 MAHIRITSU, 0x5188c0 KASHIKOSA
 *   player properties: 0x518898 MHP, 0x5189a0 MAHITEIKOU, 0x5189b0 DOKUTEIKOU, 0x5188d0 SEISHIN, 0x5188d8 SUBAYASA, 0x518950 MEICHURITSU,
 *     0x5188b0 TSUYOSA, 0x5188b8 MAMORI, 0x518b78 DOWNDATA (list)
 *   KOUKA values: 0x5191f8 doku, 0x519230 sleep, 0x519238 ashidome (bind), 0x519248 freeze, 0x519250 powerdown
 *   mode strings: 0x5191b8 TIME, 0x519220 DAMAGE, 0x519228 GEDOKU */
#include "fightrecord.h"
#include <string.h>
#include "dw4/fightstatus_e2p.h"

/* Retail 0x4cf5d8 (case 11 DOWNDATA[0]), 0x4cf5e0 (case 11 [1]), 0x4cf5e8 (case 12 [4]), 0x4cf5f0 (case 12 [5]): single words that the
 * retail code only ever loads (lui at,0x4d; lw -2600/-2592/-2584/-2576(at) at 0x404564, 0x4047ac, 0x404d7c, 0x404fc4). The ELF
 * image holds 0 in all four. */
const int32_t dw4_fight_status_down_value[4]={0,0,0,0};

static int num(dw4_property_folder *f,const char *n,int32_t *v){return dw4_fight_record_number(f,n,v)?-1:0;}
static int enemy_int(const dw4_fight_e2p_ctx *c,int32_t row,const char *col,int32_t *v){return dw4_dbt_number(c->enemy,row,col,v)?-1:0;}
static int atk_int(const dw4_fight_e2p_ctx *c,int32_t attack,const char *col,int32_t *v){return dw4_dbt_number(c->eneatk,attack%10000,col,v)?-1:0;}
static unsigned draw(const dw4_fight_e2p_ctx *c,unsigned m){return dw4_random_next(c->rng)%m;}
static int kouka_is(const dw4_fight_e2p_ctx *c,int32_t attack,const char *want)
{const char *k=dw4_dbt_string(c->eneatk,attack%10000,"KOUKA");return k && !strcmp(k,want);}
static int valid(const dw4_fight_e2p_ctx *c){return c && c->player && dw4_dbtable_valid(c->enemy) && dw4_dbtable_valid(c->eneatk) && c->rng;}

/* s0 = ((enemy.KASHIKOSA * 3) / SEISHIN + 100) - SEISHIN / 40: the hit/duration scale of sleep, bind and attack/power-down. */
static int scale(const dw4_fight_e2p_ctx *c,int32_t row,int32_t *s0)
{
    int32_t kash,seishin;
    if(enemy_int(c,row,"KASHIKOSA",&kash) || num(c->player,"SEISHIN",&seishin) || !seishin)return -1;
    *s0=((int32_t)(kash*3)/seishin+100)-seishin/40;return 0;
}
/* Cases 11/12 property branches: v = clamp(KOUKARANK + ((KASHIKOSA * 150) / SEISHIN) / 100 - SEISHIN / 80, 20, 80). */
static int down_factor(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,int32_t *v)
{
    int32_t rank,kash,seishin;
    if(atk_int(c,attack,"KOUKARANK",&rank) || enemy_int(c,row,"KASHIKOSA",&kash) || num(c->player,"SEISHIN",&seishin) || !seishin)return -1;
    int32_t x=(rank+((int32_t)(kash*0x96)/seishin)/100)-seishin/80;
    *v=x<0x14?0x14:x>0x50?0x50:x;return 0;
}

int dw4_fight_e2p_status_stun(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,int32_t damage,int32_t rank,int32_t mahi_down,int32_t *out)
{
    int32_t type,s8=0,s1=0;int active=0;
    if(!valid(c) || !out || atk_int(c,attack,"TYPE",&type))return -1;
    if(type==0){
        if(rank==1 || rank==2){int32_t m;if(enemy_int(c,row,"MAHIRITSU",&m))return -1;s8=m-mahi_down;active=1;}
    }else if(type==1){
        if(atk_int(c,attack,"MAHIRITSU",&s1))return -1;
        if(s1>0)active=1;
    }else if(type==2 && (rank==1 || rank==2))active=1;
    int32_t t=0;
    if(active){
        int32_t mhp,res;
        if(num(c->player,"MHP",&mhp) || num(c->player,"MAHITEIKOU",&res) || !mhp)return -1;
        unsigned r=draw(c,100);
        int32_t sum=s1+s8,lo=(int32_t)(damage*0x32)/mhp;
        if((int32_t)r<(res+(lo+100+sum))/2)t=(res+(lo+30+sum))/4;
        if(!t)t=-1;
    }
    *out=t;return 0;
}

int dw4_fight_e2p_status_poison(const dw4_fight_e2p_ctx *c,const char *mode,int32_t attack,int32_t *out)
{
    if(!valid(c) || !mode || !out)return -1;
    if(!strcmp(mode,"TIME")){
        int32_t t=0;
        if(kouka_is(c,attack,"doku")){
            int32_t rank,res,time;
            if(atk_int(c,attack,"KOUKARANK",&rank) || num(c->player,"DOKUTEIKOU",&res))return -1;
            unsigned r=draw(c,100);
            if((int32_t)r<res+(rank*0xF+0x1E)){if(atk_int(c,attack,"KOUKATIME",&time))return -1;t=res/2+time;}
            if(!t)t=-1;
        }
        *out=t;return 0;
    }
    if(!strcmp(mode,"DAMAGE")){
        int32_t mhp,rank;
        if(num(c->player,"MHP",&mhp) || atk_int(c,attack,"KOUKARANK",&rank))return -1;
        *out=(int32_t)(mhp*rank)/100;return 0;
    }
    if(!strcmp(mode,"GEDOKU"))return atk_int(c,attack,"GEDOKU",out)?-1:0;
    return 1;
}

int dw4_fight_e2p_status_sleep(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,int32_t *out)
{
    if(!valid(c) || !out)return -1;
    int32_t t=0;
    if(kouka_is(c,attack,"sleep")){
        int32_t rank,s0,time;
        if(atk_int(c,attack,"KOUKARANK",&rank) || scale(c,row,&s0))return -1;
        unsigned r=draw(c,10000);
        if((int32_t)r<rank*5*s0){if(atk_int(c,attack,"KOUKATIME",&time))return -1;t=(int32_t)(time*s0)/100;}
        if(!t)t=-1;
    }
    *out=t;return 0;
}

int dw4_fight_e2p_status_bind(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,int32_t *out)
{
    if(!valid(c) || !out)return -1;
    int32_t t=0;
    if(kouka_is(c,attack,"ashidome")){
        int32_t rank,type,s0,time;
        if(atk_int(c,attack,"KOUKARANK",&rank) || atk_int(c,attack,"TYPE",&type))return -1;
        int hit=1;
        if(type!=2){   /* TYPE 2 binds without a roll and with the unscaled time */
            if(scale(c,row,&s0))return -1;
            unsigned r=draw(c,10000);
            if(rank*5*s0<=(int32_t)r)hit=0;
        }
        if(hit){
            if(atk_int(c,attack,"KOUKATIME",&time))return -1;
            if(type==2)t=time;
            else{if(scale(c,row,&s0))return -1;t=(int32_t)(time*s0)/100;}
        }
        if(!t)t=-1;
    }
    *out=t;return 0;
}

/* Shared body of cases 11 and 12: mode "TIME" rolls (KOUKA == `kouka`); the two property modes names[i] write DOWNDATA[slots[i]] =
 * table tables[i], recalculate, then return property * down_factor / 100. */
static int down_rule(const dw4_fight_status_ctx *s,const char *mode,int32_t row,int32_t attack,int32_t *out,const char *kouka,
                     const char *const names[2],const int slots[2],const int tables[2])
{
    const dw4_fight_e2p_ctx *c=s?s->base:NULL;
    if(!valid(c) || !mode || !out)return -1;
    if(!strcmp(mode,"TIME")){
        int32_t t=0;
        if(kouka_is(c,attack,kouka)){
            int32_t rank,s0,time;
            if(atk_int(c,attack,"KOUKARANK",&rank) || scale(c,row,&s0))return -1;
            unsigned r=draw(c,10000);
            if((int32_t)r<(int32_t)(rank*0xA0)/100*s0){if(atk_int(c,attack,"KOUKATIME",&time))return -1;t=(int32_t)(time*s0)/100;}
            if(!t)t=-1;
        }
        *out=t;return 0;
    }
    for(int i=0;i<2;i++)if(!strcmp(mode,names[i])){
        int32_t v,prop;
        if(s->apply_down && s->apply_down(s->user,slots[i],dw4_fight_status_down_value[tables[i]]))return -1;
        if(down_factor(c,row,attack,&v) || num(c->player,names[i],&prop))return -1;
        *out=(int32_t)(prop*v)/100;return 0;
    }
    return 1;
}
int dw4_fight_e2p_status_atkdown(const dw4_fight_status_ctx *s,const char *mode,int32_t row,int32_t attack,int32_t *out)
{
    static const char *const n[2]={"SUBAYASA","MEICHURITSU"};static const int slot[2]={0,1},tab[2]={0,1};
    return down_rule(s,mode,row,attack,out,"freeze",n,slot,tab);
}
int dw4_fight_e2p_status_powdown(const dw4_fight_status_ctx *s,const char *mode,int32_t row,int32_t attack,int32_t *out)
{
    static const char *const n[2]={"TSUYOSA","MAMORI"};static const int slot[2]={4,5},tab[2]={2,3};
    return down_rule(s,mode,row,attack,out,"powerdown",n,slot,tab);
}
