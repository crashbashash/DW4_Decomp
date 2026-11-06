#include "dw4/reflected.h"
int FUN_00236c40();
int igObject_Destroy();

void Gap__Insight__igViewerDataPumpManager__vfunc_28(igViewerDataPumpManager *arg0) {
    igDataPumpList *l;
    int n;
    int i;
    int off;
    int m;
    int j;
    int lim;
    int off2;
    igObject *o;

    l = (igDataPumpList *)(((igDataPumpManager *)arg0->_dataPumpManager)->_dataPumpList);
    n = l->_count;
    i = 0;
    if (0 < n) {
        off = 0;
        do {
            o = (igObject *)(*(int *)((char *)l->_data + off));
            if (o != 0) {
                *(int *)&o->_refCount = *(int *)&o->_refCount - 1;
                if (((unsigned long long) ((long long) *(int *)&o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            i += 1;
            off += 4;
        } while (i < n);
    }
    m = l->_count;
    j = 0;
    if (0 < m) {
        if (m > 8) {
            lim = m - 8;
            off2 = 0;
            do {
                j += 8;
                *(int *)((char *)l->_data + off2) = 0;
                *(int *)((char *)l->_data + off2 + 4) = 0;
                *(int *)((char *)l->_data + off2 + 8) = 0;
                *(int *)((char *)l->_data + off2 + 12) = 0;
                *(int *)((char *)l->_data + off2 + 16) = 0;
                *(int *)((char *)l->_data + off2 + 20) = 0;
                *(int *)((char *)l->_data + off2 + 24) = 0;
                *(int *)((char *)l->_data + off2 + 28) = 0;
                off2 += 0x20;
            } while (j < lim);
        }
        off2 = j * 4;
        if (j < m) {
            do {
                j += 1;
                *(int *)((char *)l->_data + off2) = 0;
                off2 += 4;
            } while (j < m);
        }
    }
    l->_count = 0;
    FUN_00236c40(arg0->_insight, arg0);
}
