#include "dw4/reflected.h"
extern "C" {

int igObject_Destroy(igObject *);

void **FUN_0041d490(void **arg0, igObject *arg1) {
    igObject *temp_a0;

    if (arg1 != 0) {
        arg1->_refCount = (unsigned int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)(*arg0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (unsigned int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long) (int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *arg0 = arg1;
    return arg0;
}
}
