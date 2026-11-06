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
extern igMetaObject *g_beMatCtrlSearchList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMatCtrlSearchList_GetMetaObject(void);
extern const char beMatCtrlSearchList_className[];
int beMatCtrlSearchList_GetVTable(void);
extern char g_beMatCtrlSearchList_callbackList[];
void *beMatCtrlSearchList_Register(void);
}

void *beMatCtrlSearchList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlSearchList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlSearchList_GetMetaObject,
        beMatCtrlSearchList_className,
        0x14, /* instance size */
        beMatCtrlSearchList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlSearchList_callbackList /* callback list */
    );
}
