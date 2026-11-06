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
extern igMetaObject *g_beFile_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beFile_GetMetaObject(void);
extern const char beFile_className[];
int beFile_GetVTable(void);
void *beFile_Register(void);
}

void *beFile_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFile_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFile_GetMetaObject,
        beFile_className,
        8, /* instance size */
        beFile_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
