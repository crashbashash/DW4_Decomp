#include "dw4/reflected.h"
void Gap__Core__igPsx2VertexArray1_1__vfunc_33(igVertexArray *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0->_vdata) + 4) + (arg1 * 0xC));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
}
