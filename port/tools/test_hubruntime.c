/* Original destination start/first against a private session image. Headless. */
#include "dw4/hubruntime.h"
#include "dw4/filelist.h"
#include "dw4/database.h"
#include "dw4/playerinit.h"
#include "dw4/png.h"
#include "dw4/igfile.h"
#include "dw4/playerpoint.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
static const char *capture_dir;
struct boot {dw4_playerrecords *players;dw4_scriptservices *sd;};
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct boot *b=user;int rc=dw4_playerrecords_call(b->players,method,a,n,r,error,cap);if(rc<=0)return rc;
    if(!strcmp(method,"SYSgetLightMode")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;}
    return dw4_scriptservices_call(b->sd,method,a,n,r,error,cap);
}
static void step(dw4_hubruntime *h,uint64_t *frame,uint32_t analog,uint32_t pressed)
{
    dw4_hubruntime_input(h,0,0,analog,0,pressed);
    if(dw4_hubruntime_tick(h,(*frame)++*1000000000ULL/60)) {
        fprintf(stderr,"runtime tick: %s\n",dw4_hubruntime_error(h));assert(0);
    }
}
static uint32_t field(const dw4_igb_record *r,unsigned ordinal)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;assert(0);return 0;}
/* Read the authored event box independently of the runtime's membership mask.
 * Begin at its authored arrival point, then walk the bridge with camera-relative
 * stick input. Relocation to that point is the fixture; movement, membership,
 * callback dispatch, player ownership and choices are live. */
