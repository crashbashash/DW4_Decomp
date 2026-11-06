#include "dw4/reflected.h"
extern "C" {
int FUN_004480a0(beNDMWItemBlueArmor *, int, int);
int FUN_00448190(beNDMWItemBlueArmor *, int, int);
int FUN_00448410(beNDMWItemBlueArmor *, int, int, int);

void FUN_00448430(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3) {
    FUN_00448190(arg0, arg2, arg3);
    FUN_004480a0(arg0, arg2, arg3);
    FUN_00448410(arg0, arg1, arg0->_pocket, arg0->_revision);
}
}
