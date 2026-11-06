#include "dw4/savescene.h"
#include "dw4/saveintf.h"
#include "dw4/savectrl.h"
#include "dw4/filelist.h"
#include "dw4/database.h"
#include "dw4/stageobjects.h"
#include "dw4/controllers.h"
#include "dw4/dialogue.h"
#include "dw4/modelview.h"
#include "dw4/stagetravel.h"
#include "dw4/padrepeat.h"
#include "dw4/gl_layer.h"
#include "dw4/playertransactions.h"
#include "dw4/playerinit.h"
#include "dw4/cardshop.h"
#include "dw4/statusstats.h"
#include "dw4/subwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

/* Card result codes the SaveIntf flows branch on (item state 4): 2 OK, 4 no game file (retail
 * FILEFIND on a card without one: LoadIntf2 shows "This memory card (PS2) contains no Digimon
 * World 4 game file."), 5 no card, 7 unformatted, 9/10 write/read failure. The retail numbering
 * beyond these is not recovered. */
enum {R_OK=2,R_NO_FILE=4,R_NO_CARD=5,R_BAD_READ=10,R_BAD_WRITE=9};

struct dw4_savescene {
    dw4_mount *mount;dw4_be_state state;dw4_playerrecords *players;
    dw4_scriptengine *scripts;dw4_scriptservices *sd;dw4_filelist *files;
    dw4_stageobjects *objects;dw4_controllers *models;dw4_dialogue *dialogue;dw4_databases *databases;dw4_modelview *ui;
    dw4_stageinput input;dw4_stagetravel travel;dw4_padrepeat analog,digital;
    uint32_t horizontal,edges,repeats;
    dw4_memcard *card;dw4_savectrl ctrl;dw4_saveintf *intf;
    uint64_t origin_ns,now_ns,ticks;char error[512];
    char pend_model[48];int pend_ram,pending;float pend_pos[3];
    int card_result,card_ready;dw4_memcard_summary summaries[DW4_SAVE_SLOTS];
    int64_t timer_end;
    int exited,exit_pos,card_released;char exit_stage[64];dw4_savescene_kind kind;
    dw4_gl_layer *gpu;int shared_gpu;
    void (*sound)(void *,const char *,const char *);void *sound_user;
    dw4_statusstats stats;                  /* the card album's player panel (StatusTitle01) refresh owner */
};
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static void fail(dw4_savescene *s,const char *what){if(!s->error[0])snprintf(s->error,sizeof s->error,"%s",what);}

/* ---- services the scripts and controllers reach ---- */
static int service_ignore(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{(void)user;(void)method;(void)a;(void)n;(void)error;(void)cap;*r=(dw4_script_value){0};return 0;}
/* CAMERA: the scene is screen-space windows; the authored demo camera "entry" completes at once. */
static int camera(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    (void)user;(void)a;(void)n;(void)error;(void)cap;*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    return strcmp(method,"sd")&&strcmp(method,"querySD")?-1:0;
}
static int gameram(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{return dw4_playerrecords_service(((dw4_savescene *)user)->players,method,a,n,r,error,cap);}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_savescene *s=user;int rc=dw4_playerrecords_call(s->players,method,a,n,r,error,cap);
    if(rc>0)rc=dw4_playertransactions_folder_call(s->players,method,a,n,r,error,cap);
    if(rc<=0)return rc;
    if(!strcmp(method,"PLAYERgetPos")&&!n){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,s->travel.generate_pos,NULL,0};return 0;}
    dw4_scriptservices_scope(s->sd,dw4_scriptengine_scope(s->scripts));
    return dw4_scriptservices_call(s->sd,method,a,n,r,error,cap);
}

/* ---- SaveIntf host (messenger, text, pad, records, card) ---- */
static int sd_call(dw4_savescene *s,const char *query,const char *cat,const char *name,int slot,const char *key,const char *data,dw4_script_value *r)
{
    dw4_script_value a[]={str(cat),name?str(name):(dw4_script_value){0},{DW4_SCRIPT_NUMBER,slot,NULL,0},str(key),{0}};
    dw4_script_value local={0};if(data)a[4]=str(data);
    char error[256]="";
    int rc=dw4_scriptservices_call(s->sd,query,a,data?5:4,r?r:&local,error,sizeof error);
    if(rc){snprintf(s->error,sizeof s->error,"%s %s %s: %.200s",cat,name?name:"",key,error);return -1;}
    return 0;
}
static int q_number(dw4_savescene *s,const char *name,int ram,const char *key,const char *data)
{
    dw4_script_value r={0};if(sd_call(s,"querySD","MODELCTRL",name,ram,key,data,&r))return -1;
    return r.type==DW4_SCRIPT_NUMBER&&r.number!=0;
}
static int h_generate(void *u,const char *model,int ram,const float pos[3])
{
    dw4_savescene *s=u;snprintf(s->pend_model,sizeof s->pend_model,"%s",model);s->pend_ram=ram;memcpy(s->pend_pos,pos,sizeof s->pend_pos);s->pending=1;return 0;
}
/* Retail sends GENERATE(position) and then the sequence; the controllers take "sequence/V<position>" in one GENERATE,
 * and an already active model just receives the sequence (the status windows' rule, statusui.c). */
