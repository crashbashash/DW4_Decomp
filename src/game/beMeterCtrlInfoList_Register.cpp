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
extern igMetaObject *g_beMeterCtrlInfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMeterCtrlInfoList_GetMetaObject(void);
extern const char beMeterCtrlInfoList_className[];
int beMeterCtrlInfoList_GetVTable(void);
extern char pq5[];
void *beMeterCtrlInfoList_Register(void);
}

void *beMeterCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMeterCtrlInfoList_GetMetaObject,
        beMeterCtrlInfoList_className,
        0x14, /* instance size */
        beMeterCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        pq5 /* callback list */
    );
}
