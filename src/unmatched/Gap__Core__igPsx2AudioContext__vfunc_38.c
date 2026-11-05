/* 0x001458f0 - Gap__Core__igPsx2AudioContext__vfunc_38. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
int FUN_0032d850();

int Gap__Core__igPsx2AudioContext__vfunc_38(igPsx2AudioContext *arg0, int arg1) {
    int sp1C;
    int sp18;

    FUN_0032d850(&sp18, arg0->_connection, arg1 | 0xB0000, 0, &sp1C, 0);
    return sp1C;
}
