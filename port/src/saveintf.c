#include "dw4/saveintf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saveintf_tables.inc"

/* ---- object model -------------------------------------------------------------------------------------------
 * Retail keeps these as property bags found by name in each SaveIntf's collection (CTRL, COMMDLCTRL, MESWIN, SELSLOT,
 * COMMONINTF, DEGISTATECTRL, DATASELINTF). They are plain data; every behaviour is in 4081a0 and the helpers.
 * Field comments give the retail offsets so the draft can be followed line by line. */
typedef struct {int ram;const char *model,*sequence;} si_track;
typedef struct {si_track v[16];int n;} si_tracks;
typedef struct {si_tracks a,b;float home[3];} si_comdl;       /* COMMDLCTRL: +0x14 list A (ISSEQNAME), +0x18 list B (ISRUN), +0x1C vec3 */

typedef struct {                                                /* MESWIN */
    uint8_t active,autoclose,done,notice_only,clear_req,dirty,busy,shown;  /* +0x1C..+0x23 */
    int32_t mode,state,player,choice,message,notice;            /* +0x24 +0x28 +0x2C +0x30 +0x34 +0x38 */
    int32_t notice_step;                                        /* +0x3C */
} si_meswin;

typedef struct {                                                /* a saved-character display (COMMONINTF +0x24 / entries) */
    dw4_si_summary s;
} si_display;
typedef struct {int slot;si_display area[DW4_SI_SLOTS];int players[DW4_SI_PLAYERS],nplayers;int allocated;} si_entry;  /* COMMONINTF +0x20 element */

typedef struct {                                                /* COMMONINTF +0x34 card object */
    uint8_t present,flag_d,busy,unformatted;                    /* +0xC +0xD +0xE +0xF */
    int32_t formatted_now;                                      /* +0x10 */
    int32_t slot,kind,result,done,step;                         /* +0x14 +0x1C +0x20 +0x24 +0x30 */
    dw4_si_card_slot slots[DW4_SI_CARD_SLOTS];int nslots;       /* +0x2C */
    int player;
} si_card;

typedef struct {                                                /* COMMONINTF item (one per player) */
    int32_t timer;                                              /* +8 */
    uint8_t in_use,chosen,closed,pad_enabled,cancel;            /* +0xC +0xD +0xE +0xF +0x10 */
    int32_t result;                                             /* +0x14 */
    int entry;                                                  /* +0x20 index into entries or -1 */
    int32_t state,sub,subsub,subsubsub;                         /* +0x24 +0x28 +0x2C +0x30 */
    int32_t picked_slot;
} si_item;

typedef struct {int32_t state,sub,subsub,subsubsub;uint8_t flag17;                 /* CTRL: +0x24 +0x28 +0x2C +0x30, +0x17 */
    uint8_t f12,f13,f14,f15,f1c,f1d;int32_t f18;} si_ctrl;                          /* LoadIntf2 CTRL: +0x12 joined, +0x13, +0x14, +0x15, +0x1C new data, +0x1D host-joiner, +0x18 cursor */

typedef struct {                                                /* SELSLOT: one slot panel (3d9de0 family) */
    int player,side;                                            /* +0x18 +0x1C */
    int source,index;                                           /* +0x28 +0x2C */
    uint8_t used,done;                                          /* +0x30 +0x20 */
    int32_t mark,action,step,c3c,c40;                           /* +0x24 +0x34 +0x38 +0x3C +0x40 */
} si_panel;

typedef struct {                                                /* DATASELINTF: the area selector (3dafb0 family) */
    int player,cursor,mode;                                     /* +0x3C +0x14 +0x38 */
    int32_t lvl[4];                                             /* +0x4C +0x50 +0x54 +0x58 */
    uint8_t f30,f31,f32;int32_t f34,conflict,f48;uint8_t cancel; /* +0x30 +0x31 +0x32 +0x34 +0x40 +0x48 +0x49 */
} si_select;

typedef struct {                                                /* DIFFSELECT (3ddb10 init, 3ddb80 update) */
    int cursor,max,player,result,kind;                          /* +0x10 +0x14 +0x18 +0x1C +0x20 */
    uint8_t end,cancel;int32_t lvl,sub;                         /* +0x24 +0x25 +0x3C +0x40 */
} si_diff;

typedef struct {                                                /* DEGISTATECTRL: the memory-card slot chooser */
    int player,rows,row,variant,chosen_slot;                    /* +0x30 +0x2C +0x3C +0x44 +0x40 */
    int32_t lvl[4];                                             /* +0x4C +0x50 +0x54 +0x58 */
    uint8_t done,f35,cancel,f37,closed,info;                    /* +0x34 +0x35 +0x36 +0x37 +0x38 +0x48 */
} si_slots;

typedef struct {int32_t species;} si_makechr;                   /* MAKECHR: +0x30 _chaSelDegi (0 agumon 1 vmon 2 girumon 3 dorumon) */

typedef struct {                                                /* NAMESEL (beNDMWLoadIntf2NameSel: 3de260 init, 3def80 update, 3def70 answer) */
    int player;                                                 /* +0x20 _ramNo */
    int32_t sel,lang,tate_max,tate_min,tate,yoko,cur,max,pos;   /* +0x24 _selDataNo +0x28 _langID +0x2C +0x30 +0x34 _tatePoint +0x38 _yokoPoint
                                                                 * +0x3C _yokoCurPos +0x44 _nameMojiMax +0x48 _nameCurPos */
    uint8_t end,make_name,question,answer,name_ok,side;         /* +0x4C _isEnd .. +0x51 _isSideCur */
    int32_t st0,st1;                                            /* +0x54 +0x58 */
    int32_t saved[9][3];                                        /* +0x68: per cell the {_tatePoint,_yokoPoint,_yokoCurPos} it was typed with */
    int32_t cell[9];                                            /* +0xC8: 0 empty, 1 the live preview (CANCELCOLOR), 2 typed (DEFAULTCOLOR) */
    uint16_t name[10];                                          /* +0xEC: UCS-2 codes */
} si_namesel;

struct dw4_saveintf {
    dw4_saveintf_host h;int mode,generated,load;
    char error[256];
    /* COMMONINTF (shared) */
    si_item item[DW4_SI_PLAYERS];si_display display[DW4_SI_PLAYERS];si_entry entry[DW4_SI_PLAYERS];int nentries;
    si_card card;int scene_state,active_selector;   /* COMMONINTF +0x30, +0x44 */
    /* per player */
    si_ctrl ctrl[DW4_SI_PLAYERS];si_comdl comdl[DW4_SI_PLAYERS];si_meswin mes[DW4_SI_PLAYERS];
    si_panel panel[DW4_SI_PLAYERS][2];si_select select[DW4_SI_PLAYERS];si_slots slots[DW4_SI_PLAYERS];
    si_diff diff[DW4_SI_PLAYERS];si_makechr makechr[DW4_SI_PLAYERS];si_namesel namesel[DW4_SI_PLAYERS];
    int title,title_state,title_area,title_card_slot,title_difficulty;   /* the title's Game Start use of LoadIntf2 (see dw4_loadintf_open_title) */
    int joined[DW4_SI_PLAYERS];
    int64_t clock_ns;
};

#define FAIL(s,msg) do{snprintf((s)->error,sizeof (s)->error,"%s",msg);return -1;}while(0)
static int ok(dw4_saveintf *s,int rc,const char *what){if(rc&&!s->error[0])snprintf(s->error,sizeof s->error,"%s failed%s%s",what,s->h.error?": ":"",s->h.error?s->h.error:"");return rc;}
static int lvl_get(const int32_t c[4],int level){return level>=1&&level<=3?c[level]:c[0];}
static void lvl_set(int32_t c[4],int level,int v)
{
    if(level<1||level>3){c[0]=v;c[1]=c[2]=c[3]=0;}
    else{c[level]=v;for(int i=level+1;i<4;i++)c[i]=0;}
}
static const char *font(int player,int index,char out[16]){snprintf(out,16,"font%d%02d",player,index);return out;}

/* ---- COMMDLCTRL: model-sequence tracker (3e3e00 3e4030 3e42a0 3e4210 3e4480 3e44f0 3e4280 3e44d0) ---- */
static int track_add(si_tracks *t,int ram,const char *model,const char *sequence)
{
    if(t->n>=(int)(sizeof t->v/sizeof *t->v))return -1;
    t->v[t->n++]=(si_track){ram,model,sequence};return 0;
}
static int cd_generate(dw4_saveintf *s,si_comdl *c,int ram,const char *model,const char *seq,const float pos[3],int track)
{
    if(ok(s,s->h.model_generate(s->h.user,model,ram,pos),"MODELCTRL GENERATE"))return -1;
    if(ok(s,s->h.model_sequence(s->h.user,model,ram,seq),"MODELCTRL sequence"))return -1;
    if(track&&track_add(&c->a,ram,model,seq))FAIL(s,"tracker list A is full");
    return 0;
}
static int cd_play(dw4_saveintf *s,si_comdl *c,int ram,const char *model,const char *seq,int track)   /* 3e4030 */
{
    if(ok(s,s->h.model_sequence(s->h.user,model,ram,seq),"MODELCTRL sequence"))return -1;
    if(track&&track_add(&c->a,ram,model,seq))FAIL(s,"tracker list A is full");
    return 0;
}
static int cd_play_b(dw4_saveintf *s,si_comdl *c,int ram,const char *model,const char *seq,int track) /* 3e42a0 */
{
    if(ok(s,s->h.model_sequence(s->h.user,model,ram,seq),"MODELCTRL sequence"))return -1;
    if(track&&track_add(&c->b,ram,model,seq))FAIL(s,"tracker list B is full");
    return 0;
}
/* 3e44f0 runs inside the update before the state machine: drop finished entries (list A: sequence no longer
 * current; list B: model no longer running), walking from the end as retail does. */
static void cd_prune(dw4_saveintf *s,si_comdl *c)
{
    for(int i=c->a.n-1;i>=0;i--)
        if(!s->h.model_is_sequence(s->h.user,c->a.v[i].model,c->a.v[i].ram,c->a.v[i].sequence)){
            memmove(&c->a.v[i],&c->a.v[i+1],(size_t)(c->a.n-i-1)*sizeof c->a.v[0]);c->a.n--;
        }
    for(int i=c->b.n-1;i>=0;i--)
        if(!s->h.model_is_running(s->h.user,c->b.v[i].model,c->b.v[i].ram)){
            memmove(&c->b.v[i],&c->b.v[i+1],(size_t)(c->b.n-i-1)*sizeof c->b.v[0]);c->b.n--;
        }
}
static int cd_empty_a(const si_comdl *c){return c->a.n<=0;}   /* 3e4280 */
static int cd_empty_b(const si_comdl *c){return c->b.n<=0;}   /* 3e44d0 */

/* ---- text order (3eba10 3ebce0 3ebd70 3ebdc0 3ebe00 3ec050 3ec120) ---- */
static int to_set(dw4_saveintf *s,const char *group,int player,int index,const char *ascii,const uint16_t *wide,int align,int colour)
{
    char f[16];return ok(s,s->h.text_set(s->h.user,group,font(player,index,f),align,colour,ascii,wide),"TEXTCTL set");
}
static int to_clear(dw4_saveintf *s,const char *group,int player,int index)                 /* 3ebdc0 */
{
    char f[16];return ok(s,s->h.text_clear(s->h.user,group,font(player,index,f)),"TEXTCTL clear");
}
static int msg_row(uint32_t id){for(int i=0;i<SI_MESSAGES;i++)if((si_messages[i].id&0xFFFFF)==id)return i;return -1;}
static int msg_run(dw4_saveintf *s,int row,uint32_t id)
{
    switch(id&0xF000){
    case 0x0000:return ok(s,s->h.text_script(s->h.user,"txt_mem.lua",si_messages[row].call),"txt_mem.lua");
    case 0x1000:case 0x2000:case 0x3000:return ok(s,s->h.text_script(s->h.user,"txt_Tar.lua",si_messages[row].call),"txt_Tar.lua");
    }
    return 0;
}
static int msg_clear_slots(dw4_saveintf *s,int row)
{
    for(unsigned k=0;k<si_messages[row].count;k++){
        const dw4_si_slot *e=&si_messages[row].slots[k];char f[16];
        if(ok(s,s->h.text_clear(s->h.user,e->group,font(e->kind,e->index,f)),"TEXTCTL clear"))return -1;
    }
    return 0;
}
/* 3ebe00: show a message: clear its slots, then run the original text script with its TXT call number. With flag 1
 * and the row's 0x100000 bit, the following row's call is run as well. */
static int msg_show(dw4_saveintf *s,uint32_t id,int flag)
{
    int row=msg_row(id);if(row<0)return 0;
    if(msg_clear_slots(s,row)||msg_run(s,row,id))return -1;
    if(flag==1&&(si_messages[row].id&0x100000)&&row+1<SI_MESSAGES){
        if(msg_run(s,row+1,id))return -1;
    }
    return 0;
}
static int msg_clear(dw4_saveintf *s,uint32_t id){int row=msg_row(id);return row<0?0:msg_clear_slots(s,row);}   /* 3ec050 */

/* ---- MESWIN (3eca70 3ecaa0 3ecad0 3ecae0 3ecb00 3ecb20 3ecb70 3ecb80 3ecb90 3ecba0 3ecbc0; update 3ec450) ---- */
static void mw_request_refresh(si_meswin *m){m->clear_req=1;m->dirty=1;}                            /* 3ecb90 */
static void mw_init(si_meswin *m){m->active=1;m->autoclose=0;m->done=0;m->busy=0;m->notice_only=0;m->clear_req=0;m->dirty=0;}  /* 3eca70 */
static void mw_autoclose(si_meswin *m){mw_request_refresh(m);m->autoclose=1;}                      /* 3ecaa0 */
static void mw_notice(si_meswin *m,int msg){m->dirty=1;m->message=msg;}                             /* 3ecad0: show a text only */
static void mw_choice(si_meswin *m,int msg,int initial){m->dirty=1;m->busy=1;m->message=msg;m->choice=initial;m->state=0;m->mode=0;}  /* 3ecae0 */
static void mw_continue(si_meswin *m,int msg){m->dirty=1;m->busy=1;m->message=msg;m->state=0;m->mode=1;}                          /* 3ecb00 */
static int mw_close(dw4_saveintf *s,si_meswin *m)                                                  /* 3ecb20 */
{
    m->busy=0;
    if(ok(s,s->h.model_sequence(s->h.user,"j_chrselmesswin",m->player,"SQ_WAIT"),"MODELCTRL j_chrselmesswin"))return -1;
    mw_request_refresh(m);return 0;
}
static void mw_text_only(si_meswin *m,int msg){m->dirty=1;m->notice_only=1;m->notice=msg;m->notice_step=0;}    /* 3ecba0 */
static void mw_resume(si_meswin *m)                                                                 /* 3ecbc0 */
{
    m->notice_only=0;
    if(m->shown==1){
        if(m->busy==1){if(m->mode==0)mw_choice(m,m->message,m->choice);else if(m->mode==1)mw_continue(m,m->message);}
        else mw_notice(m,m->message);
    }else mw_request_refresh(m);
}
static int mw_step(dw4_saveintf *s,si_meswin *m,const char *seq){return ok(s,s->h.model_sequence(s->h.user,"j_chrselmesswin",m->player,seq),"MODELCTRL j_chrselmesswin");}
static int mw_pad(dw4_saveintf *s,int player,uint32_t *h,uint32_t *e,uint32_t *r)
{
    *h=*e=*r=0;return s->h.pad(s->h.user,player,h,e,r);
}
static int mw_update(dw4_saveintf *s,si_meswin *m)                                                 /* 3ec450 */
{
    if(m->active!=1)return 0;
    if(m->notice_only!=1){
        if(m->busy==1){
            if(m->mode==0){
                switch(m->state){
                case 0:if(mw_step(s,m,m->choice==0?"SQ_LINESL00":"SQ_LINESL01"))return -1;m->state=1;break;
                case 1:{
                    uint32_t h,e,r;if(mw_pad(s,m->player,&h,&e,&r))return -1;
                    int up=(h&1)||((e|r)&0x10),down=(h&4)||((e|r)&0x40);
                    if(up){if(m->choice==1){m->choice=0;if(mw_step(s,m,"SQ_LINEUP00"))return -1;m->state=2;}}
                    else if(down){if(m->choice==0){m->choice=1;if(mw_step(s,m,"SQ_LINEDW01"))return -1;m->state=3;}}
                    else if(e&0x4000){if(mw_step(s,m,m->choice==0?"SQ_LINEON00":"SQ_LINEON01"))return -1;m->state=4;}
                    break;}
                case 2:if(!s->h.model_is_sequence(s->h.user,"j_chrselmesswin",m->player,"SQ_LINEUP00"))m->state=1;break;
                case 3:if(!s->h.model_is_sequence(s->h.user,"j_chrselmesswin",m->player,"SQ_LINEDW01"))m->state=1;break;
                case 4:
                    if(!s->h.model_is_sequence(s->h.user,"j_chrselmesswin",m->player,m->choice==0?"SQ_LINEON00":"SQ_LINEON01")){
                        mw_request_refresh(m);m->done=1;m->busy=0;
                    }
                    break;
                }
            }else if(m->mode==1){
                switch(m->state){
                case 0:if(mw_step(s,m,"SQ_NEXTSL00"))return -1;m->state=1;break;
                case 1:{uint32_t h,e,r;if(mw_pad(s,m->player,&h,&e,&r))return -1;if(e&0x4000){if(mw_step(s,m,"SQ_NEXTON00"))return -1;m->state=2;}break;}
                case 2:if(!s->h.model_is_sequence(s->h.user,"j_chrselmesswin",m->player,"SQ_NEXTON00")){mw_request_refresh(m);m->done=1;m->busy=0;}break;
                }
            }
        }
    }else if(m->notice_step==0){if(mw_step(s,m,"SQ_WAIT"))return -1;m->notice_step=1;}
    if(m->dirty==1){
        if(m->notice_only==1){if(msg_show(s,(uint32_t)m->notice,1))return -1;}
        else if(m->clear_req==0){m->shown=1;if(msg_show(s,(uint32_t)m->message,1))return -1;}
        else{
            for(int i=0;i<4;i++)if(to_clear(s,"CHRSELFONT06",m->player,i))return -1;
            for(int i=4;i<6;i++)if(to_clear(s,"CHRSELFONT16",m->player,i-4))return -1;
            m->clear_req=0;m->shown=0;if(m->autoclose==1)m->active=0;
        }
        m->dirty=0;
    }
    return 0;
}

