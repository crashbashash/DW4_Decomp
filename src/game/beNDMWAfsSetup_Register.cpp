struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWAfsSetup_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWAfsSetup_GetMetaObject(void);
extern const char beNDMWAfsSetup_className[];
int beNDMWAfsSetup_GetVTable(void);
void beNDMWAfsSetup_InitFields(void);
extern char g_beNDMWAfsSetup_callbackList[];
void *beNDMWAfsSetup_Register(void);
}

void *beNDMWAfsSetup_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetup_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beNDMWAfsSetup_GetMetaObject,
        beNDMWAfsSetup_className,
        0x20, /* instance size */
        beNDMWAfsSetup_GetVTable,
        beNDMWAfsSetup_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetup_callbackList /* callback list */
    );
}
