/* Speed / Power / Resist buff receiver of the player and enemy model work (beNDMWMdlPEBase):
 * message handler Gap::Bec::beNDMWMdlPEBase::vfunc_47 (0x445d10, messages SETSPEEDUP / SETPOWERUP
 * / SETREFRACT) and per-frame update vfunc_46 (0x443bd0), from retail disassembly. Self-
 * consistency tested only; not compared against a running game. */
#ifndef DW4_BUFFAPPLY_H
#define DW4_BUFFAPPLY_H
#include <stddef.h>
#include <stdint.h>
#include "dw4/fightmagic.h"
/* Slots of the work's _timerList (0xf8) and _isFirstList (0xfc) that the three buffs use. */
enum {DW4_BUFF_RESIST=4,DW4_BUFF_SPEED=5,DW4_BUFF_POWER=6,DW4_BUFF_SLOTS=8};
/* Slots of _upDataList (0x10c; for a player the same array as the player record's UPDATA, 11 ints; an enemy's lazily created list has 7). */
enum {DW4_UP_SUBAYASA=0,DW4_UP_CHIMEIRITSU=1,DW4_UP_MAHITEIKOU=2,DW4_UP_KAIHIRITSU=3,DW4_UP_TSUYOSA=4,DW4_UP_MAMORI=5,DW4_UP_MAXHP=6,
      DW4_UP_RES_FIRE=7,DW4_UP_RES_ICE=8,DW4_UP_RES_THUNDER=9,DW4_UP_RES_DARK=10,DW4_UP_COUNT=11};
typedef struct {
    int32_t time[DW4_BUFF_SLOTS];       /* _timerList entry: the first message integer (TIME + KASHIKOSA for Speed/Power), 0 = inactive */
    uint8_t first[DW4_BUFF_SLOTS];      /* _isFirstList entry: 1 = the named timer is (re)armed at the next update */
    int64_t start_ns[DW4_BUFF_SLOTS];   /* engine clock when the named timer was armed */
    int64_t duration_ns[DW4_BUFF_SLOTS];
    uint8_t armed[DW4_BUFF_SLOTS];      /* the named timer exists */
    int32_t up[DW4_UP_COUNT];           /* _upDataList */
    int up_count;                       /* 11 for a player, 7 for an enemy: writes past the count are skipped, as in retail */
    int is_player;                      /* _isPlayer: a player's change is followed by RECALCPLAYER and ADDHP(index, 0) */
} dw4_buffs;
void dw4_buffs_init(dw4_buffs *,int is_player);
/* Timer duration in nanoseconds of the engine clock: (int64)1e9 * time / 60 (signed 64-bit divide), i.e. `time` is in 1/60 s. */
int64_t dw4_buff_duration_ns(int32_t time);
/* The message handler (SETSPEEDUP / SETPOWERUP / SETREFRACT): `m` is the dw4_magic of fightmagic.c (kind SPEEDUP, POWERUP or REFRACT). Overwrites
 * the slot's time and UPDATA values (no stacking) and marks the timer for re-arming. Returns 1 when a player recalculation (3fab90) must follow,
 * 0 otherwise, -1 for a non-buff kind. */
int dw4_buff_apply(dw4_buffs *,const dw4_magic *m);
/* One update step (retail vfunc_46, once per call) at engine clock `now_ns`, for a work whose _isOnCtrl is `on_ctrl`: arms pending timers, expires
 * finished ones (time and UPDATA values cleared, timer removed). Returns 1 when a player recalculation must follow. */
int dw4_buff_update(dw4_buffs *,int on_ctrl,int64_t now_ns);
/* The SD message a buff cast sends to each target ("SETSPEEDUP" / "SETPOWERUP" / "SETREFRACT" with "I<time>/I<a>/..." built from the dw4_magic values; retail
 * case 20 appends the same integers to a binary PLAYER-group message handled by vfunc_47, so this text is the port's own spelling of them). In the running game the receiver is the model's dw4_status (statusapply.c), which is the single owner of
 * the timers and the record's UPDATA lists; dw4_buffs above is the reference model of the same receiver that the unit mode `buffapply` checks, and
 * `supportbuff` asserts that both produce the same time and UPDATA values. Returns 0, or -1 for a non-buff kind. */
#define DW4_BUFF_NAME_CAP 16
#define DW4_BUFF_ARGS_CAP 96
int dw4_buff_message(const dw4_magic *m,char name[DW4_BUFF_NAME_CAP],char args[DW4_BUFF_ARGS_CAP]);
/* Copy the player record's UPDATA in / out. */
int dw4_buffs_load_player(dw4_buffs *,const dw4_property_folder *);
int dw4_buffs_store_player(const dw4_buffs *,dw4_property_folder *);
#endif
