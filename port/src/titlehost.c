#include "dw4/titlehost.h"
#include <string.h>
#include <stdio.h>
#include "completion.h"

static dw4_title_model *model(dw4_title_host *h, int target)
{
    int i;
    for (i = 0; i < DW4_TITLE_MODELS; ++i)
        if (h->model[i].target == target) return &h->model[i];
    h->error = target;
    return NULL;
}
const dw4_title_model *dw4_title_host_model(const dw4_title_host *h, int target)
{
    int i;
    for (i = 0; i < DW4_TITLE_MODELS; ++i)
        if (h->model[i].target == target) return &h->model[i];
    return NULL;
}
/* Durations and joint ranges from AREA 620 / NDMW 806 action lists.
 * A tracked play completes when its requested sequence changes; a tracked
 * close waits until the model is removed, including its chained CLOSE. */
/* The first ACTION in each requested model sequence, from AREA 620 / NDMW 806.
 * beSeCtl's authored model/action table chooses the sound, independently of input. */
static void sound_action(dw4_title_host *h, int target, int seq)
{
    if (!h->sound_action) return;
    const char *name = target == T_j_startmenu01 ? "j_startmenu01" :
                       target == T_j_startmenu02 ? "j_startmenu02" :
                       target == T_j_optionwin02 ? "j_optionwin02" :
                       target == T_j_optioncursor11 ? "j_optioncursor11" :
                       target == T_j_optioncursor12 ? "j_optioncursor12" : NULL;
    const char *action = seq == T_SQ_MOVE ? "MOVE" : seq == T_SQ_CANCEL ? "CANCEL" :
                         seq == T_SQ_CLOSE ? "CLOSE" : seq == T_SQ_OPEN ? "OPEN" :
                         seq == T_SQ_AOPEN ? "OPEN00" : seq == T_SQ_BOPEN ? "OPEN01" :
                         seq == T_SQ_LINEUP00 ? "LINEUP00" : seq == T_SQ_LINEDW01 ? "LINEDW01" :
                         seq == T_SQ_LINEON00 ? "LINEON00" : seq == T_SQ_LINEON01 ? "LINEON01" :
                         seq == T_SQ_LINEON02 ? "LINEON02" : seq == T_SQ_LINEON03 ? "LINEON03" : NULL;
    /* Horizontal option sequences first execute ACTION MOVE, then their joint action. */
    if (target == T_j_optioncursor12 &&
        (seq == T_SQ_LINERT00 || seq == T_SQ_LINERT01 || seq == T_SQ_LINERT02 ||
         seq == T_SQ_LINELF00 || seq == T_SQ_LINELF01 || seq == T_SQ_LINELF02)) action = "MOVE";
    if (name && action) h->sound_action(h->sound_user, name, action);
}
static void schedule(dw4_title_host *h, int target, int seq)
{
    dw4_title_model *m = model(h, target);
    if (!m) return;
    dw4_title_model previous = *m;
    memset(m, 0, sizeof(*m));
    m->target = target; m->sequence = seq; m->active = 1;
    m->query_sequence = seq;
    if (target == T_j_startlogo) {
        if (seq != T_SQ_OPEN && seq != T_SQ_CLOSE) goto unsupported;
        dw4_logo_start(&h->logo,seq==T_SQ_OPEN ? LOGO_SQ_OPEN : LOGO_SQ_CLOSE,&h->logo_hooks);
        if(h->logo.error)h->error=h->logo.error;
    } else if (target == T_j_startmenu01 || target == T_j_startmenu02) {
        if (seq == T_SQ_OPEN) { m->duration = 15; m->joint_last = 15; m->fade_in = 1; }
        else if (seq == T_SQ_LINEDW01 || seq == T_SQ_LINEUP00) {
            m->duration = 20; m->joint_first = seq == T_SQ_LINEDW01 ? 50 : 80;
            m->joint_last = m->joint_first + 20;
        } else if (seq == T_SQ_LINEON00 || seq == T_SQ_LINEON01) {
            m->duration = 16; /* LINEON's 15-frame joint, then CLOSE's 1-frame wait. */
            m->joint_first = target == T_j_startmenu01 ? 50 : seq == T_SQ_LINEON00 ? 110 : 170;
            m->joint_last = m->joint_first + 15;
            m->fade_delay = 15; m->fade_out = 1; m->end_remove = 1;
        } else if (seq == T_SQ_CANCEL || seq == T_SQ_CLOSE) {
            m->duration = seq == T_SQ_CANCEL ? 6 : 1;
            m->joint_first = m->joint_last = 15;
            m->fade_delay = m->duration - 1; m->fade_out = 1; m->end_remove = 1;
        } else goto unsupported;
    } else if (target == T_j_optionwin02) {
        if (seq == T_SQ_AOPEN || seq == T_SQ_BOPEN) {
            m->duration = 15; m->fade_in = 15;
            m->joint_first = seq == T_SQ_AOPEN ? 40 : 160;
            m->joint_last = m->joint_first + 10; m->loop = 1;
        }
        else if (seq == T_SQ_CLOSE) {
            m->duration = 15; m->fade_out = 15; m->end_remove = 1;
            m->joint_first = previous.joint_first; m->joint_last = previous.joint_last;
            m->loop = previous.loop; m->idle_age = previous.age + previous.idle_age;
        }
        else goto unsupported;
    } else if (target == T_j_optioncursor11 || target == T_j_optioncursor12) {
        /* NDMW 806 Action2Info 2462/2425: animate the actual authored
         * joints, including LP idle ranges and OS directional feedback. */
        int outline = target == T_j_optioncursor11;
        int row = seq == T_SQ_LINESL01 || seq == T_SQ_LINEON01 ||
                  seq == T_SQ_LINERT01 || seq == T_SQ_LINELF01 ? 1 :
                  seq == T_SQ_LINESL02 || seq == T_SQ_LINEON02 ||
                  seq == T_SQ_LINERT02 || seq == T_SQ_LINELF02 ? 2 :
                  seq == T_SQ_LINESL03 || seq == T_SQ_LINEON03 ? 3 : 0;
        if (seq == T_SQ_OPEN) {
            m->duration = 15; m->joint_first = outline ? 360 : 140;
            m->joint_last = m->joint_first + 15;
            m->fade_in = outline ? 5 : 0;
        } else if (seq == T_SQ_MOVE || seq == T_SQ_CLOSE) {
            m->duration = seq == T_SQ_MOVE ? 10 : 0;
            m->end_remove = seq == T_SQ_CLOSE;
            /* MOVE has no JOINTSET: the old joint keeps playing. */
            m->joint_first = previous.joint_first; m->joint_last = previous.joint_last;
            m->loop = previous.loop; m->idle_age = previous.age + previous.idle_age;
        } else if (seq == T_SQ_LINEON00 || seq == T_SQ_LINEON01 || seq == T_SQ_LINEON02 || seq == T_SQ_LINEON03) {
            m->duration = 15; m->fade_delay = 5; m->fade_out = 10; m->end_remove = 1;
            m->joint_first = 380 + row * 20; m->joint_last = m->joint_first + 15;
        } else if (seq == T_SQ_LINERT00 || seq == T_SQ_LINERT01 || seq == T_SQ_LINERT02 ||
                   seq == T_SQ_LINELF00 || seq == T_SQ_LINELF01 || seq == T_SQ_LINELF02) {
            m->duration = 10;
            m->joint_first = row * 50 + (seq == T_SQ_LINERT00 || seq == T_SQ_LINERT01 || seq == T_SQ_LINERT02 ? 10 : 20);
            m->joint_last = m->joint_first + 10;
        } else if (seq == T_SQ_LINESL00 || seq == T_SQ_LINESL01 || seq == T_SQ_LINESL02 || seq == T_SQ_LINESL03) {
            m->duration = -1; m->loop = 1;
            m->joint_first = row * (outline ? 90 : 50);
            m->joint_last = m->joint_first + (outline ? 59 : 10);
        }
        else goto unsupported;
    } else if (target == T_j_startback && seq == T_SQ_OPEN) {
        m->duration = 209; m->joint_last = 209;
    } else if (target == T_j_startback && seq == DW4_TITLE_SQ_WAIT) {
        m->duration = -1; m->joint_first = 240; m->joint_last = 360; m->loop = 1;
    } else if (target == T_j_startback && seq == T_SQ_CLOSE) { m->duration = 60; m->end_remove = 1; }
    else if (target == T_i_fadewn01 && seq == DW4_TITLE_SQ_BLIN30) {
        m->duration = 30; m->fade_out = 30; m->end_remove = 1;
    } else if (target == T_i_fadewn01 && seq == DW4_TITLE_SQ_WTIN60) {
        m->duration = 60; m->fade_out = 60; m->end_remove = 1;
    }
    else if (target == T_i_fadewn01 && (seq == T_SQ_WTOUT60 || seq == T_SQ_BLOUT30)) {
        m->duration = seq == T_SQ_WTOUT60 ? 60 : 30; m->fade_in = m->duration;
    } else goto unsupported;
    sound_action(h, target, seq);
    return;
unsupported:
    h->error = seq ? seq : -4; /* Fail closed: an unknown operation must never report completion. */
}
/* Completion uses recovered Action2 and a supplied clock. Fade/joint rendering
 * still uses the native presentation path; FADESET remains an explicit leaf. */
