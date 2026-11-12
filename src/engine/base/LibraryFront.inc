void BaseLibrary_MarkRegistered(void) {
    if (g_BaseLibrary_registered == 0) {
        g_BaseLibrary_registered = 1;
    }
}

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

