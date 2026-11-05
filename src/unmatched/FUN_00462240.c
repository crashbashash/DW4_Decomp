/* 0x00462240 — FUN_00462240. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_004612b0();
int FUN_00462200();
int FUN_00464080();

void FUN_00462240(igViewerSceneInfoManager *arg0) {
    long long temp_s0;
    igInsightCore *temp_v0;

    FUN_004612b0();
    temp_v0 = (igInsightCore *)arg0->_insight;
    temp_s0 = temp_v0->_frameTime;
    if (arg0->_clippingCheckFrame == temp_v0->_frames) {
        FUN_00462200(arg0);
    }
    FUN_00464080(arg0->_viewManager, temp_s0);
}
