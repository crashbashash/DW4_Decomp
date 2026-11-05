/* 0x001def90 — FUN_001def90. Fetch the rotation key at index arg2 from the
 * sequence's quaternion list, or blend keys arg2/arg3 by the method in
 * _interpolationMethod[1]. */
#include "dw4/reflected.h"
int FUN_00192ab0();
int FUN_00192cc0();

void FUN_001def90(igTransformSequence1_5 *arg0, void *arg1, int arg2, int arg3) {
    int temp_a2;
    int temp_a2_2;
    unsigned char temp_v1;
    void *temp_v1_2;

    temp_v1 = arg0->_interpolationMethod[1];
    if (temp_v1 == 0) {
        temp_v1_2 = (void *)(((igQuaternionfList *)arg0->_quatList)->_data + (arg2 * 0x10));
        *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(temp_v1_2) + 0);
        *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(temp_v1_2) + 4);
        *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(temp_v1_2) + 8);
        *(float *)((char *)(arg1) + 12) = (float) *(float *)((char *)(temp_v1_2) + 12);
        return;
    }
    if (temp_v1 == 3) {
        temp_a2 = ((igQuaternionfList *)arg0->_quatList)->_data;
        FUN_00192ab0(arg1, temp_a2 + (arg2 * 0x10), temp_a2 + (arg3 * 0x10));
        return;
    }
    temp_a2_2 = ((igQuaternionfList *)arg0->_quatList)->_data;
    FUN_00192cc0(arg1, temp_a2_2 + (arg2 * 0x10), temp_a2_2 + (arg3 * 0x10));
}
