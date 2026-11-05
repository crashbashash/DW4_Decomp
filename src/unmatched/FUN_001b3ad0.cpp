#include "dw4/reflected.h"
extern "C" {
int FUN_001b1e50(...);
int FUN_001c5660(...);
}
class H { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(int, int); char p0[180]; igBitMask *f184; };
extern "C" igMetaObject *igTextureBindAttr_GetMetaObject(...);
extern "C" igMetaObject *DAT_0055efe8[4];
extern "C" H *DAT_005625f0[4];
extern "C" int FUN_001b3ad0(igCommonTraversal *arg0, int arg1);
int FUN_001b3ad0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *p;
    igMetaObject *mo;
    igAttrStack *a0;
    igAttrStack *l;
    int a2;
    int km;
    int k;
    unsigned s2;
    bool flag;
    igBitMask *b;
    igBitMask *b2;
    unsigned idx;
    int n;
    unsigned *d;
    unsigned w;
    unsigned idx2;
    unsigned w2;

    p = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[DAT_0055efe8[0]->_id]];
    k = a0->_count;
    km = k - 1;
    if (k == 0) {
        a2 = 0;
    } else {
        a2 = ((int *)a0->_data)[km];
    }
    DAT_005625f0[0]->vX(arg1, a2);
    mo = igTextureBindAttr_GetMetaObject();
    p = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[mo->_id]];
    if (l != 0) {
        flag = !(l->_count == 0);
    } else {
        flag = 0;
    }
    b = DAT_005625f0[0]->f184;
    s2 = b->_bitCount;
    FUN_001b1e50(b, s2 + 1);
    b2 = DAT_005625f0[0]->f184;
    if (flag) {
        idx = s2 >> 5;
        w = ((unsigned *)b2->_data)[idx] | (1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx >= 0 && (int)idx < b2->_count) {
            ((unsigned *)b2->_data)[idx] = w;
        }
    } else {
        idx2 = s2 >> 5;
        w2 = ((unsigned *)b2->_data)[idx2] & ~(1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx2 >= 0 && (int)idx2 < b2->_count) {
            ((unsigned *)b2->_data)[idx2] = w2;
        }
    }
    FUN_001c5660(arg1, 4, 1);
    return 0;
}
