#include "dw4/reflected.h"
extern "C" int FUN_0037d680(void *, void *);
extern int DAT_0058a460[];
extern "C" bool FUN_0037d780(beCri *o) {
    bool ok = true;
    igObjectList *l = (igObjectList *)o->_lsBinObjs;
    if (o->_dataType == 1) {
        bool first = ok;
        int i = 0;
        if (0 < l->_count) {
            do {
                beCriSfpData *e = ((beCriSfpData **)l->_data)[i];
                if (e->_isTransfer == 0) {
                    e->_portNo = i;
                    if (first) {
                        if (FUN_0037d680(o, e) == 0) ok = false;
                        first = false;
                    } else {
                        DAT_0058a460[i] = 1;
                    }
                } else {
                    DAT_0058a460[i] = 2;
                }
                i++;
            } while (i < l->_count);
        }
    }
    return ok;
}
