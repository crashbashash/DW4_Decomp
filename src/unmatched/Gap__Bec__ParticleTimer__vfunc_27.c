/* 0x001c5380 — Gap__Bec__ParticleTimer__vfunc_27. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
extern void * DAT_00562768[4];
void Gap__Bec__ParticleTimer__vfunc_27(ParticleTimer *arg0, int arg1) {
    void *temp_a0;

    arg0->_flags = arg1;
    temp_a0 = (void *)(*(int *)((char *)arg0 + *(int *)((char *)(DAT_00562768[0]) + 8)));
    if (arg1 & 8) {
        *(int *)((char *)(temp_a0) + 24) = 2;
        return;
    }
    if (arg1 & 4) {
        *(int *)((char *)(temp_a0) + 24) = 1;
        return;
    }
    *(int *)((char *)(temp_a0) + 24) = 0;
}
