#include "fightrecord.h"
#include <string.h>
#include "dw4/fightstatus.h"
/* The technique row and the player's SKILL[pcTech.SKILL] value. */
static int tech_skill(const dw4_fight_ctx *c,int32_t attack,int32_t *trow,int32_t *s)
{
    int32_t idx;size_t n=0;
    if(!dw4_dbtable_valid(c->tech) || !dw4_dbtable_valid(c->enemy) || dw4_fight_record_technique(c->player,attack%10000,trow) || dw4_dbt_number(c->tech,*trow,"SKILL",&idx))return -1;
    const int32_t *sk=dw4_fight_record_array(c->player,"SKILL",&n);
    if(!sk || idx<0 || (size_t)idx>=n)return -1;
    *s=sk[idx];return 0;
}
/* Skill bands: s<1001: s/4 + b0; s<2001: (s-1000)/5 + b1; else (s-2000)/10 + b2. */
static int32_t band(int32_t s,int32_t b0,int32_t b1,int32_t b2)
{
    if(s<0x3E9)return s/4+b0;
    if(s<0x7D1)return (s-0x3E8)/5+b1;
    return (s-0x7D0)/10+b2;
}
/* The shared tail: one draw % 1000 against `chance`; on success pcTech.TIME + KASHIKOSA/2 (0 becomes -1), else -1. */
static int roll_time(const dw4_fight_ctx *c,int32_t trow,int32_t chance,int32_t *out)
{
    int32_t v=0;
    if((int32_t)(dw4_random_next(c->rng)%1000u)<chance){
        int32_t kashi,t;
        if(dw4_fight_record_number(c->player,"KASHIKOSA",&kashi) || dw4_dbt_number(c->tech,trow,"TIME",&t))return -1;
        v=t+kashi/2;
    }
    *out=v?v:-1;return 0;
}
/* Sleep / bind / attack-down TIME / power-down TIME: chance = band(s,550,800,1000)*100 / enemy.SEISHIN. */
static int timed(const dw4_fight_ctx *c,int32_t row,int32_t attack,int32_t *out)
{
    int32_t trow,s,sei;
    if(!c || !out || tech_skill(c,attack,&trow,&s) || dw4_dbt_number(c->enemy,row,"SEISHIN",&sei) || !sei)return -1;
    return roll_time(c,trow,band(s,0x226,0x320,0x3E8)*0x64/sei,out);
}
int dw4_fight_p2e_sleep_time(const dw4_fight_ctx *c,int32_t row,int32_t attack,int32_t *out){return timed(c,row,attack,out);}
int dw4_fight_p2e_bind_time(const dw4_fight_ctx *c,int32_t row,int32_t attack,int32_t *out){return timed(c,row,attack,out);}
int dw4_fight_p2e_poison_time(const dw4_fight_ctx *c,int32_t row,int32_t attack,const char *what,int32_t *out)
{
    int32_t trow,s,res;
    if(!c || !what || !out || !dw4_dbtable_valid(c->tech) || !dw4_dbtable_valid(c->enemy))return -1;
    if(strcmp(what,"TIME")){   /* damage per tick: -(pcTech.HP / 5) */
        int32_t hp;
        if(dw4_fight_record_technique(c->player,attack%10000,&trow) || dw4_dbt_number(c->tech,trow,"HP",&hp))return -1;
        *out=-(hp/5);return 0;
    }
    if(tech_skill(c,attack,&trow,&s) || dw4_dbt_number(c->enemy,row,"RES_POISON",&res))return -1;
    /* chance per 1000 = band(s,750,1000,1200) * (1000 - RES_POISON) / 1000 */
    return roll_time(c,trow,band(s,0x2EE,0x3E8,0x4B0)*(0x3E8-res)/1000,out);
}
/* Strength reply: -max(pcTech[col] - SKILL/20, -(enemy[col] * 80 / 100)); no draw. */
static int strength(const dw4_fight_ctx *c,int32_t row,int32_t attack,const char *col,int32_t *out)
{
    int32_t trow,s,e,t;
    if(tech_skill(c,attack,&trow,&s) || dw4_dbt_number(c->enemy,row,col,&e) || dw4_dbt_number(c->tech,trow,col,&t))return -1;
    int32_t floor_=-e*0x50/100,v=t-s/20;
    if(v<floor_)v=floor_;
    *out=-v;return 0;
}
/* Flat reply: -pcTech[col]; no draw. */
static int flat(const dw4_fight_ctx *c,int32_t attack,const char *col,int32_t *out)
{
    int32_t trow,t;
    if(dw4_fight_record_technique(c->player,attack%10000,&trow) || dw4_dbt_number(c->tech,trow,col,&t))return -1;
    *out=-t;return 0;
}
int dw4_fight_p2e_atkdwn_time(const dw4_fight_ctx *c,int32_t row,int32_t attack,const char *what,int32_t *out)
{
    if(!c || !what || !out || !dw4_dbtable_valid(c->tech) || !dw4_dbtable_valid(c->enemy))return -1;
    if(!strcmp(what,"TIME"))return timed(c,row,attack,out);
    if(!strcmp(what,"SUBAYASA"))return strength(c,row,attack,"SUBAYASA",out);
    if(!strcmp(what,"CHIMEIRITSU"))return flat(c,attack,"CHIMEIRITSU",out);
    if(!strcmp(what,"MAHIRITSU"))return flat(c,attack,"MHIRITSU",out);   /* the pcTech column is spelled MHIRITSU */
    if(!strcmp(what,"KAIHIRITSU"))return flat(c,attack,"KAIHIRITSU",out);
    return 1;
}
int dw4_fight_p2e_powdwn_time(const dw4_fight_ctx *c,int32_t row,int32_t attack,const char *what,int32_t *out)
{
    if(!c || !what || !out || !dw4_dbtable_valid(c->tech) || !dw4_dbtable_valid(c->enemy))return -1;
    if(!strcmp(what,"TIME"))return timed(c,row,attack,out);
    if(!strcmp(what,"TSUYOSA"))return strength(c,row,attack,"TSUYOSA",out);
    if(!strcmp(what,"MAMORI"))return strength(c,row,attack,"MAMORI",out);
    return 1;
}
