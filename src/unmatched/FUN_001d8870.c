#include "dw4/reflected.h"
int igObject_Destroy();
struct A { char pad[20]; igObjectList *f20; };
void FUN_001d8870(struct A *arg0, int arg1, igObject *arg2) {
    igObjectList *l;
    igObject *old;
    int n;
    int off;
    l = arg0->f20;
    if (arg2 != 0) {
        arg2->_refCount = arg2->_refCount + 1;
    }
    off = arg1 * 4;
    old = *(igObject **)(l->_data + off);
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    n = l->_count;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        *(igObject **)(l->_data + off) = arg2;
    }
}
