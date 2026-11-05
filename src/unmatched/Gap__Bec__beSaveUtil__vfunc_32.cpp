#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(igObject *);
void Gap__Bec__beSaveUtil__vfunc_32(beSaveUtil *arg0);
}


void Gap__Bec__beSaveUtil__vfunc_32(beSaveUtil *arg0) {
    igObject *temp_a0;
    igObject *temp_a0_2;

    temp_a0 = (igObject *)arg0->_api;
    if (temp_a0 != 0) {
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_api = 0;
    }
    temp_a0_2 = (igObject *)arg0->_connectCheck;
    if (temp_a0_2 != 0) {
        if (temp_a0_2 != 0) {
            temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0_2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->_connectCheck = 0;
    }
}
