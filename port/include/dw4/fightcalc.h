/* Player-to-enemy FIGHTCALC rules (GAMERAM command FIGHTCALC, FightCom P2EISHITCHECK,
 * P2EISCRITICAL, P2EDAMAGE, P2EEXPUP), ported from beNDMWGameRam::vfunc_34 (cases 1, 2, 5, 6 of
 * the FIGHTCALC switch). Weapon hits and, with `tech` set, technique hits (attack number / 10000
 * == 4: the player's WAZALIST row, its element and skill). Every random draw uses the one engine
 * stream as retail (`next % n`, unsigned). */
#ifndef DW4_FIGHTCALC_H
#define DW4_FIGHTCALC_H
#include "dw4/playerrecords.h"
#include "dw4/database.h"
#include "dw4/random.h"
typedef struct {
    dw4_property_folder *player;   /* the attacker's GETPLAYER folder */
    dw4_dbtable enemy;             /* the `enemy` table (typed beDataBase in the owner's arena) */
    dw4_random *rng;
    dw4_dbtable tech;              /* the `pcTech` table: needed for technique attacks (attack number / 10000 == 4), invalid (zero) otherwise */
} dw4_fight_ctx;
/* The target's active status data read by the rules: the first entry of its _downDataList (retail work +0xc..), zero when none. */
typedef struct {int32_t evasion_down,defense_down;} dw4_fight_down;
typedef struct {int32_t damage,element;int high_roll;} dw4_fight_damage;
/* P2EISHITCHECK: 0 miss / 1 hit, -1 on an unsupported attack class or missing data. */
int dw4_fight_p2e_is_hit(const dw4_fight_ctx *,int32_t row,int32_t attack,dw4_fight_down down,int *hit);
/* P2EISCRITICAL */
int dw4_fight_p2e_is_critical(const dw4_fight_ctx *,int32_t row,int32_t attack,int *critical);
/* P2EDAMAGE */
int dw4_fight_p2e_damage(const dw4_fight_ctx *,int32_t row,int32_t attack,int critical,dw4_fight_down down,dw4_fight_damage *out);
/* P2ESTUNTIME (case 14): stun duration (0 when the draw fails). */
int dw4_fight_p2e_stun_time(const dw4_fight_ctx *,int32_t row,int32_t max_hp,int32_t damage,int32_t *time);
/* P2EEXPUP (case 6): EXP for every joined living player below level 999, split by the session's player count; the attacker's share is
 * returned. A level up (EXP >= NEXTEXP, repeated while still above, up to 999) raises LEVEL, recalculates the record with the equipment-applying FUN_003fab90 rule and refills HP and MP
 * to their new maxima; retail also runs FUN_003f8760 (not ported) and queues the level-up display messages. The *level-up count is added to the return value's sign: returns 0 on success, -1 on error. */
int dw4_fight_p2e_expup(dw4_playerrecords *records,const dw4_databases *databases,int32_t row,int32_t attacker,int32_t *share);
/* Enemy-to-player rules (FightCom E2PISHITCHECK, E2PDAMAGE, E2PDAMAGERANK; source cases 0, 3, 4). The attack number selects the `eneatk`
 * row (attack % 10000). `player` is the TARGET's GETPLAYER folder. */
typedef struct {dw4_property_folder *player;dw4_dbtable enemy,eneatk;dw4_random *rng;} dw4_fight_e2p_ctx;
/* The attacking enemy's first _downDataList entry: [1] lowers its critical chance, [4] its strength; zero without a status. */
typedef struct {int32_t critical_down,attack_down;} dw4_fight_e2p_down;
int dw4_fight_e2p_is_hit(const dw4_fight_e2p_ctx *,int32_t row,int32_t attack,int *hit);
int dw4_fight_e2p_damage(const dw4_fight_e2p_ctx *,int32_t row,int32_t attack,dw4_fight_e2p_down down,dw4_fight_damage *out);
/* hp = the player's HP after the hit; one_flag = the ONE flag of the retail work object (meaning unknown, 0 in the port). */
int dw4_fight_e2p_damage_rank(const dw4_fight_e2p_ctx *,int32_t attack,int32_t hp,int32_t damage,int one_flag,int32_t *rank);
/* E2PSTUNTIME (source case 7): stun frames for a hit of `damage` at damage rank `rank` (only ranks 1 and 2 can stun a physical hit). `mahi_down` is
 * the attacking enemy's _downDataList[2]. */
int dw4_fight_e2p_stun_time(const dw4_fight_e2p_ctx *,int32_t row,int32_t attack,int32_t damage,int32_t rank,int32_t mahi_down,int32_t *time);
/* 1 when the attack row carries a status effect (eneatk KOUKA not empty): its sleep/bind/attack-down/power-down/poison times are in fightstatus_e2p.h. */
int dw4_fight_e2p_has_effect(const dw4_fight_e2p_ctx *,int32_t attack);
/* P2ESKILLUP (BLTcalcSkillUp): after a hit the weapon skill rises by one with the table chance while it is below the level cap, and the record is recalculated. Returns 1 when
 * the skill rose (*raised = its index), 0 when it did not, -1 on missing data. One draw (rand % 100000) is consumed exactly when the skill is below the cap. Technique attacks
 * (class 4/8/9) use the technique row's SKILL index and a flat table chance. */
int32_t dw4_fight_skillup_cap(int32_t level);
int dw4_fight_p2e_skillup(dw4_playerrecords *,const dw4_databases *,dw4_random *,int32_t shooter,int32_t attack,int crit,int32_t *raised);
#endif
