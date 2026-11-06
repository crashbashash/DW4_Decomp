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
extern igMetaObject *g_beSeCtl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beSeCtl_GetMetaObject(void);
extern const char beSeCtl_className[];
int beSeCtl_GetVTable(void);
void beSeCtl_InitFields(void);
extern char g_beSeCtl_callbackList[];
void *beSeCtl_Register(void);
}

void *beSeCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSeCtl_GetMetaObject,
        beSeCtl_className,
        0x24, /* instance size */
        beSeCtl_GetVTable,
        beSeCtl_InitFields,
        0, /* extra callback item */
        g_beSeCtl_callbackList /* callback list */
    );
}
