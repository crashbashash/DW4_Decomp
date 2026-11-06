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
extern igMetaObject *g_beDemoManager_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beDemoManager_GetMetaObject(void);
extern const char beDemoManager_className[];
int beDemoManager_GetVTable(void);
void beDemoManager_InitFields(void);
extern char g_beDemoManager_callbackList[];
void *beDemoManager_Register(void);
}

void *beDemoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beDemoManager_GetMetaObject,
        beDemoManager_className,
        0x24, /* instance size */
        beDemoManager_GetVTable,
        beDemoManager_InitFields,
        0, /* extra callback item */
        g_beDemoManager_callbackList /* callback list */
    );
}
