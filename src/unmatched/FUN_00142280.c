/* 0x00142280 — FUN_00142280. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver: igViewportAttr (vtable slot of Gap::Core::igViewportAttr at 0x522520;
 * fields _x/_y/_w/_h/_nearZ/_farZ at +12/+16/+20/+24/+32/+36 match). */
#include "dw4/reflected.h"
void FUN_00142280(igViewportAttr *arg0, int arg1, int arg2, int arg3, int arg4, float fparg0, float fparg1) {
    arg0->_x = arg1;
    arg0->_y = arg2;
    arg0->_w = arg3;
    arg0->_h = arg4;
    arg0->_nearZ = fparg0;
    arg0->_farZ = fparg1;
}
