#include "dw4/reflected.h"
/* 0x0040c1c0 - Gap__Bec__beNDMWSaveIntf__vfunc_29. typed receiver struct; first call forwards a1 (dropped argument) Verified byte-identical by tools/verify.py. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_RegisterReceiver(int, beBaseInfoRam *, int *, int, int);
int beMessenger_RegisterReceiverFromInfo(int, beBaseInfoRam *, int *);
extern int DAT_00519908[4];
extern int DAT_00519918[4];
void Gap__Bec__beNDMWSaveIntf__vfunc_29(beNDMWSaveIntf *arg0, beBaseInfoRam *arg1) {
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_00519908[0]);
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_00519918[0], 0, arg1->_ramNo);
}
} /* extern "C" */
