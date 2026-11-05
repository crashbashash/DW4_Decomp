#include "dw4/reflected.h"
extern void * DAT_00562768[4];
void Gap__Bec__ParticleTimer__vfunc_26(ParticleTimer *arg0, int arg1, int arg2) {
    int temp_a2;
    int *temp_a0;

    if (arg2 != 0) {
        arg0->_flags = arg0->_flags | arg1;
    } else {
        arg0->_flags = arg0->_flags & ~arg1;
    }
    temp_a0 = *(int **)((char *)arg0 + *(int *)((char *)(DAT_00562768[0]) + 8));
    temp_a2 = arg0->_flags;
    if (temp_a2 & 8) {
        temp_a0[6] = 2;
        return;
    }
    if (temp_a2 & 4) {
        temp_a0[6] = 1;
        return;
    }
    temp_a0[6] = 0;
}

