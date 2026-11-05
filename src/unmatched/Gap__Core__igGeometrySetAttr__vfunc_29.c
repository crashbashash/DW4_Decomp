#include "dw4/reflected.h"
void FUN_0013e6e0(void *, int, int);
void Gap__Core__igGeometrySetAttr__vfunc_29(igGeometrySetAttr *arg0, int arg1) {
    int t;
    if (arg0->_renderListState != 0) {
        t = arg0->_renderListHandle;
        if (t == -1) {
            FUN_0013e6e0(arg0, arg1, t);
        }
    }
}
