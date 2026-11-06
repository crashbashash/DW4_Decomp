#ifndef DW4_HUBRUNTIME_H
#define DW4_HUBRUNTIME_H
#include "dw4/lobby.h"
#include "dw4/input.h"
#include "dw4/combat.h"
#include "dw4/playerrecords.h"
#include "dw4/stagetravel.h"
#include "dw4/controllers.h"
#include "dw4/database.h"
#include "dw4/shopstock.h"
typedef struct dw4_hubruntime dw4_hubruntime;
/* Last HP meter percent/number the field hit scripts published per player slot (no field HUD is drawn yet). */
typedef struct {float hp_percent[4];int32_t hp_value[4];unsigned updates;} dw4_hubruntime_hud;
/* The floating numbers (FUN_00373ef0) the field has spawned: per row (0 damage, 1 exp, 3 player damage) the count, plus the last spawned sequence and value, and the digit-plate vertices drawn so far. */
typedef struct {unsigned spawned[5],refused,digit_vertices;int32_t last_value;char last_sequence[16];} dw4_hubruntime_popups;
const dw4_hubruntime_popups *dw4_hubruntime_popup_stats(const dw4_hubruntime *);
/* The drop presentation (FUN_00384800 / beNDMWMdlItem): item models generated and ended, 'got
 * item' effects and name labels sent. `unmodelled` counts drops whose model name has no controller
 * in the stage (kept record-only; `missing` is the last such name), `lost` drops whose model pool
 * was full (retail's GENERATE reaches no free instance, so no item exists), `expired` models that
 * ended before anyone took them. */
typedef struct {
    unsigned spawned,unmodelled,lost,failed,expired,erased,effects,labels_on,labels_off,dropitems;
    char missing[16],last_effect_panel[20],last_effect_sequence[16],last_label[64];int last_effect_slot,last_label_slot;
} dw4_hubruntime_loot;
const dw4_hubruntime_loot *dw4_hubruntime_loot_stats(const dw4_hubruntime *);
/* Isolated destination: owns a complete record snapshot, copied engine/RNG
 * state, VM/SD/DM, prepared assets and native controllers. Never mutates the
 * source owners. No graphics context or audio device is opened by prepare. */
typedef struct {
    const dw4_playerrecords *records;
    const dw4_be_state *state;
    const dw4_stageinput *input;
    uint64_t world_ns;
} dw4_hubruntime_source;
dw4_hubruntime *dw4_hubruntime_prepare(dw4_mount *,const dw4_hubruntime_source *,
    const char *stage,int32_t point,int light_hard,char *,size_t);
/* 1 when the runtime prepares this kind of destination: the hub areas (stagML..), the interface scenes (stagIS..) and the first
 * field stage (stag0101). 0 for the other field (stag0...) and dungeon (dng...) stages and anything else that the original gate prompts can request but
 * this build has no runtime for; prepare refuses them with a "not available" error. */
int dw4_field_stage(const char *stage);
int dw4_field_stage_ready(const char *stage);
int dw4_hubruntime_destination_available(const char *stage);
/* Failed-load Back restores the retained source using original model sequences. */
int dw4_hubruntime_cancel_travel(dw4_hubruntime *);
void dw4_hubruntime_close(dw4_hubruntime *);
/* Tick only after publication, once per admitted world simulation tick. */
int dw4_hubruntime_tick(dw4_hubruntime *,uint64_t world_ns);
uint64_t dw4_hubruntime_time(const dw4_hubruntime *);
const dw4_stageinput *dw4_hubruntime_input_state(const dw4_hubruntime *);
void dw4_hubruntime_input(dw4_hubruntime *,float x,float y,uint32_t analog,uint32_t held,uint32_t pressed);
/* Local co-op: the pad of player slot 1..3, the same inputs as the first pad on that slot's model (walk stick, jump, R1 technique panel, the Cross swing and
 * talk probe, Start for STATUS). The pad words also reach the selectors and menus that name the slot (SELECTCTRL <name> <slot>, SUBWND ... I<slot>). */
void dw4_hubruntime_input_slot(dw4_hubruntime *,unsigned slot,float x,float y,uint32_t analog,uint32_t held,uint32_t pressed);
/* The host pads of players 2-4 (`mates[0..2]`, with last frame's states for the button edges) as the engine reads them (dw4/pads.h): each drives its own
 * player through dw4_hubruntime_input_slot. Slots nobody joined ignore their pad. */
