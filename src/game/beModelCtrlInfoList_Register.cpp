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
extern igMetaObject *g_beModelCtrlInfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoList_GetMetaObject(void);
extern const char beModelCtrlInfoList_className[];
int beModelCtrlInfoList_GetVTable(void);
extern char g_beModelCtrlInfoList_callbackList[];
void *beModelCtrlInfoList_Register(void);
}

void *beModelCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlInfoList_GetMetaObject,
        beModelCtrlInfoList_className,
        0x14, /* instance size */
        beModelCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlInfoList_callbackList /* callback list */
    );
}
