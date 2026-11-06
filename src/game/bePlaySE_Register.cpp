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
extern igMetaObject *g_bePlaySE_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *bePlaySE_GetMetaObject(void);
extern const char bePlaySE_className[];
int bePlaySE_GetVTable(void);
void bePlaySE_InitFields(void);
void *bePlaySE_Register(void);
}

void *bePlaySE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePlaySE_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        bePlaySE_GetMetaObject,
        bePlaySE_className,
        0x18, /* instance size */
        bePlaySE_GetVTable,
        bePlaySE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
