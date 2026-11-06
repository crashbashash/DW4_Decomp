/* src/game/ParticleArray.c — the ParticleArray methods
 *
 * One translation unit: 4 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

#include "dw4/reflected.h"
extern int g_ParticleArray_metaObject[4];

/* 0x0015c830 */
int Gap__Bec__ParticleArray__vfunc_30(ParticleArray *p)
{
    return p->_particleFormat;
}

/* 0x0015c840 */
int Gap__Bec__ParticleArray__vfunc_29(ParticleArray *p)
{
    return p->_maxNum;
}

/* 0x00180f50 */
void Gap__Bec__ParticleArray__vfunc_37(ParticleArray *a0, int a1)
{
    a0->_timeControlState = a1;
}

/* 0x003a4910 */
int Gap__Bec__ParticleArray__vfunc_20(void)
{
    return g_ParticleArray_metaObject[0];
}
