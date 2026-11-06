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
extern igMetaObject *g_beHitLandModelOrder_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beHitLandModelOrder_GetMetaObject(void);
extern const char beHitLandModelOrder_className[];
int beHitLandModelOrder_GetVTable(void);
void beHitLandModelOrder_InitFields(void);
extern char g_beHitLandModelOrder_callbackList[];
void *beHitLandModelOrder_Register(void);
}

void *beHitLandModelOrder_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModelOrder_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandModelOrder_GetMetaObject,
        beHitLandModelOrder_className,
        0x3c, /* instance size */
        beHitLandModelOrder_GetVTable,
        beHitLandModelOrder_InitFields,
        0, /* extra callback item */
        g_beHitLandModelOrder_callbackList /* callback list */
    );
}
