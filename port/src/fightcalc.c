#include "fightrecord.h"
#include <stdio.h>
#include <stdlib.h>
#include "dw4/fightcalc.h"
#include "dw4/playerstats.h"
#include <string.h>
static int num(dw4_property_folder *f,const char *name,int32_t *v){return dw4_fight_record_number(f,name,v);}
static int skill_value(dw4_property_folder *f,int32_t index,int32_t *v)
{
    size_t n=0;const int32_t *s=dw4_fight_record_array(f,"SKILL",&n);
    if(!s || index<0 || (size_t)index>=n)return -1;
    *v=s[index];return 0;
}
static int row_int(const dw4_fight_ctx *c,int32_t row,const char *col,int32_t *v){return dw4_dbt_number(c->enemy,row,col,v)?-1:0;}
static unsigned draw(const dw4_fight_ctx *c,unsigned modulus){return dw4_random_next(c->rng)%modulus;}
static int tech_element(const char *z)
{
    static const char *const names[5]={"fire","ice","thunder","dark","poison"};
    for(int i=0;z && i<5;i++)if(!strcmp(z,names[i]))return i;
    return -1;
}
static const char *const tech_res[5]={"RES_FIRE","RES_ICE","RES_THUNDER","RES_DARK","RES_POISON"};
static int weapon_hit(int32_t attack){return attack/10000!=4;}
int dw4_fight_p2e_is_hit(const dw4_fight_ctx *c,int32_t row,int32_t attack,dw4_fight_down down,int *hit)
{
    if(!c || !hit)return -1;
    if(!weapon_hit(attack)){*hit=1;return 0;}   /* case 4: techniques always connect */
    int32_t skill_no,subayasa,s,meichu,enemy_subayasa;
    if(num(c->player,"WEAPONSKILLNO",&skill_no) || num(c->player,"SUBAYASA",&subayasa) || skill_value(c->player,skill_no,&s) ||
       num(c->player,"MEICHURITSU",&meichu) || row_int(c,row,"SUBAYASA",&enemy_subayasa))return -1;
    /* rand % 10000 < MEICHURITSU * (30*SUBAYASA + 20*S + 6000) / (enemy.SUBAYASA * (100 - evasion_down) / 100) */
    int32_t divisor=(int32_t)(enemy_subayasa*(100-down.evasion_down))/100;
    if(!divisor)return -1;
    unsigned r=draw(c,10000);
    *hit=(int32_t)r<(int32_t)(meichu*(subayasa*30+s*20+0x1770))/divisor;return 0;
}
int dw4_fight_p2e_is_critical(const dw4_fight_ctx *c,int32_t row,int32_t attack,int *critical)
{
    if(!c || !critical)return -1;
    if(!weapon_hit(attack)){   /* technique: the pcTech row's own CHIMEIRITSU, scaled by the target's resistance to its element */
        int32_t trow,chance;
        if(!dw4_dbtable_valid(c->tech) || dw4_fight_record_technique(c->player,attack%1000,&trow) || dw4_dbt_number(c->tech,trow,"CHIMEIRITSU",&chance))return -1;
        int elem=tech_element(dw4_dbt_string(c->tech,trow,"ZOKUSEI"));
        if(elem>=0){
            int32_t res;if(row_int(c,row,tech_res[elem],&res))return -1;
            int32_t d=res*12/10+0x32;if(!d)return -1;
            *critical=(int32_t)draw(c,1000)<(int32_t)((chance+0x64)*(0x2710/d))/100;
        }else *critical=(int32_t)draw(c,100)<chance;
        return 0;
    }
    int32_t chance;if(num(c->player,"CHIMEIRITSU",&chance))return -1;
    *critical=(int32_t)draw(c,200)<chance;return 0;
}
int dw4_fight_p2e_damage(const dw4_fight_ctx *c,int32_t row,int32_t attack,int critical,dw4_fight_down down,dw4_fight_damage *out)
{
    if(!c || !out)return -1;
    static const char *const resist[4]={"RES_FIRE","RES_ICE","RES_THUNDER","RES_DARK"};
    int32_t skill_no,tsuyosa,s=0,mamori,element=-1,dmg=0;
    if(!weapon_hit(attack)){
        /* technique (class 4): (SKILL[tech skill]*5 + 20*(-HP column) + 10*KASHIKOSA) / target SEISHIN, scaled by (1000 - the target's resistance to the technique's element) / 1000 */
        int32_t trow,hpc,tsk,sei,kashi;
        if(!dw4_dbtable_valid(c->tech) || dw4_fight_record_technique(c->player,attack%1000,&trow) || dw4_dbt_number(c->tech,trow,"HP",&hpc) || dw4_dbt_number(c->tech,trow,"SKILL",&tsk) ||
           skill_value(c->player,tsk,&s) || row_int(c,row,"SEISHIN",&sei) || num(c->player,"KASHIKOSA",&kashi) || !sei)return -1;
        int32_t v=-hpc;
        if(v){
            dmg=(int32_t)(s*5+(v*0x14+kashi*0xA))/sei;
            if(dmg<0)dmg=0;else if(dmg>0x1869F)dmg=0x1869F;
        }
        if(dmg){
            element=tech_element(dw4_dbt_string(c->tech,trow,"ZOKUSEI"));
            int32_t res=0;if(element>=0 && row_int(c,row,tech_res[element],&res))return -1;
            dmg=(int32_t)(dmg*(0x3E8-res))/1000;
        }
    }else{
    if(num(c->player,"WEAPONSKILLNO",&skill_no) || num(c->player,"TSUYOSA",&tsuyosa) || skill_value(c->player,skill_no,&s) ||
       row_int(c,row,"MAMORI",&mamori))return -1;
    int32_t defense=mamori-down.defense_down;
    if(!defense)return -1;
    dmg=(int32_t)(tsuyosa*6+s*4)/defense;
    if(dmg<0)dmg=0;else if(dmg>0x1869F)dmg=0x1869F;
    element=-1;
    if(dmg){
        if(num(c->player,"ATTACKZOKUSEI",&element))return -1;
        if(element!=-1){
            int32_t res;
            if(element<0 || element>3 || row_int(c,row,resist[element],&res))return -1;
            /* retail adds the elemental bonus only when the resistance is below a 0..999 draw */
            if(res<(int32_t)draw(c,1000))dmg+=(int32_t)(dmg*(0x3E8-res))/1000;
        }
    }
    }
    if(dmg<0)dmg=0;else if(dmg>0x1869F)dmg=0x1869F;
    int high=0;
    if(dmg){
        if(critical){
            if(s<0x3E9)dmg+=(int32_t)(dmg*(s/20+0x1E))/100;
            else if(s<0x7D1)dmg+=(int32_t)(dmg*((s-0x3E8)/50+0x50))/100;
            else dmg+=(int32_t)(dmg*((s-0x7D0)/100+0x64))/100;
        }
        if(dmg){
            unsigned roll=dw4_random_next(c->rng)&3;
            unsigned spread=dw4_random_next(c->rng)%(unsigned)(dmg*0x19);
            static const int32_t scale[4]={950,975,1000,1025};
            dmg=(int32_t)((int32_t)spread+dmg*scale[roll])/1000;high=roll==3;
        }
        if(dmg<0)dmg=0;else if(dmg>0x1869F)dmg=0x1869F;
    }
    *out=(dw4_fight_damage){dmg,element,high};
    return 0;
}
int dw4_fight_p2e_stun_time(const dw4_fight_ctx *c,int32_t row,int32_t max_hp,int32_t damage,int32_t *time)
{
    int32_t base,res;
    if(!c || !time || max_hp<=0 || num(c->player,"MAHIRITSU",&base) || row_int(c,row,"RES_STUN",&res))return -1;
    unsigned r=draw(c,100);*time=0;
    int32_t chance=(base+(int32_t)(damage*0x32)/max_hp+0x64-res)/2;
    if((int32_t)r<chance)*time=(int32_t)((0xC8-res)*((int32_t)(damage*0x1E)/max_hp+base*3))/400;
    return 0;
}
int dw4_fight_p2e_expup(dw4_playerrecords *records,const dw4_databases *databases,int32_t row,int32_t attacker,int32_t *share)
{
    dw4_dbtable enemy=databases?dw4_databases_table(databases,"enemy"):(dw4_dbtable){0};
    int32_t players,base;
    if(!records || !dw4_dbtable_valid(enemy) || !share || dw4_fight_record_number(dw4_playerrecords_get(records,"GETCOMMON",0),"NINZU",&players) ||
       dw4_dbt_number(enemy,row,"EXP",&base))return -1;
    *share=0;
    for(int32_t i=0;i<4;i++){
        dw4_property_folder *p=dw4_playerrecords_get(records,"GETPLAYER",i);
        int32_t used,hp,level,bonus,exp,next;
        if(!p || dw4_fight_record_number(p,"ISUSE",&used) || !(uint8_t)used || dw4_fight_record_number(p,"HP",&hp) || !hp ||
           dw4_fight_record_number(p,"LEVEL",&level) || level==0x3E7)continue;
        int32_t value=base;
        if(!dw4_fight_record_number(p,"EXPRITSU",&bonus) && bonus)value=(int32_t)(value*(bonus+0x64))/100;
        int32_t split=players==2?(value*140)/3:players==3?(value*160)/4:players==4?(value*200)/5:(value*100)/2;
        if(i==attacker){split/=50;*share=split;}else split/=100;
        if(dw4_fight_record_number(p,"EXP",&exp) || dw4_fight_record_number(p,"NEXTEXP",&next))return -1;
        exp+=split;
        if(dw4_property_set_number(p,"EXP",exp))return -1;
        if(next<=exp){
            /* FUN_003fab90(index, 1) after every LEVEL+1, then HP/MP are refilled to the new maxima (vfunc_34 case 6). */
            int32_t lv=level;
            do{
                lv++;
                if(dw4_property_set_number(p,"LEVEL",lv) || dw4_playerstats_recalculate((void *)databases,p) || dw4_fight_record_number(p,"NEXTEXP",&next))return -1;
            }while(lv!=0x3E7 && exp>=next);
            int32_t mhp,mmp;
            if(dw4_fight_record_number(p,"MHP",&mhp) || dw4_fight_record_number(p,"MMP",&mmp) || dw4_property_set_number(p,"HP",mhp) || dw4_property_set_number(p,"MP",mmp))return -1;
        }
    }
    return 0;
}

