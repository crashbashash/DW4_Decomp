/* 0x00147690 - Gap__Core__igDefaultInterfaceManager__vfunc_41. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
#include "dw4/reflected.h"
void Gap__Core__igDefaultInterfaceManager__vfunc_41(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_keyUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}
