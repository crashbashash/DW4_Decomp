/* 0x0016a130 — FUN_0016a130. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_0016a130(igPsx2VisualContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4, float *arg5, float *arg6) {
    *arg1 = arg0->_iViewportX;
    *arg2 = arg0->_iViewportY;
    *arg3 = arg0->_iViewportW;
    *arg4 = arg0->_iViewportH;
    *arg5 = arg0->_viewportNear;
    *arg6 = arg0->_viewportFar;
}
