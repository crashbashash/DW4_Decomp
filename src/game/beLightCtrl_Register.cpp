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
extern igMetaObject *g_beLightCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beLightCtrl_GetMetaObject(void);
extern const char beLightCtrl_className[];
int beLightCtrl_GetVTable(void);
void *beLightCtrl_Register(void);
}

void *beLightCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLightCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLightCtrl_GetMetaObject,
        beLightCtrl_className,
        0x20, /* instance size */
        beLightCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