/* ---- shared lookups ---- */
static int model_row(const char *model){for(int i=0;i<16;i++)if(!strcmp(si_digimon[i].model,model))return i;return 0;}
static si_display *area_of(dw4_saveintf *s,int player,int index)      /* item[player]->entry->areas[index] */
{
    int e=s->item[player].entry;if(e<0||index<0||index>=DW4_SI_SLOTS)return NULL;return &s->entry[e].area[index];
}
static si_display *panel_source(dw4_saveintf *s,const si_panel *p)    /* 3d9ec0: source 0 = a saved area, 1 = the player's own display */
{
    return p->source==0?area_of(s,p->player,p->index):&s->display[p->player];
}
#define NEED(s,p,what) do{if(!(p)){snprintf((s)->error,sizeof (s)->error,"%s: the player's data entry is missing",what);return -1;}}while(0)
static const char *const area_open[4]={"SQ_AAREAOPEN","SQ_BAREAOPEN","SQ_CAREAOPEN","SQ_DAREAOPEN"};
static int same_data(const si_display *a,const si_display *b)          /* the conflict test of 3db060/3db780 */
{
    return a->s.used==1&&a->s.unique==b->s.unique&&a->s.name[0]&&b->s.name[0]&&!memcmp(a->s.name,b->s.name,sizeof a->s.name);
}
/* Whether another player already holds the data of `d` (retail loops players but the current one). */
static int data_free(dw4_saveintf *s,int player,const si_display *d)
{
    if(d->s.used!=1)return 1;
    for(int k=0;k<DW4_SI_PLAYERS;k++)if(k!=player&&same_data(&s->display[k],d))return 0;
    return 1;
}

/* ---- SELSLOT panel (3d9de0 3d9e10 3d9e40 3d9e70 3d9e90 3d9ec0 3da5f0 3da7c0) ---- */
static void pn_open(si_panel *p,int source,int index){p->source=source;p->index=index;p->done=0;p->action=1;p->c40=p->c3c=p->step=0;}    /* 3d9e10 */
static void pn_clear(si_panel *p,int source,int index){p->source=source;p->index=index;p->done=0;p->action=3;p->c40=p->c3c=p->step=0;}  /* 3d9e40 */
static void pn_mark(si_panel *p,int mark){p->done=0;p->mark=mark;p->action=2;p->c40=p->c3c=p->step=0;}                                  /* 3d9e70 */
static int digits(dw4_saveintf *s,const char *group,int player,int index,int value,int align)
{
    char t[16];snprintf(t,sizeof t,"%d",value);return to_set(s,group,player,index,t,NULL,align,0);
}
static int pn_texts(dw4_saveintf *s,si_panel *p)                       /* 3d9ec0 */
{
    si_display *d=panel_source(s,p);NEED(s,d,"panel");
    int left=p->side==0,pl=p->player;
    if(d->s.used==1){
        int row=model_row(d->s.model);char name[64];
        if(to_set(s,"CHRSELFONT03",pl,left?0:0xA,NULL,d->s.name,0,0))return -1;
        if(s->h.species_name(s->h.user,row,name,sizeof name))FAIL(s,"DATABASE shinka NAME is unavailable");
        if(to_set(s,"CHRSELFONT04",pl,left?0xA:0xB,name,NULL,0,0))return -1;
        if(digits(s,"CHRSELFONT04",pl,left?0:1,d->s.level,1))return -1;
        if(digits(s,"CHRSELFONT05",pl,left?0:2,d->s.hp,2))return -1;
        if(digits(s,"CHRSELFONT05",pl,left?0xA:0xC,d->s.mhp,2))return -1;
        if(digits(s,"CHRSELFONT05",pl,left?1:3,d->s.mp,2))return -1;
        if(digits(s,"CHRSELFONT05",pl,left?0xB:0xD,d->s.mmp,2))return -1;
    }else if(msg_show(s,(uint32_t)((pl<<16)|(left?0x10:0x110)),0))return -1;
    return 0;
}
static int pn_clear_texts(dw4_saveintf *s,si_panel *p)                 /* 3da5f0 */
{
    int pl=p->player;
    if(p->side==0){
        if(to_clear(s,"CHRSELFONT03",pl,0)||to_clear(s,"CHRSELFONT04",pl,0)||to_clear(s,"CHRSELFONT04",pl,0xA)||
           to_clear(s,"CHRSELFONT05",pl,0)||to_clear(s,"CHRSELFONT05",pl,0xA)||to_clear(s,"CHRSELFONT05",pl,1)||
           to_clear(s,"CHRSELFONT05",pl,0xB))return -1;
        return msg_clear(s,(uint32_t)((pl<<16)|0x10));
    }
    if(p->used==1){
        if(to_clear(s,"CHRSELFONT03",pl,0xA)||to_clear(s,"CHRSELFONT04",pl,0xB)||to_clear(s,"CHRSELFONT04",pl,1)||
           to_clear(s,"CHRSELFONT05",pl,2)||to_clear(s,"CHRSELFONT05",pl,0xC)||to_clear(s,"CHRSELFONT05",pl,3)||
           to_clear(s,"CHRSELFONT05",pl,0xD))return -1;
        return 0;
    }
    return msg_clear(s,(uint32_t)((pl<<16)|0x110));
}
static void pn_reset(si_panel *p){p->done=1;p->action=0;p->c40=p->c3c=p->step=0;}
/* Returns 1 when the panel's action has finished (3da7c0). */
static int pn_update(dw4_saveintf *s,si_panel *p)
{
    if(p->done==1)return 1;
    si_comdl *c=&s->comdl[p->player];int pl=p->player;
    switch(p->action){
    case 0:break;
    case 1:{
        if(p->step==0){
            si_display *d=panel_source(s,p);NEED(s,d,"panel");
            p->used=d->s.used==1;
            if(p->used){
                int row=model_row(d->s.model);
                if(p->side==0){
                    if(cd_generate(s,c,pl,"j_digifacewin",si_digimon[row].open,c->home,1)||
                       cd_generate(s,c,pl,"j_mainstatuswin","SQ_OPEN",c->home,1))return -1;
                }else if(cd_generate(s,c,pl,"j_savecheckwin",si_digimon[row].open,c->home,1))return -1;
            }else if(p->side==0){
                if(cd_generate(s,c,pl,"j_digifacewin","SQ_nofaceOPEN",c->home,1)||
                   cd_generate(s,c,pl,"j_mainstatuswin","SQ_NOOPEN",c->home,1))return -1;
            }else if(cd_generate(s,c,pl,"j_savecheckwin","SQ_nofaceOPEN",c->home,1))return -1;
            p->step++;p->c40=p->c3c=0;
        }else if(p->step==1&&cd_empty_a(c)){
            if(pn_texts(s,p))return -1;
            pn_reset(p);
        }
        break;}
    case 3:{
        si_display *d=panel_source(s,p);NEED(s,d,"panel");
        p->used=d->s.used==1;
        if(p->used){
            int row=model_row(d->s.model);
            if(p->side==0){
                if(cd_play(s,c,pl,"j_digifacewin",si_digimon[row].idle,0)||cd_play(s,c,pl,"j_mainstatuswin","SQ_WAIT",0))return -1;
            }else if(cd_play(s,c,pl,"j_savecheckwin",si_digimon[row].idle,0))return -1;
        }else if(p->side==0){
            if(cd_play(s,c,pl,"j_digifacewin","SQ_noface",0)||cd_play(s,c,pl,"j_mainstatuswin","SQ_NOWAIT",0))return -1;
        }else if(cd_play(s,c,pl,"j_savecheckwin","SQ_noface",0))return -1;
        if(pn_clear_texts(s,p)||pn_texts(s,p))return -1;
        pn_reset(p);
        break;}
    case 2:{
        si_display *d=panel_source(s,p);NEED(s,d,"panel");
        p->used=d->s.used==1;
        if(p->step==0){
            if(p->side==0){
                if(cd_play_b(s,c,pl,"j_digifacewin","SQ_CLOSE",1))return -1;
                if(p->used){
                    const char *seq=p->mark==0?"SQ_CLOSE":p->mark==1?"SQ_LINEON00":"SQ_CANCEL";
                    if(cd_play_b(s,c,pl,"j_mainstatuswin",seq,1))return -1;
                }else if(cd_play_b(s,c,pl,"j_mainstatuswin","SQ_NOCLOSE",1))return -1;
            }else if(cd_play_b(s,c,pl,"j_savecheckwin","SQ_CLOSE",1))return -1;
            if(pn_clear_texts(s,p))return -1;
            p->step++;p->c40=p->c3c=0;
        }else if(p->step==1&&cd_empty_b(c)){pn_reset(p);}
        break;}
    }
    return p->done;
}

