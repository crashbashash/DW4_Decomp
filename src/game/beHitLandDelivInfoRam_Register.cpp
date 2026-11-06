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
extern igMetaObject *g_beHitLandDelivInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beHitLandDelivInfoRam_GetMetaObject(void);
extern const char beHitLandDelivInfoRam_className[];
int beHitLandDelivInfoRam_GetVTable(void);
void beHitLandDelivInfoRam_InitFields(void);
extern char g_beHitLandDelivInfoRam_callbackList[];
void *beHitLandDelivInfoRam_Register(void);
}

void *beHitLandDelivInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandDelivInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandDelivInfoRam_GetMetaObject,
        beHitLandDelivInfoRam_className,
        0x68, /* instance size */
        beHitLandDelivInfoRam_GetVTable,
        beHitLandDelivInfoRam_InitFields,
        0, /* extra callback item */
        g_beHitLandDelivInfoRam_callbackList /* callback list */
    );
}
