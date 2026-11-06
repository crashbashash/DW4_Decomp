#ifndef DW4_STATUSAPPLY_H
#define DW4_STATUSAPPLY_H
#include <stdint.h>
#include <stddef.h>
#include "dw4/arena.h"

/* Per-model status state: the part of beNDMWMdlPEBaseInfoWork that the retail status manager keeps
 * for one enemy or player model (_timerList, _isFirstList, _poisonDamage, _poisonEndurance,
 * _downDataList, _upDataList, icon slots) and the per-frame rules of beNDMWMdlPEBase::vfunc_46
 * (0x443bd0, tick) and vfunc_47 (0x445d10, SETxxx / CHECKSTATUS / CLEARSTATUS / ALLCLEARSTATUS
 * messages). The state has no knowledge of damage formulas: the caller (the hit script's MDLsetSD
 * / MDLsetSeq / MDLisStatus) passes the already computed times. */

/* Index into the timer list == the status enum (0x4ca9a0): the same numbers key _timerList and the CHECKSTATUS names. */
enum {
    DW4_STATUS_POISON=0, DW4_STATUS_ATTACKDOWN=1, DW4_STATUS_POWERDOWN=2, DW4_STATUS_BIND=3, DW4_STATUS_REFRACT=4,
    DW4_STATUS_SPEEDUP=5, DW4_STATUS_POWERUP=6, DW4_STATUS_METAL=7, DW4_STATUS_SLEEP=8, DW4_STATUS_STUN=9, DW4_STATUS_RARE=10,
    DW4_STATUS_FRAME=11,        /* not a status: timer[11] mirrors "any of statuses 0..7 is shown" and keys the icon frame */
    DW4_STATUS_TIMER_SLOTS=12
};
/* _downDataList slots (value > 0 lowers the holder's stat; the readers are the P2E/E2P rules in fightcalc.c / fightstatus_*.c). */
enum {
    DW4_DOWN_SUBAYASA=0, DW4_DOWN_CRITICAL=1 /* CHIMEIRITSU */, DW4_DOWN_PARALYSIS=2 /* MAHIRITSU */, DW4_DOWN_EVASION=3 /* KAIHIRITSU */,
    DW4_DOWN_ATTACK=4 /* TSUYOSA */, DW4_DOWN_DEFENSE=5 /* MAMORI */
};
#define DW4_STATUS_DOWN_ENEMY 6   /* the list retail allocates for a non-player model (0x4456c0: resize to 6) */
#define DW4_STATUS_UP_ENEMY 7     /* _upDataList for a non-player model (0x445990: resize to 7) */
#define DW4_STATUS_DOWN_SLOTS 7   /* capacity: a player aliases the record's DOWNDATA (7 entries, playerstats.c) ... */
#define DW4_STATUS_UP_SLOTS 11    /* ... and UPDATA (11 entries) */
#define DW4_STATUS_FPS 60         /* timer values are frames: duration = value * 1e9 / 60 ns (0x22e4b8 is the signed 64-bit divide) */
#define DW4_STATUS_POISON_PERIOD_NS 2000000000LL   /* 0x77359400, the POISON named timer */

typedef struct {
    uint8_t armed;
    int64_t start_ns, duration_ns;
} dw4_status_clock;

