/* 0x00333820 — Gap__igAdxFile__vfunc_11. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_11();

void Gap__igAdxFile__vfunc_11(igAdxFile *arg0) {
    Gap__Core__igObject__vfunc_11();
    arg0->_pBufferPtr = (int)((int) arg0->_pBuffer);
    arg0->_bBufferFilled = 0;
    arg0->_iBufferPos = 0;
    *(int *)((char *)(arg0) + 96) = 0;
}
}
