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
extern igMetaObject *g_beLayerCtl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beLayerCtl_GetMetaObject(void);
extern const char beLayerCtl_className[];
int beLayerCtl_GetVTable(void);
void beLayerCtl_InitFields(void);
extern char g_beLayerCtl_callbackList[];
void *beLayerCtl_Register(void);
}

void *beLayerCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLayerCtl_GetMetaObject,
        beLayerCtl_className,
        0x28, /* instance size */
        beLayerCtl_GetVTable,
        beLayerCtl_InitFields,
        0, /* extra callback item */
        g_beLayerCtl_callbackList /* callback list */
    );
}
