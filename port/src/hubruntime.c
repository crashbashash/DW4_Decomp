#include "dw4/playertransactions.h"
#include "dw4/hubruntime.h"
#include "dw4/options.h"
#include "dw4/fieldhud.h"
#include "dw4/playerstats.h"
#include "dw4/xdatashop.h"
#include "dw4/shoproot.h"
#include "dw4/bankshop.h"
#include "dw4/cnosshop.h"
#include "dw4/diskshop.h"
#include "dw4/equipshop.h"
#include "dw4/laboshop.h"
#include "dw4/savescene.h"
#include "dw4/memcard.h"
#include "dw4/frontaudio.h"
#include "dw4/filelist.h"
#include "dw4/database.h"
#include "dw4/playerhealth.h"
#include "dw4/magicapply.h"
#include "dw4/modelview.h"
#include "dw4/statusmenu.h"
#include "dw4/statusscene.h"
#include "dw4/statusui.h"
#include "dw4/padrepeat.h"
#include "dw4/evodemo.h"
#include <stdlib.h>
#include <math.h>
#include "dw4/fieldgen.h"
#include "dw4/loot.h"
#include "dw4/combat.h"
#include "dw4/technique.h"
#include "eefloat.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
struct hub_window {struct dw4_hubruntime *hub;const char *name;uint64_t token;};
struct dw4_hubruntime {
    unsigned pickups;
    dw4_hubruntime_loot lootfx;struct {int drop,dim;uint64_t due_ns;} label[4];dw4_modelctrl *loot_party[4];   /* drop presentation: counters, each player's label (drop index, dimmed colour phase, next colour change) and the party models of the tick */
    dw4_loot_state loot;size_t loot_drops;int cross[4];   /* loot labels per player, the drop count of the last tick, and the Cross presses (all pads) since the last tick */
    char boss_name[24];int32_t boss_slot;   /* METERCTRL bshp10 SETMODELHP <model>/I<slot>: the gauge follows that model's HP */
    dw4_fieldhud *fhud;   /* a field world's HP/MP gauges (hpmt1..4, mpmt1..4) */
    int party_hud;   /* a hub party: the per-slot panels are drawn by the model view (fieldhud), not by the lobby HUD */
    unsigned ninzu;   /* joined players: 1 outside the field worlds, 1..4 in a dungeon or field stage (local co-op) */
    /* One repeat tracker pair and the status-page words per pad (index = player slot; slot 0 takes the main input, slots 1..3 dw4_hubruntime_input_slot). */
    struct hub_pad {dw4_padrepeat analog,digital;dw4_statuspage_input status;} pad[4];
    int32_t owner;   /* the slot whose pad drives the running STATUS/shop (the SUBWND payload's I<player>); only that pad reaches the menu */
    dw4_mount *mount;dw4_be_state state;dw4_playerrecords *players;
    dw4_scriptengine *scripts;dw4_scriptservices *sd;dw4_filelist *files;
    dw4_stageobjects *objects;dw4_controllers *models;dw4_dialogue *dialogue;
    int32_t shop_mode;dw4_databases *databases;dw4_shopstock stock;dw4_lobby *world;dw4_modelview *ui,*status_ui;
    dw4_statusscene status_scene;dw4_statusstats status_stats;
    int64_t frozen_ns,freeze_from;   /* a field world's game clock stops while its STATUS menu is open: the time spent there, and when the current stay began (0 when none) */
    dw4_lobby_control_state held_world;dw4_lobby_presentation_state held_presentation;
    dw4_stageinput input;dw4_stagetravel travel;
    struct hub_window window[5];int field;char stage[16];unsigned field_sounds;dw4_fieldgen *gen;dw4_combat *combat;dw4_technique *tech;unsigned hitland_missing;int gameover_started,dead_restarted;uint64_t attack_ready_ns;dw4_hubruntime_hud hud;dw4_hubruntime_popups popups;uint64_t ticks,origin_ns,now_ns;int light_hard;
    /* stagIS12 (save screen) runs as a scene host inside the same runtime: no lobby, the exit becomes a pending travel. */
    dw4_savescene *scene;dw4_memcard *card;dw4_frontaudio *audio_keep;
    /* stagML14 (the digivolution demo) runs as a scene host as well: its exit is the script's own pending travel. */
    dw4_evodemo *demo;
    char error[512];
};
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int health_fields(const char *v,int32_t fields[4])
{
    int count=0;
    while(v && *v && count<4) {
        if(v[0]!='I' || v[1]!='<')return -1;
        const char *start=v+2;char *end;errno=0;long value=strtol(start,&end,10);
        if(end==start || *end!='>' || errno || value<INT32_MIN || value>INT32_MAX)return -1;
        fields[count++]=(int32_t)value;v=end+1;
        if(!*v)break;
        if(*v++!='/')return -1;
    }
    return *v || count<2?-1:count;
}
static int gameram(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_hubruntime *h=user;
    if(n>=4 && a[3].type==DW4_SCRIPT_STRING && (!strcmp(a[3].string,"ADDHP") || !strcmp(a[3].string,"ADDMP"))) {
        int32_t values[4]={0,0,0,-1};int fields;
        if(strcmp(method,"sd") || n!=5 || a[4].type!=DW4_SCRIPT_STRING || !a[4].string || strlen(a[4].string)!=a[4].length ||
           (fields=health_fields(a[4].string,values))<0 || values[0]<0 || values[0]>=(int32_t)(h->ninzu?h->ninzu:1) || (!strcmp(a[3].string,"ADDMP") && fields==4)) {
            snprintf(error,cap,"hub health command requires a joined player index and supported fields");return -1;
        }
        if(dw4_playerhealth_add(h->players,values[0],!strcmp(a[3].string,"ADDMP"),values[1],values[3],error,cap))return -1;
        dw4_playerhealth health;
        if(dw4_playerhealth_restore(h->players,values[0],&health,error,cap) || (!h->field && dw4_lobby_health_publish(h->world,&health)))return -1;   /* a field world has no HUD models to publish to */
        *r=(dw4_script_value){0};return 0;
    }
    if(n>=4 && a[3].type==DW4_SCRIPT_STRING && !strcmp(a[3].string,"RECALCPLAYER")) {
        /* 3fcb80: player index, then an optional bool that defaults to true (equipment on). */
        int equipment=1;
        if(strcmp(method,"sd") || n>5 || a[2].type!=DW4_SCRIPT_NUMBER || a[2].number<0 || a[2].number>3 ||
           (n==5 && (a[4].type!=DW4_SCRIPT_STRING || !a[4].string ||
                     (strcmp(a[4].string,"FALSE") && strcmp(a[4].string,"TRUE"))))) {
            snprintf(error,cap,"RECALCPLAYER requires a player index and an optional TRUE/FALSE");return -1;
        }
        if(n==5)equipment=strcmp(a[4].string,"FALSE")!=0;
        if(dw4_playertransactions_recalculate(h->players,(int32_t)a[2].number,
               equipment?dw4_playerstats_recalculate:dw4_playerstats_recalculate_base,(void *)h->databases)) {
            snprintf(error,cap,"RECALCPLAYER failed for player %d",(int)a[2].number);return -1;
        }
        *r=(dw4_script_value){0};return 0;
    }
    return dw4_playerrecords_service(h->players,method,a,n,r,error,cap);
}
static int sound(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_hubruntime *h=user;int rc=dw4_lobby_sound_service(h->world,method,a,n,r,error,cap);
    /* Field stages name events of banks the front-end audio adapter does not load yet. Count them
     * and play nothing; stage audio is not claimed. */
    if(rc && h->field){h->field_sounds++;error[0]=0;*r=(dw4_script_value){0};return 0;}
    return rc;
}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_hubruntime *h=user;int rc=dw4_playerrecords_call(h->players,method,a,n,r,error,cap);if(rc>0)rc=dw4_playertransactions_folder_call(h->players,method,a,n,r,error,cap);if(rc<=0)return rc;
    rc=dw4_lobby_material_call(h->world,method,a,n,r,error,cap);if(rc<=0)return rc;
    if(!strcmp(method,"PLAYERgetPos") && !n){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,h->travel.generate_pos,NULL,0};return 0;}
    if(!strcmp(method,"PLAYERgetDataStr") && n==3 && a[0].type==DW4_SCRIPT_NUMBER && a[1].type==DW4_SCRIPT_NUMBER){
        static char text[96];
        if(dw4_lobby_point_string(h->world,(int)a[0].number,(int)a[1].number,text,sizeof text)){snprintf(error,cap,"PLAYERgetDataStr: no arrival point group %d player %d",(int)a[0].number,(int)a[1].number);return -1;}
        *r=(dw4_script_value){DW4_SCRIPT_STRING,0,text,strlen(text)};return 0;
    }
    /* 0x00371e10 reads the options object's camera property exactly as SYSgetLightMode (0x00371e70) reads the light one; the front-end Options row
     * stores both as 0/1 (Near/Far, Soft/Hard), and the light value is retail-checked, so the Dungeon camera option is the answer. */
    if(!strcmp(method,"SYSgetCameraMode") && !n){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,dw4_options_get()->camera_far?1:0,NULL,0};return 0;}
    if(!strcmp(method,"SYSgetLightMode") && !n){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,h->light_hard,NULL,0};return 0;}
    if(!strcmp(method,"MDLisLive") && n==2) {
        dw4_script_value args[]={str("MODELCTRL"),a[0],a[1],str("ISRUN")};
        return dw4_scriptservices_any(h->sd,args,4,r,error,cap);
    }
    if(!strcmp(method,"MDLisStatus") && n==3 && a[2].type==DW4_SCRIPT_STRING) {
        /* A message to MODELCTRL <name> <ram> CHECKSTATUS <status> (the first answer is the reply; no receiver means nothing is set). */
        dw4_script_value args[]={str("MODELCTRL"),a[0],a[1],str("CHECKSTATUS"),a[2]};
        int rc=dw4_scriptservices_call(h->sd,"querySD",args,5,r,error,cap);
        if(!rc && r->type!=DW4_SCRIPT_NUMBER)*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
        return rc;
    }
    dw4_scriptservices_scope(h->sd,dw4_scriptengine_scope(h->scripts));
    return dw4_scriptservices_call(h->sd,method,a,n,r,error,cap);
}
/* Field HUD sink: the HP meter/number commands of the hit scripts (METERCTRL hpmt<N> SETPERCENT, NUMBERCTRL hpnm<N> SETVALUE) are recorded
 * per player slot; the field has no HUD models yet, so nothing is drawn. */
static void fieldhud_uv(void *fhud,uint32_t node,uint32_t geometry,uint32_t vertex,float uv[2]){if(!dw4_fieldhud_uv(fhud,node,geometry,vertex,uv))dw4_fieldhud_popup_uv(fhud,node,geometry,vertex,uv);}
static int fieldhud_time(void *fhud,uint32_t node,int32_t slot,int64_t *time){return dw4_fieldhud_time(fhud,node,slot,time);}
static int hud_sink(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_hubruntime *h=user;*r=(dw4_script_value){0};
    if(strcmp(method,"sd") || n!=5 || a[1].type!=DW4_SCRIPT_STRING || a[3].type!=DW4_SCRIPT_STRING || a[4].type!=DW4_SCRIPT_STRING || !a[1].string || !a[3].string || !a[4].string){
        snprintf(error,cap,"unsupported HUD call %s/%zu",method,n);return -1;
    }
    char name[16],value[48];size_t nl=a[1].length<sizeof name-1?a[1].length:sizeof name-1;
    memcpy(name,a[1].string,nl);name[nl]=0;
    size_t vl=a[4].length<sizeof value-1?a[4].length:sizeof value-1;memcpy(value,a[4].string,vl);value[vl]=0;
    unsigned slot=0;const char *digits=name;while(*digits && (*digits<'0' || *digits>'9'))digits++;
    if(*digits)slot=(unsigned)atoi(digits);
    if(slot>3)slot=3;
    if((!strncmp(name,"hpmt",4) || !strncmp(name,"mpmt",4)) && !strncmp(a[3].string,"SETPERCENT",a[3].length)){
        float pct;
        if(sscanf(value,"F<%f>",&pct)==1){
            if(name[0]=='h'){h->hud.hp_percent[slot]=pct;h->hud.updates++;}
            unsigned player=a[2].type==DW4_SCRIPT_NUMBER && a[2].number>=0 && a[2].number<4?(unsigned)a[2].number:slot;   /* METERCTRL hpmt <player RAM slot> */
            dw4_fieldhud_percent(h->fhud,name[0]=='m',player,pct);
        }
        return 0;
    }
    if(!strncmp(name,"bshp",4) && !strncmp(a[3].string,"SETMODELHP",a[3].length)){
        char model[24];int32_t ms=0;
        if(sscanf(value,"%23[^/]/I<%d>",model,&ms)==2){snprintf(h->boss_name,sizeof h->boss_name,"%s",model);h->boss_slot=ms;}
        return 0;
    }
    {   /* NUMBERCTRL <dmgnm0|expnm0|dmgnm1|bitnum0> <RAM slot> SETVALUE I<value>: the floating number's digit plate of that instance */
        static const char *const popup[4]={"dmgnm0","expnm0","dmgnm1","bitnum0"};
        for(unsigned k=0;k<4;k++)if(!strcmp(name,popup[k]) && a[2].type==DW4_SCRIPT_NUMBER && a[2].number>=0 && !strncmp(a[3].string,"SETVALUE",a[3].length)){
            int v;if(sscanf(value,"I<%d>",&v)==1)dw4_fieldhud_popup_value(h->fhud,k,(unsigned)a[2].number,v);
            return 0;
        }
    }
    if(!strncmp(name,"hpnm",4) && !strncmp(a[3].string,"SETVALUE",a[3].length)){
        int v;if(sscanf(value,"I<%d>",&v)==1){h->hud.hp_value[slot]=v;h->hud.updates++;}
        return 0;
    }
    return 0;   /* other meter/number commands (MP, level) carry nothing the field slice reads */
}
/* The native HP gauge publication of the combat owner (support heals, buff recalculation): the same two values the METERCTRL / NUMBERCTRL sends carry
 * (percent = 100.0f * hp / max_hp, FUN_003f9c80), recorded like the script ones (updates counts each of the two sends). */
