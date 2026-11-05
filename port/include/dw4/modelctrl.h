#include <stdio.h>
/* Authored object-model sequence services. Rendering samples the Action2 clock. */
#ifndef DW4_MODELCTRL_H
#define DW4_MODELCTRL_H
#include "dw4/igb.h"
#include "dw4/arena.h"
#include "dw4/action2host.h"
#include "dw4/scriptengine.h"
#include "dw4/npcmotion.h"
#include "dw4/statusapply.h"
typedef struct {
    float position[3],rotation[3]; /* authored degrees; channel 3 is yaw */
    dw4_npc_motion channel[4]; /* local TX/TY/TZ and RY */
    const char *motion;
    int64_t motion_ns,motion_duration_ns;
    const char *previous_motion;int64_t previous_motion_ns,blend_ns;
    int motion_loop;
    int control,enabled,wall_check,floor_check,fall_check;
    uint32_t muteki;
} dw4_modelctrl_actor;

typedef struct dw4_modelctrl dw4_modelctrl;
typedef struct {dw4_arena *arena;dw4_handle ram,data,work,node;dw4_action2_record action;} dw4_modelctrl_record;
dw4_modelctrl_record dw4_modelctrl_records(const dw4_modelctrl *);
void dw4_modelctrl_health(dw4_modelctrl *,int32_t hp,int32_t maximum);
void dw4_modelctrl_bind_record(dw4_modelctrl *,int32_t slot,dw4_handle info,dw4_handle manager);
typedef struct {
    int32_t index; /* -1 before selection; index in this info's AIM list */
    const char *name;
    uint32_t bounds[3],rot_limit;
    float target[3];
    const char *sequence;
    int timer_present;int64_t timer_start,timer_duration;
} dw4_modelctrl_aim;
void dw4_modelctrl_aim_state(const dw4_modelctrl *,dw4_modelctrl_aim *);
/* True only when the first authored AIM map accepts a NEAR target owner. */
int dw4_modelctrl_has_near_map(const dw4_modelctrl *);
/* Actions longer than the Action2 host's component storage (DW4_A2_MAX_COMPONENTS) that the program skipped: zero in every retail pack. */
unsigned dw4_modelctrl_long_actions(const dw4_modelctrl *);
/* First authored HIT data: read-only minXYZ/maxXYZ rows. Return1 for a
 * nonzero _isHitPlayerTalk registration byte,0 otherwise. No geometry query
 * or callback is performed. Rows are shared with immutable instance programs. */
int dw4_modelctrl_talk_boxes(const dw4_modelctrl *,const float **,size_t *);
/* Immutable owning animation database, for asset preflight before publication. */
size_t dw4_modelctrl_motion_count(const dw4_modelctrl *);
const char *dw4_modelctrl_motion_name(const dw4_modelctrl *,size_t);
/* Explicit owner context, borrowed until detached/close. Bind only while not
 * dispatching. State supplies actual RAM/record/HP ownership. KIND_OBJECT
 * creation initializes zero-max HP to 100; other existing health is preserved.
 * Callback can send SD/sequence messages but must not release this owner.
 * WPOS AIMAP requires this binding; patrol choices share the engine RNG. */
void dw4_modelctrl_script(dw4_modelctrl *,dw4_scriptengine *,uint64_t scope,
    dw4_script_model *state);
typedef void (*dw4_modelctrl_trace)(void *,const char *sequence,const char *type,const char *name,int64_t ns);
/* Diagnostic observer is read-only; it must not mutate or release the owner. */
void dw4_modelctrl_observe(dw4_modelctrl *,dw4_modelctrl_trace,void *);
void dw4_modelctrl_actor_state(const dw4_modelctrl *,dw4_modelctrl_actor *);
/* Shared native actor matrix used by world rendering and hit callbacks. */
void dw4_modelctrl_actor_matrix(const dw4_modelctrl_actor *,float world[16]);
/* Current authoritative node matrix; copying it does not advance pose/clock state. */
void dw4_modelctrl_matrix(const dw4_modelctrl *,float world[16]);
/* Player-only HITPLAYERTALK/CHKBULLET consumer (kind60000). Returns0 for a
 * miss/ineligible target,1 for an intersecting callback,-1 on error. This does
 * not register receivers, create probes, or advance simulation. */
