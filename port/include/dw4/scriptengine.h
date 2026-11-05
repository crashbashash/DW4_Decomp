#ifndef DW4_SCRIPTENGINE_H
#define DW4_SCRIPTENGINE_H
#include <stdio.h>
#include "dw4/script.h"
#include "dw4/modelcontact.h"
#include "dw4/frontend.h"
#include "dw4/scriptservices.h"
typedef struct dw4_scriptengine dw4_scriptengine;
struct dw4_filelist;
/* Borrowed retail CFL queue; detach before destroying the loader. */
void dw4_scriptengine_filelist(dw4_scriptengine *,struct dw4_filelist *);
/* In a live game scene, ordinary flags belong to the session's save records.
 * Route FLG reads/writes to the native binding; isolated fixtures default to
 * the existing scalar buffer. This retains no pointer into mutable records. */
void dw4_scriptengine_record_flags(dw4_scriptengine *,int enabled);
/* True only at an empty, quiescent startup boundary. */
int dw4_scriptengine_can_start(const dw4_scriptengine *);
/* Scalar snapshot for a synchronous model callback. No receiver pointer is
 * retained by Lua or DM. Owners commit hp only if it was not changed by a
 * native/reentrant handler during the call (retail 0x394400). */
typedef struct {
    int32_t ram_no, rec_no, hp, max_hp;
    const char *info_name, *call_name;
    int target_enabled;
    float target[3];
} dw4_script_model;
/* Retail window text helper 3f5920 publishes TXTgetCallNo (3747f0) and runs
 * the original named chunk synchronously. Last call number remains published,
 * including nested calls. Scoped teardown invalidates an active callback. */
int dw4_scriptengine_text_event(dw4_scriptengine *,uint64_t,const char *,int32_t);
int dw4_scriptengine_model_event(dw4_scriptengine *,uint64_t scope,
    const char *script,dw4_script_model *);
/* Hit callbacks add the real model matrix and shooter/bullet context. The
 * snapshot is isolated across nested callbacks and scoped cancellation. Only
 * successful live calls commit HP/target and the damage-turn decision. */
int dw4_scriptengine_has_script(const dw4_scriptengine *,const char *name);
int dw4_scriptengine_contact_event(dw4_scriptengine *,uint64_t,const char *,
    dw4_script_model *,dw4_model_contact *);
/* Scope of the current synchronous callback or DM group, for timed services. */
uint64_t dw4_scriptengine_scope(const dw4_scriptengine *);
/* Release scoped named chunks and cancel owned DM groups before releasing
 * stage/receiver state. Remove SD scopes separately. Safe in a
 * callback; an invalidated synchronous model call cannot commit its snapshot. */
void dw4_scriptengine_remove_scope(dw4_scriptengine *,uint64_t scope);
/* Services receive sd(category,name,id,key[,value,delay]) and
 * querySD(category,name,id,key[,value]). querySD returns numeric bytes for
 * waits, integer results for switches, and nil for missing results/receivers
 * (waits block; switches have no selected arm). DMgetCount queries SUBWND
 * ISRUN when no groups are published. Other native methods
 * pass through unchanged. Missing services fail the current operation. */
dw4_scriptengine *dw4_scriptengine_open(dw4_be_state *state,
    dw4_script_binding services, void *user);
void dw4_scriptengine_close(dw4_scriptengine *e);
dw4_script *dw4_scriptengine_vm(dw4_scriptengine *e);
/* Quiescent manager boundary: SD -> Lua infos/VM -> DM. Reject active Lua,
 * DM or SD callbacks before any mutation. Caller must defer to between ticks
 * and only then release model/controller owners. Native flags/RNG persist.
 * remove_all leaves no VM; reset_scene additionally opens a fresh one. */
int dw4_scriptengine_remove_all(dw4_scriptengine *,dw4_scriptservices *);
int dw4_scriptengine_reset_scene(dw4_scriptengine *,dw4_scriptservices *);
/* DM manager RemoveAll: while a tick is executing, latch the request and
 * preserve published/building groups until the pass unwinds (0x37f138).
 * Does not remove SD receivers or Lua globals. */
void dw4_scriptengine_dm_remove_all(dw4_scriptengine *);
/* Ordered retail startup milestones. Collect supporting/scene infos before
 * SHARED; collect remaining stage objects and bind layers before STAGE;
 * activate the system before FIRST. SHARED recreates the VM while retaining
 * infos. Script errors are recorded but do not gate retail phase advancement.
 * The regular run API retains the separate host fail-stop policy. */
typedef enum { DW4_SCRIPT_START_SHARED, DW4_SCRIPT_START_STAGE, DW4_SCRIPT_START_FIRST } dw4_script_start;
typedef struct { int func,boot,text,start,first; } dw4_script_start_status;
int dw4_scriptengine_startup(dw4_scriptengine *,dw4_script_start);
const dw4_script_start_status *dw4_scriptengine_start_status(const dw4_scriptengine *);
/* Run an engine event. Failures discard unpublished commands and stop this
 * engine until its owner closes/recreates it during Retry/Back. Globals and
 * already performed native side effects are not rolled back. */
int dw4_scriptengine_run(dw4_scriptengine *e, const char *name);
/* Publish a named engine event for the next DM tick (same as DMsetLua/DMrun).
 * Requires no unfinished Lua command group. */
int dw4_scriptengine_queue_event(dw4_scriptengine *e, const char *name);
/* Once per simulation tick, after clock sampling/message dispatch, before model actions, never from rendering.
 * Engine services own delayed SD actions and their recovered timer clocks.
 * A paused session simply does not call this function. */
int dw4_scriptengine_tick(dw4_scriptengine *e);
/* Developer aid: one line per running DM group with its current command. */
void dw4_scriptengine_describe(const dw4_scriptengine *,FILE *);
size_t dw4_scriptengine_pending(const dw4_scriptengine *e);
const char *dw4_scriptengine_error(const dw4_scriptengine *e);
#endif
