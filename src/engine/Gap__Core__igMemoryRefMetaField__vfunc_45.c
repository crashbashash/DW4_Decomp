#include "dw4/reflected.h"
int Gap__Core__igMemoryRefMetaField__vfunc_45(igMemoryRefMetaField *arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = arg0->_offset;
    return *(int *)(arg1 + temp_v0) == *(int *)(arg2 + temp_v0);
}
