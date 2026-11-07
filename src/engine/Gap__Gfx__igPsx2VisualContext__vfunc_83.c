#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VisualContext__vfunc_83(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 32);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 36);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 40);
    *(float *)((char *)(arg2) + 12) = (float) *(float *)((char *)(temp_v1) + 44);
}