static void scene_sound(dw4_savescene *s,const char *model,const char *seq)
{
    if(!s->sound)return;
    if(!strncmp(seq,"SQ_",3))seq+=3;
    s->sound(s->sound_user,model,seq);
}
void dw4_savescene_set_sound(dw4_savescene *s,void (*fn)(void *,const char *,const char *),void *user){if(s){s->sound=fn;s->sound_user=user;}}
static int h_sequence(void *u,const char *model,int ram,const char *seq)
{
    dw4_savescene *s=u;scene_sound(s,model,seq);
    if(s->pending&&s->pend_ram==ram&&!strcmp(s->pend_model,model)){
        s->pending=0;
        int active=q_number(s,model,ram,"ISRUN",NULL);if(active<0)return -1;
        if(!active){
            char data[160];snprintf(data,sizeof data,"%s/V<%.9g,%.9g,%.9g>",seq,s->pend_pos[0],s->pend_pos[1],s->pend_pos[2]);
            return sd_call(s,"sd","MODELCTRL",model,ram,"GENERATE",data,NULL);
        }
    }
    return sd_call(s,"sd","MODELCTRL",model,ram,seq,NULL,NULL);
}
static int h_is_seq(void *u,const char *model,int ram,const char *seq){return q_number(u,model,ram,"ISSEQNAME",seq);}
static int h_is_run(void *u,const char *model,int ram){return q_number(u,model,ram,"ISRUN",NULL);}
static int h_text_clear(void *u,const char *group,const char *font)
{
    char data[96];snprintf(data,sizeof data,"%s/%s/CLR",group,font);return sd_call(u,"sd","TEXTCTL",NULL,-1,"SWITCH",data,NULL);
}
static int h_text_set(void *u,const char *group,const char *font,int align,int colour,const char *ascii,const uint16_t *wide)
{
    dw4_savescene *s=u;char data[512];
    static const char *const al[]={"LEFT","CENTER","RIGHT"};
    if(align<0||align>2)return -1;
    snprintf(data,sizeof data,"%s/%s/%s",group,font,al[align]);
    if(sd_call(s,"sd","TEXTCTL",NULL,-1,"ALIGN",data,NULL))return -1;
    if(colour==0||colour==1){snprintf(data,sizeof data,"%s/%s",group,font);if(sd_call(s,"sd","TEXTCTL",NULL,-1,colour==0?"DEFAULTCOLOR":"CANCELCOLOR",data,NULL))return -1;}
    if(wide){
        uint16_t codes[9];memcpy(codes,wide,sizeof codes);size_t n=0;while(n<8&&codes[n])n++;
        if(dw4_dialogue_replace_unknown(s->dialogue,codes,8,0x3F)||dw4_dialogue_set_unicode(s->dialogue,group,font,codes,n)){fail(s,"TEXTSET of a unicode name failed");return -1;}
    }else{
        snprintf(data,sizeof data,"%s/%s/%s",group,font,ascii);
        if(sd_call(s,"sd","TEXTCTL",NULL,-1,"TEXTSET",data,NULL))return -1;
    }
    snprintf(data,sizeof data,"%s/%s/SET",group,font);
    return sd_call(s,"sd","TEXTCTL",NULL,-1,"SWITCH",data,NULL);
}
static int h_text_script(void *u,const char *chunk,int call)
{
    dw4_savescene *s=u;
    if(dw4_scriptengine_text_event(s->scripts,dw4_scriptengine_scope(s->scripts),chunk,call)){
        snprintf(s->error,sizeof s->error,"%s call %d: %.200s",chunk,call,dw4_scriptengine_error(s->scripts));return -1;
    }
    return 0;
}
static int h_pad(void *u,int player,uint32_t *h,uint32_t *e,uint32_t *r)
{
    dw4_savescene *s=u;*h=*e=*r=0;if(player)return 0;
    *h=s->horizontal;*e=s->edges;*r=s->repeats;return 0;
}
static int h_in_use(void *u,int p)
{
    dw4_savescene *s=u;int32_t v;
    return !dw4_property_number(dw4_playerrecords_get(s->players,"GETPLAYER",p),"ISUSE",&v)&&(uint8_t)v==1;
}
static int h_current_to_base(void *u,int p)
{dw4_savescene *s=u;return dw4_playertransactions_current_to_base(s->players,p)?-1:0;}
static int h_summary(void *u,int p,dw4_si_summary *out)
{
    dw4_savescene *s=u;dw4_property_folder *f=dw4_playerrecords_get(s->players,"GETPLAYER",p);int32_t v;
    if(!f)return -1;
    memset(out,0,sizeof *out);
    if(dw4_property_number(f,"ISUSE",&v))return -1;
    out->used=(uint8_t)v;
    if(dw4_property_number(f,"UNIQUE",&v))return -1;
    out->unique=v;
    const char *model=dw4_property_string(f,"DIGIMONNAME");
    if(!model)return -1;
    snprintf(out->model,sizeof out->model,"%s",model);
    dw4_unicode_object name;if(dw4_property_unicode_object(f,"PLAYERNAME",0,&name)||!name.present)return -1;
    for(size_t i=0;i<8&&i<name.count&&name.codes[i];i++)out->name[i]=name.codes[i];
    if(dw4_property_number(f,"LEVEL",&out->level)||dw4_property_number(f,"HP",&out->hp)||dw4_property_number(f,"MHP",&out->mhp)||
       dw4_property_number(f,"MP",&out->mp)||dw4_property_number(f,"MMP",&out->mmp))return -1;
    return 0;
}
static int h_pad_connected(void *u,int p){(void)u;return p==0;}   /* only player 0's pad exists in this port (co-op is out of scope) */
/* GAMERAM GAMEDATAINIT: LoadCtrl2 sends it for each of players 1..3 that is not in use. The records of unused slots are
 * blank from session start; resetting a slot that holds data is not recovered. */
