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
extern igMetaObject *g_beNDMWShinkaObjectList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWShinkaObjectList_GetMetaObject(void);
extern const char beNDMWShinkaObjectList_className[];
int beNDMWShinkaObjectList_GetVTable(void);
extern char g_beNDMWShinkaObjectList_callbackList[];
void *beNDMWShinkaObjectList_Register(void);
}

void *beNDMWShinkaObjectList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShinkaObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWShinkaObjectList_GetMetaObject,
        beNDMWShinkaObjectList_className,
        0x14, /* instance size */
        beNDMWShinkaObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWShinkaObjectList_callbackList /* callback list */
    );
}
