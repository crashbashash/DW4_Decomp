/* src/lua/combat.c: the combat half of the Lua BLT/BLP script API.
 *
 * Each BLT* (bullet-versus-target, player attacks enemy) and BLP* (enemy
 * attacks player) helper is a thin caller of the native FIGHTCALC object:
 * it selects the GAMERAM message group, appends a command key and the cached
 * MDL/bullet fields as arguments, dispatches, and reads the answer back
 * (docs/systems/combat-lua-api.md).  The damage formulas live in the
 * FIGHTCALC callback, not here (docs/systems/combat-damage.md).
 *
 * 13 functions in retail address order.  The matching build splits a
 * function back out with tools/units.py, so `make check` still verifies one
 * function at a time. */

/* Attack codes.  The cached bullet kind is divided by 10000 to get its group;
 * group 4 marks a technique (docs/systems/combat-damage.md, P2EISCRITICAL). */
#define BULLET_KIND_GROUP_SIZE 10000
#define BULLET_KIND_TECHNIQUE_GROUP 4
/* Groups 2 and 3 raise a low damage rank by one (BLTgetDamageRank). */
#define BULLET_KIND_RANK_BONUS_GROUP_A 2
#define BULLET_KIND_RANK_BONUS_GROUP_B 3
/* BLTgetDamageRank: damage / max HP above these fractions gives rank 2 and 1. */
#define DAMAGE_RANK2_FRACTION 0.5f
#define DAMAGE_RANK1_FRACTION 0.25f
/* BLTisPlayerBullet accepts kinds below 1000, 10000..59999 and
 * 80000..89999 (docs/systems/combat-lua-api.md). */
#define PLAYER_BULLET_WEAPON_END 1000
#define PLAYER_BULLET_RANGE_A_END 60000
#define PLAYER_BULLET_RANGE_B_BEGIN 80000
#define PLAYER_BULLET_RANGE_B_END 90000
/* Required bulletKind % 10000 for each status-timer helper; any other attack
 * returns 0 without messaging (docs/systems/combat-lua-api.md, timer table). */
#define BULLET_SUBKIND_POISON 0x14
#define BULLET_SUBKIND_ATTACK_DOWN 0x46
#define BULLET_SUBKIND_POWER_DOWN 0x55
#define BULLET_SUBKIND_SLEEP 0x5A
#define BULLET_SUBKIND_BIND 0x5F

