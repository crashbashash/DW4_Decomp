#include "dw4/reflected.h"
/* True when the material controller has a non-null entry for the caller's slot (arg0->+0x38 list,
 * +0x10 table, indexed by arg0->+0x28). A C++ bool (retail builds it with daddiu) and an explicit
 * padding nop after the assignment reproduce the retail branch shape. */
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
