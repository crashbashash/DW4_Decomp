#include "dw4/reflected.h"
typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
int igObject_Destroy();

void Gap__Bec__ParticleArray__vfunc_28(ParticleArray *arg0, RefCountedHeader *arg1, int arg2, int arg3) {
    RefCountedHeader *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (void *)(arg0->_primLengthArray);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_primLengthArray = (int)(arg1);
    arg0->_primLengthArrayNum = arg2;
    arg0->_primLengthArrayOffset = arg3;
}
