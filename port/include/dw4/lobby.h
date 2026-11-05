#ifndef DW4_LOBBY_H
#define DW4_LOBBY_H
#include "dw4/mount.h"
#include "dw4/render.h"
#include "dw4/fefont.h"
#include "dw4/script.h"
#include "dw4/scriptengine.h"
#include "dw4/dialogue.h"
#include "dw4/modelctrl.h"
#include "dw4/playerhealth.h"
#include "dw4/hudmeter.h"
#include "dw4/controllers.h"
typedef struct dw4_lobby dw4_lobby;
/* First-arrival environment, using stagML11's BG02 and camsp0101 graphs.
 * Standalone callers retain the bounded reference adapter; normal boot binds
 * scene-owned controllers and original scripts. Walking/jumping, bounded
 * collision, gate proximity and heal activation are connected;
 * combat, general traversal and save persistence remain outstanding. */
dw4_lobby *dw4_lobby_open(dw4_mount *mnt, int species, const char *name);
/* Private preparation for the original hub destination/arrival group. Scene
 * startup and native model owners must bind before gameplay publication. */
/* The other joined players of a local co-op party (slots 1..3): shinka row, 8-character name, weapon asset (NULL: the starter's own, "" unarmed). */
typedef struct {int row;char name[9];const char *weapon;} dw4_lobby_member;
dw4_lobby *dw4_lobby_open_row_stage_party(dw4_mount *,int row,const char *name,const char *stage,int32_t point,const char *weapon,const dw4_lobby_member *others,unsigned nothers);
int dw4_lobby_field_world(const char *stage);   /* stag0xxx, stagGFxx and dngXXXxx: worlds opened without the hub windows */
dw4_lobby *dw4_lobby_open_stage(dw4_mount *,int species,const char *name,const char *stage,int32_t point);
/* Live destination preparation preserves the admitted equipped socket model;
 * NULL is rejected rather than silently installing a starter weapon; unarmed has its own entry below. */
/* Player models by shinka row 0..15 (starters agumon, vmon, girumon, dorumon, then the evolved forms); the open_stage calls below take the
 * legacy starter index 0..3 = dorumon, agumon, vmon, girumon. dw4_lobby_open_row_stage takes the row. */
const char *dw4_lobby_model_name(int row);
dw4_lobby *dw4_lobby_open_row_stage(dw4_mount *,int row,const char *name,const char *stage,int32_t point,const char *weapon);
/* An unarmed player (empty POWERSOCKETNAME): no weapon graph, and the player's sequences enter at their first authored
 * section, as retail does when it skips PLAYERARMS GENERATE. dw4_lobby_weapon with "" publishes the same state live. */
dw4_lobby *dw4_lobby_open_row_stage_unarmed(dw4_mount *,int row,const char *name,const char *stage,int32_t point);
/* The shinka row this lobby's player model was opened for (it also selects the HUD portrait), or -1. */
int dw4_lobby_player_row(const dw4_lobby *);
/* HUD meter 0 (HP) or 1 (MP); borrowed and read-only. */
const dw4_hudmeter *dw4_lobby_hud_meter(const dw4_lobby *,unsigned);
dw4_lobby *dw4_lobby_open_stage_equipped(dw4_mount *,int species,const char *name,const char *stage,int32_t point,const char *weapon);
typedef struct {const char *stage;int32_t arrival_point;unsigned camera_regions,materials,floor_triangles,wall_triangles;} dw4_lobby_world_state;
int dw4_lobby_world_info(const dw4_lobby *,dw4_lobby_world_state *);
/* Retail LIGHTMODE: 0 Soft (authored lights), 1 Hard (stage Lua override).
 * Selects the corresponding named world atlases too. Diagnostic lobbies default
 * to Hard. Applies to both raster backends. */
void dw4_lobby_set_light(dw4_lobby *, int hard);
/* Opt in after opening; returns renderer name, or NULL for CPU fallback.
 * The lobby owns the GPU context and closes it before its immutable textures. */
