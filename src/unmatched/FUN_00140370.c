/* 0x00140370 — FUN_00140370. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_00174ea0(int, int);
int FUN_00174ee0(int, int);
int FUN_00174fa0(int, int, int, int);
int FUN_00174fc0(int, int);
int FUN_00174fe0(int, int);

void FUN_00140370(igStencilFunctionAttr *arg0, int arg1) {
    FUN_00174fa0(arg1, arg0->_stenFailOp, arg0->_stenPassZPassOp, arg0->_stenPassZFailOp);
    FUN_00174ea0(arg1, arg0->_refVal);
    FUN_00174ee0(arg1, arg0->_func);
    FUN_00174fc0(arg1, arg0->_readMask);
    FUN_00174fe0(arg1, arg0->_writeMask);
}
