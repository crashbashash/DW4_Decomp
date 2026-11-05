#include "dw4/playerhealth.h"
#include <stdio.h>
#include <string.h>
#include "eefloat.h"
int dw4_playerhealth_add(dw4_playerrecords *players,int32_t player,int mp,int32_t amount,int32_t absolute_hp,char *error,size_t cap)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);int32_t current,max,value;
    const char *key=mp?"MP":"HP";
    if(!f || dw4_property_number(f,key,&current) || dw4_property_number(f,mp?"MMP":"MHP",&max) || max<=0){
        snprintf(error,cap,"player %d %s/max unavailable",player,key);return -1;
    }
    if(!mp && absolute_hp==-1 && !current)return 0;
    value=mp || absolute_hp==-1?(int32_t)((uint32_t)current+(uint32_t)amount):absolute_hp;
    if(value<0)value=0;
    if(value>max)value=max;
    return dw4_property_set_number(f,key,value);
}
int dw4_playerhealth_restore(dw4_playerrecords *players,int32_t player,dw4_playerhealth *out,char *error,size_t cap)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);dw4_playerhealth h={0};
    int32_t use;
    if(!out || !f || dw4_property_number(f,"ISUSE",&use) || !(uint8_t)use ||
       dw4_property_number(f,"LEVEL",&h.level) || dw4_property_number(f,"HP",&h.hp) ||
       dw4_property_number(f,"MP",&h.mp) || dw4_property_number(f,"MHP",&h.max_hp) ||
       dw4_property_number(f,"MMP",&h.max_mp) || h.level<0 || h.max_hp<=0 || h.max_mp<=0){
        snprintf(error,cap,"player %d health/maxima unavailable",player);return -1;
    }
    h.hp_publish=h.hp!=0;
    if(h.hp<0)h.hp=0;
    if(h.hp>h.max_hp)h.hp=h.max_hp;
    if(h.mp<0)h.mp=0;
    if(h.mp>h.max_mp)h.mp=h.max_mp;
    ee_f32 percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(h.hp),0x42c80000),ee_f32_from_s32(h.max_hp));memcpy(&h.hp_percent,&percent,4);
    percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(h.mp),0x42c80000),ee_f32_from_s32(h.max_mp));memcpy(&h.mp_percent,&percent,4);
    /* Existing scalar properties make both replacements nonallocating. */
    if((h.hp_publish && dw4_property_set_number(f,"HP",h.hp)) || dw4_property_set_number(f,"MP",h.mp))return -1;
    *out=h;return 0;
}
