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
extern igMetaObject *g_beUnicode_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beUnicode_GetMetaObject(void);
extern const char beUnicode_className[];
int beUnicode_GetVTable(void);
void *beUnicode_Register(void);
}

void *beUnicode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beUnicode_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beUnicode_GetMetaObject,
        beUnicode_className,
        8, /* instance size */
        beUnicode_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
