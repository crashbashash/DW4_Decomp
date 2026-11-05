/* Native combat owner of a field stage: delivers the attackers' timed HITBOX volumes to enemy receivers and serves the BLT/MDL combat calls
 * of the original hit_<model>.lua chunks through the FIGHTCALC rules (fightcalc.h). One owner per world, keyed by player slot (0..3) so
 * damage, EXP and skill attribution follow the shooter. HITBOX activation/removal follows the recovered per-model scheduler;
 * remaining delivery and gameplay fidelity limits are documented in docs/combat.md. */
#ifndef DW4_COMBAT_H
#define DW4_COMBAT_H
#include "dw4/controllers.h"
#include "dw4/fightcalc.h"
#include "dw4/playerrecords.h"
typedef struct dw4_combat dw4_combat;
/* Records/databases/RNG and the registry outlive gameplay callbacks. Individual
 * source models may close independently; close combat before its service owners. */
dw4_combat *dw4_combat_open(dw4_playerrecords *records,const dw4_databases *databases,dw4_random *rng,dw4_controllers *models);
void dw4_combat_close(dw4_combat *);
/* Sample session time and refresh player bindings before the model-manager
 * pass; delivery is synchronous in each model update. Repeated calls do not emit. */
int dw4_combat_tick(dw4_combat *,int64_t now_ns,dw4_modelctrl *const players[4],char *error,size_t cap);
/* One frame of the status manager for the given player models (record HP in, record HP out; poison, sleep, stun, bind and the stat-list expiries,
 * docs/combat.md "Status wiring"). Run once per simulation tick before the controllers' tick, which does the same for the enemies. */
int dw4_combat_status_tick(dw4_combat *,dw4_modelctrl *const players[4],char *error,size_t cap);
/* Seams for tests and for the technique firing: the combat rules as a dw4_model_fight table (user = this owner), and one synthetic enemy bullet of
 * `kind` (attack number 7xxxx) from enemy row `enemy_row` in RAM slot `enemy_slot` offered to the player model of `slot` through the real
 * hit_<species>.lua chunk (geometry skipped; `attacker` is the shooting enemy's status or NULL). Returns 1 when the script ran, 0 for no hit, -1 on error. */
void dw4_combat_fight(dw4_combat *,dw4_model_fight *out);
int dw4_combat_hit_player(dw4_combat *,int32_t slot,dw4_modelctrl *player,int64_t now_ns,int32_t kind,int32_t enemy_row,int32_t enemy_slot,
    const dw4_status *attacker,char *error,size_t cap);
/* Deliver one technique bullet volume (box offset/size in the frame of `world`, the caster's matrix at launch); see combat.c. Returns the contacts, or -1. */
int dw4_combat_fire(dw4_combat *,int64_t now_ns,int32_t slot,dw4_modelctrl *caster,int32_t attack,const float world[16],const float offset[3],const float size[3],char *error,size_t cap);
/* Scene script engine and SD scope that the player models' hit callbacks run in. Call once, before the first tick. */
void dw4_combat_scripts(dw4_combat *,dw4_scriptengine *,uint64_t scope);

/* Support techniques (Heal Lt / Heal, Cure Lt / Cure, Raise, Speed, Resist, Power; docs/combat.md "Support technique wiring"). An 80000..89999
 * volume strikes the caster's own body, the original hit_p_<species>.lua runs its support branch and reaches BLPcalcKoukaMagic, which the
 * dw4_model_fight.p2p_magic callback answers through dw4_combat_cast_support.
 * The membership of the PLAYER (and downed PLAYER2) groups the area queries read: `joined` = a player model answers, `downed` = a PLAYER2 capsule
 * exists, `running` = the PLAYER model is running (a Raise skips the HP write for it), `pos` = the GETMATRIX translation. */
typedef struct {int joined[4];int downed[4];int running[4];float pos[4][3];
    int young[4];   /* downed capsule whose ONE counter is still below 10: its RAISE handler returns early (0x3d50c0), so it is not revived (0 = ready, the default) */
} dw4_combat_view;
/* Bind player models before their first update (index = slot, NULL = not joined).
 * status_tick and combat_tick refresh these bindings too. Either the combat or
 * model owner may close first; callbacks detach and release their contexts. */
void dw4_combat_players(dw4_combat *,dw4_modelctrl *const players[4]);
/* Membership derived from the stored player models (joined / running = model active, pos = its feet position) and the downed slots. */
void dw4_combat_view_current(const dw4_combat *,dw4_combat_view *out);
/* Mark a slot as downed (a PLAYER2 capsule at `pos`) so Raise can find it, with its ONE counter already at 10 (a settled capsule). The KO flow below does
 * this by itself; this seam is for tests. */
