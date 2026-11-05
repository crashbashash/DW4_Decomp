/* 0x00150490 — FUN_00150490. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
#include "dw4/reflected.h"
int igObject_Destroy();
int StringChunk_ReleaseHeader();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00526800[4];
extern int DAT_00526c50[4];

struct S {
    void *f0;
    char pad0[64];
    void *f44;
    char pad1[16];
    void *f58;
};

void *FUN_00150490(struct S *arg0, short arg1) {
    void *p;
    igObject *o;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00526c50[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00526800[0];
            if (&arg0->f58) {
                p = arg0->f58;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
            if (&arg0->f44) {
                o = (igObject *)arg0->f44;
                if (o != 0) {
                    rc = o->_refCount - 1;
                    o->_refCount = rc;
                    if (((unsigned long long) ((long long) (int) o->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(o);
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