/* A combat bullet (a HITBOX volume of an attacker) offered to a receiver. group: whose bullets (the receiver's _isHitPlayerBullet /
 * _isHitEnemyBullet flag must match). Gates mirror the talk consumer (active, control on, not invulnerable) and are not measured for
 * combat. Returns 1 when the receiver's hit_<name>.lua ran, 0 when nothing was hit, -1 on error. */
typedef enum {DW4_BULLET_PLAYER,DW4_BULLET_ENEMY} dw4_bullet_group;
typedef struct {
    float source_world[16],box[6];
    int32_t kind,shoot_ram_no,source_row;   /* source_row: the shooting enemy's stat-table row (E2P rules) */
    dw4_bullet_group group;
    int64_t world_ns;
    const char *name;
    const dw4_model_fight *fight;
    const dw4_status *source_status;   /* the shooter's status (its _downDataList feeds the E2P rules); NULL for none */
} dw4_model_bullet;
/* Held pad buttons (PS2 mask, Cross 0x4000) for the player's attack-chain waits. */
void dw4_modelctrl_player_pad(dw4_modelctrl *,uint32_t held);
int dw4_modelctrl_bullet_hit(dw4_modelctrl *,const float world[16],const dw4_model_bullet *);
int dw4_modelctrl_talk_hit(dw4_modelctrl *,const float world[16],const dw4_model_talk_probe *);
/* Borrowed collision consumer at the post-movement/pre-completion boundary.
 * Adjust position; player consumers may additionally publish support through
 * player_floor. Channels, rotation and control gates remain owned here.
 * No callback runs for inactive/frozen instances or from snapshot/render calls. */
/* Moves `position` out of the stage collision and returns the contact mask of dw4_lobby_collision_check (bit 0: pushed out of a wall). */
/* The floor argument of the collision callback: 0 off, 1 a walking floor, DW4_COLLIDE_AIR a floor that only catches a model coming down (a model whose vertical
 * channel rises or falls: an enemy's knockback hop or SQ_FALL). An enemy's query also carries DW4_COLLIDE_FALLS: no floor edge holds it, the callback reports
 * bit 2 for a walking model with nothing under it and bit 4 for a falling one that reached a floor, and the model publishes that support itself
 * (HITFLOORCHECK, the same boundary the player's owner publishes through dw4_modelctrl_player_floor). */
#define DW4_COLLIDE_AIR 2
#define DW4_COLLIDE_FALLS 4
typedef unsigned (*dw4_modelctrl_collision)(void *,const float old[3],float position[3],int wall,int floor,const float land[4]);   /* land: the model's delivery half width, up and down range and check flag */
void dw4_modelctrl_collide(dw4_modelctrl *,dw4_modelctrl_collision,void *);
/* Player collision owner publishes HITFLOORCHECK's support/landing boundary.
 * The model consumes it after waits, following 3926d0's post-update response. */
void dw4_modelctrl_player_floor(dw4_modelctrl *,int supported,int landed);
/* Prepared NEAR map zero queries the scene's live player owner at AI expiry. */
typedef int (*dw4_modelctrl_near)(void *,const float position[3],float target[3]);
int dw4_modelctrl_nearest(dw4_modelctrl *,dw4_modelctrl_near,void *);
/* Native owner supplies the decoded walking gate and camera-relative yaw.
 * Only KIND_PLAYER consumes this boundary; frozen/disabled work retains pose. */
int dw4_modelctrl_player_input(dw4_modelctrl *,int walking,float yaw_radians);
/* Weapon label selects the authored section in each sequence, without ticking. */
int dw4_modelctrl_label(dw4_modelctrl *,const char *sequence,const char *label);
int dw4_modelctrl_has_sequence(const dw4_modelctrl *,const char *sequence);
int dw4_modelctrl_label_copy(dw4_modelctrl *,const char *from,const char *to);
/* Owns decoded programs; strings/bytes borrow the immutable mounted pack.
 * Supports ACTION, WCHECK Action (player TurnY/Landing), JUMP, LABEL/LABELCTRL,
 * CTRL, MOVE/PDMOVE/MOVEEX (TX/TY/TZ/RY), MUTEKI, bound WPOS AIMAP and
 * explicitly owned NEAR map zero. Arrival RR/LP motion
 * selection persists across frame-delay actions. Unsupported action components fail preflight. */
