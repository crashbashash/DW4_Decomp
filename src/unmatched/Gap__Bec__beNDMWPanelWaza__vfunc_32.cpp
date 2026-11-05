#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00588518[4];
void Gap__Bec__beNDMWPanelWaza__vfunc_32(beNDMWPanelWaza *arg0) {
    if (arg0->_padManager == 0) {
        arg0->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
    }
}
} /* extern "C" */