static void exit_center(dw4_mount *mount,const char *stage,const char *name,float center[3],float outside[3])
{
    dw4_igfile file={0};dw4_igb g={0};assert(!dw4_igfile_open_stage_pack(&file,mount,stage,0,0));
    assert(!dw4_igb_open(&g,file.data,file.len,0) && !dw4_igb_refs_open(&g));int found=0;
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2) {
        dw4_igb_record r={0};assert(dw4_igb_decode(&g,g.id_off[id],&r));
        if(!strcmp(r.class_name,"beMatCtrlData") && r.name && !strcmp(r.name,name)) {
            uint32_t box=field(&r,3);dw4_igb_record bounds={0};assert(box<g.table_n && g.id_kind[box]==2 && dw4_igb_decode(&g,g.id_off[box],&bounds));
            float lo[3],hi[3];unsigned vectors=0;
            for(unsigned v=0;v<bounds.nvalues;v++)if(bounds.values[v].ordinal==2 || bounds.values[v].ordinal==3) {
                assert(bounds.values[v].vsize>=12);memcpy(bounds.values[v].ordinal==2?lo:hi,g.data+bounds.values[v].voff,12);vectors++;
            }
            assert(vectors==2);for(unsigned k=0;k<3;k++){center[k]=(lo[k]+hi[k])*.5f;outside[k]=center[k];}
            outside[0]=hi[0]+4;found++;dw4_igb_record_free(&bounds);
        }dw4_igb_record_free(&r);
    }
    assert(found==1);
    int group=!strcmp(stage,"stagML11")?(!strcmp(name,"matz00")?1:2):!strcmp(name,"matz00")?0:1;
    float arrival[16];assert(!dw4_playerpoint_matrix(file.data,file.len,group,0,arrival));memcpy(outside,arrival+12,3*sizeof(float));
    dw4_igb_close(&g);dw4_igfile_close(&file);
}
static void place(dw4_hubruntime *h,const float p[3])
{
    char value[160],error[256];snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>/V<0,0,0>",p[0],p[1],p[2]);
    dw4_script_value a[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,value,strlen(value)}},r;
    assert(!dw4_lobby_player_service(dw4_hubruntime_world(h),"sd",a,5,&r,error,sizeof error));
}
static void exit_choice(dw4_hubruntime *h,dw4_mount *mount,const char *stage,const char *event,
    uint64_t *frame,int cancel,dw4_fb *fb)
{
    float center[3],outside[3];exit_center(mount,stage,event,center,outside);
    place(h,outside);step(h,frame,0,0);
    for(unsigned t=0;t<24;t++)step(h,frame,0,0);
    dw4_lobby_walk_state walking;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&walking));
    if(walking.position[1]<0 || walking.position[1]>100)fprintf(stderr,"unsupported approach %s/%s: %.9g %.9g %.9g %s\n",stage,event,walking.position[0],walking.position[1],walking.position[2],walking.motion);
    assert(walking.position[1]>=0 && walking.position[1]<100);
    unsigned approach=0;
    for(;approach<300;approach++) {
        dw4_lobby_control_state control;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&control));
        if(!control.player_control)break;
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&walking));
        float yaw=atan2f(center[0]-walking.position[0],center[2]-walking.position[2])-atan2f(control.camera_world[8],control.camera_world[10]);
        dw4_hubruntime_input(h,sinf(yaw),-cosf(yaw),0,0,0);
        if(dw4_hubruntime_tick(h,(*frame)++*1000000000ULL/60)){fprintf(stderr,"approach: %s\n",dw4_hubruntime_error(h));assert(0);}
    }
    if(approach==300){dw4_lobby_walk(dw4_hubruntime_world(h),&walking);fprintf(stderr,"missed approach %s/%s %.9g %.9g %.9g\n",stage,event,walking.position[0],walking.position[1],walking.position[2]);}
    assert(approach<300);
    for(unsigned t=0;t<80;t++)step(h,frame,cancel==2 && t==65?4:0,0);
    const dw4_dialogue *dialogue=dw4_hubruntime_dialogue(h);int visible=0;
    for(size_t i=0;i<dw4_dialogue_text_count(dialogue);i++) {
        const dw4_dialogue_text *text=dw4_dialogue_text_at(dialogue,i);
        visible+=text->visible && !strcmp(text->group,"STCHGFONT00") && text->count;
    }
    if(!visible){dw4_lobby_walk_state p;dw4_lobby_walk(dw4_hubruntime_world(h),&p);fprintf(stderr,"missing %s/%s window at %.9g,%.9g,%.9g (box %.9g,%.9g,%.9g)\n",stage,event,p.position[0],p.position[1],p.position[2],center[0],center[1],center[2]);}
    assert(visible && !dw4_hubruntime_travel(h)->pending);
    dw4_be_state before=*dw4_hubruntime_state(h);assert(dw4_hubruntime_draw(h,fb,NULL)>0);
    unsigned lit=0;for(size_t pixel=0;pixel<(size_t)fb->w*fb->h;pixel++)lit+=fb->rgba[4*pixel] || fb->rgba[4*pixel+1] || fb->rgba[4*pixel+2];assert(lit>1000);
    assert(!memcmp(&before,dw4_hubruntime_state(h),sizeof before));
    if(capture_dir && !cancel){char path[512];snprintf(path,sizeof path,"%s/%s-choice.png",capture_dir,stage);assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));}
    step(h,frame,0,cancel==1?0x2000:0x4000);
    for(unsigned t=0;t<420;t++)step(h,frame,0,0);
    const dw4_stagetravel *travel=dw4_hubruntime_travel(h);
    assert(travel->pending==!cancel);
    dw4_lobby_control_state control;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&control));
    if(cancel)assert(!dw4_hubruntime_input_state(h)->disabled && control.player_control);
    else assert(dw4_hubruntime_input_state(h)->disabled && !control.player_control);
    printf("live material %s/%s: original visible choice, %s and player control pass\n",stage,event,cancel==1?"Circle":cancel==2?"No":"accept");
}
static void status_cycle(dw4_hubruntime *h,uint64_t *frame,dw4_fb *fb)
{
    step(h,frame,0,8);assert(dw4_hubruntime_status_active(h));
    dw4_lobby_presentation_state before,after;dw4_lobby_control_state old,now;
    assert(!dw4_lobby_presentation(dw4_hubruntime_world(h),&before));
    assert(!dw4_lobby_control(dw4_hubruntime_world(h),&old));
    for(unsigned t=0;t<180;t++)step(h,frame,0,0);
    assert(dw4_hubruntime_status_active(h)==2);
    assert(dw4_hubruntime_draw(h,fb,NULL)>0);
    if(capture_dir){dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info));char path[512];snprintf(path,sizeof path,"%s/%s-status.png",capture_dir,info.stage);assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));}
    assert(!dw4_lobby_presentation(dw4_hubruntime_world(h),&after) && before.tick==after.tick);
    assert(!dw4_lobby_control(dw4_hubruntime_world(h),&now) && now.material_ticks==old.material_ticks);
    step(h,frame,0,0x2000);
    unsigned t=0;for(;t<600 && dw4_hubruntime_status_active(h);t++)step(h,frame,0,0);
    assert(t<600 && !dw4_hubruntime_status_active(h));
    assert(!dw4_lobby_presentation(dw4_hubruntime_world(h),&after) && after.tick<=before.tick+1);
    assert(!dw4_hubruntime_input_state(h)->disabled);
    printf("hub STATUS: original root open/draw/close, held world and restoration pass\n");
}
int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubTest",error,sizeof error));
    /* Establish return-visit flags/RNG by executing the real Terminal intro.
     * Flag501 is set by first.lua; do not synthesize a guessed return state. */
    dw4_hubruntime_source initial={players,&state,NULL,0};uint64_t frames=0;
    dw4_be_state source_before=state;
    assert(!dw4_hubruntime_prepare(&mount,&initial,"missing",0,1,error,sizeof error));
    assert(!memcmp(&state,&source_before,sizeof state));
    assert(!dw4_playerrecords_join(players,2,1));
    assert(!dw4_hubruntime_prepare(&mount,&initial,"stagML12",0,1,error,sizeof error));
    int32_t still_joined;assert(!dw4_property_number(dw4_playerrecords_get(players,"GETPLAYER",2),"ISUSE",&still_joined) && still_joined==1);
    assert(!dw4_playerrecords_join(players,2,0));
    dw4_hubruntime *active=dw4_hubruntime_prepare(&mount,&initial,"stagML11",0,1,error,sizeof error);
    if(!active){fprintf(stderr,"initial Terminal: %s\n",error);return 1;}
    unsigned intro=0;
    for(;intro<2200 && !dw4_lobby_intro_done(dw4_hubruntime_world(active));intro++) {
        dw4_hubruntime_input(active,0,0,0,0,intro%10==0?0x4000:0);
        if(dw4_hubruntime_tick(active,frames++*1000000000ULL/60)){fprintf(stderr,"intro %u: %s\n",intro,dw4_hubruntime_error(active));return 1;}
    }
    assert(intro<2200);
    const uint8_t *complete=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(active),"GETCOMMON",0),"FLAG",NULL);
    fprintf(stderr,"original intro ticks=%u, flags500=%u/501=%u\n",intro,complete[500],complete[501]);
    assert(complete[501]==1);
    printf("hub source: original Terminal intro completed in %u ticks; flag501 recovered through bytecode\n",intro);
    const char *stages[]={"stagML12","stagML13","stagML12","stagML11","stagML13","stagML11"};const int points[]={0,1,1,1,0,2};
    dw4_fb fb;assert(!dw4_fb_init(&fb,320,224));
    const char *from[]={"stagML11","stagML12","stagML13","stagML12","stagML11","stagML13"},*events[]={"matz00","matz01","matz01","matz00","matz01","matz00"};
    unsigned badges=0;
    for(unsigned i=0;i<sizeof stages/sizeof *stages;i++) {
        status_cycle(active,&frames,&fb);
        for(int cancel=1;cancel<=2;cancel++)exit_choice(active,&mount,from[i],events[i],&frames,cancel,&fb);
        exit_choice(active,&mount,from[i],events[i],&frames,0,&fb);
        const dw4_stagetravel *request=dw4_hubruntime_travel(active);
        assert(request->generate_pos==points[i]);
        assert(!strcasecmp(request->destination,stages[i]));
        dw4_hubruntime *previous=active;
        dw4_playerrecords *source=dw4_hubruntime_records(previous);
        const dw4_be_state *source_state=dw4_hubruntime_state(previous);
        uint8_t flags[1024];memcpy(flags,dw4_property_bytes(dw4_playerrecords_get(source,"GETCOMMON",0),"FLAG",NULL),1024);
        dw4_be_state original=*source_state;
        dw4_stageinput exit_input=*dw4_hubruntime_input_state(previous);assert(exit_input.disabled==1);
        dw4_hubruntime_source prior={source,source_state,&exit_input,dw4_hubruntime_time(previous)};
        dw4_hubruntime *hub=dw4_hubruntime_prepare(&mount,&prior,stages[i],points[i],1,error,sizeof error);
        if(!hub){fprintf(stderr,"prepare %s: %s\n",stages[i],error);return 1;}
        assert(dw4_hubruntime_records(hub)!=source && !memcmp(source_state,&original,sizeof original));
        assert(dw4_hubruntime_time(hub)==prior.world_ns && exit_input.disabled==1);
        active=hub;
        for(unsigned tick=0;tick<180;tick++) {
            dw4_hubruntime_input(hub,0,0,0,0,0);
            if(dw4_hubruntime_tick(hub,frames++*1000000000ULL/60)){fprintf(stderr,"tick %s/%u: %s\n",stages[i],tick,dw4_hubruntime_error(hub));return 1;}
            if(tick<30){dw4_lobby_control_state early;assert(!dw4_lobby_control(dw4_hubruntime_world(hub),&early) && !early.player_control);
                assert(dw4_controllers_live(dw4_hubruntime_models(hub),"i_pcnumic",0)!=1);} /* no badge before the player has control */
        }
        fprintf(stderr,"arrival %s input disable=%u\n",stages[i],dw4_hubruntime_input_state(hub)->disabled);
        assert(!dw4_hubruntime_input_state(hub)->disabled);
        dw4_lobby_control_state control;assert(!dw4_lobby_control(dw4_hubruntime_world(hub),&control));
        if(!control.player_control || !control.box_camera || !control.material_updates || !dw4_lobby_intro_done(dw4_hubruntime_world(hub)))
            fprintf(stderr,"restore %s: player%d camera%d materials%d done%d\n",stages[i],control.player_control,control.box_camera,control.material_updates,dw4_lobby_intro_done(dw4_hubruntime_world(hub)));
        assert(control.player_control && control.box_camera && control.material_updates && dw4_lobby_intro_done(dw4_hubruntime_world(hub)));
        /* Retail's player-number badge (MODELCTRL SETEFFECT i_pcnumic 480.0, 3d4390) appears only after 480 idle frames
         * (measured live: absent at 420, present at 540), so it is absent just after control returns and live once idle. */
        {int badge=dw4_controllers_live(dw4_hubruntime_models(hub),"i_pcnumic",0);
         assert(badge!=1);
         for(unsigned tick=0;tick<540;tick++) {
            dw4_hubruntime_input(hub,0,0,0,0,0);
            if(dw4_hubruntime_tick(hub,frames++*1000000000ULL/60)){fprintf(stderr,"idle %s/%u: %s\n",stages[i],tick,dw4_hubruntime_error(hub));return 1;}
            if(tick==300)assert(dw4_controllers_live(dw4_hubruntime_models(hub),"i_pcnumic",0)!=1);
         }
         badge=dw4_controllers_live(dw4_hubruntime_models(hub),"i_pcnumic",0);
         fprintf(stderr,"badge %s: %s\n",stages[i],badge<0?"no i_pcnumic model":badge?"live":"inactive");
         assert(badge!=0);badges+=badge==1;}
        const char *keys[]={"BIT","XDATA","LEVEL","HP","MP"};
        for(unsigned k=0;k<5;k++) {
            int32_t old_value,new_value;
            assert(!dw4_property_number(dw4_playerrecords_get(source,"GETPLAYER",0),keys[k],&old_value));
            assert(!dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(hub),"GETPLAYER",0),keys[k],&new_value) && old_value==new_value);
        }
        dw4_lobby_player_state appearance;assert(!dw4_lobby_player(dw4_hubruntime_world(hub),&appearance));
        char weapon_path[64];snprintf(weapon_path,sizeof weapon_path,"%s.igb",dw4_property_string_at(dw4_playerrecords_get(source,"GETPLAYER",0),"POWERSOCKETNAME",0));
        assert(!strcmp(appearance.weapon_asset,weapon_path));
        dw4_be_state before=*dw4_hubruntime_state(hub);
        int triangles=dw4_hubruntime_draw(hub,&fb,NULL);
        if(triangles<0){fprintf(stderr,"draw %s failed: %s\n",stages[i],dw4_lobby_script_error(dw4_hubruntime_world(hub)));return 1;}
        unsigned lit=0;for(unsigned pixel=0;pixel<320*224;pixel++)lit+=fb.rgba[4*pixel] || fb.rgba[4*pixel+1] || fb.rgba[4*pixel+2];assert(lit>1000);
        assert(!memcmp(&before,dw4_hubruntime_state(hub),sizeof before));
        assert(!memcmp(flags,dw4_property_bytes(dw4_playerrecords_get(source,"GETCOMMON",0),"FLAG",NULL),1024));
        if(argc>2){char path[512];snprintf(path,sizeof path,"%s/%s-active.png",argv[2],stages[i]);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
        printf("hub startup %s point %d: original start/first, restored player/camera/materials and %d drawn triangles; source session unchanged\n",stages[i],points[i],triangles);
        dw4_hubruntime_close(previous);
    }
    dw4_hubruntime_close(active);
    dw4_fb_free(&fb);dw4_databases_close(db);dw4_stageobjects_close(objects);
    dw4_scriptengine_close(e);dw4_filelist_close(f);dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);assert(badges);puts("hub runtime: original intro, player-number badge, live exit accept/cancel, six-route activation, STATUS restoration, session clocks, source isolation and cleanup pass");return 0;
}
