/* Scene-owned MODELCTRL instances from prepared native infos. */
#ifndef DW4_CONTROLLERS_H
#define DW4_CONTROLLERS_H
#include "dw4/modelctrl.h"
#include "dw4/stageobjects.h"
typedef struct dw4_controllers dw4_controllers;
/* Each authored RAM row supplies a distinct instance/selector slot. Excluded
 * names belong to specialized title/window owners; no duplicate callbacks.
 * The prepared owner and SD registry must outlive this owner. */
dw4_controllers *dw4_controllers_open(dw4_scriptservices *,uint64_t scope,
    const dw4_stageobjects *,const char *const *exclude,size_t nexclude,
    dw4_random *,uint32_t *rhythm,dw4_scriptengine *);
dw4_controllers *dw4_controllers_open_party(dw4_scriptservices *,uint64_t scope,
    const dw4_stageobjects *,const char *const *exclude,size_t nexclude,
    dw4_random *,uint32_t *rhythm,dw4_scriptengine *,const char *const *party,unsigned nparty);
void dw4_controllers_close(dw4_controllers *);
/* Borrowed event sink for decoded ACTION commands; specialized peers retain
 * their own sinks. Callback must not mutate/release the model owner. */
typedef void (*dw4_controllers_action)(void *,const char *model,const char *action);
void dw4_controllers_actions(dw4_controllers *,dw4_controllers_action,void *);
/* Sample before SD/DM, then update after DM at the model-manager boundary. */
void dw4_controllers_sample(dw4_controllers *,int64_t world_ns);
int dw4_controllers_tick(dw4_controllers *,int64_t world_ns);
/* HITPLAYERTALK dispatch (3993e0 CHKBULLET): every registered receiver, in accepted
 * info/RAM order, evaluates the probe against its own authored boxes. Returns the
 * number of accepted hits or -1 (see dw4_controllers_error). Not nearest-NPC selection. */
int dw4_controllers_talk(dw4_controllers *,const dw4_model_talk_probe *);
size_t dw4_controllers_talk_count(const dw4_controllers *);
const char *dw4_controllers_error(const dw4_controllers *);
size_t dw4_controllers_count(const dw4_controllers *);
/* Add a read-only presentation peer for a specialized owner already registered
 * in SD. It is never registered/ticked/closed here; its owner outlives us. */
int dw4_controllers_external(dw4_controllers *,const dw4_stageobjects *,const char *,int32_t,const dw4_modelctrl *);
/* Bind a specialized model to this scene's effect/sound/bone/track services.
 * It remains owned, registered, updated and drawn by its original owner; it is
 * not added to the presentation roster. Claims an unbound RAM identity and
 * exposes it to named attachment lookup. Duplicate identities/managers fail.
 * Either close order is supported: detach finishes dependent entries and
 * clears borrowed manager/info links before their resources are released. */
int dw4_controllers_bind_model(dw4_controllers *,const char *name,int32_t slot,dw4_modelctrl *);
/* Renderer boundary: state and native info are borrowed until close. */
const dw4_modelctrl *dw4_controllers_model(const dw4_controllers *,size_t,
    const dw4_stageobject **info,int32_t *slot);
/* KIND_OBJECT slots own persistent scalar callback state, bound to the supplied
 * scene engine/scope. Snapshots do not tick or consume RNG. Other kinds return
 * -1 until their gameplay record/health owners exist. Engine, registry and
 * prepared infos outlive this owner; cancel the scene before close. */
int dw4_controllers_model_state(const dw4_controllers *,size_t,dw4_script_model *);
/* Native health consumers write the same state seen by synchronous callbacks.
 * A reentrant HP change takes precedence over the Lua snapshot commit. */
int dw4_controllers_health(dw4_controllers *,size_t,int32_t hp,int32_t max_hp);
/* Bind collision only to the exact owned RAM identity; presentation peers are
 * immutable and cannot acquire a second updater. Consumer outlives binding. */
int dw4_controllers_collision(dw4_controllers *,const char *,int32_t,
    dw4_modelctrl_collision,void *);
/* Bind a borrowed live-target consumer to an exact owned NEAR RAM slot.
 * Detach before releasing the scene/player owner. External peers are rejected. */
/* The script-visible state (HP, row) of a script-bound receiver: objects and enemies. NULL for other models. */
dw4_script_model *dw4_controllers_state(dw4_controllers *,const char *name,int32_t slot);
/* Offer one bullet to every active enemy receiver (those registered under ENEMY) in receiver order. Returns the number of hits, or -1
 * with the controller error set. */
int dw4_controllers_enemy_bullet(dw4_controllers *,dw4_model_bullet *);
/* Number of active ENEMY receivers (all, or of one model name). */
size_t dw4_controllers_enemies_alive(const dw4_controllers *,const char *name);
int dw4_controllers_nearest(dw4_controllers *,const char *,int32_t,
    dw4_modelctrl_near,void *);
/* Send one MODELCTRL message straight to an owned instance (the native equivalent of a script
 * sd call, without the queue). Returns -1 when no such non-external instance exists. */
int dw4_controllers_send(dw4_controllers *,const char *name,int32_t slot,const char *method,
    const dw4_script_value *,size_t,dw4_script_value *,char *error,size_t cap);
/* The status work (ailment timers and stat lists) of an owned instance; NULL for models without one and for absent instances. */
const dw4_status *dw4_controllers_status(const dw4_controllers *,const char *name,int32_t slot);
/* 1 when the named owned instance exists and its model is active, 0 when inactive, -1 when absent. */
int dw4_controllers_live(const dw4_controllers *,const char *name,int32_t slot);
/* Borrowed mutable model owned here; external peers are managed by their owner. */
dw4_modelctrl *dw4_controllers_owned_model(dw4_controllers *,size_t index);
/* Prepared media owner outlives the controller closure; NULL disables media.
 * Unknown/unprepared clips fail explicitly. No device is opened here. */
struct dw4_frontaudio;
void dw4_controllers_audio(dw4_controllers *,struct dw4_frontaudio *);
/* Read-only simulation-pose lookup, shared with MOVERL. Returns 1 found,
 * 0 missing/inactive receiver or bone, -1 unsupported/failed pose decoding.
 * Copies local-bone * source-node; no controller clock or scene is advanced. */
int dw4_controllers_bone(dw4_controllers *,const char *model,int32_t slot,const char *bone,float world[16]);
#endif
