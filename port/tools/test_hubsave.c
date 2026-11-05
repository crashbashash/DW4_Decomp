/* The Save Keeper end to end, headless: Central's n_digilfm[0] (live Cross probe, original dialogue, accepted choice) requests
 * stagIS12; the interface-scene host runs the original pack with the native SaveCtrl/SaveIntf, saves the character to a host
 * card; the save loads back; SaveCtrl's exit (stagML12 at point 2) prepares Central again and control returns. */
#include "savetest.h"

static unsigned run_ticks;
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","KeeperPl",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};

    /* 1. Central: the Save Keeper's conversation ends in a stagIS12 request. */
    frame=0;dw4_hubruntime *h=boot_central(&mount,&initial);
    const dw4_modelctrl *keeper=find(dw4_hubruntime_models(h),"n_digilfm",0);assert(keeper);
    assert(talk_to(h,keeper));
    const dw4_stagetravel *travel=dw4_hubruntime_travel(h);unsigned k=0;
    for(;k<4000 && !travel->pending;k++)step(h,0,(!control(h)&&k%45==44)?0x4000:0);
    assert(k<4000 && travel->pending && !strcmp(travel->destination,"stagIS12"));
    /* IS11 (the card album) is hosted by the same scene host and needs no save library: it prepares and waits at its menu. */
    {
        char perr[512];dw4_hubruntime *card=dw4_hubruntime_prepare(&mount,&initial,"stagIS11",0,1,perr,sizeof perr);
        if(!card){fprintf(stderr,"stagIS11: %s\n",perr);assert(0);}
        assert(!dw4_hubruntime_world(card) && dw4_hubruntime_scene(card));dw4_hubruntime_close(card);
    }

    /* 2. stagIS12 prepared by the hub runtime itself (the path the engine takes): the native save library directory
     * comes from DW4_SAVE_DIR here; the pad saves the character. */
    char dir[]="/tmp/dw4-hubsave-XXXXXX";assert(mkdtemp(dir));assert(!setenv("DW4_SAVE_DIR",dir,1));
    dw4_hubruntime_source from_hub={dw4_hubruntime_records(h),dw4_hubruntime_state(h),NULL,dw4_hubruntime_time(h)};
    dw4_hubruntime *scene_hub=dw4_hubruntime_prepare(&mount,&from_hub,"stagIS12",0,1,error,sizeof error);
    if(!scene_hub){fprintf(stderr,"prepare stagIS12: %s\n",error);assert(0);}
    assert(!dw4_hubruntime_world(scene_hub) && dw4_hubruntime_scene(scene_hub));
    uint64_t ns=from_hub.world_ns;unsigned ticks=0;int pos=-9;char stage[128]="";
    for(;ticks<12000;ticks++){
        const dw4_saveintf *si=dw4_savescene_intf(dw4_hubruntime_scene(scene_hub));dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(si,0,&t);
        uint32_t pressed=0;
        if(t.control==8&&t.control_sub==3)pressed=(ticks%20==0)?0x8:0;else if(ticks%20==0)pressed=0x4000;
        dw4_hubruntime_input(scene_hub,0,0,0,0,pressed);
        ns+=16666667ULL;
        if(dw4_hubruntime_tick(scene_hub,ns)){fprintf(stderr,"scene tick %u: %s\n",ticks,dw4_hubruntime_error(scene_hub));assert(0);}
        const dw4_stagetravel *tr=dw4_hubruntime_travel(scene_hub);
        if(tr->pending){snprintf(stage,sizeof stage,"%s",tr->destination);pos=tr->generate_pos;break;}
    }
    assert(ticks<12000 && !strcmp(stage,"stagML12") && pos==2);
    assert(dw4_hubruntime_cancel_travel(scene_hub)==-1); /* no retained source to restore */
    dw4_memcard *card=dw4_memcard_open(dir);assert(card);
    verify_card(card,dw4_hubruntime_records(scene_hub));
    char bak[700];snprintf(bak,sizeof bak,"%s/%s.bak",dir,DW4_MEMCARD_FILE);assert(!access(bak,R_OK));

    /* 3. Back to Central at SaveCtrl's generate position with the saved session; control returns. */
    dw4_hubruntime_source back={dw4_hubruntime_records(scene_hub),dw4_hubruntime_state(scene_hub),dw4_hubruntime_input_state(scene_hub),dw4_hubruntime_time(scene_hub)};
    dw4_hubruntime *h2=dw4_hubruntime_prepare(&mount,&back,stage,pos,1,error,sizeof error);
    if(!h2){fprintf(stderr,"return to Central: %s\n",error);assert(0);}
    dw4_hubruntime_close(h);
    uint64_t base=back.world_ns;
    unsigned t=0;
    for(;t<1500;t++){
        dw4_hubruntime_input(h2,0,0,0,0,0);
        assert(!dw4_hubruntime_tick(h2,base+(uint64_t)(t+1)*16666667ULL+1));
        dw4_lobby_control_state c;if(t>60&&!dw4_lobby_control(dw4_hubruntime_world(h2),&c)&&c.player_control)break;
    }
    assert(t<1500);
    dw4_lobby_walk_state arrival;assert(!dw4_lobby_walk(dw4_hubruntime_world(h2),&arrival));
    printf("hub save: arrival position (%.3f, %.3f, %.3f)\n",arrival.position[0],arrival.position[1],arrival.position[2]);
    if(getenv("DW4_ARRIVAL_SHOT")){dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h2,&fb,NULL)>0);assert(!dw4_png_write(getenv("DW4_ARRIVAL_SHOT"),fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);}
    dw4_hubruntime_close(h2);dw4_hubruntime_close(scene_hub);
    unsetenv("DW4_SAVE_DIR");
    run_ticks=ticks;
    printf("hub save: Save Keeper -> stagIS12 via the hub runtime (%u ticks) -> card slot 0 round trip with .bak -> stagML12 point %d, control restored after %u ticks\n",
        run_ticks,pos,t);
    dw4_memcard_close(card);remove_dir(dir);
    return 0;
}
