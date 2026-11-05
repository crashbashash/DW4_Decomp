#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_003c22e0();
int beMessenger_ResolveEnumValue(int, int, int);

int Gap__Bec__beNDMWLogo__vfunc_34(beNDMWLogo *arg0, beBaseInfoRam *arg1, void *arg2) {
    if (arg1->_dataList == 0) {
        return 1;
    }
    beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003c22e0(), *(int *)((char *)(arg2) + 20));
    return 1;
}
} /* extern "C" */
