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
extern igMetaObject *g_beBaseInfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoList_GetMetaObject(void);
extern const char beBaseInfoList_className[];
int beBaseInfoList_GetVTable(void);
extern char g_beBaseInfoList_callbackList[];
void *beBaseInfoList_Register(void);
}

void *beBaseInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoList_GetMetaObject,
        beBaseInfoList_className,
        0x14, /* instance size */
        beBaseInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoList_callbackList /* callback list */
    );
}
