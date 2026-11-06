#include "dw4/reflected.h"
void Gap__igDefaultInterfaceManager__vfunc_37(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_controllerDisconnectionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}
