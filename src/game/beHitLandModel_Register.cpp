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
extern igMetaObject *g_beHitLandModel_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beHitLandModel_GetMetaObject(void);
extern const char beHitLandModel_className[];
int beHitLandModel_GetVTable(void);
void beHitLandModel_InitFields(void);
extern char g_beHitLandModel_callbackList[];
void *beHitLandModel_Register(void);
}

void *beHitLandModel_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModel_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandModel_GetMetaObject,
        beHitLandModel_className,
        0x70, /* instance size */
        beHitLandModel_GetVTable,
        beHitLandModel_InitFields,
        0, /* extra callback item */
        g_beHitLandModel_callbackList /* callback list */
    );
}
