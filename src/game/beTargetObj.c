/* src/game/beTargetObj.c — the beTargetObj methods
 *
 * beTargetObj keeps the positions of the players and enemies (and the players' RAM
 * numbers) as three reflected lists; slot 27 empties all of them
 * (docs/engine/typed-game-layer.md: _playerPosList / _enemyPosList are igVec3fList,
 * _playerRamNoList is igIntList).
 *
 * One translation unit: 4 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern int g_beTargetObj_metaObject_00587ce8[4];

/* 0x003a5a60: slot 24, empty override. */
void Gap__Bec__beTargetObj__vfunc_24(void)
{
}

/* 0x003a5a70: slot 25, empty override returning 0. */
int Gap__Bec__beTargetObj__vfunc_25(void) {
    return 0;
}

/* 0x003a5b20: slot 27, empty the player-position, player-RAM-number and
 * enemy-position lists by zeroing each list's element count. */
void Gap__Bec__beTargetObj__vfunc_27(beTargetObj *self) {
    ((igVec3fList *)self->_playerPosList)->_count = 0;
    ((igIntList *)self->_playerRamNoList)->_count = 0;
    ((igVec3fList *)self->_enemyPosList)->_count = 0;
}

/* 0x003a6940: slot 20, MetaObject return (class handle at 0x00587ce8). */
int Gap__Bec__beTargetObj__vfunc_20(void)
{
    return g_beTargetObj_metaObject_00587ce8[0];
}
