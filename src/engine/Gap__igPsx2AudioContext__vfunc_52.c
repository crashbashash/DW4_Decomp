#include "dw4/reflected.h"
int FUN_0032d6d0();

void Gap__igPsx2AudioContext__vfunc_52(igPsx2AudioContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    int a[4];
    int r;
    FUN_0032d6d0(&r, arg0->_connection, 0xE0000, 0, 0, a, 0x20, 0);
    if (arg1 != 0) {
        *arg1 = a[0];
    }
    if (arg2 != 0) {
        *arg2 = a[1];
    }
    if (arg3 != 0) {
        *arg3 = a[2];
    }
    if (arg4 != 0) {
        *arg4 = a[3];
    }
}