/* ---- enemy-to-player rules ---- */
/* Enemy-to-player FIGHTCALC rules (GAMERAM command FIGHTCALC, FightCom E2PISHITCHECK, E2PDAMAGE, E2PDAMAGERANK), ported from the
 * reviewed source of beNDMWGameRam::vfunc_34 (src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp cases 0, 3, 4 of the FIGHTCALC
 * switch on sp494; retail 0x00401e68 E2PDAMAGE, 0x00402ec0 E2PDAMAGERANK). Compared with the retail Mammothmon reads of 2026-11-01 (check-fieldstage e2pboss, findings
 * #2984, #3021): the hit check's dependence on the player's SUBAYASA and the plain TYPE 0 damage ranges agree; the contact criticals do not fully. Every random draw uses the one engine stream (beSystem::_random, system+0x30) as `next % n`, unsigned.
 *
 * Strings resolved from the retail ELF (virtual address -> text):
 *   eneatk columns: 0x5191d0 TYPE, 0x5191d8 SEQUENCE, 0x518950 MEICHURITSU, 0x5188b0 TSUYOSA, 0x518960 CHIMEIRITSU, 0x519018 ZOKUSEI
 *   enemy columns:  0x5188d8 SUBAYASA, 0x5188b0 TSUYOSA, 0x518960 CHIMEIRITSU, 0x5188c0 KASHIKOSA
 *   player (target) properties: 0x518990 BOUGYORITSU, 0x5188d8 SUBAYASA, 0x518980 KAIHIRITSU, 0x5188b8 MAMORI, 0x5188c0 KASHIKOSA,
 *     0x5188d0 SEISHIN, 0x518898 MHP, 0x5188e8 HONOOTEIKO, 0x5188f8 KOORITEIKO, 0x518908 KAMINARITEIKO, 0x518918 YAMITEIKO
 *   ZOKUSEI values: 0x518fa8 fire, 0x518fb0 ice, 0x518fb8 thunder, 0x518fc0 dark (0x519160 poison is not tested by E2PDAMAGE)
 *   lazy fetch: 0x5194b0/0x519488 DATABASE, 0x5194a8 eneatk, 0x519480 enemy, 0x519498/0x519470 GETDATABASE
 *   E2PDAMAGERANK object property: 0x5191e8 ONE
 *   (for reference) 0x4cf360 = {RES_FIRE,RES_ICE,RES_THUNDER,RES_DARK,RES_POISON}, 0x4cf380 = {RES_FIRE,..,RES_DARK} (P2E only)
 *
 * case 0 E2PISHITCHECK  args GetInt(0)=player index, GetInt(1)=enemy row, GetInt(2)=attack (eneatk row = attack % 10000); no object.
 *   t = eneatk.TYPE. t != 0: hit. t == 0:
 *     draw#1 r1 = next % 100; if player.BOUGYORITSU > r1: miss (guarded; no second draw)
 *     else draw#2 r2 = next % 100; hit iff r2 < (eneatk.MEICHURITSU * enemy.SUBAYASA) / (player.SUBAYASA * (player.KAIHIRITSU + 100) / 100)
 *   Output: ClearBool, AppendBool(hit).
 * case 3 E2PDAMAGE  args GetInt(0)=player, GetInt(1)=enemy row, GetInt(2)=attack; GetObject(0)=the ENEMY's beNDMWMdlPEBaseInfoWork
 *   (its _downDataList first entry: [4] subtracted from enemy.TSUYOSA, [1] subtracted from enemy.CHIMEIRITSU; 0 when the list is empty).
 *   dmg = 0, element = -1; switch eneatk.TYPE:
 *   TYPE 0: dmg = clamp(((enemy.TSUYOSA - down[4]) * eneatk.TSUYOSA) / player.MAMORI)
 *     element/res from eneatk.ZOKUSEI (fire->HONOOTEIKO 0, ice->KOORITEIKO 1, thunder->KAMINARITEIKO 2, dark->YAMITEIKO 3, else res 0, -1)
 *     if res != 0: draw r = next % 1000; if res/5 <= r: dmg += res<1001 ? dmg*((1000-res)/20+50)/100 : res<5001 ? dmg*((5000-res)/80)/100 : 0
 *     if dmg != 0: c = enemy.CHIMEIRITSU - down[1]; a = eneatk.CHIMEIRITSU; draw r = next % 10000;
 *       if (100-c)*(100-a) <= r: dmg += dmg*(a/2+90)/100
 *   TYPE 1: v = eneatk.TSUYOSA; if v != 0:
 *     dmg = clamp((enemy.KASHIKOSA * v) / player.SEISHIN); element/res as above (no draw);
 *     if res != 0: dmg = res<1001 ? dmg*((1000-res)/20+50)/100 : res<4201 ? dmg*((5000-res)/80)/100 : dmg/10   (replaces, not adds)
 *     if dmg != 0 && (a = eneatk.CHIMEIRITSU) != 0: thr = res<1001 ? (1000-res)+a*100 : a*100-(res-1000)/10; draw r = next % 10000;
 *       if thr <= r: dmg += (dmg + (a/2+90))/100   (retail ADDS here, `addu s3,s3,v1` at 0x402994, unlike TYPE 0's multiply)
 *   TYPE 2: dmg = clamp((player.MHP * eneatk.TSUYOSA) / 100); element/res as above (no draw);
 *     if res != 0: res<1001: dmg += dmg*((1000-res)/20+50)/100; else res<5001: dmg += dmg*((5000-res)/80)/100; else unchanged
 *   other TYPE: dmg 0, element -1.
 *   Then clamp; if dmg != 0: roll = next & 3; spread = next % (unsigned)(dmg*25);
 *     dmg = (int)(spread + dmg*{950,975,1000,1025}[roll]) / 1000 (unsigned sum, cast to int, signed /); high = roll == 3. Clamp.
 *   clamp = [0, 0x1869F]. Output: ClearInt, AppendInt(dmg), AppendInt(element), AppendInt(high).
 * case 4 E2PDAMAGERANK  args GetInt(0)=player, GetInt(1)=attack, GetInt(2)=player HP after the hit (<= 0 -> 3), GetInt(3)=damage,
 *   GetObject(0)=an object whose +0x28 property list holds ONE (see dw4_fight_e2p_damage_rank).
 *   hp <= 0: rank 3 (no reads). Else: reads eneatk.TSUYOSA, eneatk.SEQUENCE, player.MHP (always, in that order), switch SEQUENCE:
 *     0: TSUYOSA == 0 ? -1 : (q = damage*100/MHP) < 10 ? 0 : q < 40 ? 1 : 2;  1: -1;  2: 0;  3: 2;  4: 1;  other: 0.
 *   rank == 2 and ONE flag set: rank 1. Output: ClearInt, AppendInt(rank). No draws.
 * Status cases 7-12 (stun, poison, sleep, bind, attack-down, power-down times) live in src/fightstatus_e2p.c.
 * Division by zero: retail divides without a check; the port returns -1 instead of producing the EE's undefined quotient. */
