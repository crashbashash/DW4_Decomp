#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiverFromInfo(int, void *, int *);
extern int DAT_00516788[4];
void Gap__Bec__beNDMWStatus__vfunc_29(beNDMWStatus *arg0, void *arg1) {
    if (((beBaseInfoList *)arg0->_infoList)->_count == 1) {
        beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_00516788[0]);
        *(char *)((char *)(arg1) + 20) = 0;
    }
}
}
