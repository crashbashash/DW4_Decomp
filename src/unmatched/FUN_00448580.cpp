#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_004480a0(beNDMWItemYellowArmor *, int, int);
int FUN_00448560(beNDMWItemYellowArmor *, int, int);

void FUN_00448580(beNDMWItemYellowArmor *arg0, int arg1, int arg2, int arg3) {
    FUN_004480a0(arg0, arg2, arg3);
    FUN_00448560(arg0, arg1, arg0->_revision);
}
} /* extern "C" */
