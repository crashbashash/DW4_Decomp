int FUN_0015b7d0();
int FUN_0015b7f0();
int FUN_0015b820();
#include "dw4/reflected.h"
void Gap__Bec__ParticleArray__vfunc_23(ParticleArray *arg0, char *arg1, unsigned int arg2) {
    char *s1;
    s1 = (char *)arg0->_particleArray + arg2 * (int)arg0->_particleDataSize /* matching construct: signed stride keeps the retail load order */;
    FUN_0015b820(s1, arg1);
    FUN_0015b820(s1 + 0xC, arg1 + 0xC);
    FUN_0015b820(s1 + 0x18, arg1 + 0x18);
    FUN_0015b7f0(s1 + 0x24, arg1 + 0x24);
    FUN_0015b7f0(s1 + 0x34, arg1 + 0x34);
    FUN_0015b7f0(s1 + 0x44, arg1 + 0x44);
    FUN_0015b7d0(s1 + 0x54, arg1 + 0x54);
    FUN_0015b7d0(s1 + 0x5C, arg1 + 0x5C);
    FUN_0015b7d0(s1 + 0x64, arg1 + 0x64);
    FUN_0015b7d0(s1 + 0x6C, arg1 + 0x6C);
    FUN_0015b7d0(s1 + 0x74, arg1 + 0x74);
    FUN_0015b820(s1 + 0x7C, arg1 + 0x7C);
    FUN_0015b7d0(s1 + 0x88, arg1 + 0x88);
    arg0->_setConstant = 0;
    if (arg0->_arrayIndex <= arg2) {
        arg0->_arrayIndex = arg2 + 1;
    }
}
