#include "dw4/reflected.h"
void Gap__Sg__igTransformSequence1_5__vfunc_47(igTransformSequence1_5 *arg0, int arg1, void *arg2) {
    void *temp_v1;
    if (arg0->_drivenChannels & 4) {
        float z = *(float *)((char *)(arg2) + 8);
        float y = *(float *)((char *)(arg2) + 4);
        float x = *(float *)((char *)(arg2) + 0);
        temp_v1 = (void *)(((igDataList *)arg0->_quatList)->_data + (arg1 * 0x10));
        *(float *)((char *)(temp_v1) + 0) = x;
        *(float *)((char *)(temp_v1) + 4) = y;
        *(float *)((char *)(temp_v1) + 8) = z;
        *(int *)((char *)(temp_v1) + 12) = 0;
    }
}
