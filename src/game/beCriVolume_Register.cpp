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
extern igMetaObject *g_beCriVolume_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beCriVolume_GetMetaObject(void);
extern const char beCriVolume_className[];
int beCriVolume_GetVTable(void);
void beCriVolume_InitFields(void);
void *beCriVolume_Register(void);
}

void *beCriVolume_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriVolume_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriVolume_GetMetaObject,
        beCriVolume_className,
        0x20, /* instance size */
        beCriVolume_GetVTable,
        beCriVolume_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
