/* Receiver: beNDMWMcUtilCtrl (reflected +8 _messenger, +12 _isUseUtil; callers pass
 * beNDMWLoadCtrl2CommonIntf::_mcUtilCtrl, +52). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBoolCount(int);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int DAT_00517fd0[4];
extern int DAT_00517fe0[4];
void FUN_003f1270(beNDMWMcUtilCtrl *arg0) {
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00517fd0[0], 0, -1);
    beMessenger_AppendInt(arg0->_messenger, 4);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517fe0[0]);
    if (beMessenger_GetBoolCount(arg0->_messenger) > 0) {
        arg0->_isUseUtil = 1;
    } else {
        arg0->_isUseUtil = 0;
    }
}
} /* extern "C" */
