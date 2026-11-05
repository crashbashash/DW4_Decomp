#include "dw4/reflected.h"
int beMatCtrl_IsRidePlayer(beMatCtrl *arg0, int arg1) {
    int idx;
    int bit;

    idx = arg0->_wkChkMat * 4;
    bit = 1 << arg1;
    if ((bit == (bit & *(int *)((char *)((igDataList *)arg0->_wkMatOnList)->_data + idx))) && (bit != (bit & *(int *)((char *)((igDataList *)arg0->_wkMatOldOnList)->_data + idx)))) {
        return 1;
    }
    return 0;
}
