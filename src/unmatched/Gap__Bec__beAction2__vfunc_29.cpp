/* 0x00375e20 - Gap__Bec__beAction2__vfunc_29. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiverFromInfo(int, char *, int *);
extern int DAT_0050dfc8[4];
extern int DAT_005626e0[4];
void Gap__Bec__beAction2__vfunc_29(beAction2 *arg0, char *arg1);
}

void Gap__Bec__beAction2__vfunc_29(beAction2 *arg0, char *arg1) {
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050dfc8[0]);
    arg1[20] = 0;
    DAT_005626e0[0] = 0xBD088889;
}
