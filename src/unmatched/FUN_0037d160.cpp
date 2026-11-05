/* 0x0037d160 - FUN_0037d160. Forwards three floats to FUN_003a7590 for the beCri handle (the BGM or ambience stream handle, then the effect list) whose 64-bit play id equals arg1; alternate compiler. Receivers by the matched beSound::vfunc_34 (case 5 passes the beCri). */
#include "dw4/reflected.h"
extern "C" {
void FUN_003a7590(int, int, float, float, float);
void FUN_0037d160(beCri *arg0, long long arg1, float fparg0, float fparg1, float fparg2);
}

void FUN_0037d160(beCri *arg0, long long arg1, float fparg0, float fparg1, float fparg2) {
    beCriHandle *c;
    int i;
    c = (beCriHandle *)arg0->_hdBGM;
    if (arg1 == c->_playID) {
        FUN_003a7590(c->_volume, arg0->_baseVolume, fparg0, fparg1, fparg2);
        return;
    }
    c = (beCriHandle *)arg0->_hdENV;
    if (arg1 == c->_playID) {
        FUN_003a7590(c->_volume, arg0->_baseVolume, fparg0, fparg1, fparg2);
        return;
    }
    for (i = 0; i < ((igObjectList *)arg0->_hdSEs)->_count; i++) {
        c = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[i];
        if (arg1 == c->_playID) {
            FUN_003a7590(c->_volume, arg0->_baseVolume, fparg0, fparg1, fparg2);
        }
    }
}
