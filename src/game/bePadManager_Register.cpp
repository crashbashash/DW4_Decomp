struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_bePadManager_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *bePadManager_GetMetaObject(void);
extern const char bePadManager_className[];
int bePadManager_GetVTable(void);
void bePadManager_InitFields(void);
extern char g_bePadManager_callbackList[];
void *bePadManager_Register(void);
}

void *bePadManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePadManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        bePadManager_GetMetaObject,
        bePadManager_className,
        0x20, /* instance size */
        bePadManager_GetVTable,
        bePadManager_InitFields,
        0, /* extra callback item */
        g_bePadManager_callbackList /* callback list */
    );
}
