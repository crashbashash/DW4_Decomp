#include "dw4/reflected.h"
void Gap__Core__igTransformSequence1_5__vfunc_55(igTransformSequence1_5 *arg0, int arg1, long long arg2) {
    int temp_v1;
    void *temp_a3;

    temp_a3 = (void *)(arg0->_timeListLong);
    temp_v1 = *(int *)((char *)(temp_a3) + 8);
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        *(long long *)(*(int *)((char *)(temp_a3) + 16) + (arg1 * 8)) = arg2;
    }
}
