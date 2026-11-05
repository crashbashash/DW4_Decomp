/* 0x00225790 — FUN_00225790. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
#include "dw4/reflected.h"
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_0052bea0[4];

struct S {
    void *f0;
    char pad[28];
    void *f20;
    void *f24;
};

void *FUN_00225790(struct S *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052bea0[0];
        if (&arg0->f24) {
            p = (igObject *)arg0->f24;
            if (p != 0) {
                rc = (int) p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f20) {
            p = (igObject *)arg0->f20;
            if (p != 0) {
                rc = (int) p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
