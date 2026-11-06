extern "C" {
int FUN_004542a0(int, int);
int FUN_004542e0(int, int, int);
}
#include "dw4/reflected.h"

extern "C" {
void Gap__Bec__bePadManager__vfunc_24(bePadManager *arg0);
}
void Gap__Bec__bePadManager__vfunc_24(bePadManager *arg0) {
    int temp_s0;
    void *temp_v0;

    temp_v0 = (void *)arg0->_insight;
    temp_s0 = *(int *)((char *)(temp_v0) + 32);
    FUN_004542e0(temp_s0, arg0->_kbReceiver, *(int *)((char *)(temp_v0) + 36));
    FUN_004542a0(temp_s0, arg0->_kbReceiver);
}
