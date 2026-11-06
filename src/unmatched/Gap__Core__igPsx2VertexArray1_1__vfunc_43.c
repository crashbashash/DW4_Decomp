#include "dw4/reflected.h"
int Gap__Core__igPsx2VertexArray1_1__vfunc_43(igPsx2VertexArray1_1 *arg0, int arg1) {
    int temp_a1;
    unsigned int temp_a0;
    temp_a1 = *(int *)(*(int *)((char *)(arg0->_vdata) + 8) + (arg1 * 4));
    temp_a0 = (unsigned int)(temp_a1 & 0x80000000) >> 7;
    return (temp_a1 & 0xFFFFFF) | (temp_a0 + (((temp_a1 & 0xFF000000) - temp_a0) * 2));
}
