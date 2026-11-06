#include "dw4/reflected.h"
int Gap__Core__igPsx2VertexArray1_1__vfunc_37(igPsx2VertexArray1_1 *arg0, int arg1) {
    if (arg0->_vertexFormat & 0x400000) {
        return *(int *)((char *)(arg0->_vdata) + 68) + (arg1 * 0xC);
    }
    return 0;
}
