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
extern igMetaObject *g_beHitLandDeliv_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beHitLandDeliv_GetMetaObject(void);
extern const char beHitLandDeliv_className[];
int beHitLandDeliv_GetVTable(void);
void *beHitLandDeliv_Register(void);
}

void *beHitLandDeliv_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandDeliv_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandDeliv_GetMetaObject,
        beHitLandDeliv_className,
        0x20, /* instance size */
        beHitLandDeliv_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
