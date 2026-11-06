/* The Action2 host starts each MOTIONSET when the component walk reaches it (beAction2_StartComponents -> beAction2MOTIONSET_Start, 0x377340), and a
 * `WAITCHECK Motion` holds the walk until THAT motion has played out (beAction2WAITCHECK_Update, A2_WAIT_MOTION). An action with several MOTIONSETs
 * separated by Motion waits therefore plays them in order (: Mammothmon's ACTN03 is actn03 1.517 s, wait, actn04 0.05 s, wait; the port used
 * to register both at the start so only the last played and the sequence lasted 3-5 ticks).
 *   host level:   fixed programs with known durations (order, durations, consecutive MOTIONSETs, a MOTIONSET behind a Frame wait, one motion unchanged)
 *   pack level:   the retail Mammothmon pack (needs the extracted assets) still reads ACTN03 as four components, two of them MOTIONSETs. The sequence span itself
 *                 (SQ_ATCK3 about 103 ticks, 1.72 s with the blend model below) is asserted where the boss runs: test_fieldstage dungeonroute2 and dungeondoors2 (dng102b3). */
#include "dw4/action2host.h"
#include "dw4/modelctrl.h"
#include "dw4/modelai.h"
#include "dw4/igfile.h"
#include "dw4/mount.h"
#include "../src/arenalist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TICK 16666667LL
static dw4_action2_component motion(const char *name,int64_t duration,const char *loop)
{return (dw4_action2_component){DW4_A2_MOTIONSET,name,0,0,loop,duration,0};}
/* A MOTIONSET with a blend time (hokanTime frames; 60 frames per second as the host converts it, dw4_model_ai_duration). */
static dw4_action2_component motionb(const char *name,int64_t duration,const char *loop,float frames)
{
    uint32_t bits;memcpy(&bits,&frames,4);
    return (dw4_action2_component){DW4_A2_MOTIONSET,name,0,bits,loop,duration,dw4_model_ai_duration(bits)};
}
static dw4_action2_component waitc(const char *name,uint32_t frames_bits)
{return (dw4_action2_component){DW4_A2_WAITCHECK,name,frames_bits,0,"",0,0};}
static const char *playing(dw4_action2_host *h)
{
    dw4_action2_record r=dw4_action2_host_records(h);
    return al_text(r.arena,DW4_ARENA_OBJ(r.arena,igAnimation,r.animation)->_name);
}
/* Run the host from clock 0; return the tick at which the program completes and fill `switched` with the first tick each listed name was playing. */
static char final_motion[64];   /* the motion playing when the last run ended */
static int run(const dw4_action2_component *c,unsigned n,const char *const *names,unsigned nnames,int *first_seen)
{
    dw4_action2_host h;dw4_action2_host_init(&h);assert(!h.error);
    dw4_action2_host_start_program(&h,c,n,0);assert(!h.error);
    for(unsigned i=0;i<nnames;i++)first_seen[i]=-1;
    int done=-1;
    for(int t=0;t<600 && done<0;t++) {
        const char *now=playing(&h);
        for(unsigned i=0;i<nnames;i++)if(first_seen[i]<0 && now && !strcmp(now,names[i]))first_seen[i]=t;
        if(dw4_action2_host_tick(&h,(int64_t)(t+1)*TICK))done=t+1;
        assert(!h.error);
    }
    snprintf(final_motion,sizeof final_motion,"%s",playing(&h)?playing(&h):"");
    dw4_action2_host_close(&h);return done;
}
static void host_level(void)
{
    dw4_arena *a=dw4_session_arena();unsigned live=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    const char *names[]={"actn03","actn04"};int seen[2];
    const int64_t first=1517000000LL,second=50000000LL;   /* Mammothmon's two motions */
    /* Two MOTIONSETs with a Motion wait after each: actn03 plays for its own duration, then actn04, and the program ends after both. */
    dw4_action2_component two[]={motion("actn03",first,"OS"),waitc("Motion",0),motion("actn04",second,"OS"),waitc("Motion",0)};
    int done=run(two,4,names,2,seen);
    int t1=(int)(first/TICK),t2=(int)((first+second)/TICK);
    assert(seen[0]==0);                                        /* the first motion plays from the start */
    assert(seen[1]>=t1 && seen[1]<=t1+2);                      /* the second starts when the first has ended, not at the start */
    assert(done>=t2 && done<=t2+3);                            /* and the program ends after the second one */
    fprintf(stderr,"  two MOTIONSETs: actn03 from tick %d, actn04 from tick %d (first motion %.1f ticks), program done at tick %d (%.3f s)\n",seen[0],seen[1],(double)first/TICK,done,done*(double)TICK/1e9);
    /* One MOTIONSET and its wait is unchanged: it plays at once and the program ends with it. */
    dw4_action2_component one[]={motion("actn03",first,"OS"),waitc("Motion",0)};
    done=run(one,2,names,2,seen);
    assert(seen[0]==0 && seen[1]<0 && done>=t1 && done<=t1+3);
    /* The second wait is what holds the program: without it the program ends once the second MOTIONSET has been started. */
    dw4_action2_component nowait[]={motion("actn03",first,"OS"),waitc("Motion",0),motion("actn04",second,"OS")};
    done=run(nowait,3,names,2,seen);
    assert(seen[0]==0 && seen[1]<0 && done>=t1 && done<=t1+3 && !strcmp(final_motion,"actn04"));   /* ends the tick the wait ends, with actn04 started */
    /* Consecutive MOTIONSETs (the player's RUNN: wait pose, then run) start in the same walk: the last one plays from the first tick. */
    dw4_action2_component back[]={motion("actn03",first,"LP"),motion("actn04",first,"LP")};
    done=run(back,2,names,2,seen);
    assert(seen[1]==0 && seen[0]<0 && done<=1 && !strcmp(final_motion,"actn04"));
    /* A MOTIONSET behind a Frame wait (20 frames) starts when the wait ends. */
    dw4_action2_component late[]={waitc("Frame",0x41a00000),motion("actn03",first,"OS"),waitc("Motion",0)};
    done=run(late,3,names,2,seen);
    assert(seen[0]>=19 && seen[0]<=22 && done>=seen[0]+t1 && done<=seen[0]+t1+3);
    /* A blend leaves two states in the combiner until it has run out, and the Motion wait only proceeds with one state (beAction2WAITCHECK_Update case 2;
     * the old state is removed once elapsed >= the blend time, FUN_001ac140): the wait ends at max(length, blend) after the motion started. Mammothmon's
     * ACTN03 is actn03 (hokan 8 frames) then actn04 (12 frames, a 0.05 s animation): 1.517 s + 0.2 s = 103.02 ticks, retail 103.0-103.1. */
    dw4_action2_component mammos[]={motionb("actn03",first,"OS",8),waitc("Motion",0),motionb("actn04",second,"OS",12),waitc("Motion",0)};
    done=run(mammos,4,names,2,seen);
    int tb=(int)((first+200000000LL)/TICK);   /* 103 */
    assert(seen[0]==0 && seen[1]>=t1 && seen[1]<=t1+2);        /* the long first motion is not delayed by its 8 frame blend */
    assert(done>=tb && done<=tb+2 && tb==103);                 /* the short second one is held for its blend: 103, not 94 */
    fprintf(stderr,"  Mammothmon-shaped ACTN03 (blend 8 / 12 frames): actn04 from tick %d, program done at tick %d (blend model %.2f ticks, animations alone %.2f)\n",seen[1],done,(double)(first+200000000LL)/TICK,(double)(first+second)/TICK);
    /* A blend shorter than the animation changes nothing: the same program with 8 and 2 frame blends ends with the no-blend program. */
    dw4_action2_component shortb[]={motionb("actn03",first,"OS",8),waitc("Motion",0),motionb("actn04",first,"OS",2),waitc("Motion",0)};
    dw4_action2_component noblend[]={motion("actn03",first,"OS"),waitc("Motion",0),motion("actn04",first,"OS"),waitc("Motion",0)};
    int d_short=run(shortb,4,names,2,seen),s_short=seen[1],d_none=run(noblend,4,names,2,seen);
    assert(d_short==d_none && s_short==seen[1]);
    /* A blend that outlasts a lone motion holds its wait too: 50 ms animation, 12 frame blend -> 12 ticks, not 3. */
    dw4_action2_component lone[]={motion("actn03",second,"OS"),waitc("Motion",0),motionb("actn04",second,"OS",12),waitc("Motion",0)};
    done=run(lone,4,names,2,seen);
    assert(seen[1]>=3 && seen[1]<=5 && done>=seen[1]+12 && done<=seen[1]+14);
    /* ... but the first motion of a fresh combiner has nothing to blend from (one state): its wait is the animation's length alone. */
    dw4_action2_component first_only[]={motionb("actn04",second,"OS",12),waitc("Motion",0)};
    done=run(first_only,2,names,2,seen);
    assert(done>=3 && done<=5);
    /* A zero blend time (hokanTime 0: the old state goes at once) leaves the 50 ms animation's wait as it was. */
    dw4_action2_component zero[]={motion("actn03",second,"OS"),waitc("Motion",0),motionb("actn04",second,"OS",0),waitc("Motion",0)};
    done=run(zero,4,names,2,seen);
    assert(done>=6 && done<=10);
    /* A second action replaces the first one cleanly (the arena holds nothing from the earlier programs). */
    assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==live);
}
static void pack_level(const char *roms)
{
    dw4_mount mount;if(dw4_mount_open(&mount,roms)){fprintf(stderr,"  pack level skipped: no assets\n");return;}
    dw4_igfile f={0};assert(!dw4_igfile_open_stage_pack(&f,&mount,"dng102b3",0,0));
    dw4_modelctrl *m=dw4_modelctrl_open(dw4_igfile_data(&f),dw4_igfile_size(&f),"e_mammos");assert(m);
    char *text=NULL;size_t len=0;FILE *o=open_memstream(&text,&len);dw4_modelctrl_census(m,o);fclose(o);
    const char *line=strstr(text,"ACTION ACTN03 components 4 supported 1: [4 actn03 ");assert(line);
    const char *wait1=strstr(line,"] [3 Motion "),*second=wait1?strstr(wait1,"] [4 actn04 "):NULL;assert(wait1 && second);
    fprintf(stderr,"  e_mammos ACTN03: MOTIONSET actn03, WAITCHECK Motion, MOTIONSET actn04, WAITCHECK Motion\n");
    free(text);dw4_modelctrl_close(m);dw4_igfile_close(&f);dw4_mount_close(&mount);
}
int main(int argc,char **argv)
{
    host_level();
    pack_level(argc>1?argv[1]:"../../local/extracted");
    puts("motionset: ok");return 0;
}
