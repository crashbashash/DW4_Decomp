/* Application of the P2PKOUKAMAGIC numbers (fightmagic.h) to the players: the PLAYER area query of beNDMWGameRam_CollectNearbyNonzeroHp (0x3fc780), the Heal
 * HP delta (FUN_003f9c80), the Cure poison draw (FUN_00447b00 / 0x447b40) and the Raise receiver (PLAYER2 handler 0x3d50c0). The caller supplies the
 * positions (retail: the GETMATRIX translation of each group member) and the group membership. Self-consistency tested only
 * (`check-fieldstage magicapply`), not compared against retail. docs/combat.md "Area queries and heal/cure/raise application". */
#ifndef DW4_MAGICAPPLY_H
#define DW4_MAGICAPPLY_H
#include "dw4/fightmagic.h"
#include "dw4/playerrecords.h"
#define DW4_MAGIC_AREA_RADIUS_SQ 900.0f   /* 0x3fc8c0: c.lt.s dist^2 < 900.0 (lui 0x4461): radius 30 units, 3D, strict */
typedef struct {
    int member[4];       /* answers the group message (retail: SendGroup(group,"GETMATRIX") answers; PLAYER: the player's model exists) */
    float pos[4][3];     /* GETMATRIX translation of each member */
    int answer[4];       /* the per-member GETHP check answer: PLAYER = the player's HP; PLAYER2 = unresolved (the caller states it) */
} dw4_magic_group;
/* CollectNearbyNonzeroHp: out[] = member ids (ascending slot = assumed group order) with member, id != excluded (-1 excludes nobody), squared 3D distance to
 * `center` < 900 and a non-zero answer. Returns the count. */
int dw4_magic_area_collect(const dw4_magic_group *,int32_t excluded,const float center[3],int32_t out[4]);
/* Fill a PLAYER group from the records: answer[i] = HP of slot i, member[i] = joined[i]. */
int dw4_magic_player_group(dw4_playerrecords *,const int joined[4],const float pos[4][3],dw4_magic_group *out);
/* HEAL (kind HEAL, case 40/45): HP += m->v[0] on the caster (FUN_003f9c80; a dead caster is left alone), then, for Heal (45), on every member of the area
 * (the caster excluded), the full delta each, in list order. applied[i] = 1 when slot i changed. Returns the number of area targets, -1 on error. */
int dw4_magic_apply_heal(dw4_playerrecords *,const dw4_magic *,int32_t caster,const dw4_magic_group *,int applied[4]);
/* CURE (kind CURE, case 55/60): the caster first, then (Cure 60) the area. For each target whose poison timer slot is non-zero (poisoned[i]) exactly one
 * rand%10 draw is made; cured[i] = 1 when v[0] - endurance[i] >= draw. Returns the number of draws, -1 on error. */
int dw4_magic_apply_cure(const dw4_fight_ctx *,const dw4_magic *,int32_t caster,const dw4_magic_group *,const int poisoned[4],const int32_t endurance[4],int cured[4]);
/* RAISE (kind RAISE): the PLAYER2 group is queried around the caster with excluded -1. Each target receives v[0] (percent of its stashed EXP) and v[1]
 * (absolute HP). When the target's PLAYER model is not running (running[i] = ISRUN answer) the handler sets HP = v[1] with no clamp and no gauge message.
 * Returns the number of targets (ids in targets[], percents in exp_percent[]). */
int dw4_magic_apply_raise(dw4_playerrecords *,const dw4_magic *,const dw4_magic_group *player2,const float caster_pos[3],const int running[4],int32_t targets[4],int32_t exp_percent[4]);
/* Buff targets (SPEEDUP / POWERUP / REFRACT): the area list of the PLAYER query around the caster (caster excluded) with the caster appended LAST
 * (retail RecoveryList::append, cpp ~5353 / 5460 / 5545). Returns the count (at most 4), -1 on error. Effect particles go to every target but the
 * caster in retail (presentation, not ported). */
int dw4_magic_buff_targets(const dw4_magic_group *,int32_t caster,int32_t out[4]);
/* The bank-chip refund every Raise receiver performs for the revived slot (PLAYER2 handler 0x3d50c0): GETCOMMON BKCHIPDATA[2*slot] is added to the
 * player's BIT and cleared; when the player's DIGIMONNAME equals BKCHIPNAME[slot], BKCHIPDATA[2*slot+1] * percent / 100 is added to EXP and cleared;
 * BKCHIPSTAGE[slot] is cleared. `percent` is the first Raise integer (59..95, item 59). Which fields the retail code clears exactly is read from the
 * recovered description, not measured. Returns 0, or -1 when the records are unavailable. The death-side stash is dw4_magic_bkchip_bitexp below. */
int dw4_magic_apply_raise_refund(dw4_playerrecords *,int32_t slot,int32_t percent);
/* GAMERAM BKCHIPBITEXP (beNDMWGameRam::vfunc_34 outer case 20, src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp ~5618-5666): the death stash of `slot`.
 * BKCHIPNAME[slot] = DIGIMONNAME; BKCHIPDATA[2*slot] = BIT and BIT = 0; unless LEVEL is 1 or 999 the EXP drops by 2/10 of the level span
 * (g(L-1,L) - g(L-2,L-1), g = the NEXTEXP curve; the product is divided by 10 with integer division) but never below the level's base g(L-1,L), and the
 * amount lost goes to BKCHIPDATA[2*slot+1] (at level 1 or 999 that entry is not touched). Returns 0, or -1 when the records are unavailable.
 * Hand-computed values only (`check-fieldstage deathflow`), not retail-measured. */
int dw4_magic_bkchip_bitexp(dw4_playerrecords *,int32_t slot);
/* GAMERAM DEADRESTART (message 16, vfunc_34 ~2235): every slot whose ISUSE byte is non-zero gets HP = MHP and MP = MMP (records only, no gauge message).
 * Who sends it is not found in any Lua; the port sends it when the game-over chunk requests the return to the hub (inference). */
int dw4_magic_dead_restart(dw4_playerrecords *);
/* The record side of the capsule's start (beNDMWMdlPlayer2::vfunc_36, 0x3d4a20): GETCOMMON BKCHIPSTAGE[slot] = the loaded stage name and
 * BKCHIPPOS[3*slot..3*slot+2] = the capsule's translation. */
int dw4_magic_capsule_start(dw4_playerrecords *,int32_t slot,const char *stage,const float pos[3]);
#endif
