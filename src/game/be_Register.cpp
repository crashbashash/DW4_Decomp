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
extern igMetaObject *g_be_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *be_GetMetaObject(void);
extern const char be_className[];
int be_GetVTable(void);
void be_InitFields(void);
extern char g_be_callbackList[];
void *be_Register(void);
}

void *be_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_be_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        be_GetMetaObject,
        be_className,
        0x14, /* instance size */
        be_GetVTable,
        be_InitFields,
        0, /* extra callback item */
        g_be_callbackList /* callback list */
    );
}
