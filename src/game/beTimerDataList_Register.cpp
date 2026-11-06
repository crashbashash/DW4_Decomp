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
extern igMetaObject *g_beTimerDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beTimerDataList_GetMetaObject(void);
extern const char beTimerDataList_className[];
int beTimerDataList_GetVTable(void);
extern char g_beTimerDataList_callbackList[];
void *beTimerDataList_Register(void);
}

void *beTimerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTimerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTimerDataList_GetMetaObject,
        beTimerDataList_className,
        0x14, /* instance size */
        beTimerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beTimerDataList_callbackList /* callback list */
    );
}
