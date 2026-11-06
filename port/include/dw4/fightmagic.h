/* Player technique support rules of FIGHTCALC (GAMERAM command FIGHTCALC): P2PKOUKAMAGIC (source
 * case 20: healing, curing, reviving and the Speed / Power / Resist buffs) and GETPATKZOKUSEI
 * (case 21: the attacker's element), ported from beNDMWGameRam::vfunc_34. The messenger sends
 * (area queries, buff/raise receivers, effect particles) are not ported: the outputs are the
 * integers the source appends to the SET*UP / RAISE messages. */
#ifndef DW4_FIGHTMAGIC_H
#define DW4_FIGHTMAGIC_H
#include "dw4/fightcalc.h"
/* GETPATKZOKUSEI: the attacker's element, 0 fire / 1 ice / 2 thunder / 3 dark / 4 poison, -1 none. A technique attack (attack / 10000 == 4) uses the
 * player's learned technique row's ZOKUSEI string; any other attack the player's ATTACKZOKUSEI property. -1 return: missing data. */
int dw4_fight_attack_element(const dw4_fight_ctx *,int32_t attack,int32_t *element);
typedef enum {DW4_MAGIC_NONE=0,DW4_MAGIC_HEAL,DW4_MAGIC_CURE,DW4_MAGIC_RAISE,DW4_MAGIC_SPEEDUP,DW4_MAGIC_POWERUP,DW4_MAGIC_REFRACT} dw4_magic_kind;
typedef struct {
    dw4_magic_kind kind;
    int32_t row;        /* the learned technique's pcTech row */
    int self;           /* the caster is affected directly, before the area list */
    int area;           /* the players found by the PLAYER area query (retail: around the caster's GETMATRIX) are affected too */
    int area_has_caster;/* the area list gets the caster appended (buffs); for Heal/Cure the caster is handled by `self` */
    int nv;             /* values used */
    int32_t v[5];       /* the integers appended to the message, in order. HEAL v[0] = HP delta; CURE v[0] = cure chance numerator (row - base + 5, minus the
                         * target's poison endurance, tested against rand % 10); RAISE v[0..1]; SPEEDUP time, speed, CHIMEIRITSU, MHIRITSU, KAIHIRITSU;
                         * POWERUP time, TSUYOSA, MAMORI, MAXHP; REFRACT time, FIRE, ICE, THUNDER, DARK */
} dw4_magic;
/* P2PKOUKAMAGIC: `target` is the second message argument (the retail work does nothing unless it equals `caster`); `attack` the attack number
 * (attack % 10000 selects the technique family: 40 Heal Lt, 45 Heal, 55 Cure Lt, 60 Cure, 50 Raise (-50: the item version), 65 Speed, 75 Resist, 80 Power).
 * kind NONE when gated off or not a support technique. No random draw happens here. Returns -1 on missing data. */
int dw4_fight_p2p_magic(const dw4_fight_ctx *,int32_t caster,int32_t target,int32_t attack,dw4_magic *out);
/* FUN_003f9c80 (HP gauge): HP += delta clamped to 0..MHP; a dead player (HP 0) is left alone. Returns 1 when applied, 0 when the player was dead, -1 error. */
int dw4_fight_apply_hp(dw4_property_folder *player,int32_t delta);
/* Poison cure for one poisoned target (FUN_00447b00 true): one draw `rand % 10` (consumed per poisoned target, in list order); cured when
 * v[0] - poison_endurance >= draw. */
int dw4_fight_p2p_cure_poison(const dw4_fight_ctx *,const dw4_magic *,int32_t poison_endurance,int *cured);
#endif
