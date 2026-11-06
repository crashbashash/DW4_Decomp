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
extern igMetaObject *g_beNDMWAfsSetupDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWAfsSetupDataList_GetMetaObject(void);
extern const char beNDMWAfsSetupDataList_className[];
int beNDMWAfsSetupDataList_GetVTable(void);
extern char g_beNDMWAfsSetupDataList_callbackList[];
void *beNDMWAfsSetupDataList_Register(void);
}

void *beNDMWAfsSetupDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetupDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWAfsSetupDataList_GetMetaObject,
        beNDMWAfsSetupDataList_className,
        0x14, /* instance size */
        beNDMWAfsSetupDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWAfsSetupDataList_callbackList /* callback list */
    );
}
