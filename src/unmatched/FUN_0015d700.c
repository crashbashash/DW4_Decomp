/* 0x0015d700 - FUN_0015d700. Pointer web joined across the stride multiply (p = idx*12; p = base + p) with the base as first addend. */
#include "dw4/reflected.h"
void FUN_0015d700(igPsx2PointSpriteExt *arg0, int arg1, void *arg2) {
    int temp_a0;
    char *var_v1;
    temp_a0 = *(int *)((char *)(((igVertexArray *)arg0->_vertexArray)->_vdata) + 64);
    if (temp_a0 != 0) { var_v1 = (char *)(arg1 * 0xC); var_v1 = (char *)(temp_a0 + (int)var_v1); } else { var_v1 = 0; }
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(var_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(var_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(var_v1) + 8);
}
