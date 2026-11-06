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
extern igMetaObject *g_beMatCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beMatCtrl_GetMetaObject(void);
extern const char beMatCtrl_className[];
int beMatCtrl_GetVTable(void);
void beMatCtrl_InitFields(void);
extern char g_beMatCtrl_callbackList[];
void *beMatCtrl_Register(void);
}

void *beMatCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMatCtrl_GetMetaObject,
        beMatCtrl_className,
        0x44, /* instance size */
        beMatCtrl_GetVTable,
        beMatCtrl_InitFields,
        0, /* extra callback item */
        g_beMatCtrl_callbackList /* callback list */
    );
}
