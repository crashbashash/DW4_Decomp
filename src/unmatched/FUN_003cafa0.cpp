extern "C" {
#include "dw4/reflected.h"
int FUN_00100610(void *);
int igObject_Destroy(void *);
igObject **FUN_003cafa0(igObject **arg0, short arg1) {
    igObject *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
}