static int h_data_init(void *u,int p)
{
    if(h_in_use(u,p)){fail(u,"GAMERAM GAMEDATAINIT of a player in use is not implemented");return -1;}
    return 0;
}
static int h_start_game(void *u,int p,const char *model)
{(void)p;(void)model;fail(u,"GAMERAM GAMESTART (a new game from the data-select screen) is not implemented");return -1;}
static int h_remove(void *u,int p)
{
    /* GAMEREMOVE of a player without a record is a no-op; removing a live character is not recovered. */
    if(!h_in_use(u,p))return 0;
    fail(u,"GAMERAM GAMEREMOVE of an in-use player (leaving without saving) is not implemented");return -1;
}
static int h_species(void *u,int row,char *out,size_t cap)
{
    dw4_savescene *s=u;const char *n=dw4_databases_shinka_name(s->databases,row);if(!n)return -1;snprintf(out,cap,"%s",n);return 0;
}
static int h_card_request(void *u,int kind,int slot,int player,int area)
{
    dw4_savescene *s=u;char error[160]="";s->card_ready=1;s->card_result=R_OK;
    int present=dw4_memcard_ready(s->card),exists=present&&dw4_memcard_needed(s->card)==0;
    if(!present||slot!=0){s->card_result=R_NO_CARD;return 0;}
    switch(kind){
    case 3:break;                                         /* USE_CHECK */
    case 1:if(!exists)s->card_result=R_NO_FILE;break;    /* FILEFIND */
    case 2:case 6:case 7:break;                           /* FORMAT, GETFREESIZE, REPORT_GAMEDATA: a directory has none of these */
    case 0:if(dw4_memcard_make(s->card,error,sizeof error))s->card_result=R_BAD_WRITE;break;
    case 4:
        if(!exists)s->card_result=R_NO_FILE;
        else if(dw4_memcard_summaries(s->card,s->summaries,error,sizeof error))s->card_result=R_BAD_READ;
        break;
    case 5:{
        int32_t who[DW4_SAVE_SLOTS]={-1,-1,-1,-1};
        if(area<0||area>=DW4_SAVE_SLOTS){s->card_result=R_BAD_WRITE;break;}
        who[area]=player;
        if(dw4_memcard_save(s->card,s->players,who,error,sizeof error))s->card_result=R_BAD_WRITE;
        break;}
    default:snprintf(s->error,sizeof s->error,"unknown SAVEUTILITY request %d",kind);return -1;
    }
    if(error[0])fprintf(stderr,"save scene card: %s\n",error);
    return 0;
}
static int h_card_done(void *u,int *result)
{dw4_savescene *s=u;if(!s->card_ready)return 0;s->card_ready=0;*result=s->card_result;return 1;}
static int h_card_state(void *u,int *present,int *unformatted,dw4_si_card_slot slots[DW4_SI_CARD_SLOTS],int *n)
{
    dw4_savescene *s=u;*present=dw4_memcard_ready(s->card);*unformatted=0;
    memset(slots,0,sizeof *slots*DW4_SI_CARD_SLOTS);slots[0].ok=*present;*n=2;return 0;
}
static int h_card_read(void *u,int slot,dw4_si_summary areas[DW4_SI_SLOTS])
{
    dw4_savescene *s=u;(void)slot;memset(areas,0,sizeof *areas*DW4_SI_SLOTS);
    for(int i=0;i<DW4_SI_SLOTS;i++){
        const dw4_memcard_summary *m=&s->summaries[i];dw4_si_summary *o=&areas[i];
        o->used=m->used;o->unique=m->unique;memcpy(o->model,m->model,sizeof o->model);memcpy(o->name,m->name,sizeof o->name);
        o->level=m->level;o->hp=m->hp;o->mhp=m->mhp;o->mp=m->mp;o->mmp=m->mmp;
    }
    return 0;
}
/* LoadIntf2 commit (title): the chosen card area becomes player 0's character in the scene's own records (the engine rebuilds it from the
 * same slot when it loads the lobby). hostLoad.lua then reads the loaded character's story flags. */
