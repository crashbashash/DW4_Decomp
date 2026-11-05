/* Sequencing test for the recovered beNDMWSaveIntf (4081a0 + helpers): a scripted host stands in for MODELCTRL, TEXTCTL,
 * the pad and SAVEUTILITY. The test drives player 0 through the data-select/save path and asserts the retail order of
 * model sequences, message numbers, card requests and states. This is a sequencing test against the recovered bodies,
 * not an instruction-level retail oracle (the controllers need the messenger/property-bag objects). Headless. */
#include "dw4/saveintf.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEV 4096
struct sim {
    char ev[MAXEV][96];int nev;
    /* models: sequence + remaining updates until a sequence/run finishes */
    struct {char model[32];int ram;char seq[32];int left;int used,gen;} m[128];
    uint32_t pad_edges;int cross_every;int frame;
    int card_present,card_unformatted;dw4_si_card_slot slots[DW4_SI_CARD_SLOTS];
    int req_kind,req_slot,req_area,req_left;int request_result[8];
    int64_t timer_end;int writes,write_slot,write_area;
    int in_use,started,removed[4];
    dw4_si_summary summary;int last_choice_cross;
    int seq_delay,start_now;
};
static void ev(struct sim *s,const char *fmt,...)
{
    va_list a;
    if(s->nev>=MAXEV)return;
    va_start(a,fmt);vsnprintf(s->ev[s->nev++],sizeof s->ev[0],fmt,a);va_end(a);
}
#define EV(s,...) ev(s,__VA_ARGS__)
#include <stdarg.h>
static int slot_of(struct sim *s,const char *model,int ram)
{
    for(int i=0;i<128;i++)if(s->m[i].used&&s->m[i].ram==ram&&!strcmp(s->m[i].model,model))return i;
    for(int i=0;i<128;i++)if(!s->m[i].used){s->m[i].used=1;s->m[i].ram=ram;snprintf(s->m[i].model,sizeof s->m[i].model,"%s",model);return i;}
    return -1;
}
static int h_generate(void *u,const char *model,int ram,const float pos[3]){struct sim *s=u;(void)pos;s->m[slot_of(s,model,ram)].gen=1;EV(s,"GEN %s %d",model,ram);return 0;}
static int h_sequence(void *u,const char *model,int ram,const char *seq)
{
    struct sim *s=u;int i=slot_of(s,model,ram);snprintf(s->m[i].seq,sizeof s->m[i].seq,"%s",seq);s->m[i].left=s->seq_delay;EV(s,"SEQ %s %d %s",model,ram,seq);return 0;
}
static int h_is_seq(void *u,const char *model,int ram,const char *seq)
{
    struct sim *s=u;int i=slot_of(s,model,ram);return s->m[i].left>0&&!strcmp(s->m[i].seq,seq);
}
/* ISRUN (modelctrl.c: the slot is active): a generated model runs until one of the sequences that end it has finished. */
static int ends_model(const char *seq)
{
    return !strcmp(seq,"SQ_CLOSE")||!strcmp(seq,"SQ_CANCEL")||!strcmp(seq,"SQ_NOCLOSE")||!strncmp(seq,"SQ_LINEON0",10);
}
static int h_is_run(void *u,const char *model,int ram)
{
    struct sim *s=u;int i=slot_of(s,model,ram);
    return s->m[i].gen&&!(ends_model(s->m[i].seq)&&s->m[i].left==0);
}
static int h_text_clear(void *u,const char *g,const char *f){(void)u;(void)g;(void)f;return 0;}
static int h_text_set(void *u,const char *g,const char *f,int al,int col,const char *a,const uint16_t *w)
{
    struct sim *s=u;(void)al;(void)col;(void)w;EV(s,"TXT %s %s %s",g,f,a?a:"(name)");return 0;
}
static int h_text_script(void *u,const char *chunk,int call){struct sim *s=u;EV(s,"MSG %s %d",chunk,call);return 0;}
static int h_pad(void *u,int player,uint32_t *h,uint32_t *e,uint32_t *r)
{
    struct sim *s=u;*h=0;*r=0;*e=0;if(player==0&&s->cross_every&&s->frame%s->cross_every==0)*e=s->start_now?0x8:s->pad_edges;return 0;
}
static int h_in_use(void *u,int p){struct sim *s=u;return p==0&&s->in_use;}
static int h_c2b(void *u,int p){struct sim *s=u;(void)p;EV(s,"CURRENT2BASE");return 0;}
static int h_summary(void *u,int p,dw4_si_summary *out){struct sim *s=u;(void)p;*out=s->summary;return 0;}
static int h_start(void *u,int p,const char *m){struct sim *s=u;(void)p;(void)m;s->started++;s->in_use=1;return 0;}
static int h_remove(void *u,int p){struct sim *s=u;s->removed[p]++;return 0;}
static int h_species(void *u,int row,char *out,size_t cap){(void)u;snprintf(out,cap,"Species%d",row);return 0;}
static int h_card_request(void *u,int kind,int slot,int player,int area)
{
    struct sim *s=u;(void)player;s->req_kind=kind;s->req_slot=slot;s->req_area=area;s->req_left=2;EV(s,"CARD %d %d %d",kind,slot,area);
    if(kind==5){s->writes++;s->write_slot=slot;s->write_area=area;}
    return 0;
}
static int h_card_done(void *u,int *result)
{
    struct sim *s=u;if(s->req_left>0&&--s->req_left>0)return 0;if(s->req_left<0)return 0;
    s->req_left=-1;*result=s->request_result[s->req_kind];return 1;
}
static int h_card_state(void *u,int *present,int *unf,dw4_si_card_slot slots[DW4_SI_CARD_SLOTS],int *n)
{
    struct sim *s=u;*present=s->card_present;*unf=s->card_unformatted;memcpy(slots,s->slots,sizeof s->slots);*n=2;return 0;
}
static int h_card_read(void *u,int slot,dw4_si_summary areas[DW4_SI_SLOTS]){struct sim *s=u;(void)slot;memset(areas,0,sizeof *areas*DW4_SI_SLOTS);areas[0]=s->summary;return 0;}
static int h_timer_start(void *u,const char *name,int64_t ns){struct sim *s=u;(void)name;(void)ns;s->timer_end=s->frame+10;return 0;}
static int h_timer_done(void *u,const char *name){struct sim *s=u;(void)name;return s->frame>=s->timer_end;}