static int e2p_num(dw4_property_folder *f,const char *name,int32_t *v){return dw4_fight_record_number(f,name,v);}
static int e2p_enemy_int(const dw4_fight_e2p_ctx *c,int32_t row,const char *col,int32_t *v){return dw4_dbt_number(c->enemy,row,col,v)?-1:0;}
static int e2p_atk_int(const dw4_fight_e2p_ctx *c,int32_t attack,const char *col,int32_t *v)
{return dw4_dbt_number(c->eneatk,attack%10000,col,v)?-1:0;}
static unsigned e2p_draw(const dw4_fight_e2p_ctx *c,unsigned modulus){return dw4_random_next(c->rng)%modulus;}
static int32_t e2p_clamp(int32_t d){return d<0?0:d>0x1869F?0x1869F:d;}

int dw4_fight_e2p_is_hit(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,int *hit)
{
    int32_t type;
    if(!c || !hit || e2p_atk_int(c,attack,"TYPE",&type))return -1;
    if(type){*hit=1;return 0;}
    int32_t guard;if(e2p_num(c->player,"BOUGYORITSU",&guard))return -1;
    *hit=0;
    if(guard>(int32_t)e2p_draw(c,100))return 0;   /* guarded: no second draw */
    int32_t subayasa,kaihi,enemy_subayasa,meichu;
    if(e2p_num(c->player,"SUBAYASA",&subayasa) || e2p_num(c->player,"KAIHIRITSU",&kaihi) || e2p_enemy_int(c,row,"SUBAYASA",&enemy_subayasa) ||
       e2p_atk_int(c,attack,"MEICHURITSU",&meichu))return -1;
    int32_t divisor=(int32_t)(subayasa*(kaihi+0x64))/100;
    if(!divisor)return -1;
    unsigned r=e2p_draw(c,100);
    *hit=(int32_t)r<(int32_t)(meichu*enemy_subayasa)/divisor;return 0;
}

