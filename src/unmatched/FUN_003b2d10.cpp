#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(igObject *);
int thunk_FUN_002ed460__002ff810(beNDMWWindowCtrl *);
extern int DAT_0053dc30[4];
void *FUN_003b2d10(beNDMWWindowCtrl *arg0, short arg1);
}

void *FUN_003b2d10(beNDMWWindowCtrl *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_0053dc30[0];
        if (&arg0->_modelCloseSeqNameList) {
            p = (igObject *)arg0->_modelCloseSeqNameList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_modelCloseRamNoList) {
            p = (igObject *)arg0->_modelCloseRamNoList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_modelCloseInfoNameList) {
            p = (igObject *)arg0->_modelCloseInfoNameList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_textCloseNameList) {
            p = (igObject *)arg0->_textCloseNameList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_textCloseTypeList) {
            p = (igObject *)arg0->_textCloseTypeList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_mother) {
            p = (igObject *)arg0->_mother;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_subWindow) {
            p = (igObject *)arg0->_subWindow;
            if (p != 0) {
                rc = p->_refCount - 1;
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
