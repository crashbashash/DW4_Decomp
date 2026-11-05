#include "dw4/reflected.h"
extern "C" int igObject_Destroy(void *);
extern "C" void FUN_00431670(beNDMWShopCtrlEvolve *arg0, igObjectList *arg1) {
    int i;
    int off;
    beNDMWItemBase *o;
    beNDMWItemBase *p;
    i = 0;
    goto guard;
body:
    o = *(beNDMWItemBase **)(arg1->_data + off);
    if (o != 0) o->_isEquip = 0;
    p = *(beNDMWItemBase **)(arg1->_data + off);
    if (p != 0) {
        p->_refCount = (int)p->_refCount - 1;
        if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(p);
    }
    if (arg1->_count != 0 && i >= 0 && i < arg1->_count) *(beNDMWItemBase **)(arg1->_data + off) = 0;
    off += 4;
    i++;
cond:
    if (i < arg1->_count) goto body;
done:
    return;
guard:
    if (0 < arg1->_count) { off = 0; goto cond; }
    goto done;
}
