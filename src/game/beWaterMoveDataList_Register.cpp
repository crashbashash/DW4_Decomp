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
extern igMetaObject *g_beWaterMoveDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beWaterMoveDataList_GetMetaObject(void);
extern const char beWaterMoveDataList_className[];
int beWaterMoveDataList_GetVTable(void);
extern char g_beWaterMoveDataList_callbackList[];
void *beWaterMoveDataList_Register(void);
}

void *beWaterMoveDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterMoveDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWaterMoveDataList_GetMetaObject,
        beWaterMoveDataList_className,
        0x14, /* instance size */
        beWaterMoveDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWaterMoveDataList_callbackList /* callback list */
    );
}