static void combat_hud(void *user,int32_t slot,int32_t hp,int32_t max_hp)
{
    dw4_hubruntime *h=user;
    if(!h || slot<0 || slot>3 || max_hp<=0)return;
    h->hud.hp_percent[slot]=100.0f*(float)hp/(float)max_hp;h->hud.hp_value[slot]=hp;h->hud.updates+=2;
    dw4_fieldhud_percent(h->fhud,0,(unsigned)slot,100.0f*(float)hp/(float)max_hp);
}
/* FUN_00373ef0: the number popup of a hit script (MDLdspDamage / MDLdspExp / MDLdspDamageP). Row names and per-digit-count sequences are the table at
 * 0x4c8770; the digit count is the value's decimal length capped at five (99999). Retail sends MODELCTRL <model> FIND_SPACE, GENERATE (sequence,
 * position) and NUMBERCTRL <number> SETVALUE; the model pool is full -> the popup is dropped, as FIND_SPACE finding nothing leaves GetObjectCount at zero. */
static void combat_popup(void *user,int32_t row,int32_t value,const float position[3])
{
    static const char *const model[5]={"i_dmgnum","i_expnum","i_healnum","i_pcdmgnum","i_bitnum"};
    static const char *const prefix[5]={"SQ_DMGNM0","SQ_EXPNM0","SQ_HEALNM0","SQ_DMGNM0","SQ_BITNM0"};
    dw4_hubruntime *h=user;char error[160];
    if(!h || row<0 || row>4)return;
    int digits=value<10?1:value<100?2:value<1000?3:value<10000?4:5;
    if(value>99999)value=99999;
    if(row==1 || row==4)digits=digits>4?4:digits;   /* SQ_EXPNM04 / SQ_BITNM04 repeat for five digits */
    int32_t slot=dw4_scriptservices_first_inactive(h->sd,"MODELCTRL",model[row]);
    if(slot<0){h->popups.refused++;return;}
    char sequence[16],text[160];snprintf(sequence,sizeof sequence,"%s%d",prefix[row],digits);
    snprintf(text,sizeof text,"V<%.9g,%.9g,%.9g>/V<0,0,0>/%s",position[0],position[1],position[2],sequence);
    dw4_script_value a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,model[row],strlen(model[row])},{DW4_SCRIPT_NUMBER,slot,NULL,0},
        {DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,text,strlen(text)}},r;
    if(dw4_scriptservices_call(h->sd,"sd",a,5,&r,error,sizeof error)){h->popups.refused++;return;}
    {   /* NUMBERCTRL <number> SETVALUE: dmgnm0 / expnm0 / (healnm0) / dmgnm1 / bitnum0 */
        static const char *const number[5]={"dmgnm0","expnm0","healnm0","dmgnm1","bitnum0"};
        char v[24];snprintf(v,sizeof v,"I<%d>",value);
        dw4_script_value n[5]={{DW4_SCRIPT_STRING,0,"NUMBERCTRL",10},{DW4_SCRIPT_STRING,0,number[row],strlen(number[row])},{DW4_SCRIPT_NUMBER,slot,NULL,0},
            {DW4_SCRIPT_STRING,0,"SETVALUE",8},{DW4_SCRIPT_STRING,0,v,strlen(v)}};
        if(dw4_scriptservices_call(h->sd,"sd",n,5,&r,error,sizeof error)){h->popups.refused++;return;}
    }
    h->popups.spawned[row]++;h->popups.last_value=value;snprintf(h->popups.last_sequence,sizeof h->popups.last_sequence,"%s",sequence);
}
/* Drop presentation helpers (beNDMWMdlItem). One sd call with a MODELCTRL / TEXTCTL shape. */
static int loot_sd(dw4_hubruntime *h,const char *category,const char *name,int32_t slot,const char *command,const char *value)
{
    dw4_script_value a[5]={str(category),name?str(name):(dw4_script_value){0},{DW4_SCRIPT_NUMBER,slot,NULL,0},str(command),{0}},r;
    char error[160];
    if(value)a[4]=str(value);
    return dw4_scriptservices_call(h->sd,"sd",a,value?5:4,&r,error,sizeof error);
}
static int loot_text(dw4_hubruntime *h,int slot,const char *command,const char *value)
{
    char data[160];
    snprintf(data,sizeof data,"ITNAMEFONT/%s/%s",dw4_loot_label_font(slot),value);
    return loot_sd(h,"TEXTCTL",NULL,-1,command,data);
}
/* The 'got item' effect (FUN_004412c0): PLAYER <slot> SETEFFECT <panel> <sequence> 1.0 V<0,0,0> false true. The player's controller turns it into the panel model's sequence. */
static void loot_effect(dw4_hubruntime *h,int slot,int32_t record)
{
    const char *panel,*sequence;char value[96],error[160];dw4_script_value r;
    if(slot<0 || slot>3 || !h->loot_party[slot] || dw4_loot_effect(record,&panel,&sequence))return;
    snprintf(value,sizeof value,"%s/%s/F<1>/V<0,0,0>/FALSE/TRUE",panel,sequence);
    dw4_script_value a[5]={str("MODELCTRL"),str("PLAYER"),{DW4_SCRIPT_NUMBER,slot,NULL,0},str("SETEFFECT"),str(value)};
    if(dw4_modelctrl_service(h->loot_party[slot],"sd",a,5,&r,error,sizeof error)){h->lootfx.failed++;return;}
    h->lootfx.effects++;h->lootfx.last_effect_slot=slot;
    snprintf(h->lootfx.last_effect_panel,sizeof h->lootfx.last_effect_panel,"%s",panel);snprintf(h->lootfx.last_effect_sequence,sizeof h->lootfx.last_effect_sequence,"%s",sequence);
}
/* Loot (src/loot.c): the item databases behind the drop categories, the roll hook and the pickup callbacks. */
static int loot_number(void *user,int category,int32_t record,const char *column,int32_t *out)
{
    dw4_hubruntime *h=user;const dw4_database *db=dw4_databases_get(h->databases,dw4_loot_category_name(category));
    return db?dw4_database_number(db,record,column,out):-1;
}
static const char *loot_string(void *user,int category,int32_t record,const char *column)
{
    dw4_hubruntime *h=user;const dw4_database *db=dw4_databases_get(h->databases,dw4_loot_category_name(category));
    return db?dw4_database_string(db,record,column):NULL;
}
/* FUN_00384800: the drop spawns its model (MODELCTRL <model> GENERATE with the position, the record and the category index) on the model's first free instance, and
 * beNDMWMdlItem::vfunc_36 builds the item object with the LEVEL of player 1 in that step. A model pool that is full leaves no instance, so no item exists (nothing is
 * rolled); a model name no controller of the stage carries keeps the record-only drop; GENERATE here takes the position alone (the record and category stay in the drop). */
