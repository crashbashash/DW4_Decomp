/* 0x00448430 — FUN_00448430. m2c draft (build/m2c/FUN_00448430.c), dropped leading call arguments restored; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_004480a0(beNDMWItemBlueArmor *, int, int);
int FUN_00448190(beNDMWItemBlueArmor *, int, int);
int FUN_00448410(beNDMWItemBlueArmor *, int, int, int);

void FUN_00448430(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3) {
    FUN_00448190(arg0, arg2, arg3);
    FUN_004480a0(arg0, arg2, arg3);
    FUN_00448410(arg0, arg1, arg0->_pocket, arg0->_revision);
}
} /* extern "C" */
