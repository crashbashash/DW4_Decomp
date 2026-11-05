#define _POSIX_C_SOURCE 200809L
#include "dw4/engine.h"
#include "dw4/window.h"
#include "dw4/simulation.h"
#include "dw4/frontend.h"
#include "dw4/statusscene.h"
#include "dw4/lobby.h"
#include "dw4/stageinput.h"
#include "dw4/statusmenu.h"
#include "dw4/modelview.h"
#include "dw4/gpupolicy.h"
#include "dw4/statusdetail.h"
#include "dw4/statusdisk.h"
#include "dw4/statusflag.h"
#include "dw4/statusbit.h"
#include "dw4/frontaudio.h"
#include "dw4/audio.h"
#include "dw4/gl_layer.h"
#include "dw4/png.h"
#include "dw4/controllers.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#ifdef DW4_ENABLE_SDL2
#include <SDL.h>
static SDL_Joystick *pad;
static int device=-1;
static unsigned polls,scene_ticks,opens,closes,swaps;
static unsigned focus_end,focus_checks,focus_presentations,focus_changed;
static int focus_only;static int64_t focus_ns;static uint64_t focus_hash;
static int lobby_parity;static dw4_lobby *parity_lobby;static dw4_playerrecords *parity_players;
static int portal_edge;static unsigned edge_first_fall,edge_first_land,edge_second_fall,edge_second_land;
static int edge_stairs_placed;
static const char *parity_capture;
static unsigned parity_phase,parity_jump,parity_fall,parity_land,parity_loops;static float parity_floor;
static int64_t parity_gate_time;
int __real_dw4_playerhealth_restore(dw4_playerrecords *,int32_t,dw4_playerhealth *,char *,size_t);
int __wrap_dw4_playerhealth_restore(dw4_playerrecords *p,int32_t i,dw4_playerhealth *h,char *e,size_t n)
{parity_players=p;return __real_dw4_playerhealth_restore(p,i,h,e,n);}
static unsigned manual_poll;static int manual_checked;static int64_t manual_ns;
static dw4_audio *focus_audio;static double focus_audio_seconds;
dw4_audio *__real_dw4_audio_open(void);
dw4_audio *__wrap_dw4_audio_open(void)
{focus_audio=__real_dw4_audio_open();return focus_audio;}
void __real_dw4_audio_close(dw4_audio *a);
void __wrap_dw4_audio_close(dw4_audio *a)
{if(focus_audio==a)focus_audio=NULL;__real_dw4_audio_close(a);}
int __real_dw4_window_present(dw4_window *,const dw4_fb *);
int __wrap_dw4_window_present(dw4_window *w,const dw4_fb *fb)
{
    if(focus_end){
        uint64_t hash=1469598103934665603ULL;
        for(size_t i=0;i<(size_t)fb->w*fb->h*4;i++)hash=(hash^fb->rgba[i])*1099511628211ULL;
        if(focus_presentations && hash!=focus_hash)focus_changed++;
        focus_hash=hash;focus_presentations++;
    }
    return __real_dw4_window_present(w,fb);
}
static int gpu_check,gpu_fail,gpu_failed;static unsigned gpu_calls;static double gpu_ms,model_ms;static unsigned model_calls;
static double measure_ms(void)
{struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec*1000.0+t.tv_nsec/1e6;}
int __real_dw4_modelview_draw(dw4_modelview *,unsigned,unsigned,const dw4_ui_draw **,size_t *,char *,size_t);
int __wrap_dw4_modelview_draw(dw4_modelview *v,unsigned w,unsigned h,const dw4_ui_draw **d,size_t *n,char *error,size_t cap)
{double start=measure_ms();int rc=__real_dw4_modelview_draw(v,w,h,d,n,error,cap);model_ms+=measure_ms()-start;model_calls++;return rc;}
int __real_dw4_gl_layer_ui(dw4_gl_layer *,dw4_fb *,const dw4_ui_draw *,int);
int __wrap_dw4_gl_layer_ui(dw4_gl_layer *g,dw4_fb *fb,const dw4_ui_draw *draw,int n)
{gpu_calls++;if(gpu_fail && model_calls && !gpu_failed){gpu_failed=1;return -1;}
 double start=measure_ms();int rc=__real_dw4_gl_layer_ui(g,fb,draw,n);gpu_ms+=measure_ms()-start;if(gpu_check)assert(g && !rc);return rc;}