static void loot_drop_hook(void *user,dw4_drop *d,dw4_random *rng)
{
    dw4_hubruntime *h=user;int32_t level=0;
    dw4_loot_db db={h,loot_number,loot_string};
    d->loot_ready=0;d->model_slot=-1;d->model_live=0;d->model[0]=0;
    if(dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",0),"LEVEL",&level))return;
    int category=dw4_loot_category(d->entry.category);
    const char *model=dw4_loot_model(&db,category,d->entry.id);
    int32_t slot=-1;
    if(model && strlen(model)<sizeof d->model){
        if(dw4_scriptservices_is_active(h->sd,"MODELCTRL",model,0)<0){   /* no controller of this name in the stage */
            h->lootfx.unmodelled++;snprintf(h->lootfx.missing,sizeof h->lootfx.missing,"%s",model);
        }else if((slot=dw4_scriptservices_first_inactive(h->sd,"MODELCTRL",model))<0){
            h->lootfx.lost++;d->collected=1;return;   /* every instance is busy: GENERATE finds no receiver, no item object is built */
        }
    }
    d->loot_ready=!dw4_loot_make(&db,d->entry.category,d->entry.id,level,rng,&d->loot);
    if(!d->loot_ready || slot<0)return;
    char value[64];snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>",d->position[0],d->position[1],d->position[2]);
    if(loot_sd(h,"MODELCTRL",model,slot,"GENERATE",value)){h->lootfx.failed++;return;}
    snprintf(d->model,sizeof d->model,"%s",model);d->model_slot=slot;d->model_live=1;h->lootfx.spawned++;
}
static dw4_loot_drop *loot_at(void *user,size_t i)
{
    dw4_drop *d=(dw4_drop *)user+i;
    if(!d->loot_ready)return NULL;
    memcpy(d->loot.position,d->position,sizeof d->loot.position);d->loot.collected=d->collected;return &d->loot;
}
/* The model is told SQ_DDMG once its item was delivered (the unnamed models' key event after the effect, the named models' DROPITEM answer): it plays its DEAD01 fade and ends. */
static void loot_picked(void *user,size_t index,int slot,int32_t bit)
{
    dw4_hubruntime *h=user;size_t nd=0;dw4_drop *dr=dw4_fieldgen_drops_mut(h->gen,&nd);
    if(index>=nd)return;
    dw4_drop *d=dr+index;
    d->collected=1;h->pickups++;
    if(!dw4_loot_named(d->loot.model_kind)){
        if(bit>0)combat_popup(h,4,bit,d->position);   /* record 0: the Instant item's BIT case sends FUN_00373ef0(amount, 4) */
        else if(d->loot.record>=1)loot_effect(h,slot,d->loot.record);   /* records 1..25: FUN_004412c0 */
    }else h->lootfx.dropitems++;
    if(d->model_live && !loot_sd(h,"MODELCTRL",d->model,d->model_slot,"SQ_DDMG",NULL))h->lootfx.erased++;
}
/* The DROPITEM message of beNDMWMdlPlayer::vfunc_38's Cross branch, sent when the press arrives (not on the next tick): the drop this player's label names answers it
 * (vfunc_45) and delivers. Returns 1 when a pickup took the press: the branch swings only when no bool came back (`beMessenger_GetBoolCount == 0`), so the caller skips
 * the swing. A press with no label, or one the item refuses (a full folder, nine disks), returns 0 and the swing goes ahead. A press in the very tick the label appears
 * is not answered here (the label is shown by the tick's own pickup step, which then delivers it; that edge still swings). */
static int loot_cross(dw4_hubruntime *h,unsigned slot)
{
    if(!h->gen || !h->field || slot>3 || !h->loot_party[slot])return 0;
    int32_t hp=1;dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",(int)slot),"HP",&hp);
    if(hp<=0)return 0;   /* a downed player has no pickup (and holds no label) */
    size_t nd=0;dw4_drop *dr=dw4_fieldgen_drops_mut(h->gen,&nd);
    dw4_loot_ctx ctx={.players=h->players,.db={h,loot_number,loot_string},.random=&h->state.random,
        .recalculate=dw4_playerstats_recalculate,.recalculate_user=(void *)h->databases};
    int rc=dw4_loot_cross(&h->loot,&ctx,nd,loot_at,dr,(int)slot,loot_picked,h);
    if(rc<0){snprintf(h->error,sizeof h->error,"loot delivery failed");return 0;}
    return rc;
}
/* beNDMWMdlItem::vfunc_38 / vfunc_43: the label of a named model on a player's ITNAMEFONT text (ALIGN CENTER, TEXTSET the item's NAME, SWITCH SET; dropped with SWITCH CLR). */
static void loot_label(void *user,size_t index,int slot,int on)
{
    dw4_hubruntime *h=user;size_t nd=0;dw4_drop *dr=dw4_fieldgen_drops_mut(h->gen,&nd);
    if(slot<0 || slot>3)return;
    if(!on){
        if(h->label[slot].drop<0)return;
        loot_text(h,slot,"SWITCH","CLR");h->label[slot].drop=-1;h->lootfx.labels_off++;return;
    }
    if(index>=nd)return;
    const char *name=loot_string(h,dr[index].loot.category,dr[index].loot.record,"NAME");
    if(loot_text(h,slot,"ALIGN","CENTER") || (name && loot_text(h,slot,"TEXTSET",name)) || loot_text(h,slot,"SWITCH","SET")){h->lootfx.failed++;return;}
    h->label[slot].drop=(int)index;h->label[slot].dim=0;h->label[slot].due_ns=0;   /* the colour timer starts expired: the first tick sets the full colour */
    h->lootfx.labels_on++;h->lootfx.last_label_slot=slot;snprintf(h->lootfx.last_label,sizeof h->lootfx.last_label,"%s",name?name:"");
}
/* vfunc_38 state 1, each tick a label is up: the colour alternates between the item colour and a third of it every 0.5 s (FUN_00447d00 gives the colour), and the
 * text is placed over the item - its position 10 units up through the camera's view and projection, as screen units of 1/100 of a pixel of the 640x448 frame,
 * x shifted by -0.7, depth -5 (SETPOSITION). Only the box camera of a field stage is known to the tick; elsewhere the authored position stays. */
static void loot_label_tick(dw4_hubruntime *h)
{
    size_t nd=0;dw4_drop *dr=dw4_fieldgen_drops_mut(h->gen,&nd);
    dw4_lobby_control_state camera={0};int have=!dw4_lobby_control(h->world,&camera) && camera.box_camera;
    for(int slot=0;slot<4;slot++){
        int i=h->label[slot].drop;
        if(i<0 || (size_t)i>=nd)continue;
        char value[96];
        if(h->now_ns>=h->label[slot].due_ns){
            float c[3];dw4_loot_label_color(&dr[i].loot,c);
            h->label[slot].dim=!h->label[slot].dim;   /* 0 at creation: full colour first */
            float k=h->label[slot].dim?1.0f:1.0f/3.0f;
            snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>",c[0]*k,c[1]*k,c[2]*k);
            loot_text(h,slot,"COLOR",value);
            h->label[slot].due_ns=h->now_ns+500000000ull;
        }
        if(have){
            const float *w=camera.camera_world;float view[16]={0},p[3]={dr[i].position[0],dr[i].position[1]+10.0f,dr[i].position[2]};
            view[15]=1;
            for(unsigned r=0;r<3;r++)for(unsigned col=0;col<3;col++)view[4*r+col]=w[4*col+r];
            for(unsigned k=0;k<3;k++)view[12+k]=-(w[12]*view[k]+w[13]*view[4+k]+w[14]*view[8+k]);
            float v[3];
            for(unsigned k=0;k<3;k++)v[k]=p[0]*view[k]+p[1]*view[4+k]+p[2]*view[8+k]+view[12+k];
            v[2]=-v[2];   /* the lobby negates the camera Z after this view */
            if(v[2]>0.0f){
                const float t=tanf(DW4_SCENE_CAMERA_FOV*.5f);
                float nx=v[0]*(0.7f/t)/v[2],ny=v[1]*(1.0f/t)/v[2];   /* the 640x448 projection: scale 0.7 / tan and 1 / tan */
                snprintf(value,sizeof value,"V<%.9g,%.9g,-5>",nx*320.0f/100.0f-0.7f,ny*224.0f/100.0f);
                loot_text(h,slot,"SETPOSITION",value);
            }
        }
    }
}
/* A model that ended without being taken (the unnamed models blink out after 960 frames) takes its item with it; a taken one is done once its fade ended. */
static void loot_model_tick(dw4_hubruntime *h)
{
    size_t nd=0;dw4_drop *dr=dw4_fieldgen_drops_mut(h->gen,&nd);
    for(size_t i=0;i<nd;i++){
        dw4_drop *d=dr+i;
        if(!d->model_live || dw4_scriptservices_is_active(h->sd,"MODELCTRL",d->model,d->model_slot)==1)continue;
        d->model_live=0;
        if(!d->collected){d->collected=1;h->lootfx.expired++;}
    }
}
const dw4_hubruntime_loot *dw4_hubruntime_loot_stats(const dw4_hubruntime *h){return h?&h->lootfx:NULL;}
const dw4_hubruntime_popups *dw4_hubruntime_popup_stats(const dw4_hubruntime *h){if(!h)return NULL;((dw4_hubruntime *)h)->popups.digit_vertices=dw4_fieldhud_popup_hits(h->fhud);return &h->popups;}
/* Field worlds have no sub-window owner (it belongs to the hub's status UI): the practice stage only removes it and waits for it to stop running. */
static int subwnd_stub(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    (void)user;(void)error;(void)cap;*r=(dw4_script_value){0};
    if(!strcmp(method,"sd") && n==4 && a[3].type==DW4_SCRIPT_STRING && a[3].string && a[3].length==5 && !strncmp(a[3].string,"ISRUN",5)){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};return 0;}
    return 0;
}
static int window(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    struct hub_window *w=user;dw4_script_value args[5];if(n<4 || n>5)return -1;
    memcpy(args,a,n*sizeof *a);args[1]=str(w->name);
    int rc=dw4_lobby_window_service(w->hub->world,method,args,n,r,error,cap);
    if(!rc) {
        dw4_script_value query[]={str("MODELCTRL"),str(w->name),{DW4_SCRIPT_NUMBER,0,NULL,0},str("ISRUN")},active;
        if(dw4_lobby_window_service(w->hub->world,"querySD",query,4,&active,error,cap))return -1;
        dw4_scriptservices_active(w->hub->sd,w->token,active.number!=0);
    }
    return rc;
}
/* HITLANDMODEL <name> ONHIT/OFFHIT (the Commander Room's start.lua removes hitmovepass01z05 once its moving pass is switched on,
 * flag 324): the named beHitLandModelInfo's static collision graph leaves or rejoins walking. Its engine receiver is not recovered;
 * this host owner changes only the collision the walking solver uses. Other keys fail loudly. */
static int hitland(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_hubruntime *h=user;*r=(dw4_script_value){0};
    if(strcmp(method,"sd") || n!=4 || a[1].type!=DW4_SCRIPT_STRING || !a[1].string || a[3].type!=DW4_SCRIPT_STRING || !a[3].string ||
       (strcmp(a[3].string,"OFFHIT") && strcmp(a[3].string,"ONHIT"))) {
        snprintf(error,cap,"unsupported HITLANDMODEL %s %s",method,n>=4 && a[3].type==DW4_SCRIPT_STRING && a[3].string?a[3].string:"");return -1;
    }
    if(dw4_lobby_collision_hit(h->world,a[1].string,!strcmp(a[3].string,"ONHIT"))){
        /* A name the stage does not own reaches no receiver in retail (the call is a no-op); the hubs keep the strict check, field scripts
         * (stagGF02 names hitbreakinggatez050) rely on the lenient one. */
        if(h->field && strstr(dw4_lobby_script_error(h->world),"no such hit-land model")){h->hitland_missing++;dw4_lobby_clear_script_error(h->world);return 0;}
        snprintf(error,cap,"%s",dw4_lobby_script_error(h->world));return -1;
    }
    return 0;
}
static void model_action(void *user,const char *name,const char *action)
{dw4_lobby_model_action(((dw4_hubruntime *)user)->world,name,action);}
static int publish(dw4_hubruntime *h)
{
    static const char *names[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky"};
    if(dw4_lobby_bind_scripts(h->world,h->scripts,&h->state,1)){snprintf(h->error,sizeof h->error,"bind scripts: %s",dw4_lobby_script_error(h->world));return -1;}
    if(dw4_lobby_native_scene(h->world,h->models,h->objects,h->origin_ns)){snprintf(h->error,sizeof h->error,"native scene: %s",dw4_lobby_script_error(h->world));return -1;}
    for(unsigned i=0;i<5 && !h->field;i++) {
        if(!dw4_stageobjects_find(h->objects,"beModelCtrlInfo",names[i],0))return -1;
        h->window[i]=(struct hub_window){h,names[i],0};
        h->window[i].token=dw4_scriptservices_register(h->sd,1,"MODELCTRL",names[i],0,0,window,h->window+i);
        if(!h->window[i].token || dw4_controllers_external(h->models,h->objects,names[i],0,dw4_lobby_window_model(h->world,i)))return -1;
    }
    const char *player=dw4_property_string(dw4_playerrecords_get(h->players,"GETPLAYER",0),"DIGIMONNAME");
    if(!player || dw4_lobby_publish_player(h->world,h->sd,1,player)){snprintf(h->error,sizeof h->error,"publish player: %s",dw4_lobby_script_error(h->world));return -1;}
    if(!dw4_scriptservices_register(h->sd,1,"CAMERA",NULL,-1,1,dw4_lobby_camera_service,h->world) ||
       !dw4_scriptservices_register(h->sd,1,"MATCTRL",NULL,-1,1,dw4_lobby_material_service,h->world) ||
       !dw4_scriptservices_register(h->sd,1,"LIGHTCTRL",NULL,-1,1,dw4_lobby_light_service,h->world) ||
       !dw4_scriptservices_register(h->sd,1,"SWITCHCTRL",NULL,-1,1,dw4_stageobjects_switch_service,h->objects) ||
       !dw4_scriptservices_register(h->sd,1,"HITLANDMODEL",NULL,-1,1,hitland,h))return -1;
    for(size_t i=0;i<dw4_stageobjects_count(h->objects) && !h->field;i++) {
        const dw4_stageobject *o=dw4_stageobjects_at(h->objects,i);const char *kind=dw4_stageobject_kind_string(o);
        if(!strcmp(dw4_stageobject_class(o),"beNDMWPanelWazaInfo") || (kind && (!strcmp(kind,"KIND_ENEMY") || !strcmp(kind,"KIND_PLAYER2")))) {
            snprintf(h->error,sizeof h->error,"hub startup requires an unsupported gameplay owner: %s",dw4_stageobject_class(o));return -1;
        }
    }
    if(h->field){
        /* The generator set follows the save's difficulty (generator<n|h|v>.igb): retail's common DIFFICULTY record read 1 in a Hard save and its Humid Cave generators spawned the Hard rows. */
        int32_t difficulty=0;{dw4_property_folder *common=dw4_playerrecords_get(h->players,"GETCOMMON",0);if(!common || dw4_property_number(common,"DIFFICULTY",&difficulty) || difficulty<0 || difficulty>2)difficulty=0;}
        h->gen=dw4_fieldgen_open(h->mount,h->stage,(int)difficulty);
        if(!h->gen || !dw4_scriptservices_register(h->sd,1,"GENERATER",NULL,-1,1,dw4_fieldgen_service,h->gen))return -1;
        dw4_fieldgen_attach(h->gen,h->sd,h->databases,h->models);dw4_fieldgen_scripts(h->gen,h->scripts);dw4_fieldgen_random(h->gen,&h->state.random);dw4_loot_state_reset(&h->loot);dw4_fieldgen_on_drop(h->gen,loot_drop_hook,h);dw4_loot_state_label(&h->loot,loot_label,h);for(int q=0;q<4;q++)h->label[q].drop=-1;
        if(!dw4_scriptservices_register(h->sd,1,"SUBWND",NULL,-1,1,subwnd_stub,h) || !dw4_scriptservices_register(h->sd,1,"METERCTRL",NULL,-1,1,hud_sink,h) || !dw4_scriptservices_register(h->sd,1,"NUMBERCTRL",NULL,-1,1,hud_sink,h))return -1;
        h->combat=dw4_combat_open(h->players,h->databases,&h->state.random,h->models);
        if(!h->combat)return -1;
        dw4_combat_scripts(h->combat,h->scripts,1);
        dw4_combat_popup(h->combat,combat_popup,h);
        dw4_combat_hud(h->combat,combat_hud,h);   /* heals and buff recalculations publish the HP gauge like FUN_003f9c80 / ADDHP(index, 0) */
        h->tech=dw4_technique_open(h->players,h->databases);
        if(!h->tech)return -1;
    }
    if(dw4_scriptservices_category(h->sd,"ENEMY") || dw4_scriptservices_category(h->sd,"PLAYER2") || dw4_scriptservices_category(h->sd,"NDMWPANEL"))return -1;
    dw4_lobby_dialogue(h->world,h->dialogue);dw4_lobby_services_sample(h->world,h->origin_ns);
    return 0;
}
static dw4_statusview_context status_view(dw4_hubruntime *h,int player)
{return (dw4_statusview_context){.sd=h->sd,.engine=h->scripts,.players=h->players,.scope=1,.player=player};}
static int status_generators_available(dw4_hubruntime *h)
{
    for(size_t i=0;i<dw4_stageobjects_count(h->objects);i++)
        if(!strcmp(dw4_stageobject_class(dw4_stageobjects_at(h->objects,i)),"beGeneraterInfo"))return 0;
    return 1;
}
/* The menu reads the pad of the slot that owns it (SUBWND ... I<player>, retail g_messPlayerNo); the other pads never reach it. */
static int status_input(void *user,int32_t player,dw4_statuspage_input *out)
{
    dw4_hubruntime *h=user;if(player<0 || player>3 || player!=h->owner)return -1;
    *out=dw4_stageinput_slot(&h->input,player)==4?(dw4_statuspage_input){0}:h->pad[player].status;return 0;
}
static int status_appearance(void *user,int32_t player,char *error,size_t cap)
{
    dw4_hubruntime *h=user;if(player<0 || player>3 || player!=h->owner)return -1;
    /* No equipped weapon publishes the unarmed appearance (no weapon graph, first authored motion section). The weapon goes on the owner's own
     * lobby player; a slot the lobby has not joined has no model to dress (the hubs open one player). */
    const char *weapon=dw4_property_string_at(dw4_playerrecords_get(h->players,"GETPLAYER",player),"POWERSOCKETNAME",0);
    if(dw4_lobby_select_player(h->world,(unsigned)player)){snprintf(error,cap,"STATUS appearance: player %d has no lobby model",(int)player);return -1;}
    int rc=dw4_lobby_weapon(h->world,h->mount,weapon?weapon:"",error,cap);
    dw4_lobby_select_player(h->world,0);return rc;
}
static int status_scene(void *user,const dw4_statusscene_command *c,char *error,size_t cap)
{
    dw4_hubruntime *h=user;
    if(c->op==DW4_STATUSSCENE_HOLD) {
        int hold=!strcmp(c->value,"1");
        if(hold) {
            if(dw4_lobby_control(h->world,&h->held_world) || dw4_lobby_presentation(h->world,&h->held_presentation))return -1;
        }else {
            dw4_lobby_control_state world;dw4_lobby_presentation_state presentation;
            if(dw4_lobby_control(h->world,&world) || dw4_lobby_presentation(h->world,&presentation) ||
               world.material_ticks!=h->held_world.material_ticks || presentation.tick!=h->held_presentation.tick ||
               (!h->field && memcmp(world.camera_world,h->held_world.camera_world,sizeof world.camera_world))) {   /* a field stage's scripts keep running and may cut its camera */
                snprintf(error,cap,"hub STATUS world clock advanced while held");return -1;
            }
        }
        dw4_lobby_status(h->world,hold);dw4_lobby_native_ui(h->world,hold?h->status_ui:h->ui);return 0;
    }
    if(c->op==DW4_STATUSSCENE_HEALTH) {
        dw4_playerhealth health;
        if(c->player<0 || c->player>3 || dw4_playerhealth_restore(h->players,c->player,&health,error,cap))return -1;
        if(h->field) {   /* a field world has no lobby HUD: the gauges follow the records (hp*100/max, as ADDHP/ADDMP 0 publish) */
            int32_t hp=0,mp=0,mhp=0,mmp=0;dw4_property_folder *pf=dw4_playerrecords_get(h->players,"GETPLAYER",c->player);
            if(h->fhud && !dw4_property_number(pf,"HP",&hp) && !dw4_property_number(pf,"MP",&mp) && !dw4_property_number(pf,"MHP",&mhp) && !dw4_property_number(pf,"MMP",&mmp) && mhp>0 && mmp>0) {
                if(hp<0)hp=0;
                if(hp>mhp)hp=mhp;
                if(mp<0)mp=0;
                if(mp>mmp)mp=mmp;
                float value;ee_f32 percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(hp),0x42c80000),ee_f32_from_s32(mhp));memcpy(&value,&percent,4);
                if(hp)dw4_fieldhud_percent(h->fhud,0,(unsigned)c->player,value);
                percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(mp),0x42c80000),ee_f32_from_s32(mmp));memcpy(&value,&percent,4);
                dw4_fieldhud_percent(h->fhud,1,(unsigned)c->player,value);
            }
            return 0;
        }
        return c->player?0:dw4_lobby_health_publish(h->world,&health);   /* the hub HUD shows player zero only; the other slots have no hub panel yet */
    }
    if(!strcmp(c->category,"GENERATER")) {
        if((strcmp(c->key,"ONFREEZE") && strcmp(c->key,"OFFREEZE")) || (!h->field && !status_generators_available(h)))return -1;
        return 0; /* No Work in the validated generator-free hub roster; a field world's generators stop with its game clock (frozen_ns, dw4_hubruntime_tick). */
    }
    dw4_statusview_context v=status_view(h,h->owner);
    if(!strcmp(c->category,"LAYERCTL")) {
        char value[96];snprintf(value,sizeof value,"%s/%s",c->name,c->value);
        return dw4_statusui_call(&v,0,"LAYERCTL",NULL,-1,c->key,value,error,cap);
    }
    return dw4_statusui_call(&v,0,c->category,c->name,-1,c->key,c->value,error,cap);
}
/* Chip quote preview: compare the staged, recalculated stats with the STATUS baseline, taking the
 * baseline from the current record the first time (retail's SUBWND UPDATE owner). */
