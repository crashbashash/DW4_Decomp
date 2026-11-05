/* A called character's Main Lobby arrival through the real boot: title -> Call Digimon -> card chooser -> data -> log-in -> START
 * -> stagML11 with the original start/first scripts. The character on the synthesized card has already seen the greeting (story
 * flags 501/508) and has flag 2 (Terminal stage start GENERATEs the guide n_digilff RAM 2 for flag 2 with flag 20 clear), so
 * first.lua skips its greeting branch and only queues the guide's SQ_WALKON 25, the fade-in SQ_BLIN60 5, the player's SQ_ENTR
 * and the delayed 120 control hand-off. Checks (lobby ticks):
 *   - no greeting and no demo camera; the other two Digi-Elves stand at their stations from the first tick;
 *   - the guide is drawn from the first tick, starts its authored WALKON patrol, moves and stays on the Terminal floor;
 *   - the player entry rings start with the script's SQ_ENTR (about half a second after the fade begins), not 180 ticks in;
 *   - the HUD/control hand-off keeps its delay-120 tick;
 *   - talking (the first-Terminal Cross probe over the hub's HITPLAYERTALK receivers): a probe before the hand-off claims nothing;
 *     standing in front of the station elf n_digilfm[0] and pressing Cross hits exactly one receiver and opens its original talk
 *     (SQ_TALK, TALKFONT text); Cross through the pages gives control back; the conversation then repeats.
 * Headless (SDL dummy video/audio); uses a throw-away XDG data/config directory. */
#define _XOPEN_SOURCE 700
#include "dw4/engine.h"
#include "dw4/lobby.h"
#include "dw4/controllers.h"
#include "dw4/modelctrl.h"
#include "dw4/stageobjects.h"
#include "dw4/object.h"
#include "dw4/audio.h"
#include "dw4/options.h"
#pragma GCC diagnostic ignored "-Wunused-function"  /* shared helpers this test does not use */
#include "savetest.h"
#include <limits.h>
#include <ftw.h>
static int rm_entry(const char *path,const struct stat *st,int type,struct FTW *f){(void)st;(void)type;(void)f;return remove(path);}
static void rm_tree(const char *dir){nftw(dir,rm_entry,16,FTW_DEPTH|FTW_PHYS);}
#ifdef DW4_ENABLE_SDL2
static dw4_controllers *models;
void __real_dw4_controllers_sample(dw4_controllers *,int64_t);
void __wrap_dw4_controllers_sample(dw4_controllers *m,int64_t ns){__real_dw4_controllers_sample(m,ns);models=m;}

