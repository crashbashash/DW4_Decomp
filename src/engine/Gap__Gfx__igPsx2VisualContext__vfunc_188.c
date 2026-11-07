#include "dw4/reflected.h"
int FUN_0016a520();

void Gap__Gfx__igPsx2VisualContext__vfunc_188(igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4) {
    int temp_a1;

    arg0->_scissorX = arg1;
    arg0->_scissorY = arg2;
    arg0->_scissorW = arg3;
    arg0->_scissorH = arg4;
    temp_a1 = arg0->_scissorType;
    if (temp_a1 == 1) {
        FUN_0016a520(arg0, temp_a1);
    }
}