static int xdata_preview(void *user,dw4_property_folder *staged,char *error,size_t cap)
{
    dw4_hubruntime *h=user;
    if(!dw4_statusstats_state(&h->status_stats).valid && dw4_statusstats_refresh(&h->status_stats,h->owner,error,cap))return -1;
    return dw4_statusstats_compare_folder(&h->status_stats,staged,error,cap);
}
/* The selected service of the generic shop root (the original factory table, entry code = SUBWND mode): XDATA 1, BANK 3,
 * CNOS 4, DISK 5, WPU/APU/CHIP 6..8 and JUNK 9. Each shares STATUS's scene freeze, restore and balance refresh. */
static dw4_menu_window *shop_service(void *user)
{
    dw4_hubruntime *h=user;int32_t mode=h->shop_mode;
    if(mode==2) {
        /* SUBWND LABO (Digilabo 431760 with its Evolve child) inside the shop root's backdrop, player panel and header; it embeds the
         * STATUS equipment menu for its "check" entry. */
        dw4_statusgear_context g={.view=status_view(h,h->owner),.databases=h->databases,.stats=&h->status_stats,
            .input=status_input,.appearance=status_appearance,.user=h};
        return dw4_laboshop_window_open(&g);
    }
    if(mode==1) {
        dw4_xdatashop_context x={.view=status_view(h,h->owner),.databases=h->databases,.input=status_input,.preview=xdata_preview,.user=h};
        return dw4_xdatashop_window_open(&x);
    }
    if(mode==3) {
        dw4_bankshop_context b={.view=status_view(h,h->owner),.databases=h->databases,.input=status_input,.user=h};
        return dw4_bankshop_window_open(&b);
    }
    if(mode==4) {
        /* CNOS: the item converter draws from the engine's shared MT19937 stream. */
        dw4_cnosshop_context n={.view=status_view(h,h->owner),.databases=h->databases,.input=status_input,.random=&h->state.random,.user=h};
        return dw4_cnosshop_window_open(&n);
    }
    if(mode==5) {
        dw4_diskshop_context d={.view=status_view(h,h->owner),.databases=h->databases,.input=status_input,.user=h};
        return dw4_diskshop_window_open(&d);
    }
    /* WPU/APU/CHIP/JUNK: the stock selection ran in prepare; the goods preview compares against the STATUS stat owner. */
    dw4_equipshop_context e={.view=status_view(h,h->owner),.databases=h->databases,.stock=&h->stock,.mode=mode,.input=status_input,
        .preview=xdata_preview,.user=h};
    return dw4_equipshop_window_open(&e);
}
static int status_prepare(void *user,int32_t mode,int32_t player,dw4_menu_window **out,char *error,size_t cap)
{
    dw4_hubruntime *h=user;
    if(mode<0 || mode>10){snprintf(error,cap,"hub SUBWND mode %d is invalid",mode);return -1;}
    if(mode>1 && mode>9){snprintf(error,cap,"hub SUBWND mode %d is not implemented",mode);return -1;}
    int32_t joined=0;
    if(player<0 || player>3 || dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",player),"ISUSE",&joined) || !(uint8_t)joined ||
       !h->status_ui || !dw4_lobby_intro_done(h->world) || (!h->field && !status_generators_available(h))) {
        snprintf(error,cap,"hub STATUS/XDATA requires a joined player after arrival in a generator-free scene (a field stage: after arrival)");return -1;
    }
    /* Retail names the owner in the payload (SUBWND nil 0 GENERATE "<MODE>/I<g_messPlayerNo>"): the menu runs on that player's records and only that pad. */
    h->owner=player;
    h->shop_mode=0;
    h->status_scene=(dw4_statusscene){.players=h->players,.io=status_scene,.user=h};
    /* Clear the borrowed RAM link before replacing an owned Work, including on allocation failure. */
    if(dw4_subwindows_bind_work(dw4_dialogue_subwindows(h->dialogue),0,(dw4_handle){0}))return -1;
    dw4_statusstats_close(&h->status_stats);
    h->status_stats=(dw4_statusstats){.players=h->players,.sd=h->sd,.dialogue=h->dialogue,.name=dw4_databases_shinka_name,.database=h->databases};
    if(dw4_statusstats_bind(&h->status_stats,(dw4_handle){0}) ||
       dw4_subwindows_bind_work(dw4_dialogue_subwindows(h->dialogue),0,h->status_stats.work)){
        snprintf(error,cap,"STATUS Work allocation/binding failed");return -1;
    }
    if(mode==2) {
        /* SUBWND LABO (Digilabo 431760 with its Evolve child): shares STATUS's scene freeze and restore, and embeds the
         * STATUS equipment menu for its "check" entry. The shop root with entry code 2 builds Digilabo's own widgets
         * (backdrop, legend, "Digi-Lab" header); the controller adds the talk window and the compact player panel. */
        h->shop_mode=2;
        dw4_shoproot_context r={.view=status_view(h,player),.stats=&h->status_stats,.entry=2,.service=shop_service,.user=h};
        *out=dw4_shoproot_window_open(&r);return *out?0:-1;
    }
    if(mode==1 || (mode>=3 && mode<=9)) {
        /* The generic shop root (ShopCtrl00, 4267b0) builds the common widgets (backdrop, player panel, message window,
         * Select/Confirm/Cancel legend, header) and then the service selected by the entry code. */
        if(mode>=6 && mode<=9 && dw4_shopstock_prepare(&h->stock,mode,h->databases,h->players,&h->state.random,error,cap))return -1;
        if(mode>=6 && mode<=9 && (dw4_statusstats_bind(&h->status_stats,h->stock.work) || dw4_subwindows_bind_work(dw4_dialogue_subwindows(h->dialogue),0,h->stock.work))){
            snprintf(error,cap,"shop Work binding failed");return -1;
        }
        h->shop_mode=mode;
        dw4_shoproot_context r={.view=status_view(h,player),.stats=&h->status_stats,.entry=mode,.service=shop_service,.user=h};
        *out=dw4_shoproot_window_open(&r);return *out?0:-1;
    }
    dw4_statusmenu_context c={.gear={.view=status_view(h,player),.databases=h->databases,.stats=&h->status_stats,
        .input=status_input,.appearance=status_appearance,.user=h},.dialogue=h->dialogue};
    *out=dw4_statusmenu_window_open(&c);return *out?0:-1;
}
static int status_activate(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)mode;(void)player;return dw4_statusscene_freeze(&((dw4_hubruntime *)user)->status_scene,error,cap);}
static int status_begin(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)mode;(void)player;return dw4_statusscene_enter(&((dw4_hubruntime *)user)->status_scene,error,cap);}
static int status_end(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)mode;(void)player;return dw4_statusscene_restore(&((dw4_hubruntime *)user)->status_scene,error,cap);}
static int status_update(void *user,int32_t player,char *error,size_t cap)
{
    dw4_hubruntime *h=user;
    if(!h->status_scene.phase || player!=h->owner){snprintf(error,cap,"STATUS update requires the active hub menu");return -1;}
    return dw4_statusstats_refresh(&h->status_stats,player,error,cap);
}
static int status_preview(void *user,int32_t player,int on,char *error,size_t cap)
{
    dw4_hubruntime *h=user;
    if(!h->status_scene.phase || player!=h->owner){snprintf(error,cap,"STATUS preview requires the active hub menu");return -1;}
    /* OFPREVIEW is always sent after a chip quote, including for an unequipped chip that never
     * published a comparison; with no baseline there is nothing to restore. */
    if(!on && !dw4_statusstats_state(&h->status_stats).valid)return 0;
    return dw4_statusstats_compare(&h->status_stats,player,on,error,cap);
}
/* Field worlds (overworld/fortress stages): the lobby loader opens them as ordinary worlds without the hub's windows. */
int dw4_field_stage(const char *stage){return dw4_lobby_field_world(stage);}
/* The field stages whose runtime is brought up: the chain towards the Goblin Fortress's Leomon
 * room. */
