/* beNDMWSaveCtrl (407120) sequencing against a scripted host: every messenger call of the retail body, in order.
 * Headless; no game data. */
#include "dw4/savectrl.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct world {
    char log[4096];
    int card_answers,card_ready,ready_after;      /* SAVEUTILITY */
    int open_polls_left,running_polls_left;       /* j_chrselback ISSEQNAME / ISRUN */
    int intf_state;
    int player_ready[4],player_done[4];
    int closed,published_count,published[4],published_calls;
    char stage[16];int stage_pos,stage_calls,generate_calls;
};
static void note(struct world *w,const char *s){strncat(w->log,s,sizeof w->log-strlen(w->log)-2);strncat(w->log,";",2);}
static int card_generate(void *u){struct world *w=u;note(w,"card.gen");return w->card_answers;}
static int card_ready(void *u){struct world *w=u;note(w,"card.rdy");if(w->ready_after>0){w->ready_after--;return 0;}return w->card_ready;}
static void card_remove(void *u){note(u,"card.rm");((struct world *)u)->card_ready=0;}
static void model_send(void *u,const char *m,const char *k){char b[64];snprintf(b,sizeof b,"%s.%s",m,k);note(u,b);}
static int model_is_sequence(void *u,const char *m,const char *s){struct world *w=u;(void)m;(void)s;note(w,"seq?");return w->open_polls_left-->0;}
static int model_is_running(void *u,const char *m){struct world *w=u;(void)m;note(w,"run?");return w->running_polls_left-->0;}
static void intf_generate(void *u){note(u,"intf.gen");}
static int intf_state(void *u){return ((struct world *)u)->intf_state;}
static void intf_scan(void *u){struct world *w=u;note(w,"scan");w->intf_state=3;}
static void players_close(void *u){struct world *w=u;note(w,"close");w->closed=1;}
static int player_ready(void *u,int i){struct world *w=u;return w->closed?w->player_ready[i]:0;}
static int player_done(void *u,int i){return ((struct world *)u)->player_done[i];}
static void intf_select(void *u){note(u,"select");}
static void publish(void *u,int n,const int d[4]){struct world *w=u;note(w,"publish");w->published_count=n;memcpy(w->published,d,sizeof w->published);w->published_calls++;}
static void go(void *u,const char *s,int p){struct world *w=u;snprintf(w->stage,sizeof w->stage,"%s",s);w->stage_pos=p;w->stage_calls++;note(w,"go");}
static void self_generate(void *u){struct world *w=u;w->generate_calls++;note(w,"self.gen");}
static dw4_savectrl_host host(struct world *w)
{
    return (dw4_savectrl_host){w,card_generate,card_ready,card_remove,model_send,model_is_sequence,model_is_running,intf_generate,
        intf_state,intf_scan,players_close,player_ready,player_done,intf_select,publish,go,self_generate};
}
static void run(dw4_savectrl *c,const dw4_savectrl_host *h,int n){for(int i=0;i<n;i++)dw4_savectrl_update(c,h);}

