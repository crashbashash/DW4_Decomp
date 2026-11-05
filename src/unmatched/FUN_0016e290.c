/* 0x0016e290 — FUN_0016e290. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_0016e290(igPsx2BlendEquationExt *arg0, int arg1, int arg2, int arg3, int arg4, char arg5) {
    arg0->_blendA = arg1;
    arg0->_blendB = arg2;
    arg0->_blendC = arg3;
    arg0->_blendD = arg4;
    arg0->_blendConstant = arg5;
}
