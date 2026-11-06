#include "dw4/reflected.h"
extern "C" {
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_00517fd0[4];
extern int DAT_00517ff8[4];
void FUN_003f1380(beNDMWMcUtilCtrl *arg0) {
    if (arg0->_isUseUtil == 1) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff8[0]);
    }
}
}
