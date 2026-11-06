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
extern igMetaObject *g_beWaterMoveData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beWaterMoveData_GetMetaObject(void);
extern const char beWaterMoveData_className[];
int beWaterMoveData_GetVTable(void);
void beWaterMoveData_InitFields(void);
extern char g_beWaterMoveData_callbackList[];
void *beWaterMoveData_Register(void);
}

void *beWaterMoveData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterMoveData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMoveData_GetMetaObject,
        beWaterMoveData_className,
        0x18, /* instance size */
        beWaterMoveData_GetVTable,
        beWaterMoveData_InitFields,
        0, /* extra callback item */
        g_beWaterMoveData_callbackList /* callback list */
    );
}