static int h_restore(void *u,int player,int card_slot,int area)
{
    dw4_savescene *s=u;char error[160]="";(void)card_slot;
    if(dw4_memcard_restore(s->card,s->players,s->databases,player,area,error,sizeof error)){snprintf(s->error,sizeof s->error,"loading the character: %s",error);return -1;}
    return 0;
}
/* LoadIntf2 Create: GAMEDATAINIT + GAMESTART for the typed name and the chosen starter, then
 * UNIQUE. The record is built by the native fresh-character owner (dw4_playerrecords_create),
 * which takes the name as text: the NameSel's full-width codes (U+FF01..U+FF5E) become their ASCII
 * forms, U+30FC and U+30FB (the symbol row's long-vowel mark and middle dot) become '-' and '.'.
 * The retail conversion of a name object in GAMESTART is not recovered. */
static int h_create(void *u,int player,const char *model,const uint16_t name[8],int32_t unique)
{
    dw4_savescene *s=u;char text[9]={0},error[256]="";size_t n=0;
    for(int i=0;i<8&&name[i];i++){
        uint16_t c=name[i];char a=c>=0xFF01&&c<=0xFF5E?(char)(c-0xFF00+0x20):c<0x80?(char)c:c==0x30FC?'-':c==0x30FB?'.':0;
        if(a)text[n++]=a;
    }
    if(dw4_playerrecords_create(s->players,s->databases,player,model,text,error,sizeof error)){snprintf(s->error,sizeof s->error,"GAMESTART: %s",error);return -1;}
    if(dw4_property_set_number(dw4_playerrecords_get(s->players,"GETPLAYER",player),"UNIQUE",unique)){fail(s,"GETPLAYER UNIQUE could not be set");return -1;}
    return 0;
}
static int h_send(void *u,const char *model,int ram,const char *key,const char *data){return sd_call(u,"sd","MODELCTRL",model,ram,key,data,NULL);}
static int64_t h_world_ns(void *u){return (int64_t)((dw4_savescene *)u)->now_ns;}
static int h_difficulty_cap(void *u,int player)               /* hostLoad.lua: flag 77 -> 2, else flag 711 -> 1, else 0 */
{
    dw4_savescene *s=u;size_t n=0;
    const uint8_t *f=dw4_property_bytes(dw4_playerrecords_get(s->players,"GETPLAYER",player),"BASE_FLAG",&n);
    if(!f||n<712)return 0;
    return f[77]?2:f[711]?1:0;
}
static int h_timer_start(void *u,const char *name,int64_t ns){dw4_savescene *s=u;(void)name;s->timer_end=(int64_t)s->now_ns+ns;return 0;}
static int h_timer_done(void *u,const char *name){dw4_savescene *s=u;(void)name;return (int64_t)s->now_ns>=s->timer_end;}

