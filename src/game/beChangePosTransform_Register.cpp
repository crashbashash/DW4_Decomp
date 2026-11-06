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
extern igMetaObject *g_beChangePosTransform_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beChangePosTransform_GetMetaObject(void);
extern const char beChangePosTransform_className[];
int beChangePosTransform_GetVTable(void);
void beChangePosTransform_InitFields(void);
void *beChangePosTransform_Register(void);
}

void *beChangePosTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beChangePosTransform_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beChangePosTransform_GetMetaObject,
        beChangePosTransform_className,
        0x2c, /* instance size */
        beChangePosTransform_GetVTable,
        beChangePosTransform_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
