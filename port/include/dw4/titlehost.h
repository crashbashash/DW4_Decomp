/* Native boundary for the unchanged recovered title controller.
 * Common-model queues use the recovered reference. Model action execution
 * remains a bounded interpretation of the title packs; see docs/title-controller.md. */
#ifndef DW4_TITLEHOST_H
#define DW4_TITLEHOST_H
#include "title-menu.h"
#include "dw4/commdlhost.h"
#include "dw4/logoseq.h"
#include "dw4/action2host.h"
#include "dw4/clockhost.h"
#include "dw4/script.h"
enum { DW4_TITLE_MODELS = 8 };
typedef struct {
    int target, sequence, active, query_sequence, end_remove;
    int age, duration, joint_first, joint_last, loop;
    int fade_in, fade_out, fade_delay;
    int idle_age; /* menu idle timer; Options retained joint phase on no-JOINTSET actions */
} dw4_title_model;
typedef struct {
    Dw4TitleCtrl ctrl;
    Dw4TitleOption option;
    Dw4TitleApi api;
    dw4_commdl_host common_model;
    dw4_title_model model[DW4_TITLE_MODELS];
    dw4_logo_seq logo;
    dw4_logo_hooks logo_hooks;
    dw4_action2_host logo_action;
    int64_t clock_ns; /* Last sampled world time, mirrored for Action2 starts. */
    dw4_clock_host clock;
    unsigned text;
    int frame, handoff, next_stage, error;
    int msg_target, msg_node, msg_token, args[2], nargs, result;
    int camera, light;
    void (*sound_action)(void *, const char *, const char *);
    void *sound_user;
} dw4_title_host;
void dw4_title_host_close(dw4_title_host *);
void dw4_title_host_init(dw4_title_host *, int camera, int light);
/* Supplies raw nanoseconds, held until replaced. World time updates on the next
 * model tick; this setter does not sample or dispatch models. Default raw source
 * advances a provisional 16,666,667 ns per model tick. */
void dw4_title_host_set_clock(dw4_title_host *,int64_t raw_ns);
void dw4_title_host_tick(dw4_title_host *, const Dw4TitleInput *, int run);
/* Lua MODELCTRL uses the same sequence state as the recovered menu controller. */
int dw4_title_host_sequence(dw4_title_host *, int target, int sequence);
enum { DW4_TITLE_SQ_BLIN30 = -101, DW4_TITLE_SQ_WTIN60 = -102,
       DW4_TITLE_SQ_WAIT = -103 };
const dw4_title_model *dw4_title_host_model(const dw4_title_host *, int target);
long long dw4_title_model_time(const dw4_title_model *);
int dw4_title_model_alpha(const dw4_title_model *);
/* Canonical SD/querySD boundary, backed by these same eight model states. */
int dw4_title_host_script_service(void *,const char *,const dw4_script_value *,
    size_t,dw4_script_value *,char *,size_t);
#endif