/* ---- SaveCtrl host (the SAVECTRL / SAVEUTILITY / COMMONINTF messages of 407120) ---- */
static int c_card_generate(void *u){return dw4_memcard_ready(((dw4_savescene *)u)->card)?1:0;}
/* SAVEUTILITY ISRDY / REMOVE: after REMOVE the receiver shuts down and ISRDY turns false (3f13d0 waits for that). */
static int c_card_ready(void *u){dw4_savescene *s=u;return !s->card_released&&dw4_memcard_ready(s->card);}
static void c_card_remove(void *u){((dw4_savescene *)u)->card_released=1;}
static void c_model_send(void *u,const char *model,const char *key)
{
    dw4_savescene *s=u;
    if(!strcmp(key,"GENERATE")){snprintf(s->pend_model,sizeof s->pend_model,"%s",model);s->pend_ram=0;s->pending=2;return;}  /* generated with its sequence */
    float z[3]={0,0,0};
    if(s->pending==2&&!strcmp(s->pend_model,model)){
        s->pending=0;
        char data[96];snprintf(data,sizeof data,"%s/V<%g,%g,%g>",key,z[0],z[1],z[2]);
        if(sd_call(s,"sd","MODELCTRL",model,0,"GENERATE",data,NULL))return;
        return;
    }
    sd_call(s,"sd","MODELCTRL",model,0,key,NULL,NULL);
}
static int c_is_seq(void *u,const char *model,const char *seq){return q_number(u,model,0,"ISSEQNAME",seq);}
static int c_is_run(void *u,const char *model){return q_number(u,model,0,"ISRUN",NULL);}
static void c_intf_generate(void *u){dw4_savescene *s=u;if(dw4_saveintf_generate(s->intf))fail(s,"SAVEINTF_ALL GENERATE failed");}
static int c_intf_state(void *u){return dw4_saveintf_scene_state(((dw4_savescene *)u)->intf);}
static void c_intf_scan(void *u){dw4_saveintf_scan(((dw4_savescene *)u)->intf);}
static void c_players_close(void *u){dw4_saveintf_close_players(((dw4_savescene *)u)->intf);}
static int c_player_ready(void *u,int p){return dw4_saveintf_player_closed(((dw4_savescene *)u)->intf,p);}
static int c_player_done(void *u,int p){return dw4_saveintf_player_done(((dw4_savescene *)u)->intf,p);}
static void c_intf_select_data(void *u){dw4_savescene *s=u;if(dw4_saveintf_select_data(s->intf))fail(s,dw4_saveintf_error(s->intf));}
static void c_publish_players(void *u,int count,const int done[DW4_SAVECTRL_PLAYERS])
{
    dw4_savescene *s=u;(void)done;
    if(dw4_property_set_number(dw4_playerrecords_get(s->players,"GETCOMMON",0),"NINZU",count))fail(s,"GETCOMMON NINZU could not be set");
}
static void c_go(void *u,const char *stage,int pos){dw4_savescene *s=u;snprintf(s->exit_stage,sizeof s->exit_stage,"%s",stage);s->exit_pos=pos;s->exited=1;}
static void c_self_generate(void *u){dw4_savescene *s=u;if(s->kind==DW4_SCENE_SAVE)dw4_savectrl_generate(&s->ctrl);}   /* LoadCtrl2 waits for the pack's LOADCTRL2 GENERATE */
/* The pack's first chunk sends LOADCTRL2 GENERATE (sd, no integers = hub mode 0): beNDMWLoadCtrl2 vfunc_34 (3f2490)
 * builds the controller and sends GAMEDATAINIT for every player 1..3 that is not in use. */
static int loadctrl2(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_savescene *s=user;*r=(dw4_script_value){0};
    if(strcmp(method,"sd")&&strcmp(method,"querySD")){snprintf(error,cap,"LOADCTRL2 has no method %s",method);return -1;}
    if(!strcmp(method,"querySD"))return 0;
    if(n<4||a[3].type!=DW4_SCRIPT_STRING||strcmp(a[3].string,"GENERATE")){snprintf(error,cap,"LOADCTRL2 supports only GENERATE");return -1;}
    if(s->ctrl.built)return 0;
    if(dw4_loadctrl_generate(&s->ctrl,0)){snprintf(error,cap,"LOADCTRL2 GENERATE failed");return -1;}
    for(int p=1;p<DW4_SI_PLAYERS;p++)if(!h_in_use(s,p)&&h_data_init(s,p)){snprintf(error,cap,"%s",s->error);return -1;}
    return 0;
}

/* ---- SUBWND CARD (the stagIS11 scene): mode 10's window tree over the scene's own owners ---- */
static int card_prepare(void *user,int32_t mode,int32_t player,dw4_menu_window **out,char *error,size_t cap)
{
    dw4_savescene *s=user;
    if(mode!=10 || player!=0){snprintf(error,cap,"the card scene serves only SUBWND CARD for player zero");return -1;}
    s->stats=(dw4_statusstats){.players=s->players,.sd=s->sd,.dialogue=s->dialogue,.name=dw4_databases_shinka_name,.database=s->databases};
    dw4_cardshop_context c={.view={.sd=s->sd,.engine=s->scripts,.players=s->players,.scope=1,.player=player},.databases=s->databases,
        .random=&s->state.random,.refresh=dw4_statusstats_refresh,.user=&s->stats};
    *out=dw4_cardshop_window_open(&c);return *out?0:-1;
}
static int card_begin(void *user,int32_t mode,int32_t player,char *error,size_t cap){(void)user;(void)mode;(void)player;(void)error;(void)cap;return 0;}
/* The CARD completion (SUBWND lifecycle): STAGECTL ISRESETSTART answers zero here, so PLAYERPOINT SETGENERATEPOS 4 and
 * NEXTSTAGE stagML12 follow, and the scene reports them as its exit. */
