#include "dw4/reflected.h"
int FUN_0013ba30();
int FUN_0013c060();
int FUN_00460c80();
int ObjectList_AppendRetained();
int igObject_Destroy();

void FUN_00460e00(int *a, void *arg1) {
    igObject *sp3C;
    igObject *sp38;
    igObject *t;

    if ((arg1 != 0) && !(FUN_00460c80(arg1, a[12]) & 0xFF) && !(FUN_00460c80(arg1, a[11]) & 0xFF)) {
        sp38 = (igObject *)(arg1);
        if (sp38 != 0) {
            sp38->_refCount = sp38->_refCount + 1;
        }
        FUN_0013ba30(&sp3C, FUN_0013c060(), &sp38);
        if (sp38 != 0) {
            sp38->_refCount = sp38->_refCount - 1;
            if ((sp38->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(sp38);
            }
        }
        ObjectList_AppendRetained(*(int *)((char *)(a[11]) + 32), sp3C);
        t = sp3C;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if ((t->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
}
