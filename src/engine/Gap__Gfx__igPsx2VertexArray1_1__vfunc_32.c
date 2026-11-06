#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_32(igPsx2VertexArray1_1 *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0->_vdata) + 4) + (arg1 * 0xC));
    *(float *)((char *)(temp_v1) + 0) = (float) *(float *)((char *)(arg2) + 0);
    *(float *)((char *)(temp_v1) + 4) = (float) *(float *)((char *)(arg2) + 4);
    *(float *)((char *)(temp_v1) + 8) = (float) *(float *)((char *)(arg2) + 8);
}