/* ---- DATASELINTF: the area selector (3dafb0 3daff0 3db060 3db780 3dbf90 3dc2e0 3dc590 3dcab0 3dcc60 3dd160 3dd440 3dd6d0) ---- */
static void sel_init(si_select *x,int player,int mode){x->player=player;x->f48=0;x->mode=mode;x->cursor=0;x->f30=x->f31=x->f32=0;x->f34=0;memset(x->lvl,0,sizeof x->lvl);}  /* 3dafb0 */
static void sel_reset(si_select *x,int level){                                                                                      /* 3daff0 */
    switch(level){default:x->lvl[0]=x->lvl[3]=x->lvl[2]=x->lvl[1]=0;break;case 1:x->lvl[1]=x->lvl[3]=x->lvl[2]=0;break;case 2:x->lvl[2]=x->lvl[3]=0;break;case 3:x->lvl[3]=0;break;}
}
/* Generate the four area windows (open sequence of the saved character's model, or SQ_NOOPEN). */
static int sel_generate_areas(dw4_saveintf *s,int pl,si_comdl *c)
{
    for(int i=0;i<4;i++){
        si_display *d=area_of(s,pl,i);NEED(s,d,"areas");
        if(d->s.used==1){
            if(d->s.model[0]){
                int row=model_row(d->s.model);
                if(cd_generate(s,c,pl,si_area_window[i],si_digimon[row].open,c->home,1))return -1;
            }else{d->s.used=0;if(cd_generate(s,c,pl,si_area_window[i],"SQ_NOOPEN",c->home,1))return -1;}
        }else{d->s.used=0;if(cd_generate(s,c,pl,si_area_window[i],"SQ_NOOPEN",c->home,1))return -1;}
    }
    return 0;
}
static int sel_area_names(dw4_saveintf *s,int pl)                      /* the CHRSELFONT08 names (or 0x300|i notices) */
{
    for(int i=0;i<4;i++){
        si_display *d=area_of(s,pl,i);NEED(s,d,"areas");
        if(d->s.used==1){if(to_set(s,"CHRSELFONT08",pl,i,NULL,d->s.name,1,0))return -1;}
        else{d->s.used=0;if(msg_show(s,(uint32_t)((pl<<16)|0x300|i),0))return -1;}
    }
    return 0;
}
static int sel_close_areas(dw4_saveintf *s,si_select *x,si_comdl *c)    /* the shared prologue of 3dbf90/3dc2e0/3dd440 */
{
    int pl=x->player;
    for(int i=0;i<4;i++)if(cd_play_b(s,c,pl,si_area_window[i],"SQ_CLOSE",1))return -1;
    for(int i=0;i<4;i++)if(to_clear(s,"CHRSELFONT08",pl,i))return -1;
    x->f30=0;return 0;
}
static int sel_open(dw4_saveintf *s,si_select *x,int level)            /* 3db060 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];
    switch(v){
    case 0:{
        if(sel_generate_areas(s,pl,c))return -1;
        x->f30=1;
        if(cd_generate(s,c,pl,"j_saveareacursorr","SQ_OPEN",c->home,1))return -1;
        x->f34=1;
        if(x->mode==0){
            si_display *e=area_of(s,pl,x->cursor);NEED(s,e,"cursor");
            int free_=data_free(s,pl,e);
            if(free_){x->conflict=0;mw_notice(m,(pl<<16)|0x513);}else{x->conflict=1;mw_notice(m,(pl<<16)|0x515);}
            pn_open(&s->panel[pl][0],0,x->cursor);
        }else{x->conflict=0;mw_notice(m,(pl<<16)|0x503);pn_open(&s->panel[pl][0],1,pl);}
        x->f31=1;v++;break;}
    case 1:
        if(pn_update(s,&s->panel[pl][0])==1&&cd_empty_a(c)){
            if(sel_area_names(s,pl))return -1;
            ret=1;v++;
        }
        break;
    case 2:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_pad(dw4_saveintf *s,si_select *x,uint32_t *edges,int *up,int *down,int *right,int *left)
{
    uint32_t h=0,e=0,r=0;*up=*down=*right=*left=0;*edges=0;
    if(!s->item[x->player].pad_enabled)return 0;
    if(s->h.pad(s->h.user,x->player,&h,&e,&r))FAIL(s,"pad is unavailable");
    *edges=e;
    *up=(h&1)||((e|r)&0x10);*down=(h&4)||((e|r)&0x40);*left=(h&8)||((e|r)&0x80);*right=(h&2)||((e|r)&0x20);
    return 0;
}
static void item_choose(dw4_saveintf *s,int player)                    /* 3ee190: the player took the data; others wait 0x3C */
{
    for(int i=0;i<DW4_SI_PLAYERS;i++){si_item *t=&s->item[i];t->state=1;t->subsub=t->sub=t->subsubsub=0;t->pad_enabled=0;t->timer=0x3C;}
    si_item *t=&s->item[player];t->state=0;t->subsubsub=t->subsub=t->sub=0;t->pad_enabled=1;t->timer=0;
}
static int sel_navigate(dw4_saveintf *s,si_select *x,int level)         /* 3db780 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    uint32_t edges;int up,down,right,left;
    if(sel_pad(s,x,&edges,&up,&down,&right,&left))return -1;
    switch(v){
    case 0:{
        int cur=x->cursor,nxt=cur;
        if(up){if(cur==2)nxt=0;else if(cur==3)nxt=1;}
        else if(down){if(cur==0)nxt=2;else if(cur==1)nxt=3;}
        else if(right){if(cur==0)nxt=1;else if(cur==2)nxt=3;}
        else if(left){if(cur==1)nxt=0;else if(cur==3)nxt=2;}
        if(nxt!=cur){
            x->cursor=nxt;
            if(x->mode==0)pn_clear(&s->panel[pl][0],0,x->cursor);
            if(cd_play(s,c,pl,"j_saveareacursorr","SQ_MOVE",0))return -1;
            v=1;
        }else if(edges&0x4000){
            if(x->mode==0){
                si_display *d=area_of(s,pl,cur);NEED(s,d,"cursor");
                if(d->s.used==1&&data_free(s,pl,d)){
                    s->display[pl].s.used=1;s->display[pl].s.unique=d->s.unique;memcpy(s->display[pl].s.name,d->s.name,sizeof d->s.name);
                    x->cancel=0;v=2;
                }
            }else{item_choose(s,pl);x->cancel=0;v=2;}
        }else if(edges&0x2000){v=4;x->cancel=1;}
        if(x->mode==0){
            pn_clear(&s->panel[pl][0],0,x->cursor);
            si_display *d=area_of(s,pl,x->cursor);NEED(s,d,"cursor");
            if(data_free(s,pl,d)){if(x->conflict!=0){x->conflict=0;mw_notice(&s->mes[pl],(pl<<16)|0x513);}}
            else if(x->conflict!=1){x->conflict=1;mw_notice(&s->mes[pl],(pl<<16)|0x515);}
        }
        break;}
    case 1:
        if(x->mode==0){if(pn_update(s,&s->panel[pl][0])!=1)break;}
        if(cd_empty_a(c)){if(cd_play(s,c,pl,"j_saveareacursorr",si_line_select[x->cursor],0))return -1;v=0;}
        break;
    case 2:
        if(cd_play_b(s,c,pl,"j_saveareacursorr",si_line_on[x->cursor],1))return -1;
        x->f34=0;v=3;break;
    case 3:if(cd_empty_b(c))v=6;break;
    case 4:if(cd_play_b(s,c,pl,"j_saveareacursorr","SQ_CANCEL",1))return -1;x->f34=0;v=5;break;
    case 5:if(cd_empty_b(c))v=6;break;
    case 6:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_close(dw4_saveintf *s,si_select *x,int level)            /* 3dbf90 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    switch(v){
    case 0:
        if(x->f30==1&&sel_close_areas(s,x,c))return -1;
        if(x->f31==1)pn_mark(&s->panel[pl][0],0);
        if(x->f32==1)pn_mark(&s->panel[pl][1],0);
        if(x->f34==1&&cd_play_b(s,c,pl,"j_saveareacursorr","SQ_CLOSE",1))return -1;
        v++;break;
    case 1:
        if(x->f31==1){if(pn_update(s,&s->panel[pl][0])!=1)break;x->f31=0;}
        if(x->f32==1){if(pn_update(s,&s->panel[pl][1])!=1)break;x->f32=0;}
        if(cd_empty_b(c)){ret=1;v++;}
        break;
    case 2:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_to_second(dw4_saveintf *s,si_select *x,int level)         /* 3dc2e0: areas close, then the second panel opens on the cursor */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    switch(v){
    case 3:break;
    case 0:if(x->f30==1&&sel_close_areas(s,x,c))return -1;v++;break;
    case 1:if(cd_empty_b(c)){v++;pn_open(&s->panel[pl][1],0,x->cursor);x->f32=1;}break;
    case 2:if(pn_update(s,&s->panel[pl][1])==1){ret=1;v++;}break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_return_areas(dw4_saveintf *s,si_select *x,int level)      /* 3dc590 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    switch(v){
    case 0:pn_mark(&s->panel[pl][1],0);x->f32=0;v++;break;
    case 1:if(pn_update(s,&s->panel[pl][1])==1)v++;break;
    case 2:
        for(int i=0;i<4;i++){
            si_display *d=area_of(s,pl,i);NEED(s,d,"areas");
            if(d->s.used==1){if(cd_generate(s,c,pl,si_area_window[i],si_digimon[model_row(d->s.model)].open,c->home,1))return -1;}
            else if(cd_generate(s,c,pl,si_area_window[i],"SQ_NOOPEN",c->home,1))return -1;
        }
        v++;x->f30=1;break;
    case 3:if(cd_empty_a(c)){if(sel_area_names(s,pl))return -1;v++;}break;
    case 4:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_close_both(dw4_saveintf *s,si_select *x,int level)       /* 3dcab0 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);
    switch(v){
    case 0:pn_mark(&s->panel[pl][0],0);pn_mark(&s->panel[pl][1],0);x->f32=0;v++;x->f31=0;break;
    case 1:if(pn_update(s,&s->panel[pl][0])==1&&pn_update(s,&s->panel[pl][1])==1)v++;break;
    case 2:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return ret;
}
static int sel_reopen(dw4_saveintf *s,si_select *x,int level)            /* 3dcc60 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    switch(v){
    case 0:
        for(int i=0;i<4;i++){
            si_display *d=area_of(s,pl,i);NEED(s,d,"areas");
            if(d->s.used==1){if(cd_generate(s,c,pl,si_area_window[i],si_digimon[model_row(d->s.model)].open,c->home,1))return -1;}
            else if(cd_generate(s,c,pl,si_area_window[i],"SQ_NOOPEN",c->home,1))return -1;
        }
        x->f30=1;pn_open(&s->panel[pl][0],1,pl);v++;x->f31=1;break;
    case 1:
        if(cd_empty_a(c)&&pn_update(s,&s->panel[pl][0])==1){v++;if(sel_area_names(s,pl))return -1;}
        break;
    case 2:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_area_opening(dw4_saveintf *s,si_select *x,int level)      /* 3dd160 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    switch(v){
    case 0:
        if(x->f34==0){
            if(x->cursor<0||x->cursor>3)FAIL(s,"area cursor out of range");
            if(cd_generate(s,c,pl,"j_saveareacursorr",area_open[x->cursor],c->home,1))return -1;
            x->f34=1;
        }
        v++;break;
    case 1:
        if(cd_empty_a(c)){v++;mw_notice(&s->mes[pl],(pl<<16)|(x->mode==0?0x513:0x503));}
        break;
    case 2:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_close_cursor(dw4_saveintf *s,si_select *x,int level)      /* 3dd440 */
{
    int pl=x->player,ret=0,v=lvl_get(x->lvl,level);si_comdl *c=&s->comdl[pl];
    switch(v){
    case 0:
        if(x->f30==1&&sel_close_areas(s,x,c))return -1;
        if(x->f34==1&&cd_play_b(s,c,pl,"j_saveareacursorr","SQ_CLOSE",1))return -1;
        v++;break;
    case 1:if(cd_empty_b(c)){ret=1;v++;}break;
    case 2:ret=1;break;
    }
    lvl_set(x->lvl,level,v);return s->error[0]?-1:ret;
}
static int sel_idle_areas(dw4_saveintf *s,si_select *x,int level)        /* 3dd6d0: every player sharing the entry returns its areas to idle */
{
    int pl=x->player,e=s->item[pl].entry;NEED(s,e>=0,"areas");
    int v=lvl_get(x->lvl,level);(void)v;
    si_entry *en=&s->entry[e];
    for(int k=0;k<en->nplayers;k++){
        int q=en->players[k];si_comdl *c=&s->comdl[q];
        for(int i=0;i<4;i++){
            si_display *d=area_of(s,q,i);NEED(s,d,"areas");
            if(d->s.used==1){
                if(cd_play(s,c,q,si_area_window[i],si_digimon[model_row(d->s.model)].idle,0))return -1;
                if(to_set(s,"CHRSELFONT08",q,i,NULL,d->s.name,1,0))return -1;
            }else{
                if(cd_play(s,c,q,si_area_window[i],"SQ_NOOPEN",0))return -1;
                if(msg_show(s,(uint32_t)((q<<16)|0x300|i),0))return -1;
            }
        }
    }
    lvl_set(x->lvl,level,lvl_get(x->lvl,level));return 1;
}

/* ---- DEGISTATECTRL: the memory-card slot chooser (3e0b80 3e0bb0 3e0c40 3e1760 3e2a80 3e2b10 3e3070) ---- */
typedef struct {const char *sequence;int32_t slot;} si_row;
static const si_row *sl_rows(const si_slots *x){return x->variant==0?(const si_row *)si_card_rows2:(const si_row *)si_card_rows5;}
static int sl_slot_ok(const dw4_saveintf *s,const si_slots *x,int row){int slot=sl_rows(x)[row].slot;return slot>=0&&slot<s->card.nslots&&s->card.slots[slot].ok==1;}
static void sl_mark(const si_slots *x,int row,int *ram,const char **model,const char **open_seq)
{
    static const char *const q[4]={"SQ_OPEN1A","SQ_OPEN1B","SQ_OPEN1C","SQ_OPEN1D"};
    if(x->variant==0){*ram=x->player*2+row;*model="j_slotmark02";*open_seq=row==0?"SQ_OPEN01":"SQ_OPEN02";}
    else if(row<4){*ram=x->player*5+row;*model="j_slotmark01";*open_seq=q[row];}
    else{*ram=x->player*2;*model="j_slotmark02";*open_seq="SQ_OPEN02";}
}
static void sl_reset(si_slots *x){x->done=0;x->cancel=0;x->closed=0;x->f35=0;memset(x->lvl,0,sizeof x->lvl);}                          /* 3e0b80 */
static void sl_init(si_slots *x,int scene_mode){sl_reset(x);x->row=0;if(scene_mode==0){x->rows=5;}else if(scene_mode==1){x->rows=2;}else x->rows=9;}  /* 3e0bb0 */
/* A mark opens when its slot is usable (3e3e00 when not yet running, else a plain sequence); `close_others` also closes
 * the marks of slots that are not usable (3e1760/3e3070). exclude is a row index treated as unusable (3e3070). */
static int sl_marks(dw4_saveintf *s,si_slots *x,int close_others,int exclude)
{
    int pl=x->player,n=x->variant==0?2:5;si_comdl *c=&s->comdl[pl];
    for(int i=0;i<n;i++){
        int ram;const char *model,*seq;sl_mark(x,i,&ram,&model,&seq);
        int usable=sl_slot_ok(s,x,i)&&i!=exclude;
        if(usable){
            if(!s->h.model_is_running(s->h.user,model,ram)){if(cd_generate(s,c,ram,model,seq,c->home,0))return -1;}
            else if(cd_play(s,c,ram,model,seq,0))return -1;
        }else if(close_others&&s->h.model_is_running(s->h.user,model,ram)){
            if(cd_play_b(s,c,ram,model,"SQ_CLOSE",0))return -1;
        }
    }
    return 0;
}
static int sl_row_texts(dw4_saveintf *s,si_slots *x)
{
    int pl=x->player,r=x->row;uint32_t base=(uint32_t)(pl<<16);
    if(x->variant==0){if(r==0&&msg_show(s,base|0x1100,0))return -1;if(r==1&&msg_show(s,base|0x1101,0))return -1;}
    else{static const int id[5]={0x1102,0x1103,0x1104,0x1105,0x1101};if(r>=0&&r<5&&msg_show(s,base|(uint32_t)id[r],0))return -1;}
    return 0;
}
static int sl_info(dw4_saveintf *s,si_slots *x,int initial)             /* the 0x102E warning follows the highlighted row */
{
    uint32_t id=(uint32_t)((x->player<<16)|0x102E);int usable=sl_slot_ok(s,x,x->row);
    if(initial){if(!usable){x->info=0;return msg_show(s,id,0);}x->info=1;return msg_clear(s,id);}
    if(x->info==0){if(usable){x->info=1;return msg_clear(s,id);}}
    else if(!usable){x->info=0;return msg_show(s,id,0);}
    return 0;
}
static int sl_open(dw4_saveintf *s,si_slots *x,int cursor)               /* 3e0c40 (returns the done flag, +0x34) */
{
    int pl=x->player;si_comdl *c=&s->comdl[pl];
    if(x->lvl[0]!=0)return 0;
    switch(x->lvl[1]){
    case 0:
        if(cursor!=-1)x->row=cursor;
        if(s->card.unformatted==0){if(cd_generate(s,c,pl,"j_slotbase","SQ_OPENPS01",c->home,1))return -1;x->variant=0;}
        else{if(cd_generate(s,c,pl,"j_slotbase","SQ_OPENPS02",c->home,1))return -1;x->variant=1;}
        if(cd_generate(s,c,pl,"j_memoryiconwin","SQ_OPEN",c->home,1))return -1;
        x->f37=0;x->lvl[1]++;x->lvl[3]=x->lvl[2]=0;break;
    case 1:
        if(cd_empty_a(c)){
            if(cd_generate(s,c,pl,"j_slotcursor",sl_rows(x)[x->row].sequence,c->home,1))return -1;
            if(sl_marks(s,x,0,-1))return -1;
            if(msg_show(s,(uint32_t)((pl<<16)|0x100C),0)||sl_row_texts(s,x)||sl_info(s,x,1))return -1;
            x->lvl[1]++;x->lvl[3]=x->lvl[2]=0;
        }
        break;
    case 2:
        if(cd_empty_a(c)){x->done=1;x->lvl[0]++;x->lvl[3]=x->lvl[2]=x->lvl[1]=0;}
        break;
    }
    return s->error[0]?-1:x->done;
}
static int sl_update(dw4_saveintf *s,si_slots *x,int pad_enabled,int wait_open)   /* 3e1760 (returns +0x35) */
{
    int pl=x->player;si_comdl *c=&s->comdl[pl];int n=x->variant==0?2:5;
    if(wait_open==1){if(x->lvl[0]!=1)return 0;if(x->f35==1)return 1;}
    uint32_t h=0,e=0,r=0;int up=0,down=0,left=0,right=0;
    if(pad_enabled==1){
        if(s->h.pad(s->h.user,pl,&h,&e,&r))FAIL(s,"pad is unavailable");
        up=(h&1)||((e|r)&0x10);down=(h&4)||((e|r)&0x40);left=(h&8)||((e|r)&0x80);right=(h&2)||((e|r)&0x20);
    }
    if(sl_marks(s,x,1,-1))return -1;
    if(sl_info(s,x,0))return -1;
    if((x->variant==0&&s->card.unformatted==1)||(x->variant==1&&s->card.unformatted==0)){   /* the card's layout changed */
        x->f37=1;x->f35=1;x->lvl[0]++;x->lvl[3]=x->lvl[2]=0;x->lvl[1]=0;return x->f35;
    }
    const si_row *rows=sl_rows(x);
    switch(x->lvl[1]){
    case 0:{
        int moved=0;
        if(x->variant==0){
            if(up){if(x->row!=0){x->row=0;moved=1;}}
            else if(down){if(x->row!=1){x->row=1;moved=1;}}
            else if(e&0x4000){
                if(sl_slot_ok(s,x,x->row)){item_choose(s,pl);x->chosen_slot=rows[x->row].slot;if(cd_play(s,c,pl,"j_slotcursor","SQ_ON",1))return -1;x->lvl[1]=2;x->lvl[3]=x->lvl[2]=0;}
            }else if(e&0x2000){x->cancel=1;if(cd_play(s,c,pl,"j_slotcursor","SQ_CANCEL",1))return -1;x->lvl[1]=2;x->lvl[3]=x->lvl[2]=0;}
        }else{
            if(e&0x4000){
                if(sl_slot_ok(s,x,x->row)){item_choose(s,pl);x->chosen_slot=rows[x->row].slot;if(cd_play(s,c,pl,"j_slotcursor","SQ_ON",1))return -1;x->lvl[1]=2;x->lvl[3]=x->lvl[2]=0;}
            }else if(e&0x2000){x->cancel=1;if(cd_play(s,c,pl,"j_slotcursor","SQ_CANCEL",1))return -1;x->lvl[1]=2;x->lvl[3]=x->lvl[2]=0;}
            else if(up){if(x->row!=0){x->row=0;moved=1;}}
            else if(down){if(x->row!=x->rows-1){x->row=x->rows-1;moved=1;}}
            else if(x->row!=x->rows-1){
                if(right){x->row++;if(x->row>=x->rows-1)x->row=x->rows-2;else moved=1;}
                else if(left){x->row--;if(x->row<0)x->row=0;else moved=1;}
            }
        }
        if(moved){if(cd_play(s,c,pl,"j_slotcursor","SQ_MOVE",1))return -1;x->lvl[1]++;x->lvl[3]=x->lvl[2]=0;}
        break;}
    case 1:
        if(cd_empty_a(c)){
            if(cd_play(s,c,pl,"j_slotcursor",rows[x->row].sequence,0)||sl_row_texts(s,x)||sl_info(s,x,0))return -1;
            x->lvl[1]=0;x->lvl[3]=x->lvl[2]=0;
        }
        break;
    case 2:
        if(cd_empty_a(c)){
            if(cd_play(s,c,pl,"j_slotcursor",rows[x->row].sequence,0))return -1;
            x->f35=1;x->lvl[0]++;x->lvl[3]=x->lvl[2]=0;x->lvl[1]=0;
        }
        break;
    }
    (void)n;return x->f35;
}
static int sl_confirm(dw4_saveintf *s,si_slots *x)                       /* 3e2a80: back to the live chooser */
{
    int pl=x->player;x->lvl[0]=1;x->lvl[3]=x->lvl[2]=x->lvl[1]=0;x->f35=0;
    return cd_play(s,&s->comdl[pl],pl,"j_slotcursor",sl_rows(x)[x->row].sequence,0);
}
static int sl_close(dw4_saveintf *s,si_slots *x)                         /* 3e2b10 (returns +0x38) */
{
    int pl=x->player;si_comdl *c=&s->comdl[pl];
    if(x->lvl[0]!=2)return 0;
    if(x->closed==1)return 1;
    switch(x->lvl[1]){
    case 0:{
        if(cd_play_b(s,c,pl,"j_slotbase","SQ_CLOSE",1)||cd_play_b(s,c,pl,"j_slotcursor","SQ_CLOSE",1)||cd_play_b(s,c,pl,"j_memoryiconwin","SQ_CLOSE",1))return -1;
        if(msg_clear(s,(uint32_t)((pl<<16)|0x100C))||msg_clear(s,(uint32_t)((pl<<16)|0x1100))||msg_clear(s,(uint32_t)((pl<<16)|0x102E)))return -1;
        int n=x->variant==0?2:5;
        for(int i=0;i<n;i++){
            int ram;const char *model,*seq;sl_mark(x,i,&ram,&model,&seq);
            if(s->h.model_is_running(s->h.user,model,ram)&&cd_play_b(s,c,ram,model,"SQ_CLOSE",0))return -1;
        }
        x->lvl[1]++;x->lvl[3]=0;x->lvl[2]=0;break;}
    case 1:
        if(cd_empty_b(c)){x->closed=1;x->lvl[1]++;x->lvl[3]=0;x->lvl[2]=0;}
        break;
    }
    return x->closed;
}
static int sl_refresh(dw4_saveintf *s,si_slots *x,int exclude)           /* 3e3070 */
{
    if(sl_marks(s,x,1,exclude))return -1;
    uint32_t id=(uint32_t)((x->player<<16)|0x102E);
    if(x->info==0){if(sl_slot_ok(s,x,x->row)){x->info=1;return msg_clear(s,id);}}
    else if(!sl_slot_ok(s,x,x->row)){x->info=0;return msg_show(s,id,0);}
    return 0;
}

/* ---- card object and flows (3f1460, update 3f1490; flows 3ecdc0 3ed050 3ed2e0 3ed650 3edc20 3edf60) ---- */
static int32_t *it_lv(si_item *it,int level){switch(level){case 1:return &it->sub;case 2:return &it->subsub;case 3:return &it->subsubsub;default:return &it->state;}}
static void it_set(si_item *it,int level,int v)                          /* the write-back tail shared by every flow */
{
    switch(level){
    case 0:it->state=v;it->subsubsub=0;it->subsub=0;it->sub=0;break;
    case 1:it->sub=v;it->subsubsub=0;it->subsub=0;break;
    case 2:it->subsub=v;it->subsubsub=0;break;
    case 3:it->subsubsub=v;break;
    }
}
static void it_go(si_item *it,int state,int sub,int subsub,int subsubsub){it->state=state;it->sub=sub;it->subsub=subsub;it->subsubsub=subsubsub;}
static void ct_go(si_ctrl *t,int state,int sub,int subsub,int subsubsub){t->state=state;t->sub=sub;t->subsub=subsub;t->subsubsub=subsubsub;}
static int card_begin(dw4_saveintf *s,int kind,int slot,int player,int area)   /* 3f1460 */
{
    si_card *c=&s->card;c->slot=slot;c->kind=kind;c->result=0;c->done=0;c->busy=1;c->formatted_now=0;c->step=0;c->player=player;
    return ok(s,s->h.card_request(s->h.user,kind,slot,player,area),"SAVEUTILITY request");
}
static int card_update(dw4_saveintf *s)                                    /* 3f1490, one poll per update */
{
    si_card *c=&s->card;int present=0,unf=0,n=0;
    if(s->h.card_state(s->h.user,&present,&unf,c->slots,&n))FAIL(s,"SAVEUTILITY GETDELIVER failed");
    c->present=(uint8_t)present;c->unformatted=(uint8_t)unf;c->nslots=n;
    if(c->busy){int r=0;if(s->h.card_done(s->h.user,&r)){c->result=r;c->busy=0;c->done=1;}}
    return 0;
}
static int flow_choice(dw4_saveintf *s,int pl,si_meswin *m,int msg_a,int msg_b,int initial,int level)       /* 3ecdc0 */
{
    si_item *it=&s->item[pl];int v=*it_lv(it,level),ret=0;
    switch(v){
    case 0:mw_continue(m,msg_a);v++;break;
    case 1:if(!m->busy)v++;break;
    case 2:mw_choice(m,msg_b,initial);v++;break;
    case 3:if(!m->busy){if(m->choice==0)ret=1;else if(m->choice==1)ret=2;}break;
    }
    it_set(it,level,v);return ret;
}
static int flow_check(dw4_saveintf *s,int pl,int slot,int level)                                             /* 3ed050 */
{
    si_item *it=&s->item[pl];int v=*it_lv(it,level),ret=0;
    switch(v){
    case 0:if(card_begin(s,3,slot,pl,0))return -1;v++;break;
    case 1:if(s->card.done){if(s->card.result!=2)ret=2;else v++;}break;
    case 2:if(card_begin(s,1,slot,pl,0))return -1;v++;break;
    case 3:if(s->card.done)ret=s->card.result!=2?2:1;break;
    }
    it_set(it,level,v);return ret;
}
static int flow_make(dw4_saveintf *s,int pl,si_meswin *m,int slot,int level)                                  /* 3ed2e0 */
{
    si_item *it=&s->item[pl];int v=*it_lv(it,level),ret=0;
    switch(v){
    case 0:mw_notice(m,(pl<<16)|0x1003);if(card_begin(s,6,slot,pl,0))return -1;v++;break;
    case 1:if(s->card.done){if(s->card.result!=2)ret=2;else v++;}break;
    case 2:if(card_begin(s,0,slot,pl,0)||ok(s,s->h.timer_start(s->h.user,"MakeDataTime",3000000000LL),"timer"))return -1;v++;break;
    case 3:
        if(slot<s->card.nslots&&s->card.slots[slot].ok==1){
            if(s->h.timer_done(s->h.user,"MakeDataTime")==1){v++;if(s->card.done)ret=s->card.result!=2?2:1;}
        }else{v++;if(s->card.done)ret=s->card.result!=2?2:1;}
        break;
    case 4:if(s->card.done)ret=s->card.result!=2?2:1;break;
    }
    it_set(it,level,v);return ret;
}
static int flow_read(dw4_saveintf *s,int pl,int slot,int level)                                               /* 3ed650 */
{
    si_item *it=&s->item[pl];int v=*it_lv(it,level),ret=0;
    switch(v){
    case 0:if(card_begin(s,4,slot,pl,0))return -1;v++;break;
    case 1:
        if(s->card.done){
            ret=2;
            if(s->card.result==2){
                ret=1;
                if(s->nentries>=DW4_SI_PLAYERS)FAIL(s,"too many data entries");
                si_entry *e=&s->entry[s->nentries];memset(e,0,sizeof *e);e->slot=slot;e->allocated=1;
                dw4_si_summary areas[DW4_SI_SLOTS];memset(areas,0,sizeof areas);
                if(ok(s,s->h.card_read(s->h.user,slot,areas),"READ_MEDIA payload"))return -1;
                for(int i=0;i<DW4_SI_SLOTS;i++)e->area[i].s=areas[i];
                e->players[e->nplayers++]=pl;it->entry=s->nentries++;
            }
        }
        break;
    }
    it_set(it,level,v);return ret;
}
static int write_check(dw4_saveintf *s,int pl,int area)
{
    if(!s->card.done)return 0;
    if(s->card.result!=2)return 2;
    si_item *it=&s->item[pl];
    if(it->entry>=0&&area>=0&&area<DW4_SI_SLOTS)s->entry[it->entry].area[area]=s->display[pl];   /* 3ee490 */
    return 1;
}
static int flow_write(dw4_saveintf *s,int pl,int slot,int area,int level)                                      /* 3edc20 */
{
    si_item *it=&s->item[pl];int v=*it_lv(it,level),ret=0;
    switch(v){
    case 0:
        if(card_begin(s,5,slot,pl,area)||ok(s,s->h.timer_start(s->h.user,"SaveDataTime",3000000000LL),"timer"))return -1;
        v++;break;
    case 1:
        if(slot<s->card.nslots&&s->card.slots[slot].ok==1){
            if(s->h.timer_done(s->h.user,"SaveDataTime")==1){v++;ret=write_check(s,pl,area);}
        }else{v++;ret=write_check(s,pl,area);}
        break;
    case 2:ret=write_check(s,pl,area);break;
    }
    it_set(it,level,v);return ret;
}
static int flow_format(dw4_saveintf *s,int pl,int slot,int level)                                             /* 3edf60 */
{
    si_item *it=&s->item[pl];int v=*it_lv(it,level),ret=0;
    switch(v){
    case 0:if(card_begin(s,2,slot,pl,0))return -1;s->card.formatted_now=1;v++;break;
    case 1:if(s->card.done)ret=s->card.result!=2?2:1;break;
    }
    it_set(it,level,v);return ret;
}
/* 3ee250 (selected player enters state `st`; the others wait) and 3ee320 (drop a player from every entry's viewer list). */
static void item_enter(dw4_saveintf *s,int player,int st)
{
    for(int i=0;i<DW4_SI_PLAYERS;i++){
        si_item *t=&s->item[i];t->state=1;t->subsubsub=t->subsub=t->sub=0;t->pad_enabled=0;if(t->timer<=0)t->timer=0xA;
    }
    si_item *t=&s->item[player];t->state=st;t->subsubsub=t->subsub=t->sub=0;t->pad_enabled=1;t->timer=0;
    s->active_selector=player;   /* COMMONINTF +0x44 */
}

/* ---- vfunc_31, per player ---------------------------------------------------------------------------------- */
static int count_players(const dw4_saveintf *s,int *in_use,int *chosen)     /* the loops over FUN_002294f0(items) in states 7/8 */
{
    int a=0,b=0;for(int i=0;i<DW4_SI_PLAYERS;i++){if(s->item[i].in_use==1)a++;if(s->item[i].chosen==1)b++;}
    *in_use=a;*chosen=b;return a==b;
}
static int any_other_in_use(const dw4_saveintf *s)                          /* player 0 only: the others' items +0xC */
{
    for(int k=1;k<DW4_SI_PLAYERS;k++)if(s->item[k].in_use==1)return 1;
    return 0;
}
static void entry_leave(dw4_saveintf *s,int player)                          /* 3ee320: drop the player from every entry's viewer list */
{
    for(int e=s->nentries-1;e>=0;e--){
        si_entry *en=&s->entry[e];
        for(int k=0;k<en->nplayers;k++)if(en->players[k]==player){
            memmove(&en->players[k],&en->players[k+1],(size_t)(en->nplayers-k-1)*sizeof en->players[0]);en->nplayers--;break;
        }
    }
}
/* Item state 0: the control machine (CTRL +0x24 .. +0x30). Returns -1 on error; the caller stops the update either way
 * because every retail `return` ends this player's update. */
static int ctrl_body(dw4_saveintf *s,int pl,uint32_t edges)
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];
    si_select *sel=&s->select[pl];si_slots *sl=&s->slots[pl];si_panel *p0=&s->panel[pl][0];
    uint32_t base=(uint32_t)(pl<<16);
    switch(ct->state){
    case 0:
        if(ct->sub!=2){
            if(ct->sub!=1){
                if(cd_generate(s,c,pl,"j_chrselbase","SQ_OPEN",c->home,1))return -1;
                ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
            }
            if(cd_empty_a(c)){ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
            break;
        }
        if(s->h.player_in_use(s->h.user,pl)==1){
            if(ok(s,s->h.player_current_to_base(s->h.user,pl),"GAMERAM CURRENT2BASE"))return -1;
            if(ok(s,s->h.player_summary(s->h.user,pl,&s->display[pl].s),"player record"))return -1;
            ct_go(ct,1,0,0,0);it->chosen=0;it->in_use=1;return 0;
        }
        if(pl==0){
            if(ok(s,s->h.player_start_game(s->h.user,0,si_digimon[0].model),"GAMERAM GAMESTART"))return -1;
            if(ok(s,s->h.player_summary(s->h.user,0,&s->display[0].s),"player record"))return -1;
            return 0;
        }
        it->in_use=0;ct_go(ct,9,0,0,0);return 0;
    case 1:
        if(ct->sub==0){
            if(cd_generate(s,c,pl,"j_chrselmesswin","SQ_OPEN",c->home,1))return -1;
            mw_init(m);ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
        }
        if(ct->sub==1&&cd_empty_a(c)){mw_request_refresh(m);ct_go(ct,2,0,0,0);return 0;}
        break;
    case 2:
        if(ct->sub!=2){
            if(ct->sub!=1){mw_choice(m,(int)(base|0x502),0);ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
            if(!m->busy){
                if(m->choice==0){ct_go(ct,4,0,0,0);return 0;}
                if(m->choice==1){ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
            }
        }else if(ct->subsub==0){pn_open(p0,1,pl);ct->subsub++;ct->subsubsub=0;return 0;}
        else if(ct->subsub==1&&pn_update(s,p0)==1){
            if(pl==0&&any_other_in_use(s))ct_go(ct,8,0,0,0);else ct_go(ct,7,0,0,0);
            return 0;
        }
        break;
    case 4:
        if(ct->sub==0){
            if(ct->subsub==0){
                entry_leave(s,pl);sl_init(sl,s->mode);memset(sl->lvl,0,sizeof sl->lvl);ct->subsub++;ct->subsubsub=0;return 0;
            }
            if(ct->subsub==1&&sl_open(s,sl,-1)==1){
                mw_notice(m,(int)(base|0x1024));sl->lvl[0]=1;sl->lvl[3]=sl->lvl[2]=sl->lvl[1]=0;
                ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
            }
        }else if(ct->sub==1){
            if(ct->subsub==0){
                if(sl_update(s,sl,it->pad_enabled,1)==1){
                    if(sl->f37==1||sl->cancel==1){ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
                    ct->subsub++;ct->subsubsub=0;return 0;
                }
            }else if(ct->subsub==1){
                if(ct->subsubsub==0){
                    mw_notice(m,(int)(base|0x1004));item_enter(s,pl,4);ct->subsubsub++;return 0;
                }
                if(ct->subsubsub==1){
                    switch(it->result){
                    case 0:ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
                    case 1:case 2:case 4:
                        mw_notice(m,(int)(base|0x1024));if(sl_confirm(s,sl))return -1;ct->sub=1;ct->subsubsub=0;ct->subsub=0;return 0;
                    }
                }
            }
        }else if(ct->sub==2){
            if(ct->subsub==0){sl->lvl[0]=2;sl->lvl[3]=sl->lvl[2]=sl->lvl[1]=0;ct->subsub++;ct->subsubsub=0;return 0;}
            if(ct->subsub==1&&sl_close(s,sl)==1){
                if(sl->f37==1)ct_go(ct,4,0,0,0);else if(sl->cancel==1)ct_go(ct,2,0,0,0);else ct_go(ct,5,0,0,0);
                return 0;
            }
        }
        break;
    case 5:
        if(ct->sub==0){sel_init(sel,pl,1);ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
        if(ct->sub==1){
            if(ct->subsub==0){sel_reset(sel,0);ct->subsub++;ct->subsubsub=0;return 0;}
            if(ct->subsub==1&&sel_open(s,sel,0)==1){ct_go(ct,6,0,0,0);return 0;}
        }
        break;
    case 6:
        if(ct->sub==0){
            if(it->cancel==1){ct->sub=0x64;ct->subsubsub=0;ct->subsub=0;return 0;}
            switch(ct->subsub){
            case 0:sel_reset(sel,0);ct->subsub++;ct->subsubsub=0;return 0;
            case 1:
                if(sel_navigate(s,sel,0)==1){
                    if(sel->cancel!=0){ct->subsub++;ct->subsubsub=0;return 0;}
                    ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
                }
                break;
            case 2:sel_reset(sel,0);ct->subsub++;ct->subsubsub=0;return 0;
            case 3:if(sel_close(s,sel,0)==1){ct_go(ct,4,0,0,0);return 0;}break;
            }
        }else if(ct->sub==1){
            switch(ct->subsub){
            case 0:item_enter(s,pl,3);ct->subsub++;ct->subsubsub=0;return 0;
            case 1:
                switch(it->result){
                case 0:ct->flag17=1;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
                case 1:case 2:ct->subsub=0x32;ct->subsubsub=0;return 0;
                case 3:sl->f35=0;ct->sub=0;ct->subsubsub=0;ct->subsub=0;return 0;
                }
                break;
            case 0x32:sl->lvl[0]=2;sl->lvl[3]=sl->lvl[2]=sl->lvl[1]=0;ct->subsub++;ct->subsubsub=0;return 0;
            case 0x33:if(sl_close(s,sl)==1){ct->sub=0x64;ct->subsubsub=0;ct->subsub=0;return 0;}break;
            }
        }else if(ct->sub==2){
            if(it->cancel==1){ct->sub=0x64;ct->subsubsub=0;ct->subsub=0;return 0;}
            switch(ct->subsub){
            default:mw_continue(m,(int)(base|0x50B));ct->subsub++;ct->subsubsub=0;return 0;
            case 1:if(!m->busy){ct->subsub++;ct->subsubsub=0;return 0;}break;
            case 2:mw_choice(m,(int)(base|0x50D),0);ct->subsub++;ct->subsubsub=0;return 0;
            case 3:if(!m->busy){if(m->choice==0){ct->subsub=5;ct->subsubsub=0;return 0;}if(m->choice==1){ct->subsub=4;ct->subsubsub=0;return 0;}}break;
            case 4:
                if(ct->subsubsub==0){sel_reset(sel,0);ct->subsubsub++;return 0;}
                if(ct->subsubsub==1&&sel_area_opening(s,sel,0)==1){ct_go(ct,6,0,0,0);return 0;}
                break;
            case 5:
                if(ct->subsubsub==0){entry_leave(s,pl);sel_reset(sel,0);ct->subsubsub++;return 0;}
                if(ct->subsubsub==1&&sel_close_cursor(s,sel,0)==1){
                    if(pl==0&&any_other_in_use(s))ct_go(ct,8,0,0,0);else ct_go(ct,7,0,0,0);
                    return 0;
                }
                break;
            }
        }else if(ct->sub==0x64){
            if(ct->subsub==0){if(mw_close(s,m))return -1;sel_reset(sel,0);ct->subsub++;ct->subsubsub=0;return 0;}
            if(ct->subsub==1&&sel_close(s,sel,0)==1){ct_go(ct,4,0,0,0);return 0;}
        }
        break;
    case 7:
        if(ct->sub!=1){
            switch(ct->subsub){
            case 0:mw_continue(m,(int)(base|0x50E));ct->subsub++;ct->subsubsub=0;return 0;
            case 1:if(!m->busy){ct->subsub++;ct->subsubsub=0;return 0;}break;
            case 2:mw_choice(m,(int)(base|0x510),0);ct->subsub++;ct->subsubsub=0;return 0;
            case 3:if(!m->busy){if(m->choice==0){ct_go(ct,8,0,0,0);return 0;}if(m->choice==1){ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}}break;
            }
        }else{
            switch(ct->subsub){
            case 0:
                if(ct->flag17==1){ct->subsub=4;ct->subsubsub=0;return 0;}
                mw_continue(m,(int)(base|0x527));ct->subsub++;ct->subsubsub=0;return 0;
            case 1:if(!m->busy){ct->subsub++;ct->subsubsub=0;return 0;}break;
            case 2:mw_choice(m,(int)(base|0x529),1);ct->subsub++;ct->subsubsub=0;return 0;
            case 3:if(!m->busy){if(m->choice==0){ct->subsub=4;ct->subsubsub=0;return 0;}if(m->choice==1){ct->subsub=5;ct->subsubsub=0;return 0;}}break;
            case 4:
                if(ct->subsubsub==0){
                    pn_mark(p0,1);
                    if(cd_play_b(s,c,pl,"j_chrselmesswin","SQ_CLOSE",1))return -1;
                    mw_autoclose(m);ct->subsubsub++;return 0;
                }
                if(ct->subsubsub==1&&pn_update(s,p0)==1&&cd_empty_b(c)){
                    ct_go(ct,9,0,0,0);it->in_use=0;it->chosen=0;return 0;
                }
                break;
            case 5:
                if(ct->subsubsub==0){pn_mark(p0,0);ct->subsubsub++;return 0;}
                if(ct->subsubsub==1&&pn_update(s,p0)==1){ct_go(ct,2,0,0,0);return 0;}
                break;
            }
        }
        break;
    case 8:{
        int a,b,eq;
        switch(ct->sub){
        case 0:
            it->chosen=1;
            if(pl==0){
                eq=count_players(s,&a,&b);
                if(eq){mw_notice(m,(int)(base|0x51D));ct->sub=3;ct->subsubsub=0;ct->subsub=0;return 0;}
                mw_notice(m,(int)(base|0x530));ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
            }
            mw_notice(m,(int)(base|0x530));ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
        case 1:
            if(ct->subsubsub==0){
                if(pl==0){
                    eq=count_players(s,&a,&b);
                    if(eq){ct->sub=3;ct->subsubsub=0;ct->subsub=0;return 0;}
                    if(edges&0x2000){it->chosen=0;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
                }else{
                    eq=count_players(s,&a,&b);
                    if(eq){mw_notice(m,(int)(base|0x51F));ct->subsubsub++;return 0;}
                    if(edges&0x2000){it->chosen=0;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
                }
            }else if(ct->subsubsub==1){
                eq=count_players(s,&a,&b);
                if(!eq){mw_notice(m,(int)(base|0x530));ct->subsubsub=0;return 0;}
                if(edges&0x2000){it->chosen=0;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;}
            }
            break;
        case 2:
            if(ct->subsub==0){pn_mark(p0,2);ct->subsub++;ct->subsubsub=0;return 0;}
            if(ct->subsub==1&&pn_update(s,p0)==1){ct_go(ct,2,0,0,0);return 0;}
            break;
        case 3:
            if(ct->subsub==0){mw_notice(m,(int)(base|0x51D));ct->subsub++;ct->subsubsub=0;return 0;}
            if(ct->subsub==1){
                if(edges&0x2000){it->chosen=0;ct->sub=2;ct->subsubsub=0;ct->subsub=0;return 0;}
                eq=count_players(s,&a,&b);
                if(eq){
                    if(edges&8){
                        s->scene_state=3;
                        for(int i=0;i<DW4_SI_PLAYERS;i++)s->item[i].pad_enabled=0;
                        ct->subsub++;ct->subsubsub=0;return 0;
                    }
                }else{mw_notice(m,(int)(base|0x530));ct->sub=1;ct->subsubsub=0;ct->subsub=0;return 0;}
            }
            break;
        }
        break;}
    case 9:
        if(ct->sub==0){
            if(pl==0){
                mw_notice(m,(int)(base|0x51F));s->scene_state=3;
                for(int i=0;i<DW4_SI_PLAYERS;i++)s->item[i].pad_enabled=0;
            }
            ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
        }
        break;
    }
    return 0;
}
static int card_slot_ok(const dw4_saveintf *s,int slot){return slot>=0&&slot<s->card.nslots&&s->card.slots[slot].ok==1;}
static int notice_for_result(int code)                                       /* item state 6: the card-status notices */
{
    switch(code){case 7:return 0x1012;case 9:return 0x1014;case 10:return 0x1015;case 5:return 0x1010;case 6:return 0x1011;
        case 8:return 0x1013;case 12:return 0x1016;case 4:return 0x100F;default:return 0x100E;}
}
static si_entry *entry_new(dw4_saveintf *s,int slot,int pl)
{
    if(s->nentries>=DW4_SI_PLAYERS)return NULL;
    si_entry *e=&s->entry[s->nentries];memset(e,0,sizeof *e);e->slot=slot;e->allocated=1;e->players[e->nplayers++]=pl;
    s->item[pl].entry=s->nentries++;return e;
}
/* Item state 3: the chosen area's confirmation, the overwrite check and the WRITE (3edc20). */
static int item_state3(dw4_saveintf *s,int pl)
{
    si_item *it=&s->item[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];si_select *sel=&s->select[pl];si_slots *sl=&s->slots[pl];
    uint32_t base=(uint32_t)(pl<<16);
    switch(it->sub){
    case 0:
        if(it->subsub==0){sel_reset(sel,0);it->subsub++;it->subsubsub=0;return 0;}
        if(it->subsub==1&&sel_to_second(s,sel,0)==1){it->sub++;it->subsubsub=0;it->subsub=0;return 0;}
        break;
    case 1:
        switch(it->subsub){
        default:{
            if(it->cancel==1){it->sub=0x64;it->subsubsub=0;it->subsub=0;return 0;}
            si_display *a=area_of(s,pl,sel->cursor);NEED(s,a,"area");
            switch(it->subsubsub){
            case 0:mw_continue(m,(int)(base|(a->s.used==0?0x508:0x505)));it->subsubsub++;return 0;
            case 1:if(!m->busy){it->subsubsub++;return 0;}break;
            case 2:mw_choice(m,(int)(base|(a->s.used==1?0x50A:0x507)),0);it->subsubsub++;return 0;
            case 3:if(!m->busy){it->subsub++;it->subsubsub=0;return 0;}break;
            }
            break;}
        case 1:
            if(it->subsubsub==0){sel_reset(sel,0);it->subsubsub++;return 0;}
            if(it->subsubsub==1){
                if(m->choice==0){if(sel_close_both(s,sel,0)==1){it->subsub++;it->subsubsub=0;return 0;}}
                else if(sel_return_areas(s,sel,0)==1){it->subsub++;it->subsubsub=0;return 0;}
            }
            break;
        case 2:
            if(m->choice==0){it->sub++;it->subsubsub=0;it->subsub=0;mw_notice(m,(int)(base|0x100B));return 0;}
            if(m->choice==1){it->subsub++;it->subsubsub=0;return 0;}
            break;
        case 3:
            if(it->subsubsub==0){sel_reset(sel,0);it->subsubsub++;return 0;}
            if(it->subsubsub==1&&sel_area_opening(s,sel,0)==1){it_go(it,7,0,0,0);it->result=3;return 0;}
            break;
        }
        break;
    case 2:
        switch(it->subsub){
        case 0:
            if(it->subsubsub==0){sl_reset(sl);it->subsubsub++;return 0;}
            if(it->subsubsub==1){
                if(!card_slot_ok(s,sl->chosen_slot)){it->subsubsub++;return 0;}
                if(sl_open(s,sl,-1)==1){it->subsub++;it->subsubsub=0;return 0;}
            }else if(it->subsubsub==2&&sl_open(s,sl,-1)==1){s->card.result=0xC;it_go(it,6,0,0,0);return 0;}
            break;
        case 1:{
            int r=flow_check(s,pl,sl->chosen_slot,3);
            if(r==1){it->subsub++;it->subsubsub=0;return 0;}
            if(r==2){it_go(it,6,0,0,0);return 0;}
            break;}
        case 2:{
            int r=flow_write(s,pl,sl->chosen_slot,sel->cursor,3);
            if(r==1){it->sub++;it->subsubsub=0;it->subsub=0;return 0;}
            if(r==2){it_go(it,6,0,0,0);return 0;}
            break;}
        }
        break;
    case 3:
        if(it->subsubsub==0&&!card_slot_ok(s,sl->chosen_slot))it->subsubsub=1;
        switch(it->subsub){
        case 0:sl->lvl[0]=2;sl->lvl[3]=sl->lvl[2]=sl->lvl[1]=0;it->subsub++;it->subsubsub=0;return 0;
        case 1:if(sl_close(s,sl)==1){it->subsub++;it->subsubsub=0;return 0;}break;
        case 2:sel_reset(sel,0);it->subsub++;it->subsubsub=0;return 0;
        case 3:if(sel_reopen(s,sel,0)==1){it->subsub++;it->subsubsub=0;return 0;}break;
        case 4:sel_reset(sel,0);it->subsub++;it->subsubsub=0;return 0;
        case 5:
            if(sel_idle_areas(s,sel,0)==1){
                if(it->subsubsub==0){it_go(it,7,0,0,0);it->result=0;return 0;}
                it->sub++;it->subsubsub=0;it->subsub=0;return 0;
            }
            break;
        }
        break;
    case 4:
        if(it->subsubsub==0){mw_continue(m,(int)(base|0x50B));it->subsubsub++;return 0;}
        if(it->subsubsub==1&&!m->busy){it->sub=0x64;it->subsubsub=0;it->subsub=0;return 0;}
        break;
    case 0x64:
        if(it->subsub==0){if(mw_close(s,m))return -1;it->subsub++;it->subsubsub=0;sel_reset(sel,0);return 0;}
        if(it->subsub==1&&sel_close(s,sel,0)==1){it_go(it,7,0,0,0);it->result=2;return 0;}
        break;
    }
    (void)c;return s->error[0]?-1:0;
}
/* Item state 4: card access for the chosen slot (USE_CHECK/FILEFIND, format, FILEMAKE, READ_MEDIA). */
static int item_state4(dw4_saveintf *s,int pl)
{
    si_item *it=&s->item[pl];si_meswin *m=&s->mes[pl];si_slots *sl=&s->slots[pl];uint32_t base=(uint32_t)(pl<<16);
    int slot=sl->chosen_slot;
    switch(it->sub){
    case 0:{
        int r=flow_check(s,pl,slot,3);
        if(r==1){it_go(it,4,5,0,0);return 0;}
        if(r==2){
            switch(s->card.result){
            case 2:it->sub=5;break;
            case 3:case 4:it->sub=1;break;
            case 7:it->sub=3;break;
            case 12:it_go(it,6,0,0,0);return 0;
            default:it_go(it,6,0,0,0);return 0;
            }
            it->subsubsub=0;it->subsub=0;return 0;
        }
        break;}
    case 1:{
        if(!card_slot_ok(s,slot)){if(mw_close(s,m))return -1;it_go(it,7,0,0,0);it->result=2;return 0;}
        int r=flow_choice(s,pl,m,(int)(base|0x1000),(int)(base|0x1002),0,3);
        if(r==1){it->sub=2;it->subsubsub=0;it->subsub=0;return 0;}
        if(r==2){it_go(it,7,0,0,0);it->result=1;return 0;}
        break;}
    case 2:
        if(it->subsub==0){it->subsub++;it->subsubsub=0;return 0;}
        if(it->subsub==1){
            int r=flow_make(s,pl,m,slot,3);
            if(r==1){it->sub=5;it->subsubsub=0;it->subsub=0;}
            else if(r==2){
                if(s->card.result==7){it->sub=3;it->subsubsub=0;it->subsub=0;}
                else{it_go(it,6,0,0,0);it->result=1;}
            }
            if(r!=0)return 0;
        }
        break;
    case 3:{
        if(!card_slot_ok(s,slot)){if(mw_close(s,m))return -1;it_go(it,7,0,0,0);it->result=2;return 0;}
        int r=flow_choice(s,pl,m,(int)(base|0x1005),(int)(base|0x1007),1,3);
        if(r==1){it->sub=4;it->subsubsub=0;it->subsub=0;return 0;}
        if(r==2){it_go(it,7,0,0,0);it->result=1;return 0;}
        break;}
    case 4:
        if(it->subsub==0){mw_notice(m,(int)(base|0x1008));it->subsub++;it->subsubsub=0;return 0;}
        if(it->subsub==1){
            int r=flow_format(s,pl,slot,3);
            if(r==1){it->sub=1;it->subsubsub=0;it->subsub=0;}
            else if(r==2){it_go(it,6,0,0,0);it->result=2;}
            if(r!=0)return 0;
        }
        break;
    case 5:{
        int found=-1;
        for(int e=0;e<s->nentries;e++)if(s->entry[e].slot==slot){found=e;break;}
        if(found<0){if(s->card.present!=0){it->sub++;it->subsubsub=0;it->subsub=0;return 0;}}
        else{
            si_entry *en=&s->entry[found];
            if(en->nplayers>=DW4_SI_PLAYERS)FAIL(s,"entry viewer list is full");
            en->players[en->nplayers++]=pl;it->entry=found;it_go(it,7,0,0,0);it->result=0;return 0;
        }
        break;}
    case 6:{
        int r=flow_read(s,pl,slot,3);
        if(r==1){it_go(it,7,0,0,0);it->result=0;return 0;}
        if(r==2){
            switch(s->card.result){
            case 7:it->sub=3;it->subsubsub=0;it->subsub=0;return 0;
            case 9:case 10:it_go(it,6,0,0,0);it->result=1;return 0;
            case 8:it->sub++;it->subsubsub=0;it->subsub=0;return 0;
            default:it_go(it,6,0,0,0);it->result=1;return 0;
            }
        }
        break;}
    case 7:
        if(!card_slot_ok(s,slot)){if(mw_close(s,m))return -1;it_go(it,7,0,0,0);it->result=2;return 0;}
        switch(it->subsub){
        case 0:mw_continue(m,(int)(base|0x102B));it->subsub++;it->subsubsub=0;return 0;
        case 1:if(!m->busy){it->subsub++;it->subsubsub=0;return 0;}break;
        case 2:mw_continue(m,(int)(base|0x102C));it->subsub++;it->subsubsub=0;return 0;
        case 3:if(!m->busy){it->subsub++;it->subsubsub=0;return 0;}break;
        case 4:mw_choice(m,(int)(base|0x102D),0);it->subsub++;it->subsubsub=0;return 0;
        case 5:
            if(!m->busy){
                if(m->choice==0){it->subsub++;it->subsubsub=0;return 0;}
                if(m->choice==1){it->result=1;it_go(it,7,0,0,0);return 0;}
            }
            break;
        case 6:{
            si_entry *e=entry_new(s,slot,pl);if(!e)FAIL(s,"too many data entries");
            it->result=0;it_go(it,7,0,0,0);return 0;}
        }
        break;
    }
    return s->error[0]?-1:0;
}
/* The whole vfunc_31 for one player. */
static int player_update(dw4_saveintf *s,int pl)
{
    si_item *it=&s->item[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];si_panel *p0=&s->panel[pl][0];uint32_t held=0,edges=0,repeats=0;
    cd_prune(s,c);
    if(mw_update(s,m))return -1;
    if(it->pad_enabled==1){if(mw_pad(s,pl,&held,&edges,&repeats))return -1;}
    switch(it->state){
    case 1:{
        int done=0;
        if(it->sub==0){mw_text_only(m,(int)((pl<<16)|0x51C));it->sub=1;it->subsubsub=0;it->subsub=0;}
        else if(it->sub==1){if(--it->timer<=0){it->timer=0;done=1;}}
        if(done!=1)return ctrl_body(s,pl,edges);
        break;}
    case 0:return ctrl_body(s,pl,edges);
    case 2:
        switch(it->sub){
        case 0:
            if(s->ctrl[pl].state!=8){it->sub=1;it->subsubsub=0;it->subsub=0;}
            else{
                if(cd_play_b(s,c,pl,"j_chrselmesswin","SQ_CLOSE",1))return -1;
                mw_autoclose(m);pn_mark(p0,1);it->sub=2;it->subsubsub=0;it->subsub=0;
            }
            if(cd_play_b(s,c,pl,"j_chrselbase","SQ_CLOSE",1))return -1;
            return 0;
        case 1:if(cd_empty_b(c)){it->closed=1;it->sub=3;it->subsubsub=0;it->subsub=0;}break;
        case 2:if(pn_update(s,p0)==1&&cd_empty_b(c)){it->closed=1;it->sub=3;it->subsubsub=0;it->subsub=0;}break;
        }
        break;
    case 3:return item_state3(s,pl);
    case 4:return item_state4(s,pl);
    case 6:
        if(it->sub!=0)return 0;
        if(it->subsub==0){
            si_slots *sl=&s->slots[pl];int slot=sl->chosen_slot;int code=s->card.result;int id;
            if(s->card.formatted_now==1){if(sl_refresh(s,sl,code==12?slot:-1))return -1;id=0x100E;}
            else if(card_slot_ok(s,slot)){if(sl_refresh(s,sl,code==12?slot:-1))return -1;id=notice_for_result(code);}
            else{if(sl_refresh(s,sl,slot))return -1;id=0x1016;}
            mw_continue(m,(int)((pl<<16)|id));it->subsub++;it->subsubsub=0;return 0;
        }
        if(it->subsub==1&&!m->busy){it->result=1;it_go(it,7,0,0,0);return 0;}
        break;
    case 7:
        for(int i=0;i<DW4_SI_PLAYERS;i++)it_go(&s->item[i],8,0,0,0);
        return 0;
    case 8:
        mw_resume(m);it_go(it,0,0,0,0);it->pad_enabled=1;break;
    }
    return s->error[0]?-1:0;
}

/* ---- DIFFSELECT: the difficulty window (3ddb10 init, 3ddb80 update, recovered from the m2c draft) ----------------------
 * kind 0 is the two-row window j_linewin02 (Normal / Hard), kind 1 the three-row j_linewin03; hostLoad.lua's
 * LISsetDifficultMax (0 none, 1 two rows, 2 three rows) picks it. The result is the highlighted row. */
static void diff_init(si_diff *x,int kind,int player)                                      /* 3ddb10 */
{
    x->cursor=0;x->result=0;x->player=player;x->kind=kind;x->end=0;x->cancel=0;x->lvl=0;x->sub=0;x->max=kind==0?2:3;
}
static int diff_update(dw4_saveintf *s,si_diff *x,int pad_enabled)                         /* 3ddb80 (returns +0x24) */
{
    int pl=x->player;si_comdl *c=&s->comdl[pl];uint32_t base=(uint32_t)(pl<<16);
    if(x->end==1)return 1;
    uint32_t h=0,e=0,r=0;int up=0,down=0;
    if(pad_enabled==1){
        if(s->h.pad(s->h.user,pl,&h,&e,&r))FAIL(s,"pad is unavailable");
        up=(h&1)||((e|r)&0x10);down=(h&4)||((e|r)&0x40);
    }
    const char *win=x->kind==0?"j_linewin02":"j_linewin03";
    switch(x->lvl){
    case 0:
        if(x->sub==0){if(cd_generate(s,c,pl,win,"SQ_OPEN",c->home,1))return -1;x->sub++;}
        else if(x->sub==1&&cd_empty_a(c)){
            if(msg_show(s,base|(x->kind==0?0x402:0x403),0))return -1;
            mw_notice(&s->mes[pl],(int)(base|0x404));x->lvl++;x->sub=0;
        }
        break;
    case 1:
        if(x->sub==0){
            if(up){
                if(--x->cursor<0)x->cursor=0;
                else{
                    const char *seq=x->kind==0||x->cursor==0?"SQ_LINEUP00":"SQ_LINEUP01";
                    if(cd_play(s,c,pl,win,seq,1))return -1;
                    x->sub++;
                }
            }else if(down){
                if(++x->cursor>x->max-1)x->cursor=x->max-1;
                else{
                    const char *seq=x->kind==0||x->cursor==1?"SQ_LINEDW01":"SQ_LINEDW02";
                    if(cd_play(s,c,pl,win,seq,1))return -1;
                    x->sub++;
                }
            }else if(e&0x4000){x->result=x->cursor;x->lvl++;x->sub=0;}
            else if(e&0x2000){x->cancel=1;x->lvl++;x->sub=0;}
        }else if(x->sub==1&&cd_empty_a(c))x->sub=0;
        break;
    case 2:
        if(x->sub==0){
            if(msg_clear(s,base|(x->kind==0?0x402:0x403)))return -1;
            const char *seq=x->cancel?"SQ_CANCEL":x->cursor==0?"SQ_LINEON00":x->cursor==1?"SQ_LINEON01":"SQ_LINEON02";
            if(x->kind==0&&!x->cancel)seq=x->cursor==0?"SQ_LINEON00":"SQ_LINEON01";
            if(cd_play_b(s,c,pl,win,seq,1))return -1;
            x->sub++;
        }else if(x->sub==1&&cd_empty_b(c))x->end=1;
        break;
    }
    return x->end;
}

/* ---- LoadIntf2 (stagIS13): update 3e4750 (vfunc_31), receiver 3e9430 (vfunc_34) -------------------------------------
 * The same toolkit as SaveIntf. A player with data (hub mode: player 0) goes control 0 -> 8: the character panel opens,
 * the player is marked chosen, and START finishes the scene once every player in use has chosen. A player without data
 * waits for a pad (control 1), joins (2) and then chooses new or loaded data (3..7). The title runs player 0 through the
 * Create/Call window (3), Create's starter choice and name entry (4, 5) and Call's chooser and data select (6, 7), and both through
 * the commit and log-in prompt (8). A pad-owning joiner (players 1..3) is coded but unexercised: the host connects only player 0. */
/* ---- LoadIntf2 control states 6..8 (card chooser, data select, difficulty and the log-in prompt) -----------------------
 * Recovered from the behavioural reference recovered/frontend/loadintf2.c (3e4750, states 6, 7 and 8). The title's Call
 * Digimon reaches 6 from the Create/Call window (state 3); the toolkit helpers are the ones the Save Keeper runs. */
#define CT_SUB(k) do{ct->sub=(k);ct->subsub=0;ct->subsubsub=0;}while(0)
#define CT_ADV() do{ct->sub++;ct->subsub=0;ct->subsubsub=0;}while(0)
#define CT_NEXT() do{ct->subsub++;ct->subsubsub=0;}while(0)
static void display_blank(dw4_saveintf *s,int pl){memset(&s->display[pl],0,sizeof s->display[pl]);}   /* 3c6830 + 3e9160: an empty character display */
static int ld_card_notice(int code)                                        /* item state 6 (mode 0): the card-status notices */
{
    switch(code){case 4:case 7:return 0x1028;case 5:return 0x1010;case 6:return 0x1011;case 8:return 0x1013;case 9:return 0x1014;
        case 10:return 0x1015;case 12:return 0x1016;default:return 0x100D;}
}
static int ld_chooser(dw4_saveintf *s,int pl)                              /* control state 6 */
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_meswin *m=&s->mes[pl];si_slots *sl=&s->slots[pl];uint32_t base=(uint32_t)(pl<<16);
    switch(ct->sub){
    case 0:
        if(ct->subsub==1){
            if(sl_open(s,sl,-1)==1){sl->lvl[0]=1;sl->lvl[1]=sl->lvl[2]=sl->lvl[3]=0;CT_ADV();}
        }else if(ct->subsub==0){
            entry_leave(s,pl);sl_init(sl,s->mode);memset(sl->lvl,0,sizeof sl->lvl);
            mw_notice(m,(int)(base|0x1009));CT_NEXT();
        }
        break;
    case 1:
        if(ct->subsub==1){
            if(ct->subsubsub==1){
                switch(it->result){
                case 4:case 2:case 1:
                    mw_notice(m,(int)(base|0x1009));if(sl_confirm(s,sl))return -1;CT_SUB(1);break;
                case 0:CT_ADV();break;
                }
            }else if(ct->subsubsub==0){
                mw_notice(m,(int)(base|0x1004));item_enter(s,pl,5);ct->subsubsub++;
            }
        }else if(ct->subsub==0){
            if(sl_update(s,sl,it->pad_enabled,1)==1){
                if(sl->f37==1||sl->cancel==1)CT_ADV();else CT_NEXT();
            }
        }
        break;
    case 2:
        if(ct->subsub==1){
            if(sl_close(s,sl)==1){
                if(sl->f37==1)ct_go(ct,6,0,0,0);else if(sl->cancel==1)ct_go(ct,3,0,0,0);else ct_go(ct,7,0,0,0);
                mw_request_refresh(m);
            }
        }else if(ct->subsub==0){sl->lvl[0]=2;sl->lvl[1]=sl->lvl[2]=sl->lvl[3]=0;CT_NEXT();}
        break;
    }
    return 0;
}
static int ld_data_select(dw4_saveintf *s,int pl)                          /* control state 7: DATASELINTF in load mode */
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_select *sel=&s->select[pl];
    switch(ct->sub){
    case 100:
        if(ct->subsub==1){if(sel_close(s,sel,0)==1){display_blank(s,pl);ct_go(ct,6,0,0,0);}}
        else if(ct->subsub==0){sel_reset(sel,0);CT_NEXT();}
        break;
    case 2:
        if(sel->cancel==1)ct_go(ct,6,0,0,0);
        else{ct->f1c=0;ct_go(ct,8,0,0,0);}
        break;
    case 1:
        switch(ct->subsub){
        case 4:
            if(sel_close(s,sel,0)==1){if(ct->subsubsub==1)CT_SUB(100);else if(ct->subsubsub==0)CT_ADV();}
            break;
        case 3:
            if(it->cancel==1){sel_reset(sel,0);ct->subsub++;ct->subsubsub=1;}
            else if(sel_navigate(s,sel,0)==1){sel_reset(sel,0);ct->subsub++;ct->subsubsub=0;}
            break;
        case 2:sel_reset(sel,0);CT_NEXT();break;
        case 1:if(sel_open(s,sel,0)==1)CT_NEXT();break;
        case 0:sel_reset(sel,0);CT_NEXT();break;
        }
        break;
    case 0:sel_init(sel,pl,0);CT_ADV();break;
    }
    return s->error[0]?-1:0;
}
static int ld_commit(dw4_saveintf *s,int pl)                               /* state 8 sub 0: the data is taken (GAMEDATAINIT .. RECALCPLAYER) */
{
    si_item *it=&s->item[pl];si_select *sel=&s->select[pl];
    if(it->entry<0)FAIL(s,"LoadIntf2: the chosen data has no card entry");
    si_entry *e=&s->entry[it->entry];
    if(ok(s,s->h.player_data_init(s->h.user,pl),"GAMERAM GAMEDATAINIT"))return -1;
    s->display[pl]=e->area[sel->cursor];                                   /* 3e90f0 + 3e9160 */
    entry_leave(s,pl);
    if(ok(s,s->h.player_restore(s->h.user,pl,e->slot,sel->cursor),"loading the character (3ef5d0, BASE2CURRENT, RECALCPLAYER)"))return -1;
    s->title_card_slot=e->slot;s->title_area=sel->cursor;
    return 0;
}
/* ---- NAMESEL: the name entry (3de260 init, 3de480/3de7a0/3de990 texts, 3def80 update, 3def70 answer) ------------------------
 * Recovered from the m2c drafts of the five functions and the ELF tables: the key rows 4cc860 ({count; UCS-2 codes}, stride 0x44;
 * _langID 1 = USA uses rows 0..3: lower case, upper case, digits, symbols), the windows j_namewin01, j_namecursor01/02,
 * j_namecursorup/down/left/right and the cursor j_namecursorus, and the text sets CHRSELFONT10 (the three key-row heads),
 * CHRSELFONT11 (the five visible keys) and CHRSELFONT13 (the eight name cells). 3de260 always sets _langID 1. */
static int ns_key(const si_namesel *x){int n=si_key_rows[x->tate].count;return n>0?si_key_rows[x->tate].code[(x->yoko+x->cur)%n]:0;}
static void ns_init(si_namesel *x,int reset)                                     /* 3de260 */
{
    x->lang=1;x->max=8;x->tate_max=4;x->tate_min=0;
    if(reset==1){memset(x->cell,0,sizeof x->cell);memset(x->name,0,sizeof x->name);x->pos=-1;}
    if(x->pos==-1){x->saved[0][0]=x->saved[0][1]=x->saved[0][2]=0;x->pos=0;}
    x->tate=x->saved[x->pos][0];x->yoko=x->saved[x->pos][1];x->cur=x->saved[x->pos][2];x->cell[x->pos]=1;
    x->end=x->make_name=x->question=x->answer=x->name_ok=x->side=0;
    x->st0=0;x->st1=0;   /* retail capture: the keyboard reopens on a second name entry, so every entry starts from step 0 (the widget is built anew) */
}
static int ns_text(dw4_saveintf *s,const char *group,int player,int index,uint16_t code,int colour)
{uint16_t w[9]={code,0};return to_set(s,group,player,index,NULL,w,1,colour);}
static int ns_heads(dw4_saveintf *s,si_namesel *x,int clear)                    /* 3de480: the previous, current and next key row */
{
    for(int i=0;i<3;i++){
        if(clear){if(to_clear(s,"CHRSELFONT10",x->player,i))return -1;continue;}
        int row=x->tate+i-1;if(row<x->tate_min)row=x->tate_max-1;else if(row>=x->tate_max)row=x->tate_min;
        if(ns_text(s,"CHRSELFONT10",x->player,i,si_key_rows[row].code[0],0))return -1;
    }
    return 0;
}
static int ns_keys(dw4_saveintf *s,si_namesel *x,int clear)                     /* 3de7a0: the five visible keys */
{
    for(int i=0;i<5;i++){
        if(clear){if(to_clear(s,"CHRSELFONT11",x->player,i))return -1;continue;}
        int n=si_key_rows[x->tate].count;
        if(ns_text(s,"CHRSELFONT11",x->player,i,si_key_rows[x->tate].code[(x->yoko+i)%n],0))return -1;
    }
    return 0;
}
static int ns_cells(dw4_saveintf *s,si_namesel *x,int clear)                    /* 3de990 (_langID 1: CHRSELFONT13, eight cells) */
{
    int i=0;
    if(!clear)for(;i<8&&x->name[i];i++){
        if(x->cell[i]==1&&ns_text(s,"CHRSELFONT13",x->player,i,x->name[i],1))return -1;
        if(x->cell[i]==2&&ns_text(s,"CHRSELFONT13",x->player,i,x->name[i],0))return -1;
    }
    for(;i<8;i++)if(to_clear(s,"CHRSELFONT13",x->player,i))return -1;
    return 0;
}
static void ns_answer(si_namesel *x,int ok){x->name_ok=(uint8_t)ok;x->answer=1;}  /* 3def70 */
#define NS_GO(a,b) do{x->st0=(a);x->st1=(b);}while(0)
static int ns_update(dw4_saveintf *s,si_namesel *x,int pad_enabled)             /* 3def80 (returns _isEnd) */
{
    int pl=x->player;si_comdl *c=&s->comdl[pl];char seq[32];
    static const char *const cursor="j_namecursorus";                          /* _langID 1 (0 is j_namecursorjp) */
    if(x->end==1)return 1;
    uint32_t h=0,e=0,r=0;int up=0,down=0,left=0,right=0;
    if(pad_enabled==1){
        if(s->h.pad(s->h.user,pl,&h,&e,&r))FAIL(s,"pad is unavailable");
        up=(h&1)||((e|r)&0x10);down=(h&4)||((e|r)&0x40);left=(h&8)||((e|r)&0x80);right=(h&2)||((e|r)&0x20);
    }
#define SEQ(fmt,v) (snprintf(seq,sizeof seq,fmt,(v)),seq)
    switch(x->st0){
    case 0:
        switch(x->st1){
        case 0:{
            static const char *const open[]={"j_namecursor01","j_namecursor02","j_namewin01","j_namecursordown","j_namecursorup","j_namecursorleft","j_namecursorright"};
            if(cd_generate(s,c,pl,"j_digifacewin",si_digimon[x->sel&15].open,c->home,1))return -1;
            for(unsigned k=0;k<sizeof open/sizeof *open;k++)if(cd_generate(s,c,pl,open[k],"SQ_OPEN",c->home,1))return -1;
            x->side=1;x->name[x->pos]=(uint16_t)ns_key(x);
            if(cd_generate(s,c,pl,cursor,SEQ("SQ_NAMESL0%d",x->pos),c->home,0))return -1;
            if(ns_heads(s,x,0)||ns_keys(s,x,0)||ns_cells(s,x,0))return -1;
            x->st1++;break;}
        case 1:if(cd_empty_a(c))x->st1++;break;
        case 2:
            if(x->pos>=x->max)x->pos=x->max-1;
            if(cd_play(s,c,pl,"j_namecursor02",SEQ("SQ_SELECT0%d",x->cur),1))return -1;
            x->st1++;break;
        case 3:if(cd_empty_a(c))NS_GO(1,0);break;
        }
        break;
    case 1:
        switch(x->st1){
        case 0:{
            int n=si_key_rows[x->tate].count;
            if(right||left){
                int scroll=0;
                if(right){if(++x->cur>=5){x->cur=4;if(n>=6){scroll=1;if(++x->yoko>=n)x->yoko=0;}}else scroll=-1;}
                else{if(--x->cur<0){x->cur=0;if(n>=6){scroll=1;if(--x->yoko<0)x->yoko=n-1;}}else scroll=-1;}
                if(scroll==1){
                    if(x->side==1&&(cd_play(s,c,pl,right?"j_namecursorright":"j_namecursorleft","SQ_ON00",1)||
                                    cd_play(s,c,pl,cursor,SEQ("SQ_NAMECG0%d",x->pos),1)))return -1;
                    if(ns_keys(s,x,0))return -1;
                }else if(scroll==-1){
                    if(cd_play(s,c,pl,"j_namecursor02",SEQ("SQ_SELECT0%d",x->cur),1)||cd_play(s,c,pl,cursor,SEQ("SQ_NAMECG0%d",x->pos),1))return -1;
                }
                x->name[x->pos]=(uint16_t)ns_key(x);
                if(ns_cells(s,x,0))return -1;
                x->st1++;
            }else if(up||down){
                if(cd_play(s,c,pl,up?"j_namecursorup":"j_namecursordown","SQ_ON00",1)||cd_play(s,c,pl,cursor,SEQ("SQ_NAMECG0%d",x->pos),1))return -1;
                if(up){if(--x->tate<x->tate_min)x->tate=x->tate_max-1;}
                else if(++x->tate>=x->tate_max)x->tate=x->tate_min;
                const char *mark=si_key_rows[x->tate].count>=6?"SQ_SELECT00":"SQ_NOSELECT";
                if(cd_play(s,c,pl,"j_namecursorleft",mark,0)||cd_play(s,c,pl,"j_namecursorright",mark,0))return -1;
                x->side=si_key_rows[x->tate].count>=6;
                x->yoko=0;x->name[x->pos]=(uint16_t)ns_key(x);x->st1++;
                if(ns_cells(s,x,0)||ns_heads(s,x,0)||ns_keys(s,x,0))return -1;
            }else if(e&0x4000){
                if(x->pos<x->max){
                    x->saved[x->pos][0]=x->tate;x->saved[x->pos][1]=x->yoko;x->saved[x->pos][2]=x->cur;x->cell[x->pos]=2;
                    x->name[x->pos]=(uint16_t)ns_key(x);
                    if(cd_play(s,c,pl,cursor,SEQ("SQ_NAMEON0%d",x->pos),1))return -1;
                    x->pos++;x->name[x->pos+1]=0;x->cell[x->pos]=1;x->st1=3;
                }
                if(ns_cells(s,x,0))return -1;
            }else if(e&0x2000){
                x->name[x->pos]=0;x->pos--;
                if(cd_play(s,c,pl,cursor,"SQ_NAMECANCEL",1))return -1;
                if(x->pos<0){x->pos=-1;NS_GO(4,0);}
                else{
                    x->tate=x->saved[x->pos][0];x->yoko=x->saved[x->pos][1];x->cur=x->saved[x->pos][2];
                    x->name[x->pos]=(uint16_t)ns_key(x);
                    if(cd_play(s,c,pl,"j_namecursor02",SEQ("SQ_SELECT0%d",x->cur),1)||ns_keys(s,x,0)||ns_heads(s,x,0))return -1;
                    x->st1=2;
                }
                if(ns_cells(s,x,0))return -1;
            }else if(e&8){                                                     /* START: the name is complete */
                if(x->pos>0){
                    if(cd_play(s,c,pl,cursor,SEQ("SQ_NAMEON0%d",x->pos),1))return -1;
                    x->name[x->pos]=0;x->pos--;
                    if(ns_cells(s,x,0))return -1;
                    x->st1=4;
                }
            }
            break;}
        case 1:if(cd_empty_a(c))x->st1=0;break;
        case 2:
            if(cd_empty_a(c)){
                if(cd_play(s,c,pl,cursor,SEQ("SQ_NAMESL0%d",x->pos),0))return -1;
                x->cell[x->pos]=1;if(ns_cells(s,x,0))return -1;
                x->st1=0;
            }
            break;
        case 3:
            if(cd_empty_a(c)){
                if(x->pos>=x->max){x->pos=x->max-1;NS_GO(2,0);}
                else{
                    if(cd_play(s,c,pl,cursor,SEQ("SQ_NAMESL0%d",x->pos),0))return -1;
                    x->name[x->pos]=(uint16_t)ns_key(x);
                    if(ns_cells(s,x,0))return -1;
                }
                for(int k=x->pos+1;k<x->max;k++)x->name[k]=0;
                x->st1=0;
            }
            break;
        case 4:if(cd_empty_a(c))NS_GO(2,0);break;
        }
        break;
    case 2:
        if(x->st1==0){if(cd_play(s,c,pl,cursor,"SQ_LINESL00",1))return -1;x->st1++;}
        else if(x->st1==1&&cd_empty_b(c))NS_GO(3,0);
        break;
    case 3:
        switch(x->st1){
        case 0:x->question=1;x->answer=0;x->st1++;break;
        case 1:
            if(x->answer==1){
                x->question=0;
                if(x->name_ok==1){x->st1++;x->make_name=1;}
                else{x->make_name=0;x->st1=4;}
            }
            break;
        case 2:if(cd_play_b(s,c,pl,cursor,"SQ_LINEON00",1))return -1;x->st1++;break;
        case 3:if(cd_empty_b(c))NS_GO(5,0);break;
        case 4:
            x->tate=x->saved[x->pos][0];x->yoko=x->saved[x->pos][1];x->cur=x->saved[x->pos][2];x->cell[x->pos]=1;
            if(cd_play(s,c,pl,cursor,SEQ("SQ_NAMESL0%d",x->pos),0)||cd_play(s,c,pl,"j_namecursor02",SEQ("SQ_SELECT0%d",x->cur),1)||
               ns_keys(s,x,0)||ns_heads(s,x,0)||ns_cells(s,x,0))return -1;
            x->st1++;break;
        case 5:if(cd_empty_b(c))NS_GO(1,0);break;
        }
        break;
    case 4:
        if(x->st1==0){if(cd_play_b(s,c,pl,cursor,"SQ_CLOSE",1))return -1;x->st1++;}
        else if(x->st1==1&&cd_empty_b(c))NS_GO(5,0);
        break;
    case 5:
        if(x->st1==0){
            static const char *const close[]={"j_digifacewin","j_namewin01","j_namecursor01","j_namecursor02","j_namecursordown","j_namecursorup","j_namecursorleft","j_namecursorright"};
            if(ns_heads(s,x,1)||ns_keys(s,x,1)||ns_cells(s,x,1))return -1;
            for(unsigned k=0;k<sizeof close/sizeof *close;k++)if(cd_play_b(s,c,pl,close[k],"SQ_CLOSE",1))return -1;
            x->st1++;
        }else if(x->st1==1&&cd_empty_b(c))x->end=1;
        break;
    }
#undef SEQ
    return s->error[0]?-1:x->end;
}
#undef NS_GO

/* GAMESTART for a created character (state 8 sub 0, CTRL +0x1C): GAMEDATAINIT, GAMESTART with the starter's player model and the
 * typed name, GETPLAYER UNIQUE = the world clock's low word, and the record copied into the player's display (3ee6d0). */
static int ld_create(dw4_saveintf *s,int pl)
{
    si_namesel *x=&s->namesel[pl];uint16_t name[8]={0};
    for(int i=0;i<8&&x->name[i];i++)name[i]=x->name[i];
    if(!s->h.player_create||!s->h.world_ns)FAIL(s,"LoadIntf2: the host cannot create a character (GAMESTART)");
    int32_t unique=(int32_t)(uint32_t)(uint64_t)s->h.world_ns(s->h.user);
    if(ok(s,s->h.player_create(s->h.user,pl,si_digimon[s->makechr[pl].species&15].model,name,unique),"GAMERAM GAMEDATAINIT/GAMESTART"))return -1;
    if(ok(s,s->h.player_summary(s->h.user,pl,&s->display[pl].s),"player record"))return -1;
    s->title_card_slot=s->title_area=-1;
    return 0;
}
static int ld_all(const dw4_saveintf *s){int a,b;return count_players(s,&a,&b);}
static int ld_log_in(dw4_saveintf *s,int pl,uint32_t edges)                /* control state 8 */
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];si_panel *p0=&s->panel[pl][0];
    si_diff *df=&s->diff[pl];uint32_t base=(uint32_t)(pl<<16);
    switch(ct->sub){
    case 0:
        if(ct->subsub==1){
            if(pn_update(s,p0)==1){
                it->chosen=1;
                if(pl==0){if(ld_all(s))CT_SUB(3);else CT_SUB(1);}else CT_SUB(1);
            }
        }else if(ct->subsub==0){
            if(ct->subsubsub==1){
                if(diff_update(s,df,it->pad_enabled)==1){
                    if(df->cancel==1){display_blank(s,pl);it->chosen=0;ct_go(ct,6,0,0,0);}
                    else{s->title_difficulty=df->cursor;pn_open(p0,1,pl);CT_NEXT();}
                }
            }else if(ct->subsubsub==0){
                int kind=0,pick=0;
                if(ct->f1d==1){
                    if(ct->f1c==1){if(ld_create(s,pl))return -1;}
                    else if(ld_commit(s,pl))return -1;
                }
                if(pl==0&&ct->f1d==1){
                    int cap=s->h.difficulty_cap?s->h.difficulty_cap(s->h.user,pl):0;   /* hostLoad.lua: LISsetDifficultMax */
                    s->title_difficulty=0;
                    if(cap==2){pick=1;kind=1;}else if(cap==1){pick=1;kind=0;}
                }
                if(!pick){pn_open(p0,1,pl);CT_NEXT();}
                else{diff_init(df,kind,pl);ct->subsubsub++;}
            }
        }
        break;
    case 1:
        if(ct->subsub==1){
            if(ct->subsubsub==1){
                if(ld_all(s)){if((edges&0x2000)&&ct->f1d==1){it->chosen=0;CT_ADV();}}
            }else if(ct->subsubsub==0){
                if(pl==0){
                    if(ld_all(s))CT_SUB(3);
                    else if((edges&0x2000)&&ct->f1d==1){it->chosen=0;CT_ADV();}
                }else if(ld_all(s)){mw_notice(m,(int)(base|(ct->f1d==1?0x51F:0x522)));ct->subsubsub++;}
                else if((edges&0x2000)&&ct->f1d==1){it->chosen=0;CT_ADV();}
            }
        }else if(ct->subsub==0){mw_notice(m,(int)(base|(ct->f1d==1?0x530:0x52F)));CT_NEXT();}
        break;
    case 2:
        switch(ct->subsub){
        case 3:
            if(pn_update(s,p0)==1){
                if(ct->f1c==1){ct_go(ct,5,0,0,0);ns_init(&s->namesel[pl],0);}   /* back to the name entry, the typed name kept */
                else{display_blank(s,pl);ct_go(ct,6,0,0,0);}
            }
            break;
        case 2:pn_mark(p0,0);CT_NEXT();break;
        case 1:if(cd_empty_a(c))CT_NEXT();break;
        case 0:if(cd_play(s,c,pl,"j_mainstatuswin","SQ_CANCEL",1))return -1;CT_NEXT();break;
        }
        break;
    case 3:
        if(ct->subsub==0){mw_notice(m,(int)(base|(ct->f1d==1?0x51D:0x521)));CT_NEXT();}
        else if(ct->subsub==1){
            if((edges&0x2000)&&ct->f1d==1){it->chosen=0;CT_SUB(2);}
            else if(ld_all(s)){
                if(edges&8){                                              /* START */
                    s->scene_state=3;for(int i=0;i<DW4_SI_PLAYERS;i++)s->item[i].pad_enabled=0;
                    if(s->title)s->title_state=1;
                    CT_NEXT();
                }
            }else CT_SUB(1);
        }
        break;
    }
    return s->error[0]?-1:0;
}
/* Item states 5 and 6 of LoadIntf2: the card access flows behind the chooser (check, read, make, format) and the notice. */
static int ld_card_access(dw4_saveintf *s,int pl)                          /* item state 5 */
{
    si_item *it=&s->item[pl];si_meswin *m=&s->mes[pl];si_slots *sl=&s->slots[pl];uint32_t base=(uint32_t)(pl<<16);
    int slot=sl->chosen_slot;
    if(s->card.present!=1)return 0;
#define IT_SUB(k) do{it->sub=(k);it->subsub=0;it->subsubsub=0;}while(0)
    switch(it->sub){
    case 0:{
        int lv=flow_check(s,pl,slot,3);if(lv<0)return -1;
        if(lv==2){
            int code=s->card.result;
            if(code!=3&&code!=4){
                if(code==0xC){it_go(it,6,0,0,0);return 0;}
                if(code==7){if(s->mode==1){IT_SUB(3);return 0;}it_go(it,6,0,0,0);return 0;}
                if(code==2){IT_SUB(5);return 0;}
            }
            it_go(it,6,0,0,0);
        }else if(lv==1)IT_SUB(5);
        break;}
    case 1:
        if(card_slot_ok(s,slot)){
            int lv=flow_choice(s,pl,m,(int)(base|0x1000),(int)(base|0x1002),0,3);
            if(lv==2){it_go(it,7,0,0,0);it->result=1;}else if(lv==1)IT_SUB(2);
        }else{if(mw_close(s,m))return -1;it_go(it,7,0,0,0);it->result=2;}
        break;
    case 2:
        if(it->subsub==1){
            int lv=flow_make(s,pl,m,slot,3);if(lv<0)return -1;
            if(lv==2){
                switch(s->card.result){
                case 7:IT_SUB(3);break;
                default:it_go(it,6,0,0,0);it->result=1;break;
                }
            }else if(lv==1)IT_SUB(5);
        }else if(it->subsub==0){it->subsub++;it->subsubsub=0;}
        break;
    case 3:
        if(card_slot_ok(s,slot)){
            int lv=flow_choice(s,pl,m,(int)(base|0x1005),(int)(base|0x1007),1,3);
            if(lv==2){it_go(it,7,0,0,0);it->result=1;}else if(lv==1)IT_SUB(4);
        }else{if(mw_close(s,m))return -1;it_go(it,7,0,0,0);it->result=2;}
        break;
    case 4:
        if(it->subsub==1){
            int lv=flow_format(s,pl,slot,3);if(lv<0)return -1;
            if(lv==2){it->result=2;it_go(it,6,0,0,0);}
            else if(lv==1){it_go(it,7,0,0,0);it->result=4;}
        }else if(it->subsub==0){mw_notice(m,(int)(base|0x1008));it->subsub++;it->subsubsub=0;}
        break;
    case 5:{
        int found=-1;
        for(int e=0;e<s->nentries;e++)if(s->entry[e].slot==slot){found=e;break;}
        if(found<0)IT_SUB(6);
        else{
            si_entry *en=&s->entry[found];
            if(en->nplayers<DW4_SI_PLAYERS)en->players[en->nplayers++]=pl;
            it->entry=found;it_go(it,7,0,0,0);it->result=0;
        }
        break;}
    case 6:
        if(it->subsub==1){
            int lv=flow_read(s,pl,slot,3);if(lv<0)return -1;
            if(lv==2){
                switch(s->card.result){
                case 7:IT_SUB(3);break;
                default:it_go(it,6,0,0,0);it->result=1;break;
                }
            }else if(lv==1){it_go(it,7,0,0,0);it->result=0;}
        }else if(it->subsub==0){it->subsub++;it->subsubsub=0;}
        break;
    }
#undef IT_SUB
    return s->error[0]?-1:0;
}
static int ld_card_notice_state(dw4_saveintf *s,int pl)                    /* item state 6 */
{
    si_item *it=&s->item[pl];si_meswin *m=&s->mes[pl];si_slots *sl=&s->slots[pl];uint32_t base=(uint32_t)(pl<<16);
    if(it->sub!=0)return 0;
    if(it->subsub==0){
        int slot=sl->chosen_slot,code=s->card.result,id;
        if(s->card.formatted_now==1){if(sl_refresh(s,sl,code==12?slot:-1))return -1;id=0x100E;}
        else if(card_slot_ok(s,slot)){if(sl_refresh(s,sl,code==12?slot:-1))return -1;id=ld_card_notice(code);}
        else{if(sl_refresh(s,sl,slot))return -1;id=0x1016;}
        mw_continue(m,(int)(base|id));it->subsub++;it->subsubsub=0;
    }else if(it->subsub==1&&!m->busy){it->result=1;it_go(it,7,0,0,0);}
    return s->error[0]?-1:0;
}

/* Control state 3: the Create/Call window (j_chrselmesswin with the two-row j_linewin02, texts 0x401 and 0x523/0x524). Cross on
 * Create goes to state 4 (species), on Call to state 6 (the chooser). Circle closes the window only for players 1..3 (back to the
 * join prompt, sub 4); player 0 has no cancel here. */
static int ld_create_call(dw4_saveintf *s,int pl,uint32_t held,uint32_t edges,uint32_t repeats)
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];uint32_t base=(uint32_t)(pl<<16);
    int up=(held&1)||((edges|repeats)&0x10),down=(held&4)||((edges|repeats)&0x40);
    switch(ct->sub){
    case 0:
        if(ct->f15==0){
            if(cd_generate(s,c,pl,"j_chrselmesswin","SQ_OPEN",c->home,1))return -1;
            mw_init(m);ct->f15=1;
        }
        it->in_use=1;
        if(cd_generate(s,c,pl,"j_linewin02","SQ_OPEN",c->home,1))return -1;
        ct->f18=0;CT_ADV();
        break;
    case 1:
        if(ct->subsub==0){
            int open=s->h.model_is_sequence(s->h.user,"j_linewin02",pl,"SQ_OPEN");   /* 3e4210 */
            if(open<0)return ok(s,-1,"MODELCTRL j_linewin02 ISSEQNAME");
            if(open==0){
                if(msg_show(s,base|0x401,0))return -1;
                ct->subsub++;ct->subsubsub=0;
                mw_notice(m,(int)(pl==0?0x523:(base|0x524)));
            }
        }
        if(cd_empty_a(c))CT_ADV();
        break;
    case 2:
        if(ct->subsub==1){if(cd_empty_a(c)){ct->subsub=0;ct->subsubsub=0;}}
        else if(ct->subsub==0){
            if(up){
                int v=ct->f18-1;
                if(v<0)v=0;else if(cd_play(s,c,pl,"j_linewin02","SQ_LINEUP00",1))return -1;
                ct->f18=v;ct->subsub++;ct->subsubsub=0;
            }else if(down){
                int v=ct->f18+1;
                if(v<2){if(cd_play(s,c,pl,"j_linewin02","SQ_LINEDW01",1))return -1;}else v=1;
                ct->f18=v;ct->subsub++;ct->subsubsub=0;
            }else if(!(edges&0x4000)){
                if((edges&0x2000)&&pl!=0){
                    if(cd_play_b(s,c,pl,"j_linewin02","SQ_CANCEL",1)||cd_play_b(s,c,pl,"j_chrselmesswin","SQ_CLOSE",1))return -1;
                    if(msg_clear(s,base|0x401))return -1;
                    mw_autoclose(m);ct->sub+=2;ct->subsubsub=0;ct->subsub=0;
                }
            }else{
                if(cd_play(s,c,pl,"j_linewin02",ct->f18==0?"SQ_LINEON00":"SQ_LINEON01",1))return -1;
                CT_ADV();
            }
        }
        break;
    case 3:
        if(cd_empty_a(c)){
            if(msg_clear(s,base|0x401))return -1;
            ct_go(ct,ct->f18==0?4:6,0,0,0);
        }
        break;
    case 4:
        if(cd_empty_b(c)){it->in_use=0;ct->f12=0;ct_go(ct,2,0,0,0);ct->f15=0;}
        break;
    }
    return s->error[0]?-1:0;
}
/* Control state 4: the starter choice (MAKECHR _chaSelDegi, recovered/frontend/loadintf2.c case 4). The window set is
 * j_digiselcursorleft/right and the nameplate j_namewin02 (text CHRSELFONT14: DATABASE shinka NAME), the face window j_digifacewin
 * (SQ_<species>OPEN, then SQ_p_<species> on a change) and the 3D preview h_<species> (GENERATE, MOVETRANS to the origin, SQ_ENTR;
 * SQ_EXIT when it is replaced). Left/right cycle the four starters (wrapping); Cross goes on to the name entry (state 5), Circle
 * back to the Create/Call window (state 3). Message 0x511. */
