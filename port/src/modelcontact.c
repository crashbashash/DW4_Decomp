#include "dw4/modelcontact.h"
#include "dw4/modelai.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
static ee_f32 bits(float f){ee_f32 u;memcpy(&u,&f,4);return u;}
static float value(ee_f32 u){float f;memcpy(&f,&u,4);return f;}
/* BLTgetAttributeStr's mapping of the cached element: -1 and anything from 4 (poison) is "common", 0..3 fire, ice, thunder, dark. */
static const char *attribute_name(int32_t e)
{
    static const char *const names[5]={"common","fire","ice","thunder","dark"};
    return e>=4?names[0]:names[e+1<0?0:e+1];
}
int dw4_model_contact_call(dw4_model_contact *c,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    if(!c)return 1;
    if(!strcmp(method,"MDLgetBulletKind") || !strcmp(method,"MDLgetBulletBoxNo") || !strcmp(method,"BLTgetShootRamNo")) {
        if(n)goto invalid;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,!strcmp(method,"MDLgetBulletKind")?c->bullet_kind:
            !strcmp(method,"MDLgetBulletBoxNo")?c->bullet_box:c->shoot_ram_no,NULL,0};return 0;
    }
    if(!strcmp(method,"MDLsetDMGTurn")) {
        if(n!=1 || a[0].type!=DW4_SCRIPT_NUMBER || !isfinite(a[0].number) ||
           a[0].number<INT32_MIN || a[0].number>INT32_MAX)goto invalid;
        c->damage_turn=(int32_t)a[0].number==1;*r=(dw4_script_value){0};return 0;
    }
    if(c->fight && !strncmp(method,"BLT",3)){
        const dw4_model_fight *f=c->fight;int32_t out[3];int flag;
        if(!strcmp(method,"BLTisPlayerBullet")){
            int32_t k=c->bullet_kind;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,(k<10000?k<1000:k<60000)||(k>=80000&&k<90000),NULL,0};return 0;
        }
        if(!strcmp(method,"BLTisHitCheck") && f->is_hit){
            if(f->is_hit(f->user,c->shoot_ram_no,c->target_row,c->bullet_kind,c->receiver_status,&flag))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,flag,NULL,0};return 0;
        }
        if(!strcmp(method,"BLTisCritical") && f->is_critical){
            if(f->is_critical(f->user,c->shoot_ram_no,c->target_row,c->bullet_kind,&flag))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,flag,NULL,0};return 0;
        }
        if(!strcmp(method,"BLTgetDamageValue") && f->damage){
            if(n!=1 || a[0].type!=DW4_SCRIPT_NUMBER)goto invalid;
            if(f->damage(f->user,c->shoot_ram_no,c->target_row,c->bullet_kind,((int32_t)a[0].number&0xff)!=0,c->receiver_status,out))goto failed;
            memcpy(c->cached,out,sizeof out);*r=(dw4_script_value){DW4_SCRIPT_NUMBER,out[0],NULL,0};return 0;
        }
        if(!strcmp(method,"BLTgetDamageRank")){
            /* 374bb0: rank from cached damage / target max HP; bonus raises rank 0/1. */
            if(n!=2 || a[0].type!=DW4_SCRIPT_NUMBER || a[1].type!=DW4_SCRIPT_NUMBER)goto invalid;
            int rank;
            if((int32_t)a[0].number<=0)rank=3;
            else{
                float fraction=(float)c->cached[0]/(float)c->target_max_hp;
                rank=0;
                if(!(fraction<=0.5f))rank=2;else if(!(fraction<=0.25f))rank=1;
                if(rank==0 && c->cached[2]==1)rank=1;
                else if(rank==0 || rank==1){
                    if((int32_t)a[1].number!=0)rank+=1;
                    else{int cat=c->bullet_kind/10000;if(cat==2 || cat==3)rank+=1;}
                }
            }
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,rank,NULL,0};return 0;
        }
        if(!strcmp(method,"BLTgetAttributeStr")){
            const char *name=attribute_name(c->cached[1]);
            *r=(dw4_script_value){DW4_SCRIPT_STRING,0,name,strlen(name)};return 0;
        }
        if(!strcmp(method,"BLTgetStunTime") && f->stun_time){
            if(n!=2 || a[0].type!=DW4_SCRIPT_NUMBER)goto invalid;
            int32_t time;
            if(f->stun_time(f->user,c->shoot_ram_no,c->target_row,c->target_max_hp,(int32_t)a[0].number,&time))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,time,NULL,0};return 0;
        }
        /* P2E status times (the combat.c wrappers at 0x374de0..0x375240): each answers 0 WITHOUT calling FIGHTCALC unless the attack is a technique
         * (attack / 10000 == 4) of its own base number: poison 20, sleep 90, bind 95, attack down 70, power down 85. Poison, attack down and
         * power down take a selector string ("TIME" runs the chance draw, the others read a column); sleep and bind take none. */
        static const struct {const char *method;int base,selector;} p2e_timing[]={
            {"BLTgetPoisonTime",20,1},{"BLTgetSleepTime",90,0},{"BLTgetBindTime",95,0},{"BLTgetAttackDownTime",70,1},{"BLTgetPowerDownTime",85,1}};
        for(unsigned t=0;t<sizeof p2e_timing/sizeof *p2e_timing;t++)if(!strcmp(method,p2e_timing[t].method)){
            if(n!=(size_t)p2e_timing[t].selector || (n && (a[0].type!=DW4_SCRIPT_STRING || !a[0].string || a[0].length>=16)))goto invalid;
            if(c->bullet_kind/10000!=4 || c->bullet_kind%10000!=p2e_timing[t].base){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};return 0;}
            if(!f->p2e_status)goto failed;
            char what[16]={0};int32_t time;
            if(n){memcpy(what,a[0].string,a[0].length);what[a[0].length]=0;}
            /* An unmatched selector leaves the retail reply empty; the port refuses to guess what the script then reads. */
            if(f->p2e_status(f->user,c->shoot_ram_no,c->target_row,c->bullet_kind,method,n?what:NULL,&time))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,time,NULL,0};return 0;
        }
        if(!strcmp(method,"BLTcalcSkillUp") && f->skill_up){
            if(n!=2 || a[0].type!=DW4_SCRIPT_NUMBER || a[1].type!=DW4_SCRIPT_NUMBER)goto invalid;
            if(f->skill_up(f->user,c->shoot_ram_no,c->bullet_kind,(int32_t)a[0].number&0xff,(int32_t)a[1].number&0xff))goto failed;
            *r=(dw4_script_value){0};return 0;
        }
        if(!strcmp(method,"BLTcalcEXPUp") && f->exp_up){
            int32_t share;
            if(f->exp_up(f->user,c->shoot_ram_no,c->target_row,&share))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,share,NULL,0};return 0;
        }
    }
    if(c->fight && c->fight->e2p_is_hit && !strncmp(method,"BLP",3)){
        const dw4_model_fight *f=c->fight;int32_t out[3];int flag;
        if(!strcmp(method,"BLPisHitCheck")){
            if(f->e2p_is_hit(f->user,c->target_slot,c->source_row,c->bullet_kind,&flag))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,flag,NULL,0};return 0;
        }
        if(!strcmp(method,"BLPgetDamageValue")){
            if(f->e2p_damage(f->user,c->target_slot,c->source_row,c->bullet_kind,c->source_status,out))goto failed;
            memcpy(c->cached,out,sizeof out);*r=(dw4_script_value){DW4_SCRIPT_NUMBER,out[0],NULL,0};return 0;
        }
        if(!strcmp(method,"BLPgetDamageRank")){
            if(n!=2 || a[0].type!=DW4_SCRIPT_NUMBER || a[1].type!=DW4_SCRIPT_NUMBER)goto invalid;
            int32_t rank;
            if(f->e2p_rank(f->user,c->target_slot,c->bullet_kind,(int32_t)a[0].number,(int32_t)a[1].number,&rank))goto failed;
            if(rank==0 && c->cached[2]==1)rank=1;   /* 375730 */
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,rank,NULL,0};return 0;
        }
        if(!strcmp(method,"BLPgetStunTime") && f->e2p_stun){
            if(n!=2 || a[0].type!=DW4_SCRIPT_NUMBER || a[1].type!=DW4_SCRIPT_NUMBER)goto invalid;
            int32_t time;
            if(f->e2p_stun(f->user,c->target_slot,c->source_row,c->bullet_kind,(int32_t)a[0].number,(int32_t)a[1].number,c->source_status,&time))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,time,NULL,0};return 0;
        }
        /* E2P status times (the wrappers of api.c:451-523): they do not gate on the attack (the FIGHTCALC rules answer 0 for a row whose KOUKA does
         * not match), they only route. Sleep and bind carry (player, enemy row, attack), poison (mode, player, attack) without the row, attack and
         * power down (mode, player, row, attack); the selector of poison, attack down and power down is the script's string ("TIME", "DAMAGE", ...). */
        static const struct {const char *method;int selector;} e2p_timing[]={
            {"BLPgetPoisonTime",1},{"BLPgetSleepTime",0},{"BLPgetBindTime",0},{"BLPgetAttackDownTime",1},{"BLPgetPowerDownTime",1}};
        for(unsigned t=0;t<sizeof e2p_timing/sizeof *e2p_timing;t++)if(!strcmp(method,e2p_timing[t].method)){
            if(n!=(size_t)e2p_timing[t].selector || (n && (a[0].type!=DW4_SCRIPT_STRING || !a[0].string || a[0].length>=16)))goto invalid;
            char what[16]={0};int32_t time;
            if(n){memcpy(what,a[0].string,a[0].length);what[a[0].length]=0;}
            if(f->e2p_status){
                if(f->e2p_status(f->user,c->target_slot,c->source_row,c->bullet_kind,method,n?what:NULL,&time))goto failed;
                *r=(dw4_script_value){DW4_SCRIPT_NUMBER,time,NULL,0};return 0;
            }
            /* Without the status owner a plain attack still answers 0 and an effect row fails rather than guess. */
            if(f->e2p_has_effect && f->e2p_has_effect(f->user,c->bullet_kind))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};return 0;
        }
        /* BLPcalcKoukaMagic (asm 0x375cf0, FIGHTCALC P2PKOUKAMAGIC): the ints are MDLgetRamNo (the struck model's slot), BLTgetShootRamNo and
         * MDLgetBulletKind; the reply is the script's number (case 20 appends 1 for a self hit). The player hit chunk calls it for kinds 80000..89999. */
        if(!strcmp(method,"BLPcalcKoukaMagic")){
            int32_t result=0;
            if(n)goto invalid;
            if(!f->p2p_magic)goto failed;
            if(f->p2p_magic(f->user,c->target_slot,c->shoot_ram_no,c->bullet_kind,&result))goto failed;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,result,NULL,0};return 0;
        }
        /* BLPgetAttackZokusei (asm 0x375690, FIGHTCALC GETPATKZOKUSEI): stores the reply in the cached element (0x58a338) that BLTgetAttributeStr reads
         * and returns that string. */
        if(!strcmp(method,"BLPgetAttackZokusei") && f->attack_element){
            int32_t element;
            if(n)goto invalid;
            if(f->attack_element(f->user,c->shoot_ram_no,c->bullet_kind,&element))goto failed;
            c->cached[1]=element;
            const char *name=attribute_name(element);
            *r=(dw4_script_value){DW4_SCRIPT_STRING,0,name,strlen(name)};return 0;
        }
    }
    if(c->fight && !strcmp(method,"MDLdspDamageP")){
        if(n!=1 || a[0].type!=DW4_SCRIPT_NUMBER)goto invalid;
        if(c->fight->display_damage_player)c->fight->display_damage_player(c->fight->user,c->target_slot,(int32_t)a[0].number);
        if(c->fight->display_popup)c->fight->display_popup(c->fight->user,3,(int32_t)a[0].number,c->world+12);
        *r=(dw4_script_value){0};return 0;
    }
    if(c->fight && !strcmp(method,"MDLdspDamage")){
        if(n!=1 || a[0].type!=DW4_SCRIPT_NUMBER)goto invalid;
        if(c->fight->display_damage)c->fight->display_damage(c->fight->user,(int32_t)a[0].number);
        if(c->fight->display_popup)c->fight->display_popup(c->fight->user,0,(int32_t)a[0].number,c->world+12);
        *r=(dw4_script_value){0};return 0;
    }
    if(c->fight && !strcmp(method,"MDLdspExp")){
        if(n!=1 || a[0].type!=DW4_SCRIPT_NUMBER)goto invalid;
        if(c->fight->display_exp)c->fight->display_exp(c->fight->user,(int32_t)a[0].number);
        if(c->fight->display_popup)c->fight->display_popup(c->fight->user,1,(int32_t)a[0].number,c->world+12);
        *r=(dw4_script_value){0};return 0;
    }
    if(c->fight && !strcmp(method,"MDLisSeqName")){
        if(n!=1 || a[0].type!=DW4_SCRIPT_STRING || !a[0].string)goto invalid;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,c->sequence && !strcmp(c->sequence,a[0].string),NULL,0};return 0;
    }
    if(c->fight && !strcmp(method,"MDLgetBulletName")){
        /* MDLgetBulletName (0x4c873c table) returns table[kind / 10000]: the same global BLTisHitCheck pushes as the bullet kind. */
        static const char *const names[]={"","PCWA","PCCA","PCSA","PCMA","PCBA","PCTK","ENAT","PCMK","ENSP"};
        const char *name=c->bullet_name?c->bullet_name:"";
        if(!*name && c->bullet_kind>=0 && c->bullet_kind/10000<(int32_t)(sizeof names/sizeof *names))name=names[c->bullet_kind/10000];
        *r=(dw4_script_value){DW4_SCRIPT_STRING,0,name,strlen(name)};return 0;
    }
    int position=!strcmp(method,"MDLgetPosStr");
    if(!position && strcmp(method,"MDLgetRotStr"))return 1;
    if(n!=3)goto invalid;
    ee_f32 offset[3];
    for(unsigned i=0;i<3;i++) {
        if(a[i].type!=DW4_SCRIPT_NUMBER || !isfinite(a[i].number) || fabs(a[i].number)>3.402823466e38)goto invalid;
        offset[i]=bits((float)a[i].number);
    }
    for(unsigned i=0;i<16;i++)if(!isfinite(c->world[i]))goto invalid;
    float output[3];
    if(position)for(unsigned i=0;i<3;i++) {
        /* 190a50: two rounded products, ADDA, MADD, then translation ADD.
         * This preserves the EE order rather than a host fused dot product. */
        ee_f32 sum=ee_f32_add(ee_f32_mul(bits(c->world[i]),offset[0]),ee_f32_mul(bits(c->world[4+i]),offset[1]));
        sum=ee_f32_add(sum,ee_f32_mul(bits(c->world[8+i]),offset[2]));
        output[i]=value(ee_f32_add(bits(c->world[12+i]),sum));
    }else {
        /* 192f50 transforms original +Z without translation, then 123640
         * atan2(X,Z). Only yaw comes from the node; X/Z are caller offsets. */
        ee_f32 forward[3];
        for(unsigned i=0;i<3;i++) {
            ee_f32 sum=ee_f32_add(ee_f32_mul(bits(c->world[i]),0),ee_f32_mul(bits(c->world[4+i]),0));
            forward[i]=ee_f32_add(sum,ee_f32_mul(bits(c->world[8+i]),0x3f800000));
        }
        ee_f32 yaw=dw4_model_ai_direction(forward[0],forward[2],0);
        output[0]=value(offset[0]);output[1]=value(ee_f32_add(ee_f32_mul(yaw,0x42652ee1),offset[1]));output[2]=value(offset[2]);
    }
    for(unsigned i=0;i<3;i++)if(!isfinite(output[i]))goto invalid;
    int len=snprintf(c->result,sizeof c->result,"V<%f,%f,%f>",(double)output[0],(double)output[1],(double)output[2]);
    if(len<0 || (size_t)len>=sizeof c->result)goto invalid;
    *r=(dw4_script_value){DW4_SCRIPT_STRING,0,c->result,(size_t)len};return 0;
failed:
    snprintf(error,cap,"combat rule failed or unsupported for %s (attack %d row %d)",method,(int)c->bullet_kind,(int)c->target_row);return -1;
invalid:
    snprintf(error,cap,"invalid scoped model-contact arguments: %s",method);return -1;
}