static void logo_action(void *p,int action)
{
    dw4_title_host *h=p;
    dw4_title_model *m=model(h,T_j_startlogo);
    if(!m)return;
    dw4_action2_host_start(&h->logo_action,action,h->clock_ns);
    if(h->logo_action.error){h->error=h->logo_action.error;return;}
    m->age=0;m->duration=-1; /* Completion is never an age/duration comparison. */
    m->joint_first=action==LOGO_CLOSE ? h->logo_action.joint_last : h->logo_action.joint_first;
    m->joint_last=h->logo_action.joint_last;
    m->fade_in=h->logo_action.fade_in;m->fade_out=h->logo_action.fade_out;
}
static void update_models(void *p)
{
    dw4_title_host *h = p;
    int i;
    ++h->frame;
    h->clock_ns=(int64_t)dw4_clock_host_world(&h->clock);
    for (i = 0; i < DW4_TITLE_MODELS; ++i) {
        dw4_title_model *m = &h->model[i];
        if (!m->active) continue;
        ++m->age;
        if(m->target==T_j_startlogo) {
            int done=dw4_action2_host_tick(&h->logo_action,h->clock_ns);
            if(h->logo_action.error){h->error=h->logo_action.error;continue;}
            dw4_logo_tick(&h->logo,done,&h->logo_hooks);
            if(h->logo.error)h->error=h->logo.error;
            if(h->logo.removed)m->active=0;
            else if(h->logo.sequence==LOGO_SQ_WAIT)m->query_sequence=LOGO_SQ_WAIT;
            continue;
        }
        /* LINEON changes to CLOSE one frame before removal. A play wait
         * observes that change; a close wait still waits for ERAS. */
        if (m->end_remove &&
            (m->target == T_j_startmenu01 || m->target == T_j_startmenu02) &&
            (m->sequence == T_SQ_LINEON00 || m->sequence == T_SQ_LINEON01) &&
            m->age == 15) m->query_sequence = T_SQ_CLOSE;
        if (m->duration >= 0 && m->age >= m->duration) {
            if (m->end_remove) { m->active = 0; continue; }
            m->query_sequence = 0;
            if (m->target == T_j_startback) {
                m->sequence = m->query_sequence = DW4_TITLE_SQ_WAIT;
                m->joint_first = 240; m->joint_last = 360; m->loop = 1; m->age = 0;
            }
            if (m->target == T_j_startmenu01 || m->target == T_j_startmenu02) {
                m->sequence = m->sequence == T_SQ_LINEDW01 ? T_SQ_LINESL01 : T_SQ_LINESL00;
                m->joint_first = m->sequence == T_SQ_LINESL01 ? 140 : 20;
                m->joint_last = m->joint_first + 20;
                m->query_sequence = m->sequence;
                m->loop = 1; m->age = 0; m->idle_age = -1;
            }
            if (m->target == T_j_optionwin02 && !m->fade_out) {
                m->joint_first = m->sequence == T_SQ_AOPEN ? 50 : 170;
                m->joint_last = m->joint_first + 59; m->loop = 1; m->age = 0; m->fade_in = 0;
            } else if ((m->target == T_j_optioncursor11 || m->target == T_j_optioncursor12) &&
                       m->sequence != T_SQ_MOVE) {
                int row = m->sequence == T_SQ_LINERT01 || m->sequence == T_SQ_LINELF01 ? 1 :
                          m->sequence == T_SQ_LINERT02 || m->sequence == T_SQ_LINELF02 ? 2 : 0;
                m->joint_first = row * (m->target == T_j_optioncursor11 ? 90 : 50);
                m->joint_last = m->joint_first + (m->target == T_j_optioncursor11 ? 59 : 10);
                m->loop = 1; m->age = 0; m->fade_in = 0;
            }
            m->duration = -1;
        }
        if (m->target == T_j_startmenu01 && m->sequence == T_SQ_LINESL00 && ++m->idle_age >= 1800) {
            /* Asset SQ_LINESL00 -> SQ_TIMECLOSE: 30-frame wait then ERAS. */
            m->sequence = m->query_sequence = 0; m->age = 0; m->duration = 30;
            m->joint_first = 50; m->joint_last = 65; m->loop = 0; m->end_remove = 1;
        }
    }
}
static void advance_models(void *p)
{
    dw4_title_host *h=p;
    dw4_clock_host_step(&h->clock);
    if(h->clock.error)h->error=-10;
}
static void tick(void *p)
{
    dw4_title_host *h=p;
    advance_models(h);
    cm_poll(&h->common_model.api,DW4_CM_BASE);
    if(h->common_model.error) h->error=h->common_model.error;
}
static int opening(void *p)
{ dw4_title_host *h=p; return !h->error && !h->common_model.error && cm_open_empty(&h->common_model.api,DW4_CM_BASE); }
static int closing(void *p)
{ dw4_title_host *h=p; return !h->error && !h->common_model.error && cm_close_empty(&h->common_model.api,DW4_CM_BASE); }
static int exists(void *p, int slot, int target)
{ dw4_title_host *h=p; return cm_is_running(&h->common_model.api,DW4_CM_BASE,slot,target); }
static void start(void *p, int slot, int target, int seq, int wait)
{ dw4_title_host *h=p; cm_start(&h->common_model.api,DW4_CM_BASE,slot,target,seq,wait); }
static void play(void *p, int slot, int target, int seq, int wait)
{ dw4_title_host *h=p; cm_play(&h->common_model.api,DW4_CM_BASE,slot,target,seq,wait); }
static void close_model(void *p, int slot, int target, int seq, int wait)
{ dw4_title_host *h=p; cm_close(&h->common_model.api,DW4_CM_BASE,slot,target,seq,wait); }
static void show(void *p, int id, int flags)
{
    dw4_title_host *h = p; (void)flags;
    if (id == 0xf0002 || id == 0xf0003) h->text &= ~((1u<<2)|(1u<<3));
    if (id == 0xf0004 || id == 0xf0005) h->text &= ~((1u<<4)|(1u<<5));
    if (id >= 0xf0001 && id <= 0xf000d) h->text |= 1u << (id & 15);
    else h->error = id;
}
static void hide(void *p, int id)
{
    dw4_title_host *h = p;
    if (id == 0xf0002) h->text &= ~((1u<<2)|(1u<<3));
    else if (id == 0xf0005) h->text &= ~((1u<<4)|(1u<<5));
    else h->text &= ~(1u << (id & 15));
}
static void begin(void *p, int target, int node, int slot)
{
    dw4_title_host *h = p; (void)slot;
    h->msg_target = target; h->msg_node = node; h->nargs = 0; h->msg_token = 0;
}
static void target(void *p, int t) { begin(p, t, 0, 0); }
static void string(void *p, int t) { ((dw4_title_host *)p)->msg_token = t; }
static void integer(void *p, int v)
{ dw4_title_host *h = p; if (h->nargs < 2) h->args[h->nargs++] = v; else h->error = -1; }
static void end(void *p, int cmd)
{
    dw4_title_host *h = p;
    if (h->msg_target == T_MODELCTRL && cmd == T_ISSEQNAME) {
        dw4_title_model *m = model(h, h->msg_node);
        h->result = m && m->active && m->query_sequence == h->msg_token;
    } else if (h->msg_target == T_LOADCTRL2 && cmd == T_GENERATE_TITLE && h->nargs == 2) {
        h->camera = h->args[0]; h->light = h->args[1]; h->handoff = 1;
    } else if (h->msg_target == T_STAGECTL && cmd == T_NEXTSTAGE) h->next_stage = h->msg_token;
    else h->error = cmd;
}
static void send(void *p, int t, int node, int slot, int cmd)
{
    dw4_title_host *h = p; (void)slot;
    if (t != T_MODELCTRL) { h->error = cmd; return; }
    if (cmd == T_ISRUN) { dw4_title_model *m = model(h, node); h->result = m && m->active; }
    else if (cmd == T_GENERATE) { dw4_title_model *m = model(h, node); if (m) m->active = 1; }
    else schedule(h, node, cmd);
}
static int read_bool(void *p, int index) { (void)index; return ((dw4_title_host *)p)->result; }
/* The helper owns request queues; this boundary only supplies MODELCTRL
 * messages. Token addresses differ between callers but name the same strings. */
