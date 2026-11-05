/* Destination stage entry from the connected hub: every portal target prepares and runs; the three interface scenes
 * (card album, save, load) fail with their named blocker. Headless. */
#include "hubtest.h"
#include "dw4/pads.h"
#include <unistd.h>
int main(int argc,char **argv)
{
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Stages",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    /* Portal destinations and arrival groups from the original travel table (hub-travel.md). */
    static const struct {const char *stage;int32_t point;} portals[]={
        {"StagML12",0},{"StagML13",0},{"StagML11",1},{"StagML13",1},{"StagML11",2},{"StagML12",1}};
    for(unsigned i=0;i<sizeof portals/sizeof *portals;i++){
        frame=0;dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,portals[i].stage,portals[i].point,1,error,sizeof error);
        if(!h){fprintf(stderr,"%s point %d: %s\n",portals[i].stage,portals[i].point,error);assert(0);}
        for(unsigned t=0;t<300;t++){
            dw4_hubruntime_input(h,0,0,0,0,0);
            if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){fprintf(stderr,"%s tick %u: %s\n",portals[i].stage,t,dw4_hubruntime_error(h));assert(0);}
        }
        dw4_hubruntime_close(h);
    }
    /* Local co-op in the four hub worlds: NINZU 2..4 prepares each of them, every joined slot exists at its authored arrival point, its model
     * controller is bound as a PLAYER/MODELCTRL receiver and the scene draws more than the single-player frame. */
    {
        static const char *const mates[]={"p_agumon","p_girumon","p_vmon"};
        static const char *const hubs[]={"stagML11","stagML12","stagML13","stagML02"};
        for(unsigned q=1;q<4;q++)assert(!dw4_playerrecords_create(players,db,(int)q,mates[q-1],"Mate",error,sizeof error));
        for(unsigned i=0;i<4;i++){
            int tri1=0;
            for(unsigned n=1;n<=4;n++){
                assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",(int32_t)n));
                for(unsigned q=1;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",(int)q),"ISUSE",q<n));
                frame=0;dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,hubs[i],0,1,error,sizeof error);
                if(!h){fprintf(stderr,"%s party %u: %s\n",hubs[i],n,error);assert(0);}
                for(unsigned t=0;t<400;t++){
                    dw4_hubruntime_input(h,0,0,0,0,0);
                    if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){fprintf(stderr,"%s party %u tick %u: %s\n",hubs[i],n,t,dw4_hubruntime_error(h));assert(0);}
                }
                dw4_lobby *w=dw4_hubruntime_world(h);assert(dw4_lobby_player_count(w)==n);
                float seen[4][3];
                for(unsigned q=0;q<4;q++){
                    assert(dw4_lobby_player_joined(w,q)==(q<n));
                    if(q>=n)continue;
                    dw4_lobby_walk_state ws;assert(!dw4_lobby_select_player(w,q) && !dw4_lobby_walk(w,&ws));
                    assert(dw4_lobby_player_model(w) && dw4_modelctrl_active(dw4_lobby_player_model(w)));
                    memcpy(seen[q],ws.position,sizeof seen[q]);
                    for(unsigned o=0;o<q;o++)assert(fabsf(seen[o][0]-seen[q][0])+fabsf(seen[o][2]-seen[q][2])>1);   /* each slot has its own arrival point */
                }
                dw4_lobby_select_player(w,0);
                dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
                int tri=dw4_hubruntime_draw(h,&fb,NULL);assert(tri>0);dw4_fb_free(&fb);
                if(n==1)tri1=tri;else assert(tri>tri1);   /* the mates' bodies are drawn */
                fprintf(stderr,"%s with %u players: %d triangles\n",hubs[i],n,tri);
                dw4_hubruntime_close(h);
            }
        }
        /* Three players in the Terminal, driven by scripted pads exactly as the engine feeds them (--input-script-pad): each pad moves only its own player. */
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",3));
        for(unsigned q=1;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",(int)q),"ISUSE",q<3));
        frame=0;dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,"stagML11",0,1,error,sizeof error);assert(h);
        unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
        assert(t<6000);idle(h,120);
        dw4_lobby *w=dw4_hubruntime_world(h);
        dw4_input_state pads[3],prev[3];
        for(unsigned k=0;k<3;k++){dw4_input_init(pads+k);dw4_input_init(prev+k);}
        float at[3][3];
        for(unsigned pad=0;pad<3;pad++){   /* pad 1 (the first player) = index 0, pads 2 and 3 = 1 and 2 */
            for(unsigned f=0;f<60;f++){   /* let the previous player's run wind down */
                for(unsigned k=0;k<3;k++)dw4_input_init(pads+k);
                dw4_hubruntime_input(h,0,0,0,0,0);dw4_hubruntime_input_mates(h,pads,prev);memcpy(prev,pads,sizeof prev);
                assert(!dw4_hubruntime_tick(h,frame++*1000000000ULL/60));
            }
            for(unsigned q=0;q<3;q++){dw4_lobby_walk_state ws;assert(!dw4_lobby_select_player(w,q) && !dw4_lobby_walk(w,&ws));memcpy(at[q],ws.position,sizeof at[q]);}
            dw4_lobby_select_player(w,0);
            for(unsigned f=0;f<90;f++){
                for(unsigned k=0;k<2;k++)dw4_input_script(pads+k,pad==k+1?"0-1000+up":NULL,(int)f);
                dw4_hubruntime_input(h,0,pad==0?1.0f:0.0f,0,0,0);
                dw4_hubruntime_input_mates(h,pads,prev);
                memcpy(prev,pads,sizeof prev);
                assert(!dw4_hubruntime_tick(h,frame++*1000000000ULL/60));
            }
            for(unsigned q=0;q<3;q++){
                dw4_lobby_walk_state ws;assert(!dw4_lobby_select_player(w,q) && !dw4_lobby_walk(w,&ws));
                float moved=fabsf(ws.position[0]-at[q][0])+fabsf(ws.position[2]-at[q][2]);
                fprintf(stderr,"Terminal, pad %u held: player %u moved %g\n",pad+1,q,moved);
                if(q==pad)assert(moved>5);else assert(moved<1);
            }
            dw4_lobby_select_player(w,0);
        }
        dw4_hubruntime_close(h);
