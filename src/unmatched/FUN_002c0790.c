/* 0x002c0790 — FUN_002c0790. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00524950[4];
extern int DAT_00530150[4];

void *FUN_002c0790(igFile *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00530150[0];
        if (&arg0->_completeFilename) {
            p = (void *)arg0->_completeFilename;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
        }
        if (&arg0->_fileName) {
            p = (void *)arg0->_fileName;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)&DAT_00524950[0];
            if (&arg0->_name) {
                p = (void *)arg0->_name;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
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
