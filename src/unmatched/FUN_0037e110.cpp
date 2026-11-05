#include "dw4/reflected.h"
extern "C" {
int FUN_0037e3a0(beDemoManager *, int, int, int, int, int, int, int);
void FUN_0037e110(beDemoManager *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
}

void FUN_0037e110(beDemoManager *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    if (arg0->_turningOK == 0) {
        arg0->_turningOK = 1;
    } else {
        return;
    }
    FUN_0037e3a0(arg0, 3, arg1, arg2, arg3, arg4, arg5, 0);
}
