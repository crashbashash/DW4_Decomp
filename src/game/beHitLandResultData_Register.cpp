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
extern igMetaObject *g_beHitLandResultData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beHitLandResultData_GetMetaObject(void);
extern const char beHitLandResultData_className[];
int beHitLandResultData_GetVTable(void);
void beHitLandResultData_InitFields(void);
void *beHitLandResultData_Register(void);
}

void *beHitLandResultData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandResultData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandResultData_GetMetaObject,
        beHitLandResultData_className,
        0x58, /* instance size */
        beHitLandResultData_GetVTable,
        beHitLandResultData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