/* Borrowed read-only projection of Work's typed subcommands, refreshed at each
 * query. end_frames is the actual retail endpoint (length -1 becomes 1e8).
 * length_frames is diagnostic; consumers use the endpoint without subtracting
 * and adding floats again. Queries never activate or consume a subcommand. */
typedef struct {int32_t kind;float start_frames,length_frames;dw4_handle object;float run_frame;float offset[3],size[3];float end_frames;} dw4_modelctrl_hitbox;
/* The model's own held clock; it may differ from session time after a freeze. */
int64_t dw4_modelctrl_now(const dw4_modelctrl *);
const dw4_modelctrl_hitbox *dw4_modelctrl_hitboxes(const dw4_modelctrl *,unsigned *count);
/* Synchronous 395b50 subcommand phase, after waits/MUTEKI and before floor
 * response. The snapshot/matrix are borrowed for this call. Scripts may replace
 * the source sequence, but may not recursively tick or destroy this model or
 * its sink owner. The time is the source input sample (possibly stage-relative). */
typedef int (*dw4_modelctrl_hit_emit)(void *,dw4_modelctrl *,const dw4_modelctrl_hitbox *,const float world[16],int64_t sample_ns);
void dw4_modelctrl_hit_sink(dw4_modelctrl *,dw4_modelctrl_hit_emit,void *,void (*release)(void *));
/* Node-lock branch of 395b50: retain the source node and apply a local offset
 * at the movement phase; NULL unlocks. Named-bone/track lookup is a separate seam. */
int dw4_modelctrl_position_lock(dw4_modelctrl *,const dw4_modelctrl *source,const float offset[3]);
/* Borrowed manager/media leaves. Bind outside dispatch, and keep their owners
 * alive until this model's subcommands have been cleared/closed. Effect sees
 * the actual typed SCEffect handle and writes _geneRamNo/start keep. Sound
 * retains only nonzero/non--1 handles with type4. Bone returns 1 found, 0 no
 * matching receiver/bone, -1 unavailable; output is the composed world matrix.
 * Track returns a borrowed beModelCtrlInfoDataTrc; its recorder owner outlives
 * every lock. None of these callbacks may tick or destroy the active model. */
typedef struct {
    void *user;
    int (*effect)(void *,dw4_modelctrl *,dw4_handle,int finish,int *keep);
    int (*sound_play)(void *,const char *,int64_t *handle,int *type);
    int (*sound_down)(void *,int64_t handle);
    int (*bone)(void *,dw4_modelctrl *,const char *model,const char *bone,float world[16]);
    int (*track)(void *,dw4_modelctrl *,const char *model,dw4_handle *);
    /* Called once after finish/unlock, while the model records still exist.
     * Must not destroy or rebind the model. */
    void (*release)(void *);
} dw4_modelctrl_dependencies;
/* Replacement/detach finishes effect/sound entries through the old services,
 * releases named/track locks, then releases the old context. HITBOX and model
 * activity are preserved. Reentrant replacement is rejected. On a finish error
 * the old context is detached and the new binding is not installed. */
int dw4_modelctrl_dependencies_bind(dw4_modelctrl *,const dw4_modelctrl_dependencies *);
/* Direct recovered MOVERL consumer; JOINT selects TRC, all other names select
 * a named bone. A missing JOINT result leaves the lock disabled. */
int dw4_modelctrl_relative(dw4_modelctrl *,const char *kind,const char *model,const char *bone);
/* GENERATE's effect receiver leaf (396340). Angles are radians; follow retains
 * the source node, and hit-parent identity propagates through effect chains. */
