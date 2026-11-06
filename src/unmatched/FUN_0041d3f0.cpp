#include "dw4/reflected.h"
extern "C" {

int igObject_Destroy(igObject *);

void FUN_0041d3f0(igObjectList *arg0, int arg1, int arg2) {
    int temp_s2;
    int var_s1;
    int var_s0;
    igObject *temp_a0;

    temp_s2 = arg1 + arg2;
    var_s1 = arg1;
    if (arg1 < temp_s2) {
        var_s0 = arg1 * 4;
        do {
            temp_a0 = *(igObject **)(arg0->_data + var_s0);
            if (temp_a0 != 0) {
                temp_a0->_refCount = temp_a0->_refCount - 1;
                if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(temp_a0);
                    asm { nop }
                }
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < temp_s2);
    }
}
}