static int card_end(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{
    dw4_savescene *s=user;(void)mode;(void)player;(void)error;(void)cap;
    snprintf(s->exit_stage,sizeof s->exit_stage,"stagML12");s->exit_pos=4;s->exited=1;return 0;
}

dw4_savescene *dw4_savescene_open(dw4_mount *mount,const dw4_savescene_source *source,char *error,size_t cap)
{
    dw4_savescene *s=calloc(1,sizeof *s);if(!s)return NULL;
    const char *step="session snapshot";s->mount=mount;
    if(!mount||!source||!source->state||(source->kind!=DW4_SCENE_CARD&&!source->card)||!(s->players=dw4_playerrecords_snapshot(source->records)))goto fail;
    s->state=*source->state;s->card=source->card;s->origin_ns=s->now_ns=source->world_ns;s->kind=source->kind;
    dw4_padrepeat_init(&s->analog);dw4_padrepeat_init(&s->digital);s->travel.input=&s->input;s->travel.generate_pos=-1;
    step="script engine";
    s->sd=dw4_scriptservices_open();if(!s->sd)goto fail;
    s->scripts=dw4_scriptengine_open(&s->state,binding,s);s->files=dw4_filelist_open(mount);if(!s->scripts||!s->files)goto fail;
    dw4_scriptengine_filelist(s->scripts,s->files);dw4_scriptengine_record_flags(s->scripts,1);
    if(!dw4_scriptservices_register(s->sd,0,"GAMERAM",NULL,-1,1,gameram,s)||
       !dw4_scriptservices_register(s->sd,0,"SOUND",NULL,-1,1,service_ignore,s)||
       !dw4_scriptservices_register(s->sd,0,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,&s->travel)||
       !dw4_scriptservices_register(s->sd,0,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,&s->travel))goto fail;
    step="interface scene pack and native objects";
    s->objects=dw4_stageobjects_open();if(!s->objects)goto fail;
    if(dw4_filelist_begin(s->files,s->scripts,s->kind==DW4_SCENE_LOAD||s->kind==DW4_SCENE_TITLE?"stagIS13":s->kind==DW4_SCENE_CARD?"stagIS11":"stagIS12",1)||dw4_filelist_shared(s->files)||
       dw4_filelist_route_assets(s->files,dw4_stageobjects_route,s->objects)||
       dw4_filelist_bind_layers(s->files,dw4_stageobjects_bind_layers,s->objects)||
       dw4_stageobjects_publish(s->objects,s->sd,1))goto fail;
    step="database/model/dialogue owners";
    s->databases=dw4_databases_open(s->objects,s->error,sizeof s->error);
    if(!s->databases||dw4_databases_publish(s->databases,s->sd,1))goto fail;
    s->models=dw4_controllers_open(s->sd,1,s->objects,NULL,0,&s->state.random,&s->state.action_rhythm,s->scripts);
    s->dialogue=dw4_dialogue_open(s->sd,1,s->objects);if(!s->models||!s->dialogue)goto fail;
    dw4_controllers_sample(s->models,(int64_t)s->origin_ns);
    if(dw4_scriptservices_tick(s->sd,s->origin_ns))goto fail;
    s->ui=dw4_modelview_open_scene(s->objects,s->models,s->error,sizeof s->error);if(!s->ui)goto fail;
    step="scene services";
    if(!dw4_scriptservices_register(s->sd,1,"CAMERA",NULL,-1,1,camera,s)||
       !dw4_scriptservices_register(s->sd,1,"SWITCHCTRL",NULL,-1,1,dw4_stageobjects_switch_service,s->objects)||
       ((s->kind==DW4_SCENE_LOAD||s->kind==DW4_SCENE_TITLE)&&!dw4_scriptservices_register(s->sd,1,"LOADCTRL2",NULL,-1,1,loadctrl2,s))||
       dw4_scriptservices_category(s->sd,"LAYERCTL")||dw4_scriptservices_category(s->sd,"ENEMY")||dw4_scriptservices_category(s->sd,"PLAYER"))goto fail;
    if(s->kind==DW4_SCENE_CARD){
        step="SUBWND CARD owner";
        dw4_subwindow_factory factory={.prepare=card_prepare,.begin=card_begin,.end=card_end,.user=s};
        if(dw4_subwindows_factory(dw4_dialogue_subwindows(s->dialogue),&factory))goto fail;
    }else{
    step="native save controllers";
    {
        int joined[DW4_SI_PLAYERS]={1,0,0,0};
        dw4_saveintf_host h={.user=s,.model_generate=h_generate,.model_sequence=h_sequence,.model_is_sequence=h_is_seq,.model_is_running=h_is_run,
            .text_clear=h_text_clear,.text_set=h_text_set,.text_script=h_text_script,.pad=h_pad,.player_in_use=h_in_use,
            .player_current_to_base=h_current_to_base,.player_summary=h_summary,.player_start_game=h_start_game,.player_remove=h_remove,
            .species_name=h_species,.card_request=h_card_request,.card_done=h_card_done,.card_state=h_card_state,.card_read=h_card_read,
            .timer_start=h_timer_start,.timer_done=h_timer_done,.pad_connected=h_pad_connected,.player_data_init=h_data_init,
            .player_restore=h_restore,.difficulty_cap=h_difficulty_cap,.player_create=h_create,.model_send=h_send,.world_ns=h_world_ns};
        s->intf=s->kind==DW4_SCENE_TITLE?dw4_loadintf_open_title(&h):s->kind==DW4_SCENE_LOAD?dw4_loadintf_open(&h,joined):dw4_saveintf_open(&h,0,joined);
        if(!s->intf)goto fail;
    }
    }
    step="original start/first";
    if(dw4_filelist_start(s->files)||dw4_filelist_first(s->files))goto fail;
    return s;
fail:
    snprintf(error,cap,"%s: %.120s; %.180s; %.120s",step,s->error,s->files?dw4_filelist_error(s->files):"",
        s->scripts?dw4_scriptengine_error(s->scripts):"");
    dw4_savescene_close(s);return NULL;
}
void dw4_savescene_close(dw4_savescene *s)
{
    if(!s)return;
    if(s->scripts&&s->sd)dw4_scriptengine_remove_all(s->scripts,s->sd);
    dw4_modelview_forget_gpu(s->ui,s->gpu);dw4_dialogue_forget_gpu(s->dialogue,s->gpu);   /* the layer may be the engine's, and these pixels are freed below */
    dw4_saveintf_close(s->intf);dw4_modelview_close(s->ui);dw4_dialogue_close(s->dialogue);dw4_controllers_close(s->models);
    dw4_databases_close(s->databases);dw4_stageobjects_close(s->objects);dw4_filelist_close(s->files);
    dw4_scriptengine_close(s->scripts);dw4_scriptservices_close(s->sd);dw4_playerrecords_close(s->players);
    dw4_gl_layer_close(s->gpu);free(s);
}
void dw4_savescene_input(dw4_savescene *s,uint32_t analog,uint32_t held,uint32_t pressed)
{
    if(!s)return;
    dw4_padrepeat_tick(&s->analog,analog);dw4_padrepeat_tick(&s->digital,held|pressed);
    s->horizontal=s->analog.trigger|s->analog.repeat;s->edges=s->digital.trigger;s->repeats=s->digital.repeat;
    dw4_dialogue_input(s->dialogue,0,analog,held,pressed);
}
int dw4_savescene_tick(dw4_savescene *s,uint64_t ns)
{
    if(!s||s->error[0])return -1;
    if(ns<s->origin_ns||ns>INT64_MAX||(s->ticks&&ns<=s->now_ns)){fail(s,"save scene tick requires the next admitted session clock sample");return -1;}
    s->now_ns=ns;dw4_controllers_sample(s->models,(int64_t)ns);
    if(dw4_scriptservices_tick(s->sd,ns)||dw4_scriptengine_tick(s->scripts)||dw4_controllers_tick(s->models,(int64_t)ns)||dw4_dialogue_tick(s->dialogue)){
        snprintf(s->error,sizeof s->error,"%.120s; %.120s; %.120s; %.120s",dw4_scriptengine_error(s->scripts),dw4_scriptservices_error(s->sd),
            dw4_controllers_error(s->models),dw4_dialogue_error(s->dialogue));return -1;
    }
    if(!s->exited && s->kind!=DW4_SCENE_CARD){
        dw4_savectrl_host ch={.user=s,.card_generate=c_card_generate,.card_ready=c_card_ready,.card_remove=c_card_remove,.model_send=c_model_send,
            .model_is_sequence=c_is_seq,.model_is_running=c_is_run,.intf_generate=c_intf_generate,.intf_state=c_intf_state,.intf_scan=c_intf_scan,
            .players_close=c_players_close,.player_ready=c_player_ready,.player_done=c_player_done,.intf_select_data=c_intf_select_data,
            .publish_players=c_publish_players,.go=c_go,.self_generate=c_self_generate};
        dw4_savectrl_update(&s->ctrl,&ch);
        if(s->error[0])return -1;
        if(s->ctrl.built&&dw4_saveintf_generate(s->intf)==0&&s->ctrl.phase>=2&&s->ctrl.sub>=3){
            if(dw4_saveintf_update(s->intf)){snprintf(s->error,sizeof s->error,"%s",dw4_saveintf_error(s->intf));return -1;}
        }
    }
    s->ticks++;return s->error[0]?-1:0;
}
const char *dw4_savescene_enable_gpu(dw4_savescene *s,int w,int h)
{
    if(!s)return NULL;
    dw4_gl_layer_close(s->gpu);s->gpu=dw4_gl_layer_open(w,h);
    return s->gpu?dw4_gl_layer_info(s->gpu):NULL;
}
const char *dw4_savescene_use_gpu(dw4_savescene *s,dw4_gl_layer *layer)
{
    if(!s)return NULL;
    dw4_gl_layer_close(s->gpu);s->gpu=dw4_gl_layer_share(layer);s->shared_gpu=s->gpu!=NULL;
    return s->gpu?dw4_gl_layer_info(s->gpu):NULL;
}
int dw4_savescene_title_state(const dw4_savescene *s,int *card_slot,int *area,int *difficulty)
{
    if(!s||s->kind!=DW4_SCENE_TITLE)return -1;
    return dw4_saveintf_title_state(s->intf,card_slot,area,difficulty);
}
uint64_t dw4_savescene_ticks(const dw4_savescene *s){return s?s->ticks:0;}
int dw4_savescene_warm(dw4_savescene *s,uint64_t first_ns,uint64_t step_ns,int ticks)
{
    int used=0;uint64_t ns=first_ns;
    for(;used<ticks;used++,ns+=step_ns){
        if(dw4_savescene_tick(s,ns))return -1;
        if(s->ctrl.phase>=2&&s->ctrl.sub>=3&&(s->kind!=DW4_SCENE_TITLE||dw4_saveintf_title_ready(s->intf)))break;   /* the title: base panels and Create/Call window open */
    }
    return used;
}
int dw4_savescene_draw(dw4_savescene *s,dw4_fb *fb)
{
    if(!s||!fb)return -1;
    const dw4_ui_draw *draw;size_t n;char error[256]="";
    if(!s->shared_gpu)memset(fb->rgba,0,(size_t)fb->w*fb->h*4);   /* a shared layer (the engine's resident frame) is cleared by the caller */
    if(dw4_modelview_draw(s->ui,fb->w,fb->h,&draw,&n,error,sizeof error)){snprintf(s->error,sizeof s->error,"%s",error);return -1;}
    if(getenv("DW4_SAVESCENE_DEBUG"))fprintf(stderr,"save scene: %zu model draws\n",n);
    if(!s->gpu)dw4_render_zbuf_clear(fb);   /* only the CPU UI path tests it */
    dw4_gl_layer_ui_or_cpu(&s->gpu,fb,draw,(int)n,8);
    if(dw4_dialogue_draw(s->dialogue,fb->w,fb->h,&draw,&n))return -1;
    dw4_gl_layer_ui_or_cpu(&s->gpu,fb,draw,(int)n,8);
    return (int)n;
}
const char *dw4_savescene_error(const dw4_savescene *s){return s?s->error:"missing save scene";}
int dw4_savescene_exit(const dw4_savescene *s,char *stage,size_t cap,int *generate_pos)
{
    if(!s||!s->exited)return 0;
    snprintf(stage,cap,"%s",s->exit_stage);if(generate_pos)*generate_pos=s->exit_pos;return 1;
}
dw4_playerrecords *dw4_savescene_records(dw4_savescene *s){return s?s->players:NULL;}
const dw4_be_state *dw4_savescene_state(const dw4_savescene *s){return s?&s->state:NULL;}
const struct dw4_saveintf *dw4_savescene_intf(const dw4_savescene *s){return s?s->intf:NULL;}
const struct dw4_dialogue *dw4_savescene_dialogue(const dw4_savescene *s){return s?s->dialogue:NULL;}
const struct dw4_controllers *dw4_savescene_models(const dw4_savescene *s){return s?s->models:NULL;}
const struct dw4_databases *dw4_savescene_databases(const dw4_savescene *s){return s?s->databases:NULL;}
int dw4_savescene_card_state(const dw4_savescene *s,int *primary,int *main,int *sub)
{
    if(!s||s->kind!=DW4_SCENE_CARD)return -1;
    dw4_subwindows *w=dw4_dialogue_subwindows(s->dialogue);
    const dw4_menu_window *root=dw4_subwindows_root(w,0);
    dw4_cardshop_state st;if(!root||dw4_cardshop_window_state(root,&st))return -1;
    *primary=st.state;*main=st.main;*sub=st.sub;return 0;
}
void dw4_savescene_control(const dw4_savescene *s,int *phase,int *sub,int *subsub){*phase=s->ctrl.phase;*sub=s->ctrl.sub;*subsub=s->ctrl.subsub;}
