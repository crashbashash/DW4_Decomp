unsigned char g_InsightLibrary_registered;

void InsightLibrary_MarkRegistered(void) {
    if (g_InsightLibrary_registered == 0) {
        g_InsightLibrary_registered = 1;
    }
}

igRenderer *igRenderer_Destroy(igRenderer *self, short deleteFlag) {
    igObject *context;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igRenderer_vtable[0];
        if (&self->_visualContext) {
            context = (igObject *)self->_visualContext;
            if (context != 0) {
                rc = context->_refCount - 1;
                context->_refCount = rc;
                if (((unsigned long long) ((long long) (int)context->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(context);
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igMetaObject *FUN_00231010(void) {
    return g_igRenderer_metaObject;
}

igMetaObject *igMessage_GetPublishedMetaObject(void) {
    return g_igMessage_metaObject;
}

void *igInfoManager_Destroy(igInfoManager *manager, short flags) {
    void *p;
    int *h;
    int rc;

    if (manager != 0) {
        manager->_vtable = (int)g_igInfoManager_vtable;
        if (manager != 0) {
            manager->_vtable = (int)g_igNamedObject_vtable;
            if (&manager->_name) {
                p = (void *)manager->_name;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
                    }
                }
            }
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(manager);
        }
    }
    return manager;
}

igMetaObject *igInfoManager_GetPublishedMetaObject(void) {
    return g_igInfoManager_metaObject;
}

