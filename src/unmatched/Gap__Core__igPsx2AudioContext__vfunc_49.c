#include "dw4/reflected.h"
int FUN_0032d850();
extern void * DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_49(igPsx2AudioContext *arg0, int arg1, int arg2) {
    int sp1C;
    *(int *)((char *)((*(int *)((char *)(DAT_0055f5d0[0]) + 16) + (arg1 * 0x24))) + 32) = arg2;
    *(int *)((char *)((*(int *)((char *)(DAT_0055f5d0[0]) + 16) + (arg2 * 0x24))) + 32) = arg1;
    FUN_0032d850(&sp1C, arg0->_connection, arg1 | 0x2B0000, arg2, 0, 1);
}