const char *dw4_lobby_enable_gpu(dw4_lobby *l, int w, int h);
const char *dw4_lobby_gpu_info(const dw4_lobby *);
/* Decode while preparing; open the device only after publishing the lobby. */
int dw4_lobby_prepare_audio(dw4_lobby *, dw4_mount *);
void dw4_lobby_start_audio(dw4_lobby *);
int dw4_lobby_start_scripted_audio(dw4_lobby *);
int dw4_lobby_adopt_audio(dw4_lobby *destination,dw4_lobby *source);
struct dw4_frontaudio *dw4_lobby_audio(dw4_lobby *);
void dw4_lobby_model_action(dw4_lobby *,const char *model,const char *action);
void dw4_lobby_close(dw4_lobby *l);
/* Attach on the simulation thread after preparation, before publication.
 * Executes original guide WPos callbacks and native MAP01 choice draws after
 * greeting closure. Borrows engine/state until detach/close. */
int dw4_lobby_attach_scripts(dw4_lobby *,dw4_mount *,dw4_scriptengine *,dw4_be_state *,uint64_t scope);
/* Use after the file-list loader has collected infos and run func/boot.
 * Attaches callbacks without recollecting or reexecuting shared definitions. */
int dw4_lobby_bind_scripts(dw4_lobby *,dw4_scriptengine *,dw4_be_state *,uint64_t scope);
void dw4_lobby_detach_scripts(dw4_lobby *);
void dw4_lobby_dialogue(dw4_lobby *,dw4_dialogue *);
const char *dw4_lobby_script_error(const dw4_lobby *);
typedef struct { int32_t hp; float target[3]; unsigned events,choices; int choice; } dw4_lobby_ai_state;
int dw4_lobby_ai(const dw4_lobby *,dw4_lobby_ai_state *);
/* Cross is an input edge; opening/closing transitions ignore it. */
void dw4_lobby_tick(dw4_lobby *l, int advance_pressed);
/* Sample assigned input once per simulation update; no movement from rendering.
 * Menu/focus/STATUS ownership supplies neutral input while held. */
void dw4_lobby_input(dw4_lobby *,float x,float y);
/* Circle pressed edge, consumed once on an eligible world update. */
void dw4_lobby_jump(dw4_lobby *,int pressed);
/* Cross pressed edge (3d22f0 0x4000). Consumed on the next eligible player update; the
 * one-frame 60000 talk probe then runs after movement against the HITPLAYERTALK
 * receivers. Ignored while jumping/falling or without player control. */
void dw4_lobby_talk(dw4_lobby *,int pressed);
/* Last talk dispatch: accepted hits, or -1 after an error (see script error). */
int dw4_lobby_talk_result(const dw4_lobby *);
typedef struct {float position[3],yaw,speed;const char *motion;int64_t motion_ns;unsigned contacts;} dw4_lobby_walk_state;
int dw4_lobby_walk(const dw4_lobby *,dw4_lobby_walk_state *);
/* Borrow scene-owned actors for original start/first execution. Bind before
 * startup, tick their owner before lobby tick, detach before controller close. */
int dw4_lobby_native_models(dw4_lobby *,dw4_controllers *,uint64_t origin_ns);
/* Destination binding: every authored non-UI world model RAM slot, with
 * per-instance transform/animation sampling. Bind once before startup/drawing. */
int dw4_lobby_native_scene(dw4_lobby *,dw4_controllers *,const dw4_stageobjects *,uint64_t origin_ns);
int dw4_lobby_publish_player(dw4_lobby *,dw4_scriptservices *,uint64_t,const char *name);
int dw4_lobby_player_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
int dw4_lobby_material_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
/* Admit the original hub travel events (the matz bridges and the mate gate pads) only when a travel consumer exists.
 * Legacy/standalone owners retain the heal and label material boundary. */
void dw4_lobby_exit_events(dw4_lobby *,int enabled);
/* Authored beMatCtrlData region by name: its index and bounds, or -1. The name of region <index>, or NULL. Test/inspection aid. */
int dw4_lobby_material_region(const dw4_lobby *,const char *name,float min[3],float max[3]);
const char *dw4_lobby_material_name(const dw4_lobby *,unsigned index);
/* HITLANDMODEL <name> ONHIT/OFFHIT: add or remove the info-owned static collision graph of the beHitLandModelInfo that lists
 * <name> (its slot-9 igNamedObjectList) from walking; an info that lists several names over as many meshes switches the name's own mesh
 * (one door). Fails for an unknown name or a graph that is not a floor/wall graph. */
