/* Receiver is the model-controller sub-object beNDMWMcUtilCtrl (CommonIntf._mcUtilCtrl, +0x34):
 * _isUseUtil gates the SendNamed on _messenger. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_00517fd0[4];
extern int DAT_00517ff8[4];
void FUN_003f1380(beNDMWMcUtilCtrl *arg0) {
    if (arg0->_isUseUtil == 1) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff8[0]);
    }
}
} /* extern "C" */
