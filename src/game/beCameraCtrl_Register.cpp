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
extern igMetaObject *g_beCameraCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beCameraCtrl_GetMetaObject(void);
extern const char beCameraCtrl_className[];
int beCameraCtrl_GetVTable(void);
void beCameraCtrl_InitFields(void);
extern char g_beCameraCtrl_callbackList[];
void *beCameraCtrl_Register(void);
}

void *beCameraCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beCameraCtrl_GetMetaObject,
        beCameraCtrl_className,
        0xdc, /* instance size */
        beCameraCtrl_GetVTable,
        beCameraCtrl_InitFields,
        0, /* extra callback item */
        g_beCameraCtrl_callbackList /* callback list */
    );
}
