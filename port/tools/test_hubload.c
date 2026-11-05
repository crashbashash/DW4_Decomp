/* The load/join screen (stagIS13) end to end, headless: the Terminal's n_digilff[0] (live Cross probe, original dialogue,
 * accepted choice) requests stagIS13; the interface-scene host runs the original pack 812 with the native LoadCtrl2/LoadIntf2.
 * Player 0 already has a character (the hub case), so the screen shows its panel, marks it chosen and waits for START;
 * LoadCtrl2 then closes the windows, publishes NINZU and leaves for stagML11 at generate position 4, where the Terminal is
 * prepared again and control returns. No save is written by this screen. */
#include "savetest.h"

static dw4_hubruntime *boot_terminal(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    char error[512];
    dw4_hubruntime *h=dw4_hubruntime_prepare(mount,source,"stagML11",0,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare stagML11: %s\n",error);assert(0);}
    unsigned t=0;
    for(;t<2600;t++){step(h,0,t%10==0?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
    assert(t<2600);idle(h,60);return h;
}
/* The Terminal's NPCs stand on raised platforms: land beside the NPC at its own height, wake it, walk up and press Cross. */
static int talk_on_platform(dw4_hubruntime *h,const dw4_modelctrl *npc)
{
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(npc,&a);
    for(int i=0;i<16;i++){
        float r=i<8?30:55,ang=(float)(i%8)*0.78539816f;
        float at[3]={a.position[0]+r*cosf(ang),a.position[1],a.position[2]+r*sinf(ang)};
        move_player(h,at);idle(h,90);
        dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        if(fabsf(w.position[1]-a.position[1])>6)continue;
        if(!approach(h,npc,9))continue;
        step(h,0,0x4000);
        if(dw4_lobby_talk_result(dw4_hubruntime_world(h))==1)return 1;
        idle(h,10);
    }
    return 0;
}
static int32_t player_number(dw4_playerrecords *r,int player,const char *key)
{int32_t v;assert(!dw4_property_number(dw4_playerrecords_get(r,"GETPLAYER",player),key,&v));return v;}

int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_agumon","LoadPl",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};

    /* 1. The Terminal: n_digilff[0]'s conversation ends in a stagIS13 request. */
    frame=0;dw4_hubruntime *h=boot_terminal(&mount,&initial);
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilff",0);assert(npc);
    assert(talk_on_platform(h,npc));
    const dw4_stagetravel *travel=dw4_hubruntime_travel(h);unsigned k=0;
    for(;k<4000 && !travel->pending;k++)step(h,0,(!control(h)&&k%45==44)?0x4000:0);
    if(!(k<4000 && travel->pending))fprintf(stderr,"Terminal conversation did not request a stage (k=%u)\n",k);
    assert(k<4000 && travel->pending && !strcmp(travel->destination,"stagIS13"));
    int32_t xdata=player_number(dw4_hubruntime_records(h),0,"XDATA"),level=player_number(dw4_hubruntime_records(h),0,"LEVEL");

    /* 2. stagIS13 prepared by the hub runtime (the engine's path) over an empty save library. */
    char dir[]="/tmp/dw4-hubload-XXXXXX";assert(mkdtemp(dir));assert(!setenv("DW4_SAVE_DIR",dir,1));
    dw4_hubruntime_source from_hub={dw4_hubruntime_records(h),dw4_hubruntime_state(h),NULL,dw4_hubruntime_time(h)};
    dw4_hubruntime *scene_hub=dw4_hubruntime_prepare(&mount,&from_hub,"stagIS13",0,1,error,sizeof error);
    if(!scene_hub){fprintf(stderr,"prepare stagIS13: %s\n",error);assert(0);}
    assert(!dw4_hubruntime_world(scene_hub) && dw4_hubruntime_scene(scene_hub));
    uint64_t ns=from_hub.world_ns;unsigned ticks=0,at_start=0,saw8=0,saw83=0;int pos=-9;char stage[128]="";
    for(;ticks<12000;ticks++){
        const dw4_saveintf *si=dw4_savescene_intf(dw4_hubruntime_scene(scene_hub));dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(si,0,&t);
        uint32_t pressed=0;
        if(t.control==8)saw8=1;
        if(t.control==8&&t.control_sub==3&&t.control_subsub==1){
            if(!saw83){
                for(int w=0;w<30;w++){dw4_hubruntime_input(scene_hub,0,0,0,0,0);ns+=16666667ULL;assert(!dw4_hubruntime_tick(scene_hub,ns));}
                dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
                int n=dw4_hubruntime_draw(scene_hub,&fb,NULL);assert(n>=0);
                unsigned lit=0;for(size_t i=0;i<(size_t)fb.w*fb.h;i++)lit+=fb.rgba[4*i]||fb.rgba[4*i+1]||fb.rgba[4*i+2];
                assert(lit>1000);
                if(capture_dir){char path[512];snprintf(path,sizeof path,"%s/load-start.png",capture_dir);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
                dw4_fb_free(&fb);
            }
            saw83=1;if(!at_start)at_start=ticks;
            pressed=(ticks%20==0)?0x8:0;   /* START, once every player in use has chosen */
        }
        dw4_hubruntime_input(scene_hub,0,0,0,0,pressed);
        ns+=16666667ULL;
        if(dw4_hubruntime_tick(scene_hub,ns)){fprintf(stderr,"scene tick %u: %s\n",ticks,dw4_hubruntime_error(scene_hub));assert(0);}
        const dw4_stagetravel *tr=dw4_hubruntime_travel(scene_hub);
        if(tr->pending){snprintf(stage,sizeof stage,"%s",tr->destination);pos=tr->generate_pos;break;}
    }
    assert(ticks<12000 && saw8 && saw83);
    if(strcmp(stage,"stagML11")||pos!=4)fprintf(stderr,"load screen exit: %s at %d\n",stage,pos);
    assert(!strcmp(stage,"stagML11") && pos==4);
    dw4_playerrecords *after=dw4_hubruntime_records(scene_hub);
    assert(player_number(after,0,"XDATA")==xdata && player_number(after,0,"LEVEL")==level && player_number(after,0,"ISUSE")==1);
    assert(!strcmp(dw4_property_string(dw4_playerrecords_get(after,"GETPLAYER",0),"DIGIMONNAME"),"p_agumon"));
    int32_t ninzu;assert(!dw4_property_number(dw4_playerrecords_get(after,"GETCOMMON",0),"NINZU",&ninzu) && ninzu==1);
    for(int p=1;p<4;p++)assert(player_number(after,p,"ISUSE")==0);
    char file[700];snprintf(file,sizeof file,"%s/%s",dir,DW4_MEMCARD_FILE);assert(access(file,F_OK)!=0); /* nothing was saved */

    /* 3. Back to the Terminal at generate position 4 with the session; control returns. */
    dw4_hubruntime_source back={dw4_hubruntime_records(scene_hub),dw4_hubruntime_state(scene_hub),dw4_hubruntime_input_state(scene_hub),dw4_hubruntime_time(scene_hub)};
    dw4_hubruntime *h2=dw4_hubruntime_prepare(&mount,&back,stage,pos,1,error,sizeof error);
    if(!h2){fprintf(stderr,"return to the Terminal: %s\n",error);assert(0);}
    dw4_hubruntime_close(h);
    uint64_t base=back.world_ns;unsigned t=0;
    for(;t<2600;t++){
        dw4_hubruntime_input(h2,0,0,0,0,0);
        assert(!dw4_hubruntime_tick(h2,base+(uint64_t)(t+1)*16666667ULL+1));
        dw4_lobby_control_state c;if(t>60&&!dw4_lobby_control(dw4_hubruntime_world(h2),&c)&&c.player_control)break;
    }
    assert(t<2600);
    {dw4_lobby_walk_state arrival;assert(!dw4_lobby_walk(dw4_hubruntime_world(h2),&arrival));
     printf("hub load: arrival position (%.3f, %.3f, %.3f)\n",arrival.position[0],arrival.position[1],arrival.position[2]);
     if(getenv("DW4_ARRIVAL_SHOT")){dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h2,&fb,NULL)>0);assert(!dw4_png_write(getenv("DW4_ARRIVAL_SHOT"),fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);}}
    dw4_hubruntime_close(h2);dw4_hubruntime_close(scene_hub);
    unsetenv("DW4_SAVE_DIR");remove_dir(dir);
    printf("hub load: Terminal n_digilff[0] -> stagIS13 via the hub runtime (%u ticks, START at %u) -> record untouched, NINZU 1, nothing saved -> stagML11 point %d, control restored after %u ticks\n",
        ticks,at_start,pos,t);
    return 0;
}
