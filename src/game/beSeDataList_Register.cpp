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
extern igMetaObject *g_beSeDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beSeDataList_GetMetaObject(void);
extern const char beSeDataList_className[];
int beSeDataList_GetVTable(void);
extern char g_beSeDataList_callbackList[];
void *beSeDataList_Register(void);
}

void *beSeDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSeDataList_GetMetaObject,
        beSeDataList_className,
        0x14, /* instance size */
        beSeDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSeDataList_callbackList /* callback list */
    );
}