/* eneatk.ZOKUSEI -> the player's resistance property; res 0 and element -1 for any other string. */
static int element_resist(const dw4_fight_e2p_ctx *c,int32_t attack,int32_t *element,int32_t *res)
{
    static const char *const names[4]={"fire","ice","thunder","dark"};
    static const char *const props[4]={"HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO"};
    const char *z=dw4_dbt_string(c->eneatk,attack%10000,"ZOKUSEI");
    *res=0;
    if(!z)return 0;   /* open point: retail igStrCmp on a missing string */
    for(int i=0;i<4;i++)if(!strcmp(z,names[i])){*element=i;return e2p_num(c->player,props[i],res)?-1:0;}
    return 0;
}
int dw4_fight_e2p_damage(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,dw4_fight_e2p_down down,dw4_fight_damage *out)
{
    int32_t type,dmg=0,element=-1,res;
    if(!c || !out || e2p_atk_int(c,attack,"TYPE",&type))return -1;
    switch(type){
    case 0: {
        int32_t mamori,tsuyosa,atk_tsuyosa;
        if(e2p_num(c->player,"MAMORI",&mamori) || e2p_enemy_int(c,row,"TSUYOSA",&tsuyosa) || e2p_atk_int(c,attack,"TSUYOSA",&atk_tsuyosa) || !mamori)
            return -1;
        dmg=e2p_clamp((int32_t)((tsuyosa-down.attack_down)*atk_tsuyosa)/mamori);
        if(element_resist(c,attack,&element,&res))return -1;
        if(res){
            unsigned r=e2p_draw(c,1000);
            if(res/5<=(int32_t)r)
                dmg+=res<0x3E9?(int32_t)(dmg*((int32_t)(0x3E8-res)/20+0x32))/100:res<0x1389?(int32_t)(dmg*((int32_t)(0x1388-res)/80))/100:0;
        }
        if(dmg){
            int32_t crit,atk_crit;
            if(e2p_enemy_int(c,row,"CHIMEIRITSU",&crit) || e2p_atk_int(c,attack,"CHIMEIRITSU",&atk_crit))return -1;
            crit-=down.critical_down;
            unsigned r=e2p_draw(c,10000);
            if((0x64-crit)*(0x64-atk_crit)<=(int32_t)r)dmg+=(int32_t)(dmg*(atk_crit/2+0x5A))/100;
        }
        break; }
    case 1: {
        int32_t v,kashikosa,seishin,a;
        if(e2p_atk_int(c,attack,"TSUYOSA",&v))return -1;
        if(!v)break;
        if(e2p_enemy_int(c,row,"KASHIKOSA",&kashikosa) || e2p_num(c->player,"SEISHIN",&seishin) || !seishin)return -1;
        dmg=e2p_clamp((int32_t)(kashikosa*v)/seishin);
        if(element_resist(c,attack,&element,&res))return -1;
        if(res){
            if(res<0x3E9)dmg=(int32_t)(dmg*((int32_t)(0x3E8-res)/20+0x32))/100;
            else if(res<0x1069)dmg=(int32_t)(dmg*((int32_t)(0x1388-res)/80))/100;
            else dmg/=10;
        }
        if(dmg){
            if(e2p_atk_int(c,attack,"CHIMEIRITSU",&a))return -1;
            if(a){
                int32_t thr=res<0x3E9?(0x3E8-res)+a*0x64:a*0x64-(int32_t)(res-0x3E8)/10;
                unsigned r=e2p_draw(c,10000);
                if(thr<=(int32_t)r)dmg+=(int32_t)(dmg+(a/2+0x5A))/100;   /* retail quirk: + not * */
            }
        }
        break; }
    case 2: {
        int32_t v,mhp;
        if(e2p_atk_int(c,attack,"TSUYOSA",&v) || e2p_num(c->player,"MHP",&mhp))return -1;
        dmg=e2p_clamp((int32_t)(mhp*v)/100);
        if(element_resist(c,attack,&element,&res))return -1;
        if(res){
            if(res<0x3E9)dmg+=(int32_t)(dmg*((int32_t)(0x3E8-res)/20+0x32))/100;
            else if(res<0x1389)dmg+=(int32_t)(dmg*((int32_t)(0x1388-res)/80))/100;
        }
        break; }
    default: break;
    }
    dmg=e2p_clamp(dmg);
    int high=0;
    if(dmg){
        unsigned roll=dw4_random_next(c->rng)&3;
        unsigned spread=dw4_random_next(c->rng)%(unsigned)(dmg*0x19);
        static const int32_t scale[4]={950,975,1000,1025};
        dmg=(int32_t)(spread+(unsigned)(dmg*scale[roll]))/1000;high=roll==3;
    }
    *out=(dw4_fight_damage){e2p_clamp(dmg),element,high};
    return 0;
}

