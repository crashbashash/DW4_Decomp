#include "dw4/reflected.h"
extern "C" {
bool beMatCtrl_IsPlayer(beMatCtrl *);
}
bool beMatCtrl_IsPlayer(beMatCtrl *arg0)
{
    bool r = false;
    if (*(int *)(((igDataList *)arg0->_wkMatOnList)->_data + arg0->_wkChkMat * 4) != 0) {
        r = true;
    }
    return r;
}
