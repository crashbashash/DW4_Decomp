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
extern igMetaObject *g_beTextureCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beTextureCtrl_GetMetaObject(void);
extern const char beTextureCtrl_className[];
int beTextureCtrl_GetVTable(void);
void beTextureCtrl_InitFields(void);
extern char g_beTextureCtrl_callbackList[];
void *beTextureCtrl_Register(void);
}

void *beTextureCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beTextureCtrl_GetMetaObject,
        beTextureCtrl_className,
        0x28, /* instance size */
        beTextureCtrl_GetVTable,
        beTextureCtrl_InitFields,
        0, /* extra callback item */
        g_beTextureCtrl_callbackList /* callback list */
    );
}
