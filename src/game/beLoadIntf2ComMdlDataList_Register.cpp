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
extern igMetaObject *g_beLoadIntf2ComMdlDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beLoadIntf2ComMdlDataList_GetMetaObject(void);
extern const char beLoadIntf2ComMdlDataList_className[];
int beLoadIntf2ComMdlDataList_GetVTable(void);
extern char g_beLoadIntf2ComMdlDataList_callbackList[];
void *beLoadIntf2ComMdlDataList_Register(void);
}

void *beLoadIntf2ComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLoadIntf2ComMdlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLoadIntf2ComMdlDataList_GetMetaObject,
        beLoadIntf2ComMdlDataList_className,
        0x14, /* instance size */
        beLoadIntf2ComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLoadIntf2ComMdlDataList_callbackList /* callback list */
    );
}