int dw4_field_stage_ready(const char *stage)
{
    static const char *const ready[]={"stag0001","stag0101","stagGF01","stagGF02","stagGF03","dng101b1","dng101b2","dng102b1","dng102b2","dng102b3","stag0102"};
    for(unsigned i=0;stage && i<sizeof ready/sizeof *ready;i++)if(!strcasecmp(stage,ready[i]))return 1;
    return 0;
}
/* The hub worlds the lobby opens with a party (the Terminal, Central, the Shop, the Commander Room). */
static int hub_world_stage(const char *stage)
{
    static const char *const hubs[]={"stagML11","stagML12","stagML13","stagML02"};
    for(unsigned i=0;stage && i<sizeof hubs/sizeof *hubs;i++)if(!strcasecmp(stage,hubs[i]))return 1;
    return 0;
}
int dw4_hubruntime_destination_available(const char *stage)
{
    return stage && (!strncasecmp(stage,"stagML",6) || !strncasecmp(stage,"stagIS",6) || dw4_field_stage_ready(stage));
}
dw4_hubruntime *dw4_hubruntime_prepare(dw4_mount *mount,const dw4_hubruntime_source *source,
    const char *stage,int32_t point,int light_hard,char *error,size_t cap)
{
    /* The Terminal's field gate (mate00) and Emergency Gate (mate02) request field and dungeon stages: refuse them by name. */
    if(!dw4_hubruntime_destination_available(stage)) {
        if(error && cap)snprintf(error,cap,"%s is not available: field and dungeon stages have no runtime in this build",stage?stage:"(null)");
        return NULL;
    }
    dw4_hubruntime *h=calloc(1,sizeof *h);if(!h)return NULL;
    const char *step="session snapshot";h->mount=mount;h->light_hard=!!light_hard;
    if(!mount || !source || !source->state || source->world_ns>INT64_MAX || !(h->players=dw4_playerrecords_snapshot(source->records)))goto fail;
    int32_t joined,joined2;
    /* NINZU players occupy slots 0..NINZU-1. Local co-op (2-4) runs in the field worlds, the dungeons and the four hub worlds (stagML11/12/13/02);
     * the digivolution demo and the interface scenes still take the single player-zero owner. */
    if(dw4_property_number(dw4_playerrecords_get(h->players,"GETCOMMON",0),"NINZU",&joined) || joined<1 || joined>4 ||
       (joined>1 && !dw4_field_stage(stage) && !hub_world_stage(stage)) ||
       dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",0),"ISUSE",&joined2) || !(uint8_t)joined2) {
        snprintf(h->error,sizeof h->error,"destination runtime currently requires the single joined player-zero owner");goto fail;
    }
    h->ninzu=(unsigned)joined;
    for(int i=1;i<4;i++)if(dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",i),"ISUSE",&joined2) || (i<(int)h->ninzu)!=!!(uint8_t)joined2) {
        snprintf(h->error,sizeof h->error,"destination runtime has no live additional-player owner");goto fail;
    }
    for(unsigned q=0;q<4;q++){dw4_padrepeat_init(&h->pad[q].analog);dw4_padrepeat_init(&h->pad[q].digital);}
    h->state=*source->state;h->input=source->input?*source->input:(dw4_stageinput){0};
    h->origin_ns=h->now_ns=source->world_ns;h->travel.input=&h->input;h->travel.generate_pos=point;
    const char *name=dw4_property_string(dw4_playerrecords_get(h->players,"GETPLAYER",0),"DIGIMONNAME");
    int species=0;while(species<16 && (!name || strcmp(name,dw4_lobby_model_name(species))))species++;   /* the shinka row of the player model */
    if(species==16)goto fail;
    /* stagML14 is the digivolution demo that Central's closing lab script (entry 824 chunk 61) requests when a Digimon changed:
     * its pack (NDMW 831/832) stages the old and new s_<species> models with g_changebg/i_evoline/g_dchange/i_evowipe, the
     * "entry" demo camera and DM_EVOLV/AM_EVOLV, then its only exit is PLAYERPOINT I<3> + NEXTSTAGE stagML12 (832 chunk 3). It has
     * no player and no Central world regions, so it runs as a scene host (dw4/evodemo.h) instead of a lobby; its exit is the
     * script's own travel request. DW4_EVODEMO=skip, or a demo that cannot be prepared, continues at that authored exit instead. */
    if(stage && !strcasecmp(stage,"stagML14")) {
        const char *mode=getenv("DW4_EVODEMO");
        if(!mode || strcmp(mode,"skip")) {
            step="digivolution demo";
            dw4_evodemo_source src={h->players,&h->state,h->now_ns,&h->travel};
            if((h->demo=dw4_evodemo_open(mount,&src,h->error,sizeof h->error)))return h;
            printf("  hub: stagML14 (digivolution demo) could not be prepared (%.300s); continuing at its exit stagML12 point 3\n",h->error);
            h->error[0]=0;
        }else printf("  hub: stagML14 (digivolution demo) skipped by DW4_EVODEMO=skip; continuing at its exit stagML12 point 3\n");
        stage="stagML12";point=3;h->travel.generate_pos=point;
    }
    /* stagIS11..13 are interface scenes, not hub worlds: the lobby opens only the four stagML packs, and their
     * screens run on native controllers (SAVECTRL/SAVEINTF over the SAVEUTILITY card receiver for the save
     * screen) whose update bodies are not recovered. Name the blocker instead of failing inside the lobby. */
    static const struct {const char *stage,*role;} interface_scenes[]={
        {"stagIS11","card album"},{"stagIS12","save screen"},{"stagIS13","load screen"}};
    for(unsigned i=0;i<sizeof interface_scenes/sizeof *interface_scenes;i++)if(stage && !strcasecmp(stage,interface_scenes[i].stage)){
        if(i==0) {
            /* The card album (stagIS11): the SUBWND CARD window tree hosted by the scene; it needs no memory card. */
            step="card album";
            dw4_savescene_source src={h->players,&h->state,h->now_ns,NULL,DW4_SCENE_CARD};
            h->scene=dw4_savescene_open(mount,&src,h->error,sizeof h->error);
            if(!h->scene)goto fail;
            return h;
        }
        if(i==1 || i==2) {
            /* The save screen (stagIS12) and the load/join screen (stagIS13): native SaveCtrl/SaveIntf over the host memory card, in the native save library
             * directory (DW4_SAVE_DIR overrides it for tests). The scene owns its own record snapshot. */
            step=i==2?"load screen":"save screen";
            char dir[600];const char *over=getenv("DW4_SAVE_DIR");
            if(over && *over)snprintf(dir,sizeof dir,"%s",over);
            else if(dw4_memcard_default_directory(dir,sizeof dir,1)){snprintf(h->error,sizeof h->error,"cannot create the save library directory");goto fail;}
            h->card=dw4_memcard_open(dir);
            if(!h->card || !dw4_memcard_ready(h->card)){snprintf(h->error,sizeof h->error,"save library is not usable: %.400s",dir);goto fail;}
            dw4_savescene_source src={h->players,&h->state,h->now_ns,h->card,i==2?DW4_SCENE_LOAD:DW4_SCENE_SAVE};
            h->scene=dw4_savescene_open(mount,&src,h->error,sizeof h->error);
            if(!h->scene)goto fail;
            return h;
        }
        step="interface scene";
        snprintf(h->error,sizeof h->error,"%s (%s): native interface controllers not recovered, see save-keeper.md",
            interface_scenes[i].stage,interface_scenes[i].role);
        goto fail;
    }
    h->field=dw4_field_stage(stage);snprintf(h->stage,sizeof h->stage,"%s",stage);
    step="destination CPU assets";
    char display[9]={0};dw4_unicode_object player_name;
    if(dw4_property_unicode_object(dw4_playerrecords_get(h->players,"GETPLAYER",0),"PLAYERNAME",0,&player_name) || !player_name.present)goto fail;
    for(unsigned i=0;i<8 && i<player_name.count && player_name.codes[i];i++)display[i]=dw4_name_char(player_name.codes[i]);
    if(!display[0])goto fail;
    const char *weapon=dw4_property_string_at(dw4_playerrecords_get(h->players,"GETPLAYER",0),"POWERSOCKETNAME",0);
    /* An empty POWERSOCKETNAME opens the unarmed appearance: retail skips PLAYERARMS GENERATE (3d3d88..3d3d98). */
    dw4_lobby_member others[3]={{0}};
    for(unsigned q=1;q<h->ninzu;q++) {   /* the co-op players: their model, 8-character name and equipped weapon come from their record folders */
        dw4_property_folder *pf=dw4_playerrecords_get(h->players,"GETPLAYER",(int)q);
        const char *model=dw4_property_string(pf,"DIGIMONNAME"),*wpn=dw4_property_string_at(pf,"POWERSOCKETNAME",0);
        dw4_unicode_object un;int row=0;while(model && row<16 && strcmp(model,dw4_lobby_model_name(row)))row++;
        if(!model || row==16 || dw4_property_unicode_object(pf,"PLAYERNAME",0,&un) || !un.present)goto fail;
        for(unsigned i=0;i<8 && i<un.count && un.codes[i];i++)others[q-1].name[i]=dw4_name_char(un.codes[i]);
        if(!others[q-1].name[0])goto fail;
        others[q-1].row=row;others[q-1].weapon=wpn?wpn:"";
    }
    h->world=h->ninzu>1?dw4_lobby_open_row_stage_party(mount,species,display,stage,point,weapon?weapon:"",others,h->ninzu-1):
        weapon?dw4_lobby_open_row_stage(mount,species,display,stage,point,weapon):
        dw4_lobby_open_row_stage_unarmed(mount,species,display,stage,point);
    if(!h->world)goto fail;
    dw4_lobby_set_light(h->world,h->light_hard);
    if(dw4_lobby_prepare_audio(h->world,mount))goto fail;
    step="script engine";h->sd=dw4_scriptservices_open();if(!h->sd)goto fail;
    h->scripts=dw4_scriptengine_open(&h->state,binding,h);h->files=dw4_filelist_open(mount);if(!h->scripts || !h->files)goto fail;
    dw4_scriptengine_filelist(h->scripts,h->files);dw4_scriptengine_record_flags(h->scripts,1);
    if(!dw4_scriptservices_register(h->sd,0,"GAMERAM",NULL,-1,1,gameram,h) ||
       !dw4_scriptservices_register(h->sd,0,"SOUND",NULL,-1,1,sound,h) ||
       !dw4_scriptservices_register(h->sd,0,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,&h->travel) ||
       !dw4_scriptservices_register(h->sd,0,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,&h->travel))goto fail;
    step="original func/boot and native objects";h->objects=dw4_stageobjects_open();if(!h->objects)goto fail;
    if(dw4_filelist_begin(h->files,h->scripts,stage,1) || dw4_filelist_shared(h->files) ||
       dw4_filelist_route_assets(h->files,dw4_stageobjects_route,h->objects) ||
       dw4_filelist_bind_layers(h->files,dw4_stageobjects_bind_layers,h->objects) ||
       dw4_stageobjects_publish(h->objects,h->sd,1))goto fail;
    step="database/model/dialogue owners";h->databases=dw4_databases_open(h->objects,h->error,sizeof h->error);
    if(!h->databases || dw4_databases_publish(h->databases,h->sd,1))goto fail;
    static const char *exclude[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky",
        "p_agumon","p_vmon","p_girumon","p_dorumon","p_weregaru","p_hekabut","p_wargrey","p_angelr","p_beelzeb","p_alpha","p_bwargrey",
        "p_impdrafm","p_impdrapm","p_metalgaru","p_dukecrim","p_susanoo"};
    /* The hubs publish the message/talk windows as native lobby-UI peers (excluded here); a field world has no such UI, so its window models run as
     * ordinary controllers: their sequences and ISRUN/ISSEQNAME queries let the scripts' prompts proceed, nothing is drawn. */
    static const char *const field_exclude[]={"n_digilffic","p_agumon","p_vmon","p_girumon","p_dorumon","p_weregaru","p_hekabut","p_wargrey","p_angelr","p_beelzeb",
        "p_alpha","p_bwargrey","p_impdrafm","p_impdrapm","p_metalgaru","p_dukecrim","p_susanoo"};
    const char *party[4]={NULL};   /* the co-op players' model names by slot: the lobby owns those controllers, so the stage's spare copies are not created */
    for(unsigned q=0;q<h->ninzu;q++)party[q]=dw4_property_string(dw4_playerrecords_get(h->players,"GETPLAYER",(int)q),"DIGIMONNAME");
    h->models=h->field?dw4_controllers_open_party(h->sd,1,h->objects,field_exclude,17,&h->state.random,&h->state.action_rhythm,h->scripts,party,h->ninzu):
        dw4_controllers_open_party(h->sd,1,h->objects,exclude,21,&h->state.random,&h->state.action_rhythm,h->scripts,party,h->ninzu);
    h->dialogue=dw4_dialogue_open(h->sd,1,h->objects);if(!h->models || !h->dialogue)goto fail;
    dw4_controllers_actions(h->models,model_action,h);
    dw4_controllers_audio(h->models,dw4_lobby_audio(h->world));
    dw4_controllers_sample(h->models,(int64_t)h->origin_ns);
    if(dw4_scriptservices_tick(h->sd,h->origin_ns))goto fail;
    /* Snapshot the generic WN roster before publish appends the five external
     * greeting peers. Those remain rendered exactly once by lobbyui. */
    /* A hub with a party (NINZU 2-4) has one panel set i_stpnl00..04 per joined slot (the chunks' funcPlayerStatusGenerate generates them at x = -260, -110, 40, 190, y = -160); like a
     * field world's they draw in the model view with the pack's own gauges (hpmt1..4, mpmt1..4) and plates (lvnm/hpnm/mpnm1..4), and the single-player lobby HUD draws none. */
    h->party_hud=!h->field && h->ninzu>1;
    step="destination window models";h->ui=h->field||h->party_hud?dw4_modelview_open_field(h->objects,h->models,h->error,sizeof h->error):dw4_modelview_open(h->objects,h->models,h->error,sizeof h->error);
    if(!h->ui)goto fail;
    if(h->field || h->party_hud){   /* the HUD gauges: panel nodes under a meter pose at that meter's time */
        h->fhud=dw4_fieldhud_open(mount,stage);
        if(h->party_hud && !h->fhud){snprintf(h->error,sizeof h->error,"party HUD: the stage pack has no player gauges");goto fail;}
        if(h->fhud){dw4_modelview_node_times(h->ui,fieldhud_time,h->fhud);dw4_modelview_vertex_uvs(h->ui,fieldhud_uv,h->fhud);}
        if(h->party_hud){dw4_lobby_party_hud(h->world,1);dw4_modelview_hide_hud(h->ui,1);}   /* shown once the lobby restores its HUD (see dw4_hubruntime_tick) */
    }
    step="destination native bindings";if(publish(h))goto fail;
    dw4_lobby_native_ui(h->world,h->ui);dw4_lobby_exit_events(h->world,1);
    /* The STATUS menu: a hub's and any field or dungeon stage that carries a beNDMWStatusInfo (stag0101, the dungeon floors, stagGF01 do; the practice stage does not and
     * has no Start menu). The lobby HUD and its HP/MP publication are the hubs' only. */
    {int has_status=!h->field;
     for(size_t i=0;h->field && i<dw4_stageobjects_count(h->objects);i++)if(!strcmp(dw4_stageobject_class(dw4_stageobjects_at(h->objects,i)),"beNDMWStatusInfo"))has_status=1;
    if(has_status){
    h->status_ui=dw4_modelview_open(h->objects,h->models,h->error,sizeof h->error);if(!h->status_ui)goto fail;
    dw4_subwindow_factory factory={.prepare=status_prepare,.begin=status_begin,.end=status_end,.user=h,
        .activate=status_activate,.update=status_update,.preview=status_preview};
    if(dw4_subwindows_factory(dw4_dialogue_subwindows(h->dialogue),&factory))goto fail;
    }}
    if(!h->field){
    dw4_playerhealth health;
    if(dw4_playerhealth_restore(h->players,0,&health,h->error,sizeof h->error) || dw4_lobby_health_publish(h->world,&health))goto fail;
    }
    step="original start/first";
    if(dw4_filelist_start(h->files) || dw4_filelist_first(h->files))goto fail;
    return h;
fail:
    snprintf(error,cap,"%s: %.120s; %.180s; %.120s",step,h->error,
        h->files?dw4_filelist_error(h->files):"",h->world?dw4_lobby_script_error(h->world):"");
    dw4_hubruntime_close(h);return NULL;
}
void dw4_hubruntime_close(dw4_hubruntime *h)
{
    if(!h)return;
    dw4_fieldhud_close(h->fhud);dw4_evodemo_close(h->demo);dw4_technique_close(h->tech);dw4_combat_close(h->combat);dw4_fieldgen_close(h->gen);dw4_savescene_close(h->scene);dw4_memcard_close(h->card);dw4_frontaudio_close(h->audio_keep);
    if(h->scripts && h->sd)dw4_scriptengine_remove_all(h->scripts,h->sd);
    if(h->world){dw4_lobby_native_ui(h->world,NULL);dw4_lobby_native_models(h->world,NULL,0);dw4_lobby_dialogue(h->world,NULL);}
    dw4_modelview_close(h->status_ui);dw4_modelview_close(h->ui);dw4_dialogue_close(h->dialogue);dw4_controllers_close(h->models);dw4_databases_close(h->databases);
    dw4_stageobjects_close(h->objects);dw4_filelist_close(h->files);dw4_lobby_close(h->world);
    dw4_scriptengine_close(h->scripts);dw4_scriptservices_close(h->sd);dw4_playerrecords_close(h->players);dw4_statusstats_close(&h->status_stats);dw4_shopstock_close(&h->stock);free(h);
}
/* One technique bullet volume to the combat owner (dw4_technique_deliver). */
struct fire_ctx {dw4_hubruntime *h;dw4_modelctrl *const *players;uint64_t ns;};
static int fire_volume(void *user,int32_t slot,int32_t attack,const float world[16],const float offset[3],const float size[3])
{
    struct fire_ctx *c=user;
    return dw4_combat_fire(c->h->combat,(int64_t)c->ns,slot,c->players[slot],attack,world,offset,size,c->h->error,sizeof c->h->error);
}
/* The joined players' model controllers by slot (NULL for a slot nobody joined); the lobby's current slot is left at 0. */
static void party_models(dw4_hubruntime *h,dw4_modelctrl *out[4])
{
    for(unsigned q=0;q<4;q++)out[q]=q<h->ninzu && !dw4_lobby_select_player(h->world,q)?dw4_lobby_player_model(h->world):NULL;
    dw4_lobby_select_player(h->world,0);
}
/* The player hook's per-frame part of the technique panel (beNDMWMdlPlayer::vfunc_38 polling ISCHECK): a fired technique starts SQ_WAZA with the
 * pcTech LABEL and launches its bullet; then the live bullets fly one frame. Runs after the combat tick, before the player's own tick. */