static int ld_starter_name(dw4_saveintf *s,int pl)
{
    char name[64]="";int row=model_row(si_starter_model[s->makechr[pl].species&3]);
    if(ok(s,s->h.species_name(s->h.user,row,name,sizeof name),"DATABASE shinka NAME"))return -1;
    return to_set(s,"CHRSELFONT14",pl,0,name,NULL,1,0);
}
static int ld_preview_enter(dw4_saveintf *s,int pl)                        /* GENERATE + ISRUN, then MOVETRANS and SQ_ENTR (CTRL +0x17) */
{
    si_ctrl *ct=&s->ctrl[pl];const char *h=si_starter_preview[s->makechr[pl].species&3];
    if(ok(s,s->h.model_send(s->h.user,h,pl,"GENERATE",NULL),"MODELCTRL GENERATE"))return -1;
    int run=s->h.model_is_running(s->h.user,h,pl);if(run<0)return ok(s,-1,"MODELCTRL ISRUN");
    if(run==1){
        if(ok(s,s->h.model_send(s->h.user,h,pl,"MOVETRANS","V<0,0,0>/V<0,0,0>"),"MODELCTRL MOVETRANS")||
           ok(s,s->h.model_sequence(s->h.user,h,pl,"SQ_ENTR"),"MODELCTRL SQ_ENTR"))return -1;
        ct->flag17=0;
    }else ct->flag17=1;
    return 0;
}
static int ld_species(dw4_saveintf *s,int pl,uint32_t held,uint32_t edges,uint32_t repeats)
{
    si_ctrl *ct=&s->ctrl[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];si_makechr *mk=&s->makechr[pl];
    uint32_t base=(uint32_t)(pl<<16);
    int left=(held&8)||((edges|repeats)&0x80),right=(held&2)||((edges|repeats)&0x20);
    switch(ct->sub){
    case 0:
        if(cd_generate(s,c,pl,"j_digiselcursorleft","SQ_OPEN",c->home,1)||cd_generate(s,c,pl,"j_digiselcursorright","SQ_OPEN",c->home,1)||
           cd_generate(s,c,pl,"j_namewin02","SQ_OPEN",c->home,1))return -1;
        mk->species=3;
        mw_notice(m,(int)(base|0x511));
        if(ld_starter_name(s,pl))return -1;
        if(cd_generate(s,c,pl,"j_digifacewin",si_digimon[mk->species].open,c->home,1))return -1;
        if(ld_preview_enter(s,pl))return -1;
        CT_ADV();ct->f14=0;
        break;
    case 1:
        if(cd_empty_a(c)){if(cd_play(s,c,pl,"j_namewin02","SQ_LINESL00",0))return -1;CT_ADV();}
        break;
    case 2:
        if(ct->subsub==1){if(cd_empty_a(c)){ct->subsub=0;ct->subsubsub=0;}}
        else if(ct->subsub==0){
            const char *h=si_starter_preview[mk->species&3];
            if(right||left){
                if(ct->flag17==0){
                    int run=s->h.model_is_running(s->h.user,h,pl);if(run<0)return ok(s,-1,"MODELCTRL ISRUN");
                    if(run==1&&ok(s,s->h.model_sequence(s->h.user,h,pl,"SQ_EXIT"),"MODELCTRL SQ_EXIT"))return -1;
                }
                mk->species=right?(mk->species+1>3?0:mk->species+1):(mk->species-1<0?3:mk->species-1);
                if(ld_starter_name(s,pl))return -1;
                if(cd_play(s,c,pl,right?"j_digiselcursorright":"j_digiselcursorleft","SQ_ON00",1)||
                   cd_play(s,c,pl,"j_namewin02","SQ_LINECG00",0)||cd_play(s,c,pl,"j_digifacewin",si_digimon[mk->species].idle,0))return -1;
                ct->subsub++;ct->subsubsub=0;
            }else{
                int run=s->h.model_is_running(s->h.user,h,pl);if(run<0)return ok(s,-1,"MODELCTRL ISRUN");
                if(run==1){
                    if(edges&0x4000)CT_ADV();
                    else if(edges&0x2000){ct->f14=1;CT_ADV();}
                }else if(ld_preview_enter(s,pl))return -1;
            }
        }
        break;
    case 3:
        if(cd_play_b(s,c,pl,"j_namewin02",ct->f14==0?"SQ_LINEON00":"SQ_CANCEL",1))return -1;
        if(ct->flag17==0&&cd_play_b(s,c,pl,si_starter_preview[mk->species&3],"SQ_EXIT",1))return -1;
        if(to_clear(s,"CHRSELFONT14",pl,0))return -1;
        CT_ADV();break;
    case 4:if(cd_empty_b(c))CT_ADV();break;
    case 5:
        if(cd_play_b(s,c,pl,"j_digifacewin","SQ_CLOSE",1)||cd_play_b(s,c,pl,"j_digiselcursorleft","SQ_CLOSE",1)||
           cd_play_b(s,c,pl,"j_digiselcursorright","SQ_CLOSE",1))return -1;
        CT_ADV();break;
    case 6:
        if(cd_empty_b(c)){
            if(ct->f14==1)ct_go(ct,3,0,0,0);
            else{ct_go(ct,5,0,0,0);ns_init(&s->namesel[pl],1);}
        }
        break;
    }
    return s->error[0]?-1:0;
}
/* Control state 5: the name entry (NAMESEL, recovered/frontend/loadintf2.c case 5). Message 0x517 while typing; the finished name asks
 * 0x519 (continue) and 0x51B (Yes/No). Yes commits (CTRL +0x1C = 1, state 8: GAMESTART); No returns to typing; Circle out of the
 * first cell returns to the starter choice (state 4). Retail passes 3def70 a1 = 1 for Yes (the li at 3e66ec) and 0 for No. */
