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
extern igMetaObject *g_beSystem_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beSystem_GetMetaObject(void);
extern const char beSystem_className[];
int beSystem_GetVTable(void);
void beSystem_InitFields(void);
extern char g_beSystem_callbackList[];
void *beSystem_Register(void);
}

void *beSystem_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSystem_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beSystem_GetMetaObject,
        beSystem_className,
        0x68, /* instance size */
        beSystem_GetVTable,
        beSystem_InitFields,
        0, /* extra callback item */
        g_beSystem_callbackList /* callback list */
    );
}
