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
extern igMetaObject *g_beSwitchCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beSwitchCtrl_GetMetaObject(void);
extern const char beSwitchCtrl_className[];
int beSwitchCtrl_GetVTable(void);
void *beSwitchCtrl_Register(void);
}

void *beSwitchCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSwitchCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSwitchCtrl_GetMetaObject,
        beSwitchCtrl_className,
        0x20, /* instance size */
        beSwitchCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
