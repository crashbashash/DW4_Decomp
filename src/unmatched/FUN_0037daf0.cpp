#include "dw4/reflected.h"
extern "C" {
int FUN_00281cf8(...);
int FUN_0037d680(...);
int Memory_FreeBuffer(...);
extern int DAT_0058a460[4];
}
extern "C" bool FUN_0037daf0(beCri *arg0) {
    int st;
    beCriSfpData *nx;
    bool ok;
    int i;
    int *p;
    int off;
    beCriSfpData *e;

    ok = true;
    i = 0;
    if (0 < ((igObjectList *)arg0->_lsBinObjs)->_count) {
        off = 0;
        p = &DAT_0058a460[0];
        do {
            if (*p != 0 && *p != 2) {
                *p = FUN_00281cf8(i);
                st = *p;
                switch (st) {
                case 1:
                    return false;
                case 2:
                    e = *(beCriSfpData **)((char *)((igObjectList *)arg0->_lsBinObjs)->_data + off);
                    Memory_FreeBuffer(e->_dataBuffer);
                    e->_dataBuffer = 0;
                    e->_isTransfer = 1;
                    if (i < ((igObjectList *)arg0->_lsBinObjs)->_count - 1) {
                        nx = *(beCriSfpData **)((char *)((igObjectList *)arg0->_lsBinObjs)->_data + off + 4);
                        if (nx->_isTransfer == 0) {
                            FUN_0037d680(arg0, nx);
                        }
                    }
                    break;
                case 3:
                    ok = false;
                    break;
                default:
                    ok = false;
                    break;
                }
            }
            i += 1;
            p += 1;
            off += 4;
        } while (i < ((igObjectList *)arg0->_lsBinObjs)->_count);
    }
    return ok;
}
