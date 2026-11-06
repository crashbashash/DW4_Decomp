#include "dw4/reflected.h"
int FUN_001958f0();
int FUN_00195970();
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_005284f0[4];
extern int DAT_00528dd0[4];

struct S {
    void *f0;
    char pad0[96];
    void *f64;
    void *f68;
};

void *FUN_001962d0(struct S *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_005284f0[0];
        if (&arg0->f68) {
            p = (igObject *)arg0->f68;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f64) {
            p = (igObject *)arg0->f64;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_00528dd0[0];
            FUN_001958f0((char *)arg0 + 0x1C, -1);
            FUN_00195970(arg0, 0);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
