#include "dw4/reflected.h"
int Gap__Gfx__igPsx2VisualContext__vfunc_161(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_163(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_165(int, int, int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_167(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_169(int, int);

void Gap__Attrs__igStencilFunctionAttr__vfunc_24(igStencilFunctionAttr *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_165(arg1, arg0->_stenFailOp, arg0->_stenPassZPassOp, arg0->_stenPassZFailOp);
    Gap__Gfx__igPsx2VisualContext__vfunc_161(arg1, arg0->_refVal);
    Gap__Gfx__igPsx2VisualContext__vfunc_163(arg1, arg0->_func);
    Gap__Gfx__igPsx2VisualContext__vfunc_167(arg1, arg0->_readMask);
    Gap__Gfx__igPsx2VisualContext__vfunc_169(arg1, arg0->_writeMask);
}
