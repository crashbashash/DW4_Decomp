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
extern igMetaObject *g_beSaveIntfComMdlDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beSaveIntfComMdlDataList_GetMetaObject(void);
extern const char beSaveIntfComMdlDataList_className[];
int beSaveIntfComMdlDataList_GetVTable(void);
extern char g_beSaveIntfComMdlDataList_callbackList[];
void *beSaveIntfComMdlDataList_Register(void);
}

void *beSaveIntfComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveIntfComMdlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSaveIntfComMdlDataList_GetMetaObject,
        beSaveIntfComMdlDataList_className,
        0x14, /* instance size */
        beSaveIntfComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSaveIntfComMdlDataList_callbackList /* callback list */
    );
}