void dw4_hubruntime_input_mates(dw4_hubruntime *,const dw4_input_state mates[3],const dw4_input_state previous[3]);
int dw4_hubruntime_draw(dw4_hubruntime *,dw4_fb *,const dw4_fefont *);
dw4_lobby *dw4_hubruntime_world(dw4_hubruntime *);
dw4_playerrecords *dw4_hubruntime_records(dw4_hubruntime *);
const dw4_be_state *dw4_hubruntime_state(const dw4_hubruntime *);
const dw4_stagetravel *dw4_hubruntime_travel(const dw4_hubruntime *);
/* Development/profiling only (DW4_DEV_WARP): queue a stage change as the world's own exit would. */
void dw4_hubruntime_dev_travel(dw4_hubruntime *,const char *stage,int32_t point);
int dw4_hubruntime_status_active(const dw4_hubruntime *);
/* The SUBWND mode (1 XDATA, 3..9) running under the generic shop root, or 0 when no such window is open. */
int32_t dw4_hubruntime_shop_mode(const dw4_hubruntime *);
const dw4_dialogue *dw4_hubruntime_dialogue(const dw4_hubruntime *);
/* Borrowed scene model owner (NPC instances); valid until close. */
const dw4_controllers *dw4_hubruntime_models(const dw4_hubruntime *);
/* The prepared hub's database owner (the services' item, chip and reroll tables). */
const dw4_databases *dw4_hubruntime_databases(const dw4_hubruntime *);
/* The hub's shop stock (SUBWND work lists); populated by the first WPU/APU/CHIP/JUNK visit. */
dw4_shopstock *dw4_hubruntime_shopstock(dw4_hubruntime *);
/* Move the audio output from the retained source (a hub or the first lobby) to this destination. */
int dw4_hubruntime_adopt_audio(dw4_hubruntime *to,dw4_hubruntime *from_hub,dw4_lobby *from_lobby);
/* Open the destination's GPU context (the lobby's, or the save screen's UI layer); the renderer or NULL. */
const char *dw4_hubruntime_enable_gpu(dw4_hubruntime *,int w,int h);
/* The save-screen scene when this runtime is stagIS12 (diagnostics and tests), else NULL. */
struct dw4_savescene;
const struct dw4_savescene *dw4_hubruntime_scene(const dw4_hubruntime *);
/* Run a named stage chunk (epic.lua, gatedisc.lua ...) as the engine would when an event selects it. Test/bring-up use. */
int dw4_hubruntime_run_chunk(dw4_hubruntime *,const char *name);

/* Send one SD command to the runtime's receivers (test and bring-up use; scripts go through the same registry). */
int dw4_hubruntime_sd(dw4_hubruntime *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
/* Script-visible state (row, HP) of an enemy or object receiver. */
/* Test fixture: drop the enemy's NEAR target so its authored AI stops choosing walks and attacks. */
int dw4_hubruntime_enemy_ai_off(dw4_hubruntime *,const char *name,int32_t slot);
dw4_script_model *dw4_hubruntime_enemy_state(dw4_hubruntime *,const char *name,int32_t slot);
const dw4_hubruntime_hud *dw4_hubruntime_hud_state(const dw4_hubruntime *);
const dw4_combat_stats *dw4_hubruntime_combat(const dw4_hubruntime *);
/* Test seam: the field stage's combat owner (NULL outside a field stage), for dw4_combat_fight / dw4_combat_hit_player. */
dw4_combat *dw4_hubruntime_combat_owner(dw4_hubruntime *);
/* The field stage's R1 technique panels (dw4/technique.h), NULL elsewhere. */
struct dw4_technique;
const struct dw4_technique *dw4_hubruntime_technique(const dw4_hubruntime *);
const struct dw4_fieldgen *dw4_hubruntime_fieldgen(const dw4_hubruntime *);
/* Field stages: HITLANDMODEL calls that named a hit-land model the stage does not own (retail no-ops; the port drops them silently). */
unsigned dw4_hubruntime_hitland_missing(const dw4_hubruntime *);
struct dw4_scriptengine *dw4_hubruntime_scripts(const dw4_hubruntime *);
/* Drops collected so far (field stages). */
unsigned dw4_hubruntime_pickups(const dw4_hubruntime *);
/* The digivolution demo scene when this runtime is stagML14 (dw4/evodemo.h), else NULL (also when it fell back to its exit). */
struct dw4_evodemo;
const struct dw4_evodemo *dw4_hubruntime_demo(const dw4_hubruntime *);
const char *dw4_hubruntime_error(const dw4_hubruntime *);
#endif