/* one_flag: retail looks up property ONE (FUN_003e9280 with type DAT_00585be0[0]) in GetObject(0)+0x28 (creating that list when
 * missing), follows +0x14 then +0xC8 to a byte list and tests count != 0 && byte[1] != 0. The caller supplies that result. */
int dw4_fight_e2p_damage_rank(const dw4_fight_e2p_ctx *c,int32_t attack,int32_t hp,int32_t damage,int one_flag,int32_t *rank)
{
    if(!c || !rank)return -1;
    int32_t r=0;
    if(hp<=0)r=3;
    else{
        int32_t tsuyosa,sequence,mhp;
        if(e2p_atk_int(c,attack,"TSUYOSA",&tsuyosa) || e2p_atk_int(c,attack,"SEQUENCE",&sequence) || e2p_num(c->player,"MHP",&mhp))return -1;
        switch(sequence){
        case 0:
            if(!tsuyosa)r=-1;
            else{
                if(!mhp)return -1;
                int32_t q=(int32_t)(damage*0x64)/mhp;
                r=q<0xA?0:q<0x28?1:2;
            }
            break;
        case 1: r=-1;break;
        case 2: r=0;break;
        case 3: r=2;break;
        case 4: r=1;break;
        default: break;
        }
    }
    if(r==2 && one_flag)r=1;
    *rank=r;return 0;
}

