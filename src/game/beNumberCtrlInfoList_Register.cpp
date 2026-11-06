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
extern igMetaObject *g_beNumberCtrlInfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNumberCtrlInfoList_GetMetaObject(void);
extern const char beNumberCtrlInfoList_className[];
int beNumberCtrlInfoList_GetVTable(void);
extern char g_beNumberCtrlInfoList_callbackList[];
void *beNumberCtrlInfoList_Register(void);
}

void *beNumberCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumberCtrlInfoList_GetMetaObject,
        beNumberCtrlInfoList_className,
        0x14, /* instance size */
        beNumberCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumberCtrlInfoList_callbackList /* callback list */
    );
}