#ifdef DW4_ENABLE_SDL2
        {   /* the SDL routing of the mates' controllers (device-less: instance ids stand in for opened pads) */
            dw4_matepads *m=dw4_matepads_open(NULL);assert(m);
            dw4_matepads_assign(m,0,101);dw4_matepads_assign(m,1,102);
            dw4_input_state ms[3];for(unsigned k=0;k<3;k++)dw4_input_init(ms+k);
            SDL_Event e;memset(&e,0,sizeof e);
            e.type=SDL_CONTROLLERBUTTONDOWN;e.cbutton.which=102;e.cbutton.button=SDL_CONTROLLER_BUTTON_A;
            assert(dw4_matepads_event(m,NULL,&e,ms)==1 && ms[1].cross && !ms[0].cross && !ms[2].cross);
            e.cbutton.which=999;assert(dw4_matepads_event(m,NULL,&e,ms)==0);   /* someone else's pad stays player 1's */
            e.cbutton.which=102;assert(dw4_matepads_event(m,NULL,&e,NULL)==0);   /* without mate states the pad is player 1's */
            memset(&e,0,sizeof e);e.type=SDL_CONTROLLERAXISMOTION;e.caxis.which=101;e.caxis.axis=SDL_CONTROLLER_AXIS_LEFTX;e.caxis.value=32767;
            assert(dw4_matepads_event(m,NULL,&e,ms)==1 && ms[0].lx>0.99f && ms[1].lx==0);
            e.caxis.axis=SDL_CONTROLLER_AXIS_LEFTY;e.caxis.value=-32767;
            assert(dw4_matepads_event(m,NULL,&e,ms)==1 && ms[0].ly>0.99f);   /* +y is up */
            memset(&e,0,sizeof e);e.type=SDL_CONTROLLERDEVICEREMOVED;e.cdevice.which=102;
            assert(dw4_matepads_event(m,NULL,&e,ms)==1 && !ms[1].cross);
            e.type=SDL_CONTROLLERBUTTONDOWN;e.cbutton.which=102;e.cbutton.button=SDL_CONTROLLER_BUTTON_A;
            assert(dw4_matepads_event(m,NULL,&e,ms)==0);   /* the removed pad is gone */
            dw4_matepads_close(m);
        }
