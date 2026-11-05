/* 0x0044be30 — FUN_0044be30. m2c draft, hand-fixed; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
#include "dw4/reflected.h"
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00541e90[4];

void *FUN_0044be30(igGeometryElement *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00541e90[0];
        if (&arg0->_sharableAttrs) {
            p = (igObject *)arg0->_sharableAttrs;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_geometry) {
            p = (igObject *)arg0->_geometry;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
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
