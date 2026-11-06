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
extern igMetaObject *g_beActionStarter_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beActionStarter_GetMetaObject(void);
extern const char beActionStarter_className[];
int beActionStarter_GetVTable(void);
void *beActionStarter_Register(void);
}

void *beActionStarter_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarter_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beActionStarter_GetMetaObject,
        beActionStarter_className,
        0x20, /* instance size */
        beActionStarter_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
