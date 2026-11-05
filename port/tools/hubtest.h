/* Shared headless helpers for the prepared-hub interaction tests. */
#ifndef DW4_TEST_HUBTEST_H
#define DW4_TEST_HUBTEST_H
#include "dw4/hubruntime.h"
#include "dw4/filelist.h"
#include "dw4/database.h"
#include "dw4/playerinit.h"
#include "dw4/playertransactions.h"
#include "dw4/png.h"
#include "dw4/statuscontent.h"
#include "dw4/playerstats.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <stdlib.h>
struct boot {dw4_playerrecords *players;dw4_scriptservices *sd;};
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct boot *b=user;int rc=dw4_playerrecords_call(b->players,method,a,n,r,error,cap);if(rc>0)rc=dw4_playertransactions_folder_call(b->players,method,a,n,r,error,cap);if(rc<=0)return rc;
    if(!strcmp(method,"SYSgetLightMode")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;}
    return dw4_scriptservices_call(b->sd,method,a,n,r,error,cap);
}
static uint64_t frame;static const char *capture_dir;
static void step(dw4_hubruntime *h,uint32_t analog,uint32_t pressed)
{
    dw4_hubruntime_input(h,0,0,analog,0,pressed);
    if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));assert(0);}
}
static void idle(dw4_hubruntime *h,unsigned n){while(n--)step(h,0,0);}
static void press(dw4_hubruntime *h,uint32_t bits){step(h,0,bits);idle(h,3);}
static void down(dw4_hubruntime *h){step(h,4,0);idle(h,8);}
static int has_text(const dw4_hubruntime *h,const char *group,const char *name)
{
    const dw4_dialogue *d=dw4_hubruntime_dialogue(h);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++) {
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(t->visible && t->count && !strcmp(t->group,group) && (!name || !strcmp(t->name,name)))return 1;
    }
    return 0;
}
static const char *text_value(const dw4_hubruntime *h,const char *group,const char *name)
{
    static char out[64];const dw4_dialogue *d=dw4_hubruntime_dialogue(h);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++) {
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(t->visible && t->count && !strcmp(t->group,group) && !strcmp(t->name,name)) {
            size_t n=t->count<sizeof out-1?t->count:sizeof out-1;
            for(size_t k=0;k<n;k++)out[k]=(char)t->codes[k];
            out[n]=0;return out;
        }
    }
    return NULL;
}
static int wait_text(dw4_hubruntime *h,const char *group,const char *name,unsigned max)
{for(unsigned i=0;i<max;i++){if(has_text(h,group,name))return 1;step(h,0,0);}return 0;}
static int wait_gone(dw4_hubruntime *h,const char *group,const char *name,unsigned max)
{for(unsigned i=0;i<max;i++){if(!has_text(h,group,name))return 1;step(h,0,0);}return 0;}
static const dw4_modelctrl *find(const dw4_controllers *models,const char *name,int32_t want)
{
    for(size_t i=0;i<dw4_controllers_count(models);i++) {
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&slot);
        if(!strcmp(dw4_stageobject_name(info),name) && slot==want)return m;
    }
    return NULL;
}
static int control(dw4_hubruntime *h)
{dw4_lobby_control_state c;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c));return c.player_control;}
static int walk_to(dw4_hubruntime *h,float tx,float tz,float stop)
{
    dw4_lobby_walk_state w;
    for(unsigned t=0;t<900;t++) {
        dw4_lobby_control_state c;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c));
        if(!c.player_control)return 0;
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        float dx=tx-w.position[0],dz=tz-w.position[2];
        if(sqrtf(dx*dx+dz*dz)<=stop)return 1;
        float yaw=atan2f(dx,dz)-atan2f(c.camera_world[8],c.camera_world[10]);
        dw4_hubruntime_input(h,sinf(yaw),-cosf(yaw),0,0,0);
        if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){fprintf(stderr,"walk: %s\n",dw4_hubruntime_error(h));assert(0);}
    }
    return 0;
}
/* Walk toward the NPC with camera-relative stick input and stop inside probe range. */
static int approach(dw4_hubruntime *h,const dw4_modelctrl *npc,float stop)
{
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(npc,&a);
    if(!walk_to(h,a.position[0],a.position[2],stop))return 0;
    idle(h,20);return 1;
}
static int32_t number(dw4_property_folder *f,const char *key)
{int32_t v;assert(!dw4_property_number(f,key,&v));return v;}
static dw4_hubruntime *boot_central(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    char error[512];
    dw4_hubruntime *h=dw4_hubruntime_prepare(mount,source,"stagML12",0,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare Central: %s\n",error);assert(0);}
    unsigned t=0;
    for(;t<900;t++){step(h,0,0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
    assert(t<900);return h;
}
/* Headless CPU reference draw of the current frame; optional PNG capture for inspection. */
static void gpu_compare(dw4_hubruntime *h,const char *tag);
/* The shop root's common widgets (ShopCtrl00, SUBWND modes 1 and 3..9): the player panel's name and species, the
 * Select/Confirm/Cancel legend (StatusTitle03, STWINFONT34 font000..002, txt_status call 0) and the i_sttitle header text
 * must all be on screen with every service frame. The Digi-Lab (mode 2, Digilabo's own widget set) shows the compact
 * name/level base, so its species line is not required. */
static void assert_shop_chrome(dw4_hubruntime *h,const char *tag)
{
    if(!dw4_hubruntime_shop_mode(h))return;
    int lab=dw4_hubruntime_shop_mode(h)==2;
    int ok=has_text(h,"STWINFONT12","font000") && has_text(h,"STWINFONT04","font000") && has_text(h,"STWINFONT34","font000") &&
        (lab || has_text(h,"STWINFONT04","font001"));
    if(!ok)fprintf(stderr,"hub chrome %s: header %d name %d species %d legend %d\n",tag,has_text(h,"STWINFONT12","font000"),
        has_text(h,"STWINFONT04","font000"),has_text(h,"STWINFONT04","font001"),has_text(h,"STWINFONT34","font000"));
    assert(ok);
}
static void draw_frame(dw4_hubruntime *h,const char *tag)
{
    assert_shop_chrome(h,tag);
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    int triangles=dw4_hubruntime_draw(h,&fb,NULL);
    if(triangles<=0)fprintf(stderr,"draw %s: %s\n",tag,dw4_lobby_script_error(dw4_hubruntime_world(h)));
    assert(triangles>0);
    unsigned lit=0;for(size_t i=0;i<(size_t)fb.w*fb.h;i++)lit+=fb.rgba[4*i] || fb.rgba[4*i+1] || fb.rgba[4*i+2];
    assert(lit>1000);
    if(capture_dir){char path[512];snprintf(path,sizeof path,"%s/xdata-%s.png",capture_dir,tag);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
    dw4_fb_free(&fb);
    gpu_compare(h,tag); /* every drawn service frame is also checked on the GPU backend */
}
/* Draw the current hub frame on the CPU oracle and on the GPU backend and compare them with the
 * lobby GPU check's tolerances (RGB MAE <= 3/255, <= 4% of pixels off by more than four levels here; the lobby check uses 1/255 and 1%).
 * The GPU context is created on first use; without one the comparison is skipped and says so. */
/* The hub service frames are full-screen UI (a backdrop, a dozen bordered windows and small text), so the one-pixel edge
 * differences between the CPU and GPU rasterisers add up to more than in the lobby world frames. */
enum {GPU_MAE_MAX=3,GPU_PCT_MAX=4};
static unsigned gpu_checked,gpu_skipped;
static void gpu_compare(dw4_hubruntime *h,const char *tag)
{
    dw4_fb a,b;assert(!dw4_fb_init(&a,640,448) && !dw4_fb_init(&b,640,448));
    assert(dw4_hubruntime_draw(h,&a,NULL)>0);
    dw4_lobby *world=dw4_hubruntime_world(h);
    if(!dw4_lobby_gpu_info(world) && !dw4_lobby_enable_gpu(world,640,448)){
        gpu_skipped++;fprintf(stderr,"hub GPU %s: GPU context unavailable, skipped\n",tag);dw4_fb_free(&a);dw4_fb_free(&b);return;
    }
    static int announced;if(!announced){announced=1;printf("hub GPU renderer: %s\n",dw4_lobby_gpu_info(world));}
    int tri=dw4_hubruntime_draw(h,&b,NULL);assert(tri>0);
    double sum=0;size_t far=0,n=(size_t)a.w*a.h;
    for(size_t i=0;i<n;i++){
        unsigned worst=0;
        for(int c=0;c<3;c++){int d=abs((int)a.rgba[4*i+c]-(int)b.rgba[4*i+c]);sum+=d;if((unsigned)d>worst)worst=(unsigned)d;}
        far+=worst>4;
    }
    double mae=sum/(3.0*n),pct=100.0*far/n;
    if(capture_dir){char path[512];snprintf(path,sizeof path,"%s/gpu-%s.png",capture_dir,tag);assert(!dw4_png_write(path,b.rgba,b.w,b.h));}
    if(mae>GPU_MAE_MAX || pct>GPU_PCT_MAX)fprintf(stderr,"hub GPU %s: MAE %.3f, %.3f%% pixels > 4 levels\n",tag,mae,pct);
    assert(mae<=GPU_MAE_MAX && pct<=GPU_PCT_MAX);
    gpu_checked++;dw4_fb_free(&a);dw4_fb_free(&b);
}
static void leave_service(dw4_hubruntime *h)
{
    idle(h,60);press(h,0x2000); /* cancel the main menu */
    unsigned k=0;for(;k<900 && dw4_hubruntime_status_active(h);k++)step(h,0,0);
    assert(k<900 && !dw4_hubruntime_status_active(h));
    unsigned e=0;for(;e<200 && (!control(h) || dw4_hubruntime_input_state(h)->disabled);e++)step(h,0,0);
    assert(e<200 && control(h) && !dw4_hubruntime_travel(h)->pending);
}
static void move_player(dw4_hubruntime *h,const float p[3])
{
    char value[160],error[256];snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>/V<0,0,0>",p[0],p[1],p[2]);
    dw4_script_value a[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,value,strlen(value)}},r;
    assert(!dw4_lobby_player_service(dw4_hubruntime_world(h),"sd",a,5,&r,error,sizeof error));
}
/* Teleport beside the NPC (waking it through its NEAR map; sides without floor under them are
 * skipped), close in with real stick input and press Cross. Returns 1 when the probe hit. */
static int talk_to(dw4_hubruntime *h,const dw4_modelctrl *npc)
{
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(npc,&a);
    for(int i=0;i<16;i++){
        float r=i<8?30:55,ang=(float)(i%8)*0.78539816f;
        float at[3]={a.position[0]+r*cosf(ang),a.position[1],a.position[2]+r*sinf(ang)};
        move_player(h,at);idle(h,90);
        dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        if(fabsf(w.position[1]-a.position[1])>6)continue;
        if(!approach(h,npc,9))continue;
        step(h,0,0x4000);if(dw4_lobby_talk_result(dw4_hubruntime_world(h))==1)return 1;
        idle(h,10);
    }
    return 0;
}

#endif
