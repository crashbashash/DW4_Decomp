/* 0x00147660 - Gap__Core__igDefaultInterfaceManager__vfunc_40. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
void Gap__Core__igDefaultInterfaceManager__vfunc_40(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_keyDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}
