#include "dw4/reflected.h"
extern "C" {
extern int beMessenger_AppendString(int, const char *);
extern int beMessenger_DispatchSelected(int, const char *);
extern int beMessenger_SelectReceivers(int, const char *, int, int);
extern char DAT_005179b0[], DAT_005179b8[], DAT_005179c0[], DAT_005179c8[], DAT_005179d0[], DAT_005179d8[], DAT_005179e8[], DAT_005179f8[], DAT_00517a00[], DAT_00517a08[];
void TextOrder_Configure(beNDMWLoadIntf2TextOrder *arg0, char *arg1, char *arg2, char *arg3, int arg4, int arg5) {
    switch (arg4) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_AppendString(arg0->_messenger, DAT_005179b8);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005179c0);
        break;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_AppendString(arg0->_messenger, DAT_005179c8);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005179c0);
        break;
    case 2:
        beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_AppendString(arg0->_messenger, DAT_005179d0);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005179c0);
        break;
    }
    switch (arg5) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005179d8);
        break;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005179e8);
        break;
    case 2:
        break;
    }
    beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg3);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_005179f8);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_005179b0, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, DAT_00517a00);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00517a08);
}
}
