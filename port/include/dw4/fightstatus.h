/* Player-to-enemy status-time rules of the FIGHTCALC switch (GAMERAM command FIGHTCALC, FightCom P2EPOISONTIME, P2ESLEEPTIME, P2EBINDTIME,
 * P2EATKDWNTIME, P2EPOWDWNTIME), ported from src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp (cases 15-19 of the second switch). The
 * context is the one of fightcalc.h; `tech` (pcTech) is required. All take the attack number (the technique's base number is
 * attack % 10000) and find the pcTech row through the player's WAZALIST. Time results are frames; -1 = no status applied (chance draw failed).
 * Not compared against retail; the formulas are the matched source's. docs/combat.md, "Status times". */
#ifndef DW4_FIGHTSTATUS_H
#define DW4_FIGHTSTATUS_H
#include "dw4/fightcalc.h"
/* P2ESTUNTIME (case 14) has NO technique branch in the source: the one formula of dw4_fight_p2e_stun_time covers every attack class.
 *
 * The `what` selector of poison / attack-down / power-down is the column the script asks for: "TIME" runs the chance draw and returns the
 * duration (or -1); poison with any other value returns -(pcTech HP / 5) (damage per tick, no draw); attack-down accepts "SUBAYASA",
 * "CHIMEIRITSU", "MAHIRITSU", "KAIHIRITSU" and power-down "TSUYOSA", "MAMORI" (no draw). Return value 0 = *out set, 1 = the selector matched
 * nothing (retail leaves the reply empty; *out untouched), -1 = missing data / zero divisor. */
int dw4_fight_p2e_poison_time(const dw4_fight_ctx *,int32_t row,int32_t attack,const char *what,int32_t *out);
int dw4_fight_p2e_sleep_time(const dw4_fight_ctx *,int32_t row,int32_t attack,int32_t *out);
int dw4_fight_p2e_bind_time(const dw4_fight_ctx *,int32_t row,int32_t attack,int32_t *out);
int dw4_fight_p2e_atkdwn_time(const dw4_fight_ctx *,int32_t row,int32_t attack,const char *what,int32_t *out);
int dw4_fight_p2e_powdwn_time(const dw4_fight_ctx *,int32_t row,int32_t attack,const char *what,int32_t *out);
#endif