static const dw4_modelctrl *npc(const char *name,int32_t want)
{
    for(size_t i=0;models && i<dw4_controllers_count(models);i++) {
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&slot);
        if(m && slot==want && !strcmp(dw4_stageobject_name(info),name))return m;
    }
    return NULL;
}
static const dw4_dialogue *dialogue;
void __real_dw4_lobby_dialogue(dw4_lobby *,dw4_dialogue *);
void __wrap_dw4_lobby_dialogue(dw4_lobby *l,dw4_dialogue *d){if(d)dialogue=d;__real_dw4_lobby_dialogue(l,d);}
static int inject_cross;   /* one Cross for the message pages, added to the engine's (idle) pad on the next dialogue input */
void __real_dw4_dialogue_input(dw4_dialogue *,unsigned,uint32_t,uint32_t,uint32_t);
void __wrap_dw4_dialogue_input(dw4_dialogue *d,unsigned player,uint32_t analog,uint32_t held,uint32_t pressed)
{if(inject_cross){pressed|=0x4000;inject_cross=0;}__real_dw4_dialogue_input(d,player,analog,held,pressed);}
enum{TALK_PLACE=640,TALK_FIRST=670};
static unsigned talks,cycles,quiet,early_hits,saw_sq_talk,talk_text,forced,talk_ticks;
static int in_talk;
static unsigned ticks,fade_tick=UINT_MAX,ring_tick=UINT_MAX,hud_tick=UINT_MAX,walk_tick=UINT_MAX;
static float guide_start[3],guide_min[3]={1e9f,1e9f,1e9f},guide_max[3]={-1e9f,-1e9f,-1e9f},guide_travel;
static void station(const char *name,int32_t slot,float x,float y,float z,float yaw)
{
    const dw4_modelctrl *m=npc(name,slot);assert(m && dw4_modelctrl_active(m) && dw4_modelctrl_drawable(m));
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(m,&a);
    assert(fabsf(a.position[0]-x)<1e-3f && fabsf(a.position[1]-y)<1e-3f && fabsf(a.position[2]-z)<1e-3f &&
           fabsf(remainderf(a.rotation[1]-yaw,360))<1e-3f);
}
void __real_dw4_lobby_tick(dw4_lobby *,int);
void __wrap_dw4_lobby_tick(dw4_lobby *l,int pressed)
{
    /* Talk scenario, applied before the tick it concerns (overriding the engine's own probe for this frame). */
    unsigned next=ticks;forced=0;
    if(next==60){dw4_lobby_talk(l,1);forced=1;}   /* before the control hand-off: must claim nothing */
    if(next==TALK_PLACE) {
        const dw4_modelctrl *m=npc("n_digilfm",0);dw4_modelctrl_actor a;dw4_modelctrl_actor_state(m,&a);
        float r=a.rotation[1]*0.0174533f;
        assert(!dw4_lobby_place_player(l,a.position[0]+12*sinf(r),a.position[1],a.position[2]+12*cosf(r),a.rotation[1]+180));
    }
    if(next==TALK_FIRST || (cycles==1 && talks==1 && quiet>=30)) {
        dw4_lobby_control_state before;assert(!dw4_lobby_control(l,&before) && before.player_control);
        dw4_lobby_talk(l,1);forced=2;
    }
    __real_dw4_lobby_tick(l,pressed);
    dw4_lobby_presentation_state p;dw4_lobby_control_state c;
    assert(!dw4_lobby_presentation(l,&p) && !dw4_lobby_control(l,&c));
    unsigned t=p.tick;ticks=t+1;
    if(forced==1)early_hits+=dw4_lobby_talk_result(l)!=0;
    if(forced==2){assert(dw4_lobby_talk_result(l)==1);talks++;in_talk=1;quiet=0;talk_ticks=0;}
    if(in_talk) {
        const char *seq=dw4_modelctrl_sequence(npc("n_digilfm",0));saw_sq_talk|=seq && !strcmp(seq,"SQ_TALK");
        int open=dw4_dialogue_talk_open(dialogue);talk_text|=open;
        if(open && !(t%20))inject_cross=1;
        if(talk_text && !open && c.player_control){in_talk=0;cycles++;talk_text=0;}
        else assert(++talk_ticks<900);   /* the talk opens and closes again with control back */
    } else if(c.player_control)quiet++;
    static float dark=1;  /* the fade-in starts on the first lit tick after the black SQ_BLOUT00 */
    if(fade_tick==UINT_MAX && !dark && p.screen_alpha>0)fade_tick=t;
    dark=p.screen_alpha;
    if(ring_tick==UINT_MAX && p.arrival_mask)ring_tick=t;
    if(hud_tick==UINT_MAX && c.hud)hud_tick=t;
    assert(c.box_camera);   /* no greeting demo camera */
    if(t<=600 && !(t%60)) {
        station("n_digilfm",0,258.187f,40,174,180);
        station("n_digilff",3,240,40,-150,0);
    }
    const dw4_modelctrl *guide=npc("n_digilff",2);
    assert(guide && dw4_modelctrl_active(guide) && dw4_modelctrl_drawable(guide));
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(guide,&a);
    if(!t){memcpy(guide_start,a.position,sizeof guide_start);assert(guide_start[0]==60 && guide_start[1]==10 && guide_start[2]==-10);}
    if(walk_tick==UINT_MAX && a.motion && !strcmp(a.motion,"walk01"))walk_tick=t;
    for(unsigned k=0;k<3;k++){guide_min[k]=fminf(guide_min[k],a.position[k]);guide_max[k]=fmaxf(guide_max[k],a.position[k]);}
    float dx=a.position[0]-guide_start[0],dz=a.position[2]-guide_start[2];guide_travel=fmaxf(guide_travel,sqrtf(dx*dx+dz*dz));
}
#endif

