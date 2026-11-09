#include "dw4/reflected.h"

#include "dw4/igTDataList.h"

extern "C" {
int FUN_001b1490(...);
int FUN_001b9530(void *, void *);
int FUN_001dca40(void *, void *);
int FUN_00130f20();
}
typedef int (*CB)(void *, int, void *);
class TraversalTimeOps { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long v24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(long long);
    virtual void v31();
};
extern "C" int FUN_003a3960(ParticleTimer *arg0, igCommonTraversal *arg1)
{
    long long t;
    long long dd;
    igTimeAttrPool *p;
    igAttrStackManager *b;
    igTimeAttr *item;
    int cnt2;
    int cnt;
    igTDataList<igTimeAttr *> *l;
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

    t = ((TraversalTimeOps *)arg1)->v24();
    if (arg0->_time == -1) {
        arg0->_timeBias = t;
    }
    if (arg0->_timeRunning == 0) {
        arg0->_timeBias = arg0->_timeBias + (t - arg0->_time);
    }
    arg0->_time = t;
    dd = arg0->_time - arg0->_timeBias;
    p = (igTimeAttrPool *)arg1->_timePool;
    b = (igAttrStackManager *)arg1->_attrStack;
    if (p->_freeIndex >= p->_count) {
        FUN_001dca40(p, (void *)&FUN_00130f20);
    }
    cnt = p->_freeIndex;
    p->_freeIndex = cnt + 1;
    item = ((igTimeAttr **)p->_data)[cnt];
    item->_time = dd;
    ((TraversalTimeOps *)arg1)->v30(dd);
    pg = &item->_cachedAttrIndex;
    pi = &item->_cachedUnitID;
    l = (igTDataList<igTimeAttr *> *)b->_attrStacks;
    idx = *pg;
    idx = *pi + ((int *)b->_attrStackIndexTable)[idx];
    l = ((igTDataList<igTimeAttr *> **)l->_data)[idx];
    l->append(item);
    FUN_001b1490(b, l, idx);
    r = FUN_001b9530(arg1, arg0);
    idx2 = *pi + ((int *)b->_attrStackIndexTable)[*pg];
    l2 = ((igAttrStack **)((igAttrStackList *)b->_attrStacks)->_data)[idx2];
    ix = l2->_count - 1;
    dp = (void **)l2->_data;
    cb = (CB)l2->_popProc;
    ob = dp[ix];
    if (cb != 0) {
        cb(ob, b->_popProcData, cb);
    }
    l2->_count = l2->_count - 1;
    FUN_001b1490(b, l2, idx2);
    ((TraversalTimeOps *)arg1)->v31();
    return r;
}
