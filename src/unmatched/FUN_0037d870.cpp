#include "dw4/reflected.h"
extern "C" {
int FUN_002813c8(int);
int List_Reserve(...);
int igObject_Destroy(...);
extern int DAT_00589998[4];
extern int DAT_00589ad0[4];
extern int DAT_0058a360[4];
extern int DAT_0058a460[4];
}
/* matching construct: dummy-virtual view (20 slots) so Kind() compiles to the retail jalr; fields are read through beCriSfpData. */
struct SndKindV {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int Kind();
};
extern "C" int FUN_0037d870(beCri *arg0, int arg1) {
    int idx;
    int lo;
    beCriSfpData *e;
    int off;
    int a;
    int b;
    igObjectList *l;
    int n;
    int i;
    beCriSfpData *o;
    igObjectList *l2;
    lo = -(arg1 & 0xFF);
    idx = ((igObjectList *)arg0->_lsBinObjs)->_count - 1;
    if (lo < idx) {
        off = idx * 4;
        do {
            a = DAT_00589ad0[0];
            e = *(beCriSfpData **)((char *)((igObjectList *)arg0->_lsBinObjs)->_data + off);
            if (a != ((SndKindV *)e)->Kind()) {
                b = DAT_00589998[0];
                if (b == ((SndKindV *)e)->Kind() && e->_isTransfer != 0) {
                    int ch = e->_portNo;
                    int k = ch * 4;
                    if (*(int *)((char *)DAT_0058a360 + k) != 0 || *(int *)((char *)DAT_0058a360 + k + 128) != 0) {
                        FUN_002813c8(ch);
                        *(int *)((char *)DAT_0058a360 + k) = 0;
                        *(int *)((char *)DAT_0058a360 + k + 128) = 0;
                        *(int *)((char *)DAT_0058a460 + k) = 0;
                    }
                }
            }
            idx -= 1;
            off -= 4;
        } while (lo < idx);
    }
    l = ((igObjectList *)arg0->_lsBinObjs);
    n = l->_count;
    for (i = 0; i < n; i++) {
        o = (beCriSfpData *)((int *)l->_data)[i];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((int *)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
    l2 = ((igObjectList *)arg0->_lsBinObjs);
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
    return 1;
}