int main(int argc,char **argv)
{
#ifndef DW4_ENABLE_SDL2
    (void)argc;(void)argv;puts("called arrival: SDL unavailable, skipped");return 0;
#else
    const char *roms=argc>1?argv[1]:"../../local/extracted";
    char home[]="/tmp/dw4-called-arrival-XXXXXX";assert(mkdtemp(home));
    assert(!setenv("XDG_DATA_HOME",home,1) && !setenv("XDG_CONFIG_HOME",home,1));
    {   /* The card: one p_agumon in data area 0 with flags 2, 501 and 508. */
        dw4_mount mount;assert(!dw4_mount_open(&mount,roms));
        dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
        struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
        assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
        dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
        dw4_scriptengine_filelist(e,f);
        assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
        dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
        assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));
        assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
        char error[512],dir[4096];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
        assert(!dw4_memcard_default_directory(dir,sizeof dir,1) && !strncmp(dir,home,strlen(home)));
        dw4_memcard *card=dw4_memcard_open(dir);assert(card && dw4_memcard_ready(card));
        dw4_playerrecords *a=dw4_playerrecords_open();assert(a);
        assert(!dw4_playerrecords_create(a,db,0,"p_agumon","Agu",error,sizeof error));
        dw4_property_folder *fa=dw4_playerrecords_get(a,"GETPLAYER",0);size_t n=0;
        const uint8_t *old=dw4_property_bytes(fa,"BASE_FLAG",&n);assert(old && n==1024);
        uint8_t flags[1024];memcpy(flags,old,sizeof flags);flags[2]=flags[501]=flags[508]=1;flags[20]=0;
        assert(!dw4_property_set_bytes(fa,"BASE_FLAG",flags,sizeof flags));
        int32_t map[DW4_SAVE_SLOTS]={0,-1,-1,-1};assert(!dw4_memcard_save(card,a,map,error,sizeof error));
        dw4_playerrecords_close(a);dw4_memcard_close(card);
        dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_filelist_close(f);dw4_scriptengine_close(e);
        dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    }
    dw4_audio_set_muted(1);assert(dw4_options_init(0)>=0);
    char out[4096];snprintf(out,sizeof out,"%s/frames",home);assert(!mkdir(out,0700));
    assert(!setenv("DW4_SHOT_FRAMES","0",1));
    dw4_engine_opts o={.roms=roms,.frames=2800,.w=160,.h=112,.window=1,.headless=1,.software=1,.out_dir=out};
    char stage[64];
    int rc=dw4_engine_boot(&o,"5:cross,200:start,260:cross,400:down,440:cross,600:cross,760:cross,860:cross,980:start",stage,sizeof stage);
    fprintf(stderr,"called arrival: rc %d ticks %u fade %u ring %u hud %u guide walk %u travel %.1f x %.1f..%.1f y %.1f..%.1f z %.1f..%.1f\n",
        rc,ticks,fade_tick,ring_tick,hud_tick,walk_tick,guide_travel,guide_min[0],guide_max[0],guide_min[1],guide_max[1],guide_min[2],guide_max[2]);
    fprintf(stderr,"called arrival talk: early hits %u, talks %u, cycles %u, SQ_TALK %u\n",early_hits,talks,cycles,saw_sq_talk);
    rm_tree(home);
    assert(rc>=0 && ticks>=500);
    /* first.lua: SQ_BLIN60 at 5, SQ_ENTR at 30 and the hand-off at 120, each queued one tick after start. */
    assert(fade_tick>=5 && fade_tick<=7);
    assert(ring_tick>fade_tick && ring_tick-fade_tick>=20 && ring_tick-fade_tick<=35);
    assert(hud_tick==121);
    /* SQ_WALKON 25, then the authored MAP01 route (X 130/20/60, Z -35/-35/-10) on the Terminal floor. */
    assert(walk_tick>=25 && walk_tick<=40);
    assert(guide_travel>20 && fabsf(guide_min[1]-10)<.5f && fabsf(guide_max[1]-10)<.5f);
    assert(guide_min[0]>=0 && guide_max[0]<=140 && guide_min[2]>=-60 && guide_max[2]<=20);
    assert(!early_hits && talks==2 && cycles==2 && saw_sq_talk);
    puts("called arrival: no greeting; guide patrols from SQ_WALKON 25; stations held; entry rings at SQ_ENTR; HUD at 121; "
         "the station elf talk opens, gives control back and repeats");
    return 0;
#endif
}
