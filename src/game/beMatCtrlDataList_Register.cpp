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
extern igMetaObject *g_beMatCtrlDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMatCtrlDataList_GetMetaObject(void);
extern const char beMatCtrlDataList_className[];
int beMatCtrlDataList_GetVTable(void);
extern char g_beMatCtrlDataList_callbackList[];
void *beMatCtrlDataList_Register(void);
}

void *beMatCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlDataList_GetMetaObject,
        beMatCtrlDataList_className,
        0x14, /* instance size */
        beMatCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlDataList_callbackList /* callback list */
    );
}
