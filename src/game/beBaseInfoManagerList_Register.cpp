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
extern igMetaObject *g_beBaseInfoManagerList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoManagerList_GetMetaObject(void);
extern const char beBaseInfoManagerList_className[];
int beBaseInfoManagerList_GetVTable(void);
extern char g_beBaseInfoManagerList_callbackList[];
void *beBaseInfoManagerList_Register(void);
}

void *beBaseInfoManagerList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoManagerList_GetMetaObject,
        beBaseInfoManagerList_className,
        0x14, /* instance size */
        beBaseInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoManagerList_callbackList /* callback list */
    );
}