static int technique_tick(dw4_hubruntime *h,uint64_t ns,dw4_modelctrl *const players[4])
{
    for(int32_t slot=0;slot<4;slot++) {
        dw4_modelctrl *pm=players[slot];
        if(!pm || !dw4_modelctrl_active(pm))continue;
        dw4_lobby_control_state control={0};const char *seq=dw4_modelctrl_sequence(pm);
        dw4_lobby_select_player(h->world,(unsigned)slot);
        dw4_modelctrl_actor qa={0};dw4_modelctrl_actor_state(pm,&qa);
        int on_ctrl=slot?qa.enabled:!dw4_lobby_control(h->world,&control) && control.player_control;   /* slot 0 follows the lobby's control state, the others their own model's */
        int airborne=seq && (!strcmp(seq,"SQ_JUMP") || !strcmp(seq,"SQ_FALL"));
        dw4_technique_tick(h->tech,slot,on_ctrl);
        dw4_technique_cast cast;
        if(dw4_technique_poll(h->tech,slot,airborne,&cast)) {
            /* The label is selected first, then the pending SQ_WAZA request is made (immediate here, like the weapon swing). MP is already spent. */
            if(dw4_modelctrl_label(pm,"SQ_WAZA",cast.label) || dw4_lobby_player_request(h->world,"SQ_WAZA")) {
                /* Not fatal (like a refused swing): the cast is dropped, its MP stays spent. */
                fprintf(stderr,"technique %s: SQ_WAZA refused: %.200s\n",cast.label,dw4_modelctrl_error(pm));continue;
            }
            float world[16];
            dw4_modelctrl_matrix(pm,world);
            dw4_technique_launch(h->tech,slot,&cast,world);
        }
        struct fire_ctx ctx={h,players,ns};
        if(dw4_technique_step(h->tech,slot,fire_volume,&ctx)<0){dw4_lobby_select_player(h->world,0);return -1;}
    }
    dw4_lobby_select_player(h->world,0);
    return 0;
}
int dw4_hubruntime_tick(dw4_hubruntime *h,uint64_t ns)
{
    if(!h || h->error[0])return -1;
    if(ns<h->origin_ns || ns>INT64_MAX || (h->ticks && ns<=h->now_ns)) {
        snprintf(h->error,sizeof h->error,"hub tick requires the next admitted session clock sample");return -1;
    }
    if(h->demo) {
        if(dw4_evodemo_tick(h->demo,ns)){snprintf(h->error,sizeof h->error,"%s",dw4_evodemo_error(h->demo));return -1;}
        h->now_ns=ns;h->ticks++;return 0;
    }
    if(h->scene) {
        if(dw4_savescene_tick(h->scene,ns)){snprintf(h->error,sizeof h->error,"%s",dw4_savescene_error(h->scene));return -1;}
        h->now_ns=ns;h->ticks++;
        char next[sizeof h->travel.destination];int pos;
        if(!h->travel.pending && dw4_savescene_exit(h->scene,next,sizeof next,&pos)) {
            snprintf(h->travel.destination,sizeof h->travel.destination,"%s",next);h->travel.generate_pos=pos;h->travel.pending=1;
        }
        return 0;
    }
    h->now_ns=ns;
    dw4_controllers_sample(h->models,(int64_t)ns);dw4_lobby_services_sample(h->world,ns);
    for(unsigned i=0;i<5 && !h->field;i++) {
        dw4_script_value a[]={str("MODELCTRL"),str(h->window[i].name),{DW4_SCRIPT_NUMBER,0,NULL,0},str("ISRUN")},r;
        if(window(h->window+i,"querySD",a,4,&r,h->error,sizeof h->error))return -1;
    }
    /* A field world's game clock stops while its STATUS menu is open (retail freezes MODELCTRL, GENERATER and SOUND and holds message time): the combat, generator,
     * loot, KO, technique and gauge systems below get the clock without the time spent in the menu and do not run while it is open. */
    const int frozen=h->field && h->status_scene.phase;
    if(frozen && !h->freeze_from)h->freeze_from=(int64_t)ns?(int64_t)ns:1;
    else if(!frozen && h->freeze_from){h->frozen_ns+=(int64_t)ns-h->freeze_from;h->freeze_from=0;}
    const uint64_t gns=(uint64_t)((int64_t)ns-h->frozen_ns);
    int rc_sd=dw4_scriptservices_tick(h->sd,ns),rc_eng=0,rc_ctl=0,rc_lob=0,rc_dlg=0;
    if(!rc_sd)rc_eng=dw4_scriptengine_tick(h->scripts);
    if(!rc_sd && !rc_eng && h->combat && !frozen) {
        /* The players' status manager runs before the model tick, as the enemies' does inside it. */
        dw4_modelctrl *players[4];party_models(h,players);
        if(dw4_combat_tick(h->combat,(int64_t)gns,players,h->error,sizeof h->error) ||
           dw4_combat_status_tick(h->combat,players,h->error,sizeof h->error))return -1;
    }
    if(!rc_sd && !rc_eng)rc_ctl=dw4_controllers_tick(h->models,(int64_t)ns);
    if(!rc_sd && !rc_eng && !rc_ctl)rc_lob=dw4_lobby_services_tick(h->world,ns);
    if(!rc_sd && !rc_eng && !rc_ctl && !rc_lob)rc_dlg=dw4_dialogue_tick(h->dialogue);
    if(rc_sd || rc_eng || rc_ctl || rc_lob || rc_dlg) {
        if(getenv("DW4_TICK_DEBUG"))fprintf(stderr,"tick failure: sd %d engine %d controllers %d lobby %d dialogue %d\n",rc_sd,rc_eng,rc_ctl,rc_lob,rc_dlg);
        snprintf(h->error,sizeof h->error,"%.120s; %.120s; %.120s; %.120s",dw4_scriptengine_error(h->scripts),
            dw4_scriptservices_error(h->sd),dw4_controllers_error(h->models),dw4_dialogue_error(h->dialogue));return -1;
    }
    dw4_modelctrl *party[4];party_models(h,party);
    if(h->gen && h->field && !frozen) {   /* pickups (src/loot.c): BIT, x-data and UPCNT items are taken by walking over them, named models (weapons, armour, chips, disks, keys) with Cross */
        size_t nd=0;dw4_drop *dr=dw4_fieldgen_drops_mut(h->gen,&nd);
        memcpy(h->loot_party,party,sizeof h->loot_party);
        if(nd<h->loot_drops){   /* the list was cleared: the labels pointed into the old one */
            for(int q=0;q<4;q++)if(h->label[q].drop>=0){loot_text(h,q,"SWITCH","CLR");h->label[q].drop=-1;}
            dw4_loot_state_reset(&h->loot);dw4_loot_state_label(&h->loot,loot_label,h);
        }
        h->loot_drops=nd;
        loot_model_tick(h);
        if(nd){
            float pos[4][3]={{0}};int joined[4]={0},pressed[4]={0};
            for(unsigned q=0;q<4;q++){
                dw4_modelctrl *pm=party[q];int32_t hp=1;
                dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",(int)q),"HP",&hp);
                if(!pm || hp<=0)continue;   /* a living player */
                dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(pm,&pa);
                memcpy(pos[q],pa.position,sizeof pos[q]);joined[q]=1;pressed[q]=h->cross[q];
            }
            dw4_loot_ctx ctx={.players=h->players,.db={h,loot_number,loot_string},.random=&h->state.random,
                .recalculate=dw4_playerstats_recalculate,.recalculate_user=(void *)h->databases};
            if(dw4_loot_step(&h->loot,&ctx,nd,loot_at,dr,(const float (*)[3])pos,joined,pressed,loot_picked,h)<0){
                snprintf(h->error,sizeof h->error,"loot delivery failed");return -1;
            }
        }
        loot_label_tick(h);
        memset(h->cross,0,sizeof h->cross);
    }
    if(h->gen && !frozen) {
        /* Radar generators test every joined player model's position (the walking state may be unavailable while a scene hides the player). */
        float player[4][3]={{0}};unsigned np=0;dw4_modelctrl_actor actor;
        for(unsigned q=0;q<4;q++)if(party[q]){dw4_modelctrl_actor_state(party[q],&actor);memcpy(player[np++],actor.position,sizeof player[0]);}
        if(!np)np=1;
        if(dw4_fieldgen_tick(h->gen,(int64_t)gns,(const float (*)[3])player,np,h->error,sizeof h->error))return -1;
    }
    if(h->combat && !h->gameover_started && !frozen) {
        /* KO flow: a player at 0 HP gets its PLAYER2 capsule (BKCHIP stash) after the measured
         * delay; the capsule's tick finds no living PLAYER once every joined player is down, and
         * the engine's end chunk (end_g_000bcaps.lua: GAMEOVER fade, message, NEXTSTAGE stagML11)
         * runs. */
        int over=0;
        if(dw4_combat_ko_tick(h->combat,h->stage,&over)){snprintf(h->error,sizeof h->error,"KO flow: %.200s",dw4_combat_error(h->combat));return -1;}
        if(over){
            h->gameover_started=1;
            if(dw4_scriptengine_run(h->scripts,"end_g_000bcaps.lua")){snprintf(h->error,sizeof h->error,"game over chunk: %.200s",dw4_scriptengine_error(h->scripts));return -1;}
        }
    }
    if(h->gameover_started && !h->dead_restarted && h->travel.pending) {   /* GAMERAM DEADRESTART: HP = MHP, MP = MMP for the joined players; its sender is unrecovered, sent here (inference) */
        h->dead_restarted=1;
        if(dw4_magic_dead_restart(h->players)){snprintf(h->error,sizeof h->error,"DEADRESTART failed");return -1;}
    }
    if(h->combat) {
        dw4_modelctrl *players[4];party_models(h,players);
        if(!frozen && technique_tick(h,gns,players))return -1;
    }
    if(h->fhud && h->boss_name[0]){   /* the boss gauge follows its model's HP */
        const dw4_script_model *bm=dw4_controllers_state(h->models,h->boss_name,h->boss_slot);
        if(bm && bm->max_hp>0)dw4_fieldhud_boss_percent(h->fhud,100.0f*(float)bm->hp/(float)bm->max_hp);
    }
    if(!frozen)dw4_fieldhud_tick(h->fhud);
    for(unsigned q=0;h->fhud && q<h->ninzu;q++){   /* the number plates show each joined player's level, HP and MP records */
        dw4_property_folder *pf=dw4_playerrecords_get(h->players,"GETPLAYER",(int)q);int32_t lv=0,hp=0,mp=0;
        if(!dw4_property_number(pf,"LEVEL",&lv))dw4_fieldhud_number(h->fhud,0,q,lv);
        if(!dw4_property_number(pf,"HP",&hp))dw4_fieldhud_number(h->fhud,1,q,hp);
        if(!dw4_property_number(pf,"MP",&mp))dw4_fieldhud_number(h->fhud,2,q,mp);
        if(h->party_hud){   /* a hub has no combat owner publishing the gauges: each slot's record sets its HP and MP target (hp*100/max, as ADDHP/ADDMP 0 publish) */
            int32_t mhp=0,mmp=0;
            if(!dw4_property_number(pf,"MHP",&mhp) && !dw4_property_number(pf,"MMP",&mmp) && mhp>0 && mmp>0){
                if(hp<0)hp=0;
                if(hp>mhp)hp=mhp;
                if(mp<0)mp=0;
                if(mp>mmp)mp=mmp;
                ee_f32 percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(hp),0x42c80000),ee_f32_from_s32(mhp));float value;memcpy(&value,&percent,4);
                if(hp)dw4_fieldhud_percent(h->fhud,0,q,value);   /* a dead player's HP is not published (ADDHP) */
                percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(mp),0x42c80000),ee_f32_from_s32(mmp));memcpy(&value,&percent,4);
                dw4_fieldhud_percent(h->fhud,1,q,value);
            }
        }
    }
    if(h->party_hud){   /* the panels follow the lobby HUD: closed until its restore, and while a message window is open */
        dw4_lobby_control_state hud;
        dw4_modelview_hide_hud(h->ui,dw4_lobby_control(h->world,&hud) || !hud.hud || dw4_dialogue_talk_open(h->dialogue));
    }
    dw4_lobby_tick(h->world,0);h->ticks++;
    if(dw4_lobby_script_error(h->world)[0]){snprintf(h->error,sizeof h->error,"%s",dw4_lobby_script_error(h->world));return -1;}
    return 0;
}
/* The pad words of one slot, as the menus and selectors read them: the repeat trackers (first 10, next 6 frames) behind the status-page words, and the
 * dialogue owner's per-slot pad (a SELECTCTRL <name> <slot> reads the pad of that slot, so a talk's choice is answered by the talker's pad). */
