#include "dw4/reflected.h"
int FUN_00100610();
int FUN_00234ca0();
int igObject_Destroy();
int StringChunk_ReleaseHeader();

struct App {
    void *f0;
    char pad[228];
    igObject *f232;
    igObject *f236;
};

void *FUN_00234b90(struct App *arg0, short arg1) {
    igObject *p;
    void *q;
    int *h;
    int rc;

    if (arg0 != 0) {
        FUN_00234ca0(arg0);
        if (&arg0->f236) {
            p = arg0->f236;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f232) {
            p = arg0->f232;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            q = arg0->f0;
            if (q != 0) {
                h = (int *)((char *)(q) - 8);
                rc = *(int *)((char *)(q) - 4) - 1;
                *(int *)((char *)(q) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
