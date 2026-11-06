#include "dw4/reflected.h"
int FUN_001c5b80();
extern void * DAT_00562768[4];
void Gap__Bec__ParticleTimer__vfunc_15(ParticleTimer *arg0) {
    void *temp_a0;
    int temp_a1;

    FUN_001c5b80();
    temp_a0 = (void *)(*(int *)((char *)arg0 + *(int *)((char *)(DAT_00562768[0]) + 8)));
    temp_a1 = arg0->_flags;
    if (temp_a1 & 8) {
        *(int *)((char *)(temp_a0) + 24) = 2;
        return;
    }
    if (temp_a1 & 4) {
        *(int *)((char *)(temp_a0) + 24) = 1;
        return;
    }
    *(int *)((char *)(temp_a0) + 24) = 0;
}
