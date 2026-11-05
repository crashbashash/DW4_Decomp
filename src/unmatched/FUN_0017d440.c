/* 0x0017d440 — FUN_0017d440. Copies a 12-byte vector from a table entry (index * 12). Verified
 * byte-identical by tools/verify.py. Receiver: igPsx2VertexArray1_1 (_vdata at +8, an
 * arena handle used as a pointer to the stream-pointer table; entry 0 is read). */
#include "dw4/reflected.h"
void FUN_0017d440(igPsx2VertexArray1_1 *arg0, int arg1, float *arg2) {
    float *p = (float *)(*(int *)arg0->_vdata + arg1 * 12);
    arg2[0] = p[0];
    arg2[1] = p[1];
    arg2[2] = p[2];
}
