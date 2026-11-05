#include "dw4/reflected.h"
extern "C" {
int beMessenger_GetBool(int, int);
int beMessenger_SendNamed(int, void *, int, int, void *);
extern int DAT_00517fd0[4];
extern int DAT_00517ff0[4];
}
extern "C" bool FUN_003f13d0(beNDMWMcUtilCtrl *arg0) {
    bool r = false;
    if (arg0->_isUseUtil == 1) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff0[0]);
        if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
            r = true;
        }
    } else {
        r = true;
    }
    return r;
}
