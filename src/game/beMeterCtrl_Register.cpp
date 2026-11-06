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
extern igMetaObject *g_beMeterCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beMeterCtrl_GetMetaObject(void);
extern const char beMeterCtrl_className[];
int beMeterCtrl_GetVTable(void);
void *beMeterCtrl_Register(void);
}

void *beMeterCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMeterCtrl_GetMetaObject,
        beMeterCtrl_className,
        0x20, /* instance size */
        beMeterCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