#endif
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",1));
        for(unsigned q=1;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",(int)q),"ISUSE",0));
    }
    /* The hub HUD of a party: one panel per joined slot (the chunks' funcPlayerStatusGenerate generates i_stpnl01..04 once per joined player at x = -260, -110, 40, 190, y = -160,
     * i_stpnl00 once, and the point-message band i_stpnl06 once per joined player, or slot 4 for a single player); the party's panels draw in the model view from the pack's own gauges
     * and plates, the single player keeps the lobby HUD. */
    {
        for(unsigned n=1;n<=4;n+=n==1?1:2){   /* 1, 2, 4 */
            assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",(int32_t)n));
            for(unsigned q=1;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",(int)q),"ISUSE",q<n));
            for(unsigned q=0;q<n;q++){dw4_property_folder *pf=dw4_playerrecords_get(players,"GETPLAYER",(int)q);int32_t mhp=number(pf,"MHP");assert(!dw4_property_set_number(pf,"HP",mhp));}
            frame=0;dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,"stagML11",0,1,error,sizeof error);assert(h);
            dw4_fb early,late,hurt;assert(!dw4_fb_init(&early,640,448) && !dw4_fb_init(&late,640,448) && !dw4_fb_init(&hurt,640,448));
            idle(h,6);assert(dw4_hubruntime_draw(h,&early,NULL)>0);   /* the intro message is open: no HUD yet */
            unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
            assert(t<6000);idle(h,120);
            unsigned panels[7]={0};   /* active instances of i_stpnl00..06 */
            for(unsigned k=0;k<7;k++){
                char name[16];snprintf(name,sizeof name,"i_stpnl%02u",k);
                for(int32_t s=0;s<5;s++){const dw4_modelctrl *m=find(dw4_hubruntime_models(h),name,s);if(m && dw4_modelctrl_active(m))panels[k]++;}
            }
            fprintf(stderr,"Terminal with %u players: i_stpnl00..06 instances %u %u %u %u %u - %u\n",n,panels[0],panels[1],panels[2],panels[3],panels[4],panels[6]);
            assert(panels[0]==1 && panels[1]==n && panels[2]==n && panels[3]==n && panels[4]==n);
            assert(n==1?!!(find(dw4_hubruntime_models(h),"i_stpnl06",4) && dw4_modelctrl_active(find(dw4_hubruntime_models(h),"i_stpnl06",4))):panels[6]==n);
            for(int32_t s=0;s<(int32_t)n;s++){   /* each slot's panel stands at its authored place */
                dw4_modelctrl_actor a;dw4_modelctrl_actor_state(find(dw4_hubruntime_models(h),"i_stpnl03",s),&a);
                assert(fabsf(a.position[0]-(-260+150*s))<0.01f && fabsf(a.position[1]+160)<0.01f);
            }
            assert(dw4_hubruntime_draw(h,&late,NULL)>0);
            unsigned green_early=0,green_late[4]={0};
            for(unsigned s=0;s<4;s++)for(unsigned y=345;y<425;y++)for(unsigned x=60+150*s-45;x<60+150*s+45;x++){
                const uint8_t *p=late.rgba+4*((size_t)y*late.w+x);
                if(p[1]>180 && p[0]<120 && p[2]<140)green_late[s]++;
                if(!s){const uint8_t *e=early.rgba+4*((size_t)y*early.w+x);if(e[1]>180 && e[0]<120 && e[2]<140)green_early++;}
            }
            fprintf(stderr,"  HP arc pixels: before the HUD %u; slots %u %u %u %u\n",green_early,green_late[0],green_late[1],green_late[2],green_late[3]);
            for(unsigned s=0;s<4;s++)if(s<n)assert(green_late[s]>200);else if(n>1)assert(green_late[s]<green_late[0]/4);   /* a joined slot has its gauge; an empty slot has no panel */
            if(n>1){
                assert(green_early<green_late[0]/4);
                /* Slot 1's HP record falls to a tenth: its gauge eases down into the low-HP colours and its HP digits change, the other panels do not move. */
                dw4_property_folder *p1=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",1);int32_t mhp=number(p1,"MHP");
                assert(!dw4_property_set_number(p1,"HP",mhp/10));   /* below a quarter the ring turns orange and the portrait darkens (the gauge pose at the meter time) */
                idle(h,120);assert(dw4_hubruntime_draw(h,&hurt,NULL)>0);
                unsigned green_hurt[4]={0},changed[4]={0};
                for(unsigned s=0;s<4;s++)for(unsigned y=345;y<425;y++)for(unsigned x=60+150*s-45;x<60+150*s+90;x++){
                    const uint8_t *p=hurt.rgba+4*((size_t)y*hurt.w+x),*o=late.rgba+4*((size_t)y*late.w+x);
                    if(x<60+150*s+45 && p[1]>180 && p[0]<120 && p[2]<140)green_hurt[s]++;
                    if(abs(p[0]-o[0])+abs(p[1]-o[1])+abs(p[2]-o[2])>60)changed[s]++;
                }
                fprintf(stderr,"  after slot 1 falls to HP %d/%d: HP arc pixels %u %u %u %u, changed pixels %u %u %u %u\n",mhp/10,mhp,green_hurt[0],green_hurt[1],green_hurt[2],green_hurt[3],changed[0],changed[1],changed[2],changed[3]);
                assert(green_hurt[1]*10<green_late[1]*3);   /* slot 1's green arc is gone (orange) */
                assert(green_hurt[0]*10>green_late[0]*9);   /* slot 0's did not */
                assert(changed[1]>150);
                for(unsigned s=2;s<n;s++){assert(green_hurt[s]*10>green_late[s]*9);}
                assert(!dw4_property_set_number(p1,"HP",mhp));
            }
            dw4_fb_free(&early);dw4_fb_free(&late);dw4_fb_free(&hurt);dw4_hubruntime_close(h);
        }
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",1));
        for(unsigned q=1;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",(int)q),"ISUSE",0));
    }
    /* Interface scenes: IS11 (card album), IS12 (save) and IS13 (load/join) are hosted natively. */
    char dir[]="/tmp/dw4-stages-XXXXXX";assert(mkdtemp(dir));assert(!setenv("DW4_SAVE_DIR",dir,1));
    static const char *const hosted[]={"stagIS11","stagIS12","stagIS13"};
    for(unsigned i=0;i<3;i++){
        dw4_hubruntime *save=dw4_hubruntime_prepare(&mount,&initial,hosted[i],0,1,error,sizeof error);
        if(!save){fprintf(stderr,"%s: %s\n",hosted[i],error);assert(0);}
        assert(!dw4_hubruntime_world(save) && dw4_hubruntime_scene(save));
        uint64_t ns=dw4_hubruntime_time(save);
        for(unsigned t=0;t<300;t++){ns+=16666667ULL;dw4_hubruntime_input(save,0,0,0,0,0);assert(!dw4_hubruntime_tick(save,ns));}
        assert(!dw4_hubruntime_travel(save)->pending);   /* the scene is waiting for the player's choices */
        dw4_hubruntime_close(save);
    }
    unsetenv("DW4_SAVE_DIR");
    {char f[700];snprintf(f,sizeof f,"%s/%s",dir,"BASLUS-20836savedata");remove(f);}rmdir(dir);
    printf("hub stages: the six portal destinations prepare and run (and the four hub worlds with 2-4 players, each pad driving its own player); stagIS11, stagIS12 and stagIS13 run as hosted scenes\n");
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    return 0;
}
