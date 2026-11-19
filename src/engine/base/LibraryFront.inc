unsigned char g_BaseLibrary_registered;

void BaseLibrary_MarkRegistered(void) {
    if (g_BaseLibrary_registered == 0) {
        g_BaseLibrary_registered = 1;
    }
}

void *FUN_00225790(igOptBase *self, short deleteFlag) {
    igObject *p;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&DAT_0052bea0[0];
        if (&self->_configuration) {
            p = (igObject *)self->_configuration;
            if (p != 0) {
                rc = (int) p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&self->_registry) {
            p = (igObject *)self->_registry;
            if (p != 0) {
                rc = (int) p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

