/* Enemy-to-player status rules of FIGHTCALC (FightCom E2PSTUNTIME, E2PPOISONTIME, E2PSLEEPTIME,
 * E2PBINDTIME, E2PATKDWNTIME, E2PPOWDWNTIME; source cases 7-12 of the second switch of
 * beNDMWGameRam::vfunc_34). Every random draw uses the one engine stream as `next % n`, unsigned,
 * in source order. Return value of every rule: -1 on missing data or a zero divisor, 0 with *out
 * set to the integer the retail rule appends to the messenger, 1 when the retail rule appends
 * nothing (unrecognised mode string). Where the retail rule yields 0 for an effect that failed to
 * land, `*out` is 0; where an effect landed but rounds to 0 it is -1. */
#ifndef DW4_FIGHTSTATUS_E2P_H
#define DW4_FIGHTSTATUS_E2P_H
#include "dw4/fightcalc.h"
/* Cases 11 and 12 write one entry of the target's DOWNDATA list (the list property of the player record, 0x518b78) and then run the
 * equipment-applying stat recalculation (FUN_003fab90(game, player, 1)) BEFORE reading the player's property. The caller supplies
 * that step: apply_down(user, slot, value) must store `value` into list entry `slot` when the list holds more than `slot` entries,
 * then recalculate the player's stats (always). Returns nonzero on error. NULL = neither step is performed. */
typedef struct {
    const dw4_fight_e2p_ctx *base;
    int (*apply_down)(void *user,int slot,int32_t value);
    void *user;
} dw4_fight_status_ctx;
/* Case 7 E2PSTUNTIME. Arguments: row (enemy row), attack, damage, rank (damage rank), mahi_down (attacker's DownDataList[2], 0 if none).
 * *out: stun time, 0 when no stun roll applies or the roll fails, -1 when the roll succeeded but the time computes to 0.
 * (dw4_fight_e2p_stun_time in fightcalc.h is the same rule without the -1 mapping.) */
int dw4_fight_e2p_status_stun(const dw4_fight_e2p_ctx *,int32_t row,int32_t attack,int32_t damage,int32_t rank,int32_t mahi_down,int32_t *out);
/* Case 8 E2PPOISONTIME. mode "TIME" | "DAMAGE" | "GEDOKU" (retail strings 0x5191b8, 0x519220, 0x519228). */
int dw4_fight_e2p_status_poison(const dw4_fight_e2p_ctx *,const char *mode,int32_t attack,int32_t *out);
/* Case 9 E2PSLEEPTIME (row = enemy row of the attacker). */
int dw4_fight_e2p_status_sleep(const dw4_fight_e2p_ctx *,int32_t row,int32_t attack,int32_t *out);
/* Case 10 E2PBINDTIME. */
int dw4_fight_e2p_status_bind(const dw4_fight_e2p_ctx *,int32_t row,int32_t attack,int32_t *out);
/* Case 11 E2PATKDWNTIME, mode "TIME" | "SUBAYASA" | "MEICHURITSU". */
int dw4_fight_e2p_status_atkdown(const dw4_fight_status_ctx *,const char *mode,int32_t row,int32_t attack,int32_t *out);
/* Case 12 E2PPOWDWNTIME, mode "TIME" | "TSUYOSA" | "MAMORI". */
int dw4_fight_e2p_status_powdown(const dw4_fight_status_ctx *,const char *mode,int32_t row,int32_t attack,int32_t *out);
/* Retail tables 0x4cf5d8/e0/e8/f0: one word each, zero in the retail image. */
extern const int32_t dw4_fight_status_down_value[4];
#endif