static int ld_name(dw4_saveintf *s,int pl)
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_meswin *m=&s->mes[pl];si_namesel *x=&s->namesel[pl];uint32_t base=(uint32_t)(pl<<16);
    switch(ct->sub){
    default:x->sel=s->makechr[pl].species;x->player=pl;CT_ADV();mw_notice(m,(int)(base|0x517));break;
    case 1:{
        int done=ns_update(s,x,it->pad_enabled);if(done<0)return -1;
        if(done==0){if(x->question==1)CT_ADV();}
        else if(x->make_name==1){ct->f1c=1;ct_go(ct,8,0,0,0);}
        else ct_go(ct,4,0,0,0);
        break;}
    case 2:mw_continue(m,(int)(base|0x519));CT_ADV();break;
    case 3:if(!m->busy)CT_ADV();break;
    case 4:mw_choice(m,(int)(base|0x51B),0);CT_ADV();break;
    case 5:
        if(!m->busy){
            if(m->choice==1){mw_notice(m,(int)(base|0x517));ns_answer(x,0);}
            else if(m->choice==0)ns_answer(x,1);
            CT_SUB(1);
        }
        break;
    }
    return s->error[0]?-1:0;
}
static int load_ctrl_body(dw4_saveintf *s,int pl,uint32_t held,uint32_t edges,uint32_t repeats)
{
    si_item *it=&s->item[pl];si_ctrl *ct=&s->ctrl[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];
    uint32_t base=(uint32_t)(pl<<16);
    switch(ct->state){
    case 0:
        switch(ct->sub){
        case 0:if(cd_generate(s,c,pl,"j_chrselbase","SQ_OPEN",c->home,1))return -1;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
        case 1:if(cd_empty_a(c)){ct->sub++;ct->subsubsub=0;ct->subsub=0;}return 0;
        case 2:
            if(s->h.player_in_use(s->h.user,pl)==1){
                if(ok(s,s->h.player_summary(s->h.user,pl,&s->display[pl].s),"player record"))return -1;
                ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
            }
            if(pl==0)ct_go(ct,3,0,0,0);
            else if(s->h.pad_connected(s->h.user,pl))ct_go(ct,2,0,0,0);
            else ct_go(ct,1,0,0,0);
            ct->f1d=1;return 0;
        case 3:
            if(cd_generate(s,c,pl,"j_chrselmesswin","SQ_OPEN",c->home,1))return -1;
            mw_init(m);it->in_use=1;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
        case 4:if(cd_empty_a(c)){ct->f1d=0;ct_go(ct,8,0,0,0);}return 0;
        }
        return 0;
    case 1:
        if(it->pad_enabled==1&&s->h.pad_connected(s->h.user,pl))ct_go(ct,2,0,0,0);
        return 0;
    case 2:
        switch(ct->sub){
        case 0:if(cd_generate(s,c,pl,"j_linewin01","SQ_OPEN",c->home,1))return -1;ct->sub++;ct->subsubsub=0;ct->subsub=0;return 0;
        case 1:if(cd_empty_a(c)){if(msg_show(s,base|0x400,0))return -1;ct->sub++;ct->subsubsub=0;ct->subsub=0;}return 0;
        case 2:{
            int go=0;
            if(it->pad_enabled==1){if(s->h.pad_connected(s->h.user,pl)){if(edges&0x4000){go=1;it->in_use=1;ct->f12=1;}}else go=1;}
            else go=1;
            if(go){
                if(cd_play_b(s,c,pl,"j_linewin01",ct->f12==1?"SQ_LINEON00":"SQ_CLOSE",1))return -1;
                if(msg_clear(s,base|0x400))return -1;
                ct->sub++;ct->subsubsub=0;ct->subsub=0;
            }
            return 0;}
        case 3:if(cd_empty_b(c)){if(ct->f12==1)ct_go(ct,3,0,0,0);else ct_go(ct,1,0,0,0);}return 0;
        }
        return 0;
    case 3:return ld_create_call(s,pl,held,edges,repeats);
    case 4:return ld_species(s,pl,held,edges,repeats);
    case 5:return ld_name(s,pl);
    case 6:return ld_chooser(s,pl);
    case 7:return ld_data_select(s,pl);
    case 8:return ld_log_in(s,pl,edges);
    }
    return 0;
}
static int load_player_update(dw4_saveintf *s,int pl)
{
    si_item *it=&s->item[pl];si_comdl *c=&s->comdl[pl];si_meswin *m=&s->mes[pl];si_panel *p0=&s->panel[pl][0];uint32_t held=0,edges=0,repeats=0;
    cd_prune(s,c);
    if(mw_update(s,m))return -1;
    if(it->pad_enabled==1){if(mw_pad(s,pl,&held,&edges,&repeats))return -1;}
    switch(it->state){
    case 1:{
        int done=0;
        if(it->sub==0){
            if(s->ctrl[pl].state==2){it->state=0;it->sub=it->subsub=it->subsubsub=0;}
            else{mw_text_only(m,(int)((pl<<16)|0x51C));it->sub=1;it->subsubsub=0;it->subsub=0;}
        }else if(it->sub==1){if(--it->timer<=0){it->timer=0;done=1;}}
        if(done!=1)return load_ctrl_body(s,pl,held,edges,repeats);
        break;}
    case 0:return load_ctrl_body(s,pl,held,edges,repeats);
    case 2:
        switch(it->sub){
        case 0:
            if(s->ctrl[pl].state!=8){it->sub=1;it->subsubsub=0;}
            else{
                if(cd_play_b(s,c,pl,"j_chrselmesswin","SQ_CLOSE",1))return -1;
                mw_autoclose(m);pn_mark(p0,1);it->sub=2;it->subsubsub=0;
            }
            it->subsub=0;
            if(cd_play_b(s,c,pl,"j_chrselbase","SQ_CLOSE",1))return -1;
            return 0;
        case 1:if(cd_empty_b(c)){it->closed=1;it->sub=3;it->subsubsub=0;it->subsub=0;}break;
        case 2:if(pn_update(s,p0)==1&&cd_empty_b(c)){it->closed=1;it->sub=3;it->subsubsub=0;it->subsub=0;}break;
        }
        break;
    case 5:return ld_card_access(s,pl);
    case 6:return ld_card_notice_state(s,pl);
    case 7:
        for(int i=0;i<DW4_SI_PLAYERS;i++)it_go(&s->item[i],8,0,0,0);
        return 0;
    case 8:
        mw_resume(m);it_go(it,0,0,0,0);it->pad_enabled=1;break;
    }
    return s->error[0]?-1:0;
}

