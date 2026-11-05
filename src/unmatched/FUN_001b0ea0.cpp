#include "dw4/reflected.h"
extern "C" {
void *igLightStateAttr_GetMetaObject(...);
unsigned char FUN_001b0ea0(void *arg0, unsigned int arg1);
}
unsigned char FUN_001b0ea0(void *arg0, unsigned int arg1) {
    igAttrStackManager *s = (igAttrStackManager *)arg0;
    if (arg1 == 0) return 0;
    volatile unsigned k1;
    volatile unsigned k2;
    k1 = arg1;
    igUnsignedIntList *l = (igUnsignedIntList *)s->_lightAttrAddrs;
    k2 = k1;
    int mid;
    int lo;
    int hi;
    unsigned key;
    int n;
    int idx;
    unsigned v;
    n = l->_count;
    lo = 0;
    hi = n - 1;
    key = k2;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        v = ((unsigned *)l->_data)[mid];
        if (v < key) lo = mid + 1;
        else if (key < v) hi = mid - 1;
        else { idx = mid; goto found; }
    }
    if (n == 0) idx = -1;
    else {
        v = ((unsigned *)l->_data)[lo];
        unsigned kk = k2;
        if (kk < v || v < kk) idx = -1;
        else idx = lo;
    }
found:
    if (idx != -1) {
        int base = ((int *)((igIntList *)s->_lightAttrStackAddrs)->_data)[idx];
        igMetaObject *m = (igMetaObject *)igLightStateAttr_GetMetaObject();
        igAttrStack *c = ((igAttrStack **)((igObjectList *)s->_attrStacks)->_data)[base + ((int *)s->_attrStackIndexTable)[m->_id]];
        igLightStateAttr *o;
        int cur = c->_cachedOverride;
        if (cur >= 0) o = ((igLightStateAttr **)c->_data)[cur];
        else {
            int cnt = c->_count;
            if (cnt != 0) { int last = cnt - 1; o = ((igLightStateAttr **)c->_data)[last]; }
            else o = (igLightStateAttr *)c->_default;
        }
        return o->_enabled;
    }
    return 0;
}
