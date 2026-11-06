#include "dw4/reflected.h"
/* igObject header: vtable and reference count (the count is not a reflected field) */
extern "C" {
int igObject_Destroy(igObject *);
void Gap__Core__igObject__vfunc_08__002ff0f0(beNDMWLoadCtrl2CommonIntf *);
void Gap__Bec__beNDMWLoadCtrl2CommonIntf__vfunc_08(beNDMWLoadCtrl2CommonIntf *arg0) {
    beNDMWDegiDataList *l = (beNDMWDegiDataList *)arg0->_gameUseData;
    /* matching construct: volatile read forces the early count load */
    if (((volatile beNDMWDegiDataList *)l)->_count > 0) {
        int n = l->_count;
        int i;
        igObject *o;
        for (i = 0; i < n; i++) {
            o = ((igObject **)l->_data)[i];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        {
            int m = l->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l->_data)[j] = 0;
            }
        }
        l->_count = 0;
    }
    {
    beNDMWLoadSavePlWorkList *l2 = (beNDMWLoadSavePlWorkList *)arg0->_flagWork;
    /* matching construct: volatile read forces the early count load */
    if (((volatile beNDMWLoadSavePlWorkList *)l2)->_count > 0) {
        int n = l2->_count;
        int i;
        igObject *o;
        for (i = 0; i < n; i++) {
            o = ((igObject **)l2->_data)[i];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        {
            int m = l2->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l2->_data)[j] = 0;
            }
        }
        l2->_count = 0;
    }
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
}
