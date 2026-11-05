#include "dw4/reflected.h"
/* beMatCtrl._wkPlExist (+32) is an igBoolArray; the reflected header declares only its first word, so the byte array is spelled by this view.
 * matching construct: an array member keeps retail's addu-then-lbu shape; the view carries the receiver, the other fields are read through beMatCtrl. */
struct beMatCtrlView { int pad[8]; unsigned char act[8]; int idx; int pad3[3]; int a; int b; };
extern "C" bool beMatCtrl_IsAllPlayer(beMatCtrlView *c);
bool beMatCtrl_IsAllPlayer(beMatCtrlView *c) {
    bool r = true;
    beMatCtrl *m = (beMatCtrl *)c;
    for (int i = 0; i < 4; i++) {
        if (c->act[i] != 0) {
            int bit = 1 << i;
            if (bit != (bit & ((unsigned int *)((igDataList *)m->_wkMatOnList)->_data)[m->_wkChkMat])) { r = false; break; }
        }
    }
    return r;
}
