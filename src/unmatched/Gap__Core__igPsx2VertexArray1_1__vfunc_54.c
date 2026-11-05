/* 0x0015ec00 - Gap__Core__igPsx2VertexArray1_1__vfunc_54. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
float Gap__Core__igPsx2VertexArray1_1__vfunc_54(igPsx2VertexArray1_1 *arg0, int arg1) {
    int a, idx, c;
    a = arg0->_vdata;
    idx = arg1 * 4;
    c = *(int *)(a + 60);
    return 2.0f * *(float *)(c + idx);
}
