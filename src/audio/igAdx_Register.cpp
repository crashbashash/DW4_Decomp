struct igMetaObject;
extern "C" {
void AdxMovieLibrary_MarkRegistered(void);
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
extern igMetaObject *g_igAdx_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *igAdx_GetMetaObject(void);
extern const char igAdx_className[];
int igAdx_GetVTable(void);
void igAdx_InitFields(void);
void FUN_003345d0(void);
void *igAdx_Register(void);
}

void *igAdx_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAdx_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAdx_GetMetaObject,
        igAdx_className,
        8, /* instance size */
        igAdx_GetVTable,
        igAdx_InitFields,
        FUN_003345d0, /* extra callback item */
        0 /* callback list */
    );
}
