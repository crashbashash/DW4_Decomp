struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWSaveCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWSaveCtrl_GetMetaObject(void);
extern const char beNDMWSaveCtrl_className[];
int beNDMWSaveCtrl_GetVTable(void);
void beNDMWSaveCtrl_InitFields(void);
extern char g_beNDMWSaveCtrl_callbackList[];
void *beNDMWSaveCtrl_Register(void);
}

void *beNDMWSaveCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWSaveCtrl_GetMetaObject,
        beNDMWSaveCtrl_className,
        0x24, /* instance size */
        beNDMWSaveCtrl_GetVTable,
        beNDMWSaveCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveCtrl_callbackList /* callback list */
    );
}
