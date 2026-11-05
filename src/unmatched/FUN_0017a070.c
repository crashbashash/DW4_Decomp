#include "dw4/reflected.h"
int igObject_Destroy(igObject *);

void FUN_0017a070(int *a) {
    igObject *temp_a0;
    igObject *temp_a0_2;

    a[0] = 7;
    a[1] = 1;
    a[2] = 1;
    a[3] = 1;
    a[4] = 1;
    a[21] = 0;
    a[22] = 0x20;
    a[23] = 0;
    a[24] = 0x20;
    a[5] = 0;
    a[8] = -1;
    a[9] = -1;
    a[10] = -1;
    temp_a0 = (igObject *)(a[12]);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)temp_a0->_refCount - 1;
        if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    a[12] = 0;
    temp_a0_2 = (igObject *)(a[13]);
    if (temp_a0_2 != 0) {
        temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
        if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    a[13] = 0;
    a[14] = 0;
    a[15] = 0;
    a[25] = -1;
    a[27] = 0;
    a[26] = -1;
    a[18] = 0;
    a[19] = 0;
    a[33] = 0;
    *(char *)((char *)a + 80) = 1;
    *(char *)((char *)a + 81) = 1;
    a[7] = -1;
}
