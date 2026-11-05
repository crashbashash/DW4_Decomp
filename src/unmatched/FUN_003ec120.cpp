#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendInt(int, int);
int beMessenger_AppendObject(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int *DAT_004ceb30[][20];
extern int DAT_005179b0[4];
extern int DAT_005179b8[4];
extern int DAT_005179c0[4];
extern int DAT_005179c8[4];
extern int DAT_005179d0[4];
extern int DAT_005179d8[4];
extern int DAT_005179e8[4];
extern int DAT_005179f8[4];
extern int DAT_00517a00[4];
extern int DAT_00517a08[4];
extern int DAT_00517a38[4];
void FUN_003ec120(beNDMWLoadIntf2TextOrder *arg0, int *arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int *temp_s0;

    beMessenger_SelectGroup(arg0->_messenger, &DAT_005179b0[0]);
    beMessenger_AppendObject(arg0->_messenger, arg4);
    beMessenger_AppendInt(arg0->_messenger, 0x3F);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517a38[0]);
    temp_s0 = DAT_004ceb30[arg2][arg3];
    switch (arg5) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_AppendString(arg0->_messenger, &DAT_005179b8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179c0[0]);
        break;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_AppendString(arg0->_messenger, &DAT_005179c8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179c0[0]);
        break;
    case 2:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_AppendString(arg0->_messenger, &DAT_005179d0[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179c0[0]);
        break;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005179b0[0]);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, temp_s0);
    beMessenger_AppendObject(arg0->_messenger, arg4);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179f8[0]);
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, temp_s0);
    beMessenger_AppendString(arg0->_messenger, &DAT_00517a00[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517a08[0]);
    switch (arg6) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179d8[0]);
        return;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179e8[0]);
    case 2:
        ;
    }
}
} /* extern "C" */
