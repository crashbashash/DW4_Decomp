#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiver(int, beBaseInfoRam *, int *, int, int);
int beMessenger_RegisterReceiverFromInfo(int, beBaseInfoRam *, int *);
extern int DAT_005175d8[4];
extern int DAT_005175e8[4];
void Gap__Bec__beNDMWLoadIntf2__vfunc_29(beNDMWLoadIntf2 *arg0, beBaseInfoRam *arg1) {
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_005175d8[0]);
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_005175e8[0], 0, arg1->_ramNo);
}
}
