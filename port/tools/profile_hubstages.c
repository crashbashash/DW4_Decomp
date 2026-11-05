/* Per-stage CPU cost of the connected hub, headless: prepares every portal destination and the three interface scenes,
 * runs them for a few seconds and prints the average per-frame tick time and, for world stages, the CPU-side part of the
 * world draw (scene-node driving and the mesh/triangle build).  The GPU passes are not run here, so these figures
 * isolate the work the port does on the CPU every frame.  `make profile-hubstages [PROFILE_BUDGET_MS=8]` fails when a
 * stage's CPU-side cost exceeds the budget.  Companion to tools/profile_lobby.py (the full boot-to-lobby route). */
#include "hubtest.h"
#include <time.h>
#include <unistd.h>
void dw4_lobby_trace_take(double out[16]);
static double now_ms(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec*1e3+t.tv_nsec/1e6;}
int main(int argc,char **argv)
{
    const char *roms=argc>1?argv[1]:"../local/extracted";double budget=argc>2?atof(argv[2]):0;int bad=0;
    int fw=argc>3?atoi(argv[3]):1280,fh=argc>4?atoi(argv[4]):960;   /* the live window size by default */
    dw4_mount mount;assert(!dw4_mount_open(&mount,roms));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Profile",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    char dir[]="/tmp/dw4-profile-XXXXXX";assert(mkdtemp(dir));assert(!setenv("DW4_SAVE_DIR",dir,1));
    static const struct {const char *stage;int32_t point;} stages[]={
        {"StagML12",0},{"StagML13",0},{"StagML11",1},{"StagML13",1},{"StagML11",2},{"StagML12",1},
        {"stagIS11",0},{"stagIS12",0},{"stagIS13",0}};
    dw4_fb fb;assert(!dw4_fb_init(&fb,fw,fh));
    printf("%-10s %5s %8s %8s %10s %9s %7s %9s\n","stage","point","tick ms","draw ms","node-drive","mesh-loop","(pose","instances)");
    for(unsigned i=0;i<sizeof stages/sizeof *stages;i++){
        dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,stages[i].stage,stages[i].point,1,error,sizeof error);
        if(!h){fprintf(stderr,"%s: %s\n",stages[i].stage,error);return 1;}
        uint64_t ns=dw4_hubruntime_time(h);double tick=0,draw=0,lt[16];unsigned n=0;
        for(unsigned t=0;t<240;t++){
            double a=now_ms();ns+=16666667ULL;dw4_hubruntime_input(h,0,0,0,0,0);
            if(dw4_hubruntime_tick(h,ns)){fprintf(stderr,"%s tick: %s\n",stages[i].stage,dw4_hubruntime_error(h));return 1;}
            double b=now_ms();
            if(t>=120){   /* the first two seconds are the arrival fade-in and one-off setup */
                if(t==120)dw4_lobby_trace_take(lt);
                if(dw4_hubruntime_draw(h,&fb,NULL)<0){fprintf(stderr,"%s draw: %s\n",stages[i].stage,dw4_hubruntime_error(h));return 1;}
                draw+=now_ms()-b;tick+=b-a;n++;
            }
        }
        dw4_lobby_trace_take(lt);
        double cpu=tick/n+lt[6]/n+lt[0]/n;
        printf("%-10s %5d %8.2f %8.2f %10.2f %9.2f %7.2f %9.2f%s\n",stages[i].stage,(int)stages[i].point,tick/n,draw/n,lt[6]/n,lt[0]/n,lt[7]/n,lt[8]/n,
               budget>0&&cpu>budget?"   OVER BUDGET":"");
        if(budget>0&&cpu>budget)bad=1;
        dw4_hubruntime_close(h);
    }
    {char p[700];snprintf(p,sizeof p,"%s/%s",dir,"BASLUS-20836savedata");remove(p);}rmdir(dir);
    dw4_fb_free(&fb);dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    return bad;
}
