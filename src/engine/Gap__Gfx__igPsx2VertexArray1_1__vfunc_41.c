#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_41(igPsx2VertexArray1_1 *arg0, int arg1, unsigned long long arg2) {
    unsigned int lo = (unsigned int)arg2;
    *(int *)(*(int *)((char *)(arg0->_vdata) + 8) + (arg1 * 4)) = ((arg2 & 0xFFFFFFULL)) | (((lo >> 1) & 0x7F000000) + (lo & 0x01000000));
}
