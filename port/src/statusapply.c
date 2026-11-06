#include "dw4/statusapply.h"
#include "arenalist.h"
#include <stdlib.h>
#include <string.h>

/* Status application on a model. Retail sources: 0x443bd0 beNDMWMdlPEBase::vfunc_46 per-frame
 * update; 0x445d10 beNDMWMdlPEBase::vfunc_47 SETxxx / CHECKSTATUS / CLEARxxx messages; 0x4456c0 /
 * 0x445990 lazy _downDataList / _upDataList; 0x445c60 player recalculation; 0x3a7a20 / 0x3a7e90 /
 * 0x3a8580 named timers. */

static const char *const names[11]={"POISON","ATTACKDOWN","POWERDOWN","BIND","REFRACT","SPEEDUP","POWERUP","METAL","SLEEP","STUN","RARE"};

void dw4_status_bind_movement(dw4_arena *arena,dw4_handle work)
{
    beNDMWMdlPEBaseInfoWork *w=DW4_ARENA_OBJ(arena,beNDMWMdlPEBaseInfoWork,work);
    if(!w || !w->_isOnCtrl || !al_words(arena,w->_timerList)[DW4_STATUS_BIND])return;
    /* 3c03e0 / 4ca940. GetValueByName writes the status separately from the
     * enum value: 4445d4 skips this loop on success, including SQ_SDMG=0. */
    static const char *const damage[]={"SQ_SDMG","SQ_MDMG","SQ_LDMG","SQ_DDMG","SQ_DEAD",
        "SQ_SDMGC","SQ_SDMGF","SQ_SDMGI","SQ_SDMGT","SQ_SDMGD"};
    const char *seq=al_text(arena,w->_seqCodeName);
    for(unsigned i=0;seq && i<sizeof damage/sizeof *damage;i++)if(!strcmp(seq,damage[i]))return;
    int count=al_count(arena,w->_moveObjectList);int32_t *rows=al_words(arena,w->_moveObjectList);
    for(int i=0;i<count;i++)if(i!=1){
        beModelCtrlMoveObject *m=DW4_ARENA_OBJ(arena,beModelCtrlMoveObject,al_handle(rows[i]));
        m->_isRun=0;m->_speed=0;
    }
}

const char *dw4_status_name(int s){return s>=0 && s<11?names[s]:NULL;}
int dw4_status_id(const char *name)
{
    if(!name)return -1;
    for(int i=0;i<11;i++)if(!strcmp(name,names[i]))return i;
    return -1;
}

void dw4_status_init(dw4_status *s,int is_player)
{
    memset(s,0,sizeof *s);
    s->is_player=is_player?1:0;s->ready=1;
    s->down_count=is_player?DW4_STATUS_DOWN_SLOTS:DW4_STATUS_DOWN_ENEMY;s->up_count=is_player?DW4_STATUS_UP_SLOTS:DW4_STATUS_UP_ENEMY;
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++)s->icon_position[i]=-1;
}
void dw4_status_load_lists(dw4_status *s,const int32_t down[DW4_STATUS_DOWN_SLOTS],const int32_t up[DW4_STATUS_UP_SLOTS])
{
    if(!s)return;
    if(down){memcpy(s->down,down,sizeof s->down);s->has_down=1;s->down_count=DW4_STATUS_DOWN_SLOTS;}
    if(up){memcpy(s->up,up,sizeof s->up);s->has_up=1;s->up_count=DW4_STATUS_UP_SLOTS;}
    s->lists_dirty=0;
}
void dw4_status_store_lists(dw4_status *s,int32_t down[DW4_STATUS_DOWN_SLOTS],int32_t up[DW4_STATUS_UP_SLOTS])
{
    if(!s)return;
    if(down)memcpy(down,s->down,sizeof s->down);
    if(up)memcpy(up,s->up,sizeof s->up);
    s->lists_dirty=0;
}

static void result_reset(dw4_status_tick_result *r){if(r)memset(r,0,sizeof *r);}