static int count(struct sim *s,const char *prefix)
{
    int n=0;for(int i=0;i<s->nev;i++)if(!strncmp(s->ev[i],prefix,strlen(prefix)))n++;return n;
}
static int first(struct sim *s,const char *text,int from)
{
    for(int i=from;i<s->nev;i++)if(!strcmp(s->ev[i],text))return i;
    return -1;
}
static void tick_models(struct sim *s){for(int i=0;i<128;i++)if(s->m[i].used&&s->m[i].left>0)s->m[i].left--;}
static void setup(struct sim *s,dw4_saveintf_host *h)
{
    memset(s,0,sizeof *s);s->seq_delay=2;s->card_present=1;s->card_unformatted=0;
    s->slots[0].ok=1;s->slots[1].ok=0;s->in_use=1;
    for(int k=0;k<8;k++)s->request_result[k]=2;
    s->summary=(dw4_si_summary){.used=1,.unique=77,.level=12,.hp=100,.mhp=120,.mp=30,.mmp=40};
    snprintf(s->summary.model,sizeof s->summary.model,"p_dorumon");s->summary.name[0]='D';s->summary.name[1]='o';
    s->cross_every=15;s->pad_edges=0x4000;
    *h=(dw4_saveintf_host){.user=s,.model_generate=h_generate,.model_sequence=h_sequence,.model_is_sequence=h_is_seq,.model_is_running=h_is_run,
        .text_clear=h_text_clear,.text_set=h_text_set,.text_script=h_text_script,.pad=h_pad,.player_in_use=h_in_use,
        .player_current_to_base=h_c2b,.player_summary=h_summary,.player_start_game=h_start,.player_remove=h_remove,.species_name=h_species,
        .card_request=h_card_request,.card_done=h_card_done,.card_state=h_card_state,.card_read=h_card_read,
        .timer_start=h_timer_start,.timer_done=h_timer_done};
}
/* scenario: 0 save, 1 cancel at the first question (Circle on the card chooser), 2 the card reports an error on FILEFIND,
 * 3 slot 0 not usable (the chooser refuses the row) */