int dw4_lobby_collision_hit(dw4_lobby *,const char *name,int on);
/* Inspection aids for the walking collision: the live wall/floor triangle counts, and whether the named hit-land graph is part of the
 * set (1 on, 0 removed by OFFHIT, -1 unknown name). The walking contacts are accumulated; clear them to watch one stretch of walking. */
int dw4_lobby_collision_counts(const dw4_lobby *,unsigned *wall_triangles,unsigned *floor_triangles);
int dw4_lobby_hit_state(const dw4_lobby *,const char *name);
void dw4_lobby_walk_clear_contacts(dw4_lobby *);
/* Run the player's ground-walking collision pass (the same call the walk uses) for a move from old to pos without moving anyone: pos is
 * solved in place (wall push-out, floor height) and the contact bits are returned (bit 1 wall, bit 2 loss of support). For route planning. */
unsigned dw4_lobby_walk_probe(const dw4_lobby *,const float old[3],float pos[3]);
/* Borrow a prepared WN model view, excluding the five lobby-owned windows.
 * Composes before native text/HUD and the original full-screen fade. */
typedef struct dw4_modelview dw4_modelview;
void dw4_lobby_native_ui(dw4_lobby *,dw4_modelview *);
int dw4_lobby_material_call(dw4_lobby *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
int dw4_lobby_light_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
int dw4_lobby_message(const dw4_lobby *l); /* message index 39..53, or -1 (49/50 use TALKFONT01) */
int dw4_lobby_intro_done(const dw4_lobby *l);
void dw4_lobby_status(dw4_lobby *,int active);
/* A hub party (2-4 players): the player panels are drawn per joined slot by the native model view instead of the single-player HUD. */
void dw4_lobby_party_hud(dw4_lobby *,int party);
int dw4_lobby_health(dw4_lobby *,int32_t level,int32_t hp,int32_t mp,int32_t max_hp,int32_t max_mp);
int dw4_lobby_health_publish(dw4_lobby *,const dw4_playerhealth *);
int dw4_lobby_sound_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
const dw4_modelctrl *dw4_lobby_window_model(const dw4_lobby *,unsigned);
/* 1 while a speaker message is open: from the moment its window is generated until the closing range ends (the HUD and the labels are hidden for that span). */
int dw4_lobby_talk_open(const dw4_lobby *);
int dw4_lobby_window_service(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
void dw4_lobby_services_sample(dw4_lobby *,uint64_t world_ns);
int dw4_lobby_services_tick(dw4_lobby *,uint64_t world_ns);
int dw4_lobby_camera_service(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
/* State restored together after the final close + 120 simulation ticks.
 * Control flags expose current ownership/eligibility; combat remains open. */
typedef struct {
    int hud, box_camera, player_control, model_control, material_updates;
    unsigned handoff_tick, material_ticks, camera_region, material_mask;
    float camera_world[16];
} dw4_lobby_control_state;
int dw4_lobby_control(const dw4_lobby *, dw4_lobby_control_state *);
/* `frame` is retained for call compatibility; presentation samples the latest
 * simulation tick. Repeated drawing and skipped presentation do not advance it.
 * NULL font suppresses UI for environment diagnostics. A present font enables
 * the greeting, which loads its NORMAL/MINIMUM faces independently. */
int dw4_lobby_draw(dw4_lobby *l, dw4_fb *fb, unsigned frame, const dw4_fefont *font);
/* Explicit preparation diagnostic: sample environment geometry without UI or
 * the unpublished scene's black startup fade. Does not activate or tick it. */
int dw4_lobby_draw_environment(dw4_lobby *,dw4_fb *);
/* Optional authored layer eligibility. NULL preserves the complete adapter
 * draw. The callback is read-only and borrowed only for this draw call. */
typedef int (*dw4_lobby_layer_visible)(void *,const char *);
int dw4_lobby_draw_layers(dw4_lobby *,dw4_fb *,unsigned,const dw4_fefont *,dw4_lobby_layer_visible,void *);
/* Read-only diagnostic vertices from the most recent draw, valid until next draw, appearance publication or close. */
const dw4_layer_draw *dw4_lobby_last_draws(const dw4_lobby *l, unsigned *count);
/* Read-only controller diagnostics: male=0, guide=1, second female=2. */
/* motion: 0 walk01, 1 wait01, 2 talk01; guide phase 5 departs, 6 brakes/waits. */
typedef struct { float position[3],yaw,speed,turn_speed; unsigned phase,contacts; int motion; } dw4_lobby_npc_state;
int dw4_lobby_npc(const dw4_lobby *,unsigned actor,dw4_lobby_npc_state *);
/* Appearance diagnostics; strings are borrowed until publication or close. */
typedef struct {
    const char *weapon_asset, *label, *motion, *bone;
    unsigned weapon_triangles;
    unsigned weapon_submitted_triangles; /* last draw after eligibility and viewport clipping */
} dw4_lobby_player_state;
/* Authored weapon parts attach independently (for example right/left hands).
 * Submitted counts describe the latest draw after visibility and clipping. */
typedef struct {const char *bone;unsigned triangles,submitted_triangles;} dw4_lobby_weapon_part_state;
unsigned dw4_lobby_weapon_parts(const dw4_lobby *);
int dw4_lobby_weapon_part(const dw4_lobby *,unsigned,dw4_lobby_weapon_part_state *);
int dw4_lobby_player(const dw4_lobby *, dw4_lobby_player_state *);
/* Publish a validated weapon graph, attachments and matching player idle pose
 * without restarting the world. Asset is the database MODEL stem/path. */
/* Scripted first Terminal: add the generated NPCs (Call Keeper, other elves, Agumon) that the three-actor path does not draw. */
int dw4_lobby_native_npcs(dw4_lobby *,dw4_controllers *,const dw4_stageobjects *);
/* Development/test aid: place the player at a world position (original MOVETRANS). */
int dw4_lobby_place_player(dw4_lobby *,float x,float y,float z,float yaw);
/* Test aid: the authored beMatCtrlData region by name (inclusive bounds, as the material dispatch tests them).
 * Returns its index, or -1 when the stage has no region of that name. */
int dw4_lobby_weapon(dw4_lobby *,dw4_mount *,const char *,char *,size_t);
/* Bounded MODELCTRL presentation seam; power-on arms the off pose, SWON/SWOF
 * execute authored transitions. These do not change progression or teleport. */
typedef struct { int powered, active, visible, action; int64_t animation_ns; } dw4_lobby_portal_state;
typedef struct {unsigned slots,visible_slots;float position[3];} dw4_lobby_portal_instances;
int dw4_lobby_portal_slots(const dw4_lobby *,unsigned,dw4_lobby_portal_instances *);
int dw4_lobby_portal_command(dw4_lobby *, unsigned portal, const char *command);
int dw4_lobby_portal(const dw4_lobby *, unsigned portal, dw4_lobby_portal_state *);
int dw4_lobby_portal_visible(dw4_lobby *, unsigned portal, int visible);
/* Render instances: male=0, player+weapon=1, guide=2, second female=3.
 * Hidden instances keep simulating; rendering never changes simulation clocks. */
int dw4_lobby_actor_visible(dw4_lobby *, unsigned actor, int visible);
/* Generated caster map after the last draw; borrowed until the next draw/close. */
const dw4_tex *dw4_lobby_shadow_map(const dw4_lobby *);
typedef struct {
    unsigned tick; float player_alpha, screen_alpha;
    int64_t player_motion_ns; int player_loop;
    unsigned arrival_mask; float arrival_alpha[3];
    unsigned particle_mask;
} dw4_lobby_presentation_state;
int dw4_lobby_presentation(const dw4_lobby *, dw4_lobby_presentation_state *);
/* The player's model controller (hub and field worlds), for combat owners. */
struct dw4_modelctrl *dw4_lobby_player_model(dw4_lobby *);
/* Local co-op: the per-player calls (input, jump, talk, request, model, walk state, place) act on the selected slot, slot 0 by default. */
int dw4_lobby_select_player(dw4_lobby *,unsigned slot);
unsigned dw4_lobby_player_count(const dw4_lobby *);
int dw4_lobby_player_joined(const dw4_lobby *,unsigned slot);
void dw4_lobby_clear_script_error(dw4_lobby *);
int dw4_lobby_player_request(dw4_lobby *,const char *sequence);
int dw4_lobby_point_string(const dw4_lobby *,int group,int player,char *out,size_t cap);
#endif
