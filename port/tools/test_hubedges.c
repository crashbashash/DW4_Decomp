/* Walkable edges of the Terminal and Central against the retail reads (handoffs retail-hub-verify, retail-central-blockers): from a start point on a platform, hold the stick in
 * one direction for seven seconds and report where the player stops (or falls). The retail numbers are in the table; the tolerance is a few units, since
 * the retail positions were sampled at 12 Hz. Headless. */
#include "hubtest.h"
/* axis: 0 compare x and z, 1 compare z only (x was not read), 2 compare the height only (the player walks on after the drop) */
struct edge {const char *stage;const char *name;float start[3];float sx,sy;float want[3];int falls;float tol;int axis;};
/* sx,sy: the stick as the engine reads it (+Y up). Retail 'push up' moves toward -z. */
static const struct edge edges[]={
    {"stagML12","central down",{-60,40,-40},0,-1,{-54.6f,40.0f,-24.7f},0,4,0},
    {"stagML12","central up (8 s)",{-60,40,-40},0,1,{-155.97f,40.9f,-138.3f},0,3,0},
    {"stagML12","central left (8 s)",{-60,40,-40},-1,0,{-245.3f,40.0f,131.8f},0,3,0},
    {"stagML12","central bridge north",{-15,40,-42},0,1,{-15,40.0f,-45.3f},0,1.5f,1},
    {"stagML12","central bridge south",{-15,40,-42},0,-1,{-15,40.0f,-34.7f},0,1.5f,1},
    {"stagML11","terminal north rim",{0,20,-86},0,1,{-4.0f,20.0f,-113.8f},0,4,0},
    {"stagML11","terminal east rim",{20,20,-90},1,0,{25.6f,20.0f,-91.0f},0,4,0},
    {"stagML11","terminal south edge",{0,20,-65},0,-1,{16.1f,10.0f,-47.9f},1,6,2},
};
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Edges",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    unsigned bad=0;const char *loaded=NULL;dw4_hubruntime *h=NULL;
    for(unsigned i=0;i<sizeof edges/sizeof *edges;i++){
        const struct edge *g=edges+i;
        if(!loaded || strcmp(loaded,g->stage)){
            if(h)dw4_hubruntime_close(h);
            frame=0;h=dw4_hubruntime_prepare(&mount,&initial,g->stage,0,1,error,sizeof error);assert(h);loaded=g->stage;
            unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
            assert(t<6000);idle(h,60);
        }
        char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",g->start[0],g->start[1],g->start[2]);
        dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        dw4_script_value r;assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
        idle(h,30);
        dw4_lobby_control_state c;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c));
        /* the raw stick, as retail was pushed: the engine applies the camera */
        float sx=g->sx,sy=g->sy;(void)c;
        dw4_lobby_walk_state w;float lowest=g->start[1];
        float p20[3]={0};
        for(unsigned t=0;t<420;t++){dw4_hubruntime_input(h,sx,sy,0,0,0);
            assert(!dw4_hubruntime_tick(h,frame++*1000000000ULL/60));
            assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));if(w.position[1]<lowest)lowest=w.position[1];if(t==19)memcpy(p20,w.position,12);if(getenv("HUBEDGE_TRACE") && t%15==14)fprintf(stderr,"   t%3u (%.1f,%.1f,%.1f)\n",t+1,w.position[0],w.position[1],w.position[2]);}
        float dx=w.position[0]-g->want[0],dz=w.position[2]-g->want[2],dy=w.position[1]-g->want[1];
        int ok=(g->axis==2 || (g->axis==1?fabsf(dz):sqrtf(dx*dx+dz*dz))<=g->tol) && fabsf(dy)<=1.5f && (!g->falls || lowest<g->start[1]-5);
        fprintf(stderr,"  first 20 ticks: (%.1f,%.1f) ",p20[0]-g->start[0],p20[2]-g->start[2]);
        fprintf(stderr,"%-22s start (%g,%g,%g) -> (%.1f,%.1f,%.1f) lowest y %.1f; retail (%.1f,%.1f,%.1f)%s %s\n",g->name,g->start[0],g->start[1],g->start[2],
            w.position[0],w.position[1],w.position[2],lowest,g->want[0],g->want[1],g->want[2],g->falls?" falls":"",ok?"ok":"DIFFERS");
        {   /* does the port have floor 2 and 6 units beyond the retail stop, along the way the retail player was walking? */
            float vx=g->want[0]-g->start[0],vz=g->want[2]-g->start[2],vl=hypotf(vx,vz);if(vl<1)vl=1;vx/=vl;vz/=vl;
            for(unsigned k=0;k<2;k++){float d=k?6:2,old[3]={g->want[0],g->want[1],g->want[2]},pos[3]={g->want[0]+vx*d,g->want[1],g->want[2]+vz*d};
                unsigned c2=dw4_lobby_walk_probe(dw4_hubruntime_world(h),old,pos);
                fprintf(stderr,"  beyond retail stop +%g: floor y %.1f contacts %u (2 = no floor)\n",d,pos[1],c2);}
        }
        bad+=!ok;
    }
    if(getenv("HUBEDGE_TERM")){   /* Terminal ring, south edge: probe steps toward +z from the ring at several x */
        if(h)dw4_hubruntime_close(h);
        frame=0;h=dw4_hubruntime_prepare(&mount,&initial,"stagML11",0,1,error,sizeof error);assert(h);
        unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
        for(int xi=-12;xi<=12;xi+=6){float pos[3]={(float)xi,20,-90};
            for(unsigned k=0;k<80;k++){float old[3]={pos[0],pos[1],pos[2]},n[3]={pos[0],pos[1],pos[2]+1};unsigned c2=dw4_lobby_walk_probe(dw4_hubruntime_world(h),old,n);
                if(c2&1){fprintf(stderr,"term x %d: wall at z %.1f y %.1f\n",xi,pos[2],pos[1]);break;}
                memcpy(pos,n,12);if(c2&2){fprintf(stderr,"term x %d: support lost at z %.1f y %.1f\n",xi,pos[2],pos[1]);}
                if(pos[1]<12){fprintf(stderr,"term x %d: down to y %.1f at z %.1f\n",xi,pos[1],pos[2]);break;}}}
    }
    if(getenv("HUBEDGE_GRID")){   /* Terminal: wall (#), floor at y 20 (.), floor lower (-), none (space); a probe step of 1 toward +z from each cell */
        if(h)dw4_hubruntime_close(h);
        frame=0;h=dw4_hubruntime_prepare(&mount,&initial,"stagML11",0,1,error,sizeof error);assert(h);
        unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
        for(int z=-124;z<=-36;z+=2){char row[80];int n=0;for(int x=-50;x<=50;x+=2){float old[3]={(float)x,20,(float)z},p2[3]={(float)x,20,(float)z+.5f};unsigned c2=dw4_lobby_walk_probe(dw4_hubruntime_world(h),old,p2);
                row[n++]=c2&1?'#':c2&2?' ':p2[1]>19.5f?'.':'-';}row[n]=0;fprintf(stderr,"grid z %4d %s\n",z,row);}
    }
    if(getenv("HUBEDGE_CGRID")){   /* Central: floor (.), wall in some direction (#), no floor (space); x HUBEDGE_X0.. step 2, z HUBEDGE_Z0.. */
        if(h)dw4_hubruntime_close(h);
        frame=0;h=dw4_hubruntime_prepare(&mount,&initial,"stagML12",0,1,error,sizeof error);assert(h);
        unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
        int x0=atoi(getenv("HUBEDGE_CGRID")),z0=atoi(getenv("HUBEDGE_CGRID")+strcspn(getenv("HUBEDGE_CGRID"),",")+1);
        for(int z=z0;z<=z0+80;z+=2){char row[80];int n=0;for(int x=x0;x<=x0+100;x+=2){unsigned any=0,nofloor=0;
                for(unsigned d=0;d<4;d++){float old[3]={(float)x,40,(float)z},p2[3]={x+(d==0)-(d==1)*1.f,40,z+(d==2)-(d==3)*1.f};unsigned c2=dw4_lobby_walk_probe(dw4_hubruntime_world(h),old,p2);any|=c2&1;nofloor|=c2&2;}
                row[n++]=any?'#':nofloor?' ':'.';}row[n]=0;fprintf(stderr,"cgrid z %4d %s\n",z,row);}
    }
    if(getenv("HUBEDGE_MAP")){   /* Central: how far a probe walk from the arrival platform gets in 16 headings (wall = contact bit 1, no floor = bit 2) */
        if(h)dw4_hubruntime_close(h);
        frame=0;h=dw4_hubruntime_prepare(&mount,&initial,"stagML12",0,1,error,sizeof error);assert(h);
        unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
        for(unsigned a=0;a<16;a++){float ang=a*6.2831853f/16,dx=sinf(ang),dz=-cosf(ang),pos[3]={-60,40,-40};unsigned why=0;float d=0;
            for(;d<400;d+=1){float old[3]={pos[0],pos[1],pos[2]},n[3]={pos[0]+dx,pos[1],pos[2]+dz};unsigned c2=dw4_lobby_walk_probe(dw4_hubruntime_world(h),old,n);
                if(c2&3){why=c2;break;}memcpy(pos,n,12);}
            fprintf(stderr,"map heading %5.1f deg: stops at (%.1f,%.1f,%.1f) after %g units, %s\n",ang*57.29578f,pos[0],pos[1],pos[2],d,why&1?"wall":why&2?"no floor":"open to 400");}
    }
    if(h)dw4_hubruntime_close(h);
    printf("hub edges: %u of %zu differ from the retail reads\n",bad,sizeof edges/sizeof *edges);
    return bad?1:0;
}
