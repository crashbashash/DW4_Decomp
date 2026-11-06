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
extern igMetaObject *g_beXboxImage24k_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beXboxImage24k_GetMetaObject(void);
extern const char beXboxImage24k_className[];
int beXboxImage24k_GetVTable(void);
void beXboxImage24k_InitFields(void);
void *beXboxImage24k_Register(void);
}

void *beXboxImage24k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beXboxImage24k_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beXboxImage24k_GetMetaObject,
        beXboxImage24k_className,
        0x10, /* instance size */
        beXboxImage24k_GetVTable,
        beXboxImage24k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
