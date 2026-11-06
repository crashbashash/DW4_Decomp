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
extern igMetaObject *g_beHitLandModelInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beHitLandModelInfoRam_GetMetaObject(void);
extern const char beHitLandModelInfoRam_className[];
int beHitLandModelInfoRam_GetVTable(void);
void *beHitLandModelInfoRam_Register(void);
}

void *beHitLandModelInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandModelInfoRam_GetMetaObject,
        beHitLandModelInfoRam_className,
        0x2c, /* instance size */
        beHitLandModelInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
