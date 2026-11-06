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
extern igMetaObject *g_beCriHandleList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beCriHandleList_GetMetaObject(void);
extern const char beCriHandleList_className[];
int beCriHandleList_GetVTable(void);
extern char g_beCriHandleList_callbackList[];
void *beCriHandleList_Register(void);
}

void *beCriHandleList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriHandleList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beCriHandleList_GetMetaObject,
        beCriHandleList_className,
        0x14, /* instance size */
        beCriHandleList_GetVTable,
        0,
        0, /* extra callback item */
        g_beCriHandleList_callbackList /* callback list */
    );
}