/* 3a7a20: arm (or re-arm) the named timer. start = the engine clock now. */
static void arm(dw4_status *s,int i,int64_t ns){s->named[i].armed=1;s->named[i].start_ns=s->clock_ns;s->named[i].duration_ns=ns;}
/* 3a7e90: true when the duration is strictly below the elapsed time, and for a timer that does not exist. */
static int expired(const dw4_status *s,int i){return !s->named[i].armed || s->named[i].duration_ns<s->clock_ns-s->named[i].start_ns;}
static void disarm(dw4_status *s,int i){s->named[i].armed=0;}
int dw4_status_timer_complete(int armed,int64_t start_ns,int64_t duration_ns,int64_t now_ns)
{return !armed || duration_ns<(((now_ns>>18)-(start_ns>>18))<<18);}
static int expired_q(const dw4_status *s,int i){return dw4_status_timer_complete(s->named[i].armed,s->named[i].start_ns,s->named[i].duration_ns,s->clock_ns);}
int dw4_status_cure_poison(dw4_status *s)
{
    if(!s || !s->timer[DW4_STATUS_POISON])return 0;
    s->timer[DW4_STATUS_POISON]=0;s->first[DW4_STATUS_POISON]=0;s->named[DW4_STATUS_POISON].armed=0;
    return 1;
}
/* value * 1e9 / 60 as the signed 64-bit divide 0x22e4b8 (truncating toward zero). */
static int64_t frames_ns(int32_t v){return (int64_t)v*1000000000LL/DW4_STATUS_FPS;}

static void ensure_down(dw4_status *s){s->has_down=1;}
static void ensure_up(dw4_status *s){s->has_up=1;}
static void put_down(dw4_status *s,int slot,int32_t v){if(slot<s->down_count && slot<DW4_STATUS_DOWN_SLOTS){if(s->down[slot]!=v)s->lists_dirty=1;s->down[slot]=v;}}
static void put_up(dw4_status *s,int slot,int32_t v){if(slot<s->up_count && slot<DW4_STATUS_UP_SLOTS){if(s->up[slot]!=v)s->lists_dirty=1;s->up[slot]=v;}}
static void recalc(dw4_status *s,dw4_status_tick_result *r){if(s->is_player && r)r->recalc_player=1;}

static void begin(dw4_status *s,int status,int32_t timer){s->first[status]=1;s->timer[status]=timer;}

int dw4_status_set_poison(dw4_status *s,int32_t frames,int32_t damage,int have_endurance,int32_t endurance)
{
    if(!s)return -1;
    /* 0x4466c8: timer = frames/120 + 1 (the 0x88888889 multiply, shift 6, plus the sign bit); isFirst = 1; damage and, with three
     * arguments, the endurance are stored in the work area. */
    s->timer[DW4_STATUS_POISON]=frames/120+1;s->first[DW4_STATUS_POISON]=1;
    s->poison_damage=damage;
    if(have_endurance)s->poison_endurance=endurance;
    return 0;
}
int dw4_status_set_sleep(dw4_status *s,int32_t frames){if(!s)return -1;begin(s,DW4_STATUS_SLEEP,frames);return 0;}   /* 0x446790 */
int dw4_status_set_stun(dw4_status *s,int32_t frames){if(!s)return -1;begin(s,DW4_STATUS_STUN,frames);return 0;}     /* 0x4467f8 */
int dw4_status_set_bind(dw4_status *s,int32_t frames){if(!s)return -1;begin(s,DW4_STATUS_BIND,frames);return 0;}     /* 0x446860 */
int dw4_status_set_attack_down(dw4_status *s,int32_t frames,int32_t sub,int32_t crit,int32_t para,int32_t eva)
{
    if(!s)return -1;
    begin(s,DW4_STATUS_ATTACKDOWN,frames);ensure_down(s);   /* 0x4468c8 */
    put_down(s,0,sub);put_down(s,1,crit);put_down(s,2,para);put_down(s,3,eva);
    return 0;
}
int dw4_status_set_power_down(dw4_status *s,int32_t frames,int32_t atk,int32_t def)
{
    if(!s)return -1;
    begin(s,DW4_STATUS_POWERDOWN,frames);ensure_down(s);    /* 0x446a40 */
    put_down(s,4,atk);put_down(s,5,def);
    return 0;
}
int dw4_status_set_speed_up(dw4_status *s,int32_t frames,int32_t a,int32_t b,int32_t c,int32_t d)
{
    if(!s)return -1;
    begin(s,DW4_STATUS_SPEEDUP,frames);ensure_up(s);        /* 0x446b48 */
    put_up(s,0,a);put_up(s,1,b);put_up(s,2,c);put_up(s,3,d);
    return 0;
}
int dw4_status_set_power_up(dw4_status *s,int32_t frames,int32_t a,int32_t b,int32_t c)
{
    if(!s)return -1;
    begin(s,DW4_STATUS_POWERUP,frames);ensure_up(s);        /* 0x446cc0 */
    put_up(s,4,a);put_up(s,5,b);put_up(s,6,c);
    return 0;
}
int dw4_status_set_refract(dw4_status *s,int32_t frames,int32_t a,int32_t b,int32_t c,int32_t d)
{
    if(!s)return -1;
    begin(s,DW4_STATUS_REFRACT,frames);ensure_up(s);        /* 0x446e00 */
    put_up(s,7,a);put_up(s,8,b);put_up(s,9,c);put_up(s,10,d);
    return 0;
}
int dw4_status_set_rare_icon(dw4_status *s,int32_t rank){if(!s)return -1;begin(s,DW4_STATUS_RARE,rank);return 0;}   /* 0x4470a0 */

