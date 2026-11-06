#include "dw4/reflected.h"
int FUN_00174ea0(int, int);
int FUN_00174ee0(int, int);
int FUN_00174fa0(int, int, int, int);
int FUN_00174fc0(int, int);
int FUN_00174fe0(int, int);

void Gap__Core__igStencilFunctionAttr__vfunc_24(igStencilFunctionAttr *arg0, int arg1) {
    FUN_00174fa0(arg1, arg0->_stenFailOp, arg0->_stenPassZPassOp, arg0->_stenPassZFailOp);
    FUN_00174ea0(arg1, arg0->_refVal);
    FUN_00174ee0(arg1, arg0->_func);
    FUN_00174fc0(arg1, arg0->_readMask);
    FUN_00174fe0(arg1, arg0->_writeMask);
}
