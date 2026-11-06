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
extern igMetaObject *g_beNumberCtrl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNumberCtrl_GetMetaObject(void);
extern const char beNumberCtrl_className[];
int beNumberCtrl_GetVTable(void);
void *beNumberCtrl_Register(void);
}

void *beNumberCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNumberCtrl_GetMetaObject,
        beNumberCtrl_className,
        0x20, /* instance size */
        beNumberCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
