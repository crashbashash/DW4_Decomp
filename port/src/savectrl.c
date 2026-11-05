/* beNDMWSaveCtrl update 407120 (phases 1-3). See dw4/savectrl.h and port/docs/save-keeper.md. */
#include "dw4/savectrl.h"
#include <stddef.h>
static void next(dw4_savectrl *c){c->sub++;c->subsub=0;}
static void phase_to(dw4_savectrl *c,int phase){c->phase=phase;c->sub=0;c->subsub=0;}
const char *dw4_savectrl_exit_stage(int done_players,int *generate_pos)
{
    if(done_players<=0){if(generate_pos)*generate_pos=-1;return "stagis10";}
    if(generate_pos)*generate_pos=2;return "stagML12";
}
void dw4_savectrl_generate(dw4_savectrl *c){if(c->built)return;*c=(dw4_savectrl){.built=1,.phase=1};}
int dw4_loadctrl_generate(dw4_savectrl *c,int title){if(title)return -1;if(c->built)return 0;*c=(dw4_savectrl){.built=1,.load=1,.phase=1};return 0;}
const char *dw4_loadctrl_exit_stage(int *generate_pos){if(generate_pos)*generate_pos=4;return "stagML11";}
/* Card helper 3f1270: SAVEUTILITY GENERATE(4); present when a receiver answered. */
static void card_start(dw4_savectrl *c,const dw4_savectrl_host *h){c->card_present=h->card_generate(h->user)>0;}
/* 3f12f0: absent card is ready at once; a present one when ISRDY answers true. */
static int card_wait(dw4_savectrl *c,const dw4_savectrl_host *h)
{
    if(c->card_present){if(h->card_ready(h->user)==1){c->card_done=1;return 1;}return 0;}
    c->card_done=1;return 1;
}
static int done_players(const dw4_savectrl_host *h)
{int n=0;for(int i=0;i<DW4_SAVECTRL_PLAYERS;i++)if(h->player_done(h->user,i)==1)n++;return n;}
void dw4_savectrl_update(dw4_savectrl *c,const dw4_savectrl_host *h)
{
    if(!c->built){h->self_generate(h->user);return;}
    switch(c->phase) {
    case 1: /* scan the card */
        if(c->sub==0){card_start(c,h);next(c);c->subsub=0;}
        else if(c->sub==1 && card_wait(c,h))phase_to(c,2);
        break;
    case 2:
        switch(c->sub) {
        case 0:
            h->model_send(h->user,"j_chrselback","GENERATE");h->model_send(h->user,"j_chrselback","SQ_OPEN");next(c);break;
        case 1: /* retail advances once ISSEQNAME SQ_OPEN answers false */
            if(!h->model_is_sequence(h->user,"j_chrselback","SQ_OPEN"))next(c);break;
        case 2:h->intf_generate(h->user);next(c);break;
        case 3:
            switch(h->intf_state(h->user)){case 0:h->intf_scan(h->user);break;case 3:next(c);break;default:break;}
            break;
        case 4:
            switch(c->subsub) {
            case 0:h->players_close(h->user);c->subsub++;break;
            case 1:{int all=1;for(int i=0;i<DW4_SAVECTRL_PLAYERS;i++)if(h->player_ready(h->user,i)!=1){all=0;break;}
                    if(all==1)c->subsub++;break;}
            case 2:
                h->model_send(h->user,"i_fadewn01","GENERATE");h->model_send(h->user,"i_fadewn01","SQ_BLOUT30");
                h->model_send(h->user,"j_chrselback","SQ_CLOSE");c->subsub++;break;
            case 3:if(!h->model_is_running(h->user,"j_chrselback"))c->subsub++;break;
            case 4:{int done[DW4_SAVECTRL_PLAYERS],n=0;
                    h->intf_select_data(h->user);
                    for(int i=0;i<DW4_SAVECTRL_PLAYERS;i++){done[i]=h->player_done(h->user,i)==1;n+=done[i];}
                    h->publish_players(h->user,n,done);phase_to(c,3);break;}
            }
            break;
        }
        break;
    case 3:
        if(c->sub==0){if(c->card_present)h->card_remove(h->user);next(c);}
        else if(c->sub==1) {
            /* 3f13d0: an absent card is released at once; a present one when ISRDY turns false. */
            int released=c->card_present?!h->card_ready(h->user):1;
            if(released) {
                int pos;const char *stage=c->load?dw4_loadctrl_exit_stage(&pos):dw4_savectrl_exit_stage(done_players(h),&pos);
                h->go(h->user,stage,pos);phase_to(c,4);
            }
        }
        break;
    default:break; /* the retail switch has no case 4: the controller idles after the exit request */
    }
}
