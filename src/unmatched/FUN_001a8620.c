#include "dw4/reflected.h"
int igObject_Destroy();
int StringChunk_ReleaseHeader();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00529c40[4];
extern int DAT_00524950[4];

struct S {
    void *f0;
    char pad0[4];
    void *f8;
    igObject *fc;
};

void *FUN_001a8620(struct S *arg0, short arg1) {
    igObject *p;
    void *hp;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00529c40[0];
        if (&arg0->fc) {
            p = arg0->fc;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_00524950[0];
            if (&arg0->f8) {
                hp = arg0->f8;
                if (hp != 0) {
                    h = (int *)((char *)(hp) - 8);
                    rc = *(int *)((char *)(hp) - 4) - 1;
                    *(int *)((char *)(hp) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
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
