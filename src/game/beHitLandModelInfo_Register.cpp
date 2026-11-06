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
extern igMetaObject *g_beHitLandModelInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beHitLandModelInfo_GetMetaObject(void);
extern const char beHitLandModelInfo_className[];
int beHitLandModelInfo_GetVTable(void);
void beHitLandModelInfo_InitFields(void);
extern char g_beHitLandModelInfo_callbackList[];
void *beHitLandModelInfo_Register(void);
}

void *beHitLandModelInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beHitLandModelInfo_GetMetaObject,
        beHitLandModelInfo_className,
        0x2c, /* instance size */
        beHitLandModelInfo_GetVTable,
        beHitLandModelInfo_InitFields,
        0, /* extra callback item */
        g_beHitLandModelInfo_callbackList /* callback list */
    );
}