int dw4_status_is_set(const dw4_status *s,int status){return s && status>=0 && status<DW4_STATUS_TIMER_SLOTS && s->timer[status]!=0;}
int dw4_status_check(const dw4_status *s,const char *name)
{
    int id=dw4_status_id(name);
    return id<0 || !s?-1:s->timer[id]!=0;   /* 0x447108: _timerList[id] != 0 */
}
int32_t dw4_status_down(const dw4_status *s,int slot){return s && s->has_down && slot>=0 && slot<s->down_count && slot<DW4_STATUS_DOWN_SLOTS?s->down[slot]:0;}
int32_t dw4_status_up(const dw4_status *s,int slot){return s && s->has_up && slot>=0 && slot<s->up_count && slot<DW4_STATUS_UP_SLOTS?s->up[slot]:0;}

static void clear_one(dw4_status *s,int status){disarm(s,status);s->first[status]=0;s->timer[status]=0;}

void dw4_status_clear_basic(dw4_status *s,dw4_status_tick_result *out)
{
    result_reset(out);if(!s)return;
    /* 0x447608: SLEEP, STUN, BIND timers deleted, flags and times cleared, then the model is sent to SQ_WAIT. */
    clear_one(s,DW4_STATUS_SLEEP);clear_one(s,DW4_STATUS_STUN);clear_one(s,DW4_STATUS_BIND);
    if(out){out->sequence="SQ_WAIT";out->expired|=1u<<DW4_STATUS_SLEEP|1u<<DW4_STATUS_STUN|1u<<DW4_STATUS_BIND;}
}
void dw4_status_clear_all(dw4_status *s,dw4_status_tick_result *out)
{
    result_reset(out);if(!s)return;
    /* 0x4471a8: POISON, ATKDOWN, POWDOWN, SPEEDUP, POWERUP, REFRACT cleared, both lists zeroed, player recalculation, then the CLEARSTATUS part. */
    static const int list[6]={DW4_STATUS_POISON,DW4_STATUS_ATTACKDOWN,DW4_STATUS_POWERDOWN,DW4_STATUS_SPEEDUP,DW4_STATUS_POWERUP,DW4_STATUS_REFRACT};
    uint32_t mask=0;
    for(int i=0;i<6;i++){clear_one(s,list[i]);mask|=1u<<list[i];}
    for(int i=0;i<DW4_STATUS_UP_SLOTS;i++)if(s->has_up && s->up[i])s->lists_dirty=1;
    for(int i=0;i<DW4_STATUS_DOWN_SLOTS;i++)if(s->has_down && s->down[i])s->lists_dirty=1;
    if(s->has_up)memset(s->up,0,sizeof s->up);
    if(s->has_down)memset(s->down,0,sizeof s->down);
    dw4_status_tick_result tail;dw4_status_clear_basic(s,&tail);
    if(out){*out=tail;out->expired|=mask;if(s->has_up||s->has_down)recalc(s,out);}
}

/* "I<n>/I<n>/..." -> values; returns the count or -1. */
static int parse_args(const char *a,int32_t *v,int max)
{
    int n=0;
    if(!a || !*a)return 0;
    while(*a){
        if(a[0]!='I' || a[1]!='<' || n>=max)return -1;
        char *end;long x=strtol(a+2,&end,10);
        if(end==a+2 || *end!='>')return -1;
        v[n++]=(int32_t)x;a=end+1;
        if(*a=='/')a++;else if(*a)return -1;
    }
    return n;
}