/* ---- public API ---- */
dw4_saveintf *dw4_saveintf_open(const dw4_saveintf_host *h,int mode,const int joined[DW4_SI_PLAYERS])
{
    if(!h||mode!=0)return NULL;   /* modes 1/2 carry texts (0x2xxx/0x3xxx) the retail message table does not have; the shared load interface owns them */
    dw4_saveintf *s=calloc(1,sizeof *s);if(!s)return NULL;
    s->h=*h;s->mode=mode;
    for(int i=0;i<DW4_SI_PLAYERS;i++){
        s->joined[i]=joined?joined[i]:i==0;
        s->item[i].pad_enabled=(uint8_t)s->joined[i];s->item[i].entry=-1;s->item[i].state=0;
    }
    return s;
}
dw4_saveintf *dw4_loadintf_open(const dw4_saveintf_host *h,const int joined[DW4_SI_PLAYERS])
{
    dw4_saveintf *s=dw4_saveintf_open(h,0,joined);if(s)s->load=1;return s;
}
dw4_saveintf *dw4_loadintf_open_title(const dw4_saveintf_host *h)
{
    const int joined[DW4_SI_PLAYERS]={1,0,0,0};
    dw4_saveintf *s=dw4_loadintf_open(h,joined);if(s)s->title=1;return s;
}
int dw4_saveintf_title_ready(const dw4_saveintf *s)
{
    const si_ctrl *ct=&s->ctrl[0];
    return s->title&&ct->state==3&&ct->sub==2&&ct->subsub==0&&!s->mes[0].dirty;   /* the Create/Call window is open, its message shown, and takes the pad */
}
void dw4_saveintf_create_diagnostics(const dw4_saveintf *s,int p,dw4_saveintf_create_trace *t)
{
    const si_namesel *x=&s->namesel[p];memset(t,0,sizeof *t);
    t->species=s->makechr[p].species;memcpy(t->name,x->name,sizeof t->name);
    t->pos=x->pos;t->row=x->tate;t->first=x->yoko;t->column=x->cur;t->st0=x->st0;t->question=x->question;
}
int dw4_saveintf_title_state(const dw4_saveintf *s,int *card_slot,int *area,int *difficulty)
{
    if(card_slot)*card_slot=s->title_card_slot;
    if(area)*area=s->title_area;
    if(difficulty)*difficulty=s->title_difficulty;
    return s->title_state;
}
void dw4_saveintf_close(dw4_saveintf *s){free(s);}
const char *dw4_saveintf_error(const dw4_saveintf *s){return s->error;}
int dw4_saveintf_generate(dw4_saveintf *s)
{
    if(s->generated)return 0;
    for(int i=0;i<DW4_SI_PLAYERS;i++){
        memcpy(s->comdl[i].home,si_panel_position[i],sizeof s->comdl[i].home);
        s->mes[i].player=i;s->select[i].player=i;s->slots[i].player=i;
        s->panel[i][0]=(si_panel){.player=i,.side=0};s->panel[i][1]=(si_panel){.player=i,.side=1};
        s->ctrl[i]=(si_ctrl){0};
        if(s->load){s->ctrl[i].f12=(uint8_t)(i==0);s->ctrl[i].f13=1;}   /* 3e9430 GENERATE: CTRL +0x12 = player 0, +0x13 = 1 */
        diff_init(&s->diff[i],0,i);
        s->makechr[i]=(si_makechr){0};s->namesel[i]=(si_namesel){.player=i};
    }
    s->generated=1;return 0;
}
int dw4_saveintf_update(dw4_saveintf *s)
{
    if(!s->generated)return -1;
    if(s->error[0])return -1;
    if(card_update(s))return -1;
    for(int i=0;i<DW4_SI_PLAYERS;i++){   /* one instance per player slot: the four panels of the screen run even without a character */
        if(s->load?load_player_update(s,i):player_update(s,i)){if(!s->error[0])snprintf(s->error,sizeof s->error,"SaveIntf update failed for player %d",i);return -1;}
    }
    return 0;
}
int dw4_saveintf_scene_state(const dw4_saveintf *s){return s->scene_state;}
void dw4_saveintf_scan(dw4_saveintf *s)                                       /* 3ecc60 */
{
    card_update(s);
    for(int i=0;i<DW4_SI_PLAYERS;i++)s->item[i].cancel=0;
    for(int slot=0;slot<s->card.nslots;slot++)if(s->card.slots[slot].ok==0)
        for(int e=0;e<s->nentries;e++)if(s->entry[e].slot==slot)
            for(int k=0;k<s->entry[e].nplayers;k++)s->item[s->entry[e].players[k]].cancel=1;
}
void dw4_saveintf_close_players(dw4_saveintf *s){for(int i=0;i<DW4_SI_PLAYERS;i++){s->item[i].closed=0;it_go(&s->item[i],2,0,0,0);}}
int dw4_saveintf_player_closed(const dw4_saveintf *s,int p){return s->item[p].closed;}
int dw4_saveintf_player_done(const dw4_saveintf *s,int p){return s->item[p].chosen;}
int dw4_saveintf_select_data(dw4_saveintf *s)
{
    for(int i=0;i<DW4_SI_PLAYERS;i++)if(s->item[i].chosen!=1&&s->h.player_remove(s->h.user,i))return -1;
    return 0;
}
void dw4_saveintf_diagnostics(const dw4_saveintf *s,int p,dw4_saveintf_trace *t)
{
    t->state=s->item[p].state;t->sub=s->item[p].sub;t->subsub=s->item[p].subsub;t->subsubsub=s->item[p].subsubsub;
    t->control=s->ctrl[p].state;t->control_sub=s->ctrl[p].sub;t->control_subsub=s->ctrl[p].subsub;
}