int dw4_fight_e2p_stun_time(const dw4_fight_e2p_ctx *c,int32_t row,int32_t attack,int32_t damage,int32_t rank,int32_t mahi_down,int32_t *time)
{
    int32_t type,s8=0,s1=0;int active=0;
    if(!c || !time || e2p_atk_int(c,attack,"TYPE",&type))return -1;
    *time=0;
    if(type==0){
        if(rank==1 || rank==2){int32_t m;if(e2p_enemy_int(c,row,"MAHIRITSU",&m))return -1;s8=m-mahi_down;active=1;}
    }else if(type==1){
        if(e2p_atk_int(c,attack,"MAHIRITSU",&s1))return -1;
        if(s1>0)active=1;
    }else if(type==2){
        if(rank==1 || rank==2)active=1;
    }
    if(active){
        int32_t mhp,res;
        if(e2p_num(c->player,"MHP",&mhp) || e2p_num(c->player,"MAHITEIKOU",&res) || mhp==0)return -1;
        unsigned r=e2p_draw(c,100);
        int32_t sum=s1+s8,lo=(int32_t)(damage*0x32)/mhp;
        if((int32_t)r<(res+(lo+100+sum))/2)*time=(res+(lo+30+sum))/4;
    }
    return 0;
}
int dw4_fight_e2p_has_effect(const dw4_fight_e2p_ctx *c,int32_t attack)
{
    const char *k=c && dw4_dbtable_valid(c->eneatk)?dw4_dbt_string(c->eneatk,attack%10000,"KOUKA"):NULL;
    return k && *k && strcmp(k,"none");   /* the table spells "no effect" as the string none */
}

