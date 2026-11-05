#include "dw4/reflected.h"
void FUN_0041d3b0(igObjectList *arg0, int arg1, int arg2) {
    int temp_a4;
    int var_a1;
    int var_a3;

    var_a1 = arg1;
    temp_a4 = var_a1 + arg2;
    var_a3 = var_a1 * 4;
    if (var_a1 < temp_a4) {
        do {
            var_a1 += 1;
            *(int *)((char *)arg0->_data + var_a3) = 0;
            var_a3 += 4;
        } while (var_a1 < temp_a4);
    }
}
