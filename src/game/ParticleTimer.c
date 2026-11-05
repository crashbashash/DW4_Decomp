/* src/game/ParticleTimer.c — the ParticleTimer methods
 *
 * One translation unit: 3 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern int g_ParticleTimer_metaObject_0058a0a0[4];

/* 0x001e3120 */
void Gap__Bec__ParticleTimer__vfunc_36(ParticleTimer *a0, int a1)
{
    a0->_trigger = a1;
}

/* 0x001e3140 */
int Gap__Bec__ParticleTimer__vfunc_34(void)
{
    return 1;
}

/* 0x003a4920 */
int Gap__Bec__ParticleTimer__vfunc_20(void)
{
    return g_ParticleTimer_metaObject_0058a0a0[0];
}
