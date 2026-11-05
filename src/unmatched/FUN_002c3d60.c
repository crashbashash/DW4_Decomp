/* 0x002c3d60 — FUN_002c3d60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_InitHeader();
extern int DAT_005249b0[4];
extern int DAT_00524a20[4];
extern int DAT_00530890[4];
extern int DAT_005309b0[4];
extern int DAT_00532590[4];
void *FUN_002c3d60(igIGBFile *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_005309b0[0]);
    arg0->_vtable = (int)(&DAT_00524a20[0]);
    arg0->_vtable = (int)(&DAT_005249b0[0]);
    arg0->_vtable = (int)(&DAT_00532590[0]);
    arg0->_vtable = (int)(&DAT_00530890[0]);
    arg0->_name = 0;
    arg0->_externalDirectoryList = 0;
    arg0->_infoList = 0;
    arg0->_uniqueEntryList = 0;
    arg0->_refList = 0;
    arg0->_metaFieldPerObjectIndices = 0;
    arg0->_loadingSemaphore = 0;
    return arg0;
}
