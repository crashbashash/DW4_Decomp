#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_003b2840();
int beMessenger_ResolveEnumValue(int, int, int);
extern char GPR_00554e70;

int Gap__Bec__beNDMWTitle2__vfunc_34(beNDMWTitle2 *arg0, beBaseInfoRam *arg1, void *arg2) {
    int temp_v0;

    if (arg1->_dataList == 0) {
        return 1;
    }
    temp_v0 = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003b2840(), *(int *)((char *)(arg2) + 20));
    switch (temp_v0) {
    case 0:
        arg1->_st0 = 1;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
        break;
    case 1:
        GPR_00554e70 = 1;
        break;
    }
    return 1;
}
} /* extern "C" */
