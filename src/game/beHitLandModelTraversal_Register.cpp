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
extern igMetaObject *g_beHitLandModelTraversal_metaObject[];
void *igIntersectTraversal_Register(void);
igMetaObject *igIntersectTraversal_GetPublishedMetaObject(void);
igMetaObject *beHitLandModelTraversal_GetMetaObject(void);
extern const char beHitLandModelTraversal_className[];
int beHitLandModelTraversal_GetVTable(void);
void beHitLandModelTraversal_InitFields(void);
extern char g_beHitLandModelTraversal_callbackList[];
void *beHitLandModelTraversal_Register(void);
}

void *beHitLandModelTraversal_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelTraversal_metaObject,
        igIntersectTraversal_Register,
        igIntersectTraversal_GetPublishedMetaObject,
        beHitLandModelTraversal_GetMetaObject,
        beHitLandModelTraversal_className,
        0x48, /* instance size */
        beHitLandModelTraversal_GetVTable,
        beHitLandModelTraversal_InitFields,
        0, /* extra callback item */
        g_beHitLandModelTraversal_callbackList /* callback list */
    );
}
