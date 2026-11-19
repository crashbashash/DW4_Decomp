unsigned char g_InsightLibrary_registered;

void InsightLibrary_MarkRegistered(void) {
    if (g_InsightLibrary_registered == 0) {
        g_InsightLibrary_registered = 1;
    }
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

