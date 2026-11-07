#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(int *);
void Gap__Bec__beWeapon__vfunc_32(beWeapon *arg0);
}

void Gap__Bec__beWeapon__vfunc_32(beWeapon *arg0) {
    int *temp_a0;

    temp_a0 = (int *)arg0->_attachDataList;
    if (temp_a0 != 0) {
        temp_a0[1] = temp_a0[1] - 1;
        if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_attachDataList = 0;
}
