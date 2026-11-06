/* beTargetObj keeps the positions of the players and enemies (and the players' RAM numbers) as
 * three reflected lists; slot 27 empties all of them (_playerPosList and _enemyPosList are
 * igVec3fList, _playerRamNoList is igIntList). */
#include "dw4/reflected.h"
extern int g_beTargetObj_metaObject[4];

/* Slot 24, empty override. */
void Gap__Bec__beTargetObj__vfunc_24(void)
{
}

/* Slot 25, empty override returning 0. */
int Gap__Bec__beTargetObj__vfunc_25(void) {
    return 0;
}

void Gap__Bec__beTargetObj__vfunc_27(beTargetObj *self) {
    ((igVec3fList *)self->_playerPosList)->_count = 0;
    ((igIntList *)self->_playerRamNoList)->_count = 0;
    ((igVec3fList *)self->_enemyPosList)->_count = 0;
}

int Gap__Bec__beTargetObj__vfunc_20(void)
{
    return g_beTargetObj_metaObject[0];
}