extern "C" {
void beMessenger_AppendInt(int, int);
void beMessenger_AppendObject(int, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_DispatchSelected(int, const char *);
int beMessenger_GetBool(int, int);
int beMessenger_GetObject(int, int);
int beMessenger_GetObjectCount(int);
void beMessenger_SelectGroup(int, const char *);
void beMessenger_SendNamed(int, const char *, int, int, const char *);
int beMessenger_GetInt(int, int);

/* Strings the messenger is addressed with: the GAMERAM group, the FIGHTCALC
 * receiver, and the ENEMY / GETPEBASEWORK pair used to fetch a named
 * object's base work (data/strings.json). */
extern char GAMERAM[];
extern char ENEMY[];
extern char GETPEBASEWORK[];
extern char FIGHTCALC[];
/* FIGHTCALC command keys (docs/systems/combat-inventory.md, switch commands):
 * P2E* = player to enemy, E2P* = enemy to player. */
extern char P2EISHITCHECK[];
extern char P2EDAMAGE[];
extern char P2EPOISONTIME[];
extern char P2ESLEEPTIME[];
extern char P2EBINDTIME[];
extern char P2EATKDWNTIME[];
extern char P2EPOWDWNTIME[];
extern char E2PDAMAGE[];
extern char E2PDAMAGERANK[];
extern char E2PSTUNTIME[];

/* The MDL / bullet cache block at 0x0058a1c0..0x0058a340
 * (docs/engine/game-state.md). */
/* Main game object, a Gap::Bec::beMessenger (finding #415). */
extern int g_beMessenger[4];
/* Focused Digimon model entity. */
extern int g_mdlEntity[4];
extern int g_mdlRamNo[4];
extern int g_mdlMaxHp[4];
extern int g_mdlInfoName[4];
/* g_mdlRecNo, g_mdlBulletKind (the attack code, see
 * BULLET_KIND_GROUP_SIZE above) and g_bltShootRamNo are declared
 * inside each function: the status-timer helpers read them as unsigned,
 * the others as int, and the two declarations must not meet in one scope. */
/* BLP/BLT status fields (docs/engine/game-state.md lists them only as
 * "status field"); passed through to FIGHTCALC as arguments. */
extern int g_statusFieldA[4];
extern int g_blpStatus[4];
/* Results cached by the damage wrappers from the FIGHTCALC reply
 * (docs/systems/combat-lua-api.md): damage, attribute index (into
 * g_attributeNames), and the flag the damage-rank helpers use to
 * raise a zero rank to one. */
extern int g_damageResult[4];
extern int g_attackZokusei[4];
extern int g_damageFlag[4];
/* Attribute names: "common" (fallback for an out-of-range index) at 0x004c8800
 * and "fire", "ice", "thunder", "dark" at 0x004c8804..0x004c8810 (pointers to
 * strings at 0x0050de18..0x0050de38). */
extern char *g_attributeNameDefault[4];
extern char *g_attributeNames[4];
int BLTisPlayerBullet(void);
int BLTisHitCheck(void);
int BLTgetDamageValue(int criticalFlag);
int BLTgetDamageRank(int currentHp, int rankBonus);
char *BLTgetAttributeStr(void);
int BLTgetPoisonTime(const char *effectKey);
int BLTgetSleepTime(void);
int BLTgetBindTime(void);
int BLTgetAttackDownTime(const char *effectKey);
int BLTgetPowerDownTime(const char *effectKey);
int BLPgetDamageValue(void);
int BLPgetDamageRank(int scriptArg1, int scriptArg2);
int BLPgetStunTime(int scriptArg1, int scriptArg2);
}

/* 0x00374800: is the cached attack code a player bullet?  True below 1000,
 * for 10000..59999 and for 80000..89999.  The cached code is signed and not
 * range-checked, so a negative code also counts (docs/systems/combat-lua-api.md). */
int BLTisPlayerBullet(void) {
    extern int g_mdlBulletKind[4];
    if (g_mdlBulletKind[0] < BULLET_KIND_GROUP_SIZE) {
        if (g_mdlBulletKind[0] < PLAYER_BULLET_WEAPON_END) {
            return 1;
        }
        /* shape kept for the match: the early return and this jump are not
         * interchangeable with a plain `return 0` */
        goto notPlayerBullet;
    }
    if (g_mdlBulletKind[0] < PLAYER_BULLET_RANGE_A_END) {
        return 1;
    }
    if ((g_mdlBulletKind[0] >= PLAYER_BULLET_RANGE_B_BEGIN) && (g_mdlBulletKind[0] < PLAYER_BULLET_RANGE_B_END)) {
        return 1;
    }
notPlayerBullet:
    return 0;
}

/* 0x00374890: ask FIGHTCALC (P2EISHITCHECK) whether the cached player attack
 * hits.  When an InfoName is cached, the named ENEMY object's base work
 * (GETPEBASEWORK reply, index 1) is passed to FIGHTCALC as an object argument. */
int BLTisHitCheck(void) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    int baseWork;

    baseWork = 0;
    if (g_mdlInfoName[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_mdlInfoName[0], g_mdlRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EISHITCHECK);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

/* 0x00374a40: P2EDAMAGE.  The Lua caller supplies the critical flag (masked to
 * 8 bits; docs/systems/combat-damage.md, arg3).  The reply's three integers
 * (damage, attribute index, rank flag) are cached for BLTgetDamageRank and
 * BLTgetAttributeStr, and the damage is returned. */
int BLTgetDamageValue(int criticalFlag) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    int baseWork;

    baseWork = 0;
    if (g_mdlInfoName[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_mdlInfoName[0], g_mdlRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EDAMAGE);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], criticalFlag & 0xFF);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_damageResult[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 1);
    g_damageFlag[0] = beMessenger_GetInt(g_beMessenger[0], 2);
    return g_damageResult[0];
}

/* 0x00374bb0: damage rank 0..3 of the last BLTgetDamageValue result.  `currentHp`
 * is what the script passes (BLTgetDamageRank(MDLgetHp(), ...) in
 * lua/11-bosses/04-boss04-devimon-1_e751/017-boss-devl1e.lua); a
 * nonpositive value is rank 3.  Otherwise the damage / max-HP fraction picks
 * rank 2 above one half, rank 1 above one quarter, else 0.  A rank of 0 or 1
 * is raised by one when the cached rank flag is 1 (rank 0 only), when
 * `rankBonus` is set, or for attack groups 2 and 3
 * (docs/systems/combat-lua-api.md).  The comparisons stay negated as in retail. */
