/* 0x00171630 - FUN_00171630. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
void FUN_00171630(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    char *p = (char *)(*(int *)((char *)(arg0->_pLightList) + 16) + (arg1 * 0xA0));
    float z = *(float *)(p + 88);
    float y = *(float *)(p + 84);
    float x = *(float *)(p + 80);
    *(float *)((char *)arg2 + 0) = x;
    *(float *)((char *)arg2 + 4) = y;
    *(float *)((char *)arg2 + 8) = z;
}
