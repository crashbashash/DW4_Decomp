#include "dw4/reflected.h"
void Gap__igDefaultInterfaceManager__vfunc_29(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_windowMoveFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}
