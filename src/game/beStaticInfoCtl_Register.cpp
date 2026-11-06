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
extern igMetaObject *g_beStaticInfoCtl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beStaticInfoCtl_GetMetaObject(void);
extern const char beStaticInfoCtl_className[];
int beStaticInfoCtl_GetVTable(void);
void beStaticInfoCtl_InitFields(void);
extern char g_beStaticInfoCtl_callbackList[];
void *beStaticInfoCtl_Register(void);
}

void *beStaticInfoCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beStaticInfoCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beStaticInfoCtl_GetMetaObject,
        beStaticInfoCtl_className,
        0x24, /* instance size */
        beStaticInfoCtl_GetVTable,
        beStaticInfoCtl_InitFields,
        0, /* extra callback item */
        g_beStaticInfoCtl_callbackList /* callback list */
    );
}
