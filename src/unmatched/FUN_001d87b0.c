#include "dw4/reflected.h"
int igObject_Destroy();
void FUN_001d87b0(igTransformSequence *arg0, int arg1, igObject *arg2) {
    igObjectList *temp_s1;
    int temp_s0;
    int temp_v1;
    igObject *temp_a0;
    temp_s1 = (igObjectList *)arg0->_quatList;
    if (arg2 != 0) {
        arg2->_refCount = arg2->_refCount + 1;
    }
    temp_s0 = arg1 * 4;
    temp_a0 = *(igObject **)(temp_s1->_data + temp_s0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = temp_a0->_refCount - 1;
        if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    temp_v1 = temp_s1->_count;
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        *(igObject **)(temp_s1->_data + temp_s0) = arg2;
    }
}
