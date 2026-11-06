#include "dw4/reflected.h"
void FUN_0015d070(igPointSpriteExt *arg0, int arg1, void *arg2) {
    float temp_f0;
    int b, idx, c;
    b = ((igVertexArray1_1 *)arg0->_vertexArray)->_vdata;
    idx = arg1 * 4;
    c = *(int *)(b + 60);
    temp_f0 = *(float *)(c + idx);
    *(float *)((char *)(arg2) + 0) = temp_f0;
    *(float *)((char *)(arg2) + 4) = temp_f0;
}
