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
extern igMetaObject *g_beMessenger_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beMessenger_GetMetaObject(void);
extern const char beMessenger_className[];
int beMessenger_GetVTable(void);
void beMessenger_InitFields(void);
extern char g_beMessenger_callbackList[];
void *beMessenger_Register(void);
}

void *beMessenger_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessenger_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beMessenger_GetMetaObject,
        beMessenger_className,
        0x38, /* instance size */
        beMessenger_GetVTable,
        beMessenger_InitFields,
        0, /* extra callback item */
        g_beMessenger_callbackList /* callback list */
    );
}
