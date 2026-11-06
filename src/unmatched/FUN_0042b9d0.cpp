#include "dw4/reflected.h"
extern "C" {
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendString(int, int *);
extern int DAT_0051b218[4];
extern int DAT_0051b278[4];
extern int DAT_0051b288[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b550[4];
extern int DAT_0051b558[4];
extern int DAT_0051b6f8[4];
void FUN_0042b9d0(beNDMWShopCtrl50 *arg0) {
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b278[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b218[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b288[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
}
}
