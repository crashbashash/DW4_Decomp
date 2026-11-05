#include "dw4/engine.h"
#include "dw4/window.h"
#include "dw4/frontui.h"
#include "dw4/simulation.h"
#include "dw4/frontend.h"
#include "dw4/filelist.h"
#include "dw4/lobby.h"
#include <assert.h>
#include <stdio.h>
static unsigned polls,draws,presents,inject,pending;
#ifdef DW4_TEST_START_FAILURE
static unsigned first_calls,world_ticks;
int __wrap_dw4_filelist_first(dw4_filelist *f){(void)f;first_calls++;return -1;}
void __real_dw4_lobby_tick(dw4_lobby *,int);
void __wrap_dw4_lobby_tick(dw4_lobby *l,int edge){world_ticks++;__real_dw4_lobby_tick(l,edge);}
#endif
/* the windowed title opening (about 270 frames) ignores input: the title part of the pad script starts after it */
static const char *script="285:start,350:start,410:cross,580:cross,625:cross,675:cross,690:right,700:right,712:cross,728:start,780:cross,810:cross,860:start";
int __wrap_dw4_window_pump(dw4_window *w,dw4_input_state *in) {
    (void)w;pending=0;dw4_input_script(in,script,(int)polls++);
#ifdef DW4_TEST_START_FAILURE
    static int retried,back,settled;
    if(first_calls==1 && !retried){in->cross=1;retried=1;}
    if(first_calls==2 && !back){in->circle=1;back=1;}
    if(back && ++settled>30)in->quit=1;
#endif
    return 1;
}
/* The engine pumps through dw4_window_pump_mates (the co-op pads of players 2-4); the scripted pad is the first player's. */
int __wrap_dw4_window_pump_mates(dw4_window *w,dw4_input_state *in,dw4_input_state mates[3]) {(void)mates;return __wrap_dw4_window_pump(w,in);}
uint64_t __wrap_dw4_simulation_due(dw4_simulation *s,uint64_t host) {
    (void)host;if(!s->due)s->due=1;if(inject==1){s->due+=10;inject=2;}return s->due;
}
void __real_dw4_frontui_loading_sample(dw4_frontui *,uint64_t);
void __wrap_dw4_frontui_loading_sample(dw4_frontui *ui,uint64_t ns) {
    pending=1;if(++draws==20)inject=1;__real_dw4_frontui_loading_sample(ui,ns);
}
int __real_dw4_window_present(dw4_window *,const dw4_fb *);
int __wrap_dw4_window_present(dw4_window *w,const dw4_fb *fb) {
    if(pending)presents++;
    return __real_dw4_window_present(w,fb);
}
int __real_dw4_frontend_boot(const char *,dw4_title_menu *,char *,size_t,int,int,struct dw4_window *,struct dw4_vk *,const char *,int);
int __wrap_dw4_frontend_boot(const char *r,dw4_title_menu *m,char *s,size_t n,int p,int f,struct dw4_window *w,struct dw4_vk *v,const char *input,int skip) {
    (void)p;(void)w;(void)v;(void)input;(void)skip;
    return __real_dw4_frontend_boot(r,m,s,n,0,f,NULL,NULL,NULL,1);
}
/* Keep the actual windowed/catch-up engine path: input_script remains NULL.
 * Supply deterministic pad/clock leaves and count real SDL presentations.
 * Startup cards/FMV are skipped; the original database/title preparation runs. */
int main(int argc,char **argv) {
    if(!dw4_window_built()){puts("live loading: SDL unavailable, skipped");return 0;}
    assert(argc==2);dw4_engine_opts o={.roms=argv[1],.frames=1010,.w=160,.h=112,.window=1,.software=1,.fps=0,.fps_lock=0};
#ifdef DW4_TEST_START_FAILURE
    o.frames=4000;
#endif
    char stage[64];int result=dw4_engine_boot(&o,NULL,stage,sizeof stage);
    fprintf(stderr,"LIVE LOAD: result %d, %u loading draws, %u presentations, injected %u\n",result,draws,presents,inject);
    assert(result>=0 && draws>20 && inject==2 && presents==draws);
#ifdef DW4_TEST_START_FAILURE
    assert(first_calls==2 && !world_ticks);
    puts("live loading: two failed original FIRST attempts retain Retry/Back and never tick a partial world");
#else
    puts("live loading: catch-up retains every loading presentation");
#endif
    return 0;
}