static void pad_words(dw4_hubruntime *h,unsigned slot,int enabled,uint32_t analog,uint32_t held,uint32_t pressed)
{
    struct hub_pad *p=h->pad+slot;
    dw4_padrepeat_tick(&p->analog,enabled?analog:0);dw4_padrepeat_tick(&p->digital,enabled?(held|pressed):0);
    p->status=(dw4_statuspage_input){.analog=enabled?analog:0,.horizontal=p->analog.trigger|p->analog.repeat,.digital=p->digital.trigger|p->digital.repeat};
    dw4_dialogue_input(h->dialogue,slot,enabled?analog:0,enabled?held:0,enabled?pressed:0);
}
/* The technique panel's pad for one slot (R1 edge, Cross edge, cursor steps from the D-pad or stick with the status-menu repeat). */
static dw4_technique_pad technique_pad(const dw4_hubruntime *h,unsigned slot,uint32_t pressed,int can_open)
{
    const struct hub_pad *p=h->pad+slot;
    return (dw4_technique_pad){.pressed=(p->digital.trigger&0x800)|(pressed&0x4000),
        .up=!!(((p->digital.trigger|p->digital.repeat)&0x10) || ((p->analog.trigger|p->analog.repeat)&1)),
        .down=!!(((p->digital.trigger|p->digital.repeat)&0x40) || ((p->analog.trigger|p->analog.repeat)&4)),.can_open=can_open};
}
/* Start opens STATUS for the pressing player. Slot 0 is the decoded behaviour (STATUS/I<0>). That Start on pad N sends STATUS/I<N> is an ASSUMPTION: the
 * Start handler of beNDMWMdlPlayer::vfunc_38 (0x003d22f0) is not decoded for any pad, and only the shops' payload I<g_messPlayerNo> is recovered.
 * One SUBWND owner exists, so a Start while a menu runs does nothing; the world is frozen for everyone (statusscene.c) and only the owner's pad reaches the menu. */
static int start_status(dw4_hubruntime *h,int32_t slot)
{
    if(!h->status_ui)return 0;   /* a stage without a beNDMWStatusInfo (the practice stage) has no Start menu */
    char payload[16];snprintf(payload,sizeof payload,"STATUS/I<%d>",(int)slot);
    dw4_statusview_context v=status_view(h,slot);
    return dw4_statusui_call(&v,0,"SUBWND",NULL,0,"GENERATE",payload,h->error,sizeof h->error);
}
/* The Square (edge word 0x8000) request of beNDMWMdlPlayer::vfunc_38 (src/unmatched/Gap__Bec__beNDMWMdlPlayer__vfunc_38.cpp, the first test of the non-lobby branch):
 * outside the main lobby, when the sequence is not SQ_JUMP, the key SQ_GUARD is requested. It sits ahead of the Cross branch and is not gated by the panel byte or by SQ_FALL (the Cross
 * request excludes SQ_JUMP and SQ_FALL). The same-frame Cross request is the later write in retail and wins here too (it is issued after this one). A guarding player takes no damage in the
 * enemy-hit chunk. The main lobby check is the combat owner: only the field stages have one and the lobby hub does not. */