static unsigned details,disks,flags,bits;
static unsigned window_open_sounds,window_close_sounds;
static unsigned keyboard_events;static int keyboard_folder_seen;
static int key_held[4];
static dw4_menu_window *status_root;
static dw4_controllers *trace_models;
static int64_t trace_ns;
static FILE *phase_trace;
void __real_dw4_controllers_sample(dw4_controllers *,int64_t);
void __wrap_dw4_controllers_sample(dw4_controllers *models,int64_t ns)
{__real_dw4_controllers_sample(models,ns);trace_models=models;trace_ns=ns;}
static void trace_phase(void)
{
    if(!phase_trace || !trace_models || !((scene_ticks>=1600 && scene_ticks<=1850) ||
        (scene_ticks>=3400 && scene_ticks<=3950) || (scene_ticks>=7900 && scene_ticks<=8100)))return;
    const beNDMWStatusCtrl00 *state=dw4_statusmenu_window_state(status_root);
    fprintf(phase_trace,"%u\t%lld\t__ROOT__\t0\t-\t0\t%d\t0\t0\t%d\t%d\t-\n",
        scene_ticks,(long long)trace_ns,status_root!=NULL,state?state->_st0:-1,state?state->_st1:-1);
    for(size_t i=0;i<dw4_controllers_count(trace_models);i++){
        const dw4_stageobject *info;int32_t slot;
        const dw4_modelctrl *model=dw4_controllers_model(trace_models,i,&info,&slot);
        if(!model || slot || !info || (strncmp(dw4_stageobject_name(info),"i_st",4) && strcmp(dw4_stageobject_name(info),"i_messwn")))continue;
        const char *sequence=dw4_modelctrl_sequence(model);
        if(!sequence && !dw4_modelctrl_active(model))continue;
        const char *action=dw4_modelctrl_action(model);
        fprintf(phase_trace,"%u\t%lld\t%s\t%d\t%s\t%lld\t%d\t%d\t%.9g\t%d\t%d\t%s\n",
            scene_ticks,(long long)trace_ns,dw4_stageobject_name(info),slot,sequence?sequence:"-",
            (long long)dw4_modelctrl_time(model),dw4_modelctrl_active(model),
            dw4_modelctrl_drawable(model),dw4_modelctrl_alpha(model),state?state->_st0:-1,state?state->_st1:-1,action?action:"-");
    }
}
static const char *capture_dir;static unsigned capture_tick=1810,capture_frame;
static int capture_step,capture_done,phase_capture;static FILE *phase_frames;
static int phase_frame_tick(void)
{return (scene_ticks>=1651 && scene_ticks<=1720) || (scene_ticks>=1951 && scene_ticks<=2020) ||
        (scene_ticks>=2151 && scene_ticks<=2220) || (scene_ticks>=2451 && scene_ticks<=2520);}