static void run_scenario(int scenario)
{
    struct sim s;dw4_saveintf_host h;setup(&s,&h);
    if(scenario==2)s.request_result[1]=8;
    int joined[4]={1,0,0,0};dw4_saveintf *si=dw4_saveintf_open(&h,0,joined);assert(si && !dw4_saveintf_generate(si));
    int last_state=-1,done=0,cancel_sent=0;
    for(s.frame=0;s.frame<8000;s.frame++){
        tick_models(&s);
        if(dw4_saveintf_update(si)){fprintf(stderr,"update failed at frame %d: %s\n",s.frame,dw4_saveintf_error(si));assert(0);}
        dw4_saveintf_trace t;dw4_saveintf_diagnostics(si,0,&t);
        if(t.control!=last_state){EV(&s,"CTRL %d",t.control);last_state=t.control;}
        s.start_now=t.control==8&&t.control_sub==3;   /* the retail confirmation waits for START (pad bit 0x8) */
        if(scenario==1&&t.control==4&&t.control_sub==1&&t.control_subsub==0&&!cancel_sent){s.pad_edges=0x2000;cancel_sent=1;}
        if(dw4_saveintf_scene_state(si)==3){done=1;break;}
        if(scenario==1&&count(&s,"CTRL 2")>=2)break;   /* Circle returned to the first question */
    }
    if(scenario==1){
        assert(s.writes==0 && count(&s,"CARD 5")==0 && count(&s,"CTRL 2")>=2);
        printf("saveintf: Circle on the card chooser returns to the first question and writes nothing\n");
        dw4_saveintf_close(si);return;
    }
    if(scenario==2){
        /* FILEFIND answered with result 8: the card-status notice 0x1013 (call 1021?) shows and nothing is written */
        assert(s.writes==0);assert(count(&s,"CARD 1")>=1);
        assert(first(&s,"MSG txt_Tar.lua 1112",0)>=0);   /* 0x1013: txt_Tar call 1112 */
        printf("saveintf: a failing FILEFIND (result 8) shows notice 0x1013 (call 1112) and writes nothing\n");
        dw4_saveintf_close(si);return;
    }
    if(!done){
        dw4_saveintf_trace t;dw4_saveintf_diagnostics(si,0,&t);
        fprintf(stderr,"did not finish: item %d/%d/%d/%d ctrl %d/%d/%d frame %d\n",t.state,t.sub,t.subsub,t.subsubsub,t.control,t.control_sub,t.control_subsub,s.frame);
        for(int i=s.nev>60?s.nev-60:0;i<s.nev;i++)fprintf(stderr,"  %s\n",s.ev[i]);
    }
    assert(done);
    /* retail order of the opening: the base window opens before the message window, whose first message is 0x502. */
    int base=first(&s,"GEN j_chrselbase 0",0),mes=first(&s,"GEN j_chrselmesswin 0",0),ask=first(&s,"MSG txt_mem.lua 201",0);
    assert(base>=0 && mes>base && ask>mes);                     /* 0x502 -> call 201 */
    assert(count(&s,"CURRENT2BASE")==1);                       /* an in-use player is copied to its base once */
    assert(count(&s,"CARD 3 0")>=1 && count(&s,"CARD 1 0")>=1); /* USE_CHECK then FILEFIND on the chosen slot */
    assert(s.writes==1 && s.write_slot==0 && s.write_area==0);  /* exactly one WRITE_MEDIA, slot 0 area A */
    assert(first(&s,"CARD 5 0 0",0)>first(&s,"CARD 4 0 0",0));  /* the file is read before it is written */
    assert(s.removed[0]==0);
    if(getenv("SAVEINTF_DUMP"))for(int i=0;i<s.nev;i++)printf("%4d %s\n",i,s.ev[i]);
    printf("saveintf: single-player save path (%d events) ends with the scene finished after one WRITE_MEDIA to slot 0 area A\n",s.nev);
    dw4_saveintf_close(si);
}
int main(void)
{
    run_scenario(0);run_scenario(1);run_scenario(2);
    puts("saveintf: sequencing test passes (not an instruction-level retail oracle)");
    return 0;
}
