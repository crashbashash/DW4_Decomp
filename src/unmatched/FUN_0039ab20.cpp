/* 0x0039ab20 — FUN_0039ab20. Sibling of FUN_003a3960 (timed item start with an optional pending-state flush first). Alternate -O3,p (flags row); the pool pointer is read after the clock call. */
#include "dw4/reflected.h"
extern "C" {
int FUN_001b1490(...);
int FUN_001e07a0(void *, void *);
int FUN_001dca40(void *, void *);
int List_Resize(void *, int, int);
int FUN_00130f20();
int FUN_0039a960(void *, long long, long long);
long long FUN_0039a9e0(void *, long long);
}
typedef int (*CB)(void *, int, void *);
/* vtable view of the traversal context (igCommonTraversal): slots 24/30/31 only */
class Vt { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long v24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(long long);
    virtual void v31();
};
/* matching construct: the 4-byte reference fields (_attrStack, _timePool, _attrStacks, _data, _popProc, ...) are viewed through pointer casts; no layout effect */
extern "C" int FUN_0039ab20(beNodeAnim *arg0, igCommonTraversal *arg1)
{
    igTimeAttr * volatile spAC;
    long long t;
    long long dd;
    igObjectPool *p;
    igTimeAttr *item;
    int cnt2;
    igAttrStackManager *b;
    int cnt;
    igAttrStack *l;
    int idx;
    int r;
    int idx2;
    igAttrStack *l2;
    CB cb;
    void *ob;
    int ix;
    void **dp;
    short *pg;
    short *pi;

    b = (igAttrStackManager *)arg1->_attrStack;
    t = ((Vt *)arg1)->v24();
    if (arg0->_isFirstTime != 0) {
        FUN_0039a960(arg0, arg0->_startTime, t);
        arg0->_beforeTime = t;
        arg0->_isFirstTime = 0;
    }
    dd = FUN_0039a9e0(arg0, t);
    p = (igObjectPool *)arg1->_timePool;
    if (p->_freeIndex >= p->_count) {
        FUN_001dca40(p, (void *)&FUN_00130f20);
    }
    cnt = p->_freeIndex;
    p->_freeIndex = cnt + 1;
    item = ((igTimeAttr **)p->_data)[cnt];
    item->_time = dd;
    ((Vt *)arg1)->v30(dd);
    pg = &item->_cachedAttrIndex;
    pi = &item->_cachedUnitID;
    idx = *pi + ((int *)b->_attrStackIndexTable)[*pg];
    l = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idx];
    spAC = item;
    cnt2 = *(volatile int *)&l->_count;
    if (cnt2 < l->_capacity) {
        l->_count = l->_count + 1;
    } else {
        List_Resize(l, cnt2 + 1, 4);
    }
    {
        igTimeAttr *a3 = spAC;
        ((void **)l->_data)[cnt2] = a3;
        FUN_001b1490(b, l, idx, a3);
    }
    r = FUN_001e07a0(arg1, arg0);
    idx2 = *pi + ((int *)b->_attrStackIndexTable)[*pg];
    l2 = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idx2];
    ix = l2->_count - 1;
    dp = (void **)l2->_data;
    cb = (CB)l2->_popProc;
    ob = dp[ix];
    if (cb != 0) {
        cb(ob, b->_popProcData, cb);
    }
    l2->_count = l2->_count - 1;
    FUN_001b1490(b, l2, idx2);
    ((Vt *)arg1)->v31();
    if (r == 2) {
        return 2;
    }
    return 0;
}