int dw4_modelctrl_generate_effect(dw4_modelctrl *,dw4_modelctrl *source,const char *sequence,
    const float offset[3],const float rotation[3],int follow);
/* An owner supplies beSystem._frameTimeF once for its model-manager pass. */
int dw4_modelctrl_tick_frame(dw4_modelctrl *,int64_t ns,uint32_t system_frame);

/* Diagnostic: print every sequence command (sequence, type, name). */
void dw4_modelctrl_census(const dw4_modelctrl *,FILE *);
dw4_modelctrl *dw4_modelctrl_open(const uint8_t *,size_t,const char *);
/* Prepared registry uses exact pack-local info identity, independent of names. */
dw4_modelctrl *dw4_modelctrl_open_info(const dw4_igb *,uint32_t info_id);
/* Fresh inactive instance sharing immutable programs, with an independent clock. */
dw4_modelctrl *dw4_modelctrl_instance(const dw4_modelctrl *);
void dw4_modelctrl_close(dw4_modelctrl *);
void dw4_modelctrl_random(dw4_modelctrl *,dw4_random *,uint32_t *rhythm);
int dw4_modelctrl_start(dw4_modelctrl *,const char *);
void dw4_modelctrl_remove(dw4_modelctrl *);
/* Effect finish's SQ_ERAS request: preserve activity until the next unfrozen
 * update sends REMOVE, following 396a80 -> 395b50. Closing still removes now. */
void dw4_modelctrl_request_erase(dw4_modelctrl *);
void dw4_modelctrl_sample(dw4_modelctrl *,int64_t world_ns);
int dw4_modelctrl_tick(dw4_modelctrl *,int64_t world_ns);
int dw4_modelctrl_active(const dw4_modelctrl *);
/* Active work can remain live after FADESET HIDE; rendering eligibility differs. */
int dw4_modelctrl_drawable(const dw4_modelctrl *);
float dw4_modelctrl_alpha(const dw4_modelctrl *);
int dw4_modelctrl_frozen(const dw4_modelctrl *);
const char *dw4_modelctrl_sequence(const dw4_modelctrl *);
/* Current Action2 data name, distinct from its containing SQ_* sequence. */
const char *dw4_modelctrl_action(const dw4_modelctrl *);
int64_t dw4_modelctrl_time(const dw4_modelctrl *);
const char *dw4_modelctrl_error(const dw4_modelctrl *);
int dw4_modelctrl_service(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
/* Status ailments (beNDMWMdlPEBase work; docs/combat.md "Status wiring"). Enemies and players own a dw4_status; the SETxxx / CLEARSTATUS /
 * ALLCLEARSTATUS service messages and the CHECKSTATUS query reach it, the sequence-change hook (FUN_00445200) runs after every sequence set.
 * NULL for models without one (objects, NPCs, bullets). */
const dw4_status *dw4_modelctrl_status(const dw4_modelctrl *);
/* A player's stat lists live in its game-RAM record: the host loads them into the status before every message/tick/hook and stores them
 * back (and recalculates the player) afterwards. `store` gets the message or tick result (recalc_player, killed). Borrowed; NULL detaches. */
typedef struct {
    void *user;
    void (*load)(void *user,dw4_status *);
    void (*store)(void *user,dw4_status *,const dw4_status_tick_result *);
} dw4_status_player_host;
void dw4_modelctrl_status_player(dw4_modelctrl *,const dw4_status_player_host *);
/* Cure's poison removal on this model's status work (FUN_00447b40): clears the POISON timer. Returns 1 when poison was set, 0 otherwise (also for a
 * model without status work or an inactive slot). */
int dw4_modelctrl_cure_poison(dw4_modelctrl *);
/* One frame of the status manager (vfunc_46) on the model's own clock (frozen models hold it); runs before the model's tick. `*hp` is the
 * model's HP (poison changes it). Applies the requested sequence (SQ_SLEP, SQ_WAIT, SQ_DEAD) when the model has it. Returns 0, or -1 with the model error set. */
int dw4_modelctrl_status_tick(dw4_modelctrl *,int32_t *hp,dw4_status_tick_result *out);
#endif
