/* 0x00147750 - Gap__Core__igDefaultInterfaceManager__vfunc_35. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
void Gap__Core__igDefaultInterfaceManager__vfunc_35(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonPressureFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}
