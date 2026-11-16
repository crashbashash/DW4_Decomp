unsigned char g_InsightLibrary_registered;

void InsightLibrary_MarkRegistered(void) {
    if (g_InsightLibrary_registered == 0) {
        g_InsightLibrary_registered = 1;
    }
}

void *FUN_00230f70(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igRenderer_vtable[0];
        if (&arg0->f8) {
            p = arg0->f8;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igMetaObject *FUN_00231010(void) {
    return g_igRenderer_metaObject;
}

igMetaObject *FUN_00231020(void) {
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

igMetaObject *FUN_002310d0(void) {
    return g_igInfoManager_metaObject;
}

