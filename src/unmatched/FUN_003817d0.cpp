#include "dw4/reflected.h"
extern "C" {
int igInsightCore_AddInfo(int, igObject *);
int igObject_Destroy(igObject *);
int FUN_003817d0(beFileListInfoManager *arg0);
}

int FUN_003817d0(beFileListInfoManager *arg0) {
    int i;
    igObjectList *l;
    int n;
    int k;
    int j;
    igObject *o;
    l = (igObjectList *)arg0->_readInfoList;
    for (i = 0; i < l->_count; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            igInsightCore_AddInfo(arg0->_insight, o);
        }
        l = (igObjectList *)arg0->_readInfoList;
    }
    n = ((igObjectList *)arg0->_readInfoList)->_count;
    for (k = 0; k < n; k++) {
        o = ((igObject **)l->_data)[k];
        if (o != 0) {
            /* matching construct: _refCount is unsigned in the metadata; the retail load is the signed lw */
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m2 = l->_count;
        int j2;
        for (j2 = 0; j2 < m2; j2++) {
            ((igObject **)l->_data)[j2] = 0;
        }
    }
    l->_count = 0;
    return 1;
}
