#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_0051af30[4];
extern int DAT_0051afa0[4];
extern int DAT_0051afb0[4];
extern int DAT_0051afb8[4];
extern int DAT_0051afc8[4];
void FUN_00426530(beNDMWStatusTitle03 *arg0, int arg1) {
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051af30[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051afa0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051afb0[0]);
    if (arg1 != 0) {
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051afb8[0]);
        return;
    }
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051afc8[0]);
}
} /* extern "C" */