int main(void)
{
    /* The exit rule. */
    int pos=0;
    assert(!strcmp(dw4_savectrl_exit_stage(0,&pos),"stagis10") && pos==-1);
    assert(!strcmp(dw4_savectrl_exit_stage(-1,&pos),"stagis10") && pos==-1);
    assert(!strcmp(dw4_savectrl_exit_stage(1,&pos),"stagML12") && pos==2);
    assert(!strcmp(dw4_savectrl_exit_stage(4,&pos),"stagML12") && pos==2);

    /* Before SAVECTRL GENERATE the update only asks for it; a second GENERATE changes nothing. */
    {
        struct world w={0};dw4_savectrl_host h=host(&w);dw4_savectrl c={0};
        run(&c,&h,3);assert(w.generate_calls==3 && !strcmp(w.log,"self.gen;self.gen;self.gen;") && !c.built);
        dw4_savectrl_generate(&c);assert(c.built && c.phase==1 && c.sub==0 && c.subsub==0);
        c.phase=3;dw4_savectrl_generate(&c);assert(c.phase==3); /* idempotent */
    }

    /* Full path with a card, two players finishing, and every wait state exercised. */
    {
        struct world w={.card_answers=1,.card_ready=1,.ready_after=2,.open_polls_left=2,.running_polls_left=3,.intf_state=0,
            .player_ready={1,1,1,1},.player_done={1,0,1,0}};
        dw4_savectrl_host h=host(&w);dw4_savectrl c={0};dw4_savectrl_generate(&c);
        /* phase 1: GENERATE, then ISRDY polled until ready (2 false answers) */
        dw4_savectrl_update(&c,&h);assert(!strcmp(w.log,"card.gen;") && c.card_present && c.phase==1 && c.sub==1);
        run(&c,&h,2);assert(c.phase==1);
        dw4_savectrl_update(&c,&h);assert(c.phase==2 && c.sub==0 && c.card_done);
        /* phase 2: open the base window and wait until the SQ_OPEN query stops answering true */
        w.log[0]=0;dw4_savectrl_update(&c,&h);assert(!strcmp(w.log,"j_chrselback.GENERATE;j_chrselback.SQ_OPEN;") && c.sub==1);
        w.log[0]=0;run(&c,&h,2);assert(c.sub==1 && !strcmp(w.log,"seq?;seq?;"));
        dw4_savectrl_update(&c,&h);assert(c.sub==2);
        w.log[0]=0;dw4_savectrl_update(&c,&h);assert(!strcmp(w.log,"intf.gen;") && c.sub==3);
        /* COMMONINTF state 0 scans once, which finishes it (3); state 2 only waits */
        w.log[0]=0;w.intf_state=2;run(&c,&h,2);assert(!w.log[0] && c.sub==3);
        w.intf_state=0;dw4_savectrl_update(&c,&h);assert(!strcmp(w.log,"scan;") && c.sub==3);
        dw4_savectrl_update(&c,&h);assert(c.sub==4 && c.subsub==0);
        /* close all four players, wait for all of them, fade, wait for the base window to stop running */
        w.log[0]=0;dw4_savectrl_update(&c,&h);assert(!strcmp(w.log,"close;") && c.subsub==1);
        w.player_ready[2]=0;run(&c,&h,2);assert(c.subsub==1);w.player_ready[2]=1;
        w.log[0]=0;dw4_savectrl_update(&c,&h);assert(c.subsub==2);
        dw4_savectrl_update(&c,&h);
        assert(!strcmp(w.log,"i_fadewn01.GENERATE;i_fadewn01.SQ_BLOUT30;j_chrselback.SQ_CLOSE;") && c.subsub==3);
        w.log[0]=0;run(&c,&h,3);assert(c.subsub==3 && !strcmp(w.log,"run?;run?;run?;"));
        dw4_savectrl_update(&c,&h);assert(c.subsub==4);
        /* publish: SETSELECT_DATA, then the finished players are counted */
        w.log[0]=0;dw4_savectrl_update(&c,&h);
        assert(!strcmp(w.log,"select;publish;") && w.published_count==2 && w.published[0]==1 && w.published[1]==0 &&
               w.published[2]==1 && w.published[3]==0 && c.phase==3 && c.sub==0);
        /* phase 3: REMOVE the card, wait until ISRDY turns false, then leave for Central at generate position 2 */
        w.log[0]=0;dw4_savectrl_update(&c,&h);assert(!strcmp(w.log,"card.rm;") && c.sub==1);
        w.log[0]=0;w.card_ready=1;w.ready_after=0; /* ISRDY still true: the card is not released yet */
        dw4_savectrl_update(&c,&h);assert(!w.stage_calls && c.phase==3);
        w.card_ready=0;dw4_savectrl_update(&c,&h);
        assert(w.stage_calls==1 && !strcmp(w.stage,"stagML12") && w.stage_pos==2 && c.phase==4);
        /* the retail switch has no case 4: nothing more is sent */
        w.log[0]=0;run(&c,&h,5);assert(!w.log[0] && w.stage_calls==1 && w.published_calls==1);
    }

    /* No card present: ISRDY and REMOVE are never sent; nobody finished -> the title. */
    {
        struct world w={.card_answers=0,.intf_state=3,.player_ready={1,1,1,1}};
        dw4_savectrl_host h=host(&w);dw4_savectrl c={0};dw4_savectrl_generate(&c);
        run(&c,&h,2);assert(c.phase==2 && !c.card_present && c.card_done && !strstr(w.log,"card.rdy"));
        run(&c,&h,30);
        assert(!strstr(w.log,"card.rm") && !strstr(w.log,"card.rdy") && w.published_count==0 && w.stage_calls==1);
        assert(!strcmp(w.stage,"stagis10") && w.stage_pos==-1 && c.phase==4);
    }

    /* A card with every player finished still exits to Central, and a card that never answers ISRDY holds phase 1. */
    {
        struct world w={.card_answers=1,.card_ready=0,.intf_state=3,.player_ready={1,1,1,1},.player_done={1,1,1,1}};
        dw4_savectrl_host h=host(&w);dw4_savectrl c={0};dw4_savectrl_generate(&c);
        run(&c,&h,50);assert(c.phase==1 && c.sub==1 && !w.stage_calls);
        w.card_ready=1;run(&c,&h,40); /* the scripted card releases itself on REMOVE */
        assert(w.published_count==4 && w.stage_calls==1 && !strcmp(w.stage,"stagML12") && w.stage_pos==2 && c.phase==4);
    }
    printf("savectrl: card scan, scene open, interface hand-off, fade, publish, card release and both exits follow the retail order\n");
    return 0;
}
