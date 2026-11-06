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
extern igMetaObject *g_beAsTargetModelDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beAsTargetModelDataList_GetMetaObject(void);
extern const char beAsTargetModelDataList_className[];
int beAsTargetModelDataList_GetVTable(void);
extern char g_beAsTargetModelDataList_callbackList[];
void *beAsTargetModelDataList_Register(void);
}

void *beAsTargetModelDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAsTargetModelDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAsTargetModelDataList_GetMetaObject,
        beAsTargetModelDataList_className,
        0x14, /* instance size */
        beAsTargetModelDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAsTargetModelDataList_callbackList /* callback list */
    );
}
