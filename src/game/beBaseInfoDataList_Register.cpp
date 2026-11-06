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
extern igMetaObject *g_beBaseInfoDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoDataList_GetMetaObject(void);
extern const char beBaseInfoDataList_className[];
int beBaseInfoDataList_GetVTable(void);
extern char g_beBaseInfoDataList_callbackList[];
void *beBaseInfoDataList_Register(void);
}

void *beBaseInfoDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoDataList_GetMetaObject,
        beBaseInfoDataList_className,
        0x14, /* instance size */
        beBaseInfoDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoDataList_callbackList /* callback list */
    );
}
