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
extern igMetaObject *g_beBaseInfoManager_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoManager_GetMetaObject(void);
extern const char beBaseInfoManager_className[];
void beBaseInfoManager_InitFields(void);
extern char g_beBaseInfoManager_callbackList[];
void *beBaseInfoManager_Register(void);
}

void *beBaseInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBaseInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beBaseInfoManager_GetMetaObject,
        beBaseInfoManager_className,
        0x20, /* instance size */
        0,
        beBaseInfoManager_InitFields,
        0, /* extra callback item */
        g_beBaseInfoManager_callbackList /* callback list */
    );
}