/* ---- P2ESKILLUP (case 13 of FIGHTCALC; BLTcalcSkillUp) ---- */
/* Tables read from the retail image (0x4cf390 chance by level group / skill band / {normal, unused, critical}; 0x4cf590 band bounds, in 1/100000 units). */
static const int16_t skillup_chance[4][21][3]={
    {{10,5,12},{13,7,16},{16,9,21},{21,12,27},{28,15,35},{37,20,46},{48,26,60},{62,34,78},{81,44,101},{106,58,132},{132,72,165},{165,91,207},{207,113,258},{258,142,323},{323,177,404},{404,222,505},{505,278,632},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
    {{5,2,6},{6,3,8},{8,4,10},{10,6,13},{14,7,17},{18,10,23},{24,13,30},{31,17,39},{40,22,50},{53,29,66},{66,36,82},{82,45,103},{103,56,129},{129,71,161},{161,88,202},{202,111,252},{252,139,316},{316,173,395},{0,0,0},{0,0,0},{0,0,0}},
    {{2,1,3},{3,1,4},{4,2,5},{5,3,6},{7,4,8},{9,5,11},{12,7,15},{15,9,19},{20,12,25},{26,15,33},{33,19,41},{41,24,51},{51,31,64},{64,38,80},{80,48,101},{101,60,126},{126,75,158},{158,94,197},{205,123,256},{0,0,0},{0,0,0}},
    {{1,0,1},{1,0,2},{2,1,2},{2,1,3},{3,2,4},{4,2,5},{6,3,7},{7,4,9},{10,6,12},{13,7,16},{16,9,20},{20,12,25},{25,15,32},{32,19,40},{40,24,50},{50,30,63},{63,37,79},{79,47,98},{102,61,128},{128,77,160},{160,96,200}},
};
static const int16_t skillup_band[21]={1,2,3,4,5,6,7,8,9,10,20,30,100,300,500,1000,2000,3000,4000,6000,10000};
static const char *const skillup_growth[6]={"BLUNT_GROW","SLASH_GROW","STAB_GROW","BASH_GROW","SHOT_GROW","CRUSH_GROW"};
int32_t dw4_fight_skillup_cap(int32_t level){return level<0x25?level*0x1E:level<0x6C?level*0x14+0x168:level<0xE4?level*10+0x596:level*8+0x75C;}
int dw4_fight_p2e_skillup(dw4_playerrecords *records,const dw4_databases *databases,dw4_random *rng,int32_t shooter,int32_t attack,int crit,int32_t *raised)
{
    if(raised)*raised=-1;
    dw4_property_folder *p=dw4_playerrecords_get(records,"GETPLAYER",shooter);
    dw4_dbtable sh=databases?dw4_databases_table(databases,"shinka"):(dw4_dbtable){0};
    int32_t level,species,idx;size_t n=0;
    if(!p || !dw4_dbtable_valid(sh) || dw4_fight_record_number(p,"LEVEL",&level) || dw4_fight_record_number(p,"DIGIMONNO",&species))return -1;
    int cls=attack/10000,technique=cls==9 || cls==8 || cls==4;
    const int32_t *skill=dw4_fight_record_array(p,"SKILL",&n);
    if(!skill)return -1;
    if(technique){   /* the skill index is the technique row's SKILL column; the chance has no growth factor (table * 100) */
        int32_t trow;dw4_dbtable tech=dw4_databases_table(databases,"pcTech");
        if(!dw4_dbtable_valid(tech) || dw4_fight_record_technique(p,attack%10000,&trow) || dw4_dbt_number(tech,trow,"SKILL",&idx))return -1;
        if(idx<0 || (size_t)idx>=n)return -1;
    }else{
        if(dw4_fight_record_number(p,"WEAPONSKILLNO",&idx))return -1;
        if(idx<0 || (size_t)idx>=n || idx>5)return -1;
    }
    int32_t cur=skill[idx];
    if(cur>=dw4_fight_skillup_cap(level))return 0;
    int grp=level<0x25?0:level<0x6C?1:level<0xE4?2:3,band=0;
    for(;band<21;band++)if(cur<=skillup_band[band])break;
    if(band>=21)return -1;
    int32_t chance;
    if(technique)chance=skillup_chance[grp][band][crit?2:0]*100;
    else{int32_t g;if(dw4_dbt_number(sh,species,skillup_growth[idx],&g))return -1;chance=(int32_t)(skillup_chance[grp][band][crit?2:0]*g*0x1F4)/1000;}
    if(getenv("DW4_SKILL_DEBUG"))fprintf(stderr,"skillup: level %d species %d idx %d cur %d cap %d grp %d band %d table %d chance %d\n",level,species,idx,cur,dw4_fight_skillup_cap(level),grp,band,skillup_chance[grp][band][crit?2:0],chance);
    if((int32_t)(dw4_random_next(rng)%100000u)>=chance)return 0;
    int32_t next[16];if(n>16)return -1;memcpy(next,skill,n*sizeof *next);next[idx]=cur+1;
    if(dw4_property_set_array(p,"SKILL",next,n) || dw4_playerstats_recalculate((void *)databases,p))return -1;
    if(raised)*raised=idx;return 1;
}