int BLTgetDamageRank(int currentHp, int rankBonus) {
    extern int g_mdlBulletKind[4];
    float damageFraction;
    int group;
    int rank;

    if (currentHp <= 0) {
        return 3;
    }
    rank = 0;
    damageFraction = (float) g_damageResult[0] / (float) g_mdlMaxHp[0];
    if (!(damageFraction <= DAMAGE_RANK2_FRACTION)) {
        rank = 2;
    } else if (!(damageFraction <= DAMAGE_RANK1_FRACTION)) {
        rank = 1;
    }
    if ((rank == 0) && (g_damageFlag[0] == 1)) {
        return rank + 1;
    }
    if ((rank == 0) || (rank == 1)) {
        if (rankBonus != 0) {
            return rank + 1;
        }
        group = (int)((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE);
        if ((group == BULLET_KIND_RANK_BONUS_GROUP_A) || (group == BULLET_KIND_RANK_BONUS_GROUP_B)) {
            rank += 1;
        }
    }
    return rank;
}

/* 0x00374cc0: name of the cached damage attribute ("fire", "ice", "thunder",
 * "dark"); any index of 4 or more gives "common".  Scripts build the
 * "SQ_LDMG/<attribute>" sequence label from it. */
char *BLTgetAttributeStr(void)
{
    if (g_attackZokusei[0] >= 4)
        return g_attributeNameDefault[0];
    return g_attributeNames[g_attackZokusei[0]];
}

/* The five BLTget*Time helpers share one shape: only a technique attack (group
 * 4) of the matching sub-kind carries the status effect; otherwise 0 without
 * messaging.  Then the matching P2E*TIME command is sent to FIGHTCALC with the
 * cached arguments and its first integer is the duration
 * (docs/systems/combat-lua-api.md).  Poison, attack-down and power-down also
 * pass the script's `effectKey` string. */

/* 0x00374de0: poison duration (P2EPOISONTIME). */
int BLTgetPoisonTime(const char *effectKey) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POISON) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EPOISONTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* 0x00374f00: sleep duration (P2ESLEEPTIME). */
int BLTgetSleepTime(void) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_SLEEP) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESLEEPTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* 0x00375010: bind duration (P2EBINDTIME). */
int BLTgetBindTime(void) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_BIND) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EBINDTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* 0x00375120: attack-down duration (P2EATKDWNTIME). */
int BLTgetAttackDownTime(const char *effectKey) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_ATTACK_DOWN) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EATKDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* 0x00375240: power-down duration (P2EPOWDWNTIME). */
int BLTgetPowerDownTime(const char *effectKey) {
    extern int g_mdlRecNo[4];
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POWER_DOWN) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EPOWDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* 0x00375540: E2PDAMAGE, the enemy-to-player counterpart of BLTgetDamageValue.
 * Same caching of the reply (damage, attribute, rank flag); the argument
 * order differs from the P2E command (docs/systems/combat-lua-api.md). */
int BLPgetDamageValue(void) {
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    int baseWork;

    baseWork = 0;
    if (g_statusFieldA[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_statusFieldA[0], g_bltShootRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PDAMAGE);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_damageResult[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 1);
    g_damageFlag[0] = beMessenger_GetInt(g_beMessenger[0], 2);
    return g_damageResult[0];
}

/* 0x00375730: E2PDAMAGERANK.  The reply's rank is raised from 0 to 1 when the
 * cached rank flag from the last E2PDAMAGE is 1.  The two integers are the
 * script's arguments, appended unchanged (by analogy with BLTgetDamageRank
 * they are probably the current HP and a rank bonus; no Lua caller found). */
int BLPgetDamageRank(int scriptArg1, int scriptArg2) {
    extern int g_mdlBulletKind[4];
    int rank;

    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PDAMAGERANK);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg1);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg2);
    beMessenger_AppendObject(g_beMessenger[0], g_mdlEntity[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    rank = beMessenger_GetInt(g_beMessenger[0], 0);
    if ((rank == 0) && (g_damageFlag[0] == 1)) {
        rank += 1;
    }
    return rank;
}

/* 0x00375830: E2PSTUNTIME.  `scriptArg1`/`scriptArg2` are appended unchanged
 * (no Lua caller found to name them); the reply's first integer is the stun
 * duration. */
int BLPgetStunTime(int scriptArg1, int scriptArg2) {
    extern int g_mdlBulletKind[4];
    extern int g_bltShootRamNo[4];
    int baseWork;

    baseWork = 0;
    if (g_statusFieldA[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_statusFieldA[0], g_bltShootRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PSTUNTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg1);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg2);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}
