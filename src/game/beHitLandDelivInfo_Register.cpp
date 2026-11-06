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
extern igMetaObject *g_beHitLandDelivInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beHitLandDelivInfo_GetMetaObject(void);
extern const char beHitLandDelivInfo_className[];
int beHitLandDelivInfo_GetVTable(void);
void *beHitLandDelivInfo_Register(void);
}

void *beHitLandDelivInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandDelivInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beHitLandDelivInfo_GetMetaObject,
        beHitLandDelivInfo_className,
        0x1c, /* instance size */
        beHitLandDelivInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
