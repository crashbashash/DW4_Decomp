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
extern igMetaObject *g_beSaveDataDeliver_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSaveDataDeliver_GetMetaObject(void);
extern const char beSaveDataDeliver_className[];
int beSaveDataDeliver_GetVTable(void);
void beSaveDataDeliver_InitFields(void);
void *beSaveDataDeliver_Register(void);
}

void *beSaveDataDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveDataDeliver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveDataDeliver_GetMetaObject,
        beSaveDataDeliver_className,
        0x10, /* instance size */
        beSaveDataDeliver_GetVTable,
        beSaveDataDeliver_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