static void guard_request(dw4_hubruntime *h,const char *seq,const char *what)
{
    if(!seq || !strcmp(seq,"SQ_JUMP"))return;
    int rq=dw4_lobby_player_request(h->world,"SQ_GUARD");if(rq)fprintf(stderr,"%s: %s\n",what,dw4_modelctrl_error(dw4_lobby_player_model(h->world)));
}
void dw4_hubruntime_input(dw4_hubruntime *h,float x,float y,uint32_t analog,uint32_t held,uint32_t pressed)
{
    if(!h)return;
    if(h->scene){dw4_savescene_input(h->scene,analog,held,pressed);return;}
    if(h->demo)return;   /* the demo takes no input */
    int enabled=dw4_stageinput_slot(&h->input,0)!=4;
    pad_words(h,0,enabled,analog,held,pressed);
    /* R1 technique panel (vfunc_38 sends GENERATEWAZA when the panel byte is clear, outside SQ_JUMP/SQ_FALL; the panel itself then takes the cursor,
     * R1 and Cross). While it owns the frame Cross is not the player's: no swing, no talk probe, no attack-chain hold. Stick Up/Down are the analog
     * bits 1/4, the D-pad 0x10/0x40, with the repeat of the status menus (first 10, next 6 frames). Whether the stick still walks while the panel
     * is open is not measured; walking is left as it is. */
    int panel=0;
    if(h->combat && h->tech && enabled && !h->status_scene.phase) {
        dw4_lobby_control_state control;const char *seq=dw4_modelctrl_sequence(dw4_lobby_player_model(h->world));
        dw4_technique_pad pad=technique_pad(h,0,pressed,!dw4_lobby_control(h->world,&control) && control.player_control && seq && strcmp(seq,"SQ_JUMP") && strcmp(seq,"SQ_FALL"));
        panel=dw4_technique_input(h->tech,0,h->now_ns,&pad);
    }
    /* Field Square (guard_request): issued before the Cross branch, as vfunc_38 orders them. */
    if(h->combat && enabled && !h->status_scene.phase && (pressed&0x8000)) {
        dw4_lobby_control_state control;
        if(!dw4_lobby_control(h->world,&control) && control.player_control)guard_request(h,dw4_modelctrl_sequence(dw4_lobby_player_model(h->world)),"guard request");
    }
    /* Field Cross (beNDMWMdlPlayer::vfunc_38, decoded from the instructions): with player control and outside SQ_JUMP/SQ_FALL request SQ_ATCK1.
     * Measured in retail (2026-10-20, the player's sequence field read while Cross was pressed at fixed gaps): a press during a swing does nothing
     * and a press once the swing sequence is over (about 31 frames for the slash) starts the next swing at any gap from 36 to 260 frames, so
     * the decoded ATDELAY timer (5 x ATTACKDELAY, inferred as 170 frames for ATTACKDELAY 34) does not gate the next swing. The DROPITEM check (loot_cross, src/loot.c) runs first: a pickup that takes the press
     * skips the swing, as in retail; a press nothing takes is recorded below for the tick's pickup step); the spin-stick SQ_ATCK2 and the delay gauge are not ported. */
    int took=enabled && !panel && !h->status_scene.phase && (pressed&0x4000) && loot_cross(h,0);   /* a pickup that takes the press ends the branch: no swing, no loot step press */
    if(h->combat && enabled && !panel && !h->status_scene.phase && (pressed&0x4000) && !took) {
        dw4_lobby_control_state control;const char *seq=dw4_modelctrl_sequence(dw4_lobby_player_model(h->world));
        if(!dw4_lobby_control(h->world,&control) && control.player_control && seq && strcmp(seq,"SQ_JUMP") && strcmp(seq,"SQ_FALL")) {
            int32_t delay=0;dw4_property_number(dw4_playerrecords_get(h->players,"GETPLAYER",0),"ATTACKDELAY",&delay);
            int rq=dw4_lobby_player_request(h->world,"SQ_ATCK1");if(rq)fprintf(stderr,"attack request: %s\n",dw4_modelctrl_error(dw4_lobby_player_model(h->world)));(void)delay;
        }
    }
    if(enabled && !panel && !h->status_scene.phase && (pressed&0x4000) && !took)h->cross[0]=1;   /* the DROPITEM check of the Cross branch (loot labels) */
    dw4_modelctrl_player_pad(dw4_lobby_player_model(h->world),enabled && !h->status_scene.phase?held&~(panel?0x4000u:0u):0);
    dw4_lobby_input(h->world,enabled && !h->status_scene.phase?x:0,enabled && !h->status_scene.phase?y:0);
    dw4_lobby_jump(h->world,enabled && !h->status_scene.phase && (pressed&0x2000));
    dw4_lobby_talk(h->world,enabled && !panel && !h->status_scene.phase && !h->travel.pending && (pressed&0x4000));
    if(enabled && (pressed&8) && !h->status_scene.phase && dw4_lobby_intro_done(h->world) && !h->travel.pending) {
        dw4_lobby_control_state control;
        if(!dw4_lobby_control(h->world,&control) && control.player_control && start_status(h,0))return;
    }
}
/* A co-op player's pad (slots 1-3), the same inputs as the first player's applied to that slot's model: the walk stick, jump (button 0x2000), the R1
 * technique panel, the Square guard request and the Cross swing of beNDMWMdlPlayer::vfunc_38 and the Cross talk probe (whose shooter is this slot: g_messPlayerNo), and Start for STATUS.
 * Every pad is locked while a menu runs (statusscene: the world is frozen) and, as in retail, while a talk holds PLAYER OFCTRL on all players: the slot's own
 * model state (actor.enabled) gates the actions. The pad words reach the menus and selectors of the slot even before the slot is joined in the lobby. */
void dw4_hubruntime_input_slot(dw4_hubruntime *h,unsigned slot,float x,float y,uint32_t analog,uint32_t held,uint32_t pressed)
{
    if(!h || !h->world || h->demo || h->scene || slot==0 || slot>3)return;
    int pad_enabled=dw4_stageinput_slot(&h->input,(int)slot)!=4;
    pad_words(h,slot,pad_enabled,analog,held,pressed);
    if(slot>=h->ninzu || dw4_lobby_select_player(h->world,slot))return;
    int enabled=pad_enabled && !h->status_scene.phase;
    dw4_modelctrl *pm=dw4_lobby_player_model(h->world);
    dw4_modelctrl_actor a={0};dw4_modelctrl_actor_state(pm,&a);
    const char *seq=dw4_modelctrl_sequence(pm);
    int grounded=seq && strcmp(seq,"SQ_JUMP") && strcmp(seq,"SQ_FALL");
    int panel=0;
    if(h->combat && h->tech && enabled) {   /* the slot's own panel: R1 opens it, the cursor and Cross spend only this slot's MP */
        dw4_technique_pad pad=technique_pad(h,slot,pressed,a.enabled && grounded);
        panel=dw4_technique_input(h->tech,(int)slot,h->now_ns,&pad);
    }
    if(h->combat && enabled && a.enabled && (pressed&0x8000))guard_request(h,seq,"slot guard request");   /* the same Square request on this slot's model (the model under dw4_lobby_select_player) */
    int took=enabled && !panel && (pressed&0x4000) && loot_cross(h,slot);   /* the same DROPITEM check: a pickup that takes the press skips the swing */
    if(h->combat && enabled && !panel && a.enabled && (pressed&0x4000) && grounded && !took) {
        int rq=dw4_lobby_player_request(h->world,"SQ_ATCK1");if(rq)fprintf(stderr,"slot %u attack request: %s\n",slot,dw4_modelctrl_error(pm));
    }
    if(enabled && (pressed&0x4000) && !took)h->cross[slot]=1;
    dw4_modelctrl_player_pad(pm,enabled?held&~(panel?0x4000u:0u):0);
    dw4_lobby_input(h->world,enabled?x:0,enabled?y:0);
    dw4_lobby_jump(h->world,enabled && (pressed&0x2000));
    dw4_lobby_talk(h->world,enabled && !panel && !h->travel.pending && (pressed&0x4000));
    int start=enabled && (pressed&8) && h->status_ui && a.enabled && dw4_lobby_intro_done(h->world) && !h->travel.pending;
    dw4_lobby_select_player(h->world,0);
    if(start)start_status(h,(int32_t)slot);
}
void dw4_hubruntime_input_mates(dw4_hubruntime *h,const dw4_input_state mates[3],const dw4_input_state previous[3])
{
    for(unsigned q=0;h && q<3;q++) {
        float x,y;dw4_input_walk_axes(mates+q,&x,&y);
        const uint32_t pressed=(mates[q].cross && !previous[q].cross?0x4000u:0)|(mates[q].circle && !previous[q].circle?0x2000u:0)|(mates[q].square && !previous[q].square?0x8000u:0);
        float mx,my;dw4_input_menu_axes(mates+q,&mx,&my);
        dw4_hubruntime_input_slot(h,q+1,x,y,dw4_pad_directions(mx,my),dw4_input_digital(mates+q),pressed);
    }
}
static int layer(void *user,const char *name)
{
    dw4_hubruntime *h=user;
    for(size_t i=0;i<dw4_stageobjects_layers(h->objects);i++)if(!strcmp(name,dw4_stageobjects_layer(h->objects,i)))return dw4_stageobjects_layer_visible(h->objects,i);
    return 0;
}
int dw4_hubruntime_draw(dw4_hubruntime *h,dw4_fb *fb,const dw4_fefont *font)
{return !h?-1:h->demo?dw4_evodemo_draw(h->demo,fb):h->scene?dw4_savescene_draw(h->scene,fb):dw4_lobby_draw_layers(h->world,fb,0,font,layer,h);}
dw4_lobby *dw4_hubruntime_world(dw4_hubruntime *h){return h?h->world:NULL;}
dw4_playerrecords *dw4_hubruntime_records(dw4_hubruntime *h){return h?h->demo?dw4_evodemo_records(h->demo):h->scene?dw4_savescene_records(h->scene):h->players:NULL;}
const dw4_be_state *dw4_hubruntime_state(const dw4_hubruntime *h){return h?h->demo?dw4_evodemo_state(h->demo):h->scene?dw4_savescene_state(h->scene):&h->state:NULL;}
const dw4_stagetravel *dw4_hubruntime_travel(const dw4_hubruntime *h){return h?&h->travel:NULL;}
void dw4_hubruntime_dev_travel(dw4_hubruntime *h,const char *stage,int32_t point)
{
    if(!h || !stage || strlen(stage)>=sizeof h->travel.destination)return;
    strcpy(h->travel.destination,stage);h->travel.generate_pos=point;h->travel.pending=1;
}
const char *dw4_hubruntime_error(const dw4_hubruntime *h){return h?h->error:"missing hub runtime";}

uint64_t dw4_hubruntime_time(const dw4_hubruntime *h){return h?h->now_ns:0;}
const dw4_stageinput *dw4_hubruntime_input_state(const dw4_hubruntime *h){return h?&h->input:NULL;}

const dw4_dialogue *dw4_hubruntime_dialogue(const dw4_hubruntime *h){return h?h->scene?dw4_savescene_dialogue(h->scene):h->dialogue:NULL;}
const dw4_controllers *dw4_hubruntime_models(const dw4_hubruntime *h){return h?h->demo?dw4_evodemo_models(h->demo):h->models:NULL;}
const dw4_databases *dw4_hubruntime_databases(const dw4_hubruntime *h){return h?h->databases:NULL;}
dw4_shopstock *dw4_hubruntime_shopstock(dw4_hubruntime *h){return h?&h->stock:NULL;}

int dw4_hubruntime_status_active(const dw4_hubruntime *h){return h?h->status_scene.phase:0;}
int32_t dw4_hubruntime_shop_mode(const dw4_hubruntime *h){return h && h->status_scene.phase?h->shop_mode:0;}

int dw4_hubruntime_cancel_travel(dw4_hubruntime *h)
{if(h && (h->scene || h->demo)){snprintf(h->error,sizeof h->error,"%s has no retained source to return to",h->demo?"the digivolution demo":"the save screen");return -1;}
    if(!h || dw4_stagetravel_restore(h->sd,1,&h->travel,h->error,sizeof h->error))return -1;
    dw4_lobby_world_state world;if(dw4_lobby_world_info(h->world,&world))return -1;
    h->travel.generate_pos=world.arrival_point;return 0;}
/* Hand the output device over: lobbies keep it in their audio owner, a save-screen runtime in a placeholder owner. */
static dw4_frontaudio *hub_audio(dw4_hubruntime *h)
{
    if(h->world)return dw4_lobby_audio(h->world);
    if(h->demo)return dw4_evodemo_audio(h->demo);
    if(!h->audio_keep)h->audio_keep=dw4_frontaudio_open_session(h->mount);
    return h->audio_keep;
}
int dw4_hubruntime_adopt_audio(dw4_hubruntime *to,dw4_hubruntime *from_hub,dw4_lobby *from_lobby)
{
    if(!to)return -1;
    dw4_frontaudio *dst=hub_audio(to),*src=from_hub?hub_audio(from_hub):from_lobby?dw4_lobby_audio(from_lobby):NULL;
    return dw4_frontaudio_adopt_device(dst,src);
}
const char *dw4_hubruntime_enable_gpu(dw4_hubruntime *h,int w,int height)
{return !h?NULL:h->demo?dw4_evodemo_enable_gpu(h->demo,w,height):h->scene?dw4_savescene_enable_gpu(h->scene,w,height):dw4_lobby_enable_gpu(h->world,w,height);}
int dw4_hubruntime_run_chunk(dw4_hubruntime *h,const char *name){return h && h->scripts?dw4_scriptengine_run(h->scripts,name):-1;}
int dw4_hubruntime_sd(dw4_hubruntime *h,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{return h && h->sd?dw4_scriptservices_call(h->sd,"sd",a,n,r,error,cap):-1;}
int dw4_hubruntime_enemy_ai_off(dw4_hubruntime *h,const char *name,int32_t slot){return h?dw4_controllers_nearest(h->models,name,slot,NULL,NULL):-1;}
dw4_script_model *dw4_hubruntime_enemy_state(dw4_hubruntime *h,const char *name,int32_t slot){return h?dw4_controllers_state(h->models,name,slot):NULL;}
const dw4_hubruntime_hud *dw4_hubruntime_hud_state(const dw4_hubruntime *h){return h?&h->hud:NULL;}
const dw4_combat_stats *dw4_hubruntime_combat(const dw4_hubruntime *h){return h?dw4_combat_get_stats(h->combat):NULL;}
dw4_combat *dw4_hubruntime_combat_owner(dw4_hubruntime *h){return h?h->combat:NULL;}
const dw4_technique *dw4_hubruntime_technique(const dw4_hubruntime *h){return h?h->tech:NULL;}
const struct dw4_fieldgen *dw4_hubruntime_fieldgen(const dw4_hubruntime *h){return h?h->gen:NULL;}
unsigned dw4_hubruntime_hitland_missing(const dw4_hubruntime *h){return h?h->hitland_missing:0;}
const dw4_savescene *dw4_hubruntime_scene(const dw4_hubruntime *h){return h?h->scene:NULL;}
const dw4_evodemo *dw4_hubruntime_demo(const dw4_hubruntime *h){return h?h->demo:NULL;}

struct dw4_scriptengine *dw4_hubruntime_scripts(const dw4_hubruntime *h){return h?h->scripts:NULL;}

unsigned dw4_hubruntime_pickups(const dw4_hubruntime *h){return h?h->pickups:0;}
