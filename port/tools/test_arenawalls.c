/* The practice arena's boundary is made of kind-0x802 wall infos (36 triangles, x -120..120, z -75..195): players (check flag 7) collide with them, so a held stick
 * from the arena centre stops at the boundary. The kind-2 graphs of the stage have only two triangles, so without the 0x802 walls the player walked out. Headless. */
#include "hubtest.h"
int main(int argc,char **argv)
{
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Arena",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,"stag0001",0,1,error,sizeof error);assert(h);
    unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
    assert(t<6000);idle(h,60);
    static const float dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};   /* the stick as the engine reads it (+Y up) */
    unsigned out=0;
    for(unsigned d=0;d<4;d++) {
        char where[96];snprintf(where,sizeof where,"V<0,10,60>/V<0,0,0>");
        dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        dw4_script_value r;assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));idle(h,30);
        dw4_lobby_walk_state w;
        for(unsigned k=0;k<480;k++){dw4_hubruntime_input(h,dir[d][0],dir[d][1],0,0,0);assert(!dw4_hubruntime_tick(h,frame++*1000000000ULL/60));}
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        int inside=w.position[0]>=-121 && w.position[0]<=121 && w.position[2]>=-76 && w.position[2]<=196;
        fprintf(stderr,"  stick (%g,%g) from the arena centre: stops at (%.1f,%.1f,%.1f) %s\n",dir[d][0],dir[d][1],w.position[0],w.position[1],w.position[2],inside?"inside":"OUTSIDE");
        out+=!inside;
    }
    dw4_hubruntime_close(h);
    assert(!out);
    puts("arena walls: a held stick in every direction stops inside the practice arena's 0x802 boundary");
    return 0;
}