typedef struct {
    uint8_t is_player;           /* _isPlayer (+0xec) */
    uint8_t ready;               /* InfoWork+0x44, the guard byte of every block of vfunc_46 (set by code not recovered; init sets 1) */
    int32_t timer[DW4_STATUS_TIMER_SLOTS];   /* _timerList; non-zero == the status is set (CHECKSTATUS / MDLisStatus) */
    uint8_t first[DW4_STATUS_TIMER_SLOTS];   /* _isFirstList (11 entries in retail): 1 until the tick has armed the status' named timer */
    int32_t poison_damage;       /* _poisonDamage (+0x100): HP lost per poison tick */
    int32_t poison_endurance;    /* _poisonEndurance (+0x104): stored from the third SETPOISON argument; no reader recovered */
    int has_down, has_up;        /* lists exist (retail allocates them lazily on the first stat-changing status) */
    int32_t down[DW4_STATUS_DOWN_SLOTS];
    int32_t up[DW4_STATUS_UP_SLOTS];
    int32_t down_count, up_count;           /* writes past the count are dropped, exactly as in retail: 6/7 for an enemy, 7/11 for a player */
    uint8_t lists_dirty;         /* a list value changed since the last load/store (the player-record mirror writes the record when set) */
    int64_t clock_ns;            /* the engine clock the named timers compare against */
    dw4_status_clock named[DW4_STATUS_TIMER_SLOTS];
    int32_t icon_position[DW4_STATUS_TIMER_SLOTS];   /* _dispPosNoList: slot in the row of icons, -1 when never shown */
    int8_t icon_shown[DW4_STATUS_TIMER_SLOTS];       /* 1 when the tick keeps an icon for the status (retail: _dispRamNoList != -1) */
} dw4_status;

typedef struct {
    int32_t poison_damage_taken;  /* HP the poison tick removed (after the clamp at 0 and the enemy floor of 1) */
    int poison_ticks;             /* 0 or 1 */
    int killed;                   /* a player was poisoned to 0 HP: retail sends SQ_DEAD */
    int recalc_player;            /* a stat list changed on a player: retail runs GAMERAM RECALCPLAYER (0x445c60) */
    uint32_t expired;             /* bit n set when status n ended this tick */
    const char *sequence;         /* last sequence the manager asked for ("SQ_SLEP", "SQ_WAIT", "SQ_DEAD"), or NULL */
} dw4_status_tick_result;

void dw4_status_init(dw4_status *,int is_player);
/* Player-record mirror: a player's lists live in its game-RAM record (DOWNDATA 7 entries, UPDATA 11), not in the status. `load` copies both
 * into the status (and marks them present), `store` copies them back out and clears lists_dirty. NULL list pointers are skipped. */
void dw4_status_load_lists(dw4_status *,const int32_t down[DW4_STATUS_DOWN_SLOTS],const int32_t up[DW4_STATUS_UP_SLOTS]);
void dw4_status_store_lists(dw4_status *,int32_t down[DW4_STATUS_DOWN_SLOTS],int32_t up[DW4_STATUS_UP_SLOTS]);

/* The SETxxx messages of vfunc_47 (frames are the already computed times of the hit script). Return 0, or -1 for an unusable state. */
int dw4_status_set_poison(dw4_status *,int32_t frames,int32_t damage,int have_endurance,int32_t endurance); /* timer = frames/120 + 1 two-second ticks */
int dw4_status_set_sleep(dw4_status *,int32_t frames);
int dw4_status_set_stun(dw4_status *,int32_t frames);
int dw4_status_set_bind(dw4_status *,int32_t frames);
int dw4_status_set_attack_down(dw4_status *,int32_t frames,int32_t subayasa,int32_t critical,int32_t paralysis,int32_t evasion);
int dw4_status_set_power_down(dw4_status *,int32_t frames,int32_t attack,int32_t defense);
int dw4_status_set_speed_up(dw4_status *,int32_t frames,int32_t a0,int32_t a1,int32_t a2,int32_t a3);   /* up[0..3] */
int dw4_status_set_power_up(dw4_status *,int32_t frames,int32_t a0,int32_t a1,int32_t a2);              /* up[4..6] */
int dw4_status_set_refract(dw4_status *,int32_t frames,int32_t a0,int32_t a1,int32_t a2,int32_t a3);    /* up[7..10]: dropped for a 7-entry list */
int dw4_status_set_rare_icon(dw4_status *,int32_t rank);
/* Message by name with the "I<n>/I<n>/..." argument string of MDLsetSD (SETPOISON, SETSLEEP, SETSTUN, SETBIND, SETATTACKDOWN, SETPOWERDOWN,
 * SETSPEEDUP, SETPOWERUP, SETREFRACT, SETRAREICON, CLEARSTATUS, ALLCLEARSTATUS). 0 = handled, 1 = not a status message, -1 = bad arguments. */
