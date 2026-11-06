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
extern igMetaObject *g_beHitLandResultDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beHitLandResultDataList_GetMetaObject(void);
extern const char beHitLandResultDataList_className[];
int beHitLandResultDataList_GetVTable(void);
extern char g_beHitLandResultDataList_callbackList[];
void *beHitLandResultDataList_Register(void);
}

void *beHitLandResultDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandResultDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beHitLandResultDataList_GetMetaObject,
        beHitLandResultDataList_className,
        0x14, /* instance size */
        beHitLandResultDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beHitLandResultDataList_callbackList /* callback list */
    );
}
