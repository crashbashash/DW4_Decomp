struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWItemBase_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWItemBase_GetMetaObject(void);
extern const char beNDMWItemBase_className[];
void beNDMWItemBase_InitFields(void);
void *beNDMWItemBase_Register(void);
}

void *beNDMWItemBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWItemBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWItemBase_GetMetaObject,
        beNDMWItemBase_className,
        0x14, /* instance size */
        0,
        beNDMWItemBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
