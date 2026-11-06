#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiver(int, void *, int *, int, int);
extern int DAT_00515b80[4];
void Gap__Bec__beNDMWPanelWaza__vfunc_29(beNDMWPanelWaza *arg0, void *arg1) {
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_00515b80[0], 0, *(int *)((char *)(arg1) + 8));
    *(char *)((char *)(arg1) + 20) = 0;
}
}
