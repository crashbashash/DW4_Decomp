/* 0x0044a870 — FUN_0044a870. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236f80(int, int);
int beLua__RunNamedChunk(int, int *, int);
extern int DAT_0051dac0[4];
extern int DAT_00589208[4];
extern int DAT_0058a1e0[4];
extern int DAT_0058a220[4];
void FUN_0044a870(beNDMWLogo *arg0, int arg1) {
    int temp_v0;

    temp_v0 = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
    DAT_0058a220[0] = arg1;
    DAT_0058a1e0[0] = 0;
    beLua__RunNamedChunk(temp_v0, &DAT_0051dac0[0], 0);
}
} /* extern "C" */
