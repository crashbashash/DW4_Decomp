#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {

int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_005159c0[4];
extern int DAT_005159d8[4];
extern int DAT_005159e0[4];
void FUN_003ce7e0(beNDMWPanelObject *arg0) {
    int temp_v1;
    int temp_v1_2;
    temp_v1 = arg0->_cursor;
    if (temp_v1 != 0) {
        arg0->_cursor = temp_v1 - 1;
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005159e0[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
        return;
    }
    temp_v1_2 = arg0->_offset;
    if (temp_v1_2 != 0) {
        arg0->_offset = temp_v1_2 - 1;
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005159e0[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
    }
}
} /* extern "C" */
