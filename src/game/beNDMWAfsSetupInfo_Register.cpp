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
extern igMetaObject *g_beNDMWAfsSetupInfo_metaObject[];
void *igInfo_Register(void);
igMetaObject *igInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWAfsSetupInfo_GetMetaObject(void);
extern const char beNDMWAfsSetupInfo_className[];
int beNDMWAfsSetupInfo_GetVTable(void);
void beNDMWAfsSetupInfo_InitFields(void);
extern char g_beNDMWAfsSetupInfo_callbackList[];
void *beNDMWAfsSetupInfo_Register(void);
}

void *beNDMWAfsSetupInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetupInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beNDMWAfsSetupInfo_GetMetaObject,
        beNDMWAfsSetupInfo_className,
        0x1c, /* instance size */
        beNDMWAfsSetupInfo_GetVTable,
        beNDMWAfsSetupInfo_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetupInfo_callbackList /* callback list */
    );
}
