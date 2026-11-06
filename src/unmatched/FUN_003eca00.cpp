#include "dw4/reflected.h"
extern "C" {
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int DAT_00517a48[4];
extern int DAT_00517af8[4];
void FUN_003eca00(beNDMWLoadIntf2MesWin *arg0, int arg1, int arg2, int arg3) {
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00517a48[0], arg2, arg1);
    beMessenger_AppendString(arg0->_messenger, arg3);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517af8[0]);
    beMessenger_GetBool(arg0->_messenger, 0);
}
}
