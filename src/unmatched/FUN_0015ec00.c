#include "dw4/reflected.h"
float FUN_0015ec00(igPsx2VertexArray1_1 *arg0, int arg1) {
    int a, idx, c;
    a = arg0->_vdata;
    idx = arg1 * 4;
    c = *(int *)(a + 60);
    return 2.0f * *(float *)(c + idx);
}