static void capture_draws(const char *part,const dw4_ui_draw *ui,const dw4_layer_draw *world,size_t count,int append)
{
    char path[4096];snprintf(path,sizeof path,"%s/root-%u.tsv",capture_dir,capture_frame);
    FILE *out=fopen(path,append?"a":"w");assert(out);
    if(!append)fputs("part\ttexture\ttriangle\tx\ty\tu\tv\tq\tr\tg\tb\ta\tw\th\tz\tdepth\tdepth_write\tfilter\tblend\tcolor_mask\n",out);
    const dw4_tex *textures[128];unsigned nt=0;
    for(size_t i=0;i<count;i++){
        const dw4_tex *tex=world?world[i].tex:ui[i].tex;if(!tex)continue;
        unsigned idx=0;while(idx<nt && textures[idx]!=tex)idx++;
        if(idx==nt){assert(nt<128);textures[nt++]=tex;snprintf(path,sizeof path,"%s/root-%u-%s-%u.png",capture_dir,capture_frame,part,idx);assert(!dw4_png_write(path,tex->rgba,tex->w,tex->h));}
        for(unsigned v=0;v<3;v++){
            const float *p=world?world[i].v[v]:ui[i].v[v];const uint8_t *rgba=world?world[i].rgba[v]:ui[i].rgba[v];
            float q=world || ui[i].stq?p[4]:1;
            float z=world?world[i].z[v]:ui[i].z[v];
            unsigned depth=world?(world[i].depth_always?2:1):ui[i].depth_mode;
            unsigned write=world?!world[i].no_depth_write:ui[i].depth_write;
            unsigned filter=world?(world[i].filter?world[i].filter:2):ui[i].filter;
            unsigned blend=world?world[i].blend:ui[i].blend;
            unsigned mask=world?world[i].color_mask:ui[i].color_mask;
            fprintf(out,"%s\t%u\t%zu\t%.6f\t%.6f\t%.6f\t%.6f\t%.9g\t%u\t%u\t%u\t%u\t%d\t%d\t%.9g\t%u\t%u\t%u\t%u\t%u\n",part,idx,i,p[0],p[1],p[2]/q,p[3]/q,q,rgba[0],rgba[1],rgba[2],rgba[3],tex->w,tex->h,z,depth,write,filter,blend,mask);
        }
    }
    assert(!fclose(out));
}
int __real_dw4_lobby_draw_layers(dw4_lobby *,dw4_fb *,unsigned,const dw4_fefont *,dw4_lobby_layer_visible,void *);
int __wrap_dw4_lobby_draw_layers(dw4_lobby *l,dw4_fb *fb,unsigned frame,const dw4_fefont *font,dw4_lobby_layer_visible visible,void *user)
{
    uint64_t cpu_before[DW4_CPU_KIND_COUNT];
    for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)cpu_before[kind]=dw4_gpu_policy_cpu_count(kind);
    int rc=__real_dw4_lobby_draw_layers(l,fb,frame,font,visible,user);
    if(lobby_parity && parity_capture && rc>=0) {
        static unsigned active_tick;static int fell;
        const char *name=!portal_edge && scene_ticks==1320?"jump.png":NULL;
        if(portal_edge && scene_ticks==1260)name="stage-portal-a.png";
        if(portal_edge && scene_ticks==1270)name="stage-portal-b.png";
        if(parity_phase==2 && !active_tick){name=portal_edge?"commander.png":"heal-active.png";active_tick=scene_ticks;}
        else if(active_tick && scene_ticks==active_tick+4 && !portal_edge)name="heal-loop.png";
        if(!portal_edge && parity_phase==3 && !fell){name="gate-fall.png";fell=1;}
        if(portal_edge && edge_first_fall && !fell){name="stairs-fall.png";fell=1;}
        if(name){char path[4096];snprintf(path,sizeof path,"%s/%s",parity_capture,name);assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));}
    }
    if(gpu_check)for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)assert(dw4_gpu_policy_cpu_count(kind)==cpu_before[kind]);
    trace_phase();
    if(phase_capture && phase_frame_tick() && status_root){
        const beNDMWStatusCtrl00 *s=dw4_statusmenu_window_state(status_root);assert(rc>=0 && s);
        capture_frame=scene_ticks;capture_draws("world",NULL,NULL,0,0);capture_step=1;
        unsigned count;dw4_lobby_last_draws(l,&count);
        fprintf(phase_frames,"%u\t%lld\t%d\t%d\t%d\t%d\t%u\n",scene_ticks,(long long)trace_ns,s->_st0,s->_st1,fb->w,fb->h,count);
    }
    if(capture_dir && !phase_capture && !capture_done && scene_ticks==capture_tick){
        assert(rc>=0 && status_root);const beNDMWStatusCtrl00 *s=dw4_statusmenu_window_state(status_root);assert(s);
        if(capture_tick==1810)assert(s->_st0==1 && !s->_st1);
        unsigned count;const dw4_layer_draw *draw=dw4_lobby_last_draws(l,&count);
        capture_draws("world",NULL,draw,count,0);capture_step=1;
        dw4_lobby_player_state player;assert(!dw4_lobby_player(l,&player) && player.weapon_submitted_triangles);
        char path[4096];snprintf(path,sizeof path,"%s/root-world.png",capture_dir);assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));
        snprintf(path,sizeof path,"%s/manifest.tsv",capture_dir);FILE *out=fopen(path,"w");assert(out);
        fprintf(out,"scene_ticks\twidth\theight\tworld_triangles\tweapon_submitted\troot_state\troot_sub\n%u\t%d\t%d\t%u\t%u\t%d\t%d\n",scene_ticks,fb->w,fb->h,count,player.weapon_submitted_triangles,s->_st0,s->_st1);assert(!fclose(out));
    }
    return rc;
}
void __real_dw4_gl_layer_ui_or_cpu(dw4_gl_layer **,dw4_fb *,const dw4_ui_draw *,int,int);
void __wrap_dw4_gl_layer_ui_or_cpu(dw4_gl_layer **g,dw4_fb *fb,const dw4_ui_draw *draw,int n,int threads)
{
    if(gpu_check && status_root)assert(*g);
    __real_dw4_gl_layer_ui_or_cpu(g,fb,draw,n,threads);
    if(gpu_check && status_root)assert(*g); /* STATUS must never become a CPU draw. */
    if(capture_dir && capture_step && !capture_done){
        capture_draws(capture_step==1?"model":"text",draw,NULL,(size_t)n,1);
        char path[4096];
        if(phase_capture)snprintf(path,sizeof path,"%s/root-%u.png",capture_dir,capture_frame);
        else snprintf(path,sizeof path,"%s/%s",capture_dir,capture_step==1?"root-model.png":"root-0.png");
        if(!phase_capture || capture_step==2)assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));
        if(capture_step==2){if(phase_capture)capture_step=0;else{capture_done=1;capture_step++;}}
        else capture_step++;
    }
}
static dw4_stageinput *input_owner;
/* the windowed title opening (about 270 frames) ignores input: the title part of the pad script starts after it */
static const char *base="285:start,350:start,410:cross,580:cross,625:cross,675:cross,690:right,700:right,712:cross,728:start,780:cross,810:cross,860:start,880:cross,2400:start,2600:cross,2800:cross,3000:cross,3200:cross,3400:down,3600:cross,3800:circle,4000:circle,4200:circle,4500:start,4750:circle";
int __real_dw4_stageinput_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
int __wrap_dw4_stageinput_service(void *user,const char *method,const dw4_script_value *args,size_t n,dw4_script_value *result,char *error,size_t cap)
{input_owner=user;return __real_dw4_stageinput_service(user,method,args,n,result,error,cap);}
dw4_menu_window *__real_dw4_statusmenu_window_open(const dw4_statusmenu_context *);
dw4_menu_window *__wrap_dw4_statusmenu_window_open(const dw4_statusmenu_context *c)
{status_root=__real_dw4_statusmenu_window_open(c);return status_root;}
dw4_menu_window *__real_dw4_statusdetail_window_open(const dw4_statusdetail_context *);
dw4_menu_window *__wrap_dw4_statusdetail_window_open(const dw4_statusdetail_context *c)
{dw4_menu_window *w=__real_dw4_statusdetail_window_open(c);if(w)details++;return w;}
dw4_menu_window *__real_dw4_statusdisk_window_open(const dw4_statusdisk_context *);
dw4_menu_window *__wrap_dw4_statusdisk_window_open(const dw4_statusdisk_context *c)
{dw4_menu_window *w=__real_dw4_statusdisk_window_open(c);if(w)disks++;return w;}
dw4_menu_window *__real_dw4_statusflag_window_open(const dw4_statusflag_context *);
dw4_menu_window *__wrap_dw4_statusflag_window_open(const dw4_statusflag_context *c)
{dw4_menu_window *w=__real_dw4_statusflag_window_open(c);if(w)flags++;return w;}
dw4_menu_window *__real_dw4_statusbit_window_open(const dw4_statusbit_context *);
dw4_menu_window *__wrap_dw4_statusbit_window_open(const dw4_statusbit_context *c)
{dw4_menu_window *w=__real_dw4_statusbit_window_open(c);if(w)bits++;return w;}
void __real_dw4_frontaudio_action(dw4_frontaudio *,const char *,const char *);
void __wrap_dw4_frontaudio_action(dw4_frontaudio *audio,const char *model,const char *action)
{
    const char *sound=dw4_frontaudio_action_sound(audio,model,action);
    if(!strcmp(model,"i_messwn") && sound){
        if(!strcmp(sound,"WINDOW_OPEN"))window_open_sounds++;
        if(!strcmp(sound,"WINDOW_CLOSE"))window_close_sounds++;
    }
    __real_dw4_frontaudio_action(audio,model,action);
}
static void pad_command(const char *value)
{
    dw4_script_value args[]={{DW4_SCRIPT_STRING,0,"STAGECTL",8},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"PADINPUT",8},{DW4_SCRIPT_STRING,0,value,strlen(value)}},result={0};char error[128];
    assert(input_owner && !__real_dw4_stageinput_service(input_owner,"sd",args,5,&result,error,sizeof error));
}
int __real_dw4_window_pump(dw4_window *,dw4_input_state *);
int __wrap_dw4_window_pump(dw4_window *window,dw4_input_state *in);
/* The engine pumps through dw4_window_pump_mates (the co-op pads of players 2-4); the scripted pad is the first player's. */
int __wrap_dw4_window_pump_mates(dw4_window *w,dw4_input_state *in,dw4_input_state mates[3]){(void)mates;return __wrap_dw4_window_pump(w,in);}
int __wrap_dw4_window_pump(dw4_window *window,dw4_input_state *in)
{
    if(!pad){device=SDL_JoystickAttachVirtual(SDL_JOYSTICK_TYPE_GAMECONTROLLER,6,15,0);assert(device>=0 && SDL_IsGameController(device));pad=SDL_JoystickOpen(device);assert(pad);}
    if(capture_done || polls>22000 || scene_ticks>9650 || (lobby_parity && parity_phase==4) || (focus_only && scene_ticks>=1600) || (phase_capture && scene_ticks>2650)){SDL_Event quit;SDL_zero(quit);quit.type=SDL_QUIT;assert(SDL_PushEvent(&quit)==1);return __real_dw4_window_pump(window,in);}
    if(!capture_dir && !lobby_parity){
        SDL_Event event;SDL_zero(event);event.type=SDL_WINDOWEVENT;event.window.windowID=1;
        if(focus_end && polls==focus_end){
            assert(trace_ns>focus_ns+200000000 && focus_presentations>=20);
            assert(focus_audio && dw4_audio_seconds(focus_audio)>focus_audio_seconds);
            if(focus_checks==0 || focus_checks==2)assert(focus_changed);
            event.window.event=SDL_WINDOWEVENT_FOCUS_GAINED;assert(SDL_PushEvent(&event)==1);
            focus_end=0;focus_checks++;
            fprintf(stderr,"background focus check %u: clocks, rendering and automatic focus return pass without R\n",focus_checks);
        } else if(!focus_end && ((focus_checks==0 && polls==100) ||
            (focus_checks==1 && polls==320) || (focus_checks==2 && scene_ticks==1350))){
            event.window.event=SDL_WINDOWEVENT_FOCUS_LOST;assert(SDL_PushEvent(&event)==1);
            focus_end=polls+40;focus_ns=trace_ns;focus_presentations=focus_changed=0;
            assert(focus_audio);focus_audio_seconds=dw4_audio_seconds(focus_audio);
        }
        if(!manual_poll && scene_ticks==1580){
            SDL_zero(event);event.type=SDL_KEYDOWN;event.key.keysym.scancode=SDL_SCANCODE_P;
            assert(SDL_PushEvent(&event)==1);manual_poll=polls;manual_ns=trace_ns;
        } else if(manual_poll && !manual_checked){
            if(polls==manual_poll+5 || polls==manual_poll+10){
                event.window.event=polls==manual_poll+5?SDL_WINDOWEVENT_FOCUS_LOST:SDL_WINDOWEVENT_FOCUS_GAINED;
                assert(SDL_PushEvent(&event)==1);
            } else if(polls==manual_poll+20){
                assert(trace_ns==manual_ns);
                SDL_zero(event);event.type=SDL_KEYDOWN;event.key.keysym.scancode=SDL_SCANCODE_R;
                assert(SDL_PushEvent(&event)==1);manual_checked=1;
                fputs("background focus: manual pause survives focus loss/return until explicit resume\n",stderr);
            }
        }
    }
    dw4_input_state wanted;
    if(!lobby_parity && !phase_capture && scene_ticks==1750)pad_command("DISABLE");
    if(!lobby_parity && scene_ticks==1790){const beNDMWStatusCtrl00 *state=dw4_statusmenu_window_state(status_root);assert(state && state->_st0==1 && state->_st1==0 && closes==0);}
    if(!lobby_parity && !phase_capture && scene_ticks==1800)pad_command("ENABLE");
    int keyboard=scene_ticks>=8250;
    if(scene_ticks==8900){
        const beNDMWStatusCtrl00 *state=dw4_statusmenu_window_state(status_root);
        if(!state || state->_st0!=1 || state->_st1!=2 || opens!=3 || closes!=2)
            fprintf(stderr,"STATUS keyboard checkpoint: root %p state %d/%d selection %d opens %u closes %u keyboard events %u pad slot %d\n",
                (void *)status_root,state?state->_st0:-1,state?state->_st1:-1,state?state->_retCode:-1,opens,closes,keyboard_events,
                input_owner?dw4_stageinput_slot(input_owner,0):-1);
        assert(state && state->_st0==1 && state->_st1==2 && opens==3 && closes==2);
        keyboard_folder_seen=1;
    }
    if(scene_ticks){
        dw4_input_script(&wanted,"1650:start,1850:cross,2050:cross,2250:cross,2450:cross,2650:down,2850:cross,3050:circle,3250:circle,3450:circle,3750:start,3950:down,4150:cross,4350:cross,4550:cross,4750:circle,4950:circle,5150:down,5350:cross,5550:circle,5750:down,5950:cross,6150:cross,6350:down,6550:cross,6750:cross,6950:circle,7150:down,7350:cross,7550:circle,7750:circle,7950:circle",(int)scene_ticks);
        if(scene_ticks==1770)wanted.cross=1;
        if(scene_ticks==1780)wanted.circle=1;
        if(scene_ticks>=350 && scene_ticks<1250 && scene_ticks%10==0)wanted.cross=1;
        if(!capture_dir && scene_ticks>=1300 && scene_ticks<1400)wanted.right=1;
        if(phase_capture) {
            dw4_input_script(&wanted,"1650:start,1950:circle,2150:start,2450:circle",(int)scene_ticks);
            if(scene_ticks>=350 && scene_ticks<1250 && scene_ticks%10==0)wanted.cross=1;
        }
    }else dw4_input_script(&wanted,base,(int)polls);
    if(keyboard)dw4_input_script(&wanted,"8350:start,8550:down,8750:cross,8950:circle,9150:circle",(int)scene_ticks);
    float parity_x=0,parity_y=0;
    if(lobby_parity && parity_lobby) {
        wanted=(dw4_input_state){0};wanted.cross=scene_ticks<1250 && scene_ticks%10==0;
        wanted.circle=!portal_edge && scene_ticks==1300;
        if((!portal_edge && scene_ticks>=1450) || (portal_edge && parity_phase==2 && edge_stairs_placed)) {
            dw4_lobby_walk_state actor;dw4_lobby_control_state camera;
            assert(!dw4_lobby_walk(parity_lobby,&actor) && !dw4_lobby_control(parity_lobby,&camera));
            float tx=portal_edge?100:parity_phase==2?97:115,tz=portal_edge?-40:parity_phase==2?-85:-95;
            float dx=tx-actor.position[0],dz=tz-actor.position[2];
            if(hypotf(dx,dz)>1) {
                float yaw=atan2f(dx,dz)-atan2f(camera.camera_world[8],camera.camera_world[10]);
                parity_x=sinf(yaw);parity_y=-cosf(yaw);
            }
        }
    }
    int button[15]={0};button[SDL_CONTROLLER_BUTTON_A]=wanted.cross;button[SDL_CONTROLLER_BUTTON_B]=wanted.circle;
    button[SDL_CONTROLLER_BUTTON_START]=wanted.start;
    if(keyboard)memset(button,0,sizeof button);
    for(unsigned b=0;b<15;b++)assert(!SDL_JoystickSetVirtualButton(pad,(int)b,(Uint8)button[b]));
    Sint16 magnitude=scene_ticks?14745:32767;
    assert(!SDL_JoystickSetVirtualAxis(pad,SDL_CONTROLLER_AXIS_LEFTX,!keyboard?magnitude*(wanted.right-wanted.left):0));
    assert(!SDL_JoystickSetVirtualAxis(pad,SDL_CONTROLLER_AXIS_LEFTY,!keyboard && wanted.down?magnitude:0));
    if(lobby_parity && parity_lobby) {
        assert(!SDL_JoystickSetVirtualAxis(pad,SDL_CONTROLLER_AXIS_LEFTX,(int)(parity_x*magnitude)));
        assert(!SDL_JoystickSetVirtualAxis(pad,SDL_CONTROLLER_AXIS_LEFTY,(int)(-parity_y*magnitude)));
    }
    if(keyboard){
        int held[4]={wanted.start,wanted.down,wanted.cross,wanted.circle};
        const SDL_Scancode codes[4]={SDL_SCANCODE_TAB,SDL_SCANCODE_DOWN,SDL_SCANCODE_RETURN,SDL_SCANCODE_ESCAPE};
        for(unsigned i=0;i<4;i++)if(held[i]!=key_held[i]){
            SDL_Event event;SDL_zero(event);event.type=held[i]?SDL_KEYDOWN:SDL_KEYUP;
            event.key.state=held[i]?SDL_PRESSED:SDL_RELEASED;
            event.key.keysym.scancode=codes[i];event.key.windowID=1;
            assert(SDL_PushEvent(&event)==1);key_held[i]=held[i];keyboard_events++;
        }
    }
    SDL_JoystickUpdate();polls++;
    int result=__real_dw4_window_pump(window,in);
    return result;
}
uint64_t __wrap_dw4_simulation_due(dw4_simulation *s,uint64_t host)
{(void)host;if(s->holds || s->failed)return 0;if(!s->due)s->due=1;return s->due;}
void __real_dw4_lobby_tick(dw4_lobby *,int);
static void edge_place(dw4_lobby *l,const char *value)
{
    dw4_script_value a[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,value,strlen(value)}},r;char error[256];
    assert(!dw4_lobby_player_service(l,"sd",a,5,&r,error,sizeof error));
}
void __wrap_dw4_lobby_tick(dw4_lobby *l,int cross)
{
    parity_lobby=l;
    if(portal_edge && scene_ticks==1300){edge_place(l,"V<18,20,15>/V<0,0,0>");parity_phase=1;}
    if(portal_edge && parity_phase==2 && !edge_stairs_placed){edge_place(l,"V<175,30,-40>/V<0,0,0>");edge_stairs_placed=1;}
    static dw4_lobby_walk_state before;
    static unsigned camera_regions,camera_blends;
    dw4_lobby_control_state camera_before;
    int camera_probe=!capture_dir && scene_ticks>=1300 && scene_ticks<1550;
    if(camera_probe)assert(!dw4_lobby_control(l,&camera_before));
    if(!capture_dir && scene_ticks==1300)assert(!dw4_lobby_walk(l,&before));
    __real_dw4_lobby_tick(l,cross);scene_ticks++;
    if(portal_edge) {
        dw4_lobby_walk_state a;dw4_lobby_portal_state gate;dw4_lobby_portal_instances slots;
        assert(!dw4_lobby_walk(l,&a) && !dw4_lobby_portal(l,3,&gate) && !dw4_lobby_portal_slots(l,3,&slots));
        assert(slots.slots==3 && slots.visible_slots==1 && slots.position[0]==5 && slots.position[1]==27 && slots.position[2]==15);
        if(parity_phase==1 && gate.action==2){parity_phase=2;fputs("live commander: one centered authored active instance\n",stderr);}
        if(edge_stairs_placed) {
            edge_first_fall|=a.position[1]<29.9f && a.position[1]>20.1f && a.motion && !strcmp(a.motion,"jumpS02");
            edge_first_land|=edge_first_fall && fabsf(a.position[1]-20)<1e-5f;
            edge_second_fall|=edge_first_land && a.position[1]<19.9f && a.position[1]>10.1f;
            edge_second_land|=edge_second_fall && fabsf(a.position[1]-10)<1e-5f;
            if(a.position[0]<115 && edge_second_land)parity_phase=4;
        }
        assert(!dw4_lobby_script_error(l)[0] && scene_ticks<3000);return;
    }
    if(lobby_parity) {
        dw4_lobby_walk_state a;dw4_lobby_portal_state gate;assert(!dw4_lobby_walk(l,&a) && !dw4_lobby_portal(l,1,&gate));
        if(scene_ticks==1300){parity_floor=a.position[1];assert(parity_players);dw4_property_folder *f=dw4_playerrecords_get(parity_players,"GETPLAYER",0);
            assert(!dw4_property_set_number(f,"HP",1) && !dw4_property_set_number(f,"MP",1));}
        if(scene_ticks>1300 && scene_ticks<1450) {
            parity_jump|=a.position[1]>parity_floor+5;
            parity_fall|=a.motion && !strcmp(a.motion,"jumpS02");parity_land|=a.motion && !strcmp(a.motion,"jumpS03");
        }
        if(scene_ticks==1450){assert(parity_jump && parity_fall && parity_land && a.position[1]==parity_floor);parity_phase=1;}
        if(scene_ticks>1450 && gate.animation_ns!=parity_gate_time)parity_loops++;
        parity_gate_time=gate.animation_ns;
        if(parity_phase==1 && gate.action==2) {
            dw4_playerhealth h;char error[256];assert(!__real_dw4_playerhealth_restore(parity_players,0,&h,error,sizeof error));
            assert(h.hp==h.max_hp && h.mp==h.max_mp);parity_phase=2;
        }else if(parity_phase==2 && a.position[0]<102 && !gate.active)parity_phase=3;
        else if(parity_phase==3 && gate.action==2){assert(parity_loops>50);parity_phase=4;}
        if(scene_ticks%200==0)fprintf(stderr,"parity tick %u phase %u position %.3f %.3f %.3f motion %s gate %d time %lld\n",scene_ticks,parity_phase,a.position[0],a.position[1],a.position[2],a.motion?a.motion:"-",gate.action,(long long)gate.animation_ns);
        assert(!dw4_lobby_script_error(l)[0]);assert(scene_ticks<3000);
        return;
    }
    if(camera_probe){
        dw4_lobby_control_state camera_after;assert(!dw4_lobby_control(l,&camera_after));
        float rotation=0;
        for(unsigned k=0;k<12;k++){
            float d=camera_before.camera_world[k]-camera_after.camera_world[k];rotation+=d*d;
        }
        camera_regions+=camera_before.camera_region!=camera_after.camera_region;
        camera_blends+=rotation>1e-9f;
        assert(rotation<.04f);
    }
    if(!capture_dir && scene_ticks==1440){
        dw4_lobby_walk_state after;assert(!dw4_lobby_walk(l,&after));
        assert(after.position[0]>before.position[0]+10 && after.speed==0 && !strcmp(after.motion,"waitS"));
        fprintf(stderr,"live lobby movement: SDL right -> positive world X, run/idle and braking before STATUS pass\n");
    }
    if(!capture_dir && scene_ticks==1550){
        assert(camera_regions && camera_blends>20);
        fprintf(stderr,"live box camera: original-script lobby crosses a region with smooth SDL-driven camera updates\n");
    }
}
int __real_dw4_lobby_weapon(dw4_lobby *,dw4_mount *,const char *,char *,size_t);
int __wrap_dw4_lobby_weapon(dw4_lobby *l,dw4_mount *mount,const char *asset,char *error,size_t cap)
{
    dw4_lobby_player_state before,after;char old[64];assert(!dw4_lobby_player(l,&before));snprintf(old,sizeof old,"%s",before.weapon_asset);
    int rc=__real_dw4_lobby_weapon(l,mount,asset,error,cap);
    if(!rc){assert(!dw4_lobby_player(l,&after));assert(strcmp(old,after.weapon_asset));assert(after.weapon_triangles && after.motion && *after.motion);swaps++;}
    return rc;
}
int __real_dw4_statusscene_freeze(dw4_statusscene *,char *,size_t);
int __wrap_dw4_statusscene_freeze(dw4_statusscene *scene,char *error,size_t cap)
{int rc=__real_dw4_statusscene_freeze(scene,error,cap);if(!rc)opens++;return rc;}
int __real_dw4_statusscene_restore(dw4_statusscene *,char *,size_t);
int __wrap_dw4_statusscene_restore(dw4_statusscene *scene,char *error,size_t cap)
{int rc=__real_dw4_statusscene_restore(scene,error,cap);if(!rc){closes++;status_root=NULL;}return rc;}
int __real_dw4_frontend_boot(const char *,dw4_title_menu *,char *,size_t,int,int,struct dw4_window *,struct dw4_vk *,const char *,int);
int __wrap_dw4_frontend_boot(const char *r,dw4_title_menu *m,char *s,size_t n,int p,int f,struct dw4_window *w,struct dw4_vk *v,const char *input,int skip)
{(void)p;(void)w;(void)v;(void)input;(void)skip;return __real_dw4_frontend_boot(r,m,s,n,0,f,NULL,NULL,NULL,1);}
#endif
int main(int argc,char **argv)
{
#ifndef DW4_ENABLE_SDL2
    (void)argc;(void)argv;puts("live STATUS: SDL unavailable, skipped");
#else
    assert(argc==2);capture_dir=getenv("DW4_STATUS_LIVE_CAPTURE");
    focus_only=getenv("DW4_STATUS_LIVE_FOCUS_ONLY")!=NULL;
    portal_edge=getenv("DW4_LOBBY_PORTAL_EDGE")!=NULL;
    lobby_parity=portal_edge || getenv("DW4_LOBBY_PARITY")!=NULL;
    parity_capture=getenv("DW4_LOBBY_PARITY_CAPTURE");
    const char *phase=getenv("DW4_STATUS_LIVE_PHASE_CAPTURE");
    if(phase){char path[4096];assert(!capture_dir);capture_dir=phase;phase_capture=1;
        snprintf(path,sizeof path,"%s/frames.tsv",phase);phase_frames=fopen(path,"w");assert(phase_frames);
        fputs("tick\tengine_ns\troot_state\troot_sub\twidth\theight\tworld_triangles\n",phase_frames);}
    const char *trace=getenv("DW4_STATUS_LIVE_TRACE");
    if(trace){phase_trace=fopen(trace,"w");assert(phase_trace);fputs("tick\tengine_ns\tname\tslot\tsequence\tnode_ns\tactive\tdrawable\talpha\troot_state\troot_sub\taction\n",phase_trace);}
    const char *tick=getenv("DW4_STATUS_LIVE_CAPTURE_TICK");
    if(tick){char *end;unsigned long value=strtoul(tick,&end,10);assert(capture_dir && !phase_capture && *tick && !*end && value>=1651 && value<1850);capture_tick=(unsigned)value;}
    const char *gpu_size=getenv("DW4_STATUS_LIVE_GPU");gpu_check=gpu_size!=NULL;assert(!gpu_check || !capture_dir);
    gpu_fail=getenv("DW4_STATUS_LIVE_GPU_FAIL")!=NULL;assert(!gpu_fail || gpu_check);
    int w=capture_dir?640:160,h=capture_dir?448:112;
    if(gpu_check)assert(sscanf(gpu_size,"%dx%d",&w,&h)==2 && w>0 && h>0 && w<=4096 && h<=4096);
    dw4_engine_opts o={.roms=argv[1],.frames=0,.w=w,.h=h,.window=1,.software=!gpu_check,.gl=gpu_check,.fps=0,.fps_lock=0};
    if(getenv("DW4_STATUS_LIVE_FPS"))o.fps=1;
    char stage[64];int rc=dw4_engine_boot(&o,NULL,stage,sizeof stage);
    if(phase_trace){assert(!fclose(phase_trace));phase_trace=NULL;}
    if(phase_frames){assert(!fclose(phase_frames));phase_frames=NULL;}
    fprintf(stderr,"live STATUS result %d polls %u opens %u closes %u\n",rc,polls,opens,closes);
    fprintf(stderr,"live STATUS pages detail %u disk %u flag %u currency %u\n",details,disks,flags,bits);
    fprintf(stderr,"live STATUS message-window sounds open %u close %u\n",window_open_sounds,window_close_sounds);
    if(lobby_parity){
        if(portal_edge){
            assert(rc>=0 && parity_phase==4 && edge_first_fall && edge_first_land && edge_second_fall && edge_second_land && !opens);
            if(gpu_check)for(unsigned k=0;k<DW4_CPU_KIND_COUNT;k++)assert(!dw4_gpu_policy_cpu_count(k));
            puts("live lobby: original startup, single commander effect and SDL walking falls 30 -> 20 -> 10 without Circle pass");return 0;
        }
        assert(rc>=0 && parity_phase==4 && parity_jump && parity_fall && parity_land && !opens);
        if(gpu_check)for(unsigned k=0;k<DW4_CPU_KIND_COUNT;k++)assert(!dw4_gpu_policy_cpu_count(k));
        puts("live lobby: SDL Circle jump, landing, authored gate loops, walking heal HP/MP, departure and re-entry pass");return 0;
    }
    if(focus_only){
        assert(rc>=0 && focus_checks==3 && manual_checked);
        if(gpu_check)for(unsigned k=0;k<DW4_CPU_KIND_COUNT;k++)assert(!dw4_gpu_policy_cpu_count(k));
        puts("live focus: title, character creation and lobby continue clocks/rendering/audio across focus loss/return without R; manual pause remains independent");return 0;
    }
    if(gpu_check){assert(gpu_calls && model_calls);fprintf(stderr,"live STATUS GPU: %u passes %.3f ms/pass; model publication %u frames %.3f ms/frame\n",gpu_calls,gpu_ms/gpu_calls,model_calls,model_ms/model_calls);}
    if(gpu_fail){assert(gpu_failed && rc<0);puts("live STATUS GPU: failed draw stops explicitly without CPU fallback");return 0;}
    if(phase_capture){assert(rc>=0 && opens==2 && closes==2 && !swaps && !capture_step);puts("live STATUS phases: two root-only open/close cycles, actual UI submissions and composed frames saved");return 0;}
    if(capture_dir){assert(rc>=0 && capture_done && opens==1);puts("live STATUS capture: actual root world/model/font submissions and composed framebuffer saved");return 0;}
    assert(rc>=0 && opens==3 && closes==3 && swaps==1);
    assert(focus_checks==3 && manual_checked);
    assert(keyboard_events==10 && keyboard_folder_seen);
    assert(details==1 && disks==1 && flags==1 && bits==1);
    assert(window_open_sounds && window_close_sounds);
    /* The engine closes its SDL lifetime, including the virtual device. */
    pad=NULL;device=-1;
    puts("live STATUS: SDL controller and keyboard events, real window pump, weapon swap, DEVICE detail, DISK, important items, currency and three actual restores pass");
#endif
    return 0;
}
