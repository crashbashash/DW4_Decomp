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
extern igMetaObject *g_beWaterMove_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beWaterMove_GetMetaObject(void);
extern const char beWaterMove_className[];
int beWaterMove_GetVTable(void);
void beWaterMove_InitFields(void);
extern char g_beWaterMove_callbackList[];
void *beWaterMove_Register(void);
}

void *beWaterMove_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterMove_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMove_GetMetaObject,
        beWaterMove_className,
        0x28, /* instance size */
        beWaterMove_GetVTable,
        beWaterMove_InitFields,
        0, /* extra callback item */
        g_beWaterMove_callbackList /* callback list */
    );
}
