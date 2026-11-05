/* 0x00147810 - Gap__Core__igDefaultInterfaceManager__vfunc_39. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
void Gap__Core__igDefaultInterfaceManager__vfunc_39(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerPointOfViewFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}