void dw4_combat_set_downed(dw4_combat *,int32_t slot,int downed,const float pos[3]);

/* Player KO flow (docs/combat.md "KO, the capsule and game over"). Every joined player whose record HP reaches 0 after having been seen above 0 is KO'd;
 * DW4_KO_CAPSULE_DELAY ticks later (measured live, finding #340: the BKCHIP* record is written ~120 frames after the KO) its PLAYER2 capsule is created at the
 * player's feet position: BKCHIPSTAGE/BKCHIPPOS (beNDMWMdlPlayer2::vfunc_36), then BKCHIPBITEXP (beNDMWMdlPlayer::vfunc_43). The player is then no longer a PLAYER
 * (not joined, not running for the area queries, its body takes no hits). Every capsule ticks once per frame (vfunc_38): the ONE counter counts to 10,
 * the SQ_SWON/SQ_SWOF state follows the distance to the nearest living player, and with no living player left the end chunk (end_g_000bcaps.lua) is due. */
#define DW4_KO_CAPSULE_DELAY 120       /* ticks between the KO and the capsule: measured, not recovered from code */
#define DW4_CAPSULE_READY_TICKS 10     /* Raise needs the capsule's ONE counter >= 10 (0x3d50c0); vfunc_38 counts it up to 10 */
#define DW4_CAPSULE_NEAR_SQ 900.0f     /* vfunc_38 compares the nearest-PLAYER distance (units inferred as squared) with 900.0 */
typedef struct {int downed,ready,near_player;unsigned age,ko_ticks;float pos[3];} dw4_combat_capsule;
/* One frame of the KO flow; `stage` is the loaded stage name (BKCHIPSTAGE). Sets *game_over to 1 once, on the first tick at which a capsule finds no living
 * PLAYER (the engine then runs end_g_000bcaps.lua; the retail chunk's guard against repeated starts is unrecovered, the port starts it once).
 * Returns 0, or -1 with the error in dw4_combat_error. Run after dw4_combat_tick. */
int dw4_combat_ko_tick(dw4_combat *,const char *stage,int *game_over);
/* State of one slot's KO/capsule tracking (NULL out is allowed to just test the slot); returns the downed flag. */
int dw4_combat_capsule_state(const dw4_combat *,int32_t slot,dw4_combat_capsule *out);
/* HP gauge publication (retail FUN_003f9c80's METERCTRL hpmt / NUMBERCTRL hpnm sends): called with the slot and its record HP / MHP after a heal and
 * after a buff recalculation (ADDHP(index, 0)). */
typedef void (*dw4_combat_hud_fn)(void *user,int32_t slot,int32_t hp,int32_t max_hp);
void dw4_combat_hud(dw4_combat *,dw4_combat_hud_fn,void *user);
/* Floating numbers (FUN_00373ef0): row 0 damage, 1 exp, 3 player damage, at the hit model's world position. */
typedef void (*dw4_combat_popup_fn)(void *user,int32_t row,int32_t value,const float position[3]);
void dw4_combat_popup(dw4_combat *,dw4_combat_popup_fn,void *user);
/* The FIGHTCALC P2PKOUKAMAGIC work for the call (receiver, shooter, attack): nothing unless receiver == shooter, then the family of attack % 10000
 * is applied to the players the PLAYER area query finds around the caster. `view` NULL derives the membership from the stored models. *result is the
 * script's return value (1 for a self hit, the receiver otherwise). Returns 0, or -1 with the error in dw4_combat_error. */
int dw4_combat_cast_support(dw4_combat *,int32_t receiver,int32_t shooter,int32_t attack,const dw4_combat_view *view,int32_t *result);
const char *dw4_combat_error(const dw4_combat *);
/* Counters for tests and HUD hooks. */
typedef struct {unsigned skill_ups,hits,damage_total;int32_t last_damage,last_exp;unsigned exp_total;unsigned player_hits,player_damage_total;int32_t player_last_damage;
    /* support techniques: targets healed / poison cures that landed / revived slots / buff messages delivered (and skipped for want of a model) /
     * buff expiries seen by the status manager / stat recalculations it ran / support volumes that ran the hit script / ones that found no body */
    unsigned heals,cures,raises,buff_applies,buff_no_model,buff_expiries,recalcs,support_hits,support_missed;
    unsigned downs,gameovers;   /* capsules created by the KO flow / times the end chunk became due */
    unsigned skill_draws;   /* BLTcalcSkillUp calls that drew the growth chance (below the level cap), whether or not the skill rose */
} dw4_combat_stats;
const dw4_combat_stats *dw4_combat_get_stats(const dw4_combat *);
#endif