static int32_t cm_message(void *p,int32_t addr,const int32_t a[8])
{
    dw4_title_host *h=p;
    if ((addr==0x38d860 || addr==0x38e5f0) && (a[1]!=CM_MODELCTRL || (a[3]!=0 && a[3]!=-1))) {
        h->error=-9;return 0;
    }
    switch(addr) {
    case 0x38d860: begin(h,T_MODELCTRL,a[2],a[3]);break;
    case 0x38f830: string(h,a[1]);break;
    case 0x38e060: end(h,a[1]==CM_ISSEQNAME ? T_ISSEQNAME : a[1]);break;
    case 0x38e5f0: send(h,T_MODELCTRL,a[2],a[3],a[4]==CM_GENERATE ? T_GENERATE : a[4]==CM_ISRUN ? T_ISRUN : a[4]);break;
    case 0x38f220: return read_bool(h,a[1]);
    default:h->error=addr;
    }
    return 0;
}
/* The US initializer fixes _selLang=0 / _oldCountry=1. Fail on an unsupported
 * regional persistence/audio path rather than quietly simulating it. */
static void common(void *p, int t, int cmd) { (void)t; ((dw4_title_host *)p)->error = cmd; }
static int object(void *p, int index) { (void)index; ((dw4_title_host *)p)->error = -2; return 0; }
static void record(void *p, int obj, int f, int v) { (void)obj; (void)v; ((dw4_title_host *)p)->error = f; }
static void valid(void *p) { ((dw4_title_host *)p)->error = -3; }
void dw4_title_host_close(dw4_title_host *h)
{if(h)dw4_action2_host_close(&h->logo_action);}
void dw4_title_host_init(dw4_title_host *h, int camera, int light)
{
    static const int targets[] = { T_j_startlogo, T_j_startmenu01, T_j_startmenu02,
        T_j_optionwin02, T_j_optioncursor11, T_j_optioncursor12, T_j_startback, T_i_fadewn01 };
    int i;
    memset(h, 0, sizeof(*h));
    for (i = 0; i < DW4_TITLE_MODELS; ++i) h->model[i].target = targets[i];
    dw4_commdl_host_init(&h->common_model,h,cm_message);
    h->logo_hooks=(dw4_logo_hooks){h,logo_action,NULL};
    dw4_action2_host_init(&h->logo_action);
    dw4_clock_host_init(&h->clock,h,update_models);
    h->option._comConf = h->camera = camera;
    h->option._lightConf = h->light = light;
    h->api = (Dw4TitleApi){h, tick, opening, closing, exists, start, play, close_model,
        show, hide, begin, target, common, string, integer, end, send, read_bool, object, record, valid};
}
void dw4_title_host_set_clock(dw4_title_host *h,int64_t raw_ns)
{ dw4_clock_host_set_raw(&h->clock,(uint64_t)raw_ns); }
int dw4_title_host_sequence(dw4_title_host *h,int target,int sequence)
{ schedule(h,target,sequence); return h->error ? -1 : 0; }
void dw4_title_host_tick(dw4_title_host *h, const Dw4TitleInput *in, int run)
{
    if (h->common_model.error) h->error=h->common_model.error;
    if (!h->error) dw4_title_tick(&h->ctrl, &h->option, in, run, &h->api);
    h->camera = h->option._comConf; h->light = h->option._lightConf;
}
long long dw4_title_model_time(const dw4_title_model *m)
{
    int t = m->age, span = m->joint_last - m->joint_first;
    if (m->target == T_j_optionwin02 || m->target == T_j_optioncursor11 || m->target == T_j_optioncursor12)
        t += m->idle_age; /* retained joint phase when an action has no JOINTSET */
    if (m->loop && span > 0) t %= span;
    else if (t > span) t = span;
    return (long long)(m->joint_first + t) * 1000000000LL / 60;
}
int dw4_title_model_alpha(const dw4_title_model *m)
{
    if (!m->active) return 0;
    if (m->fade_out && m->age >= m->fade_delay) {
        int a = 128 - (m->age - m->fade_delay) * 128 / m->fade_out;
        return a < 0 ? 0 : a;
    }
    if (m->fade_in && m->age < m->fade_in) return m->age * 128 / m->fade_in;
    return 128;
}
static int named_token(const char *s,int is_model)
{
    static const struct {const char *name;int token;} names[]={
        {"j_startlogo",T_j_startlogo},{"j_startmenu01",T_j_startmenu01},
        {"j_startmenu02",T_j_startmenu02},{"j_optionwin02",T_j_optionwin02},
        {"j_optioncursor11",T_j_optioncursor11},{"j_optioncursor12",T_j_optioncursor12},
        {"j_startback",T_j_startback},{"i_fadewn01",T_i_fadewn01},
        {"SQ_OPEN",T_SQ_OPEN},{"SQ_CLOSE",T_SQ_CLOSE},{"SQ_WAIT",DW4_TITLE_SQ_WAIT},
        {"SQ_BLIN30",DW4_TITLE_SQ_BLIN30},{"SQ_WTIN60",DW4_TITLE_SQ_WTIN60},
        {"SQ_BLOUT30",T_SQ_BLOUT30},{"SQ_WTOUT60",T_SQ_WTOUT60},
        {"SQ_LINESL00",T_SQ_LINESL00},{"SQ_LINESL01",T_SQ_LINESL01},
        {"SQ_AOPEN",T_SQ_AOPEN},{"SQ_BOPEN",T_SQ_BOPEN},
        {"SQ_MOVE",T_SQ_MOVE},{"SQ_CANCEL",T_SQ_CANCEL},
        {"SQ_LINEUP00",T_SQ_LINEUP00},{"SQ_LINEDW01",T_SQ_LINEDW01},
        {"SQ_LINESL02",T_SQ_LINESL02},{"SQ_LINESL03",T_SQ_LINESL03},
        {"SQ_LINEON00",T_SQ_LINEON00},{"SQ_LINEON01",T_SQ_LINEON01},
        {"SQ_LINEON02",T_SQ_LINEON02},{"SQ_LINEON03",T_SQ_LINEON03},
        {"SQ_LINERT00",T_SQ_LINERT00},{"SQ_LINERT01",T_SQ_LINERT01},{"SQ_LINERT02",T_SQ_LINERT02},
        {"SQ_LINELF00",T_SQ_LINELF00},{"SQ_LINELF01",T_SQ_LINELF01},{"SQ_LINELF02",T_SQ_LINELF02}};
    unsigned first=is_model?0:8,last=is_model?8:sizeof(names)/sizeof(*names);
    for(unsigned i=first;i<last;i++)if(!strcmp(s,names[i].name))return names[i].token;
    return 0;
}
int dw4_title_host_script_service(void *user,const char *method,
    const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_title_host *h=user;
    if(n<4 || n>5 || a[1].type!=DW4_SCRIPT_STRING || a[3].type!=DW4_SCRIPT_STRING)
        goto unsupported;
    int target=named_token(a[1].string,1);
    const dw4_title_model *m=dw4_title_host_model(h,target);
    if(!m || (a[2].number!=0 && a[2].number!=-1))return 0;
    if(!strcmp(method,"querySD")) {
        if(n==4 && !strcmp(a[3].string,"ISRUN")) {
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,m->active,NULL,0};return 0;
        }
        if(n==5 && !strcmp(a[3].string,"ISSEQNAME") && a[4].type==DW4_SCRIPT_STRING) {
            int seq=named_token(a[4].string,0);
            if(target==T_j_startlogo && seq==DW4_TITLE_SQ_WAIT)seq=LOGO_SQ_WAIT;
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,m->active && seq && m->query_sequence==seq,NULL,0};
            return 0;
        }
    } else if(!strcmp(method,"sd")) {
        int seq=0;
        if(n==5 && !strcmp(a[3].string,"GENERATE") && a[4].type==DW4_SCRIPT_STRING)
            seq=named_token(a[4].string,0);
        else if(n==4)seq=named_token(a[3].string,0);
        if(seq && !dw4_title_host_sequence(h,target,seq))return 0;
    }
unsupported:
    snprintf(error,cap,"unsupported title MODELCTRL %s: %s",method,
             n>=4 && a[3].type==DW4_SCRIPT_STRING?a[3].string:"invalid arguments");
    return -1;
}
