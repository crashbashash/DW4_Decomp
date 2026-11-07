#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VisualContext__vfunc_97(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    char *p = (char *)(*(int *)((char *)(arg0->_pLightList) + 16) + (arg1 * 0xA0));
    float x, y, z;
    z = *(float *)(p + 88);
    y = *(float *)(p + 84);
    x = *(float *)(p + 80);
    *(float *)((char *)arg2 + 0) = x;
    *(float *)((char *)arg2 + 4) = y;
    *(float *)((char *)arg2 + 8) = z;
}
