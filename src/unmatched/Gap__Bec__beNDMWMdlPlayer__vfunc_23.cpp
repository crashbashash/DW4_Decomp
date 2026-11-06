#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236f80(int, int);
int Gap__Core__igObject__vfunc_23();
extern int DAT_00588518[4];
extern int DAT_0058c0a0[4];
extern int DAT_0058c790[4];
void Gap__Bec__beNDMWMdlPlayer__vfunc_23(beNDMWMdlPlayer *arg0) {
    Gap__Core__igObject__vfunc_23();
    arg0->_gameRam = FUN_00236f80(arg0->_insight, DAT_0058c0a0[0]);
    arg0->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
    arg0->_viewerSIManager = FUN_00236f80(arg0->_insight, DAT_0058c790[0]);
}
} /* extern "C" */
