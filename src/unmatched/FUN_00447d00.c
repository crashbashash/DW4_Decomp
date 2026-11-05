#include "dw4/reflected.h"
void FUN_00447d00(float *arg0, beNDMWItemBase *arg1) {
    float r = 0.9f, g = 0.9f, b = 0.9f;
    int t = arg1->_kindNo;
    if (t == 3 || t == 4 || t == 5 || t == 6) {
        arg0[0] = 0.9f; arg0[1] = 0.9f; arg0[2] = 0.9f;
        return;
    }
    if ((t == 0 && arg1->_recNo == 0x114) || (t == 1 && arg1->_recNo == 0x1F) || (t == 2 && arg1->_recNo == 0x2C)) {
        arg0[0] = 0.9f; arg0[1] = 0.9f; arg0[2] = 0.9f;
        return;
    }
    {
        int v = ((beNDMWItemRevisionBase *)arg1)->_revision;
        if (v >= 1000) { r = 1.0f; g = 0.0f; b = 0.9f; }
        else if (v >= 501) { r = 1.0f; g = 0.6f; b = 0.1f; }
        else if (v >= 101) { r = 0.9f; g = 0.8f; b = 0.1f; }
        else if (v >= 31) { r = 0.4f; g = 1.0f; b = 0.6f; }
        else if (v > 0) { r = 0.1f; g = 0.9f; b = 1.0f; }
    }
    arg0[0] = r; arg0[1] = g; arg0[2] = b;
}
