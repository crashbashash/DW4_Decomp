#include "dw4/reflected.h"
int FUN_00192f00();
int FUN_001930f0();

void FUN_001deb50(igTransformSequence1_5 *arg0, void *arg1, int arg2, int arg3) {
    int temp_a2;
    int temp_a3;
    int temp_a5;
    unsigned char temp_v1;
    void *temp_v1_2;

    temp_v1 = arg0->_interpolationMethod[0];
    if (temp_v1 == 0) {
        temp_v1_2 = (void *)(((igVec3fList *)arg0->_xlateList)->_data + (arg2 * 0xC));
        *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(temp_v1_2) + 0);
        *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(temp_v1_2) + 4);
        *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(temp_v1_2) + 8);
        return;
    }
    if (temp_v1 == 1) {
        temp_a2 = ((igVec3fList *)arg0->_xlateList)->_data;
        FUN_00192f00(arg1, temp_a2 + (arg2 * 0xC), temp_a2 + (arg3 * 0xC));
        return;
    }
    temp_a3 = ((igVec3fList *)arg0->_xlateList)->_data;
    temp_a5 = ((igDataList *)arg0->_interpolationDataTranslation)->_data;
    FUN_001930f0(arg1, temp_a3 + (arg2 * 0xC), temp_a5 + (arg2 * 0x18), temp_a5 + (((arg2 * 2) + 1) * 0xC), temp_a3 + (arg3 * 0xC), temp_a5);
}
