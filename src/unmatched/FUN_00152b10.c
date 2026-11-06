#include "dw4/reflected.h"
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00526b70[4];
extern int DAT_00527020[4];
extern int DAT_00530a10[4];

struct S {
    void *f0;
    char pad0[4];
    void *f8;
    void *fC;
    void *f10;
};

void *FUN_00152b10(struct S *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00526b70[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00527020[0];
            if (arg0 != 0) {
                arg0->f0 = &DAT_00530a10[0];
                if (&arg0->f10) {
                    p = (igObject *)arg0->f10;
                    if (p != 0) {
                        rc = (int)p->_refCount - 1;
                        p->_refCount = rc;
                        if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(p);
                        }
                    }
                }
                if (&arg0->f8) {
                    p = (igObject *)arg0->f8;
                    if (p != 0) {
                        rc = (int)p->_refCount - 1;
                        p->_refCount = rc;
                        if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(p);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
