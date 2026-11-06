#include "dw4/reflected.h"
int FUN_002d8d00();

int Gap__Core__igRawRefMetaField__vfunc_43(igRawRefArrayMetaField *arg0, int arg1, int arg2) {
    if (arg0->_persistent == 1) {
        return FUN_002d8d00(arg2, *(int *)(arg1 + arg0->_offset), 0, 0);
    }
    return -1;
}
