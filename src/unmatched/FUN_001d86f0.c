#include "dw4/reflected.h"
struct S { char pad0[8]; igObjectList *f8; };
int igObject_Destroy(igObject *);
void FUN_001d86f0(struct S *arg0, int arg1, igObject *arg2) {
    igObjectList *l;
    int off;
    int n;
    igObject *old;
    l = arg0->f8;
    if (arg2 != 0) {
        arg2->_refCount = arg2->_refCount + 1;
    }
    off = arg1 * 4;
    old = *(igObject **)(l->_data + off);
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long) ((long long) (int) old->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    n = l->_count;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        *(igObject **)(l->_data + off) = arg2;
    }
}
