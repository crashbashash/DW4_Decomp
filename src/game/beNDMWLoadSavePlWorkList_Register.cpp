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
extern igMetaObject *g_beNDMWLoadSavePlWorkList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadSavePlWorkList_GetMetaObject(void);
extern const char beNDMWLoadSavePlWorkList_className[];
int beNDMWLoadSavePlWorkList_GetVTable(void);
extern char g_beNDMWLoadSavePlWorkList_callbackList[];
void *beNDMWLoadSavePlWorkList_Register(void);
}

void *beNDMWLoadSavePlWorkList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSavePlWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadSavePlWorkList_GetMetaObject,
        beNDMWLoadSavePlWorkList_className,
        0x14, /* instance size */
        beNDMWLoadSavePlWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWorkList_callbackList /* callback list */
    );
}