int dw4_status_message(dw4_status *s,const char *name,const char *args,dw4_status_tick_result *out)
{
    result_reset(out);
    if(!s || !name)return -1;
    int32_t v[8]={0};int n=parse_args(args,v,8);
    if(!strcmp(name,"CLEARSTATUS")){dw4_status_clear_basic(s,out);return 0;}
    if(!strcmp(name,"ALLCLEARSTATUS")){dw4_status_clear_all(s,out);return 0;}
    if(n<0)return -1;   /* the retail GetInt reads missing arguments as 0 (unverified); the port rejects a malformed string instead */
    if(!strcmp(name,"SETPOISON"))return dw4_status_set_poison(s,v[0],v[1],n==3,v[2]);
    if(!strcmp(name,"SETSLEEP"))return dw4_status_set_sleep(s,v[0]);
    if(!strcmp(name,"SETSTUN"))return dw4_status_set_stun(s,v[0]);
    if(!strcmp(name,"SETBIND"))return dw4_status_set_bind(s,v[0]);
    if(!strcmp(name,"SETRAREICON"))return dw4_status_set_rare_icon(s,v[0]);
    int rc;
    if(!strcmp(name,"SETATTACKDOWN"))rc=dw4_status_set_attack_down(s,v[0],v[1],v[2],v[3],v[4]);
    else if(!strcmp(name,"SETPOWERDOWN"))rc=dw4_status_set_power_down(s,v[0],v[1],v[2]);
    else if(!strcmp(name,"SETSPEEDUP"))rc=dw4_status_set_speed_up(s,v[0],v[1],v[2],v[3],v[4]);
    else if(!strcmp(name,"SETPOWERUP"))rc=dw4_status_set_power_up(s,v[0],v[1],v[2],v[3]);
    else if(!strcmp(name,"SETREFRACT"))rc=dw4_status_set_refract(s,v[0],v[1],v[2],v[3],v[4]);
    else return 1;
    recalc(s,out);   /* 0x445c60 after every stat-changing message */
    return rc;
}

int dw4_status_apply_down_slot(void *user,int slot,int32_t value)
{
    dw4_status *s=user;
    if(!s || slot<0)return -1;
    ensure_down(s);put_down(s,slot,value);return 0;
}

/* The KO branch shared by the tick (0x443cf8) and the sequence hook (0x445200): every timer is zeroed and every icon erased. */
static void ko_clear(dw4_status *s){for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++){s->timer[i]=0;s->icon_shown[i]=0;}}

void dw4_status_sequence_changed(dw4_status *s,const char *seq,int32_t hp,dw4_status_tick_result *out)
{
    result_reset(out);
    if(!s)return;
    if(!seq)seq="";
    if(hp==0){ko_clear(s);return;}
    if(s->timer[DW4_STATUS_SLEEP] && strcmp(seq,"SQ_SLEP")){   /* anything but the sleep sequence wakes the sleeper, damage included */
        clear_one(s,DW4_STATUS_SLEEP);s->icon_shown[DW4_STATUS_SLEEP]=0;if(out)out->expired|=1u<<DW4_STATUS_SLEEP;
    }else if(s->timer[DW4_STATUS_STUN]){
        if(!strcmp(seq,"SQ_WAIT")){if(out)out->sequence="SQ_STUN";}   /* the damage sequence's JUMP SQ_WAIT becomes the stun */
        else if(strcmp(seq,"SQ_STUN")){clear_one(s,DW4_STATUS_STUN);s->icon_shown[DW4_STATUS_STUN]=0;if(out)out->expired|=1u<<DW4_STATUS_STUN;}
    }
}

static void tick_icons(dw4_status *s)
{
    /* 0x444fc8..0x4451c8: statuses 0..7 get consecutive positions in the order of the enum; 8..11 keep none. */
    int pos=0,any=0;
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++){
        if(i==DW4_STATUS_FRAME)s->timer[i]=any;
        if(s->timer[i]){
            if(i<8){if(s->icon_position[i]!=pos)s->icon_position[i]=pos;pos++;any=1;}
            s->icon_shown[i]=1;
        }else s->icon_shown[i]=0;
    }
}

