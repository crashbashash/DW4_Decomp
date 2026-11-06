#include "dw4/reflected.h"
int beMatCtrl_IsRideOffPlayer(beMatCtrl *arg0, int arg1) {
    int off = arg0->_wkChkMat * 4;
    int bit = 1 << arg1;
    int r;
    if (bit != (bit & *(int *)(((igDataList *)arg0->_wkMatOnList)->_data + off))
        && bit == (bit & *(int *)(((igDataList *)arg0->_wkMatOldOnList)->_data + off)))
        r = 1;
    else {
        r = 0;
        asm { nop } /* matching construct: retail padding nop on the false path */
    }
    return r;
}
