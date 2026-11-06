extern "C" {
int FUN_001b1490(...);
int FUN_001e07a0(void *, void *);
int FUN_001dca40(void *, void *);
int List_Resize(void *, int, int);
int FUN_001356b0();
int igMatrix44f_SetIdentity(void *);
int FUN_001904f0(void *, void *, void *);
int Matrix44_Copy(void *, void *);
}
#include "dw4/reflected.h"
typedef int (*CB)(void *, int, void *);
class Item { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(void *);
};
struct Mat { int w[16]; };
struct Rec { int pad[8]; Mat m32; int pad2[3]; Mat *src108; };
struct Dat { int pad[2]; int f8; };
extern Dat *DAT_0055efe8[4];
/* matching construct: the reflected fields hold 4-byte handles (_attrStack is the igAttrStackManager, _matrixPool an igObjectPool of igAttr subclasses, _attrStacks an igObjectList of igAttrStack); the casts give the typed views (no layout effect) */
extern "C" int FUN_0037b4d0(Rec *arg0, igCommonTraversal *arg1)
{
    igAttrStackManager *b;
    Item * volatile spAC;
    Mat mA;
    Mat mB;
    igObjectPool *p;
    Item *item;
    int cnt2;
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
    igAttrStack *l0;
    int n1;

    b = (igAttrStackManager *)arg1->_attrStack;
    ix = DAT_0055efe8[0]->f8;
    l0 = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[((int *)b->_attrStackIndexTable)[ix]];
    Matrix44_Copy(&arg0->m32, &arg0->src108->w[8]);
    igMatrix44f_SetIdentity(&mA);
    if (l0->_count != 0) {
        n1 = l0->_count - 1;
        FUN_001904f0(&mA, &arg0->m32, (char *)((void **)l0->_data)[n1] + 12);
    } else {
        igMatrix44f_SetIdentity(&mB);
        FUN_001904f0(&mA, &arg0->m32, &mB);
    }
    p = (igObjectPool *)arg1->_matrixPool;
    if (p->_freeIndex >= p->_count) {
        FUN_001dca40(p, (void *)&FUN_001356b0);
    }
    cnt = p->_freeIndex;
    p->_freeIndex = cnt + 1;
    item = ((Item **)p->_data)[cnt];
    item->v30(&mA);
    pg = &((igAttr *)item)->_cachedAttrIndex;
    pi = &((igAttr *)item)->_cachedUnitID;
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
        Item *a3 = spAC;
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
    if (r == 2) {
        return 2;
    }
    return 0;
}
