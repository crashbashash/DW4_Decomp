#include "dw4/reflected.h"
/* A C++ bool (built with daddiu) and an explicit padding nop after the assignment reproduce the
 * branch shape. */
extern "C" {
bool beMatCtrl_IsPlayer(beMatCtrl *);
}
bool beMatCtrl_IsPlayer(beMatCtrl *arg0)
{
    bool r = false;
    if (*(int *)(((igDataList *)arg0->_wkMatOnList)->_data + arg0->_wkChkMat * 4) != 0) {
        r = true;
        asm { nop } /* matching construct: padding nop reproduces the retail branch shape */
    }
    return r;
}