void dw4_status_tick(dw4_status *s,int64_t dt_ns,const char *seq,int32_t *hp,dw4_status_tick_result *out)
{
    dw4_status_tick_result local;
    if(!out)out=&local;
    result_reset(out);
    if(!s || !hp)return;
    if(dt_ns>0)s->clock_ns+=dt_ns;
    if(!seq)seq="";
    if(*hp==0){ko_clear(s);return;}   /* 0x443cf8: a KO'd model loses every timer and icon */
    if(!s->ready){tick_icons(s);return;}

    /* POISON, 0x443f10. */
    if(s->timer[DW4_STATUS_POISON]){
        if(s->first[DW4_STATUS_POISON]){arm(s,DW4_STATUS_POISON,DW4_STATUS_POISON_PERIOD_NS);s->timer[DW4_STATUS_POISON]--;s->first[DW4_STATUS_POISON]=0;}
        if(expired(s,DW4_STATUS_POISON)){
            int32_t h=*hp-s->poison_damage;if(h<0)h=0;
            out->poison_damage_taken=*hp-h;out->poison_ticks=1;*hp=h;
            if(h>0){
                s->timer[DW4_STATUS_POISON]--;
                if(s->timer[DW4_STATUS_POISON]>0)arm(s,DW4_STATUS_POISON,DW4_STATUS_POISON_PERIOD_NS);
                else{disarm(s,DW4_STATUS_POISON);s->timer[DW4_STATUS_POISON]=0;out->expired|=1u<<DW4_STATUS_POISON;}
            }else{
                if(s->is_player){out->sequence="SQ_DEAD";out->killed=1;}
                else{*hp=1;out->poison_damage_taken=out->poison_damage_taken-1;}   /* an enemy cannot die of poison: HP is set to 1 (0x444110) */
                disarm(s,DW4_STATUS_POISON);s->timer[DW4_STATUS_POISON]=0;out->expired|=1u<<DW4_STATUS_POISON;
            }
        }
    }
    /* SLEEP, 0x4441e8. */
    if(s->timer[DW4_STATUS_SLEEP]){
        if(s->first[DW4_STATUS_SLEEP]){
            arm(s,DW4_STATUS_SLEEP,frames_ns(s->timer[DW4_STATUS_SLEEP]));
            if(strcmp(seq,"SQ_SLEP"))out->sequence="SQ_SLEP";
            s->first[DW4_STATUS_SLEEP]=0;
        }
        if(expired(s,DW4_STATUS_SLEEP)){out->sequence="SQ_WAIT";disarm(s,DW4_STATUS_SLEEP);s->timer[DW4_STATUS_SLEEP]=0;out->expired|=1u<<DW4_STATUS_SLEEP;}
    }
    /* STUN, 0x444340: the whole block runs only while the current sequence is SQ_STUN. */
    if(s->timer[DW4_STATUS_STUN] && !strcmp(seq,"SQ_STUN")){
        if(s->first[DW4_STATUS_STUN]){arm(s,DW4_STATUS_STUN,frames_ns(s->timer[DW4_STATUS_STUN]));s->first[DW4_STATUS_STUN]=0;}
        if(expired(s,DW4_STATUS_STUN)){out->sequence="SQ_WAIT";disarm(s,DW4_STATUS_STUN);s->timer[DW4_STATUS_STUN]=0;out->expired|=1u<<DW4_STATUS_STUN;}
    }
    /* BIND, 0x444480. The owning model applies the movement-list gate after
     * control/AI, before movement; +0xc8 is not a HITBOX list. */
    if(s->timer[DW4_STATUS_BIND]){
        if(s->first[DW4_STATUS_BIND]){arm(s,DW4_STATUS_BIND,frames_ns(s->timer[DW4_STATUS_BIND]));s->first[DW4_STATUS_BIND]=0;}
        if(expired_q(s,DW4_STATUS_BIND)){out->sequence="SQ_WAIT";disarm(s,DW4_STATUS_BIND);s->timer[DW4_STATUS_BIND]=0;out->expired|=1u<<DW4_STATUS_BIND;}
    }
    /* ATKDOWN / POWDOWN / SPEEDUP / POWERUP / REFRACT: timed, and on expiry the slots they own are zeroed (0x444628 ... 0x444e20). */
    static const struct {int status,first_slot,count,up;} stat[5]={
        {DW4_STATUS_ATTACKDOWN,0,4,0},{DW4_STATUS_POWERDOWN,4,2,0},{DW4_STATUS_SPEEDUP,0,4,1},{DW4_STATUS_POWERUP,4,3,1},{DW4_STATUS_REFRACT,7,4,1}};
    for(int k=0;k<5;k++){
        int st=stat[k].status;
        if(!s->timer[st])continue;
        if(s->first[st]){arm(s,st,frames_ns(s->timer[st]));s->first[st]=0;}
        /* Speed / Power / Resist: the verified blocks (0x4448ac, 0x444af0, 0x444c70) test FUN_003a7e90, which quantises both clocks to 2^18 ns. */
        int done=st==DW4_STATUS_SPEEDUP || st==DW4_STATUS_POWERUP || st==DW4_STATUS_REFRACT?expired_q(s,st):expired(s,st);
        if(done){
            disarm(s,st);s->timer[st]=0;out->expired|=1u<<st;
            for(int j=0;j<stat[k].count;j++){if(stat[k].up)put_up(s,stat[k].first_slot+j,0);else put_down(s,stat[k].first_slot+j,0);}
            recalc(s,out);
        }
    }
    /* METAL (0x444e20) is not simulated: its re-arm interval comes from the player's ATTACKDELAY (unresolved). RARE never expires. */
    tick_icons(s);
}