int dw4_status_message(dw4_status *,const char *name,const char *args,dw4_status_tick_result *out);

/* CHECKSTATUS: 1 when the timer of the named status ("POISON", "ATTACKDOWN", ..., "RARE") is non-zero; -1 for an unknown name. */
int dw4_status_check(const dw4_status *,const char *name);
int dw4_status_is_set(const dw4_status *,int status);
/* 4445a8: stop every movement channel except Y unless the current sequence
 * belongs to the damage enum. Call after control/AI and status expiry, before
 * movement, on active unfrozen PE models. Reads/writes the actual Work list. */
void dw4_status_bind_movement(dw4_arena *,dw4_handle work);
int dw4_status_id(const char *name);
const char *dw4_status_name(int status);
/* The value a fight rule reads (_downDataList[slot]); 0 when the list does not exist or the slot is outside it. */
int32_t dw4_status_down(const dw4_status *,int slot);
int32_t dw4_status_up(const dw4_status *,int slot);
/* Cure's poison removal (FUN_00447b40: FUN_003a8580 removes the POISON named timer and `_timerList[0]` takes the word at 0x4cfe80, 0 in the ELF
 * image and never found written, so the timer slot is cleared: an ASSUMPTION about the run-time value). Returns 1 when poison was set and is now
 * cleared, 0 when it was not set. */
int dw4_status_cure_poison(dw4_status *);
/* FUN_003a7e90, the named-timer completion test: a timer that does not exist reads complete,
 * otherwise `duration < elapsed` (strict) with both clock samples first truncated to 2^18 ns
 * steps. The Bind / Speed / Power / Resist blocks of the tick use it; the other statuses still
 * compare unquantised. */
int dw4_status_timer_complete(int armed,int64_t start_ns,int64_t duration_ns,int64_t now_ns);
/* CLEARSTATUS (sleep, stun and bind, then SQ_WAIT) and ALLCLEARSTATUS (every timed status and both lists). */
void dw4_status_clear_basic(dw4_status *,dw4_status_tick_result *out);
void dw4_status_clear_all(dw4_status *,dw4_status_tick_result *out);

/* Adapter for the `apply_down` hook of dw4_fight_status_ctx (fightstatus_e2p.h): `user` is the dw4_status. Writes _downDataList[slot], creating the list. */
int dw4_status_apply_down_slot(void *user,int slot,int32_t value);

/* The sequence-change hook of the model class (FUN_00445200, vtable slot 44 of beNDMWMdlEnemy / beNDMWMdlPlayer, run after every by-name
 * sequence set and every JUMP): `new_sequence` is the sequence the model just entered, `hp` its HP. KO (hp 0): every timer and icon is
 * cleared. Otherwise a set SLEEP ends unless the new sequence is "SQ_SLEP"; a set STUN turns an "SQ_WAIT" into "SQ_STUN" (out->sequence), is left
 * alone by "SQ_STUN" and ends for any other sequence. Needs no clock; the tick arms and expires the timers. */
void dw4_status_sequence_changed(dw4_status *,const char *new_sequence,int32_t hp,dw4_status_tick_result *out);

/* One frame of vfunc_46: advance the clock by `dt_ns`, run the blocks in retail order (poison, sleep, stun, bind, attack-down, power-down,
 * speed-up, power-up, refract) and refresh the icon slots. `sequence` is the model's current sequence name (the STUN block runs only while it
 * is "SQ_STUN"; SLEEP asks for "SQ_SLEP" unless it is already current). `*hp` is the model's current HP, changed by poison. A model whose
 * HP is 0 loses every timer (the KO branch at 0x443cf8). */
void dw4_status_tick(dw4_status *,int64_t dt_ns,const char *sequence,int32_t *hp,dw4_status_tick_result *out);
#endif
