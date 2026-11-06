#include "dw4/reflected.h"
extern "C" {
int beMessenger_GetBool(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_00517fd0[4];
extern int DAT_00517ff0[4];
unsigned char FUN_003f12f0(beNDMWMcUtilCtrl *arg0) {
    unsigned char var_s0;
    unsigned char one = 1;

    var_s0 = 0;
    if (arg0->_isUseUtil == one) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff0[0]);
        if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == one) {
            arg0->_isRdy = one;
            var_s0 = one;
        }
    } else {
        arg0->_isRdy = one;
        var_s0 = one;
    }
    return var_s0;
}
}
