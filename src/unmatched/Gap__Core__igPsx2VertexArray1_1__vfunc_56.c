#include "dw4/reflected.h"
void Gap__Core__igPsx2VertexArray1_1__vfunc_56(igPsx2VertexArray1_1 *arg0, int arg1, float *arg2) {
    float *p;
    float k = 2.0f;
    p = (float *)(*(int *)((char *)(arg0->_vdata) + 60) + (arg1 * 8));
    arg2[0] = p[0];
    arg2[1] = p[1];
    arg2[0] = arg2[0] * k;
    arg2[1] = arg2[1] * k;
}
