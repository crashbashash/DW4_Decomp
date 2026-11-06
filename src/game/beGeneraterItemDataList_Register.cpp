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
extern igMetaObject *g_beGeneraterItemDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beGeneraterItemDataList_GetMetaObject(void);
extern const char beGeneraterItemDataList_className[];
int beGeneraterItemDataList_GetVTable(void);
extern char g_beGeneraterItemDataList_callbackList[];
void *beGeneraterItemDataList_Register(void);
}

void *beGeneraterItemDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterItemDataList_GetMetaObject,
        beGeneraterItemDataList_className,
        0x14, /* instance size */
        beGeneraterItemDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataList_callbackList /* callback list */
    );
}
