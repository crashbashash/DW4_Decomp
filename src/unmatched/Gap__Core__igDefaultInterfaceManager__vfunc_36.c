/* 0x00147780 - Gap__Core__igDefaultInterfaceManager__vfunc_36. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
void Gap__Core__igDefaultInterfaceManager__vfunc_36(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_controllerConnectionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}
