/* 0x00142ce0 — FUN_00142ce0. m2c draft (build/m2c/FUN_00142ce0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
#include "dw4/reflected.h"
int List_Reserve();

void FUN_00142ce0(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 0xC);
    }
}
