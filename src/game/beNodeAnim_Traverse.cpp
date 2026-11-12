#include "dw4/reflected.h"
extern "C" {
int igAttrStackManager_MarkStackChanged(...);
int igTraversal_TraverseChildren(void *, void *);
int igObjectPool_Grow(void *, void *);
int List_Resize(void *, int, int);
int igTimeAttr_CreateInstance();
int beNodeAnim_SetTime(void *, long long, long long);
long long beNodeAnim_UpdateTime(void *, long long);
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
extern "C" int beNodeAnim_Traverse(beNodeAnim *arg0, igCommonTraversal *arg1)
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
        beNodeAnim_SetTime(arg0, arg0->_startTime, t);
        arg0->_beforeTime = t;
        arg0->_isFirstTime = 0;
    }
    dd = beNodeAnim_UpdateTime(arg0, t);
    p = (igObjectPool *)arg1->_timePool;
    if (p->_freeIndex >= p->_count) {
        igObjectPool_Grow(p, (void *)&igTimeAttr_CreateInstance);
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
        igAttrStackManager_MarkStackChanged(b, l, idx, a3);
    }
    r = igTraversal_TraverseChildren(arg1, arg0);
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
    igAttrStackManager_MarkStackChanged(b, l2, idx2);
    ((Vt *)arg1)->v31();
    if (r == 2) {
        return 2;
    }
    return 0;
}
