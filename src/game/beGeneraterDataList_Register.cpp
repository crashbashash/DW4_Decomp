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
extern igMetaObject *g_beGeneraterDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beGeneraterDataList_GetMetaObject(void);
extern const char beGeneraterDataList_className[];
int beGeneraterDataList_GetVTable(void);
extern char g_beGeneraterDataList_callbackList[];
void *beGeneraterDataList_Register(void);
}

void *beGeneraterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterDataList_GetMetaObject,
        beGeneraterDataList_className,
        0x14, /* instance size */
        beGeneraterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterDataList_callbackList /* callback list */
    );
}
